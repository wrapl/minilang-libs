#include <minilang/ml_library.h>
#include <minilang/ml_array.h>
#include <minilang/ml_object.h>
#include <gc/gc_cpp.h>
#include <uWebSockets/App.h>

#define anew(T, N) ((T *)GC_MALLOC((N) * sizeof(T)))

static ml_value_t *ml_string_copy(const std::string_view &View) {
	int Size = View.size();
	char Chars[Size + 1];
	View.copy(Chars, Size);
	Chars[Size] = 0;
	return ml_string_copy(Chars, Size);
}

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

template<bool SSL> static ml_value_t *response_status(ml_value_t **Args) {
	auto Response = (response_t<SSL> *)Args[0];
	Response->Handle->writeStatus(ml_string_value(Args[1]));
	return (ml_value_t *)Response;
}

ML_METHOD("status", ResponseT, MLStringT) {
	return response_status<false>(Args);
}

ML_METHOD("status", ResponseSSLT, MLStringT) {
	return response_status<true>(Args);
}

template<bool SSL> static ml_value_t *response_header(ml_value_t **Args) {
	auto Response = (response_t<SSL> *)Args[0];
	Response->Handle->writeHeader(ml_string_value(Args[1]), ml_string_value(Args[2]));
	return (ml_value_t *)Response;
}

ML_METHOD("header", ResponseT, MLStringT, MLStringT) {
	return response_header<false>(Args);
}

ML_METHOD("status", ResponseSSLT, MLStringT, MLStringT) {
	return response_header<true>(Args);
}

template<bool SSL> static ml_value_t *response_write(ml_value_t **Args) {
	auto Response = (response_t<SSL> *)Args[0];
	std::string_view Content(ml_address_value(Args[1]), ml_address_length(Args[1]));
	Response->Handle->write(Content);
	return (ml_value_t *)Response;
}

ML_METHOD("write", ResponseT, MLAddressT) {
	return response_write<false>(Args);
}

ML_METHOD("write", ResponseSSLT, MLAddressT) {
	return response_write<true>(Args);
}

template<bool SSL> static ml_value_t *response_end(ml_value_t **Args) {
	auto Response = (response_t<SSL> *)Args[0];
	Response->Handle->end("", false);
	return (ml_value_t *)Response;
}

ML_METHOD("end", ResponseT, MLStringT) {
	return response_end<false>(Args);
}

ML_METHOD("end", ResponseSSLT, MLStringT) {
	return response_end<true>(Args);
}

template<bool SSL> static ml_value_t *app_get(ml_context_t *Context, ml_value_t **Args) {
	auto App = (app_t<SSL> *)Args[0];
	std::string Path(ml_string_value(Args[1]));
	ml_value_t *Callback = Args[2];
	App->Handle.get(Path, [App, Context, Callback](uWS::HttpResponse<SSL> *Res, uWS::HttpRequest *Req) {
		ml_value_t **Args = ml_alloc_args(6);
		Args[0] = (ml_value_t *)App;
		auto Response = new response_t<SSL>(Res);
		Args[1] = (ml_value_t *)Response;
		Args[2] = ml_string_copy(Req->getUrl());
		Args[3] = ml_string_copy(Req->getQuery());
		ml_value_t *Headers = Args[2] = ml_list();
		for (auto Header = Req->begin(); Header != Req->end(); ++Header) {
			ml_value_t *Key = ml_string_copy(Header.ptr->key);
			ml_value_t *Value = ml_string_copy(Header.ptr->value);
			ml_list_put(Headers, ml_tuplev(2, Key, Value));
		}
		ml_result_state_t *State = ml_result_state(Context);
		ml_call(State, Callback, 4, Args);
	});
	return (ml_value_t *)App;
}

ML_METHODX("get", AppT, MLStringT, MLFunctionT) {
	ML_RETURN(app_get<false>(Caller->Context, Args));
}

ML_METHODX("get", AppSSLT, MLStringT, MLFunctionT) {
	ML_RETURN(app_get<true>(Caller->Context, Args));
}

ML_LIBRARY_ENTRY0(web_uwebsockets) {
#include "uwebsockets_init.cpp"
	Slot[0] = ml_module("uwebsockets",
		"app", AppT,
	NULL);
}
