#include <minilang/ml_library.h>
#include <minilang/ml_macros.h>
#include <minilang/ml_object.h>
#include <minilang/ml_stream.h>
#include <geos_c.h>

typedef struct {
	ml_type_t *Type;
	GEOSContextHandle_t Handle;
} context_t;

extern ml_type_t ContextT[];

static void context_finalize(context_t *Context, void *Data) {
	GEOS_finish_r(Context->Handle);
}

ML_FUNCTION(Context) {
	context_t *Context = new(context_t);
	Context->Type = ContextT;
	Context->Handle = GEOS_init_r();
	GC_register_finalizer(Context, (GC_finalization_proc)context_finalize, NULL, NULL, NULL);
	return (ml_value_t *)Context;
}

ML_TYPE(ContextT, (), "geos::context",
	.Constructor = (ml_value_t *)Context
);

typedef struct {
	ml_type_t *Type;
	GEOSGeometry *Handle;
	GEOSContextHandle_t Context;
} geometry_t;

ML_TYPE(GeometryT, (), "geos::geometry");

static void geometry_finalize(geometry_t *Geometry, void *Data) {
	GEOSGeom_destroy_r(Geometry->Context, Geometry->Handle);
}

static ml_value_t *geometry(GEOSContextHandle_t Context, GEOSGeometry *Handle) {
	geometry_t *Geometry = new(geometry_t);
	Geometry->Type = GeometryT;
	Geometry->Handle = Handle;
	Geometry->Context = Context;
	GC_register_finalizer(Geometry, (GC_finalization_proc)geometry_finalize, NULL, NULL, NULL);
	return (ml_value_t *)Geometry;
}

ML_METHOD("rectangle", ContextT, MLRealT, MLRealT, MLRealT, MLRealT) {
	context_t *Context = (context_t *)Args[0];
	return geometry(
		Context->Handle,
		GEOSGeom_createRectangle_r(Context->Handle,
			ml_real_value(Args[1]), ml_real_value(Args[2]),
			ml_real_value(Args[3]), ml_real_value(Args[4])
		)
	);
}

typedef struct {
	ml_type_t *Type;
	GEOSSTRtree *Handle;
	GEOSContextHandle_t Context;
} tree_t;

ML_TYPE(TreeT, (), "geos::tree");

static void tree_finalize(tree_t *Tree, void *Data) {
	GEOSSTRtree_destroy_r(Tree->Context, Tree->Handle);
}

ML_METHOD("tree", ContextT) {
	context_t *Context = (context_t *)Args[0];
	tree_t *Tree = new(tree_t);
	Tree->Type = TreeT;
	Tree->Handle = GEOSSTRtree_create_r(Context->Handle, 10);
	Tree->Context = Context->Handle;
	GC_register_finalizer(Tree, (GC_finalization_proc)tree_finalize, NULL, NULL, NULL);
	return (ml_value_t *)Tree;
}

ML_METHOD("insert", TreeT, GeometryT, MLAnyT) {
	tree_t *Tree = (tree_t *)Args[0];
	geometry_t *Geometry = (geometry_t *)Args[1];
	GEOSSTRtree_insert_r(Tree->Context, Tree->Handle, Geometry->Handle, Args[2]);
	return MLNil;
}

static void query_callback(ml_value_t *Item, ml_value_t *List) {
	ml_list_put(List, Item);
}

ML_LIBRARY_ENTRY0 {
#include "geos_init.c"
	Slot[0] = (ml_value_t *)ContextT;
}
