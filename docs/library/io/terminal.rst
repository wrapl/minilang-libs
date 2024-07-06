.. include:: <isonum.txt>

.. include:: <isoamsa.txt>

.. include:: <isotech.txt>

io/terminal
===========

.. rst-class:: mini-api

:mini:`type attrs`
   *TBD*


:mini:`meth (Arg₁: attrs):get(Arg₂: cflag)`
   *TBD*


:mini:`meth (Arg₁: attrs):get(Arg₂: iflag)`
   *TBD*


:mini:`meth (Arg₁: attrs):get(Arg₂: lflag)`
   *TBD*


:mini:`meth (Arg₁: attrs):get(Arg₂: oflag)`
   *TBD*


:mini:`meth (Arg₁: attrs):set(Arg₂: cflag, Arg₃: boolean)`
   *TBD*


:mini:`meth (Arg₁: attrs):set(Arg₂: iflag, Arg₃: boolean)`
   *TBD*


:mini:`meth (Arg₁: attrs):set(Arg₂: lflag, Arg₃: boolean)`
   *TBD*


:mini:`meth (Arg₁: attrs):set(Arg₂: oflag, Arg₃: boolean)`
   *TBD*


:mini:`meth (Arg₁: attrs):setraw`
   *TBD*


:mini:`type cflag < enum`
   * :mini:`::CSIZE`
   * :mini:`::CS5`
   * :mini:`::CS6`
   * :mini:`::CS7`
   * :mini:`::CS8`
   * :mini:`::CSTOPB`
   * :mini:`::CREAD`
   * :mini:`::PARENB`
   * :mini:`::PARODD`
   * :mini:`::HUPCL`
   * :mini:`::CLOCAL`


:mini:`type iflag < enum`
   * :mini:`::IGNBRK`
   * :mini:`::BRKINT`
   * :mini:`::IGNPAR`
   * :mini:`::PARMRK`
   * :mini:`::INPCK`
   * :mini:`::ISTRIP`
   * :mini:`::INLCR`
   * :mini:`::IGNCR`
   * :mini:`::ICRNL`
   * :mini:`::IUCLC`
   * :mini:`::IXON`
   * :mini:`::IXANY`
   * :mini:`::IXOFF`
   * :mini:`::IMAXBEL`
   * :mini:`::IUTF8`


:mini:`type lflag < enum`
   * :mini:`::ISIG`
   * :mini:`::ICANON`
   * :mini:`::XCASE`
   * :mini:`::ECHO`
   * :mini:`::ECHOE`
   * :mini:`::ECHOK`
   * :mini:`::ECHONL`
   * :mini:`::NOFLSH`
   * :mini:`::TOSTOP`
   * :mini:`::ECHOCTL`
   * :mini:`::ECHOPRT`
   * :mini:`::ECHOKE`
   * :mini:`::FLUSHO`
   * :mini:`::PENDIN`
   * :mini:`::IEXTEN`
   * :mini:`::EXTPROC`


:mini:`type oflag < enum`
   * :mini:`::OPOST`
   * :mini:`::OLCUC`
   * :mini:`::ONLCR`
   * :mini:`::OCRNL`
   * :mini:`::ONOCR`
   * :mini:`::ONLRET`
   * :mini:`::OFILL`
   * :mini:`::OFDEL`
   * :mini:`::NLDLY`
   * :mini:`::NL0`
   * :mini:`::NL1`
   * :mini:`::CRDLY`
   * :mini:`::CR0`
   * :mini:`::CR1`
   * :mini:`::CR2`
   * :mini:`::CR3`
   * :mini:`::TABDLY`
   * :mini:`::TAB0`
   * :mini:`::TAB1`
   * :mini:`::TAB2`
   * :mini:`::TAB3`
   * :mini:`::BSDLY`
   * :mini:`::BS0`
   * :mini:`::BS1`
   * :mini:`::FFDLY`
   * :mini:`::FF0`
   * :mini:`::FF1`
   * :mini:`::VTDLY`
   * :mini:`::VT0`
   * :mini:`::VT1`
   * :mini:`::XTABS`


:mini:`type terminal < stream::fd`
   *TBD*


:mini:`meth (Arg₁: terminal):attrs`
   *TBD*


:mini:`meth (Arg₁: terminal):attrs(Arg₂: attrs, Arg₃: integer)`
   *TBD*


:mini:`meth (Arg₁: terminal):winsize`
   *TBD*


