#include <minilang/ml_library.h>
#include <minilang/ml_array.h>
#include <minilang/ml_object.h>
#include <gc/gc_cpp.h>
#include <box2d/box2d.h>
#include <stdio.h>

#undef ML_CATEGORY
#define ML_CATEGORY "phys/box2d"

#define BOOL_FIELD(TYPE, CTYPE, FIELD) \
\
ML_METHOD(#FIELD, TYPE) { \
	CTYPE *Object = (CTYPE *)Args[0]; \
	return ml_boolean(Object->Value.FIELD); \
} \
\
ML_METHOD(#FIELD, TYPE, MLBooleanT) { \
	CTYPE *Object = (CTYPE *)Args[0]; \
	Object->Value.FIELD = ml_boolean_value(Args[1]); \
	return Args[0]; \
}

#define FLOAT_FIELD(TYPE, CTYPE, FIELD) \
\
ML_METHOD(#FIELD, TYPE) { \
	CTYPE *Object = (CTYPE *)Args[0]; \
	return ml_real(Object->Value.FIELD); \
} \
\
ML_METHOD(#FIELD, TYPE, MLRealT) { \
	CTYPE *Object = (CTYPE *)Args[0]; \
	Object->Value.FIELD = ml_real_value(Args[1]); \
	return Args[0]; \
}

#define VECTOR_FIELD(TYPE, CTYPE, FIELD) \
\
ML_METHOD(#FIELD, TYPE) { \
	CTYPE *Object = (CTYPE *)Args[0]; \
	ml_array_t *Vector = ml_array(ML_ARRAY_FORMAT_F32, 1, 2); \
	ml_array_set_float(Object->Value.FIELD.x, Vector, 0); \
	ml_array_set_float(Object->Value.FIELD.y, Vector, 1); \
	return (ml_value_t *)Vector; \
} \
\
ML_METHOD(#FIELD, TYPE, MLArrayT) { \
	CTYPE *Object = (CTYPE *)Args[0]; \
	ml_array_t *Array = (ml_array_t *)Args[1]; \
	if (Array->Degree != 1) return ml_error("ShapeError", "Invalid vector"); \
	if (Array->Dimensions[0].Size != 2) return ml_error("ShapeError", "Invalid vector"); \
	Object->Value.FIELD.x = ml_array_get_float(Array, 0); \
	Object->Value.FIELD.y = ml_array_get_float(Array, 1); \
	return Args[0]; \
}

#define ENUM_FIELD(TYPE, CTYPE, FIELD, ETYPE) \
\
ML_METHOD(#FIELD, TYPE) { \
	CTYPE *Object = (CTYPE *)Args[0]; \
	return ml_enum_value(ETYPE, Object->Value.FIELD); \
} \
\
ML_METHOD(#FIELD, TYPE, ETYPE) { \
	CTYPE *Object = (CTYPE *)Args[0]; \
	Object->Value.FIELD = (typeof(Object->Value.FIELD))ml_enum_value_value(Args[1]); \
	return Args[0]; \
}

#define ML_ARRAY_TO_B2VEC2(VALUE, USE) ({ \
	ml_array_t *Array = (ml_array_t *)VALUE; \
	if (Array->Degree != 1) return ml_error("ShapeError", "Invalid " #USE); \
	if (Array->Dimensions[0].Size != 2) return ml_error("ShapeError", "Invalid " #USE); \
	b2Vec2(ml_array_get_float(Array, 0), ml_array_get_float(Array, 1)); \
})

ML_TYPE(WorldT, (), "box2d::world");

struct world_t {
	ml_type_t *Type;
	b2World *Handle;
};

static void world_finalize(void *Ptr, void *Data) {
	delete ((world_t *)Ptr)->Handle;
}

ML_FUNCTION(World) {
	ML_CHECK_ARG_COUNT(1);
	ML_CHECK_ARG_TYPE(0, MLArrayT);
	b2Vec2 Gravity = ML_ARRAY_TO_B2VEC2(Args[0], gravity);
	world_t *World = new (GC) world_t;
	World->Type = WorldT;
	World->Handle = new b2World(Gravity);
	GC_register_finalizer(World, world_finalize, NULL, NULL, NULL);
	return (ml_value_t *)World;
}

