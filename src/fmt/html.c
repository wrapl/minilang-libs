#include <minilang/ml_library.h>
#include <minilang/ml_macros.h>
#include <string.h>
#include <stdio.h>
#include <lexbor/html/parser.h>
#include <lexbor/html/serialize.h>
#include <lexbor/css/parser.h>
#include <lexbor/dom/interfaces/element.h>
#include <lexbor/selectors/selectors.h>

static lxb_status_t serialize_fn(const lxb_char_t *Data, size_t Length, ml_stringbuffer_t *Buffer) {
	ml_stringbuffer_write(Buffer, (const char *)Data, Length);
	return LXB_STATUS_OK;
}

typedef struct {
	ml_type_t *Type;
	lxb_dom_node_t *Handle;
} node_t;

ml_value_t *node(void *Handle);

ML_TYPE(NodeT, (), "node");

ML_METHOD("name", NodeT) {
	node_t *Node = (node_t *)Args[0];
	size_t Length;
	const lxb_char_t *Name = lxb_dom_node_name(Node->Handle, &Length);
	return ml_string((const char *)Name, Length);
}

ML_METHOD("parent", NodeT) {
	node_t *Node = (node_t *)Args[0];
	return node(lxb_dom_node_parent(Node->Handle));
}

ML_METHOD("text", NodeT) {
	node_t *Node = (node_t *)Args[0];
	size_t Length;
	const lxb_char_t *Text = lxb_dom_node_text_content(Node->Handle, &Length);
	return ml_string((const char *)Text, Length);
}

ML_METHOD("append", MLStringBufferT, NodeT) {
	ml_stringbuffer_t *Buffer = (ml_stringbuffer_t *)Args[0];
	node_t *Node = (node_t *)Args[1];
	lxb_html_serialize_cb(Node->Handle, (void *)serialize_fn, Buffer);
	return Args[0];
}

typedef struct {
	ml_type_t *Type;
	lxb_dom_node_t *Head;
} node_list_t;

ML_TYPE(NodeListT, (MLSequenceT), "node::list");

ML_METHOD("children", NodeT) {
	node_t *Node = (node_t *)Args[0];
	node_list_t *List = new(node_list_t);
	List->Type = NodeListT;
	List->Head = lxb_dom_node_first_child(Node->Handle);
	return (ml_value_t *)List;
}

typedef struct {
	ml_type_t *Type;
	lxb_dom_node_t *Current;
	int Index;
} node_iter_t;

ML_TYPE(NodeIterT, (), "node::iterator");

static void ML_TYPED_FN(ml_iterate, NodeListT, ml_state_t *Caller, node_list_t *List) {
	if (!List->Head) ML_RETURN(MLNil);
	node_iter_t *Iter = new(node_iter_t);
	Iter->Type = NodeIterT;
	Iter->Current = List->Head;
	Iter->Index = 1;
	ML_RETURN(Iter);
}

static void ML_TYPED_FN(ml_iter_next, NodeIterT, ml_state_t *Caller, node_iter_t *Iter) {
	lxb_dom_node_t *Next = lxb_dom_node_next(Iter->Current);
	if (!Next) ML_RETURN(MLNil);
	Iter->Current = Next;
	++Iter->Index;
	ML_RETURN(Iter);
}

static void ML_TYPED_FN(ml_iter_key, NodeIterT, ml_state_t *Caller, node_iter_t *Iter) {
	ML_RETURN(ml_integer(Iter->Index));
}

static void ML_TYPED_FN(ml_iter_value, NodeIterT, ml_state_t *Caller, node_iter_t *Iter) {
	ML_RETURN(node(Iter->Current));
}

typedef struct {
	ml_type_t *Type;
	lxb_css_selector_list_t *Handle;
} css_selectors_t;

ML_TYPE(CSSSelectorsT, (), "css-selectors");

ML_METHOD(CSSSelectorsT, MLStringT) {
	lxb_css_parser_t Parser[1] = {{0,}};
	lxb_css_parser_init(Parser, NULL, NULL);
	css_selectors_t *List = new(css_selectors_t);
	List->Type = CSSSelectorsT;
	List->Handle = lxb_css_selectors_parse(Parser, (const unsigned char *)ml_string_value(Args[0]), ml_string_length(Args[0]));
	if (Parser->status != LXB_STATUS_OK) {
		lxb_css_parser_destroy(Parser, NULL);
		return ml_error("ParseError", "Error parsing CSS selectors");
	}
	lxb_css_parser_destroy(Parser, NULL);
	return (ml_value_t *)List;
}

ML_METHOD("append", MLStringBufferT, CSSSelectorsT) {
	ml_stringbuffer_t *Buffer = (ml_stringbuffer_t *)Args[0];
	css_selectors_t *List = (css_selectors_t *)Args[1];
	lxb_css_selector_serialize_list_chain(List->Handle, (void *)serialize_fn, Buffer);
	return Args[0];
}

static lxb_status_t selector_fn(lxb_dom_node_t *Handle, lxb_css_selector_specificity_t *Spec, ml_value_t *Result) {
	ml_list_put(Result, node(Handle));
	return LXB_STATUS_OK;
}

ML_METHOD("%", NodeT, CSSSelectorsT) {
	node_t *Node = (node_t *)Args[0];
	css_selectors_t *List = (css_selectors_t *)Args[1];
	lxb_selectors_t Selectors[1] = {{0,}};
	lxb_selectors_init(Selectors);
	ml_value_t *Result = ml_list();
	lxb_selectors_find(Selectors, Node->Handle, List->Handle, (void *)selector_fn, Result);
	return Result;
}

ML_TYPE(ElementT, (NodeT), "element");

