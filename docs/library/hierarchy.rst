
hierarchy
=========

.. graphviz::

   digraph hierarchy {
      rankdir="LR";
      fontsize="40pt"
      concentrate=true;
      overlap=false;
      packMode="node";
      outputorder="edgesfirst";
      node [shape=box,fontsize=24];
      "any":e -> "onion":w;
      "any":e -> "onion_handler":w;
      "any":e -> "onion_request":w;
      "stream":e -> "onion_response":w;
      "any":e -> "onion_state":w;
      "any":e -> "onion_url":w;
      "any":e -> "onion_websocket":w;
      "sequence":e -> "bitset":w;
      "any":e -> "plugin_class":w;
      "any":e -> "plugin":w;
      "any":e -> "port":w;
      "any":e -> "instance":w;
      "any":e -> "space":w;
      "any":e -> "parser":w;
      "parser":e -> "parser::string":w;
      "parser":e -> "parser::value":w;
      "parser::value":e -> "parser::named":w;
      "any":e -> "cleri":w;
      "any":e -> "cleri_parse":w;
      "function":e -> "cleri_grammar":w;
      "any":e -> "socket":w;
      "enum":e -> "socket_type":w;
      "enum":e -> "socket_event":w;
      "any":e -> "frame":w;
      "sequence":e -> "message":w;
      "any":e -> "curl":w;
      "enum":e -> "curl_option":w;
      "function":e -> "logger":w;
      "any":e -> "category":w;
      "any":e -> "context":w;
      "any":e -> "geometry":w;
      "any":e -> "tree":w;
      "any":e -> "node":w;
      "sequence":e -> "node_list":w;
      "any":e -> "node_iter":w;
      "any":e -> "c_s_s_selectors":w;
      "node":e -> "element":w;
      "any":e -> "attribute":w;
      "sequence":e -> "attr_list":w;
      "any":e -> "attr_iter":w;
      "node":e -> "document":w;
      "any":e -> "csv":w;
      "any":e -> "uvfile":w;
      "any":e -> "event_base":w;
      "any":e -> "event":w;
      "any":e -> "event_http":w;
      "any":e -> "connections":w;
      "any":e -> "connection":w;
      "any":e -> "source_field":w;
      "stream":e -> "md5":w;
      "stream":e -> "ripemd160":w;
      "stream":e -> "sha1":w;
      "stream":e -> "sha224":w;
      "stream":e -> "sha256":w;
      "stream":e -> "sha384":w;
      "stream":e -> "sha512":w;
      "flags":e -> "sqlite::open":w;
      "any":e -> "sqlite":w;
      "sequence":e -> "sqlite::stmt":w;
      "any":e -> "version_store":w;
      "any":e -> "string_store":w;
      "stream":e -> "string_store_writer":w;
      "stream":e -> "string_store_reader":w;
      "any":e -> "cbor_store":w;
      "any":e -> "string_index":w;
      "any":e -> "cbor_index":w;
      "any":e -> "connection":w;
      "function":e -> "statement":w;
      "any":e -> "f_d_b_database":w;
      "any":e -> "f_d_b_transaction":w;
      "any":e -> "dqlite":w;
   }

