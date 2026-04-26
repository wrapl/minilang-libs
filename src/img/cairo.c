#include "../util/gir.h"
#include <minilang/ml_library.h>
#include <minilang/ml_macros.h>
#include <minilang/ml_stream.h>
#include <minilang/ml_array.h>
#include <cairo.h>

#undef ML_CATEGORY
#define ML_CATEGORY "img/cairo"

ml_type_t *CairoContextT;
ml_type_t *CairoSurfaceT;
ml_type_t *CairoPatternT;
ml_type_t *CairoFormatT;
ml_type_t *CairoAntialiasT;
ml_type_t *CairoFillRuleT;
ml_type_t *CairoLineCapT;
ml_type_t *CairoLineJoinT;
ml_type_t *CairoOperatorT;
ml_type_t *CairoFontSlantT;
ml_type_t *CairoFontWeightT;

ML_FUNCTION(CairoCreate) {
	ML_CHECK_ARG_COUNT(1);
	ML_CHECK_ARG_TYPE(0, CairoSurfaceT);
	cairo_surface_t *Surface = ml_gir_struct_instance_value(Args[0]);
	cairo_t *Cairo = cairo_create(Surface);
	return ml_gir_struct_instance(CairoContextT, Cairo);
}

ML_METHOD("save", CairoContextT) {
	cairo_t *Cairo = ml_gir_struct_instance_value(Args[0]);
	cairo_save(Cairo);
	return MLNil;
}

ML_METHOD("restore", CairoContextT) {
	cairo_t *Cairo = ml_gir_struct_instance_value(Args[0]);
	cairo_restore(Cairo);
	return MLNil;
}

ML_METHOD("set_source", CairoContextT, CairoPatternT) {
	cairo_t *Cairo = ml_gir_struct_instance_value(Args[0]);
	cairo_pattern_t *Pattern = ml_gir_struct_instance_value(Args[1]);
	cairo_set_source(Cairo, Pattern);
	return MLNil;
}

ML_METHOD("set_source_rgb", CairoContextT, MLRealT, MLRealT, MLRealT) {
	cairo_t *Cairo = ml_gir_struct_instance_value(Args[0]);
	double Red = ml_real_value(Args[1]);
	double Green = ml_real_value(Args[2]);
	double Blue = ml_real_value(Args[3]);
	cairo_set_source_rgb(Cairo, Red, Green, Blue);
	return MLNil;
}

ML_METHOD("set_source_rgba", CairoContextT, MLRealT, MLRealT, MLRealT, MLRealT) {
	cairo_t *Cairo = ml_gir_struct_instance_value(Args[0]);
	double Red = ml_real_value(Args[1]);
	double Green = ml_real_value(Args[2]);
	double Blue = ml_real_value(Args[3]);
	double Alpha = ml_real_value(Args[4]);
	cairo_set_source_rgba(Cairo, Red, Green, Blue, Alpha);
	return MLNil;
}

ML_METHOD("get_operator", CairoContextT) {
	cairo_t *Cairo = ml_gir_struct_instance_value(Args[0]);
	cairo_operator_t Operator = cairo_get_operator(Cairo);
	return ml_gir_enum_value(CairoOperatorT, Operator);
}

ML_METHOD("set_operator", CairoContextT, CairoOperatorT) {
	cairo_t *Cairo = ml_gir_struct_instance_value(Args[0]);
	cairo_operator_t Operator = ml_gir_enum_value_value(Args[1]);
	cairo_set_operator(Cairo, Operator);
	return MLNil;
}

ML_METHOD("set_line_width", CairoContextT, MLRealT) {
	cairo_t *Cairo = ml_gir_struct_instance_value(Args[0]);
	cairo_set_line_width(Cairo, ml_real_value(Args[1]));
	return MLNil;
}

ML_METHOD("get_line_width", CairoContextT) {
	cairo_t *Cairo = ml_gir_struct_instance_value(Args[0]);
	return ml_real(cairo_get_line_width(Cairo));
}