ML_ENUM2(BodyDefTypeT, "bodydef::type",
	"Static", b2_staticBody,
	"Kinematic", b2_kinematicBody,
	"Dynamic", b2_dynamicBody
);

ML_TYPE(BodyDefT, (), "box2d::bodydef");

struct bodydef_t {
	ml_type_t *Type;
	b2BodyDef Value;
};

ENUM_FIELD(BodyDefT, bodydef_t, type, BodyDefTypeT);
VECTOR_FIELD(BodyDefT, bodydef_t, position);
FLOAT_FIELD(BodyDefT, bodydef_t, angle);
VECTOR_FIELD(BodyDefT, bodydef_t, linearVelocity);
FLOAT_FIELD(BodyDefT, bodydef_t, angularVelocity);
FLOAT_FIELD(BodyDefT, bodydef_t, linearDamping);
FLOAT_FIELD(BodyDefT, bodydef_t, angularDamping);
BOOL_FIELD(BodyDefT, bodydef_t, allowSleep);
BOOL_FIELD(BodyDefT, bodydef_t, awake);
BOOL_FIELD(BodyDefT, bodydef_t, fixedRotation);
BOOL_FIELD(BodyDefT, bodydef_t, bullet);
BOOL_FIELD(BodyDefT, bodydef_t, enabled);
FLOAT_FIELD(BodyDefT, bodydef_t, gravityScale);

ML_FUNCTION(BodyDef) {
	bodydef_t *BodyDef = new (GC) bodydef_t();
	return (ml_value_t *)BodyDef;
}

ML_TYPE(BodyT, (), "box2d::body");

struct body_t {
	ml_type_t *Type;
	b2Body *Handle;
};

ML_METHOD("create", WorldT, BodyDefT) {
	world_t *World = (world_t *)Args[0];
	bodydef_t *BodyDef = (bodydef_t *)Args[1];
	body_t *Body = new (GC) body_t;
	Body->Type = BodyT;
	Body->Handle = World->Handle->CreateBody(&BodyDef->Value);
	Body->Handle->SetUserData(Body);
	return (ml_value_t *)Body;
}

ML_TYPE(ShapeT, (), "box2d::shape");

#define SHAPE_TYPE(NAME, CNAME) \
\
ML_TYPE(NAME ## T, (ShapeT), "box2d::" #CNAME); \
\
struct CNAME ## _shape_t { \
	ml_type_t *Type; \
	b2 ## NAME ## Shape Value; \
}

SHAPE_TYPE(Chain, chain);

ML_METHOD(ChainT, MLArrayT) {
	ml_array_t *Array = (ml_array_t *)Args[0];
	if (Array->Degree != 2) return ml_error("ShapeError", "Invalid points");
	if (Array->Dimensions[1].Size != 2) return ml_error("ShapeError", "Invalid points");
	int Size = Array->Dimensions[0].Size;
	b2Vec2 Points[Size];
	ml_array_getter_float get = ml_array_float_getter(Array->Format);
	for (int I = 0; I < Size; ++I) {
		Points[I].x = get(ml_array_get(Array, I, 0));
		Points[I].y = get(ml_array_get(Array, I, 1));
	}
	chain_shape_t *Shape = new (GC) chain_shape_t;
	Shape->Type = ChainT;
	Shape->Value.CreateLoop(Points, Size);
	return (ml_value_t *)Shape;
}

SHAPE_TYPE(Circle, circle);

ML_METHOD(CircleT, MLRealT, MLArrayT) {
	b2Vec2 Position = ML_ARRAY_TO_B2VEC2(Args[1], position);
	circle_shape_t *Shape = new (GC) circle_shape_t;
	Shape->Type = CircleT;
	Shape->Value.m_radius = ml_real_value(Args[0]);
	Shape->Value.m_p = Position;
	return (ml_value_t *)Shape;
}

SHAPE_TYPE(Edge, edge);

