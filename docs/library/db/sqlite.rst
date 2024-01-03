.. include:: <isonum.txt>

.. include:: <isoamsa.txt>

.. include:: <isotech.txt>

db/sqlite
=========

.. rst-class:: mini-api

:mini:`type sqlite`
   *TBD*


:mini:`fun sqlite(Arg₁: string, Arg₂: sqlite::open): sqlite`
   *TBD*


:mini:`meth (Arg₁: sqlite):close`
   *TBD*


:mini:`meth (Arg₁: sqlite):execute(Arg₂: string, ...)`
   *TBD*


:mini:`meth (Arg₁: sqlite):statement(Arg₂: string)`
   *TBD*


:mini:`type sqlite::open < flags`
   * :mini:`::READONLY`
   * :mini:`::READWRITE`
   * :mini:`::CREATE`
   * :mini:`::DELETEONCLOSE`
   * :mini:`::EXCLUSIVE`
   * :mini:`::AUTOPROXY`
   * :mini:`::URI`
   * :mini:`::MEMORY`
   * :mini:`::MAIN_DB`
   * :mini:`::TEMP_DB`
   * :mini:`::TRANSIENT_DB`
   * :mini:`::MAIN_JOURNAL`
   * :mini:`::TEMP_JOURNAL`
   * :mini:`::SUBJOURNAL`
   * :mini:`::SUPER_JOURNAL`
   * :mini:`::NOMUTEX`
   * :mini:`::FULLMUTEX`
   * :mini:`::SHAREDCACHE`
   * :mini:`::PRIVATECACHE`
   * :mini:`::WAL`
   * :mini:`::NOFOLLOW`
   * :mini:`::EXRESCODE`


:mini:`type sqlite::stmt < sequence`
   *TBD*


