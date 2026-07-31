#include "gtk_console_completion.h"
#include "gir.h"
#include <minilang/ml_logging.h>

struct _ConsoleCompletionProvider {
	GObject parent_instance;
	ml_compiler_t *Compiler;
};

static void gtk_console_completion_provider_interface_init(GtkSourceCompletionProviderInterface *Interface);

G_DEFINE_TYPE_WITH_CODE(ConsoleCompletionProvider, gtk_console_completion_provider, G_TYPE_OBJECT, G_IMPLEMENT_INTERFACE(GTK_SOURCE_TYPE_COMPLETION_PROVIDER, gtk_console_completion_provider_interface_init))

static void gtk_console_completion_provider_class_init(ConsoleCompletionProviderClass *klass) {
}

static void gtk_console_completion_provider_init(ConsoleCompletionProvider *Provider) {
}

static gchar *gtk_console_completion_provider_get_title(GtkSourceCompletionProvider *Self) {
	//ConsoleCompletionProvider *Provider = CONSOLE_COMPLETION_PROVIDER(Self);
	return g_strdup("console-completion");
}

struct _ConsoleCompletionProposal {
	GObject parent_instance;
	const char *Text;
};

G_DEFINE_TYPE_WITH_CODE(ConsoleCompletionProposal, gtk_console_completion_proposal, G_TYPE_OBJECT, G_IMPLEMENT_INTERFACE(GTK_SOURCE_TYPE_COMPLETION_PROPOSAL, NULL));

