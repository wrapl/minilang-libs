.. include:: <isonum.txt>

.. include:: <isoamsa.txt>

.. include:: <isotech.txt>

net/zeromq
==========

:mini:`meth :MessageT(): message`
   Returns a new empty message.


:mini:`meth (Bytes: address):FrameT: frame`
   Returns a new frame with the contents of :mini:`Bytes`.


:mini:`meth (Frame₁: any):MessageT(...): message`
   Returns a new message with the specified content. :mini:`Frameᵢ` can be bytes (address / string),  a frame,  another message or :mini:`nil` to add an empty frame.


.. _type-frame:

:mini:`type frame`
   ZeroMQ frame.


:mini:`meth (Frame: frame):data: string`
   Returns the contents of :mini:`Frame`.


:mini:`meth (Arg₁: string::buffer):append(Arg₂: frame)`
   *TBD*


:mini:`meth (Signal: integer):MessageT: message`
   Returns a new signal message with specified value.


.. _type-message:

:mini:`type message < sequence`
   ZeroMQ message.


:mini:`meth (Message: message):pop: frame | nil`
   Removes and returns the first frame in :mini:`Message` or :mini:`nil` if there are no frames.


:mini:`meth (Message: message):popmsg: message | nil`
   Removes and returns the first sub message in :mini:`Message` or :mini:`nil` if there are no sub messages.


:mini:`meth (Message: message):put(Frame: frame): message`
   Appends :mini:`Frame` to the end of :mini:`Message`.


:mini:`meth (Message: message):put(Bytes: address): message`
   Appends a new frame to the end of :mini:`Message` with the specified content.


:mini:`meth (Message: message):put(Nil: nil): message`
   Appends an empty frame to the end of :mini:`Message`.


:mini:`meth (Message: message):put(SubMessage: message): message`
   Appends :mini:`SubMessage` to the end of :mini:`Message`.


:mini:`meth (Message: message):send(Socket: socket)`
   Sends :mini:`Message` on :mini:`Socket`.


:mini:`meth (Message: message):sendm(Socket: socket)`
   Sends :mini:`Message` on :mini:`Socket` without the final flag.


:mini:`meth (Arg₁: string::buffer):append(Arg₂: message)`
   *TBD*


.. _type-socket:

:mini:`type socket`
   ZeroMQ socket.


:mini:`meth (Socket: socket):MessageT: message | nil`
   Returns the next message read from :mini:`Socket`,  blocking until a message is available.


:mini:`meth (Socket: socket):MessageT(Block: boolean): message | nil`
   Returns the next message read from :mini:`Socket`; if :mini:`Block = true` then blocks until a message is available.


:mini:`meth (Socket: socket):affinity: integer`
   Returns the current affinity setting of :mini:`Socket`.


:mini:`meth (Socket: socket):affinity(Integer: integer)`
   Updates the affinity setting of :mini:`Socket`.


:mini:`meth (Arg₁: socket):attach(Arg₂: string, Arg₃: boolean)`
   *TBD*


:mini:`meth (Socket: socket):backlog: integer`
   Returns the current backlog setting of :mini:`Socket`.


:mini:`meth (Socket: socket):backlog(Integer: integer)`
   Updates the backlog setting of :mini:`Socket`.


:mini:`meth (Arg₁: socket):bind(Arg₂: string)`
   *TBD*


:mini:`meth (Socket: socket):conflate(Integer: integer)`
   Updates the conflate setting of :mini:`Socket`.


:mini:`meth (Arg₁: socket):connect(Arg₂: string)`
   *TBD*


:mini:`meth (Socket: socket):connect_rid(Integer: string)`
   Updates the connect_rid setting of :mini:`Socket`.


:mini:`meth (Socket: socket):connect_timeout: integer`
   Returns the current connect_timeout setting of :mini:`Socket`.


:mini:`meth (Socket: socket):connect_timeout(Integer: integer)`
   Updates the connect_timeout setting of :mini:`Socket`.


:mini:`meth (Socket: socket):curve_publickey: integer`
   Returns the current curve_publickey setting of :mini:`Socket`.


