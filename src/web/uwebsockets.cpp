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

static void response_run(ml_state_t *State, ml_value_t *Value) {
	fprintf(stderr, "Response completed\n");
	if (ml_is_error(Value)) {
		fprintf(stderr, "%s: %s\n", ml_error_type(Value), ml_error_message(Value));
		ml_source_t Source;
		int Level = 0;
		while (ml_error_source(Value, Level++, &Source)) {
			fprintf(stderr, "\t%s:%d\n", Source.Name, Source.Line);
		}
	}
}

#include "uwebsockets2.cpp"

#define SSL_VERSION

#include "uwebsockets2.cpp"

static void *app_fn(void *Data) {
	fprintf(stderr, "Creating app thread\n");
	app_t *App = (app_t *)Data;
	new (&App->Handle) uWS::App();
	fprintf(stderr, "Waiting for signal\n");
	pthread_mutex_lock(App->Lock);
	pthread_cond_wait(App->Ready, App->Lock);
	fprintf(stderr, "Running app loop\n");
	App->Handle.run();
	fprintf(stderr, "Exiting app loop\n");
	return NULL;
}

ML_METHOD(AppT) {
	app_t *App = new (GC) app_t;
	App->Type = AppT;
	pthread_mutex_init(App->Lock, NULL);
	pthread_cond_init(App->Ready, NULL);
	GC_pthread_create(&App->Thread, NULL, app_fn, App);
	return (ml_value_t *)App;
}

ML_LIBRARY_ENTRY0(web_uwebsockets) {
#include "uwebsockets_init.cpp"
	Slot[0] = ml_module("uwebsockets",
		"app", AppT,
	NULL);
}
