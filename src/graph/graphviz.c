#include <minilang/ml_library.h>
#include <minilang/ml_object.h>
#include <minilang/ml_stream.h>
#include <minilang/ml_macros.h>
#include <graphviz/cgraph.h>

typedef struct {
	ml_type_t *Type;
	void *Handle;
} object_t;

ML_TYPE(ObjectT, (), "graph::object");

ML_METHOD("get", ObjectT, MLStringT) {
	object_t *Object = (object_t *)Args[0];
	char *Value = agget(Object->Handle, (char *)ml_string_value(Args[1]));
	return Value ? ml_string(Value, -1) : MLNil;
}

ML_METHOD("set", ObjectT, MLStringT, MLStringT) {
	object_t *Object = (object_t *)Args[0];
	agsafeset(Object->Handle, (char *)ml_string_value(Args[1]), (char *)ml_string_value(Args[2]), ml_string_value(Args[2]));
	return Args[2];
}

typedef struct {
	ml_type_t *Type;
	Agraph_t *Handle;
} graph_t;

ML_TYPE(GraphT, (ObjectT), "graph");

ML_ENUM(GraphDescT, "graph::desc",
	"Directed", "StrictDirected",
	"Undirected", "StrictUndirected"
);

static void graph_finalize(graph_t *Graph, void *Data) {
	agclose(Graph->Handle);
}

/*static Agiddisc_t IdDisc[1] = {{
	void *(*open) (Agraph_t * g, Agdisc_t*);
    long (*map) (void *state, int objtype, char *str, IDTYPE *id,
		 int createflag);
    long (*alloc) (void *state, int objtype, IDTYPE id);
    void (*free) (void *state, int objtype, IDTYPE id);
    char *(*print) (void *state, int objtype, IDTYPE id);
    void (*close) (void *state);
    void (*idregister) (void *state, int objtype, void *obj);
}};
static Agiodisc_t IoDisc[1] = {{
	int (*afread) (void *chan, char *buf, int bufsize);
    int (*putstr) (void *chan, const char *str);
    int (*flush) (void *chan);
}};
static Agdisc_t Disc[1] = {IdDisc, IoDisc};*/

ML_METHOD(GraphT, MLStringT, GraphDescT) {
	Agdesc_t Desc = Agdirected;
	switch (ml_enum_value_value(Args[1])) {
	case 0: Desc = Agdirected; break;
	case 1: Desc = Agstrictdirected; break;
	case 2: Desc = Agundirected; break;
	case 3: Desc = Agstrictundirected; break;
	}
	graph_t *Graph = new(graph_t);
	Graph->Type = GraphT;
	Graph->Handle = agopen((char *)ml_string_value(Args[0]), Desc, NULL);
	GC_register_finalizer(Graph, (GC_finalization_proc)graph_finalize, NULL, NULL, NULL);
	return (ml_value_t *)Graph;
}

ML_METHOD(GraphT, MLStringT) {
	graph_t *Graph = new(graph_t);
	Graph->Type = GraphT;
	Graph->Handle = agmemread(ml_string_value(Args[0]));
	return (ml_value_t *)Graph;
}

ML_METHOD("append", MLStringBufferT, GraphT) {
	ml_stringbuffer_t *Buffer = (ml_stringbuffer_t *)Args[0];
	graph_t *Graph = (graph_t *)Args[1];
	char *Bytes;
	size_t Size;
	FILE *File = open_memstream(&Bytes, &Size);
	agwrite(Graph->Handle, File);
	fclose(File);
	ml_stringbuffer_write(Buffer, Bytes, Size);
	free(Bytes);
	return MLSome;
}

typedef struct {
	Agrec_t Base;
	ml_value_t *Value;
} record_t;

typedef struct {
	ml_type_t *Type;
	Agnode_t *Handle;
	graph_t *Graph;
} node_t;

ML_TYPE(NodeT, (ObjectT), "graph::node");

static ml_value_t *node(graph_t *Graph, Agnode_t *Handle) {
	record_t *Record = (record_t *)aggetrec(Handle, "minilang", 0);
	if (!Record) {
		node_t *Node = new(node_t);
		Node->Type = NodeT;
		Node->Graph = Graph;
		Node->Handle = Handle;
		Record = agbindrec(Handle, "minilang", sizeof(record_t), 0);
		Record->Value = (ml_value_t *)Node;
	}
	return Record->Value;
}

ML_METHOD("remove", NodeT) {
	node_t *Node = (node_t *)Args[0];
	agdelnode(Node->Graph->Handle, Node->Handle);
	return MLNil;
}

ML_METHOD("append", MLStringBufferT, NodeT) {
	ml_stringbuffer_t *Buffer = (ml_stringbuffer_t *)Args[0];
	node_t *Node = (node_t *)Args[1];
	const char *Name = agnameof(Node->Handle);
	ml_stringbuffer_write(Buffer, Name, strlen(Name));
	return MLSome;
}