:mini:`meth (Socket: socket):curve_publickey(Integer: string)`
   Updates the curve_publickey setting of :mini:`Socket`.


:mini:`meth (Socket: socket):curve_secretkey: integer`
   Returns the current curve_secretkey setting of :mini:`Socket`.


:mini:`meth (Socket: socket):curve_secretkey(Integer: string)`
   Updates the curve_secretkey setting of :mini:`Socket`.


:mini:`meth (Socket: socket):curve_server: integer`
   Returns the current curve_server setting of :mini:`Socket`.


:mini:`meth (Socket: socket):curve_server(Integer: integer)`
   Updates the curve_server setting of :mini:`Socket`.


:mini:`meth (Socket: socket):delay_attach_on_connect(Integer: integer)`
   Updates the delay_attach_on_connect setting of :mini:`Socket`.


:mini:`meth (Arg₁: socket):destroy`
   *TBD*


:mini:`meth (Arg₁: socket):disconnect(Arg₂: string)`
   *TBD*


:mini:`meth (Arg₁: socket):endpoint`
   *TBD*


:mini:`meth (Socket: socket):events: integer`
   Returns the current events setting of :mini:`Socket`.


:mini:`meth (Socket: socket):fd: integer`
   Returns the current fd setting of :mini:`Socket`.


:mini:`meth (Arg₁: socket):flush`
   *TBD*


:mini:`meth (Socket: socket):gssapi_plaintext: integer`
   Returns the current gssapi_plaintext setting of :mini:`Socket`.


:mini:`meth (Socket: socket):gssapi_plaintext(Integer: integer)`
   Updates the gssapi_plaintext setting of :mini:`Socket`.


:mini:`meth (Socket: socket):gssapi_principal: integer`
   Returns the current gssapi_principal setting of :mini:`Socket`.


:mini:`meth (Socket: socket):gssapi_principal(Integer: string)`
   Updates the gssapi_principal setting of :mini:`Socket`.


:mini:`meth (Socket: socket):gssapi_server: integer`
   Returns the current gssapi_server setting of :mini:`Socket`.


:mini:`meth (Socket: socket):gssapi_server(Integer: integer)`
   Updates the gssapi_server setting of :mini:`Socket`.


:mini:`meth (Socket: socket):gssapi_service_principal: integer`
   Returns the current gssapi_service_principal setting of :mini:`Socket`.


:mini:`meth (Socket: socket):gssapi_service_principal(Integer: string)`
   Updates the gssapi_service_principal setting of :mini:`Socket`.


:mini:`meth (Socket: socket):handshake_ivl: integer`
   Returns the current handshake_ivl setting of :mini:`Socket`.


:mini:`meth (Socket: socket):handshake_ivl(Integer: integer)`
   Updates the handshake_ivl setting of :mini:`Socket`.


:mini:`meth (Socket: socket):heartbeat_ivl: integer`
   Returns the current heartbeat_ivl setting of :mini:`Socket`.


:mini:`meth (Socket: socket):heartbeat_ivl(Integer: integer)`
   Updates the heartbeat_ivl setting of :mini:`Socket`.


:mini:`meth (Socket: socket):heartbeat_timeout: integer`
   Returns the current heartbeat_timeout setting of :mini:`Socket`.


:mini:`meth (Socket: socket):heartbeat_timeout(Integer: integer)`
   Updates the heartbeat_timeout setting of :mini:`Socket`.


:mini:`meth (Socket: socket):heartbeat_ttl: integer`
   Returns the current heartbeat_ttl setting of :mini:`Socket`.


:mini:`meth (Socket: socket):heartbeat_ttl(Integer: integer)`
   Updates the heartbeat_ttl setting of :mini:`Socket`.


:mini:`meth (Socket: socket):identity: integer`
   Returns the current identity setting of :mini:`Socket`.


:mini:`meth (Socket: socket):identity(Integer: string)`
   Updates the identity setting of :mini:`Socket`.


:mini:`meth (Socket: socket):immediate: integer`
   Returns the current immediate setting of :mini:`Socket`.


