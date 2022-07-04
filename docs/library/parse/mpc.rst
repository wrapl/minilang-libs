.. include:: <isonum.txt>

.. include:: <isoamsa.txt>

.. include:: <isotech.txt>

parse/mpc
=========

:mini:`meth (Arg₁: file) % (Arg₂: parser::string)`
   *TBD*


:mini:`meth (Arg₁: file) % (Arg₂: parser::value)`
   *TBD*


:mini:`meth (Arg₁: integer) * (Arg₂: parser::string)`
   *TBD*


:mini:`meth (Arg₁: integer) * (Arg₂: parser::value)`
   *TBD*


.. _type-parser:

:mini:`type parser`
   Base type of parsers.


:mini:`meth (Arg₁: parser):copy`
   *TBD*


:mini:`meth (Arg₁: parser):define(Arg₂: parser)`
   *TBD*


:mini:`meth (Arg₁: parser):expect(Arg₂: string)`
   *TBD*


:mini:`meth (Arg₁: parser):predictive`
   *TBD*


.. _type-parser-named:

:mini:`type parser::named < parser::value`
   *TBD*


.. _type-parser-string:

:mini:`type parser::string < parser`
   A parser that returns a string.


:mini:`meth !(Arg₁: parser::string)`
   *TBD*


:mini:`meth $(Parser: parser::string): parser::value`
   Returns a new parser that wraps any string returned by :mini:`Parser` into a general value.


:mini:`meth (Parser: parser::string) $ (Fn: any): parser::value`
   Returns a new parser that returns :mini:`Fn(String)` for each string returned by :mini:`Parser`.


:mini:`meth *(Arg₁: parser::string)`
   *TBD*


:mini:`meth +(Arg₁: parser::string)`
   *TBD*


:mini:`meth (Arg₁: parser::string) -> (Arg₂: function)`
   *TBD*


:mini:`meth (Arg₁: parser::string) ->? (Arg₂: function)`
   *TBD*


:mini:`meth (Arg₁: parser::string) . (Arg₂: parser::string)`
   *TBD*


:mini:`meth (Arg₁: parser::string) . (Arg₂: string)`
   *TBD*


:mini:`meth (Arg₁: parser::string) ? (Arg₂: function)`
   *TBD*


:mini:`meth ^(Arg₁: parser::string)`
   *TBD*


:mini:`meth (Parser: parser::string):as(Name: string): parser::named`
   Returns a new named parser,  for use in :mini:`mpc::map`.


:mini:`meth (Arg₁: parser::string) | (Arg₂: parser::string)`
   *TBD*


:mini:`meth ~(Arg₁: parser::string)`
   *TBD*


.. _type-parser-value:

:mini:`type parser::value < parser`
   A parser that returns an arbitrary value.


:mini:`meth !(Arg₁: parser::value)`
   *TBD*


:mini:`meth *(Arg₁: parser::value)`
   *TBD*


:mini:`meth +(Arg₁: parser::value)`
   *TBD*


:mini:`meth (Arg₁: parser::value) -> (Arg₂: function)`
   *TBD*


:mini:`meth (Arg₁: parser::value) ->? (Arg₂: function)`
   *TBD*


:mini:`meth (Arg₁: parser::value) . (Arg₂: parser::value)`
   *TBD*


:mini:`meth (Arg₁: parser::value) ? (Arg₂: function)`
   *TBD*


:mini:`meth (Parser: parser::value):as(Name: string): parser::named`
   Returns a new named parser,  for use in :mini:`mpc::map`.


:mini:`meth (Arg₁: parser::value) | (Arg₂: parser::value)`
   *TBD*


:mini:`meth ~(Arg₁: parser::value)`
   *TBD*


.. _fun-any:

:mini:`fun any(Parserᵢ: parser|string|regex, ...): parser::value`
   Returns a new parser that matches any of :mini:`Parserᵢ`,  returning its value.


.. _fun-map:

:mini:`fun map(Parserᵢ: parser|string|regex, ...): parser::value`
   Returns a new parser that matches the sequence of parsers defined by :mini:`Parserᵢ`. The parser returns a map of the parsed values corresponding to any named parsers. Unnamed parsers are still matched but the values are discarded.


.. _fun-seq:

:mini:`fun seq(Parserᵢ: parser|string|regex, ...): parser::value`
   Returns a new parser that matches the sequence of parsers defined by :mini:`Parserᵢ`. The parser returns a list of the parsed values.


.. _fun-mpcregex:

:mini:`fun mpcregex(Arg₁: string)`
   *TBD*


:mini:`meth (Arg₁: string) % (Arg₂: parser::string)`
   *TBD*


:mini:`meth (Arg₁: string) % (Arg₂: parser::value)`
   *TBD*


:mini:`meth (Arg₁: string) . (Arg₂: parser::string)`
   *TBD*


:mini:`meth parser(Arg₁: string)`
   *TBD*