ML_METHOD(EdgeT, MLArrayT, MLArrayT, MLArrayT, MLArrayT) {
	b2Vec2 V0 = ML_ARRAY_TO_B2VEC2(Args[0], "v0");
	b2Vec2 V1 = ML_ARRAY_TO_B2VEC2(Args[0], "v1");
	b2Vec2 V2 = ML_ARRAY_TO_B2VEC2(Args[0], "v2");
	b2Vec2 V3 = ML_ARRAY_TO_B2VEC2(Args[0], "v3");
	edge_shape_t *Shape = new (GC) edge_shape_t;
	Shape->Type = EdgeT;
	Shape->Value.SetOneSided(V0, V1, V2, V3);
	return (ml_value_t *)Shape;
}

ML_METHOD(EdgeT, MLArrayT, MLArrayT) {
	b2Vec2 V0 = ML_ARRAY_TO_B2VEC2(Args[0], "v0");
	b2Vec2 V1 = ML_ARRAY_TO_B2VEC2(Args[0], "v1");
	edge_shape_t *Shape = new (GC) edge_shape_t;
	Shape->Type = EdgeT;
	Shape->Value.SetTwoSided(V0, V1);
	return (ml_value_t *)Shape;
}

SHAPE_TYPE(Polygon, polygon);

ML_METHOD(PolygonT, MLArrayT) {
	ml_array_t *Array = (ml_array_t *)Args[0];
	if (Array->Degree != 2) return ml_error("ShapeError", "Invalid points");
	if (Array->Dimensions[1].Size != 2) return ml_error("ShapeError", "Invalid points");
	int Size = Array->Dimensions[0].Size;
	b2Vec2 Points[Size];
	ml_array_getter_float get = ml_array_float_getter(Array->Format);
	for (int I = 0; I < Size; ++I) {
		Points[I].x = get(ml_array_get(Array, I, 0));
		Points[I].y = get(ml_array_get(Array, I, 1));
	}
	polygon_shape_t *Shape = new (GC) polygon_shape_t;
	Shape->Type = PolygonT;
	Shape->Value.Set(Points, Size);
	return (ml_value_t *)Shape;
}

ML_METHOD(PolygonT, MLRealT, MLRealT) {
	polygon_shape_t *Shape = new (GC) polygon_shape_t;
	Shape->Type = PolygonT;
	Shape->Value.SetAsBox(ml_real_value(Args[0]), ml_real_value(Args[1]));
	return (ml_value_t *)Shape;
}

ML_METHOD(PolygonT, MLRealT, MLRealT, MLArrayT, MLRealT) {
	b2Vec2 Centre = ML_ARRAY_TO_B2VEC2(Args[2], "centre");
	polygon_shape_t *Shape = new (GC) polygon_shape_t;
	Shape->Type = PolygonT;
	Shape->Value.SetAsBox(ml_real_value(Args[0]), ml_real_value(Args[1]), Centre, ml_real_value(Args[3]));
	return (ml_value_t *)Shape;
}

static b2Shape *shape_value(ml_value_t *Value) {
	ml_type_t *Type = ml_typeof(Value);
	if (Type == ChainT) return &((chain_shape_t *)Value)->Value;
	if (Type == CircleT) return &((circle_shape_t *)Value)->Value;
	if (Type == EdgeT) return &((edge_shape_t *)Value)->Value;
	if (Type == PolygonT) return &((polygon_shape_t *)Value)->Value;
	__builtin_unreachable();
	return NULL;
}

ML_TYPE(FixtureDefT, (), "box2d::fixturedef");

struct fixturedef_t {
	ml_type_t *Type;
	b2FixtureDef Value;
};

ML_TYPE(FixtureT, (), "box2d::body");

struct fixture_t {
	ml_type_t *Type;
	b2Fixture *Handle;
};

ML_METHOD("create", BodyT, ShapeT, MLRealT) {
	body_t *Body = (body_t *)Args[0];
	b2Shape *Shape = shape_value(Args[1]);
	float Density = ml_real_value(Args[2]);
	fixture_t *Fixture = new (GC) fixture_t;
	Fixture->Type = FixtureT;
	Fixture->Handle = Body->Handle->CreateFixture(Shape, Density);
	return (ml_value_t *)Fixture;
}

extern "C" {

ML_LIBRARY_ENTRY0(geom_geos) {
#include "box2d_init.cpp"
	WorldT->Constructor = (ml_value_t *)World;
	Slot[0] = (ml_value_t *)WorldT;
}

}
