#include <minilang/ml_library.h>
#include <minilang/ml_array.h>
#include <minilang/ml_object.h>
#include <gc/gc_cpp.h>
#include <uWebSockets/App.h>

#define anew(T, N) ((T *)GC_MALLOC((N) * sizeof(T)))

#undef ML_CATEGORY
#define ML_CATEGORY "web/uwebsockets"

ML_TYPE(AppT, (), "uwebsockets::app");

ML_TYPE(AppSSLT, (AppT), "uwebsockets::app::ssl");

template<bool SSL> struct app_t : gc_cleanup {
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
	auto App = new app_t<false>();
	return (ml_value_t *)App;
}

ML_TYPE(ResponseT, (), "uwebsockets::response");

ML_TYPE(ResponseSSLT, (ResponseT), "uwebsockets::response");

template<bool SSL> struct response_t : gc_cleanup {
	ml_type_t *Type;
	uWS::HttpResponse<SSL> *Handle;

	response_t(uWS::HttpResponse<SSL> *Handle) : Handle(Handle) {
		Type = ResponseT;
	}

	~response_t() {
		if (Handle) Handle->tryEnd("", 0, true);
	}
};

static ml_value_t *ml_string_copy(const std::string_view &View) {
	int Size = View.size();
	char Chars[Size + 1];
	View.copy(Chars, Size);
	Chars[Size] = 0;
	return ml_string_copy(Chars, Size);
}

template<bool SSL> static ml_value_t *app_get(ml_value_t **Args) {
	auto App = (app_t<SSL> *)Args[0];
	std::string Path(ml_string_value(Args[1]));
	App->Handle.get(Path, [](uWS::HttpResponse<SSL> *Res, uWS::HttpRequest *Req) {
		ml_value_t **Args = ml_alloc_args(6);
		Args[0] = ml_string_copy(Req->getUrl());
		Args[1] = ml_string_copy(Req->getQuery());
		ml_value_t *Headers = Args[2] = ml_list();
		for (auto Header : Req->headers) {
			ml_value_t *Key = ml_string_copy(Header.key);
			ml_value_t *Value = ml_string_copy(Header.value);
			ml_list_put(Headers, ml_tuplev(2, Key, Value));
		}

	});
	return Args[0];
}

ML_METHOD("get", AppT, MLStringT, MLFunctionT) {
	return app_get<false>(Args);
}

ML_METHOD("get", AppSSLT, MLStringT, MLFunctionT) {
	return app_get<true>(Args);
}

ML_LIBRARY_ENTRY0(web_uwebsockets) {
#include "uwebsockets_init.cpp"
	Slot[0] = ml_module("uwebsockets",
		"app", AppT,
	NULL);
}
