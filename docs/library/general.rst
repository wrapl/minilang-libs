.. include:: <isonum.txt>

.. include:: <isoamsa.txt>

.. include:: <isotech.txt>

general
=======

.. rst-class:: mini-api

:mini:`fun context()`
   *TBD*


:mini:`fun eventsleep()`
   *TBD*


:mini:`fun eventsleep()`
   *TBD*


:mini:`meth (Arg₁: httprequest):handler(Arg₂: function)`
   *TBD*


:mini:`fun mldqlite(Arg₁: integer, Arg₂: string, Arg₃: string)`
   *TBD*


:mini:`type httprequest < stream`
   *TBD*


:mini:`type uevevent`
   *TBD*


:mini:`type httpmethod < enum`
   * :mini:`::GET`
   * :mini:`::POST`
   * :mini:`::HEAD`
   * :mini:`::PUT`
   * :mini:`::DELETE`
   * :mini:`::OPTIONS`
   * :mini:`::TRACE`
   * :mini:`::CONNECT`
   * :mini:`::PATCH`


:mini:`meth (Arg₁: sequence):DiffMethod(Arg₂: sequence)`
   *TBD*


:mini:`type requesterror < enum`
   * :mini:`::Timeout`
   * :mini:`::EOF`
   * :mini:`::InvalidHeader`
   * :mini:`::BufferError`
   * :mini:`::RequestCancel`
   * :mini:`::DataTooLong`


:mini:`type uevflags < flags`
   * :mini:`::Err`
   * :mini:`::Read`
   * :mini:`::Write`
   * :mini:`::Pri`
   * :mini:`::Hup`
   * :mini:`::RdHup`
   * :mini:`::Edge`
   * :mini:`::Once`


:mini:`meth (Arg₁: httprequest):send_stream(Arg₂: integer, Arg₃: string)`
   *TBD*


:mini:`fun eventevery(Arg₁: real, Arg₂: function)`
   *TBD*


:mini:`meth (Arg₁: httprequest):send_file(Arg₂: integer, Arg₃: string, Arg₄: string)`
   *TBD*


:mini:`meth (Arg₁: uev):exit`
   *TBD*


:mini:`meth (Arg₁: httprequest):send_reply(Arg₂: integer, Arg₃: string, Arg₄: address)`
   *TBD*


:mini:`meth (Arg₁: string):DiffMethod(Arg₂: string)`
   *TBD*


:mini:`fun eventafter(Arg₁: real, Arg₂: function)`
   *TBD*


:mini:`meth (Arg₁: uev):run`
   *TBD*


:mini:`meth (Arg₁: httprequest):method`
   *TBD*


:mini:`meth (Arg₁: httprequest):peer`
   *TBD*


:mini:`type httprequest < stream`
   *TBD*


:mini:`meth uev()`
   *TBD*


:mini:`meth (Arg₁: httprequest):method`
   *TBD*


:mini:`meth (Arg₁: slice):DiffMethod(Arg₂: slice)`
   *TBD*


:mini:`fun eventsocket(Arg₁: integer, Arg₂: eventtype, Arg₃: function)`
   *TBD*


:mini:`type uev`
   *TBD*


:mini:`meth (Arg₁: uevevent):start`
   *TBD*


:mini:`type op < enum`
   *TBD*


:mini:`type httpheader`
   *TBD*


:mini:`meth (Arg₁: tree):insert(Arg₂: geometry, Arg₃: any)`
   *TBD*


:mini:`meth (Arg₁: httprequest):headers`
   *TBD*


:mini:`meth (Arg₁: uev):event(Arg₂: function)`
   *TBD*


:mini:`meth (Arg₁: string):SqlParse`
   *TBD*


:mini:`meth (Arg₁: uev):timer(Arg₂: integer, Arg₃: integer, Arg₄: function)`
   *TBD*


:mini:`meth (Arg₁: httprequest):send_file(Arg₂: integer, Arg₃: string, Arg₄: string)`
   *TBD*


:mini:`meth (Arg₁: uev):timer(Arg₂: integer, Arg₃: function)`
   *TBD*


:mini:`type tree`
   *TBD*


