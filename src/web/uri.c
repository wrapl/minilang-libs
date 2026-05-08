#include <minilang/ml_library.h>
#include <minilang/ml_macros.h>
#include <minilang/ml_object.h>
#include <uriparser/Uri.h>

#undef ML_CATEGORY
#define ML_CATEGORY "web/uri"

typedef struct {
	ml_type_t *Type;
	UriUriA Value;
} uri_t;

ML_TYPE(UriT, (), "uri");

ML_METHOD(UriT) {
	uri_t *Uri = new(uri_t);
	Uri->Type = UriT;
	return (ml_value_t *)Uri;
}

static void *uri_malloc(UriMemoryManager *MM, size_t Size) {
	return GC_malloc(Size);
}

static void *uri_calloc(UriMemoryManager *MM, size_t Size, size_t Count) {
	return GC_malloc(Size * Count);
}

static void *uri_realloc(UriMemoryManager *MM, void *Ptr, size_t Size) {
	return GC_realloc(Ptr, Size);
}

static void *uri_reallocarray(UriMemoryManager *MM, void *Ptr, size_t Size, size_t Count) {
	return GC_realloc(Ptr, Size * Count);
}

static void uri_free(UriMemoryManager *MM, void *Ptr) {
}

static UriMemoryManager MM[1] = {{
	uri_malloc,
	uri_calloc,
	uri_realloc,
	uri_reallocarray,
	uri_free,
	NULL
}};

ML_METHOD(UriT, MLStringT) {
	uri_t *Uri = new(uri_t);
	const char *String = ml_string_value(Args[0]);
	size_t Length = ml_string_length(Args[0]);
	const char *ErrorPos;
	if (uriParseSingleUriExMmA(&Uri->Value, String, String + Length, &ErrorPos, MM) != URI_SUCCESS) {
		return ml_error("ParseError", "Error parsing URI at %s", ErrorPos);
	}
	Uri->Type = UriT;
	return (ml_value_t *)Uri;
}

#define URI_TEXT_FIELD(NAME, FIELD) \
\
ML_METHOD(#NAME, UriT) { \
	uri_t *Uri = (uri_t *)Args[0]; \
	const char *First = Uri->Value.FIELD.first; \
	if (First) { \
		return ml_string(First, Uri->Value.FIELD.afterLast - First); \
	} else { \
		return MLNil; \
	} \
}

URI_TEXT_FIELD(scheme, scheme)
URI_TEXT_FIELD(user, userInfo)
URI_TEXT_FIELD(host, hostText)
URI_TEXT_FIELD(port, portText)
URI_TEXT_FIELD(query, query)
URI_TEXT_FIELD(fragment, fragment)

typedef struct {
	ml_type_t *Type;
	unsigned char Value[4];
} ipv4_t;

ML_TYPE(IPv4T, (), "ipv4");

typedef struct {
	ml_type_t *Type;
	unsigned char Value[16];
} ipv6_t;

ML_TYPE(IPv6T, (), "ipv6");

ML_METHOD("ip", UriT) {
	uri_t *Uri = (uri_t *)Args[0];
	UriIp4 *Ip4 = Uri->Value.hostData.ip4;
	UriIp6 *Ip6 = Uri->Value.hostData.ip6;
	if (Ip4) {
		ipv4_t *Ip = new(ipv4_t);
		Ip->Type = IPv4T;
		memcpy(Ip->Value, Ip4->data, 4);
		return (ml_value_t *)Ip;
	}
	if (Ip6) {
		ipv6_t *Ip = new(ipv6_t);
		Ip->Type = IPv6T;
		memcpy(Ip->Value, Ip6->data, 16);
		return (ml_value_t *)Ip;
	}
	return MLNil;
}

ML_METHOD("path", UriT) {
	uri_t *Uri = (uri_t *)Args[0];
	ml_value_t *Path = ml_list();
	for (UriPathSegmentA *Segment = Uri->Value.pathHead; Segment; Segment = Segment->next) {
		const char *First = Segment->text.first;
		ml_list_put(Path, ml_string(First, Segment->text.afterLast - First));
	}
	return Path;
}

typedef struct {
	ml_type_t *Type;
	UriQueryListA *Value;
	int Count;
} query_t;

ML_TYPE(QueryT, (MLSequenceT), "query");

ML_METHOD(QueryT, MLStringT) {
	query_t *Query = new(query_t);
	const char *String = ml_string_value(Args[0]);
	size_t Length = ml_string_length(Args[0]);
	if (uriDissectQueryMallocExMmA(&Query->Value, &Query->Count, String, String + Length, 1, URI_BR_DONT_TOUCH, MM) != URI_SUCCESS) {
		return ml_error("ParseError", "Error parsing query string");
	}
	Query->Type = QueryT;
	return (ml_value_t *)Query;
}

static void ML_TYPED_FN(ml_iterate, QueryT, ml_state_t *Caller, query_t *Query) {
	if (!Query->Value) ML_RETURN(MLNil);
	ML_RETURN(Query);
}

static void ML_TYPED_FN(ml_iter_next, QueryT, ml_state_t *Caller, query_t *Query) {
	if (!Query->Value) ML_RETURN(MLNil);
	UriQueryListA *Next = Query->Value->next;
	if (!Next) ML_RETURN(MLNil);
	Query = new(query_t);
	Query->Type = QueryT;
	Query->Value = Next;
	ML_RETURN(Query);
}

static void ML_TYPED_FN(ml_iter_key, QueryT, ml_state_t *Caller, query_t *Query) {
	if (Query->Value->key) ML_RETURN(ml_string(Query->Value->key, -1));
	ML_RETURN(MLNil);
}

static void ML_TYPED_FN(ml_iter_value, QueryT, ml_state_t *Caller, query_t *Query) {
	if (Query->Value->value) ML_RETURN(ml_string(Query->Value->value, -1));
	ML_RETURN(MLNil);
}

ML_LIBRARY_ENTRY0(web_uri) {
#include "uri_init.c"
	stringmap_insert(UriT->Exports, "query", QueryT);
	Slot[0] = (ml_value_t *)UriT;
}