:mini:`meth (Socket: socket):immediate(Integer: integer)`
   Updates the immediate setting of :mini:`Socket`.


:mini:`meth (Socket: socket):invert_matching: integer`
   Returns the current invert_matching setting of :mini:`Socket`.


:mini:`meth (Socket: socket):invert_matching(Integer: integer)`
   Updates the invert_matching setting of :mini:`Socket`.


:mini:`meth (Socket: socket):ipv4only: integer`
   Returns the current ipv4only setting of :mini:`Socket`.


:mini:`meth (Socket: socket):ipv4only(Integer: integer)`
   Updates the ipv4only setting of :mini:`Socket`.


:mini:`meth (Socket: socket):ipv6: integer`
   Returns the current ipv6 setting of :mini:`Socket`.


:mini:`meth (Socket: socket):ipv6(Integer: integer)`
   Updates the ipv6 setting of :mini:`Socket`.


:mini:`meth (Socket: socket):linger: integer`
   Returns the current linger setting of :mini:`Socket`.


:mini:`meth (Socket: socket):linger(Integer: integer)`
   Updates the linger setting of :mini:`Socket`.


:mini:`meth (Socket: socket):maxmsgsize: integer`
   Returns the current maxmsgsize setting of :mini:`Socket`.


:mini:`meth (Socket: socket):maxmsgsize(Integer: integer)`
   Updates the maxmsgsize setting of :mini:`Socket`.


:mini:`meth (Socket: socket):multicast_hops: integer`
   Returns the current multicast_hops setting of :mini:`Socket`.


:mini:`meth (Socket: socket):multicast_hops(Integer: integer)`
   Updates the multicast_hops setting of :mini:`Socket`.


:mini:`meth (Socket: socket):multicast_maxtpdu: integer`
   Returns the current multicast_maxtpdu setting of :mini:`Socket`.


:mini:`meth (Socket: socket):multicast_maxtpdu(Integer: integer)`
   Updates the multicast_maxtpdu setting of :mini:`Socket`.


:mini:`meth (Socket: socket):plain_password: integer`
   Returns the current plain_password setting of :mini:`Socket`.


:mini:`meth (Socket: socket):plain_password(Integer: string)`
   Updates the plain_password setting of :mini:`Socket`.


:mini:`meth (Socket: socket):plain_server: integer`
   Returns the current plain_server setting of :mini:`Socket`.


:mini:`meth (Socket: socket):plain_server(Integer: integer)`
   Updates the plain_server setting of :mini:`Socket`.


:mini:`meth (Socket: socket):plain_username: integer`
   Returns the current plain_username setting of :mini:`Socket`.


:mini:`meth (Socket: socket):plain_username(Integer: string)`
   Updates the plain_username setting of :mini:`Socket`.


:mini:`meth (Socket: socket):probe_router(Integer: integer)`
   Updates the probe_router setting of :mini:`Socket`.


:mini:`meth (Socket: socket):rate: integer`
   Returns the current rate setting of :mini:`Socket`.


:mini:`meth (Socket: socket):rate(Integer: integer)`
   Updates the rate setting of :mini:`Socket`.


:mini:`meth (Socket: socket):rcvbuf: integer`
   Returns the current rcvbuf setting of :mini:`Socket`.


:mini:`meth (Socket: socket):rcvbuf(Integer: integer)`
   Updates the rcvbuf setting of :mini:`Socket`.


:mini:`meth (Socket: socket):rcvhwm: integer`
   Returns the current rcvhwm setting of :mini:`Socket`.


:mini:`meth (Socket: socket):rcvhwm(Integer: integer)`
   Updates the rcvhwm setting of :mini:`Socket`.


:mini:`meth (Socket: socket):rcvmore: integer`
   Returns the current rcvmore setting of :mini:`Socket`.


:mini:`meth (Socket: socket):rcvtimeo: integer`
   Returns the current rcvtimeo setting of :mini:`Socket`.


:mini:`meth (Socket: socket):rcvtimeo(Integer: integer)`
   Updates the rcvtimeo setting of :mini:`Socket`.


:mini:`meth (Socket: socket):reconnect_ivl: integer`
   Returns the current reconnect_ivl setting of :mini:`Socket`.