ML_METHOD("set_miter_limit", CairoContextT, MLRealT) {
	cairo_t *Cairo = ml_gir_struct_instance_value(Args[0]);
	cairo_set_miter_limit(Cairo, ml_real_value(Args[1]));
	return MLNil;
}

ML_METHOD("get_miter_limit", CairoContextT) {
	cairo_t *Cairo = ml_gir_struct_instance_value(Args[0]);
	return ml_real(cairo_get_miter_limit(Cairo));
}

ML_METHOD("set_antialias", CairoContextT, CairoAntialiasT) {
	cairo_t *Cairo = ml_gir_struct_instance_value(Args[0]);
	cairo_antialias_t Antialias = ml_gir_enum_value_value(Args[1]);
	cairo_set_antialias(Cairo, Antialias);
	return MLNil;
}

ML_METHOD("get_antialias", CairoContextT) {
	cairo_t *Cairo = ml_gir_struct_instance_value(Args[0]);
	return ml_gir_enum_value(CairoAntialiasT, cairo_get_antialias(Cairo));
}

ML_METHOD("set_fill_rule", CairoContextT, CairoFillRuleT) {
	cairo_t *Cairo = ml_gir_struct_instance_value(Args[0]);
	cairo_fill_rule_t FillRule = ml_gir_enum_value_value(Args[1]);
	cairo_set_fill_rule(Cairo, FillRule);
	return MLNil;
}

ML_METHOD("get_fill_rule", CairoContextT) {
	cairo_t *Cairo = ml_gir_struct_instance_value(Args[0]);
	return ml_gir_enum_value(CairoFillRuleT, cairo_get_fill_rule(Cairo));
}

ML_METHOD("set_line_cap", CairoContextT, CairoLineCapT) {
	cairo_t *Cairo = ml_gir_struct_instance_value(Args[0]);
	cairo_line_cap_t LineCap = ml_gir_enum_value_value(Args[1]);
	cairo_set_line_cap(Cairo, LineCap);
	return MLNil;
}

ML_METHOD("get_line_cap", CairoContextT) {
	cairo_t *Cairo = ml_gir_struct_instance_value(Args[0]);
	return ml_gir_enum_value(CairoLineCapT, cairo_get_line_cap(Cairo));
}

ML_METHOD("set_line_join", CairoContextT, CairoLineJoinT) {
	cairo_t *Cairo = ml_gir_struct_instance_value(Args[0]);
	cairo_line_join_t LineJoin = ml_gir_enum_value_value(Args[1]);
	cairo_set_line_join(Cairo, LineJoin);
	return MLNil;
}

ML_METHOD("get_line_join", CairoContextT) {
	cairo_t *Cairo = ml_gir_struct_instance_value(Args[0]);
	return ml_gir_enum_value(CairoLineJoinT, cairo_get_line_join(Cairo));
}

ML_METHOD("fill", CairoContextT) {
	cairo_t *Cairo = ml_gir_struct_instance_value(Args[0]);
	cairo_fill(Cairo);
	return MLNil;
}

ML_METHOD("fill_preserve", CairoContextT) {
	cairo_t *Cairo = ml_gir_struct_instance_value(Args[0]);
	cairo_fill_preserve(Cairo);
	return MLNil;
}

ML_METHOD("paint", CairoContextT) {
	cairo_t *Cairo = ml_gir_struct_instance_value(Args[0]);
	cairo_paint(Cairo);
	return MLNil;
}

ML_METHOD("paint_with_alpha", CairoContextT, MLRealT) {
	cairo_t *Cairo = ml_gir_struct_instance_value(Args[0]);
	double Alpha = ml_real_value(Args[1]);
	cairo_paint_with_alpha(Cairo, Alpha);
	return MLNil;
}

ML_METHOD("stroke", CairoContextT) {
	cairo_t *Cairo = ml_gir_struct_instance_value(Args[0]);
	cairo_stroke(Cairo);
	return MLNil;
}

ML_METHOD("stroke_preserve", CairoContextT) {
	cairo_t *Cairo = ml_gir_struct_instance_value(Args[0]);
	cairo_stroke_preserve(Cairo);
	return MLNil;
}

