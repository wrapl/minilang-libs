#include <minilang/ml_library.h>
#include <minilang/ml_macros.h>
#include <minilang/ml_object.h>
#include <minilang/ml_xml.h>
#include "md4c.c"

#undef ML_CATEGORY
#define ML_CATEGORY "fmt/markdown"

static const char *BlockTags[] = {
	[MD_BLOCK_DOC] = "body",
    [MD_BLOCK_QUOTE] = "blockquote",
    [MD_BLOCK_UL] = "ul",
    [MD_BLOCK_OL] = "ol",
    [MD_BLOCK_LI] = "li",
    [MD_BLOCK_HR] = "hr",
    [MD_BLOCK_H] = "h",
    [MD_BLOCK_CODE] = "pre",
    [MD_BLOCK_HTML] = "div",
    [MD_BLOCK_P] = "p",
    [MD_BLOCK_TABLE] = "table",
    [MD_BLOCK_THEAD] = "thead",
    [MD_BLOCK_TBODY] = "tbody",
    [MD_BLOCK_TR] = "tr",
    [MD_BLOCK_TH] = "th",
    [MD_BLOCK_TD] = "td"
};

static const char *SpanTags[] = {
	[MD_SPAN_EM] = "em",
	[MD_SPAN_STRONG] = "strong",
	[MD_SPAN_A] = "a",
	[MD_SPAN_IMG] = "img",
	[MD_SPAN_CODE] = "code",
	[MD_SPAN_DEL] = "s",
	[MD_SPAN_LATEXMATH] = "span",
	[MD_SPAN_LATEXMATH_DISPLAY] = "span",
	[MD_SPAN_WIKILINK] = "a",
	[MD_SPAN_U] = "u"
};

typedef struct {
	ml_xml_element_t *Node;
	ml_stringbuffer_t Buffer[1];
} xml_builder_t;

static int enter_block(MD_BLOCKTYPE Type, void *Detail0, xml_builder_t *Builder) {
	if (Builder->Buffer->Length) {
		size_t Length = Builder->Buffer->Length;
		ml_xml_element_put(Builder->Node, ml_xml_text(ml_stringbuffer_get_string(Builder->Buffer), Length));
	}
	switch (Type) {
	case MD_BLOCK_DOC:
	case MD_BLOCK_QUOTE:
	case MD_BLOCK_P:
	case MD_BLOCK_HTML:
	case MD_BLOCK_HR:
	case MD_BLOCK_TR: {
		ml_xml_element_t *Child = ml_xml_element(BlockTags[Type]);
		ml_xml_element_put(Builder->Node, (ml_xml_node_t *)Child);
		Builder->Node = Child;
		break;
	}
	case MD_BLOCK_UL: {
		ml_xml_element_t *Child = ml_xml_element(BlockTags[Type]);
		ml_xml_element_put(Builder->Node, (ml_xml_node_t *)Child);
		Builder->Node = Child;
		break;
	}
	case MD_BLOCK_OL: {
		ml_xml_element_t *Child = ml_xml_element(BlockTags[Type]);
		ml_xml_element_put(Builder->Node, (ml_xml_node_t *)Child);
		Builder->Node = Child;
		break;
	}
	case MD_BLOCK_LI: {
		MD_BLOCK_LI_DETAIL *Detail = (MD_BLOCK_LI_DETAIL *)Detail0;
		ml_xml_element_t *Child = ml_xml_element(BlockTags[Type]);
		if (Detail->is_task) {
			ml_xml_element_t *Checkbox = ml_xml_element("input");
			ml_map_insert(ml_xml_element_attributes(Checkbox), ml_cstring("type"), ml_cstring("checkbox"));
			if (Detail->task_mark != ' ') {
				ml_map_insert(ml_xml_element_attributes(Checkbox), ml_cstring("checked"), ml_cstring("true"));
			}
		}
		ml_xml_element_put(Builder->Node, (ml_xml_node_t *)Child);
		Builder->Node = Child;
		break;
	}
	case MD_BLOCK_H: {
		MD_BLOCK_H_DETAIL *Detail = (MD_BLOCK_H_DETAIL *)Detail0;
		ml_xml_element_t *Child;
		switch (Detail->level) {
		case 1: Child = ml_xml_element("h1"); break;
		case 2: Child = ml_xml_element("h2"); break;
		case 3: Child = ml_xml_element("h3"); break;
		case 4: Child = ml_xml_element("h4"); break;
		case 5: Child = ml_xml_element("h5"); break;
		default: Child = ml_xml_element("h6"); break;
		}
		ml_xml_element_put(Builder->Node, (ml_xml_node_t *)Child);
		Builder->Node = Child;
		break;
	}
	case MD_BLOCK_CODE: {
		ml_xml_element_t *Child = ml_xml_element(BlockTags[Type]);
		ml_xml_element_put(Builder->Node, (ml_xml_node_t *)Child);
		Builder->Node = Child;
		break;
	}
	case MD_BLOCK_TABLE: {
		ml_xml_element_t *Child = ml_xml_element(BlockTags[Type]);
		ml_xml_element_put(Builder->Node, (ml_xml_node_t *)Child);
		Builder->Node = Child;
		break;
	}
	case MD_BLOCK_THEAD:
	case MD_BLOCK_TBODY: {
		ml_xml_element_t *Child = ml_xml_element(BlockTags[Type]);
		ml_xml_element_put(Builder->Node, (ml_xml_node_t *)Child);
		Builder->Node = Child;
		break;
	}
	case MD_BLOCK_TH:
	case MD_BLOCK_TD: {
		ml_xml_element_t *Child = ml_xml_element(BlockTags[Type]);
		ml_xml_element_put(Builder->Node, (ml_xml_node_t *)Child);
		Builder->Node = Child;
		break;
	}
	}
	return 0;
}

