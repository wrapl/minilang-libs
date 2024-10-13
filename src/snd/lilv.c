#include <minilang/ml_library.h>
#include <minilang/ml_macros.h>
#include <lilv/lilv.h>

static LilvWorld *World;

typedef struct {
	ml_type_t *Type;
	const LilvPlugin *Handle;
} plugin_t;

ML_TYPE(PluginT, (), "lilv::plugin");

static ml_value_t *ml_node_as_string(LilvNode *Node) {
	ml_value_t *Result = ml_string_unchecked(lilv_node_as_string(Node), -1);
	lilv_node_free(Node);
	return Result;
}

static ml_value_t *ml_node_as_float(LilvNode *Node) {
	ml_value_t *Result = ml_real(lilv_node_as_float(Node));
	lilv_node_free(Node);
	return Result;
}

static ml_value_t *ml_node_as_int(LilvNode *Node) {
	ml_value_t *Result = ml_integer(lilv_node_as_int(Node));
	lilv_node_free(Node);
	return Result;
}

static ml_value_t *ml_node_as_bool(LilvNode *Node) {
	ml_value_t *Result = ml_boolean(lilv_node_as_bool(Node));
	lilv_node_free(Node);
	return Result;
}

static ml_value_t *ml_nodes_as_strings(LilvNodes *Nodes) {
	ml_value_t *Result = ml_list();
	for (LilvIter *Iter = lilv_nodes_begin(Nodes); !lilv_nodes_is_end(Nodes, Iter); Iter = lilv_nodes_next(Nodes, Iter)) {
		const LilvNode *Node = lilv_nodes_get(Nodes, Iter);
		ml_list_put(Result, ml_string_unchecked(lilv_node_as_string(Node), -1));
	}
	lilv_nodes_free(Nodes);
	return Result;
}

ML_METHOD("name", PluginT) {
	const LilvPlugin *Handle = ((plugin_t *)Args[0])->Handle;
	return ml_node_as_string(lilv_plugin_get_name(Handle));
}

ML_METHOD("uri", PluginT) {
	const LilvPlugin *Handle = ((plugin_t *)Args[0])->Handle;
	return ml_string_unchecked(lilv_node_as_string(lilv_plugin_get_uri(Handle)), -1);
}

ML_METHOD("extension_data", PluginT) {
	const LilvPlugin *Handle = ((plugin_t *)Args[0])->Handle;
	return ml_nodes_as_strings(lilv_plugin_get_extension_data(Handle));
}

ML_METHOD("required_features", PluginT) {
	const LilvPlugin *Handle = ((plugin_t *)Args[0])->Handle;
	return ml_nodes_as_strings(lilv_plugin_get_required_features(Handle));
}

ML_METHOD("optional_features", PluginT) {
	const LilvPlugin *Handle = ((plugin_t *)Args[0])->Handle;
	return ml_nodes_as_strings(lilv_plugin_get_optional_features(Handle));
}

ML_METHOD("num_ports", PluginT) {
	const LilvPlugin *Handle = ((plugin_t *)Args[0])->Handle;
	return ml_integer(lilv_plugin_get_num_ports(Handle));
}

typedef struct {
	ml_type_t *Type;
	const LilvPort *Handle;
	const LilvPlugin *Plugin;
} port_t;

ML_TYPE(PortT, (), "lilv::port");

ML_METHOD("[]", PluginT, MLIntegerT) {
	const LilvPlugin *Handle = ((plugin_t *)Args[0])->Handle;
	const LilvPort *PortHandle = lilv_plugin_get_port_by_index(Handle, ml_integer_value(Args[1]));
	if (!PortHandle) return ml_error("ValueError", "Invalid port");
	port_t *Port = new(port_t);
	Port->Type = PortT;
	Port->Handle = PortHandle;
	Port->Plugin = Handle;
	return (ml_value_t *)Port;
}

ML_METHOD("[]", PluginT, MLStringT) {
	const LilvPlugin *Handle = ((plugin_t *)Args[0])->Handle;
	LilvNode *Uri = lilv_new_uri(World, ml_string_value(Args[1]));
	const LilvPort *PortHandle = lilv_plugin_get_port_by_symbol(Handle, Uri);
	lilv_node_free(Uri);
	if (!PortHandle) return ml_error("ValueError", "Invalid port");
	port_t *Port = new(port_t);
	Port->Type = PortT;
	Port->Handle = PortHandle;
	Port->Plugin = Handle;
	return (ml_value_t *)Port;
}

