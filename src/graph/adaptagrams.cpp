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
	ml_stringbuffer_printf(Buffer, "[(%f, %f) x (%f, %f)]",
		Rectangle->Value.getMinX(), Rectangle->Value.getMaxX(),
		Rectangle->Value.getMinY(), Rectangle->Value.getMaxY()
	);
	return MLSome;
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

ML_TYPE(ClusterT, (), "cluster");

struct cluster_t : public gc {
	ml_type_t *Type;
	cola::Cluster *Value;
	cluster_t(ml_type_t *Type, cola::Cluster *Value) : Type(Type), Value(Value) {}
};

ML_METHOD("add", ClusterT, MLIntegerT) {
	cluster_t *Cluster = (cluster_t *)Args[0];
	Cluster->Value->addChildNode(ml_integer_value(Args[1]));
	return (ml_value_t *)Cluster;
}

ML_METHOD("add", ClusterT, ClusterT) {
	cluster_t *Cluster = (cluster_t *)Args[0];
	cluster_t *Child = (cluster_t *)Args[1];
	Cluster->Value->addChildCluster(Child->Value);
	return (ml_value_t *)Cluster;
}

ML_TYPE(RectangularClusterT, (ClusterT), "cluster::rectangular");

ML_METHOD(RectangularClusterT) {
	return (ml_value_t *)new cluster_t(RectangularClusterT, new cola::RectangularCluster());
}

ML_METHOD(RectangularClusterT, MLIntegerT) {
	return (ml_value_t *)new cluster_t(RectangularClusterT, new cola::RectangularCluster(ml_integer_value(Args[0])));
}

ML_TYPE(ConvexClusterT, (ClusterT), "cluster::convex");

ML_METHOD(ConvexClusterT) {
	return (ml_value_t *)new cluster_t(ConvexClusterT, new cola::ConvexCluster());
}

ML_TYPE(LayoutT, (), "layout");

struct layout_t : public gc {
	ml_type_t *Type;
	vpsc::Rectangles Rects;
	std::vector<cola::Edge> Edges;
	cola::RootCluster Cluster;
	cola::CompoundConstraints Constraints;
	layout_t() : Type(LayoutT) {}
};

ML_METHOD(LayoutT) {
	return (ml_value_t *)new layout_t();
}

ML_METHOD("add", LayoutT, RectangleT) {
	layout_t *Layout = (layout_t *)Args[0];
	rectangle_t *Rect = (rectangle_t *)Args[1];
	Layout->Rects.push_back(&Rect->Value);
	return (ml_value_t *)Layout;
}

ML_METHOD("node", LayoutT, MLIntegerT) {
	layout_t *Layout = (layout_t *)Args[0];
	Layout->Cluster.addChildNode(ml_integer_value(Args[1]));
	return (ml_value_t *)Layout;
}

ML_METHOD("edge", LayoutT, MLIntegerT, MLIntegerT) {
	layout_t *Layout = (layout_t *)Args[0];
	Layout->Edges.push_back(cola::Edge(ml_integer_value(Args[1]), ml_integer_value(Args[2])));
	return (ml_value_t *)Layout;
}

ML_METHOD("add", LayoutT, ClusterT) {
	layout_t *Layout = (layout_t *)Args[0];
	cluster_t *Cluster = (cluster_t *)Args[1];
	Layout->Cluster.addChildCluster(Cluster->Value);
	return (ml_value_t *)Layout;
}

ML_METHOD("add", LayoutT, ConstraintT) {
	layout_t *Layout = (layout_t *)Args[0];
	constraint_t *Constraint = (constraint_t *)Args[1];
	Layout->Constraints.push_back(Constraint->Value);
	return (ml_value_t *)Layout;
}

ML_METHOD("fd_layout", LayoutT) {
	layout_t *Layout = (layout_t *)Args[0];
	cola::ConstrainedFDLayout FDLayout(Layout->Rects, Layout->Edges, 1);
	FDLayout.run();
	return (ml_value_t *)Layout;
}

ML_LIBRARY_ENTRY0(adaptagrams) {
	stringmap_insert(ConstraintT->Exports, "alignment", AlignmentConstraintT);
	stringmap_insert(ConstraintT->Exports, "boundary", BoundaryConstraintT);
	stringmap_insert(ClusterT->Exports, "rectangular", RectangularClusterT);
	stringmap_insert(ClusterT->Exports, "convex", ConvexClusterT);
#include "adaptagrams_init.cpp"
	Slot[0] = ml_module("adaptagrams",
		"rectangle", RectangleT,
		"dim", DimT,
		"constraint", ConstraintT,
		"cluster", ClusterT,
		"layout", LayoutT,
	NULL);
}
