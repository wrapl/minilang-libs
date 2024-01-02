.. include:: <isonum.txt>

.. include:: <isoamsa.txt>

.. include:: <isotech.txt>

fmt/csv
=======

.. rst-class:: mini-api

:mini:`type csv`
   An open CSV file.


:mini:`meth csv(Path: string, Mode: string): csv`
   Opens the file at :mini:`Path` for reading or writing as a CSV depending on the value of :mini:`Mode`.


:mini:`meth (Csv: csv):close`
   Closes :mini:`Csv`.


:mini:`meth (Csv: csv):read: list | nil`
   Returns the new row from :mini:`Csv` or :mini:`nil` if there are no more rows.


:mini:`meth (Csv: csv):write(Row: list): csv`
   Writes a row to :mini:`Csv`.


