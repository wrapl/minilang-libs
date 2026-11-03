#include <minilang/ml_library.h>
#include <minilang/ml_object.h>
#include <minilang/ml_array.h>
#include <gc/gc_cpp.h>
#include <libcola/cola.h>

ML_TYPE(RectangleT, (), "rectangle");

struct rectangle_t : public gc {
	ml_type_t *Type;
	vpsc::Rectangle Value;
	rectangle_t(double Xmin, double Xmax, double Ymin, double Ymax, bool AllowOverlap) :
		Type(RectangleT), Value(Xmin, Xmax, Ymin, Ymax, AllowOverlap) {}
};

ML_METHOD(RectangleT, MLRealT, MLRealT, MLRealT, MLRealT) {
	return (ml_value_t *)new rectangle_t(
		ml_real_value(Args[0]), ml_real_value(Args[1]),
		ml_real_value(Args[2]), ml_real_value(Args[3]),
		false
	);
}

ML_METHOD(RectangleT, MLRealT, MLRealT, MLRealT, MLRealT, MLBooleanT) {
	return (ml_value_t *)new rectangle_t(
		ml_real_value(Args[0]), ml_real_value(Args[1]),
		ml_real_value(Args[2]), ml_real_value(Args[3]),
		Args[4] == (ml_value_t *)MLTrue
	);
}

ML_METHOD("append", MLStringBufferT, RectangleT) {
	ml_stringbuffer_t *Buffer = (ml_stringbuffer_t *)Args[0];
	rectangle_t *Rectangle = (rectangle_t *)Args[1];
	//ml_stringbuffer_printf(Buffer, "[(%f, %f) x (%f, %f)]",
}

ML_TYPE(FDLayoutT, (), "fdlayout");

struct fdlayout_t : public gc {
	ml_type_t *Type;
	cola::ConstrainedFDLayout Value;
	fdlayout_t(const vpsc::Rectangles &Rs, const std::vector<cola::Edge> &Es, const double IdealLength) :
		Type(FDLayoutT), Value(Rs, Es, IdealLength) {}
};

ML_METHOD(FDLayoutT, MLListT, MLListT, MLRealT) {
	vpsc::Rectangles Rects;
	ML_LIST_FOREACH(Args[0], Iter) {
		if (!ml_is(Iter->Value, RectangleT)) return ml_error("TypeError", "Expected rectangle");
		Rects.push_back(&((rectangle_t *)Iter->Value)->Value);
	}
	std::vector<cola::Edge> Edges;
	ML_LIST_FOREACH(Args[1], Iter) {
		if (!ml_is(Iter->Value, MLTupleT)) return ml_error("TypeError", "Expected tuple");
		if (ml_tuple_size(Iter->Value) < 2) return ml_error("ShapeError", "Expected at least 2 values");
		unsigned A = ml_integer_value(ml_tuple_get(Iter->Value, 1));
		unsigned B = ml_integer_value(ml_tuple_get(Iter->Value, 2));
		if (A == B) return ml_error("RangeError", "Invalid edge");
		if (A < 1 || B < 1 || A > Rects.size() || B > Rects.size()) return ml_error("RangeError", "Invalid edge");
		Edges.push_back(cola::Edge(A - 1, B - 1));
	}
	double IdealLength = ml_real_value(Args[2]);
	return (ml_value_t *)new fdlayout_t(Rects, Edges, IdealLength);
}

ML_ENUM2(DimT, "dim",
	"Horizontal", vpsc::Dim::HORIZONTAL,
	"Vertical", vpsc::Dim::VERTICAL,
	"Unset", vpsc::Dim::UNSET
);

ML_TYPE(ConstraintT, (), "constraint");

struct constraint_t : public gc {
	ml_type_t *Type;
	cola::CompoundConstraint *Value;
	constraint_t(ml_type_t *Type, cola::CompoundConstraint *Value) : Type(Type), Value(Value) {}
};

ML_METHOD("append", MLStringBufferT, ConstraintT) {
	ml_stringbuffer_t *Buffer = (ml_stringbuffer_t *)Args[0];
	constraint_t *Constraint = (constraint_t *)Args[1];
	std::string String = Constraint->Value->toString();
	ml_stringbuffer_write(Buffer, String.c_str(), String.size());
	return MLSome;
}

ML_METHOD("constraints", FDLayoutT, MLListT) {
	cola::CompoundConstraints Constraints;
	ML_LIST_FOREACH(Args[1], Iter) {
		if (!ml_is(Iter->Value, ConstraintT)) return ml_error("TypeError", "Expected constraint");
		constraint_t *Constraint = (constraint_t *)Iter->Value;
		Constraints.push_back(Constraint->Value);
	}
	fdlayout_t *Layout = (fdlayout_t *)Args[0];
	Layout->Value.setConstraints(Constraints);
	return (ml_value_t *)Layout;
}

ML_METHOD("run", FDLayoutT) {
	fdlayout_t *Layout = (fdlayout_t *)Args[0];
	Layout->Value.run();
	return (ml_value_t *)Layout;
}

ML_TYPE(AlignmentConstraintT, (ConstraintT), "constraint::alignment");

ML_METHOD(AlignmentConstraintT, DimT, MLRealT) {
	return (ml_value_t *)new constraint_t(AlignmentConstraintT,
		new (GC) cola::AlignmentConstraint((vpsc::Dim)ml_enum_value_value(Args[0]), ml_real_value(Args[1]))
	);
}

ML_METHOD("add", AlignmentConstraintT, MLIntegerT, MLRealT) {
	constraint_t *Constraint = (constraint_t *)Args[0];
	static_cast<cola::AlignmentConstraint *>(Constraint->Value)->addShape(ml_integer_value(Args[1]), ml_real_value(Args[2]));
	return (ml_value_t *)Constraint;
}

ML_METHOD("fix", AlignmentConstraintT, MLRealT) {
	constraint_t *Constraint = (constraint_t *)Args[0];
	static_cast<cola::AlignmentConstraint *>(Constraint->Value)->fixPos(ml_real_value(Args[1]));
	return (ml_value_t *)Constraint;
}

ML_METHOD("unfix", AlignmentConstraintT) {
	constraint_t *Constraint = (constraint_t *)Args[0];
	static_cast<cola::AlignmentConstraint *>(Constraint->Value)->unfixPos();
	return (ml_value_t *)Constraint;
}

ML_TYPE(BoundaryConstraintT, (ConstraintT), "constraint::boundary");

ML_METHOD(BoundaryConstraintT, DimT) {
	return (ml_value_t *)new constraint_t(BoundaryConstraintT,
		new (GC) cola::BoundaryConstraint((vpsc::Dim)ml_enum_value_value(Args[0]))
	);
}

ML_METHOD("add", BoundaryConstraintT, MLIntegerT, MLRealT) {
	constraint_t *Constraint = (constraint_t *)Args[0];
	static_cast<cola::BoundaryConstraint *>(Constraint->Value)->addShape(ml_integer_value(Args[1]), ml_real_value(Args[2]));
	return (ml_value_t *)Constraint;
}

ML_LIBRARY_ENTRY0(adaptagrams) {
#include "adaptagrams_init.cpp"
	Slot[0] = ml_module("adaptagrams",
		"rectangle", RectangleT,
		"fdlayout", FDLayoutT,
	NULL);
}
