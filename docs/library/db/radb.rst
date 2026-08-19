.. include:: <isonum.txt>

.. include:: <isoamsa.txt>

.. include:: <isotech.txt>

db/radb
=======

.. rst-class:: mini-api

:mini:`type cborstore`
   *TBD*


:mini:`meth (Store: cborstore):count`
   *TBD*


:mini:`type fixedindex`
   *TBD*


:mini:`meth (Arg₁: fixedindex):search(Arg₂: address)`
   *TBD*


:mini:`type fixedstore`
   A store for strings.


:mini:`meth (Arg₁: stringstore):append(Arg₂: integer)`
   *TBD*


:mini:`meth (Arg₁: uuidindex):search(Arg₂: uuid)`
   *TBD*


:mini:`fun uuidindex::open(Arg₁: string)`
   *TBD*


:mini:`meth (Store: stringstore):get(Index: integer): string`
   Returns the entry at :mini:`Index` in :mini:`Store`.


:mini:`type uuidindex`
   *TBD*


:mini:`meth (Arg₁: fixedindex):close`
   *TBD*


:mini:`meth (Store: stringstore):close`
   Closes :mini:`Store`.


:mini:`meth (Store: fixedstore):close`
   Closes :mini:`Store`.


:mini:`meth (Arg₁: stringstore):remove(Arg₂: integer, Arg₃: integer)`
   *TBD*


:mini:`fun fixedindex::create(Arg₁: string)`
   *TBD*


:mini:`meth (Arg₁: stringstore):insert(Arg₂: integer, Arg₃: integer)`
   *TBD*


:mini:`meth (Store: stringstore):count`
   *TBD*


:mini:`meth (Arg₁: stringstore):search(Arg₂: integer, Arg₃: integer)`
   *TBD*


:mini:`meth (Arg₁: uuidindex):get(Arg₂: integer)`
   *TBD*


:mini:`meth (Arg₁: stringstore):read(Arg₂: integer)`
   *TBD*


:mini:`meth (Arg₁: stringindex):get(Arg₂: integer)`
   *TBD*


:mini:`type stringstorereader < stream`
   A stream for reading from a string store entry.


:mini:`meth (Arg₁: stringindex):insert(Arg₂: address)`
   *TBD*


:mini:`meth (Arg₁: stringstore):truncate(Arg₂: integer, Arg₃: integer)`
   *TBD*


:mini:`meth (Arg₁: stringindex):close`
   *TBD*


:mini:`fun stringindex::open(Arg₁: string)`
   *TBD*


:mini:`type stringindex`
   *TBD*


:mini:`meth (Arg₁: stringstore):write(Arg₂: integer)`
   *TBD*


:mini:`type stringstore`
   A store for strings.


:mini:`type stringstorewriter < stream`
   A stream for writing to a string store entry.


:mini:`fun fixedstore::create(Path: string, NodeSize: integer): string_store`
   Creates a new string store at :mini:`Path` with node size :mini:`NodeSize` and default chunk size.


:mini:`meth (Store: stringstore):set(Index: integer, Value: address): string`
   Stores :mini:`Value` as the entry at :mini:`Index` in :mini:`Store` and returns :mini:`Value`.


:mini:`fun cborstore::create(Arg₁: string, Arg₂: integer)`
   *TBD*


:mini:`fun uuidindex::create(Arg₁: string)`
   *TBD*


:mini:`meth (Arg₁: fixedindex):count`
   *TBD*


:mini:`meth (Arg₁: fixedindex):get(Arg₂: integer)`
   *TBD*


:mini:`meth (Store: fixedstore):count`
   *TBD*


:mini:`fun fixedindex::open(Arg₁: string)`
   *TBD*


:mini:`meth (Arg₁: stringindex):count`
   *TBD*


:mini:`meth (Arg₁: stringindex):delete(Arg₂: address)`
   *TBD*


:mini:`meth (Arg₁: stringindex):search(Arg₂: address)`
   *TBD*


:mini:`fun stringstore::open(Path: string): string_store`
   Opens an existing string store at :mini:`Path`.


:mini:`fun stringindex::create(Arg₁: string)`
   *TBD*


:mini:`meth (Arg₁: cborstore):set(Arg₂: integer, Arg₃: any)`
   *TBD*


:mini:`meth (Store: fixedstore):get(Index: integer): string`
   Returns the entry at :mini:`Index` in :mini:`Store`.


:mini:`fun cborstore::open(Arg₁: string)`
   *TBD*


:mini:`meth (Arg₁: fixedindex):delete(Arg₂: address)`
   *TBD*


:mini:`meth (Arg₁: fixedindex):insert(Arg₂: address)`
   *TBD*


:mini:`fun stringstore::create(Path: string, NodeSize: integer): string_store`
   Creates a new string store at :mini:`Path` with node size :mini:`NodeSize` and default chunk size.


:mini:`fun fixedstore::open(Path: string): string_store`
   Opens an existing string store at :mini:`Path`.


:mini:`meth (Arg₁: cborstore):get(Arg₂: integer)`
   *TBD*


:mini:`meth (Arg₁: cborstore):close`
   *TBD*


:mini:`meth (Arg₁: uuidindex):count`
   *TBD*


:mini:`meth (Arg₁: uuidindex):delete(Arg₂: uuid)`
   *TBD*


:mini:`meth (Arg₁: uuidindex):close`
   *TBD*


:mini:`meth (Arg₁: uuidindex):insert(Arg₂: uuid)`
   *TBD*


