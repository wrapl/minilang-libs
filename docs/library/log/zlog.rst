.. include:: <isonum.txt>

.. include:: <isoamsa.txt>

.. include:: <isotech.txt>

log/zlog
========

.. _type-category:

:mini:`type category`
   A logging category.


.. _fun-category:

:mini:`fun category(Name?: string): category`
   Returns a new logging category. If :mini:`Name` is omitted,  a name will be inferred from the calling function.


:mini:`meth (Category: category) :: (Level: string): logger`
   Returns the logger for :mini:`Category` with level :mini:`Level`.


.. _type-logger:

:mini:`type logger < function`
   A logger (category + level). Calling a logger generates a log entry with the supplied arguments.


