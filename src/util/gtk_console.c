#include "gtk_console.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <gtksourceview/gtksource.h>
#include <gdk-pixbuf/gdk-pixbuf.h>
#include <girepository.h>
#include <minilang/ml_library.h>
#include <minilang/ml_macros.h>
#include <minilang/ml_logging.h>
#include <sys/stat.h>

#include "gir.h"
#include <minilang/ml_debugger.h>
#include <minilang/ml_object.h>
#include "gtk_console_completion.h"

#undef ML_CATEGORY
#define ML_CATEGORY "gtk_console"

#define MAX_HISTORY 128

typedef struct {
	gtk_console_t *Console;
	GtkSourceStyleSchemeManager *StyleManager;
	GtkSourceStyleScheme *StyleScheme;
	GtkSourceBuffer *PreviewBuffer;
	GtkCssProvider *CssProvider;
	GtkWidget *FontButton;
	GtkWidget *Dialog, *StyleDropDown;
	const char *FontCss;
} gtk_console_settings_t;

struct gtk_console_t {
	ml_state_t Base;
	const char *Name;
	GtkWidget *Window, *LogScrolled, *LogView, *InputView;
	GtkWidget *DebugButtons, *SourceView, *FrameView, *ThreadView, *Paned;
	GtkListStore *ThreadStore;
	GtkTreeStore *FrameStore;
	GtkNotebook *Notebook;
	GtkSourceLanguage *Language;
	GtkSourceStyleScheme *StyleScheme;
	GtkLabel *MemoryBar;
	GtkTextTag *OutputTag, *ResultTag, *ErrorTag, *BinaryTag;
	GtkTextMark *EndMark;
	GtkSourceBuffer *SourceBuffer;
	GtkCssProvider *CssProvider;
	ml_getter_t ParentGetter;
	void *ParentGlobals;
	ml_interactive_debugger_t *Debugger;
	const char *ConfigPath;
	GKeyFile *Config;
	PangoFontDescription *FontDescription;
	ml_parser_t *Parser;
	ml_compiler_t *Compiler;
	gtk_console_settings_t *Settings;
	char *History[MAX_HISTORY];
	int HistoryIndex, HistoryEnd;
	stringmap_t Globals[1];
	stringmap_t OpenFiles[1];
	stringmap_t Cycles[1];
	stringmap_t Combos[1];
	gint WindowSize[2];
	char Chars[32];
	int NumChars;
	int DisplayOutput;
	guint StatusTimeout;
};

#ifdef MINGW
static char *stpcpy(char *Dest, const char *Source) {
	while (*Source) *Dest++ = *Source++;
	return Dest;
}

#define lstat stat
#endif

static ml_value_t *console_global_get(gtk_console_t *Console, const char *Name, const char *Source, int Line, int Eval) {
	if (Console->Debugger) {
		ml_value_t *Value = ml_interactive_debugger_get(Console->Debugger, Name);
		if (Value) return Value;
	}
	ml_value_t *Value = stringmap_search(Console->Globals, Name);
	if (Value) return Value;
	return (Console->ParentGetter)(Console->ParentGlobals, Name, Source, Line, Eval);
}

void gtk_console_log(gtk_console_t *Console, ml_value_t *Value) {
	GtkTextIter End[1];
	GtkTextBuffer *LogBuffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(Console->LogView));
	gtk_text_buffer_get_end_iter(LogBuffer, End);
	if (ml_is_error(Value)) {
		char *Buffer;
		int Length = GC_asprintf(&Buffer, "%s: %s\n", ml_error_type(Value), ml_error_message(Value));
		gtk_text_buffer_insert_with_tags(LogBuffer, End, Buffer, Length, Console->ErrorTag, NULL);
		ml_source_t Source;
		int Level = 0;
		while (ml_error_source(Value, Level++, &Source)) {
			Length = GC_asprintf(&Buffer, "\t%s:%d\n", Source.Name, Source.Line);
			gtk_text_buffer_insert_with_tags(LogBuffer, End, Buffer, Length, Console->ErrorTag, NULL);
		}
	} else {
		ml_value_t *String = ml_simple_inline(MLStringT, 1, Value);
		if (ml_is(String, MLStringT)) {
			const char *Buffer = ml_string_value(String);
			int Length = ml_string_length(String);
			if (Length > 10240) {
				char Text[32];
				int TextLength = sprintf(Text, "<%d bytes>", Length);
				gtk_text_buffer_insert_with_tags(LogBuffer, End, Text, TextLength, Console->ResultTag, NULL);
			} else if (g_utf8_validate(Buffer, Length, NULL)) {
				gtk_text_buffer_insert_with_tags(LogBuffer, End, Buffer, Length, Console->ResultTag, NULL);
			} else {
				gtk_text_buffer_insert_with_tags(LogBuffer, End, "<", 1, Console->BinaryTag, NULL);
				for (int I = 0; I < Length; ++I) {
					static char HexChars[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
					char Bytes[4] = " ??";
					unsigned char Byte = Buffer[I];
					Bytes[1] = HexChars[Byte >> 4];
					Bytes[2] = HexChars[Byte & 15];
					gtk_text_buffer_insert_with_tags(LogBuffer, End, Bytes, 3, Console->BinaryTag, NULL);
				}
				gtk_text_buffer_insert_with_tags(LogBuffer, End, " >", 2, Console->BinaryTag, NULL);
			}
			gtk_text_buffer_insert_with_tags(LogBuffer, End, "\n", 1, Console->ResultTag, NULL);
		} else {
			char *Buffer;
			int Length = GC_asprintf(&Buffer, "<%s>\n", ml_typeof(Value)->Name);
			gtk_text_buffer_insert_with_tags(LogBuffer, End, Buffer, Length, Console->ResultTag, NULL);
		}
	}
	gtk_text_view_scroll_mark_onscreen(GTK_TEXT_VIEW(Console->LogView), Console->EndMark);
}

ML_TYPE(ConsoleT, (), "console");
//!internal

static __attribute__ ((noinline)) void console_new_line(gtk_console_t *Console) {
	GtkTextIter End[1];
	GtkTextBuffer *LogBuffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(Console->LogView));
	gtk_text_buffer_get_end_iter(LogBuffer, End);
	gtk_text_buffer_insert(LogBuffer, End, "\n", 1);
}

static void ml_console_repl_run(gtk_console_t *Console, ml_value_t *Result) {
	if (Result == MLEndOfInput) {
		gtk_widget_grab_focus(Console->InputView);
		return;
	}
	if (Console->DisplayOutput || ml_is_error(Result)) gtk_console_log(Console, Result);
	console_new_line(Console);
	if (ml_is_error(Result)) {
		gtk_widget_grab_focus(Console->InputView);
		return;
	}
	return ml_command_evaluate((ml_state_t *)Console, Console->Parser, Console->Compiler);
}

static void console_step_in(GtkWidget *Button, gtk_console_t *Console) {
	ml_parser_t *Parser = Console->Parser;
	ml_compiler_t *Compiler = Console->Compiler;
	ml_parser_reset(Parser);
	ml_parser_input(Parser, "step_in()", 0);
	ml_command_evaluate((ml_state_t *)Console, Parser, Compiler);
}

static void console_step_over(GtkWidget *Button, gtk_console_t *Console) {
	ml_parser_t *Parser = Console->Parser;
	ml_compiler_t *Compiler = Console->Compiler;
	ml_parser_reset(Parser);
	ml_parser_input(Parser, "step_over()", 0);
	ml_command_evaluate((ml_state_t *)Console, Parser, Compiler);
}

static void console_step_out(GtkWidget *Button, gtk_console_t *Console) {
	ml_parser_t *Parser = Console->Parser;
	ml_compiler_t *Compiler = Console->Compiler;
	ml_parser_reset(Parser);
	ml_parser_input(Parser, "step_out()", 0);
	ml_command_evaluate((ml_state_t *)Console, Parser, Compiler);
}

static void console_continue(GtkWidget *Button, gtk_console_t *Console) {
	ml_parser_t *Parser = Console->Parser;
	ml_compiler_t *Compiler = Console->Compiler;
	ml_parser_reset(Parser);
	ml_parser_input(Parser, "continue()", 0);
	ml_command_evaluate((ml_state_t *)Console, Parser, Compiler);
}

static void console_continue_all(GtkWidget *Button, gtk_console_t *Console) {
	ml_parser_t *Parser = Console->Parser;
	ml_compiler_t *Compiler = Console->Compiler;
	ml_parser_reset(Parser);
	ml_parser_input(Parser, "continue_all()", 0);
	ml_command_evaluate((ml_state_t *)Console, Parser, Compiler);
}

void gtk_console_evaluate(gtk_console_t *Console, const char *Text) {
	ml_parser_t *Parser = Console->Parser;
	ml_compiler_t *Compiler = Console->Compiler;
	ml_parser_reset(Parser);
	ml_parser_input(Parser, Text, 1);
	ml_command_evaluate((ml_state_t *)Console, Parser, Compiler);
}

