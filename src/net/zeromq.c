#include <minilang/ml_library.h>
#include <minilang/ml_macros.h>
#include <minilang/ml_object.h>
#include <czmq.h>

#undef ML_CATEGORY
#define ML_CATEGORY "net/zeromq"

typedef struct {
	ml_type_t *Type;
	zsock_t *Handle;
} socket_t;

static void socket_finalize(socket_t *Socket, void *Data) {
	zsock_destroy(&Socket->Handle);
}

ML_TYPE(SocketT, (), "zeromq::socket");
// ZeroMQ socket.

ML_ENUM2(SocketTypeT, "zeromq::socket::type",
// ZeroMQ socket type.
	"Pair", ZMQ_PAIR,
	"Pub", ZMQ_PUB,
	"Sub", ZMQ_SUB,
	"Req", ZMQ_REQ,
	"Rep", ZMQ_REP,
	"Dealer", ZMQ_DEALER,
	"Router", ZMQ_ROUTER,
	"Pull", ZMQ_PULL,
	"Push", ZMQ_PUSH,
	"XPub", ZMQ_XPUB,
	"XSub", ZMQ_XSUB,
	"Stream", ZMQ_STREAM
);

ML_METHOD(SocketT, SocketTypeT) {
//<Type
//>socket
// Returns a new socket of the specified type.
	socket_t *Socket = new(socket_t);
	Socket->Type = SocketT;
	Socket->Handle = zsock_new(ml_enum_value_value(Args[0]));
	GC_register_finalizer(Socket, (GC_finalization_proc)socket_finalize, NULL, NULL, NULL);
	return (ml_value_t *)Socket;
}

ML_METHOD("destroy", SocketT) {
	socket_t *Socket = (socket_t *)Args[0];
	zsock_destroy(&Socket->Handle);
	return MLNil;
}

ML_METHOD("bind", SocketT, MLStringT) {
	socket_t *Socket = (socket_t *)Args[0];
	int Port = zsock_bind(Socket->Handle, "%s", ml_string_value(Args[1]));
	if (Port < 0) return ml_error("ZeroMQError", "Error binding socket");
	return ml_integer(Port);
}

ML_METHOD("unbind", SocketT, MLStringT) {
	socket_t *Socket = (socket_t *)Args[0];
	if (zsock_unbind(Socket->Handle, "%s", ml_string_value(Args[1])) < 0) {
		return ml_error("ZeroMQError", "Error unbinding socket");
	}
	return (ml_value_t *)Socket;
}

ML_METHOD("endpoint", SocketT) {
	socket_t *Socket = (socket_t *)Args[0];
	const char *Endpoint = zsock_endpoint(Socket->Handle);
	if (!Endpoint) return MLNil;
	return ml_string(Endpoint, -1);
}

ML_METHOD("attach", SocketT, MLStringT, MLBooleanT) {
	socket_t *Socket = (socket_t *)Args[0];
	if (zsock_attach(Socket->Handle, ml_string_value(Args[1]), ml_boolean_value(Args[2])) < 0) {
		return ml_error("ZeroMQError", "Error attaching socket");
	}
	return (ml_value_t *)Socket;
}

ML_METHOD("connect", SocketT, MLStringT) {
	socket_t *Socket = (socket_t *)Args[0];
	int Port = zsock_connect(Socket->Handle, "%s", ml_string_value(Args[1]));
	if (Port < 0) return ml_error("ZeroMQError", "Error connecting socket");
	return ml_integer(Port);
}

ML_METHOD("disconnect", SocketT, MLStringT) {
	socket_t *Socket = (socket_t *)Args[0];
	int Port = zsock_disconnect(Socket->Handle, "%s", ml_string_value(Args[1]));
	if (Port < 0) return ml_error("ZeroMQError", "Error disconnecting socket");
	return ml_integer(Port);
}

