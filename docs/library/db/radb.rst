.. include:: <isonum.txt>

.. include:: <isoamsa.txt>

.. include:: <isotech.txt>

db/radb
=======

.. _type-cbor_store:

:mini:`type cbor_store`
   *TBD*


:mini:`meth (Arg₁: cbor_store):close`
   *TBD*


:mini:`meth (Store: cbor_store):count`
   *TBD*


:mini:`meth (Arg₁: cbor_store):get(Arg₂: integer)`
   *TBD*


:mini:`meth (Arg₁: cbor_store):set(Arg₂: integer, Arg₃: any)`
   *TBD*


.. _type-fixed_store:

:mini:`type fixed_store`
   A store for strings.


:mini:`meth (Store: fixed_store):close`
   Closes :mini:`Store`.


:mini:`meth (Store: fixed_store):count`
   *TBD*


:mini:`meth (Store: fixed_store):get(Index: integer): string`
   Returns the entry at :mini:`Index` in :mini:`Store`.


:mini:`meth (Arg₁: string_store):append(Arg₂: integer)`
   *TBD*


.. _fun-cborstorecreate:

:mini:`fun cborstorecreate(Arg₁: string, Arg₂: integer)`
   *TBD*


.. _fun-cborstoreopen:

:mini:`fun cborstoreopen(Arg₁: string)`
   *TBD*


.. _fun-fixedstorecreate:

:mini:`fun fixedstorecreate(Path: string, NodeSize: integer): string_store`
   Creates a new string store at :mini:`Path` with node size :mini:`NodeSize` and default chunk size.


.. _fun-fixedstoreopen:

:mini:`fun fixedstoreopen(Path: string): string_store`
   Opens an existing string store at :mini:`Path`.


.. _fun-stringindexcreate:

:mini:`fun stringindexcreate(Arg₁: string)`
   *TBD*


.. _fun-stringindexopen:

:mini:`fun stringindexopen(Arg₁: string)`
   *TBD*


.. _fun-stringstorecreate:

:mini:`fun stringstorecreate(Path: string, NodeSize: integer): string_store`
   Creates a new string store at :mini:`Path` with node size :mini:`NodeSize` and default chunk size.


.. _fun-stringstoreopen:

:mini:`fun stringstoreopen(Path: string): string_store`
   Opens an existing string store at :mini:`Path`.


.. _fun-uuidindexcreate:

:mini:`fun uuidindexcreate(Arg₁: string)`
   *TBD*


.. _fun-uuidindexopen:

:mini:`fun uuidindexopen(Arg₁: string)`
   *TBD*


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


:mini:`meth (Store: string_store):count`
   *TBD*


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


.. _type-u_u_i_d_index:

:mini:`type u_u_i_d_index`
   *TBD*


:mini:`meth (Arg₁: u_u_i_d_index):close`
   *TBD*


:mini:`meth (Arg₁: u_u_i_d_index):count`
   *TBD*


:mini:`meth (Arg₁: u_u_i_d_index):delete(Arg₂: uuid)`
   *TBD*


:mini:`meth (Arg₁: u_u_i_d_index):get(Arg₂: integer)`
   *TBD*


:mini:`meth (Arg₁: u_u_i_d_index):insert(Arg₂: uuid)`
   *TBD*


:mini:`meth (Arg₁: u_u_i_d_index):search(Arg₂: uuid)`
   *TBD*