static void console_submit(GtkWidget *Button, gtk_console_t *Console) {
	GtkTextBuffer *InputBuffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(Console->InputView));
	GtkTextIter InputStart[1], InputEnd[1];
	gtk_source_buffer_set_highlight_matching_brackets(GTK_SOURCE_BUFFER(InputBuffer), FALSE);
	gtk_text_buffer_get_bounds(InputBuffer, InputStart, InputEnd);
	const char *Text = gtk_text_buffer_get_text(InputBuffer, InputStart, InputEnd, FALSE);

	int HistoryEnd = Console->HistoryEnd;
	Console->History[HistoryEnd] = GC_strdup(Text);
	Console->HistoryIndex = Console->HistoryEnd = (HistoryEnd + 1) % MAX_HISTORY;

	GtkTextIter End[1];

	GtkTextBuffer *LogBuffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(Console->LogView));
	gtk_text_buffer_get_end_iter(LogBuffer, End);
	gtk_source_buffer_create_source_mark(GTK_SOURCE_BUFFER(LogBuffer), NULL, "result", End);
	gtk_text_buffer_insert_range(LogBuffer, End, InputStart, InputEnd);
	gtk_text_buffer_insert(LogBuffer, End, "\n", -1);
	gtk_text_buffer_set_text(InputBuffer, "", 0);

	GtkTextBuffer *SourceBuffer = GTK_TEXT_BUFFER(Console->SourceBuffer);
	gtk_text_buffer_get_end_iter(SourceBuffer, End);
	gtk_text_buffer_insert(SourceBuffer, End, Text, -1);
	gtk_text_buffer_insert(SourceBuffer, End, "\n", -1);
	gtk_source_buffer_set_highlight_matching_brackets(GTK_SOURCE_BUFFER(InputBuffer), TRUE);

	//GtkTextIter End[1];
	//GtkTextBuffer *LogBuffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(Console->LogView));
	gtk_text_buffer_get_end_iter(LogBuffer, End);
	gtk_text_buffer_insert(LogBuffer, End, "\n", 1);
	gtk_console_evaluate(Console, Text);
}

typedef struct {
	gtk_console_t *Console;
	ml_value_t *Name;
	GtkWidget *View;
} console_open_file_t;

static void console_breakpoint_toggle(GtkSourceView *View, GtkTextIter *Iter, GdkEvent *Event, console_open_file_t *OpenFile) {
	GtkTextBuffer *Buffer = gtk_text_iter_get_buffer(Iter);
	GSList *Marks = gtk_source_buffer_get_source_marks_at_iter(GTK_SOURCE_BUFFER(Buffer), Iter, "breakpoint");
	ml_interactive_debugger_t *Debugger = OpenFile->Console->Debugger;
	ml_value_t *BreakpointFn = NULL;
	if (Marks) {
		GtkTextMark *Mark = GTK_TEXT_MARK(Marks->data);
		gtk_text_buffer_delete_mark(Buffer, Mark);
		if (Debugger) BreakpointFn = ml_interactive_debugger_get(Debugger, "breakpoint_clear");
		g_slist_free(Marks);
	} else {
		gtk_source_buffer_create_source_mark(GTK_SOURCE_BUFFER(Buffer), NULL, "breakpoint", Iter);
		if (Debugger) BreakpointFn = ml_interactive_debugger_get(Debugger, "breakpoint_set");
	}
	if (BreakpointFn) {
		ml_value_t **Args = ml_alloc_args(2);
		Args[0] = OpenFile->Name;
		Args[1] = ml_integer(gtk_text_iter_get_line(Iter) + 1);
		ml_simple_call(BreakpointFn, 2, Args);
	}
}

static GtkWidget *console_open_source(gtk_console_t *Console, const char *SourceName) {
	console_open_file_t **Slot = (console_open_file_t **)stringmap_slot(Console->OpenFiles, SourceName);
	if (!Slot[0]) {
		console_open_file_t *OpenFile = Slot[0] = new(console_open_file_t);
		OpenFile->Console = Console;
		OpenFile->Name = ml_string(SourceName, -1);
		GtkSourceBuffer *Buffer = gtk_source_buffer_new_with_language(Console->Language);
		gtk_source_buffer_set_style_scheme(Buffer, Console->StyleScheme);
		GtkTextIter End[1];
		gtk_text_buffer_get_end_iter(GTK_TEXT_BUFFER(Buffer), End);
		FILE *File = fopen(SourceName, "r");
		if (File) {
			char Text[128];
			size_t Length;
			do {
			 Length = fread(Text, 1, 128, File);
			 gtk_text_buffer_insert(GTK_TEXT_BUFFER(Buffer), End, Text, Length);
			} while (Length == 128);
			fclose(File);
		}
		GtkWidget *View = gtk_source_view_new_with_buffer(Buffer);
		OpenFile->View = View;
		GtkWidget *Scrolled = gtk_scrolled_window_new();
		gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(Scrolled), View);
		gtk_text_view_set_monospace(GTK_TEXT_VIEW(View), TRUE);
		gtk_text_view_set_editable(GTK_TEXT_VIEW(View), FALSE);
		gtk_source_view_set_tab_width(GTK_SOURCE_VIEW(View), 4);
		gtk_source_view_set_highlight_current_line(GTK_SOURCE_VIEW(View), TRUE);
		gtk_source_view_set_show_line_numbers(GTK_SOURCE_VIEW(View), TRUE);
		gtk_source_view_set_show_line_marks(GTK_SOURCE_VIEW(View), TRUE);

		static GtkSourceMarkAttributes *BreakpointMarkAttributes = NULL;
		if (!BreakpointMarkAttributes) {
			BreakpointMarkAttributes = gtk_source_mark_attributes_new();
			gtk_source_mark_attributes_set_icon_name(BreakpointMarkAttributes, "media-record");
		}
		gtk_source_view_set_mark_attributes(GTK_SOURCE_VIEW(View), "breakpoint", BreakpointMarkAttributes, 0);

		g_signal_connect(G_OBJECT(View), "line-mark-activated", G_CALLBACK(console_breakpoint_toggle), OpenFile);

		gtk_notebook_append_page(Console->Notebook, Scrolled, gtk_label_new(SourceName));
		gtk_widget_show(GTK_WIDGET(Console->Notebook));
	}
	return Slot[0]->View;
}

static int console_debug_set_breakpoints(const char *SourceName, console_open_file_t *OpenFile, ml_value_t *BreakpointSet) {
	ml_value_t **Args = ml_alloc_args(2);
	Args[0] = OpenFile->Name;
	GtkTextBuffer *Buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(OpenFile->View));
	GtkTextIter Iter[1];
	gtk_text_buffer_get_start_iter(Buffer, Iter);
	while (gtk_source_buffer_forward_iter_to_source_mark(GTK_SOURCE_BUFFER(Buffer), Iter, "breakpoint")) {
		Args[1] = ml_integer(gtk_text_iter_get_line(Iter) + 1);
		ml_simple_call(BreakpointSet, 2, Args);
	}
	return 0;
}

static void console_show_value(GtkTreeStore *Store, GtkTreeIter *Iter, const char *Name, ml_value_t *Value) {
	typeof(console_show_value) *function = ml_typed_fn_get(ml_typeof(Value), console_show_value);
	if (function) return function(Store, Iter, Name, Value);
	ml_stringbuffer_t Buffer[1] = {ML_STRINGBUFFER_INIT};
	ml_stringbuffer_append(Buffer, Value);
	char *Display;
	if (ml_stringbuffer_length(Buffer) < 64) {
		Display = ml_stringbuffer_get_string(Buffer);
	} else {
		Display = snew(68);
		memcpy(Display, Buffer->Head->Chars, 64);
		strcpy(Display + 64, "...");
	}
	gtk_tree_store_insert_with_values(Store, NULL, Iter, -1, 0, Name, 1, Display, -1);
}

static void ML_TYPED_FN(console_show_value, MLListT, GtkTreeStore *Store, GtkTreeIter *Iter, const char *Name, ml_value_t *Value) {
	GtkTreeIter Child[1];
	char *Display;
	GC_asprintf(&Display, "list[%d]", ml_list_length(Value));
	gtk_tree_store_insert_with_values(Store, Child, Iter, -1, 0, Name, 1, Display, -1);
	int Index = 0;
	ML_LIST_FOREACH(Value, Iter) {
		if (++Index > 20) break;
		GC_asprintf(&Display, "[%d]", Index);
		console_show_value(Store, Child, Display, Iter->Value);
	}
}

static void ML_TYPED_FN(console_show_value, MLMapT, GtkTreeStore *Store, GtkTreeIter *Iter, const char *Name, ml_value_t *Value) {
	GtkTreeIter Child[1];
	char *Display;
	GC_asprintf(&Display, "map[%d]", ml_map_size(Value));
	gtk_tree_store_insert_with_values(Store, Child, Iter, -1, 0, Name, 1, Display, -1);
	int Index = 0;
	ML_MAP_FOREACH(Value, Iter) {
		if (++Index > 20) break;
		GC_asprintf(&Display, "[%d]", Index);
		GtkTreeIter Child2[1];
		gtk_tree_store_insert_with_values(Store, Child2, Child, -1, 0, Display, -1);
		console_show_value(Store, Child2, "key", Iter->Key);
		console_show_value(Store, Child2, "value", Iter->Value);
	}
}

typedef struct {
	GtkTreeStore *Store;
	GtkTreeIter *Child;
} console_show_field_t;

static int console_show_field(const char *Name, ml_value_t *Value, console_show_field_t *Show) {
	console_show_value(Show->Store, Show->Child, Name, Value);
	return 0;
}

