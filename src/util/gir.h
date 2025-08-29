#ifndef ML_GIR_H
#define ML_GIR_H

#include <minilang/minilang.h>
#include <girepository.h>

extern ml_type_t MLGirTypelibT[];

ml_value_t *ml_gir_typelib(const char *Name, const char *Version);

GITypelib *ml_gir_get_typelib(ml_value_t *Value);
const char *ml_gir_get_namespace(ml_value_t *Value);
ml_value_t *ml_gir_import(ml_value_t *Value, const char *Name);

void ml_gir_loop_init();
void ml_gir_loop_run();
void ml_gir_loop_quit();

void ml_gir_init(stringmap_t *Globals);

ml_value_t *ml_gir_instance_get(void *Handle, ml_type_t *Fallback);

ml_value_t *ml_gir_struct_instance(ml_type_t *Struct, void *Value);
void *ml_gir_struct_instance_value(ml_value_t *Value);

ml_value_t *ml_gir_enum_value(ml_type_t *Enum, gint64 Value);
gint64 ml_gir_enum_value_value(ml_value_t *Value);

#ifndef GENERATE_INIT

#define ML_GIR_TYPELIB(VALUE, NAME, VERSION) \
static ml_value_t *VALUE

#define ML_GIR_IMPORT(VALUE, TYPELIB, NAME) \
static ml_value_t *VALUE

#else

#define ML_GIR_TYPELIB(VALUE, NAME, VERSION) INIT_CODE VALUE = ml_gir_typelib(NAME, VERSION)

#define ML_GIR_IMPORT(VALUE, TYPELIB, NAME) INIT_CODE VALUE = ml_gir_import(TYPELIB, NAME)

#endif

#endif