ML_METHOD("ports", PluginT) {
	const LilvPlugin *Handle = ((plugin_t *)Args[0])->Handle;
	int NumPorts = lilv_plugin_get_num_ports(Handle);
	ml_value_t *Result = ml_list();
	for (int I = 0; I < NumPorts; ++I) {
		port_t *Port = new(port_t);
		Port->Type = PortT;
		Port->Handle = lilv_plugin_get_port_by_index(Handle, I);
		Port->Plugin = Handle;
		ml_list_put(Result, (ml_value_t *)Port);
	}
	return Result;
}

ML_METHOD("name", PortT) {
	const LilvPlugin *Plugin = ((port_t *)Args[0])->Plugin;
	const LilvPort *Handle = ((port_t *)Args[0])->Handle;
	return ml_node_as_string(lilv_port_get_name(Plugin, Handle));
}

ML_METHOD("symbol", PortT) {
	const LilvPlugin *Plugin = ((port_t *)Args[0])->Plugin;
	const LilvPort *Handle = ((port_t *)Args[0])->Handle;
	return ml_string_unchecked(lilv_node_as_string(lilv_port_get_name(Plugin, Handle)), -1);
}

ML_METHOD("range", PortT) {
	const LilvPlugin *Plugin = ((port_t *)Args[0])->Plugin;
	const LilvPort *Handle = ((port_t *)Args[0])->Handle;
	LilvNode *Def, *Min, *Max;
	lilv_port_get_range(Plugin, Handle, &Def, &Min, &Max);
	ml_value_t *Result = ml_tuple(3);
	ml_tuple_set(Result, 1, ml_node_as_float(Def));
	ml_tuple_set(Result, 2, ml_node_as_float(Min));
	ml_tuple_set(Result, 3, ml_node_as_float(Max));
	return Result;
}

ML_METHOD("classes", PortT) {
	const LilvPlugin *Plugin = ((port_t *)Args[0])->Plugin;
	const LilvPort *Handle = ((port_t *)Args[0])->Handle;
	const LilvNodes *Nodes = lilv_port_get_classes(Plugin, Handle);
	ml_value_t *Result = ml_list();
	for (LilvIter *Iter = lilv_nodes_begin(Nodes); !lilv_nodes_is_end(Nodes, Iter); Iter = lilv_nodes_next(Nodes, Iter)) {
		const LilvNode *Node = lilv_nodes_get(Nodes, Iter);
		ml_list_put(Result, ml_string_unchecked(lilv_node_as_string(Node), -1));
	}
	return Result;
}

ML_METHOD("properties", PortT) {
	const LilvPlugin *Plugin = ((port_t *)Args[0])->Plugin;
	const LilvPort *Handle = ((port_t *)Args[0])->Handle;
	const LilvNodes *Nodes = lilv_port_get_properties(Plugin, Handle);
	ml_value_t *Result = ml_list();
	for (LilvIter *Iter = lilv_nodes_begin(Nodes); !lilv_nodes_is_end(Nodes, Iter); Iter = lilv_nodes_next(Nodes, Iter)) {
		const LilvNode *Node = lilv_nodes_get(Nodes, Iter);
		ml_list_put(Result, ml_string_unchecked(lilv_node_as_string(Node), -1));
	}
	return Result;
}