ML_METHOD("[]", GraphT, MLStringT) {
	graph_t *Graph = (graph_t *)Args[0];
	return node(Graph, agnode(Graph->Handle, (char *)ml_string_value(Args[1]), TRUE));
}

ML_METHOD("nodes", GraphT) {
	graph_t *Graph = (graph_t *)Args[0];
	ml_value_t *Nodes = ml_list();
	for (Agnode_t *Handle = agfstnode(Graph->Handle); Handle; Handle = agnxtnode(Graph->Handle, Handle)) {
		ml_list_put(Nodes, node(Graph, Handle));
	}
	return Nodes;
}

typedef struct {
	ml_type_t *Type;
	Agedge_t *Handle;
	graph_t *Graph;
} edge_t;

ML_TYPE(EdgeT, (ObjectT), "graph::edge");

static ml_value_t *edge(graph_t *Graph, Agedge_t *Handle) {
	record_t *Record = (record_t *)aggetrec(Handle, "minilang", 0);
	if (!Record) {
		edge_t *Edge = new(edge_t);
		Edge->Type = EdgeT;
		Edge->Graph = Graph;
		Edge->Handle = Handle;
		Record = agbindrec(Handle, "minilang", sizeof(record_t), 0);
		Record->Value = (ml_value_t *)Edge;
	}
	return Record->Value;
}

ML_METHOD("remove", EdgeT) {
	edge_t *Edge = (edge_t *)Args[0];
	agdeledge(Edge->Graph->Handle, Edge->Handle);
	return MLNil;
}

ML_METHOD("append", MLStringBufferT, EdgeT) {
	ml_stringbuffer_t *Buffer = (ml_stringbuffer_t *)Args[0];
	edge_t *Edge = (edge_t *)Args[1];
	const char *Name = agnameof(Edge->Handle);
	if (Name) {
		ml_stringbuffer_write(Buffer, Name, strlen(Name));
	} else {
		ml_stringbuffer_printf(Buffer, "%s-->%s", agnameof(aghead(Edge->Handle)), agnameof(agtail(Edge->Handle)));
	}
	return MLSome;
}

ML_METHOD("---", NodeT, NodeT) {
	node_t *A = (node_t *)Args[0];
	node_t *B = (node_t *)Args[1];
	graph_t *Graph = A->Graph;
	if (Graph != B->Graph) return ml_error("GraphError", "Nodes are from different graphs");
	return edge(Graph, agedge(Graph->Handle, A->Handle, B->Handle, NULL, TRUE));
}

ML_METHOD("-->", NodeT, NodeT) {
	node_t *A = (node_t *)Args[0];
	node_t *B = (node_t *)Args[1];
	graph_t *Graph = A->Graph;
	if (Graph != B->Graph) return ml_error("GraphError", "Nodes are from different graphs");
	return edge(Graph, agedge(Graph->Handle, A->Handle, B->Handle, NULL, TRUE));
}

ML_METHOD("out", NodeT) {
	node_t *Node = (node_t *)Args[0];
	graph_t *Graph = Node->Graph;
	ml_value_t *Edges = ml_list();
	for (Agedge_t *Handle = agfstout(Graph->Handle, Node->Handle); Handle; Handle = agnxtout(Graph->Handle, Handle)) {
		ml_list_put(Edges, ml_tuplev(2, edge(Graph, Handle), node(Graph, agtail(Handle))));
	}
	return Edges;
}

ML_METHOD("in", NodeT) {
	node_t *Node = (node_t *)Args[0];
	graph_t *Graph = Node->Graph;
	ml_value_t *Edges = ml_list();
	for (Agedge_t *Handle = agfstin(Graph->Handle, Node->Handle); Handle; Handle = agnxtin(Graph->Handle, Handle)) {
		ml_list_put(Edges, ml_tuplev(2, edge(Graph, Handle), node(Graph, aghead(Handle))));
	}
	return Edges;
}

ML_METHOD("edges", NodeT) {
	node_t *Node = (node_t *)Args[0];
	graph_t *Graph = Node->Graph;
	ml_value_t *Edges = ml_list();
	for (Agedge_t *Handle = agfstedge(Graph->Handle, Node->Handle); Handle; Handle = agnxtedge(Graph->Handle, Handle, Node->Handle)) {
		ml_list_put(Edges, ml_tuplev(3, edge(Graph, Handle), node(Graph, aghead(Handle)), node(Graph, agtail(Handle))));
	}
	return Edges;
}

ML_LIBRARY_ENTRY0(graphviz) {
#include "graphviz_init.c"
	Slot[0] = (ml_value_t *)GraphT;
}
