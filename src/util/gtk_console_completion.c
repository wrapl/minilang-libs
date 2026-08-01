#include "gtk_console_completion.h"
#include "gir.h"
#include <minilang/ml_logging.h>

struct _ConsoleCompletionProvider {
	GObject parent_instance;
	ml_compiler_t *Compiler;
	stringmap_t *Globals;
	ml_value_t *Scope;
};

static void gtk_console_completion_provider_interface_init(GtkSourceCompletionProviderInterface *Interface);

G_DEFINE_TYPE_WITH_CODE(ConsoleCompletionProvider, gtk_console_completion_provider, G_TYPE_OBJECT, G_IMPLEMENT_INTERFACE(GTK_SOURCE_TYPE_COMPLETION_PROVIDER, gtk_console_completion_provider_interface_init))

static void gtk_console_completion_provider_class_init(ConsoleCompletionProviderClass *klass) {
}

static void gtk_console_completion_provider_init(ConsoleCompletionProvider *Provider) {
}

static gchar *gtk_console_completion_provider_get_title(GtkSourceCompletionProvider *Self) {
	//ConsoleCompletionProvider *Provider = CONSOLE_COMPLETION_PROVIDER(Self);
	return g_strdup("Minilang");
}

static gint gtk_console_completion_provider_get_priority(GtkSourceCompletionProvider *Self, GtkSourceCompletionContext  *Context) {
	return 1000;
}

struct _ConsoleCompletionProposal {
	GObject parent_instance;
	const char *Text;
};

static void gtk_console_completion_proposal_interface_init(GtkSourceCompletionProposalInterface *Interface);

G_DEFINE_TYPE_WITH_CODE(ConsoleCompletionProposal, gtk_console_completion_proposal, G_TYPE_OBJECT, G_IMPLEMENT_INTERFACE(GTK_SOURCE_TYPE_COMPLETION_PROPOSAL, gtk_console_completion_proposal_interface_init));

static void gtk_console_completion_proposal_class_init(ConsoleCompletionProposalClass *klass) {
}

static char *gtk_console_completion_proposal_get_typed_text(GtkSourceCompletionProposal *Self) {
	ConsoleCompletionProposal *Proposal = CONSOLE_COMPLETION_PROPOSAL(Self);
	return (char *)Proposal->Text;
}

static void gtk_console_completion_proposal_interface_init(GtkSourceCompletionProposalInterface *Interface) {
	Interface->get_typed_text = gtk_console_completion_proposal_get_typed_text;
}

static void gtk_console_completion_proposal_init(ConsoleCompletionProposal *Proposal) {
}

typedef struct {
	gchar *Prefix;
	GListStore *Proposals;
	int PrefixLength;
} populate_info_t;

static int populate_fn(const char *Name, void *Value, populate_info_t *Info) {
	if (Info->Prefix) {
		if (strncmp(Name, Info->Prefix, Info->PrefixLength)) return 0;
	}
	ConsoleCompletionProposal *Proposal = (ConsoleCompletionProposal *)g_object_new(CONSOLE_TYPE_COMPLETION_PROPOSAL, NULL);
	Proposal->Text = Name;
	g_list_store_append(Info->Proposals, G_OBJECT(Proposal));
	g_object_unref(Proposal);
	return 0;
}