:mini:`meth (Socket: socket):reconnect_ivl(Integer: integer)`
   Updates the reconnect_ivl setting of :mini:`Socket`.


:mini:`meth (Socket: socket):reconnect_ivl_max: integer`
   Returns the current reconnect_ivl_max setting of :mini:`Socket`.


:mini:`meth (Socket: socket):reconnect_ivl_max(Integer: integer)`
   Updates the reconnect_ivl_max setting of :mini:`Socket`.


:mini:`meth (Socket: socket):recovery_ivl: integer`
   Returns the current recovery_ivl setting of :mini:`Socket`.


:mini:`meth (Socket: socket):recovery_ivl(Integer: integer)`
   Updates the recovery_ivl setting of :mini:`Socket`.


:mini:`meth (Socket: socket):req_correlate(Integer: integer)`
   Updates the req_correlate setting of :mini:`Socket`.


:mini:`meth (Socket: socket):req_relaxed(Integer: integer)`
   Updates the req_relaxed setting of :mini:`Socket`.


:mini:`meth (Socket: socket):router_handover(Integer: integer)`
   Updates the router_handover setting of :mini:`Socket`.


:mini:`meth (Socket: socket):router_mandatory(Integer: integer)`
   Updates the router_mandatory setting of :mini:`Socket`.


:mini:`meth (Socket: socket):router_raw(Integer: integer)`
   Updates the router_raw setting of :mini:`Socket`.


:mini:`meth (Arg₁: socket):signal(Arg₂: integer)`
   *TBD*


:mini:`meth (Socket: socket):sndbuf: integer`
   Returns the current sndbuf setting of :mini:`Socket`.


:mini:`meth (Socket: socket):sndbuf(Integer: integer)`
   Updates the sndbuf setting of :mini:`Socket`.


:mini:`meth (Socket: socket):sndhwm: integer`
   Returns the current sndhwm setting of :mini:`Socket`.


:mini:`meth (Socket: socket):sndhwm(Integer: integer)`
   Updates the sndhwm setting of :mini:`Socket`.


:mini:`meth (Socket: socket):sndtimeo: integer`
   Returns the current sndtimeo setting of :mini:`Socket`.


:mini:`meth (Socket: socket):sndtimeo(Integer: integer)`
   Updates the sndtimeo setting of :mini:`Socket`.


:mini:`meth (Socket: socket):socks_proxy: integer`
   Returns the current socks_proxy setting of :mini:`Socket`.


:mini:`meth (Socket: socket):socks_proxy(Integer: string)`
   Updates the socks_proxy setting of :mini:`Socket`.


:mini:`meth (Socket: socket):stream_notify(Integer: integer)`
   Updates the stream_notify setting of :mini:`Socket`.


:mini:`meth (Socket: socket):subscribe(Integer: string)`
   Updates the subscribe setting of :mini:`Socket`.


:mini:`meth (Socket: socket):tcp_accept_filter: integer`
   Returns the current tcp_accept_filter setting of :mini:`Socket`.


:mini:`meth (Socket: socket):tcp_accept_filter(Integer: string)`
   Updates the tcp_accept_filter setting of :mini:`Socket`.


:mini:`meth (Socket: socket):tcp_keepalive: integer`
   Returns the current tcp_keepalive setting of :mini:`Socket`.


:mini:`meth (Socket: socket):tcp_keepalive(Integer: integer)`
   Updates the tcp_keepalive setting of :mini:`Socket`.


:mini:`meth (Socket: socket):tcp_keepalive_cnt: integer`
   Returns the current tcp_keepalive_cnt setting of :mini:`Socket`.


:mini:`meth (Socket: socket):tcp_keepalive_cnt(Integer: integer)`
   Updates the tcp_keepalive_cnt setting of :mini:`Socket`.


:mini:`meth (Socket: socket):tcp_keepalive_idle: integer`
   Returns the current tcp_keepalive_idle setting of :mini:`Socket`.


:mini:`meth (Socket: socket):tcp_keepalive_idle(Integer: integer)`
   Updates the tcp_keepalive_idle setting of :mini:`Socket`.