static void ML_TYPED_FN(console_show_value, MLObjectT, GtkTreeStore *Store, GtkTreeIter *Iter, const char *Name, ml_value_t *Value) {
	ml_type_t *Class = ml_typeof(Value);
	GtkTreeIter Child[1];
	gtk_tree_store_insert_with_values(Store, Child, Iter, -1, 0, Name, 1, ml_type_name(Class), -1);
	console_show_field_t Show[1] = {{Store, Child}};
	ml_object_foreach(Value, Show, (void *)console_show_field);
}

static void console_show_thread(gtk_console_t *Console, const char *SourceName, int Line) {
	GtkWidget *SourceView;
	if (!strcmp(SourceName, Console->Name)) {
		SourceView = Console->SourceView;
	} else {
		SourceView = console_open_source(Console, SourceName);
	}
	ml_value_t *BreakpointSet = ml_interactive_debugger_get(Console->Debugger, "breakpoint_set");
	stringmap_foreach(Console->OpenFiles, BreakpointSet, (void *)console_debug_set_breakpoints);
	int PageNum = gtk_notebook_page_num(Console->Notebook, gtk_widget_get_parent(SourceView));
	gtk_notebook_set_current_page(Console->Notebook, PageNum);
	GtkTextBuffer *Buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(SourceView));
	GtkTextIter LineBeg[1], LineEnd[1];
	gtk_text_buffer_get_iter_at_line(Buffer, LineBeg, Line - 1);
	gtk_text_buffer_get_iter_at_line(Buffer, LineEnd, Line);
	//gtk_text_buffer_apply_tag(Buffer, PausedTag, LineBeg, LineEnd);
	gtk_text_buffer_place_cursor(Buffer, LineBeg);
	gtk_text_view_scroll_to_iter(GTK_TEXT_VIEW(SourceView), LineBeg, 0.0, FALSE, 0.0, 0.0);
	gtk_tree_store_clear(Console->FrameStore);
	ml_value_t *FramesGet = ml_interactive_debugger_get(Console->Debugger, "frames");
	ml_value_t *LocalsGet = ml_interactive_debugger_get(Console->Debugger, "locals");
	ml_value_t *Frames = ml_simple_call(FramesGet, 0, NULL);
	ml_value_t **Args = ml_alloc_args(1);
	int Depth = 0;
	ML_LIST_FOREACH(Frames, Iter1) {
		char *Source;
		GC_asprintf(&Source, "%s:%ld",
			ml_string_value(ml_tuple_get(Iter1->Value, 1)),
			ml_integer_value(ml_tuple_get(Iter1->Value, 2))
		);
		GtkTreeIter TreeIter[1];
		gtk_tree_store_insert_with_values(Console->FrameStore, TreeIter, NULL, -1, 0, Source, -1);
		Args[0] = ml_integer(Depth++);
		ml_value_t *Locals = ml_simple_call(LocalsGet, 1, Args);
		ML_MAP_FOREACH(Locals, Iter2) {
			console_show_value(Console->FrameStore, TreeIter, ml_string_value(Iter2->Key), ml_deref(Iter2->Value));
		}
	}
	gtk_tree_view_expand_all(GTK_TREE_VIEW(Console->FrameView));
}

static void console_thread_activated(GtkTreeView *ThreadView, GtkTreePath *Path, GtkTreeViewColumn *Column, gtk_console_t *Console) {
	const char *SourceName;
	int Index, Line;
	GtkTreeIter Iter[1];
	gtk_tree_model_get_iter(GTK_TREE_MODEL(Console->ThreadStore), Iter, Path);
	gtk_tree_model_get(GTK_TREE_MODEL(Console->ThreadStore), Iter, 0, &Index, 1, &SourceName, 2, &Line, -1);
	ml_value_t *ThreadSet = ml_interactive_debugger_get(Console->Debugger, "thread");
	ml_value_t **Args = ml_alloc_args(1);
	Args[0] = ml_integer(Index);
	ml_simple_call(ThreadSet, 1, Args);
	console_show_thread(Console, SourceName, Line);
}

static void console_debug_enter(gtk_console_t *Console, ml_interactive_debugger_t *Debugger, ml_source_t Source, int Index) {
	gtk_widget_show(Console->DebugButtons);
	Console->Debugger = Debugger;
	gtk_console_printf(Console, "Debug break [%d]: %s:%d\n", Index, Source.Name, Source.Line);
	GtkTreeIter Iter[1];
	gtk_list_store_insert_with_values(Console->ThreadStore, Iter, -1, 0, Index, 1, Source.Name, 2, Source.Line, -1);
	GtkTreeSelection *Selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(Console->ThreadView));
	gtk_tree_selection_select_iter(Selection, Iter);
	console_show_thread(Console, Source.Name, Source.Line);
}

static void console_debug_exit(gtk_console_t *Console, ml_interactive_debugger_t *Debugger, ml_state_t *Caller, int Index) {
	GtkTreeIter Iter[1];
	GtkTreeModel *Model = GTK_TREE_MODEL(Console->ThreadStore);
	if (gtk_tree_model_get_iter_first(Model, Iter)) do {
		int Index0;
		gtk_tree_model_get(Model, Iter, 0, &Index0, -1);
		if (Index0 == Index) {
			gtk_list_store_remove(Console->ThreadStore, Iter);
			break;
		}
	} while (gtk_tree_model_iter_next(Model, Iter));
	gtk_tree_store_clear(Console->FrameStore);
	if (!gtk_tree_model_iter_n_children(Model, NULL)) {
		gtk_widget_hide(Console->DebugButtons);
	} else {
		// TODO: Select another thread
		GtkTreeSelection *Selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(Console->ThreadView));
		gtk_tree_selection_unselect_all(Selection);
	}
	return ml_interactive_debugger_resume(Debugger, Index);
}

static void console_clear(GtkWidget *Button, gtk_console_t *Console) {
	GtkTextBuffer *LogBuffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(Console->LogView));
	GtkTextIter Start[1], End[1];
	gtk_text_buffer_get_start_iter(LogBuffer, Start);
	gtk_text_buffer_get_end_iter(LogBuffer, End);
	gtk_text_buffer_delete(LogBuffer, Start, End);
}

static void toggle_layout(GtkWidget *Button, gtk_console_t *Console) {
	switch (gtk_orientable_get_orientation(GTK_ORIENTABLE(Console->Paned))) {
	case GTK_ORIENTATION_HORIZONTAL:
		gtk_orientable_set_orientation(GTK_ORIENTABLE(Console->Paned), GTK_ORIENTATION_VERTICAL);
		break;
	case GTK_ORIENTATION_VERTICAL:
		gtk_orientable_set_orientation(GTK_ORIENTABLE(Console->Paned), GTK_ORIENTATION_HORIZONTAL);
		break;
	}
}

static void console_settings_show(GtkWidget *Button, gtk_console_t *Console) {
	gtk_widget_show(Console->Settings->Dialog);
}

static void console_update_css(GtkCssProvider *CssProvider, PangoFontDescription *FontDescription, GtkSourceStyleScheme *Scheme) {
	const char *Style = "normal";
	switch (pango_font_description_get_style(FontDescription)) {
	case PANGO_STYLE_NORMAL: Style = "normal"; break;
	case PANGO_STYLE_ITALIC: Style = "italic"; break;
	case PANGO_STYLE_OBLIQUE: Style = "oblique"; break;
	}
	gchar *Foreground = NULL, *Background = NULL;
	gchar *SelectedForeground = NULL, *SelectedBackground = NULL;
	if (Scheme) {
		GtkSourceStyle *Text = gtk_source_style_scheme_get_style(Scheme, "text");
		if (Text) g_object_get(Text, "foreground", &Foreground, "background", &Background, NULL);
		GtkSourceStyle *Selected = gtk_source_style_scheme_get_style(Scheme, "current-line");
		if (!Selected) Selected = gtk_source_style_scheme_get_style(Scheme, "selection");
		if (Selected) g_object_get(Selected, "foreground", &SelectedForeground, "background", &SelectedBackground, NULL);

	}
	g_autofree char *CSS = g_strdup_printf(
		"textview.sourceview, treeview.debugger {\n"
		" font-family: '%s';\n"
		" font-size: %d%s;\n"
		" font-style: %s;\n"
		" font-weight: %d;\n"
		"}\n"
		"\n"
		"treeview.debugger {\n"
		" color: %s;\n"
		" background-color: %s;\n"
		"}"
		"\n"
		"treeview.debugger:selected {\n"
		" color: %s;\n"
		" background-color: %s;\n"
		"}",
		pango_font_description_get_family(FontDescription) ?: "Monospace",
		pango_font_description_get_size(FontDescription) / PANGO_SCALE ?: 12,
		pango_font_description_get_size_is_absolute(FontDescription) ? "px" : "pt",
		Style,
		pango_font_description_get_weight(FontDescription),
		Foreground ?: "initial",
		Background ?: "initial",
		SelectedForeground ?: Foreground ?: "initial",
		SelectedBackground ?: Background ?: "initial"
	);
	g_free(Foreground);
	g_free(Background);
	g_free(SelectedForeground);
	g_free(SelectedBackground);
	ML_LOG_DEBUG(NULL, "Updating font description: %s", CSS);
	gtk_css_provider_load_from_string(CssProvider, CSS);
}

