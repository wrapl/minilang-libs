.. include:: <isonum.txt>

.. include:: <isoamsa.txt>

.. include:: <isotech.txt>

fmt/yaml
========

.. rst-class:: mini-api

:mini:`def IsList: any`
   *TBD*


:mini:`fun yaml::escape(String: string): string`
   Escapes characters in :mini:`String`,  suitable for a YAML document.

   .. code-block:: mini

      import: yaml("fmt/yaml") :> module(yaml)
      yaml::escape("\'Hello\nworld!\'") :> "\'Hello\\nworld!\'"


:mini:`meth (Arg₁: string):Decode`
   *TBD*


