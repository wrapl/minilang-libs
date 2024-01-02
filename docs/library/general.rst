.. include:: <isonum.txt>

.. include:: <isoamsa.txt>

.. include:: <isotech.txt>

general
=======

.. rst-class:: mini-api

:mini:`meth :UevT()`
   *TBD*


:mini:`meth (Arg₁: context):rectangle(Arg₂: real, Arg₃: real, Arg₄: real, Arg₅: real)`
   *TBD*


:mini:`meth (Arg₁: context):tree`
   *TBD*


:mini:`meth (Arg₁: fdbtransaction):commit`
   *TBD*


:mini:`type geometry`
   *TBD*


:mini:`type graph < object`
   *TBD*


:mini:`meth (Arg₁: fdbtransaction):set(Arg₂: address, Arg₃: address)`
   *TBD*


:mini:`meth (Arg₁: fdbtransaction):get(Arg₂: address)`
   *TBD*


:mini:`type fdbtransaction`
   *TBD*


:mini:`type graphdesc < enum`
   * :mini:`::Directed`
   * :mini:`::Undirected`


:mini:`type instance`
   *TBD*


:mini:`meth (Arg₁: graph):nodes`
   *TBD*


:mini:`meth (Arg₁: graph)[Arg₂: string]`
   *TBD*


:mini:`meth (Arg₁: node) --- (Arg₂: node)`
   *TBD*


:mini:`type eventhttp`
   *TBD*


:mini:`meth (Arg₁: string::buffer):append(Arg₂: node)`
   *TBD*


:mini:`meth (Arg₁: node):remove`
   *TBD*


:mini:`type object`
   *TBD*


:mini:`type eventbase`
   *TBD*


:mini:`type node < object`
   *TBD*


:mini:`meth (Arg₁: object):get(Arg₂: string)`
   *TBD*


:mini:`meth (Arg₁: object):set(Arg₂: string, Arg₃: string)`
   *TBD*


:mini:`meth (Arg₁: plugin):name`
   *TBD*


:mini:`meth (Arg₁: plugin):uri`
   *TBD*


:mini:`type pluginclass`
   *TBD*


:mini:`type port`
   *TBD*


:mini:`type prolog`
   *TBD*


:mini:`meth (Arg₁: prolog) :: (Arg₂: string)`
   *TBD*


:mini:`type query`
   *TBD*


:mini:`type rainstance`
   *TBD*


:mini:`meth (Arg₁: rainstance)[Arg₂: string]`
   *TBD*


:mini:`type ralistener`
   *TBD*


:mini:`type raschema`
   *TBD*


:mini:`type raschemaindex`
   *TBD*


:mini:`meth (Arg₁: string):FDBDatabaseT`
   *TBD*


:mini:`meth (Arg₁: string):GraphT`
   *TBD*


:mini:`meth (Arg₁: string):GraphT(Arg₂: graphdesc)`
   *TBD*


:mini:`type term < sequence`
   *TBD*


:mini:`meth (Arg₁: node):edges`
   *TBD*


:mini:`meth (Arg₁: rainstance):delete`
   *TBD*


:mini:`type plugin`
   *TBD*


:mini:`meth (Arg₁: ralistener):delete`
   *TBD*


:mini:`meth (Arg₁: node):out`
   *TBD*


:mini:`meth (Arg₁: node) --> (Arg₂: node)`
   *TBD*


:mini:`meth (Arg₁: string::buffer):append(Arg₂: edge)`
   *TBD*


:mini:`fun mldqlite(Arg₁: integer, Arg₂: string, Arg₃: string)`
   *TBD*


:mini:`meth (Arg₁: edge):remove`
   *TBD*


:mini:`meth (Arg₁: fdbdatabase):transaction`
   *TBD*


:mini:`meth (Arg₁: eventbase):http`
   *TBD*


:mini:`type fdbdatabase`
   *TBD*


:mini:`meth (Arg₁: eventbase):dispatch`
   *TBD*


:mini:`meth (Arg₁: eventbase):new(Arg₂: file)`
   *TBD*


:mini:`type event`
   *TBD*


:mini:`meth (Arg₁: string::buffer):append(Arg₂: graph)`
   *TBD*


:mini:`meth (Arg₁: term) . (Arg₂: term)`
   *TBD*


:mini:`type tree`
   *TBD*


:mini:`meth (Arg₁: tree):insert(Arg₂: geometry, Arg₃: any)`
   *TBD*


:mini:`type uev`
   *TBD*


:mini:`meth (Arg₁: uev):event(Arg₂: function)`
   *TBD*


:mini:`meth (Arg₁: uev):exit`
   *TBD*


:mini:`meth (Arg₁: uev):io(Arg₂: stream::fd, Arg₃: uevflags, Arg₄: function)`
   *TBD*


:mini:`meth (Arg₁: uev):run`
   *TBD*


:mini:`type context`
   *TBD*


:mini:`meth (Arg₁: node):in`
   *TBD*


:mini:`meth (Arg₁: dqlite):stop`
   *TBD*


:mini:`meth (Arg₁: dqlite):start`
   *TBD*


:mini:`type edge < object`
   *TBD*


:mini:`meth :FDBDatabaseT()`
   *TBD*


:mini:`fun getallplugins()`
   *TBD*


:mini:`meth (Arg₁: string::buffer):append(Arg₂: atom)`
   *TBD*


:mini:`meth (Arg₁: uev):timer(Arg₂: integer, Arg₃: function)`
   *TBD*


:mini:`meth (Arg₁: uev):timer(Arg₂: integer, Arg₃: integer, Arg₄: function)`
   *TBD*


:mini:`type uevevent`
   *TBD*


:mini:`meth (Arg₁: uevevent):start`
   *TBD*


:mini:`type atom`
   *TBD*


:mini:`type dqlite`
   *TBD*


:mini:`fun raschema()`
   *TBD*


:mini:`fun eventsleep()`
   *TBD*


:mini:`meth (Arg₁: uevevent):stop`
   *TBD*


:mini:`type uevflags < flags`
   * :mini:`::Err`
   * :mini:`::Read`
   * :mini:`::Write`
   * :mini:`::Pri`
   * :mini:`::Hup`
   * :mini:`::RdHup`
   * :mini:`::Edge`
   * :mini:`::Once`


:mini:`fun context()`
   *TBD*


:mini:`fun eventbasenew()`
   *TBD*


:mini:`type variable`
   *TBD*


:mini:`def Prolog: prolog`
   *TBD*