static void gtk_console_completion_proposal_class_init(ConsoleCompletionProposalClass *klass) {
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

static void gtk_console_completion_provider_populate_async(GtkSourceCompletionProvider *Self, GtkSourceCompletionContext *Context, GCancellable *Cancellable, GAsyncReadyCallback Callback, gpointer Data) {
	ML_LOG_INFO(NULL, __func__);
	ConsoleCompletionProvider *Provider = CONSOLE_COMPLETION_PROVIDER(Self);
	GTask *Task = g_task_new(Provider, Cancellable, Callback, Data);
	GtkTextIter Start, End;
	gtk_source_completion_context_get_bounds(Context, &Start, &End);
	populate_info_t Info[1];
	Info->Prefix = NULL;
	Info->Proposals = g_list_store_new(CONSOLE_TYPE_COMPLETION_PROPOSAL);
	populate_fn("Test1", NULL, Info);
	populate_fn("Test2", NULL, Info);
	populate_fn("Test3", NULL, Info);
	populate_fn("Test4", NULL, Info);
	populate_fn("Test5", NULL, Info);
	populate_fn("Test6", NULL, Info);
	/*if (gtk_text_iter_ends_word(&End)) {
		Info->Prefix = gtk_text_iter_get_text(&Start, &End);
		Info->PrefixLength = strlen(Info->Prefix);
	}
	//gtk_text_iter_backward_visible_word_start(&Start);
	gtk_text_iter_backward_chars(&End, 2);
	gchar *Name = gtk_text_iter_get_text(&Start, &End);
	ML_LOG_DEBUG(NULL, "Generating completion proposals: %s", Name);
	ml_value_t *Value = ml_compiler_lookup(Provider->Compiler, Name, "", 0, 0);
	if (!Value) {
		GtkTextIter Iter = End;
		do {
			if (!gtk_text_iter_backward_char(&Iter)) break;
			if (gtk_text_iter_get_char(&Iter) != ':') break;
			if (!gtk_text_iter_backward_char(&Iter)) break;
			if (gtk_text_iter_get_char(&Iter) != ':') break;
			gchar *Name0 = gtk_text_iter_get_text(&Start, &Iter);
			ML_LOG_DEBUG(NULL, "Generating completion proposals: %s", Name);
			ml_value_t *Value0 = ml_compiler_lookup(Provider->Compiler, Name0, "", 0, 0);
			g_free(Name0);
			if (!Value0) break;
			if (ml_is(Value0, MLGlobalT)) Value0 = ml_global_get(Value0);
			if (ml_is(Value0, MLGirTypelibT)) Value = ml_gir_import(Value0, Name);
			if (ml_is(Value0, MLTypeT)) Value = stringmap_search(((ml_type_t *)Value0)->Exports, Name);
		} while (0);
	}
	g_free(Name);
	if (Value && ml_is(Value, MLGlobalT)) Value = ml_global_get(Value);
	if (Value) {
		if (ml_is(Value, MLTypeT)) {
			ml_type_t *Type = (ml_type_t *)Value;
			stringmap_foreach(Type->Exports, Info, (void *)populate_fn);
		} else if (ml_is(Value, MLModuleT)) {
			ml_module_t *Module = (ml_module_t *)Value;
			stringmap_foreach(Module->Exports, Info, (void *)populate_fn);
		} else if (ml_is(Value, MLGirTypelibT)) {
			const char *Namespace = ml_gir_get_namespace(Value);
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
	}*/
	if (Info->Prefix) g_free(Info->Prefix);
	g_task_return_pointer(Task, Info->Proposals, g_object_unref);
	g_object_unref(Task);
}

static GListModel *gtk_console_completion_provider_populate_finish(GtkSourceCompletionProvider *Self, GAsyncResult *Result, GError **Error) {
	ML_LOG_INFO(NULL, __func__);
	//ConsoleCompletionProvider *Provider = CONSOLE_COMPLETION_PROVIDER(Self);
	return g_task_propagate_pointer(G_TASK(Result), Error);
}

static void gtk_console_completion_provider_refilter(GtkSourceCompletionProvider *Self, GtkSourceCompletionContext *Context, GListModel *Model) {
	ML_LOG_INFO(NULL, __func__);
	//ConsoleCompletionProvider *Provider = CONSOLE_COMPLETION_PROVIDER(Self);
	GtkTextIter Start, End;
	gtk_source_completion_context_get_bounds(Context, &Start, &End);
	/*if (gtk_text_iter_ends_word(&Iter)) {
		if (!gtk_text_iter_backward_word_start(&Iter)) return FALSE;
	}
	if (!gtk_text_iter_backward_char(&Iter)) return FALSE;
	if (gtk_text_iter_get_char(&Iter) != ':') return FALSE;
	if (!gtk_text_iter_backward_char(&Iter)) return FALSE;
	if (gtk_text_iter_get_char(&Iter) != ':') return FALSE;*/
}

static void gtk_console_completion_provider_display(GtkSourceCompletionProvider *Self, GtkSourceCompletionContext *Context, GtkSourceCompletionProposal *Prop, GtkSourceCompletionCell *Cell) {
	ML_LOG_INFO(NULL, __func__);
	//ConsoleCompletionProvider *Provider = CONSOLE_COMPLETION_PROVIDER(Self);
	ConsoleCompletionProposal *Proposal = CONSOLE_COMPLETION_PROPOSAL(Prop);
	switch (gtk_source_completion_cell_get_column(Cell)) {
	case GTK_SOURCE_COMPLETION_COLUMN_TYPED_TEXT:
		gtk_source_completion_cell_set_text(Cell, Proposal->Text);
		break;
	}
}

static void gtk_console_completion_provider_activate(GtkSourceCompletionProvider *Self, GtkSourceCompletionContext *Context, GtkSourceCompletionProposal *Prop) {
	ML_LOG_INFO(NULL, __func__);
	//ConsoleCompletionProvider *Provider = CONSOLE_COMPLETION_PROVIDER(Self);
	ConsoleCompletionProposal *Proposal = CONSOLE_COMPLETION_PROPOSAL(Prop);
	//gtk_source_completion_cell_set_text(Cell, Proposal->Text);
	ML_LOG_INFO(NULL, "Activating proposal: %s", Proposal->Text);
}

static void gtk_console_completion_provider_interface_init(GtkSourceCompletionProviderInterface *Interface) {
	Interface->get_title = gtk_console_completion_provider_get_title;
	Interface->populate_async = gtk_console_completion_provider_populate_async;
	Interface->populate_finish = gtk_console_completion_provider_populate_finish;
	Interface->refilter = gtk_console_completion_provider_refilter;
	Interface->display = gtk_console_completion_provider_display;
	Interface->activate = gtk_console_completion_provider_activate;
}

GtkSourceCompletionProvider *gtk_console_completion_provider(ml_compiler_t *Compiler) {
	ConsoleCompletionProvider *Provider = g_object_new(CONSOLE_TYPE_COMPLETION_PROVIDER, NULL);
	Provider->Compiler = Compiler;
	return GTK_SOURCE_COMPLETION_PROVIDER(Provider);
}