static void console_size_allocate(GtkWindow *Window, GdkRectangle *Allocation, gtk_console_t *Console) {
	gint Width, Height;
	gtk_window_get_default_size(Window, &Width, &Height);
	if (Width != Console->WindowSize[0] || Height != Console->WindowSize[1]) {
		Console->WindowSize[0] = Width;
		Console->WindowSize[1] = Height;
		g_key_file_set_integer_list(Console->Config, "gtk-console", "size", Console->WindowSize, 2);
		g_key_file_save_to_file(Console->Config, Console->ConfigPath, NULL);
	}
}

static gboolean console_quit(GtkWindow *Window, gtk_console_t *Console) {
	g_source_remove(Console->StatusTimeout);
	ml_state_schedule(Console->Base.Caller, MLNil);
	return FALSE;
}

#ifdef __APPLE__
#define COMMAND_MASK GDK_META_MASK
#else
#define COMMAND_MASK GDK_CONTROL_MASK
#endif

static gboolean console_keypress(GtkEventControllerKey *Controller, guint Keyval, guint Keycode, GdkModifierType State, gtk_console_t *Console) {
	switch (Keyval) {
	case GDK_KEY_Return:
		Console->NumChars = 0;
		if (State & COMMAND_MASK) {
			console_submit(NULL, Console);
			return TRUE;
		}
		break;
	case GDK_KEY_Up:
		Console->NumChars = 0;
		if (State & COMMAND_MASK) {
			int HistoryIndex = (Console->HistoryIndex + MAX_HISTORY - 1) % MAX_HISTORY;
			if (Console->History[HistoryIndex]) {
				gtk_text_buffer_set_text(gtk_text_view_get_buffer(GTK_TEXT_VIEW(Console->InputView)), Console->History[HistoryIndex], -1);
				Console->HistoryIndex = HistoryIndex;
			}
			return TRUE;
		}
		break;
	case GDK_KEY_Down:
		Console->NumChars = 0;
		if (State & COMMAND_MASK) {
			int HistoryIndex = (Console->HistoryIndex + 1) % MAX_HISTORY;
			if (Console->History[HistoryIndex]) {
				gtk_text_buffer_set_text(gtk_text_view_get_buffer(GTK_TEXT_VIEW(Console->InputView)), Console->History[HistoryIndex], -1);
				Console->HistoryIndex = HistoryIndex;
			} else {
				gtk_text_buffer_set_text(gtk_text_view_get_buffer(GTK_TEXT_VIEW(Console->InputView)), "", 0);
				Console->HistoryIndex = Console->HistoryEnd;
			}
			return TRUE;
		}
		break;
	case GDK_KEY_Escape:
	case GDK_KEY_Left:
	case GDK_KEY_Right:
		Console->NumChars = 0;
		break;
	case GDK_KEY_BackSpace:
		if (Console->NumChars > 0) --Console->NumChars;
		break;
	case GDK_KEY_Tab: {
		Console->Chars[Console->NumChars] = 0;
		for (int I = 0; I < Console->NumChars; ++I) {
			const char *Cycle = stringmap_search(Console->Cycles, Console->Chars + I);
			if (Cycle) {
				GtkTextIter Start[1], End[1];
				GtkTextBuffer *InputBuffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(Console->InputView));
				GtkTextMark *Cursor = gtk_text_buffer_get_insert(InputBuffer);
				gtk_text_buffer_get_iter_at_mark(InputBuffer, Start, Cursor);
				gtk_text_buffer_get_iter_at_mark(InputBuffer, End, Cursor);
				gtk_text_iter_backward_chars(Start, g_utf8_strlen(Console->Chars + I, Console->NumChars - I));
				Console->NumChars = stpcpy(Console->Chars + I, Cycle) - Console->Chars;
				gtk_text_buffer_delete(InputBuffer, Start, End);
				gtk_text_buffer_insert(InputBuffer, Start, Console->Chars + I, Console->NumChars - I);
				return TRUE;
			}
		}
		break;
	}
	default: {
		guint32 Unichar = gdk_keyval_to_unicode(Keyval);
		if (!Unichar) return FALSE;
		if (Unichar <= 32) {
			Console->NumChars = 0;
			return FALSE;
		}
		Console->NumChars += g_unichar_to_utf8(Unichar, Console->Chars + Console->NumChars);
		if (Console->NumChars > 16) {
			memmove(Console->Chars, Console->Chars + Console->NumChars - 16, 16);
			Console->NumChars = 16;
		}
		Console->Chars[Console->NumChars] = 0;
		for (int I = 0; I < Console->NumChars; ++I) {
			const char *Combo = stringmap_search(Console->Combos, Console->Chars + I);
			if (Combo) {
				GtkTextIter Start[1], End[1];
				GtkTextBuffer *InputBuffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(Console->InputView));
				GtkTextMark *Cursor = gtk_text_buffer_get_insert(InputBuffer);
				gtk_text_buffer_get_iter_at_mark(InputBuffer, Start, Cursor);
				gtk_text_buffer_get_iter_at_mark(InputBuffer, End, Cursor);
				gtk_text_iter_backward_chars(Start, g_utf8_strlen(Console->Chars + I, Console->NumChars - I) - 1);
				Console->NumChars = stpcpy(Console->Chars + I, Combo) - Console->Chars;
				gtk_text_buffer_delete(InputBuffer, Start, End);
				gtk_text_buffer_insert(InputBuffer, Start, Console->Chars + I, Console->NumChars - I);
				return TRUE;
			}
		}
	}
	}
	return FALSE;
}

void gtk_console_show(gtk_console_t *Console, GtkWindow *Parent) {
	gtk_window_set_transient_for(GTK_WINDOW(Console->Window), Parent);
	gtk_window_present(GTK_WINDOW(Console->Window));
	gtk_widget_hide(Console->DebugButtons);
	gtk_widget_grab_focus(Console->InputView);
}

int gtk_console_append(gtk_console_t *Console, const char *Buffer, int Length) {
	GtkTextIter End[1];
	GtkTextBuffer *LogBuffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(Console->LogView));
	gtk_text_buffer_get_end_iter(LogBuffer, End);

	if (g_utf8_validate(Buffer, Length, NULL)) {
		gtk_text_buffer_insert_with_tags(LogBuffer, End, Buffer, Length, Console->OutputTag, NULL);
	} else {
		gtk_text_buffer_insert_with_tags(LogBuffer, End, "<", 1, Console->BinaryTag, NULL);
		for (int I = 0; I < Length; ++I) {
			static char HexChars[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
			char Bytes[4] = " ??";
			unsigned char Byte = Buffer[I];
			Bytes[1] = HexChars[Byte >> 4];
			Bytes[2] = HexChars[Byte & 15];
			gtk_text_buffer_insert_with_tags(LogBuffer, End, Bytes, 3, Console->BinaryTag, NULL);
		}
		gtk_text_buffer_insert_with_tags(LogBuffer, End, " >", 2, Console->BinaryTag, NULL);
	}
	gtk_text_view_scroll_mark_onscreen(GTK_TEXT_VIEW(Console->LogView), Console->EndMark);
	while (g_main_context_pending(NULL)) g_main_context_iteration(NULL, FALSE);
	return 0;
}

ml_value_t *gtk_console_print(gtk_console_t *Console, int Count, ml_value_t **Args) {
	GtkTextIter End[1];
	GtkTextBuffer *LogBuffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(Console->LogView));
	gtk_text_buffer_get_end_iter(LogBuffer, End);
	ml_stringbuffer_t Buffer[1] = {ML_STRINGBUFFER_INIT};
	for (int I = 0; I < Count; ++I) {
		ml_value_t *Result = ml_stringbuffer_append(Buffer, Args[I]);
		if (ml_is_error(Result)) return Result;
	}
	ml_stringbuffer_drain(Buffer, Console, (void *)gtk_console_append);
	while (g_main_context_pending(NULL)) g_main_context_iteration(NULL, FALSE);
	return MLNil;
}

ml_value_t *gtk_console_display(gtk_console_t *Console, int Count, ml_value_t **Args) {
	ML_CHECK_ARG_COUNT(1);
	ML_CHECK_ARG_TYPE(0, MLBooleanT);
	Console->DisplayOutput = Args[0] == (ml_value_t *)MLTrue;
	return Args[0];
}

void gtk_console_printf(gtk_console_t *Console, const char *Format, ...) {
	char *Buffer;
	va_list Args;
	va_start(Args, Format);
	int Length = vasprintf(&Buffer, Format, Args);
	va_end(Args);
	gtk_console_append(Console, Buffer, Length);
	free(Buffer);
}

static ml_value_t *console_set_font(gtk_console_t *Console, int Count, ml_value_t **Args) {
	ML_CHECK_ARG_COUNT(2);
	ML_CHECK_ARG_TYPE(0, MLStringT);
	ML_CHECK_ARG_TYPE(1, MLIntegerT);
	Console->FontDescription = pango_font_description_new();
	pango_font_description_set_family(Console->FontDescription, ml_string_value(Args[0]));
	pango_font_description_set_size(Console->FontDescription, PANGO_SCALE * ml_integer_value(Args[1]));
	console_update_css(Console->CssProvider, Console->FontDescription, Console->StyleScheme);
	return MLNil;
}

