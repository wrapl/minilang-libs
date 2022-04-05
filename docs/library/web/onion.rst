.. include:: <isonum.txt>

.. include:: <isoamsa.txt>

.. include:: <isotech.txt>

web/onion
=========

.. _fun-onionurl:

:mini:`fun onionurl()`
   *TBD*


:mini:`meth onion_handler(Arg₁: function)`
   *TBD*


:mini:`meth onion_handler(Arg₁: integer, Arg₂: string)`
   *TBD*


.. _type-onion:

:mini:`type onion`
   *TBD*


:mini:`meth onion()`
   *TBD*


:mini:`meth (Arg₁: onion):get_root_handler`
   *TBD*


:mini:`meth (Arg₁: onion):listen`
   *TBD*


:mini:`meth (Arg₁: onion):listen_stop`
   *TBD*


:mini:`meth (Arg₁: onion):root_url`
   *TBD*


:mini:`meth (Arg₁: onion):set_hostname(Arg₂: string)`
   *TBD*


:mini:`meth (Arg₁: onion):set_internal_error_handler(Arg₂: function)`
   *TBD*


:mini:`meth (Arg₁: onion):set_internal_error_handler(Arg₂: onion_handler)`
   *TBD*


:mini:`meth (Arg₁: onion):set_port(Arg₂: string)`
   *TBD*


:mini:`meth (Arg₁: onion):set_root_handler(Arg₂: function)`
   *TBD*


:mini:`meth (Arg₁: onion):set_root_handler(Arg₂: onion_handler)`
   *TBD*


.. _type-onion_handler:

:mini:`type onion_handler`
   *TBD*


:mini:`meth (Arg₁: onion_handler):add(Arg₂: onion_handler)`
   *TBD*


:mini:`meth onion(Arg₁: onion_mode)`
   *TBD*


.. _type-onion_request:

:mini:`type onion_request`
   *TBD*


.. _fun-onionwebsocket:

:mini:`fun onionwebsocket(Arg₁: onion_request, Arg₂: onion_response)`
   *TBD*


:mini:`meth (Arg₁: onion_request):get_cookie(Arg₂: string)`
   *TBD*


:mini:`meth (Arg₁: onion_request):get_data`
   *TBD*


:mini:`meth (Arg₁: onion_request):get_file(Arg₂: string)`
   *TBD*


:mini:`meth (Arg₁: onion_request):get_fullpath`
   *TBD*


:mini:`meth (Arg₁: onion_request):get_header(Arg₂: string)`
   *TBD*


:mini:`meth (Arg₁: onion_request):get_path`
   *TBD*


:mini:`meth (Arg₁: onion_request):get_post(Arg₂: string)`
   *TBD*


:mini:`meth (Arg₁: onion_request):get_query(Arg₂: string)`
   *TBD*


.. _type-onion_response:

:mini:`type onion_response < stream`
   *TBD*


:mini:`meth (Arg₁: onion_response):add_cookie(Arg₂: string, Arg₃: string)`
   *TBD*


:mini:`meth (Arg₁: onion_response):flush`
   *TBD*


:mini:`meth (Arg₁: onion_response):set_code(Arg₂: integer)`
   *TBD*


:mini:`meth (Arg₁: onion_response):set_header(Arg₂: string, Arg₃: string)`
   *TBD*


:mini:`meth (Arg₁: onion_response):write(Arg₂: string)`
   *TBD*


.. _type-onion_state:

:mini:`type onion_state`
   *TBD*


.. _type-onion_url:

:mini:`type onion_url`
   *TBD*


:mini:`meth (Arg₁: onion_url):add(Arg₂: string, Arg₃: function)`
   *TBD*


:mini:`meth (Arg₁: onion_url):add(Arg₂: string, Arg₃: onion_handler)`
   *TBD*


:mini:`meth (Arg₁: onion_url):add_static(Arg₂: string, Arg₃: integer, Arg₄: string)`
   *TBD*


:mini:`meth (Arg₁: onion_url):to_handler`
   *TBD*


.. _type-onion_websocket:

:mini:`type onion_websocket`
   *TBD*


:mini:`meth (Arg₁: onion_websocket):set_callback(Arg₂: function)`
   *TBD*


:mini:`meth (Arg₁: onion_websocket):set_opcode(Arg₂: onion_websocket_opcode)`
   *TBD*


:mini:`meth (Arg₁: onion_websocket):write(Arg₂: string)`
   *TBD*


:mini:`meth onion_handler(Arg₁: string)`
   *TBD*