ML_METHOD("has_current_point", CairoContextT) {
	cairo_t *Cairo = ml_gir_struct_instance_value(Args[0]);
	cairo_bool_t Result = cairo_has_current_point(Cairo);
	return Result ? (ml_value_t *)MLTrue : (ml_value_t *)MLFalse;
}

ML_METHOD("new_path", CairoContextT) {
	cairo_t *Cairo = ml_gir_struct_instance_value(Args[0]);
	cairo_new_path(Cairo);
	return MLNil;
}

ML_METHOD("new_sub_path", CairoContextT) {
	cairo_t *Cairo = ml_gir_struct_instance_value(Args[0]);
	cairo_new_sub_path(Cairo);
	return MLNil;
}

ML_METHOD("close_path", CairoContextT) {
	cairo_t *Cairo = ml_gir_struct_instance_value(Args[0]);
	cairo_close_path(Cairo);
	return MLNil;
}

ML_METHOD("arc", CairoContextT, MLRealT, MLRealT, MLRealT, MLRealT, MLRealT) {
	cairo_t *Cairo = ml_gir_struct_instance_value(Args[0]);
	double XC = ml_real_value(Args[1]);
	double YC = ml_real_value(Args[2]);
	double Radius = ml_real_value(Args[3]);
	double Angle1 = ml_real_value(Args[4]);
	double Angle2 = ml_real_value(Args[5]);
	cairo_arc(Cairo, XC, YC, Radius, Angle1, Angle2);
	return MLNil;
}

ML_METHOD("arc_negative", CairoContextT, MLRealT, MLRealT, MLRealT, MLRealT, MLRealT) {
	cairo_t *Cairo = ml_gir_struct_instance_value(Args[0]);
	double XC = ml_real_value(Args[1]);
	double YC = ml_real_value(Args[2]);
	double Radius = ml_real_value(Args[3]);
	double Angle1 = ml_real_value(Args[4]);
	double Angle2 = ml_real_value(Args[5]);
	cairo_arc_negative(Cairo, XC, YC, Radius, Angle1, Angle2);
	return MLNil;
}

ML_METHOD("curve_to", CairoContextT, MLRealT, MLRealT, MLRealT, MLRealT, MLRealT, MLRealT) {
	cairo_t *Cairo = ml_gir_struct_instance_value(Args[0]);
	double X1 = ml_real_value(Args[1]);
	double Y1 = ml_real_value(Args[2]);
	double X2 = ml_real_value(Args[3]);
	double Y2 = ml_real_value(Args[4]);
	double X3 = ml_real_value(Args[5]);
	double Y3 = ml_real_value(Args[6]);
	cairo_curve_to(Cairo, X1, Y1, X2, Y2, X3, Y3);
	return MLNil;
}

ML_METHOD("line_to", CairoContextT, MLRealT, MLRealT) {
	cairo_t *Cairo = ml_gir_struct_instance_value(Args[0]);
	double X = ml_real_value(Args[1]);
	double Y = ml_real_value(Args[2]);
	cairo_line_to(Cairo, X, Y);
	return MLNil;
}

ML_METHOD("move_to", CairoContextT, MLRealT, MLRealT) {
	cairo_t *Cairo = ml_gir_struct_instance_value(Args[0]);
	double X = ml_real_value(Args[1]);
	double Y = ml_real_value(Args[2]);
	cairo_move_to(Cairo, X, Y);
	return MLNil;
}

ML_METHOD("rectangle", CairoContextT, MLRealT, MLRealT, MLRealT, MLRealT) {
	cairo_t *Cairo = ml_gir_struct_instance_value(Args[0]);
	double X = ml_real_value(Args[1]);
	double Y = ml_real_value(Args[2]);
	double Width = ml_real_value(Args[3]);
	double Height = ml_real_value(Args[4]);
	cairo_rectangle(Cairo, X, Y, Width, Height);
	return MLNil;
}

ML_METHOD("text_path", CairoContextT, MLStringT) {
	cairo_t *Cairo = ml_gir_struct_instance_value(Args[0]);
	const char *Text = ml_string_value(Args[1]);
	cairo_text_path(Cairo, Text);
	return MLNil;
}

