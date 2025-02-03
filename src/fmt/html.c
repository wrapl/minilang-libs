#include <minilang/ml_library.h>
#include <minilang/ml_macros.h>
#include <minilang/ml_xml.h>
#include <minilang/ml_stream.h>
#include <gumbo.h>

#undef ML_CATEGORY
#define ML_CATEGORY "fmt/html"

static void convert_to_xml(ml_xml_element_t *Parent, GumboNode *Node) {
	switch (Node->type) {
	case GUMBO_NODE_TEXT:
	case GUMBO_NODE_CDATA:
	case GUMBO_NODE_WHITESPACE: {
		ml_xml_node_t *Child = ml_xml_text(GC_strdup(Node->v.text.text), -1);
		ml_xml_element_put(Parent, Child);
		break;
	}
	case GUMBO_NODE_ELEMENT: {
		ml_xml_element_t *Child = ml_xml_element(gumbo_normalized_tagname(Node->v.element.tag));
		ml_value_t *Attributes = ml_xml_element_attributes(Child);
		for (int I = 0; I < Node->v.element.attributes.length; ++I) {
			GumboAttribute *Attribute = (GumboAttribute *)Node->v.element.attributes.data[I];
			ml_map_insert(Attributes,
				ml_string_unchecked(GC_strdup(Attribute->name), -1),
				ml_string_unchecked(GC_strdup(Attribute->value), -1)
			);
		}
		for (int I = 0; I < Node->v.element.children.length; ++I) {
			convert_to_xml(Child, (GumboNode *)Node->v.element.children.data[I]);
		}
		ml_xml_element_put(Parent, (ml_xml_node_t *)Child);
		break;
	}
	case GUMBO_NODE_DOCUMENT: {
		ml_xml_element_t *Child = ml_xml_element("html");
		if (Node->v.document.has_doctype) {
			ml_value_t *ChildAttrs = ml_xml_element_attributes(Child);
			ml_map_insert(ChildAttrs,
				ml_cstring("doctype"),
				ml_string_unchecked(GC_strdup(Node->v.document.name), -1)
			);
		}
		for (int I = 0; I < Node->v.document.children.length; ++I) {
			convert_to_xml(Child, (GumboNode *)Node->v.document.children.data[I]);
		}
		ml_xml_element_put(Parent, (ml_xml_node_t *)Child);
		break;
	}
	default: break;
	}
}

ML_METHOD_ANON(Parse, "html::parse");

static GumboOptions Options;

ML_METHOD(Parse, MLStringT) {
//<Html
//>xml
// Parses :mini:`Html` as a html string and returns an :mini:`xml` version of the same content.
	GumboOutput *Output = gumbo_parse_with_options(&Options, ml_string_value(Args[0]), ml_string_length(Args[0]));
	ml_xml_element_t *Xml = ml_xml_element("html");
	for (int I = 0; I < Output->root->v.element.children.length; ++I) {
		convert_to_xml(Xml, (GumboNode *)Output->root->v.element.children.data[I]);
	}
	gumbo_destroy_output(&Options, Output);
	return (ml_value_t *)Xml;
}

static void *allocator(void *Data, size_t Size) {
	return GC_malloc(Size);
}

static void deallocator(void *Data, void *Ptr) {}

ML_LIBRARY_ENTRY0(fmt_html) {
#include "html_init.c"
	Options = kGumboDefaultOptions;
	Options.allocator = allocator;
	Options.deallocator = deallocator;
	Slot[0] = ml_callable_module("html", Parse,
		"parse", Parse,
	NULL);
}