static int leave_block(MD_BLOCKTYPE Type, void *Detail0, xml_builder_t *Builder) {
	if (Builder->Buffer->Length) {
		size_t Length = Builder->Buffer->Length;
		ml_xml_element_put(Builder->Node, ml_xml_text(ml_stringbuffer_get_string(Builder->Buffer), Length));
	}
	Builder->Node = ml_xml_node_parent((ml_xml_node_t *)Builder->Node);
	return 0;
}

static int enter_span(MD_SPANTYPE Type, void *Detail0, xml_builder_t *Builder) {
	if (Builder->Buffer->Length) {
		size_t Length = Builder->Buffer->Length;
		ml_xml_element_put(Builder->Node, ml_xml_text(ml_stringbuffer_get_string(Builder->Buffer), Length));
	}
	switch (Type) {
	case MD_SPAN_EM:
	case MD_SPAN_STRONG:
	case MD_SPAN_CODE:
	case MD_SPAN_DEL:
	case MD_SPAN_LATEXMATH:
	case MD_SPAN_LATEXMATH_DISPLAY:
	case MD_SPAN_WIKILINK:
	case MD_SPAN_U: {
		ml_xml_element_t *Child = ml_xml_element(SpanTags[Type]);
		ml_xml_element_put(Builder->Node, (ml_xml_node_t *)Child);
		Builder->Node = Child;
		break;
	}
	case MD_SPAN_A: {
		MD_SPAN_A_DETAIL *Detail = (MD_SPAN_A_DETAIL *)Detail0;
		ml_xml_element_t *Child = ml_xml_element(SpanTags[Type]);
		ml_value_t *Attributes = ml_xml_element_attributes(Child);
		ml_map_insert(Attributes, ml_cstring("href"), ml_string_copy(Detail->href.text, Detail->href.size));
		ml_map_insert(Attributes, ml_cstring("title"), ml_string_copy(Detail->title.text, Detail->title.size));
		ml_xml_element_put(Builder->Node, (ml_xml_node_t *)Child);
		Builder->Node = Child;
		break;
	}
	case MD_SPAN_IMG: {
		MD_SPAN_IMG_DETAIL *Detail = (MD_SPAN_IMG_DETAIL *)Detail0;
		ml_xml_element_t *Child = ml_xml_element(SpanTags[Type]);
		ml_value_t *Attributes = ml_xml_element_attributes(Child);
		ml_map_insert(Attributes, ml_cstring("src"), ml_string_copy(Detail->src.text, Detail->src.size));
		ml_map_insert(Attributes, ml_cstring("title"), ml_string_copy(Detail->title.text, Detail->title.size));
		ml_xml_element_put(Builder->Node, (ml_xml_node_t *)Child);
		Builder->Node = Child;
		break;
	}
	}
	return 0;
}

static int leave_span(MD_SPANTYPE Type, void *Detail0, xml_builder_t *Builder) {
	if (Builder->Buffer->Length) {
		size_t Length = Builder->Buffer->Length;
		ml_xml_element_put(Builder->Node, ml_xml_text(ml_stringbuffer_get_string(Builder->Buffer), Length));
	}
	Builder->Node = ml_xml_node_parent((ml_xml_node_t *)Builder->Node);
	return 0;
}

#include "entities.c"

const unsigned char *html_entity(const char *Value, int Length) {
	const struct entity_t *Entity = entity_lookup(Value, Length);
	return Entity ? Entity->Chars : NULL;
}