static void gtk_console_completion_provider_populate(ConsoleCompletionProvider *Provider, populate_info_t *Info) {
	ml_value_t *Scope = Provider->Scope;
	if (!Scope) {
		stringmap_foreach(Provider->Globals, Info, (void *)populate_fn);
		stringmap_foreach(MLGlobals, Info, (void *)populate_fn);
	} else if (ml_is(Scope, MLTypeT)) {
		ml_type_t *Type = (ml_type_t *)Scope;
		stringmap_foreach(Type->Exports, Info, (void *)populate_fn);
	} else if (ml_is(Scope, MLModuleT)) {
		ml_module_t *Module = (ml_module_t *)Scope;
		stringmap_foreach(Module->Exports, Info, (void *)populate_fn);
	} else if (ml_is(Scope, MLGirTypelibT)) {
		const char *Namespace = ml_gir_get_namespace(Scope);
		int Total = g_irepository_get_n_infos(NULL, Namespace);
		for (int I = 0; I < Total; ++I) {
			GIBaseInfo *Base = g_irepository_get_info(NULL, Namespace, I);
			const char *Name = g_base_info_get_name(Base);
			if (Info->Prefix) {
				if (strncmp(Name, Info->Prefix, Info->PrefixLength)) continue;
			}
			ConsoleCompletionProposal *Proposal = (ConsoleCompletionProposal *)g_object_new(CONSOLE_TYPE_COMPLETION_PROPOSAL, NULL);
			Proposal->Text = Name;
			g_list_store_append(Info->Proposals, G_OBJECT(Proposal));
		}
	}
}

static ml_value_t *gtk_console_completion_find_scope(GtkTextIter *Start, ml_compiler_t *Compiler) {
	if (!gtk_text_iter_backward_char(Start)) return NULL;
	if (gtk_text_iter_get_char(Start) != ':') return NULL;
	if (!gtk_text_iter_backward_char(Start)) return NULL;
	if (gtk_text_iter_get_char(Start) != ':') return NULL;
	GtkTextIter Iter = *Start;
	if (!gtk_text_iter_backward_word_start(Start)) return NULL;
	gchar *Name = gtk_text_iter_get_text(Start, &Iter);
	ml_value_t *Scope = gtk_console_completion_find_scope(Start, Compiler);
	ml_value_t *Value = NULL;
	if (!Scope) {
		Value = ml_compiler_lookup(Compiler, Name, "", 0, 0);
		if (Value && ml_is(Value, MLGlobalT)) Value = ml_global_get(Value);
	} else if (ml_is(Scope, MLGirTypelibT)) {
		Value = ml_gir_import(Scope, Name);
	} else if (ml_is(Scope, MLTypeT)) {
		Value = stringmap_search(((ml_type_t *)Scope)->Exports, Name);
	} else if (ml_is(Scope, MLModuleT)) {
		Value = ml_module_import(Scope, Name);
	}
	g_free(Name);
	return Value;
}

static void gtk_console_completion_provider_populate_async(GtkSourceCompletionProvider *Self, GtkSourceCompletionContext *Context, GCancellable *Cancellable, GAsyncReadyCallback Callback, gpointer Data) {
	ConsoleCompletionProvider *Provider = CONSOLE_COMPLETION_PROVIDER(Self);
	GTask *Task = g_task_new(Provider, Cancellable, Callback, Data);
	GtkTextIter Start, End;
	gtk_source_completion_context_get_bounds(Context, &Start, &End);
	gchar *Temp = gtk_text_iter_get_text(&Start, &End);
	g_free(Temp);
	populate_info_t Info[1];
	Info->Prefix = NULL;
	Info->Proposals = g_list_store_new(CONSOLE_TYPE_COMPLETION_PROPOSAL);
	if (gtk_text_iter_ends_word(&End)) {
		Info->Prefix = gtk_text_iter_get_text(&Start, &End);
		Info->PrefixLength = strlen(Info->Prefix);
	}
	Provider->Scope = gtk_console_completion_find_scope(&Start, Provider->Compiler);
	gtk_console_completion_provider_populate(Provider, Info);
	if (Info->Prefix) g_free(Info->Prefix);
	g_task_return_pointer(Task, Info->Proposals, g_object_unref);
	g_object_unref(Task);
}

static GListModel *gtk_console_completion_provider_populate_finish(GtkSourceCompletionProvider *Self, GAsyncResult *Result, GError **Error) {
	//ConsoleCompletionProvider *Provider = CONSOLE_COMPLETION_PROVIDER(Self);
	GListModel *Proposals = g_task_propagate_pointer(G_TASK(Result), Error);
	return Proposals;
}