ML_METHOD("rel_curve_to", CairoContextT, MLRealT, MLRealT, MLRealT, MLRealT, MLRealT, MLRealT) {
	cairo_t *Cairo = ml_gir_struct_instance_value(Args[0]);
	double X1 = ml_real_value(Args[1]);
	double Y1 = ml_real_value(Args[2]);
	double X2 = ml_real_value(Args[3]);
	double Y2 = ml_real_value(Args[4]);
	double X3 = ml_real_value(Args[5]);
	double Y3 = ml_real_value(Args[6]);
	cairo_rel_curve_to(Cairo, X1, Y1, X2, Y2, X3, Y3);
	return MLNil;
}

ML_METHOD("rel_line_to", CairoContextT, MLRealT, MLRealT) {
	cairo_t *Cairo = ml_gir_struct_instance_value(Args[0]);
	double X = ml_real_value(Args[1]);
	double Y = ml_real_value(Args[2]);
	cairo_rel_line_to(Cairo, X, Y);
	return MLNil;
}

ML_METHOD("rel_move_to", CairoContextT, MLRealT, MLRealT) {
	cairo_t *Cairo = ml_gir_struct_instance_value(Args[0]);
	double X = ml_real_value(Args[1]);
	double Y = ml_real_value(Args[2]);
	cairo_rel_move_to(Cairo, X, Y);
	return MLNil;
}

ML_METHOD("translate", CairoContextT, MLRealT, MLRealT) {
	cairo_t *Cairo = ml_gir_struct_instance_value(Args[0]);
	double X = ml_real_value(Args[1]);
	double Y = ml_real_value(Args[2]);
	cairo_translate(Cairo, X, Y);
	return MLNil;
}

ML_METHOD("scale", CairoContextT, MLRealT, MLRealT) {
	cairo_t *Cairo = ml_gir_struct_instance_value(Args[0]);
	double X = ml_real_value(Args[1]);
	double Y = ml_real_value(Args[2]);
	cairo_scale(Cairo, X, Y);
	return MLNil;
}

ML_METHOD("rotate", CairoContextT, MLRealT) {
	cairo_t *Cairo = ml_gir_struct_instance_value(Args[0]);
	double Angle = ml_real_value(Args[1]);
	cairo_rotate(Cairo, Angle);
	return MLNil;
}

ML_METHOD("transform", CairoContextT, MLMatrixT) {
	cairo_t *Cairo = ml_gir_struct_instance_value(Args[0]);
	cairo_matrix_t Matrix;
	ml_array_t *Array = (ml_array_t *)Args[1];
	if (Array->Dimensions[0].Size != 2) return ml_error("ShapeError", "Invalid matrix");
	if (Array->Dimensions[1].Size != 3) return ml_error("ShapeError", "Invalid matrix");
	Matrix.xx = ml_array_get_double(Array, 0, 0);
	Matrix.xy = ml_array_get_double(Array, 0, 1);
	Matrix.x0 = ml_array_get_double(Array, 0, 2);
	Matrix.yx = ml_array_get_double(Array, 1, 0);
	Matrix.yy = ml_array_get_double(Array, 1, 1);
	Matrix.y0 = ml_array_get_double(Array, 1, 2);
	cairo_transform(Cairo, &Matrix);
	return MLNil;
}

ML_METHOD("set_matrix", CairoContextT, MLMatrixT) {
	cairo_t *Cairo = ml_gir_struct_instance_value(Args[0]);
	cairo_matrix_t Matrix;
	ml_array_t *Array = (ml_array_t *)Args[1];
	if (Array->Dimensions[0].Size != 2) return ml_error("ShapeError", "Invalid matrix");
	if (Array->Dimensions[1].Size != 3) return ml_error("ShapeError", "Invalid matrix");
	Matrix.xx = ml_array_get_double(Array, 0, 0);
	Matrix.xy = ml_array_get_double(Array, 0, 1);
	Matrix.x0 = ml_array_get_double(Array, 0, 2);
	Matrix.yx = ml_array_get_double(Array, 1, 0);
	Matrix.yy = ml_array_get_double(Array, 1, 1);
	Matrix.y0 = ml_array_get_double(Array, 1, 2);
	cairo_set_matrix(Cairo, &Matrix);
	return MLNil;
}