static ml_value_t *console_set_style(gtk_console_t *Console, int Count, ml_value_t **Args) {
	ML_CHECK_ARG_COUNT(1);
	ML_CHECK_ARG_TYPE(0, MLStringT);
	GtkSourceStyleSchemeManager *StyleManager = gtk_source_style_scheme_manager_get_default();
	Console->StyleScheme = gtk_source_style_scheme_manager_get_scheme(StyleManager, ml_string_value(Args[0]));
	gtk_source_buffer_set_style_scheme(GTK_SOURCE_BUFFER(gtk_text_view_get_buffer(GTK_TEXT_VIEW(Console->InputView))), Console->StyleScheme);
	gtk_source_buffer_set_style_scheme(GTK_SOURCE_BUFFER(gtk_text_view_get_buffer(GTK_TEXT_VIEW(Console->LogView))), Console->StyleScheme);
	return MLNil;
}

static ml_value_t *console_add_cycle(gtk_console_t *Console, int Count, ml_value_t **Args) {
	ML_CHECK_ARG_COUNT(1);
	ML_CHECK_ARG_TYPE(0, MLStringT);
	for (int I = 1; I < Count; ++I) {
		ML_CHECK_ARG_TYPE(I, MLStringT);
		stringmap_insert(Console->Cycles, ml_string_value(Args[I - 1]), (void *)ml_string_value(Args[I]));
	}
	stringmap_insert(Console->Cycles, ml_string_value(Args[Count - 1]), (void *)ml_string_value(Args[0]));
	return MLNil;
}

static ml_value_t *console_add_combo(gtk_console_t *Console, int Count, ml_value_t **Args) {
	ML_CHECK_ARG_COUNT(2);
	ML_CHECK_ARG_TYPE(0, MLStringT);
	ML_CHECK_ARG_TYPE(1, MLStringT);
	stringmap_insert(Console->Combos, ml_string_value(Args[0]), (void *)ml_string_value(Args[1]));
	stringmap_insert(Console->Cycles, ml_string_value(Args[1]), (void *)ml_string_value(Args[0]));
	return MLNil;
}

static void console_included_run(ml_state_t *State, ml_value_t *Value) {
	ml_state_t *Caller = State->Caller;
	if (ml_is_error(Value)) ML_RETURN(Value);
	return ml_call(Caller, Value, 0, NULL);
}

static void console_include_fnx(ml_state_t *Caller, gtk_console_t *Console, int Count, ml_value_t **Args) {
	ML_CHECKX_ARG_COUNT(1);
	ML_CHECKX_ARG_TYPE(0, MLStringT);
	ml_state_t *State = new(ml_state_t);
	State->Caller = Caller;
	State->Context = Caller->Context;
	State->run = console_included_run;
	return ml_load_file(State, (ml_getter_t)ml_compiler_lookup, Console->Compiler, ml_string_value(Args[0]), NULL);
}

static gboolean console_update_status(gtk_console_t *Console) {
	GC_word HeapSize, FreeBytes, UnmappedBytes, BytesSinceGC, TotalBytes;
	GC_get_heap_usage_safe(&HeapSize, &FreeBytes, &UnmappedBytes, &BytesSinceGC, &TotalBytes);
	GC_word UsedSize = HeapSize - FreeBytes;
	int UsedBase, HeapBase;
	char UsedUnits, HeapUnits;
	if (UsedSize < (1 << 10)) {
		UsedBase = UsedSize;
		UsedUnits = 'b';
	} else if (UsedSize < (1 << 20)) {
		UsedBase = UsedSize >> 10;
		UsedUnits = 'k';
	} else if (UsedSize < (1 << 30)) {
		UsedBase = UsedSize >> 20;
		UsedUnits = 'M';
	} else {
		UsedBase = UsedSize >> 30;
		UsedUnits = 'G';
	}
	if (HeapSize < (1 << 10)) {
		HeapBase = HeapSize;
		HeapUnits = 'b';
	} else if (HeapSize < (1 << 20)) {
		HeapBase = HeapSize >> 10;
		HeapUnits = 'k';
	} else if (HeapSize < (1 << 30)) {
		HeapBase = HeapSize >> 20;
		HeapUnits = 'M';
	} else {
		HeapBase = HeapSize >> 30;
		HeapUnits = 'G';
	}

	char Text[48];
	sprintf(Text, "Memory: %d%c / %d%c", UsedBase, UsedUnits, HeapBase, HeapUnits);
	gtk_label_set_text(Console->MemoryBar, Text);
	/*printf("Memory Status:\n");
	printf("\tHeapSize = %ld\n", HeapSize);
	printf("\tFreeBytes = %ld\n", FreeBytes);
	printf("\tUnmappedBytes = %ld\n", UnmappedBytes);
	printf("\tBytesSinceGC = %ld\n", BytesSinceGC);
	printf("\tTotalBytes = %ld\n", TotalBytes);*/
	return G_SOURCE_CONTINUE;
}

static void console_settings_apply(GtkButton *Widget, gtk_console_settings_t *Settings) {
	gtk_console_t *Console = Settings->Console;
	GObject *SelectedItem = gtk_drop_down_get_selected_item(GTK_DROP_DOWN(Settings->StyleDropDown));
	const char *StyleId = gtk_string_object_get_string(GTK_STRING_OBJECT(SelectedItem));
	Console->StyleScheme = gtk_source_style_scheme_manager_get_scheme(Settings->StyleManager, StyleId);

	gtk_source_buffer_set_style_scheme(GTK_SOURCE_BUFFER(gtk_text_view_get_buffer(GTK_TEXT_VIEW(Console->InputView))), Console->StyleScheme);
	gtk_source_buffer_set_style_scheme(GTK_SOURCE_BUFFER(gtk_text_view_get_buffer(GTK_TEXT_VIEW(Console->LogView))), Console->StyleScheme);
	for (int I = gtk_notebook_get_n_pages(Console->Notebook); --I >= 0;) {
		GtkWidget *Widget = gtk_notebook_get_nth_page(Console->Notebook, I);
		if (GTK_IS_SCROLLED_WINDOW(Widget)) {
			GtkWidget *Widget2 = gtk_scrolled_window_get_child(GTK_SCROLLED_WINDOW(Widget));
			if (GTK_SOURCE_IS_VIEW(Widget2)) {
				GtkTextBuffer *Buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(Widget2));
				gtk_source_buffer_set_style_scheme(GTK_SOURCE_BUFFER(Buffer), Console->StyleScheme);
			}
		}
	}
	g_key_file_set_string(Console->Config, "gtk-console", "style", StyleId);
	g_key_file_save_to_file(Console->Config, Console->ConfigPath, NULL);

	Console->FontDescription = gtk_font_dialog_button_get_font_desc(GTK_FONT_DIALOG_BUTTON(Settings->FontButton));
	console_update_css(Console->CssProvider, Console->FontDescription, Console->StyleScheme);
	const char *FontName = pango_font_description_to_string(Console->FontDescription);
	g_key_file_set_string(Console->Config, "gtk-console", "font", FontName);
	g_free((void *)FontName);
	g_key_file_save_to_file(Console->Config, Console->ConfigPath, NULL);
	gtk_widget_hide(Settings->Dialog);
}

static void console_settings_cancel(GtkButton *Widget, gtk_console_settings_t *Settings) {
	gtk_widget_hide(Settings->Dialog);
}

static void style_drop_down_changed(GtkDropDown *Widget, GParamSpec *Spec, gtk_console_settings_t *Settings) {
	GObject *SelectedItem = gtk_drop_down_get_selected_item(Widget);
	const char *StyleId = gtk_string_object_get_string(GTK_STRING_OBJECT(SelectedItem));
	GtkSourceStyleScheme *StyleScheme = gtk_source_style_scheme_manager_get_scheme(Settings->StyleManager, StyleId);
	Settings->StyleScheme = StyleScheme;
	gtk_source_buffer_set_style_scheme(Settings->PreviewBuffer, StyleScheme);
}

static void console_font_changed(GtkFontDialogButton *Widget, GParamSpec *Spec, gtk_console_settings_t *Settings) {
	PangoFontDescription *FontDescription = gtk_font_dialog_button_get_font_desc(Widget);
	console_update_css(Settings->CssProvider, FontDescription, Settings->StyleScheme);
}

