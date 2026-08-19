.. include:: <isonum.txt>

.. include:: <isoamsa.txt>

.. include:: <isotech.txt>

fmt/csv
=======

.. rst-class:: mini-api

:mini:`meth (Csv: csv):read: list | nil`
   Returns the new row from :mini:`Csv` or :mini:`nil` if there are no more rows.


:mini:`meth csv(Path: stream): csv`
   Opens the file at :mini:`Path` for reading or writing as a CSV depending on the value of :mini:`Mode`.


:mini:`type csv`
   An open CSV file.


:mini:`meth (Csv: csv):write(Row: sequence): csv`
   Writes a row to :mini:`Csv`.