static int text(MD_TEXTTYPE Type, const MD_CHAR *Text, MD_SIZE Size, xml_builder_t *Builder) {
	switch (Type) {
	case MD_TEXT_NORMAL: {
		ml_stringbuffer_write(Builder->Buffer, Text, Size);
		break;
	}
	case MD_TEXT_NULLCHAR: {
		ml_stringbuffer_write(Builder->Buffer, "\uFFFD", strlen("\uFFFD"));
		break;
	}
	case MD_TEXT_BR: {
		if (Builder->Buffer->Length) {
			size_t Length = Builder->Buffer->Length;
			ml_xml_element_put(Builder->Node, ml_xml_text(ml_stringbuffer_get_string(Builder->Buffer), Length));
		}
		ml_xml_element_put(Builder->Node, (ml_xml_node_t *)ml_xml_element("br"));
		break;
	}
	case MD_TEXT_SOFTBR: {
		ml_stringbuffer_write(Builder->Buffer, "\n", strlen("\n"));
		break;
	}
	case MD_TEXT_ENTITY: {
		const char *Chars = Size > 1 ? (char *)html_entity(Text + 1, Size - 1) : NULL;
		if (Chars) {
			ml_stringbuffer_write(Builder->Buffer, Chars, strlen(Chars));
		} else {
			ml_stringbuffer_write(Builder->Buffer, Text, Size);
		}
		break;
	}
	case MD_TEXT_CODE: {
		ml_stringbuffer_write(Builder->Buffer, Text, Size);
		break;
	}
	case MD_TEXT_HTML: {
		ml_stringbuffer_write(Builder->Buffer, Text, Size);
		break;
	}
	case MD_TEXT_LATEXMATH: {
		ml_stringbuffer_write(Builder->Buffer, Text, Size);
		break;
	}
	}
	return 0;
}

ML_FLAGS2(FlagT, "markdown::flag",
	"CollapseWhitespace", MD_FLAG_COLLAPSEWHITESPACE,
	"PermissiveATXHeaders", MD_FLAG_PERMISSIVEATXHEADERS,
	"PermissiveURLAutoLinks", MD_FLAG_PERMISSIVEURLAUTOLINKS,
	"PermissiveEmailAutoLinks", MD_FLAG_PERMISSIVEEMAILAUTOLINKS,
	"NoIndentedCodeBlocks", MD_FLAG_NOINDENTEDCODEBLOCKS,
	"NoHTMLBlocks", MD_FLAG_NOHTMLBLOCKS,
	"NoHTMLSpans", MD_FLAG_NOHTMLSPANS,
	"Tables", MD_FLAG_TABLES,
	"StrikeThrough", MD_FLAG_STRIKETHROUGH,
	"PermissiveWWWAutoLinks", MD_FLAG_PERMISSIVEWWWAUTOLINKS,
	"TaskLists", MD_FLAG_TASKLISTS,
	"LaTeXMathSpans", MD_FLAG_LATEXMATHSPANS,
	"WikiLinks", MD_FLAG_WIKILINKS,
	"Underline", MD_FLAG_UNDERLINE,
	"HardSoftBreaks", MD_FLAG_HARD_SOFT_BREAKS
);

ML_METHOD_ANON(Parse, "markdown::parse");

ML_METHOD(Parse, MLStringT, FlagT) {
//<Markdown
//<Flags
//>xml
	MD_PARSER Parser[1] = {0,};
	Parser->flags = ml_flags_value_value(Args[1]);
	Parser->enter_block = (void *)enter_block;
	Parser->leave_block = (void *)leave_block;
	Parser->enter_span = (void *)enter_span;
	Parser->leave_span = (void *)leave_span;
	Parser->text = (void *)text;
	ml_xml_element_t *Root = ml_xml_element("html");
	xml_builder_t Builder[1] = {Root, {ML_STRINGBUFFER_INIT}};
	if (md_parse(ml_string_value(Args[0]), ml_string_length(Args[0]), Parser, &Builder)) {
		return ml_error("MarkdownError", "Error parsing markdown");
	}
	return (ml_value_t *)Root;
}

ML_METHOD(Parse, MLStringT) {
//<Markdown
//>xml
	MD_PARSER Parser[1] = {0,};
	Parser->flags = MD_FLAG_NOHTML;
	Parser->enter_block = (void *)enter_block;
	Parser->leave_block = (void *)leave_block;
	Parser->enter_span = (void *)enter_span;
	Parser->leave_span = (void *)leave_span;
	Parser->text = (void *)text;
	ml_xml_element_t *Root = ml_xml_element("html");
	xml_builder_t Builder[1] = {Root, {ML_STRINGBUFFER_INIT}};
	if (md_parse(ml_string_value(Args[0]), ml_string_length(Args[0]), Parser, &Builder)) {
		return ml_error("MarkdownError", "Error parsing markdown");
	}
	return (ml_value_t *)Root;
}

ML_LIBRARY_ENTRY0(fmt_markdown) {
#include "markdown_init.c"
	Slot[0] = ml_module("markdown",
		"parse", Parse,
		"flag", FlagT,
	NULL);
}
