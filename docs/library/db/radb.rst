.. include:: <isonum.txt>

.. include:: <isoamsa.txt>

.. include:: <isotech.txt>

db/radb
=======

.. _type-cbor_index:

:mini:`type cbor_index`
   *TBD*


:mini:`meth (Arg₁: cbor_index):close`
   *TBD*


:mini:`meth (Arg₁: cbor_index):delete(Arg₂: any)`
   *TBD*


:mini:`meth (Arg₁: cbor_index):get(Arg₂: integer)`
   *TBD*


:mini:`meth (Arg₁: cbor_index):insert(Arg₂: any)`
   *TBD*


:mini:`meth (Arg₁: cbor_index):search(Arg₂: any)`
   *TBD*


.. _type-cbor_store:

:mini:`type cbor_store`
   *TBD*


:mini:`meth (Arg₁: cbor_store):close`
   *TBD*


:mini:`meth (Arg₁: cbor_store):get(Arg₂: integer)`
   *TBD*


:mini:`meth (Arg₁: cbor_store):set(Arg₂: integer, Arg₃: any)`
   *TBD*


.. _fun-cborindexcreate:

:mini:`fun cborindexcreate(Arg₁: string)`
   *TBD*


.. _fun-cborindexopen:

:mini:`fun cborindexopen(Arg₁: string)`
   *TBD*


.. _fun-stringindexcreate:

:mini:`fun stringindexcreate(Arg₁: string)`
   *TBD*


.. _fun-stringindexopen:

:mini:`fun stringindexopen(Arg₁: string)`
   *TBD*


:mini:`meth (Arg₁: string):CborStoreT`
   *TBD*


:mini:`meth (Arg₁: string):CborStoreT(Arg₂: integer)`
   *TBD*


:mini:`meth (Arg₁: string):CborStoreT(Arg₂: integer, Arg₃: integer)`
   *TBD*


:mini:`meth (Path: string):StringStoreT: string_store`
   Opens an existing string store at :mini:`Path`.


:mini:`meth (Path: string):StringStoreT(NodeSize: integer): string_store`
   Creates a new string store at :mini:`Path` with node size :mini:`NodeSize` and default chunk size.


:mini:`meth (Path: string):StringStoreT(NodeSize: integer, ChunkSize: integer): string_store`
   Creates a new string store at :mini:`Path` with node size :mini:`NodeSize` and chunk size :mini:`ChunkSize`.


.. _type-string_index:

:mini:`type string_index`
   *TBD*


:mini:`meth (Arg₁: string_index):close`
   *TBD*


:mini:`meth (Arg₁: string_index):count`
   *TBD*


:mini:`meth (Arg₁: string_index):delete(Arg₂: string)`
   *TBD*


:mini:`meth (Arg₁: string_index):get(Arg₂: integer)`
   *TBD*


:mini:`meth (Arg₁: string_index):insert(Arg₂: string)`
   *TBD*


:mini:`meth (Arg₁: string_index):search(Arg₂: string)`
   *TBD*


.. _type-string_store:

:mini:`type string_store`
   A store for strings.


:mini:`meth (Store: string_store):close`
   Closes :mini:`Store`.


:mini:`meth (Store: string_store):get(Index: integer): string`
   Returns the entry at :mini:`Index` in :mini:`Store`.


:mini:`meth (Arg₁: string_store):read(Arg₂: integer)`
   *TBD*


:mini:`meth (Store: string_store):set(Index: integer, Value: string): string`
   Stores :mini:`Value` as the entry at :mini:`Index` in :mini:`Store` and returns :mini:`Value`.


:mini:`meth (Arg₁: string_store):write(Arg₂: integer)`
   *TBD*


.. _type-string_store_reader:

:mini:`type string_store_reader < stream`
   A stream for reading from a string store entry.


.. _type-string_store_writer:

:mini:`type string_store_writer < stream`
   A stream for writing to a string store entry.