:mini:`meth (Arg₁: uev):io(Arg₂: stream::fd, Arg₃: uevflags, Arg₄: function)`
   *TBD*


:mini:`meth (Arg₁: httprequest):add_header(Arg₂: string, Arg₃: string)`
   *TBD*


:mini:`meth (Arg₁: uevevent):stop`
   *TBD*


:mini:`fun toast(Arg₁: string)`
   *TBD*


:mini:`meth (Arg₁: httprequest):peer`
   *TBD*


:mini:`meth (Arg₁: eventhttp):bind(Arg₂: string, Arg₃: integer)`
   *TBD*


:mini:`meth eventhttp(Arg₁: function)`
   *TBD*


:mini:`meth (Arg₁: httpheaders)[Arg₂: string]`
   *TBD*


:mini:`meth (Arg₁: httprequest):headers`
   *TBD*


:mini:`type httpheaders < sequence`
   *TBD*


:mini:`meth (Arg₁: httprequest):send_error(Arg₂: integer, Arg₃: string)`
   *TBD*


:mini:`meth (Arg₁: httprequest):body`
   *TBD*


:mini:`meth (Arg₁: httprequest):add_header(Arg₂: string, Arg₃: string)`
   *TBD*


:mini:`type eventtype < flags`
   * :mini:`::Timeout`
   * :mini:`::Read`
   * :mini:`::Write`
   * :mini:`::Signal`
   * :mini:`::Persist`
   * :mini:`::ET`
   * :mini:`::Finalize`
   * :mini:`::Closed`


:mini:`type httpmethod < enum`
   * :mini:`::GET`
   * :mini:`::POST`
   * :mini:`::HEAD`
   * :mini:`::PUT`
   * :mini:`::DELETE`
   * :mini:`::OPTIONS`
   * :mini:`::TRACE`
   * :mini:`::CONNECT`
   * :mini:`::PATCH`


:mini:`meth eventhttp()`
   *TBD*


:mini:`type eventtimer < event`
   *TBD*


:mini:`meth (Arg₁: eventhttp):bind(Arg₂: string, Arg₃: integer)`
   *TBD*


:mini:`meth eventhttp(Arg₁: function)`
   *TBD*


:mini:`meth (Arg₁: httpheaders)[Arg₂: string]`
   *TBD*


:mini:`meth (Arg₁: httprequest):send_stream(Arg₂: integer, Arg₃: string)`
   *TBD*


:mini:`meth (Arg₁: httprequest):send_error(Arg₂: integer, Arg₃: string)`
   *TBD*


:mini:`meth (Arg₁: httprequest):send_reply(Arg₂: integer, Arg₃: string, Arg₄: address)`
   *TBD*


:mini:`meth (Arg₁: httprequest):uri`
   *TBD*


:mini:`meth (Arg₁: dqlite):stop`
   *TBD*


:mini:`meth (Arg₁: eventhttp):enable_ssl(Arg₂: string, Arg₃: string)`
   *TBD*


:mini:`type httpheader`
   *TBD*


:mini:`type geometry`
   *TBD*


:mini:`meth (Arg₁: httprequest):uri`
   *TBD*


:mini:`meth (Arg₁: eventtimer):cancel`
   *TBD*


:mini:`type eventhttp`
   *TBD*


:mini:`meth (Arg₁: eventhttp):enable_ssl(Arg₂: string, Arg₃: string)`
   *TBD*


:mini:`type httpheaders < sequence`
   *TBD*


:mini:`meth (Arg₁: httprequest):body`
   *TBD*


:mini:`meth (Arg₁: dqlite):start`
   *TBD*


:mini:`type eventhttp`
   *TBD*


:mini:`meth eventhttp()`
   *TBD*


:mini:`type event`
   *TBD*


:mini:`type event`
   *TBD*


:mini:`meth (Arg₁: context):rectangle(Arg₂: real, Arg₃: real, Arg₄: real, Arg₅: real)`
   *TBD*


:mini:`type dqlite`
   *TBD*


:mini:`meth (Arg₁: context):tree`
   *TBD*


:mini:`type context`
   *TBD*


