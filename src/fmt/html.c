#include <minilang/ml_library.h>
#include <minilang/ml_macros.h>
#include <minilang/ml_xml.h>
#include <gumbo.h>

#undef ML_CATEGORY
#define ML_CATEGORY "fmt/gumbo"

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
		ml_value_t *Attributes = ml_xml_element_attributes((ml_value_t *)Child);
		for (int I = 0; I < Node->v.element.attributes.length; ++I) {
			GumboAttribute *Attribute = (GumboAttribute *)Node->v.element.attributes.data[I];
			ml_map_insert(Attributes,
				ml_string(GC_strdup(Attribute->name), -1),
				ml_string(GC_strdup(Attribute->value), -1)
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
			ml_value_t *ChildAttrs = ml_xml_element_attributes((ml_value_t *)Child);
			ml_map_insert(ChildAttrs,
				ml_cstring("doctype"),
				ml_string(GC_strdup(Node->v.document.name), -1)
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

ML_FUNCTION(Parse) {
	ML_CHECK_ARG_COUNT(1);
	ML_CHECK_ARG_TYPE(0, MLStringT);
	GumboOutput *Output = gumbo_parse(ml_string_value(Args[0]));
	ml_xml_element_t *Xml = ml_xml_element("html");
	for (int I = 0; I < Output->root->v.element.children.length; ++I) {
		convert_to_xml(Xml, (GumboNode *)Output->root->v.element.children.data[I]);
	}
	gumbo_destroy_output(&kGumboDefaultOptions, Output);
	return (ml_value_t *)Xml;
}

void ml_library_entry0(ml_value_t **Slot) {
#include "html_init.c"
	Slot[0] = ml_module("html",
		"parse", Parse,
	NULL);
}