ML_METHOD("get_matrix", CairoContextT) {
	cairo_t *Cairo = ml_gir_struct_instance_value(Args[0]);
	cairo_matrix_t Matrix;
	cairo_get_matrix(Cairo, &Matrix);
	ml_array_t *Array = ml_array(ML_ARRAY_FORMAT_F64, 2, 2, 3);
	double *Values = (double *)ml_array_data(Array);
	Values[0] = Matrix.xx;
	Values[1] = Matrix.xy;
	Values[2] = Matrix.x0;
	Values[3] = Matrix.yx;
	Values[4] = Matrix.yy;
	Values[5] = Matrix.y0;
	return (ml_value_t *)Array;
}

ML_METHOD("identity_matrix", CairoContextT) {
	cairo_t *Cairo = ml_gir_struct_instance_value(Args[0]);
	cairo_identity_matrix(Cairo);
	return MLNil;
}

ML_METHOD("select_font_face", CairoContextT, MLStringT, CairoFontSlantT, CairoFontWeightT) {
	cairo_t *Cairo = ml_gir_struct_instance_value(Args[0]);
	const char *Family = ml_string_value(Args[1]);
	cairo_font_slant_t Slant = ml_gir_enum_value_value(Args[2]);
	cairo_font_weight_t Weight = ml_gir_enum_value_value(Args[3]);
	cairo_select_font_face(Cairo, Family, Slant, Weight);
	return MLNil;
}

ML_METHOD("set_font_size", CairoContextT, MLRealT, MLRealT) {
	cairo_t *Cairo = ml_gir_struct_instance_value(Args[0]);
	double Size = ml_real_value(Args[1]);
	cairo_set_font_size(Cairo, Size);
	return MLNil;
}

ML_METHOD("show_text", CairoContextT, MLStringT) {
	cairo_t *Cairo = ml_gir_struct_instance_value(Args[0]);
	const char *Text = ml_string_value(Args[1]);
	cairo_show_text(Cairo, Text);
	return MLNil;
}

static void cairo_surface_finalizer(void *Value, void *Data) {
	cairo_surface_t *Surface = ml_gir_struct_instance_value((ml_value_t *)Value);
	cairo_surface_destroy(Surface);
}

ML_FUNCTION(CairoSurfaceCreate) {
	ML_CHECK_ARG_COUNT(3);
	ML_CHECK_ARG_TYPE(0, CairoFormatT);
	ML_CHECK_ARG_TYPE(1, MLRealT);
	ML_CHECK_ARG_TYPE(2, MLRealT);
	cairo_surface_t *Surface = cairo_image_surface_create(
		ml_gir_enum_value_value(Args[0]),
		ml_real_value(Args[1]),
		ml_real_value(Args[2])
	);
	ml_value_t *Value = ml_gir_struct_instance(CairoSurfaceT, Surface);
	GC_register_finalizer(Value, cairo_surface_finalizer, NULL, NULL, NULL);
	return Value;
}

ML_FUNCTION(CairoSurfaceCreateForData) {
	ML_CHECK_ARG_COUNT(5);
	ML_CHECK_ARG_TYPE(0, MLBufferT);
	ML_CHECK_ARG_TYPE(1, CairoFormatT);
	ML_CHECK_ARG_TYPE(2, MLRealT);
	ML_CHECK_ARG_TYPE(3, MLRealT);
	ML_CHECK_ARG_TYPE(4, MLRealT);
	cairo_surface_t *Surface = cairo_image_surface_create_for_data(
		(unsigned char *)ml_buffer_value(Args[0]),
		ml_gir_enum_value_value(Args[1]),
		ml_real_value(Args[2]),
		ml_real_value(Args[3]),
		ml_real_value(Args[4])
	);
	ml_value_t *Value = ml_gir_struct_instance(CairoSurfaceT, Surface);
	GC_register_finalizer(Value, cairo_surface_finalizer, NULL, NULL, NULL);
	return Value;
}