ML_METHOD("value", ElementT) {
	node_t *Node = (node_t *)Args[0];
	lexbor_str_t *IsValue = ((lxb_dom_element_t *)Node->Handle)->is_value;
	if (!IsValue) return MLNil;
	return ml_string((const char *)IsValue->data, IsValue->length);
}

typedef struct {
	ml_type_t *Type;
	lxb_dom_element_t *Element;
	const lxb_char_t *Name;
	size_t Length;
} attribute_t;

static ml_value_t *attribute_deref(attribute_t *Attribute) {
	size_t Length;
	const lxb_char_t *Text = lxb_dom_element_get_attribute(Attribute->Element,
		Attribute->Name, Attribute->Length, &Length
	);
	return ml_string((const char *)Text, Length);
}

static void attribute_assign(ml_state_t *Caller, attribute_t *Attribute, ml_value_t *Value) {
	if (!ml_is(Value, MLStringT)) ML_ERROR("TypeError", "Attribute value must be string");
	lxb_dom_element_set_attribute(Attribute->Element,
		Attribute->Name, Attribute->Length,
		(const unsigned char *)ml_string_value(Value), ml_string_length(Value)
	);
	ML_RETURN(Value);
}

ML_TYPE(AttributeT, (), "attribute",
	.deref = (void *)attribute_deref,
	.assign = (void *)attribute_assign
);

ML_METHOD("[]", ElementT, MLStringT) {
	node_t *Node = (node_t *)Args[0];
	attribute_t *Attribute = new(attribute_t);
	Attribute->Type = AttributeT;
	Attribute->Element = (lxb_dom_element_t *)Node->Handle;
	Attribute->Name = (const unsigned char *)ml_string_value(Args[1]);
	Attribute->Length = ml_string_length(Args[1]);
	return (ml_value_t *)Attribute;
}

typedef struct {
	ml_type_t *Type;
	lxb_dom_attr_t *Head;
} attribute_list_t;

ML_TYPE(AttrListT, (MLSequenceT), "attribute::list");

ML_METHOD("attributes", ElementT) {
	node_t *Node = (node_t *)Args[0];
	attribute_list_t *List = new(attribute_list_t);
	List->Type = AttrListT;
	List->Head = lxb_dom_element_first_attribute((lxb_dom_element_t *)Node->Handle);
	return (ml_value_t *)List;
}

typedef struct {
	ml_type_t *Type;
	lxb_dom_attr_t *Current;
	int Index;
} attribute_iter_t;

ML_TYPE(AttrIterT, (), "attribute::iterator");

static void ML_TYPED_FN(ml_iterate, AttrListT, ml_state_t *Caller, attribute_list_t *List) {
	if (!List->Head) ML_RETURN(MLNil);
	attribute_iter_t *Iter = new(attribute_iter_t);
	Iter->Type = AttrIterT;
	Iter->Current = List->Head;
	Iter->Index = 1;
	ML_RETURN(Iter);
}

static void ML_TYPED_FN(ml_iter_next, AttrIterT, ml_state_t *Caller, attribute_iter_t *Iter) {
	lxb_dom_attr_t *Next = lxb_dom_element_next_attribute(Iter->Current);
	if (!Next) ML_RETURN(MLNil);
	Iter->Current = Next;
	++Iter->Index;
	ML_RETURN(Iter);
}

static void ML_TYPED_FN(ml_iter_key, AttrIterT, ml_state_t *Caller, attribute_iter_t *Iter) {
	size_t Length;
	const lxb_char_t *Text = lxb_dom_attr_local_name(Iter->Current, &Length);
	ML_RETURN(ml_string((const char *)Text, Length));
}

static void ML_TYPED_FN(ml_iter_value, AttrIterT, ml_state_t *Caller, attribute_iter_t *Iter) {
	size_t Length;
	const lxb_char_t *Text = lxb_dom_attr_value(Iter->Current, &Length);
	ML_RETURN(ml_string((const char *)Text, Length));
}

typedef struct {
	ml_type_t *Type;
	lxb_html_document_t *Handle;
} document_t;

ML_TYPE(DocumentT, (NodeT), "document");

ML_METHOD(DocumentT, MLStringT) {
	lxb_html_document_t *Handle = lxb_html_document_create();
	lxb_status_t Status = lxb_html_document_parse(Handle,
		(const unsigned char *)ml_string_value(Args[0]),
		ml_string_length(Args[0])
	);
	if (Status != LXB_STATUS_OK) return ml_error("HTMLError", "Error parsing HTML");
	return node(Handle);
}

ML_METHOD("head", DocumentT) {
	document_t *Document = (document_t *)Args[0];
	return node(lxb_html_document_head_element(Document->Handle));
}

ML_METHOD("body", DocumentT) {
	document_t *Document = (document_t *)Args[0];
	return node(lxb_html_document_body_element(Document->Handle));
}

ml_value_t *node(void *Handle) {
	ml_type_t *Type;
	switch (((lxb_dom_node_t *)Handle)->type) {
	case LXB_DOM_NODE_TYPE_ELEMENT:
		Type = ElementT;
		break;
	case LXB_DOM_NODE_TYPE_DOCUMENT:
		Type = DocumentT;
		break;
	default:
		Type = NodeT;
		break;
	}
	node_t *Node = new(node_t);
	Node->Type = Type;
	Node->Handle = Handle;
	return (ml_value_t *)Node;
}

void ml_library_entry0(ml_value_t **Slot) {
#include "html_init.c"
	Slot[0] = ml_module("html",
		"node", NodeT,
		"css_selectors", CSSSelectorsT,
		"element", ElementT,
		"document", DocumentT,
	NULL);
}
