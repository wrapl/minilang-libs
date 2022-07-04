.. include:: <isonum.txt>

.. include:: <isoamsa.txt>

.. include:: <isotech.txt>

db/postgres
===========

.. _type-connection:

:mini:`type connection`
   A connection to a Postgresql database.


:mini:`meth connection(Settings: map): connection`
   Connects to a Postgresql database with the supplied settings.


:mini:`meth connection(Name₁ is Value₁, ...): connection`
   Connects to a Postgresql database with the supplied settings.


:mini:`meth (Arg₁: connection):connect`
   *TBD*


:mini:`meth (Arg₁: connection):connected`
   *TBD*


:mini:`meth (Connection: connection):prepare(SQL: string): statement`
   Creates a prepared statement on :mini:`Connection`.


:mini:`meth (Connection: connection):query(SQL: string, Arg: any, ...): list[tuple] | nil`
   Executes :mini:`SQL` on :mini:`Connection`,  with arguments :mini:`Argᵢ` if supplied.
   Returns a list of tuples (for ``SELECT``,  etc) or :mini:`nil` for commands without results.


:mini:`meth (Arg₁: connection):reconnect(Arg₂: number)`
   *TBD*


.. _type-statement:

:mini:`type statement < function`
   A prepared statement. Calling a statement executes the prepared statement on the associated connection,  with the provided arguments (if any).