ML_FUNCTION(CairoSurfaceCreateFromPng) {
	ML_CHECK_ARG_COUNT(1);
	ML_CHECK_ARG_TYPE(0, MLStringT);
	cairo_surface_t *Surface = cairo_image_surface_create_from_png(
		ml_string_value(Args[0])
	);
	ml_value_t *Value = ml_gir_struct_instance(CairoSurfaceT, Surface);
	GC_register_finalizer(Value, cairo_surface_finalizer, NULL, NULL, NULL);
	return Value;
}

typedef struct {
	ml_context_t *Context;
	ml_value_t *Stream;
	union {
		typeof(ml_stream_read) *read;
		typeof(ml_stream_write) *write;
	};
} stream_context_t;

static cairo_status_t read_from_stream(stream_context_t *Reader, unsigned char *Data, unsigned int Length) {
	ml_result_state_t *State = ml_result_state(Reader->Context);
	Reader->read((ml_state_t *)State, Reader->Stream, Data, Length);
	ml_scheduler_t *Scheduler = ml_context_get_static(Reader->Context, ML_SCHEDULER_INDEX);
	while (!State->Value) Scheduler->run(Scheduler);
	ml_value_t *Result = ml_deref(State->Value);
	if (ml_is_error(Result)) return CAIRO_STATUS_WRITE_ERROR;
	//if (ml_integer_value(Result) != Length) return CAIRO_STATUS_WRITE_ERROR;
	return CAIRO_STATUS_SUCCESS;
}

ML_FUNCTIONX(CairoSurfaceCreateFromPngStream) {
	ML_CHECKX_ARG_COUNT(1);
	ML_CHECKX_ARG_TYPE(0, MLStringBufferT);
	stream_context_t Reader[1] = {{Caller->Context, Args[0]}};
	Reader->read = ml_typed_fn_get(ml_typeof(Args[0]), ml_stream_read) ?: ml_stream_read_method;
	cairo_surface_t *Surface = cairo_image_surface_create_from_png_stream(
		(cairo_read_func_t)read_from_stream,
		Reader
	);
	ml_value_t *Value = ml_gir_struct_instance(CairoSurfaceT, Surface);
	GC_register_finalizer(Value, cairo_surface_finalizer, NULL, NULL, NULL);
	ML_RETURN(Value);
}

ML_METHOD("write_to_png", CairoSurfaceT, MLStringT) {
	cairo_surface_t *Surface = ml_gir_struct_instance_value(Args[0]);
	cairo_status_t Status = cairo_surface_write_to_png(Surface, ml_string_value(Args[1]));
	if (Status == CAIRO_STATUS_SUCCESS) return Args[0];
	return ml_error("CairoError", "%s", cairo_status_to_string(Status));
}

static cairo_status_t write_to_stream(stream_context_t *Writer, const unsigned char *Data, unsigned int Length) {
	ml_result_state_t *State = ml_result_state(Writer->Context);
	Writer->write((ml_state_t *)State, Writer->Stream, Data, Length);
	ml_scheduler_t *Scheduler = ml_context_get_static(Writer->Context, ML_SCHEDULER_INDEX);
	while (!State->Value) Scheduler->run(Scheduler);
	ml_value_t *Result = ml_deref(State->Value);
	if (ml_is_error(Result)) return CAIRO_STATUS_WRITE_ERROR;
	if (ml_integer_value(Result) != Length) return CAIRO_STATUS_WRITE_ERROR;
	return CAIRO_STATUS_SUCCESS;
}

ML_METHODX("write_to_png_stream", CairoSurfaceT, MLStreamT) {
	cairo_surface_t *Surface = ml_gir_struct_instance_value(Args[0]);
	stream_context_t Writer[1] = {{Caller->Context, Args[0]}};
	Writer->write = ml_typed_fn_get(ml_typeof(Args[0]), ml_stream_write) ?: ml_stream_write_method;
	cairo_surface_write_to_png_stream(Surface, (cairo_write_func_t)write_to_stream, Writer);
	ML_RETURN(MLNil);
}