static void gtk_console_completion_provider_refilter(GtkSourceCompletionProvider *Self, GtkSourceCompletionContext *Context, GListModel *Proposals) {
	ConsoleCompletionProvider *Provider = CONSOLE_COMPLETION_PROVIDER(Self);
	GtkTextIter Start, End;
	gtk_source_completion_context_get_bounds(Context, &Start, &End);
	populate_info_t Info[1];
	Info->Prefix = gtk_text_iter_get_text(&Start, &End);
	Info->PrefixLength = strlen(Info->Prefix);
	Info->Proposals = G_LIST_STORE(Proposals);
	g_list_store_remove_all(Info->Proposals);
	gtk_console_completion_provider_populate(Provider, Info);
}

static void gtk_console_completion_provider_display(GtkSourceCompletionProvider *Self, GtkSourceCompletionContext *Context, GtkSourceCompletionProposal *Prop, GtkSourceCompletionCell *Cell) {
	//ConsoleCompletionProvider *Provider = CONSOLE_COMPLETION_PROVIDER(Self);
	ConsoleCompletionProposal *Proposal = CONSOLE_COMPLETION_PROPOSAL(Prop);
	switch (gtk_source_completion_cell_get_column(Cell)) {
	case GTK_SOURCE_COMPLETION_COLUMN_ICON:
		gtk_source_completion_cell_set_icon_name(Cell, "info-symbolic");
		break;
	case GTK_SOURCE_COMPLETION_COLUMN_TYPED_TEXT:
		gtk_source_completion_cell_set_text(Cell, Proposal->Text);
		break;
	default:
		gtk_source_completion_cell_set_text (Cell, NULL);
		break;
	}
}

static void gtk_console_completion_provider_activate(GtkSourceCompletionProvider *Self, GtkSourceCompletionContext *Context, GtkSourceCompletionProposal *Prop) {
	//ConsoleCompletionProvider *Provider = CONSOLE_COMPLETION_PROVIDER(Self);
	ConsoleCompletionProposal *Proposal = CONSOLE_COMPLETION_PROPOSAL(Prop);
	GtkTextIter Start, End;
	gtk_source_completion_context_get_bounds(Context, &Start, &End);
	GtkTextBuffer *Buffer = GTK_TEXT_BUFFER(gtk_source_completion_context_get_buffer(Context));
	gtk_text_buffer_delete(Buffer, &Start, &End);
	gtk_text_buffer_insert(Buffer, &Start, Proposal->Text, -1);
}

static gboolean gtk_console_completion_provider_is_trigger(GtkSourceCompletionProvider *Self, const GtkTextIter *Iter, gunichar Char) {
	return Char == ':';
}

static void gtk_console_completion_provider_interface_init(GtkSourceCompletionProviderInterface *Interface) {
	Interface->get_priority = gtk_console_completion_provider_get_priority;
	Interface->get_title = gtk_console_completion_provider_get_title;
	Interface->populate_async = gtk_console_completion_provider_populate_async;
	Interface->populate_finish = gtk_console_completion_provider_populate_finish;
	Interface->refilter = gtk_console_completion_provider_refilter;
	Interface->display = gtk_console_completion_provider_display;
	Interface->activate = gtk_console_completion_provider_activate;
	Interface->is_trigger = gtk_console_completion_provider_is_trigger;
}

GtkSourceCompletionProvider *gtk_console_completion_provider(ml_compiler_t *Compiler, stringmap_t *Globals) {
	ConsoleCompletionProvider *Provider = g_object_new(CONSOLE_TYPE_COMPLETION_PROVIDER, NULL);
	Provider->Compiler = Compiler;
	Provider->Globals = Globals;
	return GTK_SOURCE_COMPLETION_PROVIDER(Provider);
}