ML_METHOD("scale_points", PortT) {
	const LilvPlugin *Plugin = ((port_t *)Args[0])->Plugin;
	const LilvPort *Handle = ((port_t *)Args[0])->Handle;
	const LilvScalePoints *ScalePoints = lilv_port_get_scale_points(Plugin, Handle);
	if (!ScalePoints) return MLNil;
	ml_value_t *Result = ml_map();
	for (LilvIter *Iter = lilv_scale_points_begin(ScalePoints); !lilv_scale_points_is_end(ScalePoints, Iter); Iter = lilv_scale_points_next(ScalePoints, Iter)) {
		const LilvScalePoint *ScalePoint = lilv_scale_points_get(ScalePoints, Iter);
		ml_value_t *Label = ml_string_unchecked(lilv_node_as_string(lilv_scale_point_get_label(ScalePoint)), -1);
		const LilvNode *Value = lilv_scale_point_get_value(ScalePoint);
		if (lilv_node_is_string(Value)) {
			ml_map_insert(Result, Label, ml_string_unchecked(lilv_node_as_string(Value), -1));
		} else if (lilv_node_is_int(Value)) {
			ml_map_insert(Result, Label, ml_integer(lilv_node_as_int(Value)));
		} else if (lilv_node_is_float(Value)) {
			ml_map_insert(Result, Label, ml_real(lilv_node_as_float(Value)));
		} else if (lilv_node_is_bool(Value)) {
			ml_map_insert(Result, Label, ml_boolean(lilv_node_as_bool(Value)));
		}
	}
	return Result;
}

typedef struct {
	ml_type_t *Type;
	const LilvPluginClass *Handle;
} plugin_class_t;

ML_TYPE(PluginClassT, (), "lilv::plugin::class");

ML_METHOD("class", PluginT) {
	const LilvPlugin *Plugin = ((plugin_t *)Args[0])->Handle;
	plugin_class_t *Class = new(plugin_class_t);
	Class->Type = PluginClassT;
	Class->Handle = lilv_plugin_get_class(Plugin);
	return (ml_value_t *)Class;
}

ML_METHOD("label", PluginClassT) {
	const LilvPluginClass *Handle = ((plugin_class_t *)Args[0])->Handle;
	return ml_string_unchecked(lilv_node_as_string(lilv_plugin_class_get_label(Handle)), -1);
}

typedef struct {
	ml_type_t *Type;
	LilvInstance *Handle;
} instance_t;

ML_TYPE(InstanceT, (), "lilv::instance");

ML_METHOD("instantiate", PluginT, MLRealT) {
	const LilvPlugin *Plugin = ((plugin_t *)Args[0])->Handle;
	double SampleRate = ml_real_value(Args[1]);
	LilvInstance *Handle = lilv_plugin_instantiate(Plugin, SampleRate, NULL);
	if (!Handle) return ml_error("LilvError", "Failed to instantiate plugin");
	instance_t *Instance = new(instance_t);
	Instance->Type = InstanceT;
	Instance->Handle = Handle;
	return (ml_value_t *)Instance;
}

ML_METHOD("connect", InstanceT, MLIntegerT, MLBufferT) {
	LilvInstance *Handle = ((instance_t *)Args[0])->Handle;
	uint32_t Port = ml_integer_value(Args[1]);
	void *Location = ml_buffer_value(Args[2]);
	lilv_instance_connect_port(Handle, Port, Location);
	return Args[0];
}

ML_METHOD("activate", InstanceT) {
	LilvInstance *Handle = ((instance_t *)Args[0])->Handle;
	lilv_instance_activate(Handle);
	return Args[0];
}

ML_METHOD("run", InstanceT, MLIntegerT) {
	LilvInstance *Handle = ((instance_t *)Args[0])->Handle;
	uint32_t SampleCount = ml_integer_value(Args[1]);
	lilv_instance_run(Handle, SampleCount);
	return Args[0];
}

ML_FUNCTION(GetAllPlugins) {
	const LilvPlugins *Plugins = lilv_world_get_all_plugins(World);
	ml_value_t *Result = ml_map();
	for (LilvIter *Iter = lilv_plugins_begin(Plugins); !lilv_plugins_is_end(Plugins, Iter); Iter = lilv_plugins_next(Plugins, Iter)) {
		plugin_t *Plugin = new(plugin_t);
		Plugin->Type = PluginT;
		Plugin->Handle = lilv_plugins_get(Plugins, Iter);
		const char *Uri = lilv_node_as_string(lilv_plugin_get_uri(Plugin->Handle));
		ml_map_insert(Result, ml_string_copy(Uri, -1), (ml_value_t *)Plugin);
	}
	return Result;
};

ML_LIBRARY_ENTRY0(snd_lilv) {
	World = lilv_world_new();
	lilv_world_load_all(World);
#include "lilv_init.c"
	stringmap_insert(PluginT->Exports, "all", GetAllPlugins);
	Slot[0] = ml_module("lilv",
		"plugin", PluginT,
	NULL);
}