static gtk_console_settings_t *gtk_console_settings(gtk_console_t *Console, GtkSourceStyleSchemeManager *StyleManager) {
	gtk_console_settings_t *Settings = new(gtk_console_settings_t);
	Settings->Console = Console;
	Settings->StyleManager = StyleManager;
	GtkWidget *Box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
	gtk_widget_set_margin_top(Box, 20);
	gtk_widget_set_margin_bottom(Box, 20);
	gtk_widget_set_margin_start(Box, 20);
	gtk_widget_set_margin_end(Box, 20);
	const gchar * const *StyleIds = gtk_source_style_scheme_manager_get_scheme_ids(StyleManager);
	GtkWidget *StyleDropDown = Settings->StyleDropDown = gtk_drop_down_new_from_strings(StyleIds);
	if (Console->StyleScheme) {
		const char *StyleId = gtk_source_style_scheme_get_id(Console->StyleScheme);
		for (const gchar * const *Ptr = StyleIds; *Ptr; ++Ptr) {
			ML_LOG_INFO(NULL, "Comparing %s <-> %s", *Ptr, StyleId);
			if (!strcmp(*Ptr, StyleId)) {
				gtk_drop_down_set_selected(GTK_DROP_DOWN(StyleDropDown), Ptr - StyleIds);
				break;
			}
		}
	}
	gtk_drop_down_set_enable_search(GTK_DROP_DOWN(StyleDropDown), TRUE);
	gtk_drop_down_set_search_match_mode(GTK_DROP_DOWN(StyleDropDown), GTK_STRING_FILTER_MATCH_MODE_SUBSTRING);
	g_signal_connect(G_OBJECT(StyleDropDown), "notify::selected-item", G_CALLBACK(style_drop_down_changed), Settings);
	gtk_widget_set_hexpand(StyleDropDown, TRUE);
	GtkFontDialog *FontDialog = gtk_font_dialog_new();
	GtkWidget *FontButton = Settings->FontButton = gtk_font_dialog_button_new(FontDialog);
	g_signal_connect(G_OBJECT(FontButton), "notify::font-desc", G_CALLBACK(console_font_changed), Settings);
	gtk_widget_set_hexpand(FontButton, TRUE);
	GtkWidget *TopBox = gtk_grid_new();
	gtk_grid_set_column_spacing(GTK_GRID(TopBox), 20);
	gtk_grid_set_row_spacing(GTK_GRID(TopBox), 20);
	GtkWidget *StyleLabel = gtk_label_new("Style");
	gtk_widget_add_css_class(StyleLabel, "heading");
	GtkWidget *FontLabel = gtk_label_new("Font");
	gtk_widget_add_css_class(FontLabel, "heading");
	gtk_grid_attach(GTK_GRID(TopBox), StyleLabel, 0, 0, 1, 1);
	gtk_grid_attach(GTK_GRID(TopBox), StyleDropDown, 1, 0, 1, 1);
	gtk_grid_attach(GTK_GRID(TopBox), FontLabel, 0, 1, 1, 1);
	gtk_grid_attach(GTK_GRID(TopBox), FontButton, 1, 1, 1, 1);
	gtk_box_append(GTK_BOX(Box), TopBox);
	Settings->PreviewBuffer = gtk_source_buffer_new_with_language(Console->Language);
	if (Console->StyleScheme) {
		Settings->StyleScheme = Console->StyleScheme;
		gtk_source_buffer_set_style_scheme(Settings->PreviewBuffer, Console->StyleScheme);
	}
	GtkWidget *Preview = gtk_source_view_new_with_buffer(Settings->PreviewBuffer);
	gtk_text_buffer_set_text(GTK_TEXT_BUFFER(Settings->PreviewBuffer),
		"import: terminal(\"io/terminal\")\n"
		"\n"
		"fun test(N: integer): integer do\n"
		"\tlet L := [1, 2, 3]\n"
		"\tfor I in 1 .. N do\n"
		"\t\tswitch I % 15: integer\n"
		"\t\tcase 0 do\n"
		"\t\t\tL:put(math::sin(I))\n"
		"\t\tcase 3 do\n"
		"\t\t\tprint(max(L skip 3))\n"
		"\t\tcase 5 do\n"
		"\t\t\tterminal::Stdout:write(\"Hello world!\\n\")\n"
		"\t\telse\n"
		"\t\t\tL:put(\'I = {I}, Now = {time(), time::timezone::\"Europe/Dublin\"}\\n\')\n"
		"\t\tend\n"
		"\t\tuntil I >= 10\n"
		"\tend\n"
		"end",
	-1);
	gtk_source_view_set_tab_width(GTK_SOURCE_VIEW(Preview), 4);
	gtk_source_view_set_show_line_numbers(GTK_SOURCE_VIEW(Preview), TRUE);
	gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(Preview), TRUE);
	GtkWidget *PreviewFrame = gtk_frame_new(NULL);
	gtk_frame_set_child(GTK_FRAME(PreviewFrame), Preview);
	gtk_box_append(GTK_BOX(Box), PreviewFrame);

	Settings->Dialog = gtk_window_new();
	gtk_window_set_hide_on_close(GTK_WINDOW(Settings->Dialog), TRUE);

	GtkWidget *HeaderBar = gtk_header_bar_new();
	gtk_header_bar_set_use_native_controls(GTK_HEADER_BAR(HeaderBar), FALSE);
	gtk_header_bar_set_show_title_buttons(GTK_HEADER_BAR(HeaderBar), FALSE);
	GtkWidget *SettingsTitle = gtk_label_new("Settings");
	gtk_widget_add_css_class(SettingsTitle, "title");
	gtk_header_bar_set_title_widget(GTK_HEADER_BAR(HeaderBar), SettingsTitle);

	GtkWidget *ApplyButton = gtk_button_new_with_label("Apply");
	gtk_widget_add_css_class(ApplyButton, "suggested-action");
	GtkWidget *CancelButton = gtk_button_new_with_label("Cancel");

	g_signal_connect(ApplyButton, "clicked", G_CALLBACK(console_settings_apply), Settings);
	g_signal_connect(CancelButton, "clicked", G_CALLBACK(console_settings_cancel), Settings);

	gtk_header_bar_pack_start(GTK_HEADER_BAR(HeaderBar), CancelButton);
	gtk_header_bar_pack_end(GTK_HEADER_BAR(HeaderBar), ApplyButton);
	gtk_window_set_titlebar(GTK_WINDOW(Settings->Dialog), HeaderBar);


	gtk_window_set_child(GTK_WINDOW(Settings->Dialog), Box);
	gtk_window_set_default_size(GTK_WINDOW(Settings->Dialog), 800, -1);
	Settings->CssProvider = gtk_css_provider_new();
	gtk_style_context_add_provider(
		gtk_widget_get_style_context(Preview),
		GTK_STYLE_PROVIDER(Settings->CssProvider),
		GTK_STYLE_PROVIDER_PRIORITY_USER
	);
	if (Console->FontDescription) {
		gtk_font_dialog_button_set_font_desc(GTK_FONT_DIALOG_BUTTON(FontButton), Console->FontDescription);
		console_update_css(Settings->CssProvider, Console->FontDescription, Console->StyleScheme);
	}
	return Settings;
}