ML_METHOD("get_data", CairoSurfaceT) {
	cairo_surface_t *Surface = ml_gir_struct_instance_value(Args[0]);
	int Height = cairo_image_surface_get_height(Surface);
	int Stride = cairo_image_surface_get_stride(Surface);
	unsigned char *Pixels = cairo_image_surface_get_data(Surface);
	return ml_buffer((char *)Pixels, Height * Stride);
}

static void cairo_pattern_finalizer(void *Value, void *Data) {
	cairo_pattern_t *Pattern = ml_gir_struct_instance_value((ml_value_t *)Value);
	cairo_pattern_destroy(Pattern);
}

ML_FUNCTION(CairoPatternCreateRgb) {
	ML_CHECK_ARG_COUNT(3);
	ML_CHECK_ARG_TYPE(0, MLRealT);
	ML_CHECK_ARG_TYPE(1, MLRealT);
	ML_CHECK_ARG_TYPE(2, MLRealT);
	cairo_pattern_t *Pattern = cairo_pattern_create_rgb(
		ml_real_value(Args[0]), ml_real_value(Args[1]), ml_real_value(Args[2])
	);
	ml_value_t *Value = ml_gir_struct_instance(CairoPatternT, Pattern);
	GC_register_finalizer(Value, cairo_pattern_finalizer, NULL, NULL, NULL);
	return Value;
}

ML_FUNCTION(CairoPatternCreateRgba) {
	ML_CHECK_ARG_COUNT(4);
	ML_CHECK_ARG_TYPE(0, MLRealT);
	ML_CHECK_ARG_TYPE(1, MLRealT);
	ML_CHECK_ARG_TYPE(2, MLRealT);
	ML_CHECK_ARG_TYPE(3, MLRealT);
	cairo_pattern_t *Pattern = cairo_pattern_create_rgba(
		ml_real_value(Args[0]), ml_real_value(Args[1]), ml_real_value(Args[2]), ml_real_value(Args[3])
	);
	ml_value_t *Value = ml_gir_struct_instance(CairoPatternT, Pattern);
	GC_register_finalizer(Value, cairo_pattern_finalizer, NULL, NULL, NULL);
	return Value;
}

ML_FUNCTION(CairoPatternCreateLinear) {
	ML_CHECK_ARG_COUNT(4);
	ML_CHECK_ARG_TYPE(0, MLRealT);
	ML_CHECK_ARG_TYPE(1, MLRealT);
	ML_CHECK_ARG_TYPE(2, MLRealT);
	ML_CHECK_ARG_TYPE(3, MLRealT);
	cairo_pattern_t *Pattern = cairo_pattern_create_linear(
		ml_real_value(Args[0]), ml_real_value(Args[1]), ml_real_value(Args[2]), ml_real_value(Args[3])
	);
	ml_value_t *Value = ml_gir_struct_instance(CairoPatternT, Pattern);
	GC_register_finalizer(Value, cairo_pattern_finalizer, NULL, NULL, NULL);
	return Value;
}

ML_FUNCTION(CairoPatternCreateRadial) {
	ML_CHECK_ARG_COUNT(6);
	ML_CHECK_ARG_TYPE(0, MLRealT);
	ML_CHECK_ARG_TYPE(1, MLRealT);
	ML_CHECK_ARG_TYPE(2, MLRealT);
	ML_CHECK_ARG_TYPE(3, MLRealT);
	ML_CHECK_ARG_TYPE(4, MLRealT);
	ML_CHECK_ARG_TYPE(5, MLRealT);
	cairo_pattern_t *Pattern = cairo_pattern_create_radial(
		ml_real_value(Args[0]), ml_real_value(Args[1]), ml_real_value(Args[2]),
		ml_real_value(Args[3]), ml_real_value(Args[4]), ml_real_value(Args[5])
	);
	ml_value_t *Value = ml_gir_struct_instance(CairoPatternT, Pattern);
	GC_register_finalizer(Value, cairo_pattern_finalizer, NULL, NULL, NULL);
	return Value;
}

