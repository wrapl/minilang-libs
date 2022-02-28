#include <minilang/ml_library.h>
#include <minilang/ml_macros.h>
#include <lilv/lilv.h>

static LilvWorld *World;
static stringmap_t PluginsTable[1] = {STRINGMAP_INIT};

ML_TYPE(PluginClassT, (), "lilv-plugin-class");

typedef struct {
	ml_type_t *Type;
	const LilvPlugin *Handle;
} plugin_t;

ML_TYPE(PluginT, (), "lilv-plugin");

ML_METHOD("name", PluginT) {
	const LilvPlugin *Plugin = ((plugin_t *)Args[0])->Handle;
	const char *Name = lilv_node_as_string(lilv_plugin_get_name(Plugin));
	return ml_string(Name, -1);
}

ML_METHOD("uri", PluginT) {
	const LilvPlugin *Plugin = ((plugin_t *)Args[0])->Handle;
	const char *Name = lilv_node_as_string(lilv_plugin_get_uri(Plugin));
	return ml_string(Name, -1);
}

ML_TYPE(PortT, (), "lilv-port");

ML_TYPE(InstanceT, (), "lilv-instance");

ML_FUNCTION(GetAllPlugins) {
	const LilvPlugins *Plugins = lilv_world_get_all_plugins(World);
	ml_value_t *List = ml_list();
	for (LilvIter *Iter = lilv_plugins_begin(Plugins); !lilv_plugins_is_end(Plugins, Iter); Iter = lilv_plugins_next(Plugins, Iter)) {
		const LilvPlugin *Handle = lilv_plugins_get(Plugins, Iter);
		const char *Name = lilv_node_as_string(lilv_plugin_get_uri(Handle));
		plugin_t *Plugin = new(plugin_t);
		Plugin->Type = PluginT;
		Plugin->Handle = lilv_plugins_get(Plugins, Iter);
		ml_list_put(List, (ml_value_t *)Plugin);
		stringmap_insert(PluginsTable, Name, Plugin);
	}
	return List;
};

void ml_library_entry0(ml_value_t **Slot) {
	World = lilv_world_new();
	lilv_world_load_all(World);
#include "lilv_init.c"
	Slot[0] = ml_module("lilv",
		"plugins", GetAllPlugins,
	NULL);
}