ML_METHOD("append", MLStringBufferT, SocketT) {
	ml_stringbuffer_t *Buffer = (ml_stringbuffer_t *)Args[0];
	socket_t *Socket = (socket_t *)Args[1];
	ml_stringbuffer_printf(Buffer, "<%s>", zsock_type_str(Socket->Handle));
	return MLSome;
}

ML_METHOD("signal", SocketT, MLIntegerT) {
	socket_t *Socket = (socket_t *)Args[0];
	zsock_signal(Socket->Handle, ml_integer_value(Args[1]));
	return (ml_value_t *)Socket;
}

ML_METHOD("wait", SocketT) {
	socket_t *Socket = (socket_t *)Args[0];
	return ml_integer(zsock_wait(Socket->Handle));
}

ML_METHOD("flush", SocketT) {
	socket_t *Socket = (socket_t *)Args[0];
	zsock_flush(Socket->Handle);
	return (ml_value_t *)Socket;
}

#define SOCKET_OPTION_INTEGER_GET(NAME) \
\
ML_METHOD(#NAME, SocketT) { \
/*<Socket
//>integer
// Returns the current NAME setting of :mini:`Socket`.
*/ \
	socket_t *Socket = (socket_t *)Args[0]; \
	return ml_integer(zsock_ ## NAME(Socket->Handle)); \
}

#define SOCKET_OPTION_INTEGER_SET(NAME) \
\
ML_METHOD(#NAME, SocketT, MLIntegerT) { \
/*<Socket
//<Integer
// Updates the NAME setting of :mini:`Socket`.
*/ \
	socket_t *Socket = (socket_t *)Args[0]; \
	zsock_set_ ## NAME(Socket->Handle, ml_integer_value(Args[0])); \
	return (ml_value_t *)Socket; \
}

#define SOCKET_OPTION_INTEGER(NAME) \
SOCKET_OPTION_INTEGER_GET(NAME) \
SOCKET_OPTION_INTEGER_SET(NAME)

SOCKET_OPTION_INTEGER(heartbeat_ivl)
SOCKET_OPTION_INTEGER(heartbeat_ttl)
SOCKET_OPTION_INTEGER(heartbeat_timeout)
SOCKET_OPTION_INTEGER(use_fd)
SOCKET_OPTION_INTEGER_SET(xpub_manual)
SOCKET_OPTION_INTEGER_SET(stream_notify)
SOCKET_OPTION_INTEGER(invert_matching)
SOCKET_OPTION_INTEGER_SET(xpub_verboser)
SOCKET_OPTION_INTEGER(connect_timeout)
SOCKET_OPTION_INTEGER(tcp_maxrt)
SOCKET_OPTION_INTEGER(multicast_maxtpdu)
SOCKET_OPTION_INTEGER(vmci_buffer_size)
SOCKET_OPTION_INTEGER(vmci_buffer_min_size)
SOCKET_OPTION_INTEGER(vmci_buffer_max_size)
SOCKET_OPTION_INTEGER(vmci_connect_timeout)
SOCKET_OPTION_INTEGER(tos)
SOCKET_OPTION_INTEGER_SET(router_handover)
SOCKET_OPTION_INTEGER(handshake_ivl)
SOCKET_OPTION_INTEGER_SET(xpub_nodrop)
SOCKET_OPTION_INTEGER_SET(router_mandatory)
SOCKET_OPTION_INTEGER_SET(probe_router)
SOCKET_OPTION_INTEGER_SET(req_relaxed)
SOCKET_OPTION_INTEGER_SET(req_correlate)
SOCKET_OPTION_INTEGER_SET(conflate)
SOCKET_OPTION_INTEGER(plain_server)
SOCKET_OPTION_INTEGER(curve_server)
SOCKET_OPTION_INTEGER(gssapi_server)
SOCKET_OPTION_INTEGER(gssapi_plaintext)
SOCKET_OPTION_INTEGER(ipv6)
SOCKET_OPTION_INTEGER(immediate)
SOCKET_OPTION_INTEGER(sndhwm)
SOCKET_OPTION_INTEGER(rcvhwm)
SOCKET_OPTION_INTEGER(affinity)
SOCKET_OPTION_INTEGER(rate)
SOCKET_OPTION_INTEGER(recovery_ivl)
SOCKET_OPTION_INTEGER(sndbuf)
SOCKET_OPTION_INTEGER(rcvbuf)
SOCKET_OPTION_INTEGER(linger)
SOCKET_OPTION_INTEGER(reconnect_ivl)
SOCKET_OPTION_INTEGER(reconnect_ivl_max)
SOCKET_OPTION_INTEGER(backlog)
SOCKET_OPTION_INTEGER(maxmsgsize)
SOCKET_OPTION_INTEGER(multicast_hops)
SOCKET_OPTION_INTEGER(rcvtimeo)
SOCKET_OPTION_INTEGER(sndtimeo)
SOCKET_OPTION_INTEGER_SET(xpub_verbose)
SOCKET_OPTION_INTEGER(tcp_keepalive)
SOCKET_OPTION_INTEGER(tcp_keepalive_idle)
SOCKET_OPTION_INTEGER(tcp_keepalive_cnt)
SOCKET_OPTION_INTEGER(tcp_keepalive_intvl)
SOCKET_OPTION_INTEGER_GET(rcvmore)
SOCKET_OPTION_INTEGER_GET(fd)
SOCKET_OPTION_INTEGER_GET(events)
SOCKET_OPTION_INTEGER_SET(router_raw)
SOCKET_OPTION_INTEGER(ipv4only)
SOCKET_OPTION_INTEGER_SET(delay_attach_on_connect)

#define SOCKET_OPTION_STRING_GET(NAME) \
\
ML_METHOD(#NAME, SocketT) { \
/*<Socket
//>integer
// Returns the current NAME setting of :mini:`Socket`.
*/ \
	socket_t *Socket = (socket_t *)Args[0]; \
	char *Value = zsock_ ## NAME(Socket->Handle); \
	size_t Length = strlen(Value); \
	char *Copy = snew(Length + 1); \
	strcpy(Copy, Value); \
	zstr_free(&Value); \
	return ml_string(Copy, Length); \
}

#define SOCKET_OPTION_STRING_SET(NAME) \
\
ML_METHOD(#NAME, SocketT, MLStringT) { \
/*<Socket
//<Integer
// Updates the NAME setting of :mini:`Socket`.
*/ \
	socket_t *Socket = (socket_t *)Args[0]; \
	zsock_set_ ## NAME(Socket->Handle, ml_string_value(Args[0])); \
	return (ml_value_t *)Socket; \
}

#define SOCKET_OPTION_STRING(NAME) \
SOCKET_OPTION_STRING_GET(NAME) \
SOCKET_OPTION_STRING_SET(NAME)

SOCKET_OPTION_STRING_SET(xpub_welcome_msg)
SOCKET_OPTION_STRING_SET(connect_rid)
SOCKET_OPTION_STRING(socks_proxy)
SOCKET_OPTION_STRING(zap_domain)
SOCKET_OPTION_STRING(plain_username)
SOCKET_OPTION_STRING(plain_password)
SOCKET_OPTION_STRING(curve_publickey)
SOCKET_OPTION_STRING(curve_secretkey)
SOCKET_OPTION_STRING(gssapi_principal)
SOCKET_OPTION_STRING(gssapi_service_principal)
SOCKET_OPTION_STRING_SET(subscribe)
SOCKET_OPTION_STRING_SET(unsubscribe)
SOCKET_OPTION_STRING(identity)
SOCKET_OPTION_STRING(tcp_accept_filter)

ML_ENUM2(SocketEventT, "zeromq::socket::event",
	"In", ZMQ_POLLIN,
	"Out", ZMQ_POLLOUT,
	"Err", ZMQ_POLLERR,
	"Pri", ZMQ_POLLPRI
);

typedef struct {
	ml_type_t *Type;
	zframe_t *Handle;
} frame_t;

static void frame_finalize(frame_t *Frame, void *Data) {
	zframe_destroy(&Frame->Handle);
}

ML_TYPE(FrameT, (), "zeromq::frame");
// ZeroMQ frame.

ML_METHOD(FrameT, MLAddressT) {
//<Bytes
//>frame
// Returns a new frame with the contents of :mini:`Bytes`.
	frame_t *Frame = new(frame_t);
	Frame->Type = FrameT;
	Frame->Handle = zframe_new(ml_address_value(Args[0]), ml_address_length(Args[0]));
	GC_register_finalizer(Frame, (GC_finalization_proc)frame_finalize, NULL, NULL, NULL);
	return (ml_value_t *)Frame;
}

ML_METHOD("data", FrameT) {
//<Frame
//>string
// Returns the contents of :mini:`Frame`.
	frame_t *Frame = (frame_t *)Args[0];
	size_t Length = zframe_size(Frame->Handle);
	char *Bytes = snew(Length + 1);
	memcpy(Bytes, zframe_data(Frame->Handle), Length);
	Bytes[Length] = 0;
	return ml_string(Bytes, Length);
}

ML_METHOD("append", MLStringBufferT, FrameT) {
	ml_stringbuffer_t *Buffer = (ml_stringbuffer_t *)Args[0];
	frame_t *Frame = (frame_t *)Args[1];
	size_t Length = zframe_size(Frame->Handle);
	ml_stringbuffer_printf(Buffer, " %ld:", Length);
	byte *Bytes = zframe_data(Frame->Handle);
	for (int I = Length; --I >= 0;) ml_stringbuffer_printf(Buffer, "%02x", *Bytes++);
	return MLSome;
}

typedef struct {
	ml_type_t *Type;
	zmsg_t *Handle;
} message_t;

static void message_finalize(message_t *Message, void *Data) {
	zmsg_destroy(&Message->Handle);
}

ML_TYPE(MessageT, (MLSequenceT), "zeromq::message");
// ZeroMQ message.

ML_METHOD(MessageT) {
//>message
// Returns a new empty message.
	message_t *Message = new(message_t);
	Message->Type = MessageT;
	Message->Handle = zmsg_new();
	GC_register_finalizer(Message, (GC_finalization_proc)message_finalize, NULL, NULL, NULL);
	return (ml_value_t *)Message;
}

static ml_value_t *message_add_value(zmsg_t *Handle, ml_value_t *Arg) {
	if (ml_is(Arg, MLAddressT)) {
		zmsg_addmem(Handle, ml_address_value(Arg), ml_address_length(Arg));
	} else if (ml_is(Arg, FrameT)) {
		frame_t *Frame = (frame_t *)Arg;
		zmsg_append(Handle, &Frame->Handle);
	} else if (ml_is(Arg, MessageT)) {
		message_t *SubMessage = (message_t *)Arg;
		zmsg_addmsg(Handle, &SubMessage->Handle);
	} else if (ml_is(Arg, MLListT)) {
		ML_LIST_FOREACH(Arg, Iter) message_add_value(Handle, Iter->Value);
	} else if (Arg == MLNil) {
		zmsg_add(Handle, zframe_new_empty());

	} else {
		return ml_error("ZeroMQError", "Unable to use <%s> in message", ml_typeof(Arg)->Name);
	}
	return NULL;
}

ML_METHODV(MessageT) {
//<Frame/1
//>message
// Returns a new message with the specified content. :mini:`Frame/i` can be bytes (address / string), a frame, another message or :mini:`nil` to add an empty frame.
	message_t *Message = new(message_t);
	Message->Type = MessageT;
	zmsg_t *Handle = Message->Handle = zmsg_new();
	GC_register_finalizer(Message, (GC_finalization_proc)message_finalize, NULL, NULL, NULL);
	for (int I = 0; I < Count; ++I) message_add_value(Handle, Args[I]);
	return (ml_value_t *)Message;
}

ML_METHOD(MessageT, MLIntegerT) {
//<Signal
//>message
// Returns a new signal message with specified value.
	message_t *Message = new(message_t);
	Message->Type = MessageT;
	Message->Handle = zmsg_new_signal(ml_integer_value(Args[0]));
	GC_register_finalizer(Message, (GC_finalization_proc)message_finalize, NULL, NULL, NULL);
	return (ml_value_t *)Message;
}

ML_METHOD(MessageT, SocketT) {
//<Socket
//>message|nil
// Returns the next message read from :mini:`Socket`, blocking until a message is available.
	socket_t *Socket = (socket_t *)Args[0];
	zmsg_t *Handle = zmsg_recv(Socket->Handle);
	if (!Handle) return MLNil;
	message_t *Message = new(message_t);
	Message->Type = MessageT;
	Message->Handle = Handle;
	GC_register_finalizer(Message, (GC_finalization_proc)message_finalize, NULL, NULL, NULL);
	return (ml_value_t *)Message;
}

ML_METHOD(MessageT, SocketT, MLBooleanT) {
//<Socket
//<Block
//>message|nil
// Returns the next message read from :mini:`Socket`; if :mini:`Block = true` then blocks until a message is available.
	socket_t *Socket = (socket_t *)Args[0];
	zmsg_t *Handle = ml_boolean_value(Args[1]) ? zmsg_recv(Socket->Handle) : zmsg_recv_nowait(Socket->Handle);
	if (!Handle) return MLNil;
	message_t *Message = new(message_t);
	Message->Type = MessageT;
	Message->Handle = Handle;
	GC_register_finalizer(Message, (GC_finalization_proc)message_finalize, NULL, NULL, NULL);
	return (ml_value_t *)Message;
}

ML_METHOD("put", MessageT, MLAddressT) {
//<Message
//<Bytes
//>message
// Appends a new frame to the end of :mini:`Message` with the specified content.
	message_t *Message = (message_t *)Args[0];
	zmsg_addmem(Message->Handle, ml_address_value(Args[1]), ml_address_length(Args[1]));
	return (ml_value_t *)Message;
}

ML_METHOD("put", MessageT, FrameT) {
//<Message
//<Frame
//>message
// Appends :mini:`Frame` to the end of :mini:`Message`.
	message_t *Message = (message_t *)Args[0];
	frame_t *Frame = (frame_t *)Args[1];
	zmsg_append(Message->Handle, &Frame->Handle);
	return (ml_value_t *)Message;
}

ML_METHOD("put", MessageT, MessageT) {
//<Message
//<SubMessage
//>message
// Appends :mini:`SubMessage` to the end of :mini:`Message`.
	message_t *Message = (message_t *)Args[0];
	message_t *SubMessage = (message_t *)Args[1];
	zmsg_addmsg(Message->Handle, &SubMessage->Handle);
	return (ml_value_t *)Message;
}

ML_METHOD("put", MessageT, MLNilT) {
//<Message
//<Nil
//>message
// Appends an empty frame to the end of :mini:`Message`.
	message_t *Message = (message_t *)Args[0];
	zmsg_add(Message->Handle, zframe_new_empty());
	return (ml_value_t *)Message;
}

ML_METHOD("send", MessageT, SocketT) {
//<Message
//<Socket
// Sends :mini:`Message` on :mini:`Socket`.
	message_t *Message = (message_t *)Args[0];
	socket_t *Socket = (socket_t *)Args[1];
	zmsg_send(&Message->Handle, Socket->Handle);
	return MLNil;
}

ML_METHOD("sendm", MessageT, SocketT) {
//<Message
//<Socket
// Sends :mini:`Message` on :mini:`Socket` without the final flag.
	message_t *Message = (message_t *)Args[0];
	socket_t *Socket = (socket_t *)Args[1];
	zmsg_sendm(&Message->Handle, Socket->Handle);
	return MLNil;
}

ML_METHOD("pop", MessageT) {
//<Message
//>frame|nil
// Removes and returns the first frame in :mini:`Message` or :mini:`nil` if there are no frames.
	message_t *Message = (message_t *)Args[0];
	if (!zmsg_size(Message->Handle)) return MLNil;
	frame_t *Frame = new(frame_t);
	Frame->Type = FrameT;
	Frame->Handle = zmsg_pop(Message->Handle);
	GC_register_finalizer(Frame, (GC_finalization_proc)frame_finalize, NULL, NULL, NULL);
	return (ml_value_t *)Frame;
}

ML_METHOD("popmsg", MessageT) {
//<Message
//>message|nil
// Removes and returns the first sub message in :mini:`Message` or :mini:`nil` if there are no sub messages.
	message_t *Message = (message_t *)Args[0];
	message_t *SubMessage = new(message_t);
	SubMessage->Type = MessageT;
	SubMessage->Handle = zmsg_popmsg(Message->Handle);
	GC_register_finalizer(SubMessage, (GC_finalization_proc)message_finalize, NULL, NULL, NULL);
	return (ml_value_t *)SubMessage;
}

ML_METHOD("append", MLStringBufferT, MessageT) {
	ml_stringbuffer_t *Buffer = (ml_stringbuffer_t *)Args[0];
	message_t *Message = (message_t *)Args[1];
	ml_stringbuffer_write(Buffer, "{", 1);
	for (zframe_t *Frame = zmsg_first(Message->Handle); Frame; Frame = zmsg_next(Message->Handle)) {
		size_t Length = zframe_size(Frame);
		ml_stringbuffer_printf(Buffer, " %ld:", Length);
		byte *Bytes = zframe_data(Frame);
		for (int I = Length; --I >= 0;) ml_stringbuffer_printf(Buffer, "%02x", *Bytes++);
	}
	ml_stringbuffer_write(Buffer, " }", 2);
	return MLSome;
}

typedef struct {
	ml_type_t *Type;
	zmsg_t *Handle;
	frame_t *Frame;
	int Index;
} message_iter_t;

ML_TYPE(MessageIterT, (), "zeromq::message::iter");
//!internal

static void ML_TYPED_FN(ml_iterate, MessageT, ml_state_t *Caller, message_t *Message) {
	zframe_t *Handle = zmsg_pop(Message->Handle);
	if (!Handle) ML_RETURN(MLNil);
	message_iter_t *Iter = new(message_iter_t);
	Iter->Type = MessageIterT;
	Iter->Handle = Message->Handle;
	frame_t *Frame = Iter->Frame = new(frame_t);
	Frame->Type = FrameT;
	Frame->Handle = Handle;
	GC_register_finalizer(Frame, (GC_finalization_proc)frame_finalize, NULL, NULL, NULL);
	Iter->Index = 1;
	ML_RETURN(Iter);
}

static void ML_TYPED_FN(ml_iter_next, MessageIterT, ml_state_t *Caller, message_iter_t *Iter) {
	zframe_t *Handle = zmsg_pop(Iter->Handle);
	if (!Handle) ML_RETURN(MLNil);
	frame_t *Frame = Iter->Frame = new(frame_t);
	Frame->Type = FrameT;
	Frame->Handle = Handle;
	GC_register_finalizer(Frame, (GC_finalization_proc)frame_finalize, NULL, NULL, NULL);
	++Iter->Index;
	ML_RETURN(Iter);
}

static void ML_TYPED_FN(ml_iter_key, MessageIterT, ml_state_t *Caller, message_iter_t *Iter) {
	ML_RETURN(ml_integer(Iter->Index));
}

static void ML_TYPED_FN(ml_iter_value, MessageIterT, ml_state_t *Caller, message_iter_t *Iter) {
	ML_RETURN(Iter->Frame);
}

void ml_library_entry0(ml_value_t **Slot) {
#include "zeromq_init.c"
	stringmap_insert(SocketT->Exports, "type", SocketTypeT);
	stringmap_insert(SocketT->Exports, "event", SocketEventT);
	Slot[0] = ml_module("zeromq",
		"socket", SocketT,
		"message", MessageT,
		"frame", FrameT,
	NULL);
}