gtk_console_t *gtk_console(ml_state_t *Caller, ml_getter_t GlobalGet, void *Globals) {
	gtk_console_t *Console = new(gtk_console_t);
	Console->Base.Type = ConsoleT;
	Console->Base.run = (ml_state_fn)ml_console_repl_run;
	Console->Base.Caller = Caller;
	Console->Base.Context = Caller->Context;
	Console->Name = strdup("<console>");
	Console->ParentGetter = GlobalGet;
	Console->ParentGlobals = Globals;
	Console->HistoryIndex = 0;
	Console->HistoryEnd = 0;
	Console->Parser = ml_parser(NULL, NULL);
	Console->Compiler = ml_compiler2((ml_getter_t)console_global_get, Console, 1);
	ml_parser_source(Console->Parser, (ml_source_t){Console->Name, 0});
	Console->CssProvider = gtk_css_provider_new();
	gtk_style_context_add_provider_for_display(
		gdk_display_get_default(),
		GTK_STYLE_PROVIDER(Console->CssProvider),
		GTK_STYLE_PROVIDER_PRIORITY_USER
	);

	Console->Notebook = GTK_NOTEBOOK(gtk_notebook_new());

	GC_asprintf((char **)&Console->ConfigPath, "%s/%s", g_get_user_config_dir(), "minilang.conf");
	Console->Config = g_key_file_new();
	g_key_file_load_from_file(Console->Config, Console->ConfigPath, G_KEY_FILE_NONE, NULL);

	GtkSourceLanguageManager *LanguageManager = gtk_source_language_manager_get_default();
	Console->Language = gtk_source_language_manager_get_language(LanguageManager, "minilang");

	GtkSourceBuffer *InputBuffer = gtk_source_buffer_new_with_language(Console->Language);
	Console->InputView = gtk_source_view_new_with_buffer(InputBuffer);
	gtk_widget_set_hexpand(Console->InputView, TRUE);
	GtkSourceCompletion *Completion = gtk_source_view_get_completion(GTK_SOURCE_VIEW(Console->InputView));
	g_object_set(Completion, "select-on-show", TRUE, NULL);
	GtkSourceCompletionProvider *Provider = gtk_console_completion_provider(Console->Compiler, Console->Globals);
	gtk_source_completion_add_provider(Completion, Provider);
	GtkTextTagTable *TagTable = gtk_text_buffer_get_tag_table(GTK_TEXT_BUFFER(InputBuffer));
	Console->OutputTag = gtk_text_tag_new("log-output");
	Console->ResultTag = gtk_text_tag_new("log-result");
	Console->ErrorTag = gtk_text_tag_new("log-error");
	Console->BinaryTag = gtk_text_tag_new("log-binary");
	g_object_set(Console->OutputTag,
		"background", "#FFFFF0",
	NULL);
	g_object_set(Console->ResultTag,
		"background", "#FFF0F0",
		"foreground", "#303030",
		"indent", 10,
	NULL);
	g_object_set(Console->ErrorTag,
		"background", "#FFF0F0",
		"foreground", "#FF0000",
		"indent", 10,
	NULL);
	g_object_set(Console->BinaryTag,
		"background", "#F0F0FF",
		"foreground", "#FF8000",
	NULL);
	gtk_text_tag_table_add(TagTable, Console->OutputTag);
	gtk_text_tag_table_add(TagTable, Console->ResultTag);
	gtk_text_tag_table_add(TagTable, Console->ErrorTag);
	gtk_text_tag_table_add(TagTable, Console->BinaryTag);
	GtkSourceBuffer *LogBuffer = gtk_source_buffer_new(TagTable);
	Console->LogView = gtk_source_view_new_with_buffer(LogBuffer);
	gtk_text_view_set_editable(GTK_TEXT_VIEW(Console->LogView), FALSE);
	GtkSourceStyleSchemeManager *StyleManager = gtk_source_style_scheme_manager_get_default();
	Console->SourceBuffer = gtk_source_buffer_new_with_language(Console->Language);

	Console->LogScrolled = gtk_scrolled_window_new();
	gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(Console->LogScrolled), Console->LogView);
	gtk_widget_set_vexpand(Console->LogScrolled, TRUE);

	Console->ThreadStore = gtk_list_store_new(3, G_TYPE_INT, G_TYPE_STRING, G_TYPE_INT);
	gtk_tree_sortable_set_sort_column_id(GTK_TREE_SORTABLE(Console->ThreadStore), 0, GTK_SORT_ASCENDING);
	GtkWidget *ThreadView = Console->ThreadView = gtk_tree_view_new_with_model(GTK_TREE_MODEL(Console->ThreadStore));
	gtk_widget_add_css_class(ThreadView, "debugger");
	gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(ThreadView), -1, "Thread", gtk_cell_renderer_text_new(), "text", 0, NULL);
	gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(ThreadView), -1, "Source", gtk_cell_renderer_text_new(), "text", 1, NULL);
	gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(ThreadView), -1, "Line", gtk_cell_renderer_text_new(), "text", 2, NULL);
	gtk_tree_view_set_activate_on_single_click(GTK_TREE_VIEW(ThreadView), TRUE);
	g_signal_connect(G_OBJECT(ThreadView), "row-activated", G_CALLBACK(console_thread_activated), Console);

	Console->FrameStore = gtk_tree_store_new(2, G_TYPE_STRING, G_TYPE_STRING);
	GtkWidget *FrameView = Console->FrameView = gtk_tree_view_new_with_model(GTK_TREE_MODEL(Console->FrameStore));
	gtk_widget_add_css_class(FrameView, "debugger");
	//gtk_tree_view_set_level_indentation(GTK_TREE_VIEW(FrameView), 20);
	gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(FrameView), -1, "Name", gtk_cell_renderer_text_new(), "text", 0, NULL);
	gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(FrameView), -1, "Value", gtk_cell_renderer_text_new(), "text", 1, NULL);
	gtk_tree_view_set_activate_on_single_click(GTK_TREE_VIEW(FrameView), TRUE);

	GtkWidget *Debugging = gtk_paned_new(GTK_ORIENTATION_VERTICAL);
	GtkWidget *Scrolled = gtk_scrolled_window_new();
	gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(Scrolled), ThreadView);
	gtk_paned_set_start_child(GTK_PANED(Debugging), Scrolled);
	Scrolled = gtk_scrolled_window_new();
	gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(Scrolled), FrameView);
	gtk_paned_set_end_child(GTK_PANED(Debugging), Scrolled);

	gtk_paned_set_position(GTK_PANED(Debugging), 100);

	GtkWidget *OutputPane = gtk_paned_new(GTK_ORIENTATION_HORIZONTAL);
	gtk_paned_set_start_child(GTK_PANED(OutputPane), GTK_WIDGET(Console->Notebook));
	gtk_paned_set_end_child(GTK_PANED(OutputPane), Debugging);
	//gtk_paned_set_position(GTK_PANED(OutputPane), 200);

	Console->Paned = gtk_paned_new(GTK_ORIENTATION_VERTICAL);

	GtkWidget *InputPanel = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
	GtkWidget *DebugButtons = Console->DebugButtons = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
	GtkWidget *StepInButton = gtk_button_new();
	gtk_button_set_label(GTK_BUTTON(StepInButton), "In");
	gtk_box_append(GTK_BOX(DebugButtons), StepInButton);
	GtkWidget *StepOverButton = gtk_button_new();
	gtk_button_set_label(GTK_BUTTON(StepOverButton), "Over");
	gtk_box_append(GTK_BOX(DebugButtons), StepOverButton);
	GtkWidget *StepOutButton = gtk_button_new();
	gtk_button_set_label(GTK_BUTTON(StepOutButton), "Out");
	gtk_box_append(GTK_BOX(DebugButtons), StepOutButton);
	GtkWidget *ContinueButton = gtk_button_new();
	gtk_button_set_label(GTK_BUTTON(ContinueButton), "Run");
	gtk_box_append(GTK_BOX(DebugButtons), ContinueButton);
	GtkWidget *ContinueAllButton = gtk_button_new();
	gtk_button_set_label(GTK_BUTTON(ContinueAllButton), "Run All");
	gtk_box_append(GTK_BOX(DebugButtons), ContinueAllButton);
	g_signal_connect(G_OBJECT(StepInButton), "clicked", G_CALLBACK(console_step_in), Console);
	g_signal_connect(G_OBJECT(StepOverButton), "clicked", G_CALLBACK(console_step_over), Console);
	g_signal_connect(G_OBJECT(StepOutButton), "clicked", G_CALLBACK(console_step_out), Console);
	g_signal_connect(G_OBJECT(ContinueButton), "clicked", G_CALLBACK(console_continue), Console);
	g_signal_connect(G_OBJECT(ContinueAllButton), "clicked", G_CALLBACK(console_continue_all), Console);
	gtk_box_append(GTK_BOX(InputPanel), DebugButtons);
	GtkWidget *SubmitButton = gtk_button_new();
	gtk_button_set_icon_name(GTK_BUTTON(SubmitButton), "go-jump-symbolic");
	GtkWidget *ClearButton = gtk_button_new();
	gtk_button_set_icon_name(GTK_BUTTON(ClearButton), "edit-delete-symbolic");
	gtk_box_append(GTK_BOX(InputPanel), Console->InputView);
	gtk_box_append(GTK_BOX(InputPanel), SubmitButton);
	gtk_box_append(GTK_BOX(InputPanel), ClearButton);

	//GtkWidget *StyleCombo = gtk_source_style_scheme_chooser_button_new();
	//g_signal_connect(G_OBJECT(StyleCombo), "notify::style-scheme", G_CALLBACK(console_style_changed), Console);

	GtkWidget *SourceView = Console->SourceView = gtk_source_view_new_with_buffer(Console->SourceBuffer);
	gtk_text_view_set_monospace(GTK_TEXT_VIEW(SourceView), TRUE);
	gtk_source_view_set_tab_width(GTK_SOURCE_VIEW(SourceView), 4);
	gtk_source_view_set_highlight_current_line(GTK_SOURCE_VIEW(SourceView), TRUE);
	gtk_source_view_set_show_line_numbers(GTK_SOURCE_VIEW(SourceView), TRUE);
	GtkWidget *SourceScrolled = gtk_scrolled_window_new();
	gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(SourceScrolled), SourceView);
	gtk_notebook_append_page(Console->Notebook, SourceScrolled, gtk_label_new("<console>"));

	GtkEventController *KeyEventController = gtk_event_controller_key_new();
	gtk_widget_add_controller(Console->InputView, KeyEventController);

	g_signal_connect(G_OBJECT(KeyEventController), "key-pressed", G_CALLBACK(console_keypress), Console);
	g_signal_connect(G_OBJECT(SubmitButton), "clicked", G_CALLBACK(console_submit), Console);
	g_signal_connect(G_OBJECT(ClearButton), "clicked", G_CALLBACK(console_clear), Console);
	Console->Window = gtk_window_new();
	gtk_window_set_icon_name(GTK_WINDOW(Console->Window), "face-smile");
	gtk_window_set_title(GTK_WINDOW(Console->Window), "Minilang");

	GtkWidget *ReplBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 2);
	gtk_box_append(GTK_BOX(ReplBox), InputPanel);
	gtk_box_append(GTK_BOX(ReplBox), Console->LogScrolled);

	gtk_paned_set_start_child(GTK_PANED(Console->Paned), OutputPane);
	gtk_paned_set_end_child(GTK_PANED(Console->Paned), ReplBox);
	gtk_paned_set_position(GTK_PANED(Console->Paned), 600);

	if (g_key_file_has_key(Console->Config, "gtk-console", "font", NULL)) {
		const char *FontName = g_key_file_get_string(Console->Config, "gtk-console", "font", NULL);
		Console->FontDescription = pango_font_description_from_string(FontName);
		g_free((void *)FontName);
	} else {
		Console->FontDescription = pango_font_description_from_string("Monospace 10");
	}
	if (g_key_file_has_key(Console->Config, "gtk-console", "style", NULL)) {
		const char *StyleId = g_key_file_get_string(Console->Config, "gtk-console", "style", NULL);
		Console->StyleScheme = gtk_source_style_scheme_manager_get_scheme(StyleManager, StyleId);
		GtkSourceBuffer *InputBuffer = GTK_SOURCE_BUFFER(gtk_text_view_get_buffer(GTK_TEXT_VIEW(Console->InputView)));
		gtk_source_buffer_set_style_scheme(InputBuffer, Console->StyleScheme);
		gtk_source_buffer_set_style_scheme(LogBuffer, Console->StyleScheme);
		gtk_source_buffer_set_style_scheme(Console->SourceBuffer, Console->StyleScheme);
		//gtk_source_style_scheme_chooser_set_style_scheme(GTK_SOURCE_STYLE_SCHEME_CHOOSER(StyleCombo), Console->StyleScheme);
	}
	console_update_css(Console->CssProvider, Console->FontDescription, Console->StyleScheme);

	GtkWidget *LayoutButton = gtk_button_new_from_icon_name("object-packing-symbolic");
	g_signal_connect(G_OBJECT(LayoutButton), "clicked", G_CALLBACK(toggle_layout), Console);

	Console->Settings = gtk_console_settings(Console, StyleManager);
	GtkWidget *SettingsButton = gtk_button_new_from_icon_name("general-properties-symbolic");
	g_signal_connect(G_OBJECT(SettingsButton), "clicked", G_CALLBACK(console_settings_show), Console);

	GtkWidget *HeaderBar = gtk_header_bar_new();
	gtk_header_bar_set_use_native_controls(GTK_HEADER_BAR(HeaderBar), TRUE);
	//gtk_header_bar_set_title(GTK_HEADER_BAR(HeaderBar), "Minilang");
	//gtk_header_bar_set_has_subtitle(GTK_HEADER_BAR(HeaderBar), FALSE);
	gtk_header_bar_set_show_title_buttons(GTK_HEADER_BAR(HeaderBar), TRUE);
	gtk_header_bar_pack_start(GTK_HEADER_BAR(HeaderBar), LayoutButton);
	gtk_header_bar_pack_start(GTK_HEADER_BAR(HeaderBar), SettingsButton);
	gtk_window_set_titlebar(GTK_WINDOW(Console->Window), HeaderBar);

	GtkWidget *MemoryBar = gtk_label_new("");
	gtk_header_bar_pack_end(GTK_HEADER_BAR(HeaderBar), MemoryBar);

	Console->MemoryBar = GTK_LABEL(MemoryBar);

	gtk_window_set_child(GTK_WINDOW(Console->Window), Console->Paned);
	if (g_key_file_has_key(Console->Config, "gtk-console", "size", NULL)) {
		gsize Length = 0;
		gint *Size = g_key_file_get_integer_list(Console->Config, "gtk-console", "size", &Length, NULL);
		if (Length == 2) {
			Console->WindowSize[0] = Size[0];
			Console->WindowSize[1] = Size[1];
		}
	} else {
		Console->WindowSize[0] = 640;
		Console->WindowSize[1] = 480;
	}
	gtk_window_set_default_size(GTK_WINDOW(Console->Window), Console->WindowSize[0], Console->WindowSize[1]);
	g_signal_connect(G_OBJECT(Console->Window), "notify::default-width", G_CALLBACK(console_size_allocate), Console);
	g_signal_connect(G_OBJECT(Console->Window), "notify::default-height", G_CALLBACK(console_size_allocate), Console);
	g_signal_connect(G_OBJECT(Console->Window), "close-request", G_CALLBACK(console_quit), Console);

	stringmap_insert(Console->Globals, "set_font", ml_cfunction(Console, (ml_callback_t)console_set_font));
	stringmap_insert(Console->Globals, "set_style", ml_cfunction(Console, (ml_callback_t)console_set_style));
	stringmap_insert(Console->Globals, "add_cycle", ml_cfunction(Console, (ml_callback_t)console_add_cycle));
	stringmap_insert(Console->Globals, "add_combo", ml_cfunction(Console, (ml_callback_t)console_add_combo));
	stringmap_insert(Console->Globals, "include", ml_cfunctionx(Console, (ml_callbackx_t)console_include_fnx));

	gtk_text_view_set_top_margin(GTK_TEXT_VIEW(Console->LogView), 4);
	gtk_text_view_set_bottom_margin(GTK_TEXT_VIEW(Console->LogView), 4);
	gtk_text_view_set_left_margin(GTK_TEXT_VIEW(Console->LogView), 4);
	gtk_text_view_set_right_margin(GTK_TEXT_VIEW(Console->LogView), 4);
	gtk_text_view_set_monospace(GTK_TEXT_VIEW(Console->LogView), TRUE);
	gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(Console->LogView), TRUE);
	gtk_source_view_set_tab_width(GTK_SOURCE_VIEW(Console->LogView), 4);
	GtkTextIter End[1];
	gtk_text_buffer_get_end_iter(GTK_TEXT_BUFFER(LogBuffer), End);
	Console->EndMark = gtk_text_buffer_create_mark(GTK_TEXT_BUFFER(LogBuffer), "end", End, FALSE);

	GtkSourceMarkAttributes *MarkAttributes = gtk_source_mark_attributes_new();
	GdkPixbuf *MarkPixbuf = gdk_pixbuf_new(GDK_COLORSPACE_RGB, TRUE, 8, 32, 32);
	gdk_pixbuf_fill(MarkPixbuf, 0xFF8000FF);
	gtk_source_mark_attributes_set_pixbuf(MarkAttributes, MarkPixbuf);
	gtk_source_view_set_mark_attributes(GTK_SOURCE_VIEW(Console->LogView), "result", MarkAttributes, 10);
	gtk_source_view_set_show_line_marks(GTK_SOURCE_VIEW(Console->LogView), TRUE);

	gtk_text_view_set_top_margin(GTK_TEXT_VIEW(Console->InputView), 4);
	gtk_text_view_set_bottom_margin(GTK_TEXT_VIEW(Console->InputView), 4);
	gtk_text_view_set_left_margin(GTK_TEXT_VIEW(Console->InputView), 4);
	gtk_text_view_set_right_margin(GTK_TEXT_VIEW(Console->InputView), 4);
	gtk_text_view_set_monospace(GTK_TEXT_VIEW(Console->InputView), TRUE);
	gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(Console->InputView), TRUE);
	gtk_source_view_set_tab_width(GTK_SOURCE_VIEW(Console->InputView), 4);
	gtk_source_view_set_show_line_numbers(GTK_SOURCE_VIEW(Console->InputView), TRUE);

	Console->StatusTimeout = g_timeout_add(1000, (GSourceFunc)console_update_status, Console);

	stringmap_insert(Console->Globals, "print", ml_cfunction2(Console, (void *)gtk_console_print, ML_CATEGORY, __LINE__));
	Console->DisplayOutput = 1;
	stringmap_insert(Console->Globals, "display", ml_cfunction2(Console, (void *)gtk_console_display, ML_CATEGORY, __LINE__));
	stringmap_insert(Console->Globals, "Console", ml_gir_instance_get(Console->Window, NULL));
	stringmap_insert(Console->Globals, "InputView", ml_gir_instance_get(Console->InputView, NULL));
	stringmap_insert(Console->Globals, "LogView", ml_gir_instance_get(Console->LogView, NULL));
	stringmap_insert(Console->Globals, "idebug", ml_interactive_debugger(
		(void *)console_debug_enter,
		(void *)console_debug_exit,
		(void *)gtk_console_log,
		Console,
		GlobalGet,
		Globals
	));

	return Console;
}