ML_FUNCTION(CairoPatternCreateForSurface) {
	ML_CHECK_ARG_COUNT(1);
	ML_CHECK_ARG_TYPE(0, CairoSurfaceT);
	cairo_surface_t *Surface = ml_gir_struct_instance_value(Args[0]);
	cairo_pattern_t *Pattern = cairo_pattern_create_for_surface(Surface);
	ml_value_t *Value = ml_gir_struct_instance(CairoPatternT, Pattern);
	GC_register_finalizer(Value, cairo_pattern_finalizer, NULL, NULL, NULL);
	return Value;
}

ML_METHOD("add_color_stop_rgb", CairoPatternT, MLRealT, MLRealT, MLRealT, MLRealT) {
	cairo_pattern_t *Pattern = ml_gir_struct_instance_value(Args[0]);
	cairo_pattern_add_color_stop_rgb(Pattern,
		ml_real_value(Args[1]), ml_real_value(Args[2]), ml_real_value(Args[3]), ml_real_value(Args[4])
	);
	return MLNil;
}

ML_METHOD("add_color_stop_rgba", CairoPatternT, MLRealT, MLRealT, MLRealT, MLRealT, MLRealT) {
	cairo_pattern_t *Pattern = ml_gir_struct_instance_value(Args[0]);
	cairo_pattern_add_color_stop_rgba(Pattern,
		ml_real_value(Args[1]), ml_real_value(Args[2]), ml_real_value(Args[3]),
		ml_real_value(Args[4]), ml_real_value(Args[5])
	);
	return MLNil;
}

ML_LIBRARY_ENTRY0(img_cairo) {
	ml_value_t *Typelib = ml_gir_typelib("cairo", "1.0");
	CairoContextT = (ml_type_t *)ml_gir_import(Typelib, "Context");
	CairoContextT->Constructor = (ml_value_t *)CairoCreate;
	CairoSurfaceT = (ml_type_t *)ml_gir_import(Typelib, "Surface");
	CairoFormatT = (ml_type_t *)ml_gir_import(Typelib, "Format");
	CairoAntialiasT = (ml_type_t *)ml_gir_import(Typelib, "Antialias");
	CairoFillRuleT = (ml_type_t *)ml_gir_import(Typelib, "FillRule");
	CairoLineCapT = (ml_type_t *)ml_gir_import(Typelib, "LineCap");
	CairoLineJoinT = (ml_type_t *)ml_gir_import(Typelib, "LineJoin");
	CairoOperatorT = (ml_type_t *)ml_gir_import(Typelib, "Operator");
	CairoFontSlantT = (ml_type_t *)ml_gir_import(Typelib, "FontSlant");
	CairoFontWeightT = (ml_type_t *)ml_gir_import(Typelib, "FontWeight");
	CairoPatternT = (ml_type_t *)ml_gir_import(Typelib, "Pattern");
#include "cairo_init.c"
	stringmap_insert(CairoContextT->Exports, "create", CairoCreate);
	stringmap_insert(CairoSurfaceT->Exports, "create", CairoSurfaceCreate);
	stringmap_insert(CairoSurfaceT->Exports, "create_for_data", CairoSurfaceCreateForData);
	stringmap_insert(CairoSurfaceT->Exports, "create_from_png", CairoSurfaceCreateFromPng);
	stringmap_insert(CairoSurfaceT->Exports, "create_from_png_stream", CairoSurfaceCreateFromPngStream);
	stringmap_insert(CairoPatternT->Exports, "create_rgb", CairoPatternCreateRgb);
	stringmap_insert(CairoPatternT->Exports, "create_rgba", CairoPatternCreateRgba);
	stringmap_insert(CairoPatternT->Exports, "create_linear", CairoPatternCreateLinear);
	stringmap_insert(CairoPatternT->Exports, "create_radial", CairoPatternCreateRadial);
	stringmap_insert(CairoPatternT->Exports, "create_for_surface", CairoPatternCreateForSurface);
	Slot[0] = Typelib;
}