:mini:`meth (Socket: socket):tcp_keepalive_intvl: integer`
   Returns the current tcp_keepalive_intvl setting of :mini:`Socket`.


:mini:`meth (Socket: socket):tcp_keepalive_intvl(Integer: integer)`
   Updates the tcp_keepalive_intvl setting of :mini:`Socket`.


:mini:`meth (Socket: socket):tcp_maxrt: integer`
   Returns the current tcp_maxrt setting of :mini:`Socket`.


:mini:`meth (Socket: socket):tcp_maxrt(Integer: integer)`
   Updates the tcp_maxrt setting of :mini:`Socket`.


:mini:`meth (Socket: socket):tos: integer`
   Returns the current tos setting of :mini:`Socket`.


:mini:`meth (Socket: socket):tos(Integer: integer)`
   Updates the tos setting of :mini:`Socket`.


:mini:`meth (Arg₁: socket):unbind(Arg₂: string)`
   *TBD*


:mini:`meth (Socket: socket):unsubscribe(Integer: string)`
   Updates the unsubscribe setting of :mini:`Socket`.


:mini:`meth (Socket: socket):use_fd: integer`
   Returns the current use_fd setting of :mini:`Socket`.


:mini:`meth (Socket: socket):use_fd(Integer: integer)`
   Updates the use_fd setting of :mini:`Socket`.


:mini:`meth (Socket: socket):vmci_buffer_max_size: integer`
   Returns the current vmci_buffer_max_size setting of :mini:`Socket`.


:mini:`meth (Socket: socket):vmci_buffer_max_size(Integer: integer)`
   Updates the vmci_buffer_max_size setting of :mini:`Socket`.


:mini:`meth (Socket: socket):vmci_buffer_min_size: integer`
   Returns the current vmci_buffer_min_size setting of :mini:`Socket`.


:mini:`meth (Socket: socket):vmci_buffer_min_size(Integer: integer)`
   Updates the vmci_buffer_min_size setting of :mini:`Socket`.


:mini:`meth (Socket: socket):vmci_buffer_size: integer`
   Returns the current vmci_buffer_size setting of :mini:`Socket`.


:mini:`meth (Socket: socket):vmci_buffer_size(Integer: integer)`
   Updates the vmci_buffer_size setting of :mini:`Socket`.


:mini:`meth (Socket: socket):vmci_connect_timeout: integer`
   Returns the current vmci_connect_timeout setting of :mini:`Socket`.


:mini:`meth (Socket: socket):vmci_connect_timeout(Integer: integer)`
   Updates the vmci_connect_timeout setting of :mini:`Socket`.


:mini:`meth (Arg₁: socket):wait`
   *TBD*


:mini:`meth (Socket: socket):xpub_manual(Integer: integer)`
   Updates the xpub_manual setting of :mini:`Socket`.


:mini:`meth (Socket: socket):xpub_nodrop(Integer: integer)`
   Updates the xpub_nodrop setting of :mini:`Socket`.


:mini:`meth (Socket: socket):xpub_verbose(Integer: integer)`
   Updates the xpub_verbose setting of :mini:`Socket`.


:mini:`meth (Socket: socket):xpub_verboser(Integer: integer)`
   Updates the xpub_verboser setting of :mini:`Socket`.


:mini:`meth (Socket: socket):xpub_welcome_msg(Integer: string)`
   Updates the xpub_welcome_msg setting of :mini:`Socket`.


:mini:`meth (Socket: socket):zap_domain: integer`
   Returns the current zap_domain setting of :mini:`Socket`.


:mini:`meth (Socket: socket):zap_domain(Integer: string)`
   Updates the zap_domain setting of :mini:`Socket`.


:mini:`meth (Arg₁: string::buffer):append(Arg₂: socket)`
   *TBD*


.. _type-socket_event:

:mini:`type socket_event < enum`
   *TBD*


.. _type-socket_type:

:mini:`type socket_type < enum`
   ZeroMQ socket type.


:mini:`meth (Type: socket_type):SocketT: socket`
   Returns a new socket of the specified type.


