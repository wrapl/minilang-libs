#include <minilang/ml_library.h>
#include <minilang/ml_array.h>
#include <minilang/ml_object.h>
#include <gc/gc_cpp.h>
#include <uWebSockets/App.h>

#undef ML_CATEGORY
#define ML_CATEGORY "web/uwebsockets"

ML_TYPE(AppT, (), "uwebsockets::app");

ML_TYPE(AppSSLT, (AppT), "uwebsockets::app::ssl");

template<bool SSL> struct app_t {
	ml_type_t *Type;
	uWS::TemplatedApp<SSL> Handle;

	app_t() : Handle() {
		Type = AppT;
	}

	app_t(uWS::SocketContextOptions Options) : Handle(Options) {
		Type = AppSSLT;
	}
};

ML_METHOD(AppT) {
	auto App = new (GC) app_t<false>;
	return (ml_value_t *)App;
}

ML_METHOD("get", AppT, MLStringT, MLFunctionT) {
	auto App = (app_t<false> *)Args[0];
	std::string Path(ml_string_value(Args[1]));
	App->Handle.get(Path, [](auto *Res, auto *Req) {
	});
}

ML_LIBRARY_ENTRY0(web_uwebsockets) {
#include "uwebsockets_init.cpp"
	Slot[0] = (ml_value_t *)AppT;
}