void gtk_console_load_file(gtk_console_t *Console, const char *FileName, ml_value_t *Args) {
	ml_call_state_t *State = ml_call_state((ml_state_t *)Console, 1);
	State->Args[0] = Args;
	ml_load_file((ml_state_t *)State, (void *)console_global_get, Console, FileName, NULL);
}

ML_METHOD("load", ConsoleT, MLStringT, MLListT) {
	gtk_console_t *Console = (gtk_console_t *)Args[0];
	const char *FileName = ml_string_value(Args[1]);
	ml_call_state_t *State = ml_call_state((ml_state_t *)Console, 1);
	State->Args[0] = Args[2];
	ml_load_file((ml_state_t *)State, (void *)console_global_get, Console, FileName, NULL);
	return (ml_value_t *)Console;
}

ML_METHOD("parser", ConsoleT) {
	gtk_console_t *Console = (gtk_console_t *)Args[0];
	return (ml_value_t *)Console->Parser;
}

ML_METHOD("compiler", ConsoleT) {
	gtk_console_t *Console = (gtk_console_t *)Args[0];
	return (ml_value_t *)Console->Compiler;
}

typedef struct {
	ml_state_t Base;
	ml_value_t **Slot;
} load_state_t;

static void finish_load(load_state_t *State, ml_value_t *GirModule) {
	GError *Error = 0;
	g_irepository_require(NULL, "Gtk", "4.0", 0, &Error);
	g_irepository_require(NULL, "GtkSource", "5", 0, &Error);
	gtk_init();
	gtk_source_init();
	ml_state_t *Caller = State->Base.Caller;
#include "gtk_console_init.c"
	gtk_console_t *Console = gtk_console(Caller, (ml_getter_t)ml_stringmap_global_get, MLGlobals);
	State->Slot[0] = (ml_value_t *)Console;
	gtk_console_show(Console, NULL);
	/*if (MainModule) gtk_console_load_file(Console, MainModule, Args);
	if (Command) gtk_console_evaluate(Console, Command);
	while (!MainResult) Scheduler->run(Scheduler);*/
	ML_RETURN(Console);
}

ML_LIBRARY_ENTRY(util_gtk_console) {
	load_state_t *State = new(load_state_t);
	State->Base.Caller = Caller;
	State->Base.Context = Caller->Context;
	State->Base.run = (ml_state_fn)finish_load;
	State->Slot = Slot;
	ml_library_load((ml_state_t *)State, NULL, "gir");
}
