/* ANSI-C code produced by gperf version 3.1 */
/* Command-line: gperf -LANSI-C -C -c -t -n -KName -Zentity -Hentity_hash -Nentity_lookup -r -m 50 --null-strings entities.lst  */
/* Computed positions: -k'1-8,10,13,16,18' */

#if !((' ' == 32) && ('!' == 33) && ('"' == 34) && ('#' == 35) \
      && ('%' == 37) && ('&' == 38) && ('\'' == 39) && ('(' == 40) \
      && (')' == 41) && ('*' == 42) && ('+' == 43) && (',' == 44) \
      && ('-' == 45) && ('.' == 46) && ('/' == 47) && ('0' == 48) \
      && ('1' == 49) && ('2' == 50) && ('3' == 51) && ('4' == 52) \
      && ('5' == 53) && ('6' == 54) && ('7' == 55) && ('8' == 56) \
      && ('9' == 57) && (':' == 58) && (';' == 59) && ('<' == 60) \
      && ('=' == 61) && ('>' == 62) && ('?' == 63) && ('A' == 65) \
      && ('B' == 66) && ('C' == 67) && ('D' == 68) && ('E' == 69) \
      && ('F' == 70) && ('G' == 71) && ('H' == 72) && ('I' == 73) \
      && ('J' == 74) && ('K' == 75) && ('L' == 76) && ('M' == 77) \
      && ('N' == 78) && ('O' == 79) && ('P' == 80) && ('Q' == 81) \
      && ('R' == 82) && ('S' == 83) && ('T' == 84) && ('U' == 85) \
      && ('V' == 86) && ('W' == 87) && ('X' == 88) && ('Y' == 89) \
      && ('Z' == 90) && ('[' == 91) && ('\\' == 92) && (']' == 93) \
      && ('^' == 94) && ('_' == 95) && ('a' == 97) && ('b' == 98) \
      && ('c' == 99) && ('d' == 100) && ('e' == 101) && ('f' == 102) \
      && ('g' == 103) && ('h' == 104) && ('i' == 105) && ('j' == 106) \
      && ('k' == 107) && ('l' == 108) && ('m' == 109) && ('n' == 110) \
      && ('o' == 111) && ('p' == 112) && ('q' == 113) && ('r' == 114) \
      && ('s' == 115) && ('t' == 116) && ('u' == 117) && ('v' == 118) \
      && ('w' == 119) && ('x' == 120) && ('y' == 121) && ('z' == 122) \
      && ('{' == 123) && ('|' == 124) && ('}' == 125) && ('~' == 126))
/* The character set is not based on ISO-646.  */
#error "gperf generated tables don't work with this execution character set. Please report a bug to <bug-gperf@gnu.org>."
#endif

#line 1 "entities.lst"
struct entity_t {const char *Name; const unsigned char Chars[8];};

#define TOTAL_KEYWORDS 2231
#define MIN_WORD_LENGTH 2
#define MAX_WORD_LENGTH 32
#define MIN_HASH_VALUE 24
#define MAX_HASH_VALUE 12607
/* maximum key range = 12584, duplicates = 0 */

#ifdef __GNUC__
__inline
#else
#ifdef __cplusplus
inline
#endif
#endif
static unsigned int
entity_hash (register const char *str, register size_t len)
{
  static const unsigned short asso_values[] =
    {
      12608, 12608, 12608, 12608, 12608, 12608, 12608, 12608, 12608, 12608,
      12608, 12608, 12608, 12608, 12608, 12608, 12608, 12608, 12608, 12608,
      12608, 12608, 12608, 12608, 12608, 12608, 12608, 12608, 12608, 12608,
      12608, 12608, 12608, 12608, 12608, 12608, 12608, 12608, 12608, 12608,
      12608, 12608, 12608, 12608, 12608, 12608, 12608, 12608, 12608, 12608,
      12608, 12608,    15,    38,    18,    28,    20, 12608,    27,  1158,
         12,    98,    13, 12608,  2223,  2251,   501,    15,  1070,   209,
       2181,    89,  1023,   233,   625,    18,   625,  1513,  1751,  2390,
        487,   363,   226,   174,   338,   813,   680,   345,    46,   371,
        252,   552,  1366,  1028,    26,   676,   982,  2500,   293,  1050,
        653,   426,    17,    28,   153,   826,    69,  3779,   659,  1933,
         16,    25,    42,    24,    14,    18,    12,    21,    75,   198,
        757,    13,  1570,   129,  3744,  3431,   394,  2771,   886,  3203,
       4377,   369,    61,  3291,   379,   167, 12608, 12608, 12608, 12608,
      12608, 12608, 12608, 12608, 12608, 12608, 12608, 12608, 12608, 12608,
      12608, 12608, 12608, 12608, 12608, 12608, 12608, 12608, 12608, 12608,
      12608, 12608, 12608, 12608, 12608, 12608, 12608, 12608, 12608, 12608,
      12608, 12608, 12608, 12608, 12608, 12608, 12608, 12608, 12608, 12608,
      12608, 12608, 12608, 12608, 12608, 12608, 12608, 12608, 12608, 12608,
      12608, 12608, 12608, 12608, 12608, 12608, 12608, 12608, 12608, 12608,
      12608, 12608, 12608, 12608, 12608, 12608, 12608, 12608, 12608, 12608,
      12608, 12608, 12608, 12608, 12608, 12608, 12608, 12608, 12608, 12608,
      12608, 12608, 12608, 12608, 12608, 12608, 12608, 12608, 12608, 12608,
      12608, 12608, 12608, 12608, 12608, 12608, 12608, 12608, 12608, 12608,
      12608, 12608, 12608, 12608, 12608, 12608, 12608, 12608, 12608, 12608,
      12608, 12608, 12608, 12608, 12608, 12608, 12608, 12608, 12608, 12608,
      12608, 12608, 12608, 12608, 12608, 12608, 12608, 12608, 12608
    };
  register unsigned int hval = 0;

  switch (len)
    {
      default:
        hval += asso_values[(unsigned char)str[17]];
      /*FALLTHROUGH*/
      case 17:
      case 16:
        hval += asso_values[(unsigned char)str[15]];
      /*FALLTHROUGH*/
      case 15:
      case 14:
      case 13:
        hval += asso_values[(unsigned char)str[12]];
      /*FALLTHROUGH*/
      case 12:
      case 11:
      case 10:
        hval += asso_values[(unsigned char)str[9]];
      /*FALLTHROUGH*/
      case 9:
      case 8:
        hval += asso_values[(unsigned char)str[7]];
      /*FALLTHROUGH*/
      case 7:
        hval += asso_values[(unsigned char)str[6]+1];
      /*FALLTHROUGH*/
      case 6:
        hval += asso_values[(unsigned char)str[5]+2];
      /*FALLTHROUGH*/
      case 5:
        hval += asso_values[(unsigned char)str[4]+3];
      /*FALLTHROUGH*/
      case 4:
        hval += asso_values[(unsigned char)str[3]+5];
      /*FALLTHROUGH*/
      case 3:
        hval += asso_values[(unsigned char)str[2]+1];
      /*FALLTHROUGH*/
      case 2:
        hval += asso_values[(unsigned char)str[1]];
      /*FALLTHROUGH*/
      case 1:
        hval += asso_values[(unsigned char)str[0]+13];
        break;
    }
  return hval;
}

const struct entity_t *
entity_lookup (register const char *str, register size_t len)
{
  static const struct entity_t wordlist[] =
    {
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 1137 "entities.lst"
      {"gt",{62,0,}},
#line 1392 "entities.lst"
      {"lt",{60,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 1138 "entities.lst"
      {"gt;",{62,0,}},
#line 1393 "entities.lst"
      {"lt;",{60,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 650 "entities.lst"
      {"af;",{226,129,161,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 1116 "entities.lst"
      {"gg;",{226,137,171,0,}},
#line 1334 "entities.lst"
      {"lg;",{226,137,182,0,}},
#line 1002 "entities.lst"
      {"eg;",{226,170,154,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 686 "entities.lst"
      {"ap;",{226,137,136,0,}},
      {(char*)0},
#line 1402 "entities.lst"
      {"ltri;",{226,151,131,0,}},
      {(char*)0}, {(char*)0},
#line 1047 "entities.lst"
      {"euml",{195,171,0,}},
#line 1020 "entities.lst"
      {"ensp;",{226,128,130,0,}},
#line 702 "entities.lst"
      {"auml",{195,164,0,}},
#line 1049 "entities.lst"
      {"euro;",{226,130,172,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 980 "entities.lst"
      {"dtri;",{226,150,191,0,}},
      {(char*)0}, {(char*)0},
#line 1388 "entities.lst"
      {"lsqb;",{91,0,}},
#line 2180 "entities.lst"
      {"wr;",{226,137,128,0,}},
#line 1048 "entities.lst"
      {"euml;",{195,171,0,}},
      {(char*)0},
#line 703 "entities.lst"
      {"auml;",{195,164,0,}},
#line 626 "entities.lst"
      {"Yuml;",{197,184,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 818 "entities.lst"
      {"bump;",{226,137,142,0,}},
#line 1026 "entities.lst"
      {"epsi;",{206,181,0,}},
      {(char*)0},
#line 1232 "entities.lst"
      {"it;",{226,129,162,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1207 "entities.lst"
      {"in;",{226,136,136,0,}},
#line 1145 "entities.lst"
      {"gtrarr;",{226,165,184,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 756 "entities.lst"
      {"bnot;",{226,140,144,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 2179 "entities.lst"
      {"wp;",{226,132,152,0,}},
#line 1069 "entities.lst"
      {"fork;",{226,139,148,0,}},
#line 873 "entities.lst"
      {"comp;",{226,136,129,0,}},
#line 1003 "entities.lst"
      {"egrave",{195,168,0,}},
      {(char*)0},
#line 652 "entities.lst"
      {"agrave",{195,160,0,}},
#line 977 "entities.lst"
      {"dsol;",{226,167,182,0,}},
#line 813 "entities.lst"
      {"bsol;",{92,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1134 "entities.lst"
      {"gsim;",{226,137,179,0,}},
#line 1385 "entities.lst"
      {"lsim;",{226,137,178,0,}},
#line 1043 "entities.lst"
      {"esim;",{226,137,130,0,}},
      {(char*)0},
#line 1004 "entities.lst"
      {"egrave;",{195,168,0,}},
#line 1068 "entities.lst"
      {"forall;",{226,136,128,0,}},
#line 653 "entities.lst"
      {"agrave;",{195,160,0,}},
#line 1128 "entities.lst"
      {"gneq;",{226,170,136,0,}},
#line 1353 "entities.lst"
      {"lneq;",{226,170,135,0,}},
#line 759 "entities.lst"
      {"bottom;",{226,138,165,0,}},
#line 1235 "entities.lst"
      {"iuml",{195,175,0,}},
      {(char*)0}, {(char*)0},
#line 811 "entities.lst"
      {"bsim;",{226,136,189,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 906 "entities.lst"
      {"curarr;",{226,134,183,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 1236 "entities.lst"
      {"iuml;",{195,175,0,}},
      {(char*)0},
#line 1221 "entities.lst"
      {"iota;",{206,185,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 1594 "entities.lst"
      {"nu;",{206,189,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 890 "entities.lst"
      {"csup;",{226,171,144,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 1530 "entities.lst"
      {"not",{194,172,0,}},
#line 888 "entities.lst"
      {"csub;",{226,171,143,0,}},
#line 700 "entities.lst"
      {"atilde",{195,163,0,}},
      {(char*)0},
#line 1192 "entities.lst"
      {"igrave",{195,172,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 805 "entities.lst"
      {"bprime;",{226,128,181,0,}},
      {(char*)0}, {(char*)0},
#line 694 "entities.lst"
      {"aring",{195,165,0,}},
      {(char*)0},
#line 1034 "entities.lst"
      {"equals;",{61,0,}},
#line 701 "entities.lst"
      {"atilde;",{195,163,0,}},
      {(char*)0},
#line 1193 "entities.lst"
      {"igrave;",{195,172,0,}},
      {(char*)0},
#line 1226 "entities.lst"
      {"isin;",{226,136,136,0,}},
      {(char*)0},
#line 1028 "entities.lst"
      {"epsiv;",{207,181,0,}},
#line 1130 "entities.lst"
      {"gnsim;",{226,139,167,0,}},
#line 1355 "entities.lst"
      {"lnsim;",{226,139,166,0,}},
#line 1365 "entities.lst"
      {"lopar;",{226,166,133,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 798 "entities.lst"
      {"boxv;",{226,148,130,0,}},
#line 1031 "entities.lst"
      {"eqsim;",{226,137,130,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1070 "entities.lst"
      {"forkv;",{226,171,153,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 904 "entities.lst"
      {"cupor;",{226,169,133,0,}},
#line 879 "entities.lst"
      {"conint;",{226,136,174,0,}},
#line 895 "entities.lst"
      {"cuepr;",{226,139,158,0,}},
      {(char*)0},
#line 963 "entities.lst"
      {"doteqdot;",{226,137,145,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1129 "entities.lst"
      {"gneqq;",{226,137,169,0,}},
#line 1354 "entities.lst"
      {"lneqq;",{226,137,168,0,}},
      {(char*)0},
#line 1093 "entities.lst"
      {"gE;",{226,137,167,0,}},
#line 1259 "entities.lst"
      {"lE;",{226,137,166,0,}},
      {(char*)0},
#line 1136 "entities.lst"
      {"gsiml;",{226,170,144,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1036 "entities.lst"
      {"equiv;",{226,137,161,0,}},
      {(char*)0}, {(char*)0},
#line 1565 "entities.lst"
      {"nsim;",{226,137,129,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 1233 "entities.lst"
      {"itilde;",{196,169,0,}},
#line 962 "entities.lst"
      {"doteq;",{226,137,144,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 1580 "entities.lst"
      {"nsup;",{226,138,133,0,}},
#line 1209 "entities.lst"
      {"infin;",{226,136,158,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 1497 "entities.lst"
      {"ngeq;",{226,137,177,0,}},
#line 1572 "entities.lst"
      {"nsub;",{226,138,132,0,}},
      {(char*)0}, {(char*)0},
#line 821 "entities.lst"
      {"bumpeq;",{226,137,143,0,}},
#line 667 "entities.lst"
      {"ange;",{226,166,164,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1549 "entities.lst"
      {"npre;",{226,170,175,204,184,0,}},
      {(char*)0},
#line 1222 "entities.lst"
      {"iprod;",{226,168,188,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1387 "entities.lst"
      {"lsimg;",{226,170,143,0,}},
      {(char*)0}, {(char*)0},
#line 695 "entities.lst"
      {"aring;",{195,165,0,}},
#line 316 "entities.lst"
      {"Mu;",{206,156,0,}},
#line 1534 "entities.lst"
      {"notindot;",{226,139,181,204,184,0,}},
#line 158 "entities.lst"
      {"Euml",{195,139,0,}},
      {(char*)0}, {(char*)0},
#line 1587 "entities.lst"
      {"ntilde",{195,177,0,}},
#line 1231 "entities.lst"
      {"isinv;",{226,136,136,0,}},
#line 1596 "entities.lst"
      {"numero;",{226,132,150,0,}},
      {(char*)0},
#line 1398 "entities.lst"
      {"ltimes;",{226,139,137,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 159 "entities.lst"
      {"Euml;",{195,139,0,}},
      {(char*)0},
#line 1588 "entities.lst"
      {"ntilde;",{195,177,0,}},
#line 669 "entities.lst"
      {"angmsd;",{226,136,161,0,}},
      {(char*)0},
#line 1568 "entities.lst"
      {"nsmid;",{226,136,164,0,}},
      {(char*)0},
#line 1569 "entities.lst"
      {"nspar;",{226,136,166,0,}},
#line 799 "entities.lst"
      {"boxvH;",{226,149,170,0,}},
      {(char*)0},
#line 1403 "entities.lst"
      {"ltrie;",{226,138,180,0,}},
#line 804 "entities.lst"
      {"boxvr;",{226,148,156,0,}},
      {(char*)0},
#line 1532 "entities.lst"
      {"notin;",{226,136,137,0,}},
#line 1214 "entities.lst"
      {"integers;",{226,132,164,0,}},
#line 803 "entities.lst"
      {"boxvl;",{226,148,164,0,}},
#line 1533 "entities.lst"
      {"notinE;",{226,139,185,204,184,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 1501 "entities.lst"
      {"ngsim;",{226,137,181,0,}},
#line 1021 "entities.lst"
      {"eogon;",{196,153,0,}},
      {(char*)0},
#line 684 "entities.lst"
      {"aogon;",{196,133,0,}},
      {(char*)0},
#line 143 "entities.lst"
      {"Egrave",{195,136,0,}},
#line 1586 "entities.lst"
      {"ntgl;",{226,137,185,0,}},
#line 881 "entities.lst"
      {"coprod;",{226,136,144,0,}},
      {(char*)0},
#line 820 "entities.lst"
      {"bumpe;",{226,137,143,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 156 "entities.lst"
      {"Esim;",{226,169,179,0,}},
      {(char*)0},
#line 144 "entities.lst"
      {"Egrave;",{195,136,0,}},
      {(char*)0},
#line 1035 "entities.lst"
      {"equest;",{226,137,159,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 1229 "entities.lst"
      {"isins;",{226,139,180,0,}},
#line 588 "entities.lst"
      {"Uuml",{195,156,0,}},
#line 1125 "entities.lst"
      {"gnap;",{226,170,138,0,}},
#line 1350 "entities.lst"
      {"lnap;",{226,170,137,0,}},
      {(char*)0}, {(char*)0},
#line 1498 "entities.lst"
      {"ngeqq;",{226,137,167,204,184,0,}},
      {(char*)0}, {(char*)0},
#line 191 "entities.lst"
      {"Gt;",{226,137,171,0,}},
      {(char*)0},
#line 1135 "entities.lst"
      {"gsime;",{226,170,142,0,}},
#line 1386 "entities.lst"
      {"lsime;",{226,170,141,0,}},
      {(char*)0},
#line 589 "entities.lst"
      {"Uuml;",{195,156,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 1611 "entities.lst"
      {"nvsim;",{226,136,188,226,131,146,0,}},
#line 1550 "entities.lst"
      {"nprec;",{226,138,128,0,}},
      {(char*)0}, {(char*)0},
#line 583 "entities.lst"
      {"Upsi;",{207,146,0,}},
#line 812 "entities.lst"
      {"bsime;",{226,139,141,0,}},
#line 181 "entities.lst"
      {"Gg;",{226,139,153,0,}},
      {(char*)0}, {(char*)0},
#line 1451 "entities.lst"
      {"nGtv;",{226,137,171,204,184,0,}},
      {(char*)0},
#line 1603 "entities.lst"
      {"nvgt;",{62,226,131,146,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1219 "entities.lst"
      {"iogon;",{196,175,0,}},
#line 2181 "entities.lst"
      {"wreath;",{226,137,128,0,}},
#line 1503 "entities.lst"
      {"ngtr;",{226,137,175,0,}},
      {(char*)0},
#line 715 "entities.lst"
      {"bbrk;",{226,142,181,0,}},
      {(char*)0},
#line 1223 "entities.lst"
      {"iquest",{194,191,0,}},
      {(char*)0},
#line 307 "entities.lst"
      {"Lt;",{226,137,170,0,}},
      {(char*)0},
#line 561 "entities.lst"
      {"Ugrave",{195,153,0,}},
#line 1287 "entities.lst"
      {"lbrace;",{123,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 1224 "entities.lst"
      {"iquest;",{194,191,0,}},
      {(char*)0},
#line 891 "entities.lst"
      {"csupe;",{226,171,146,0,}},
      {(char*)0},
#line 562 "entities.lst"
      {"Ugrave;",{195,153,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1567 "entities.lst"
      {"nsimeq;",{226,137,132,0,}},
#line 889 "entities.lst"
      {"csube;",{226,171,145,0,}},
#line 764 "entities.lst"
      {"boxDr;",{226,149,147,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 763 "entities.lst"
      {"boxDl;",{226,149,150,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 2233 "entities.lst"
      {"zwnj;",{226,128,140,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 773 "entities.lst"
      {"boxUr;",{226,149,153,0,}},
#line 1172 "entities.lst"
      {"hookleftarrow;",{226,134,169,0,}},
#line 806 "entities.lst"
      {"breve;",{203,152,0,}},
      {(char*)0},
#line 772 "entities.lst"
      {"boxUl;",{226,149,156,0,}},
#line 1602 "entities.lst"
      {"nvge;",{226,137,165,226,131,146,0,}},
#line 2219 "entities.lst"
      {"yuml",{195,191,0,}},
      {(char*)0},
#line 1506 "entities.lst"
      {"nhpar;",{226,171,178,0,}},
      {(char*)0}, {(char*)0},
#line 1099 "entities.lst"
      {"gbreve;",{196,159,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 639 "entities.lst"
      {"abreve;",{196,131,0,}},
#line 1103 "entities.lst"
      {"ge;",{226,137,165,0,}},
#line 1303 "entities.lst"
      {"le;",{226,137,164,0,}},
#line 999 "entities.lst"
      {"ee;",{226,133,135,0,}},
#line 2220 "entities.lst"
      {"yuml;",{195,191,0,}},
      {(char*)0},
#line 1471 "entities.lst"
      {"nbsp",{194,160,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 668 "entities.lst"
      {"angle;",{226,136,160,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 152 "entities.lst"
      {"Equal;",{226,169,181,0,}},
#line 587 "entities.lst"
      {"Utilde;",{197,168,0,}},
      {(char*)0},
#line 1472 "entities.lst"
      {"nbsp;",{194,160,0,}},
      {(char*)0},
#line 1756 "entities.lst"
      {"quot",{34,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 912 "entities.lst"
      {"curren",{194,164,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 848 "entities.lst"
      {"check;",{226,156,147,0,}},
      {(char*)0},
#line 1566 "entities.lst"
      {"nsime;",{226,137,132,0,}},
      {(char*)0},
#line 1757 "entities.lst"
      {"quot;",{34,0,}},
      {(char*)0},
#line 882 "entities.lst"
      {"copy",{194,169,0,}},
#line 913 "entities.lst"
      {"curren;",{194,164,0,}},
#line 1113 "entities.lst"
      {"gesl;",{226,139,155,239,184,128,0,}},
      {(char*)0}, {(char*)0},
#line 1578 "entities.lst"
      {"nsucc;",{226,138,129,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1582 "entities.lst"
      {"nsupe;",{226,138,137,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 883 "entities.lst"
      {"copy;",{194,169,0,}},
#line 1599 "entities.lst"
      {"nvHarr;",{226,164,132,0,}},
      {(char*)0},
#line 1574 "entities.lst"
      {"nsube;",{226,138,136,0,}},
#line 725 "entities.lst"
      {"beta;",{206,178,0,}},
      {(char*)0}, {(char*)0},
#line 633 "entities.lst"
      {"Zeta;",{206,150,0,}},
#line 843 "entities.lst"
      {"cent",{194,162,0,}},
      {(char*)0},
#line 1072 "entities.lst"
      {"frac12",{194,189,0,}},
      {(char*)0}, {(char*)0},
#line 1075 "entities.lst"
      {"frac14",{194,188,0,}},
#line 568 "entities.lst"
      {"Union;",{226,139,131,0,}},
      {(char*)0},
#line 1082 "entities.lst"
      {"frac34",{194,190,0,}},
      {(char*)0},
#line 1356 "entities.lst"
      {"loang;",{226,159,172,0,}},
      {(char*)0}, {(char*)0},
#line 844 "entities.lst"
      {"cent;",{194,162,0,}},
#line 1073 "entities.lst"
      {"frac12;",{194,189,0,}},
      {(char*)0}, {(char*)0},
#line 1076 "entities.lst"
      {"frac14;",{194,188,0,}},
      {(char*)0},
#line 1078 "entities.lst"
      {"frac16;",{226,133,153,0,}},
#line 1083 "entities.lst"
      {"frac34;",{194,190,0,}},
      {(char*)0},
#line 662 "entities.lst"
      {"andand;",{226,169,149,0,}},
      {(char*)0},
#line 1087 "entities.lst"
      {"frac56;",{226,133,154,0,}},
#line 1600 "entities.lst"
      {"nvap;",{226,137,141,226,131,146,0,}},
#line 1079 "entities.lst"
      {"frac18;",{226,133,155,0,}},
#line 1077 "entities.lst"
      {"frac15;",{226,133,149,0,}},
      {(char*)0},
#line 1085 "entities.lst"
      {"frac38;",{226,133,156,0,}},
#line 1084 "entities.lst"
      {"frac35;",{226,133,151,0,}},
#line 1088 "entities.lst"
      {"frac58;",{226,133,157,0,}},
#line 149 "entities.lst"
      {"Eogon;",{196,152,0,}},
      {(char*)0},
#line 1106 "entities.lst"
      {"geqq;",{226,137,167,0,}},
#line 1316 "entities.lst"
      {"leqq;",{226,137,166,0,}},
#line 1056 "entities.lst"
      {"female;",{226,153,128,0,}},
#line 1074 "entities.lst"
      {"frac13;",{226,133,147,0,}},
#line 1089 "entities.lst"
      {"frac78;",{226,133,158,0,}},
#line 1039 "entities.lst"
      {"erDot;",{226,137,147,0,}},
#line 1086 "entities.lst"
      {"frac45;",{226,133,152,0,}},
#line 2170 "entities.lst"
      {"vsupne;",{226,138,139,239,184,128,0,}},
#line 1000 "entities.lst"
      {"efDot;",{226,137,146,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1750 "entities.lst"
      {"qprime;",{226,129,151,0,}},
      {(char*)0},
#line 2168 "entities.lst"
      {"vsubne;",{226,138,138,239,184,128,0,}},
      {(char*)0},
#line 1081 "entities.lst"
      {"frac25;",{226,133,150,0,}},
#line 2164 "entities.lst"
      {"vprop;",{226,136,157,0,}},
      {(char*)0},
#line 1374 "entities.lst"
      {"lpar;",{40,0,}},
#line 1023 "entities.lst"
      {"epar;",{226,139,149,0,}},
#line 585 "entities.lst"
      {"Uring;",{197,174,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 1080 "entities.lst"
      {"frac23;",{226,133,148,0,}},
#line 1483 "entities.lst"
      {"ne;",{226,137,160,0,}},
      {(char*)0},
#line 1474 "entities.lst"
      {"nbumpe;",{226,137,143,204,184,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 916 "entities.lst"
      {"cuvee;",{226,139,142,0,}},
      {(char*)0}, {(char*)0},
#line 884 "entities.lst"
      {"copysr;",{226,132,151,0,}},
#line 388 "entities.lst"
      {"Nu;",{206,157,0,}},
#line 1598 "entities.lst"
      {"nvDash;",{226,138,173,0,}},
      {(char*)0}, {(char*)0},
#line 1243 "entities.lst"
      {"jsercy;",{209,152,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 705 "entities.lst"
      {"awint;",{226,168,145,0,}},
      {(char*)0}, {(char*)0},
#line 665 "entities.lst"
      {"andv;",{226,169,154,0,}},
#line 675 "entities.lst"
      {"angmsdaf;",{226,166,173,0,}},
      {(char*)0},
#line 936 "entities.lst"
      {"deg",{194,176,0,}},
      {(char*)0},
#line 570 "entities.lst"
      {"Uogon;",{197,178,0,}},
      {(char*)0}, {(char*)0},
#line 2169 "entities.lst"
      {"vsupnE;",{226,171,140,239,184,128,0,}},
      {(char*)0}, {(char*)0},
#line 875 "entities.lst"
      {"complement;",{226,136,129,0,}},
#line 676 "entities.lst"
      {"angmsdag;",{226,166,174,0,}},
      {(char*)0}, {(char*)0},
#line 2167 "entities.lst"
      {"vsubnE;",{226,171,139,239,184,128,0,}},
      {(char*)0},
#line 1289 "entities.lst"
      {"lbrke;",{226,166,139,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 919 "entities.lst"
      {"cwint;",{226,136,177,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1473 "entities.lst"
      {"nbump;",{226,137,142,204,184,0,}},
#line 774 "entities.lst"
      {"boxV;",{226,149,145,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 814 "entities.lst"
      {"bsolb;",{226,167,133,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1376 "entities.lst"
      {"lrarr;",{226,135,134,0,}},
#line 1040 "entities.lst"
      {"erarr;",{226,165,177,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 2226 "entities.lst"
      {"zeta;",{206,182,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1357 "entities.lst"
      {"loarr;",{226,135,189,0,}},
      {(char*)0},
#line 1024 "entities.lst"
      {"eparsl;",{226,167,163,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 982 "entities.lst"
      {"duarr;",{226,135,181,0,}},
#line 1170 "entities.lst"
      {"hoarr;",{226,135,191,0,}},
      {(char*)0},
#line 1375 "entities.lst"
      {"lparlt;",{226,166,147,0,}},
      {(char*)0},
#line 1114 "entities.lst"
      {"gesles;",{226,170,148,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 69 "entities.lst"
      {"Conint;",{226,136,175,0,}},
      {(char*)0},
#line 885 "entities.lst"
      {"crarr;",{226,134,181,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 2176 "entities.lst"
      {"weierp;",{226,132,152,0,}},
      {(char*)0}, {(char*)0},
#line 1542 "entities.lst"
      {"npar;",{226,136,166,0,}},
#line 171 "entities.lst"
      {"GT",{62,0,}},
      {(char*)0}, {(char*)0},
#line 678 "entities.lst"
      {"angrt;",{226,136,159,0,}},
#line 1555 "entities.lst"
      {"nrarrw;",{226,134,157,204,184,0,}},
      {(char*)0}, {(char*)0},
#line 1120 "entities.lst"
      {"gl;",{226,137,183,0,}},
#line 1341 "entities.lst"
      {"ll;",{226,137,170,0,}},
#line 1007 "entities.lst"
      {"el;",{226,170,153,0,}},
#line 1166 "entities.lst"
      {"hercon;",{226,138,185,0,}},
      {(char*)0},
#line 172 "entities.lst"
      {"GT;",{62,0,}},
#line 932 "entities.lst"
      {"dd;",{226,133,134,0,}},
      {(char*)0}, {(char*)0},
#line 1188 "entities.lst"
      {"iexcl",{194,161,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 1132 "entities.lst"
      {"grave;",{96,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 249 "entities.lst"
      {"LT",{60,0,}},
      {(char*)0},
#line 724 "entities.lst"
      {"bernou;",{226,132,172,0,}},
      {(char*)0},
#line 386 "entities.lst"
      {"Ntilde",{195,145,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 1109 "entities.lst"
      {"gescc;",{226,170,169,0,}},
#line 1319 "entities.lst"
      {"lescc;",{226,170,168,0,}},
      {(char*)0},
#line 250 "entities.lst"
      {"LT;",{60,0,}},
      {(char*)0},
#line 1491 "entities.lst"
      {"nesim;",{226,137,130,204,184,0,}},
      {(char*)0},
#line 387 "entities.lst"
      {"Ntilde;",{195,145,0,}},
#line 555 "entities.lst"
      {"Ubreve;",{197,172,0,}},
      {(char*)0}, {(char*)0},
#line 1210 "entities.lst"
      {"infintie;",{226,167,157,0,}},
      {(char*)0},
#line 775 "entities.lst"
      {"boxVH;",{226,149,172,0,}},
      {(char*)0},
#line 1102 "entities.lst"
      {"gdot;",{196,161,0,}},
#line 780 "entities.lst"
      {"boxVr;",{226,149,159,0,}},
#line 998 "entities.lst"
      {"edot;",{196,151,0,}},
#line 238 "entities.lst"
      {"Jsercy;",{208,136,0,}},
#line 677 "entities.lst"
      {"angmsdah;",{226,166,175,0,}},
#line 779 "entities.lst"
      {"boxVl;",{226,149,162,0,}},
      {(char*)0}, {(char*)0},
#line 231 "entities.lst"
      {"Iuml",{195,143,0,}},
      {(char*)0},
#line 100 "entities.lst"
      {"DotDot;",{226,131,156,0,}},
      {(char*)0}, {(char*)0},
#line 1492 "entities.lst"
      {"nexist;",{226,136,132,0,}},
      {(char*)0}, {(char*)0},
#line 631 "entities.lst"
      {"Zdot;",{197,187,0,}},
#line 1152 "entities.lst"
      {"gvnE;",{226,137,169,239,184,128,0,}},
#line 1408 "entities.lst"
      {"lvnE;",{226,137,168,239,184,128,0,}},
      {(char*)0},
#line 1553 "entities.lst"
      {"nrarr;",{226,134,155,0,}},
#line 232 "entities.lst"
      {"Iuml;",{195,143,0,}},
      {(char*)0},
#line 227 "entities.lst"
      {"Iota;",{206,153,0,}},
      {(char*)0},
#line 1141 "entities.lst"
      {"gtdot;",{226,139,151,0,}},
#line 1396 "entities.lst"
      {"ltdot;",{226,139,150,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 839 "entities.lst"
      {"cdot;",{196,139,0,}},
#line 877 "entities.lst"
      {"cong;",{226,137,133,0,}},
#line 1544 "entities.lst"
      {"nparsl;",{226,171,189,226,131,165,0,}},
#line 1042 "entities.lst"
      {"esdot;",{226,137,144,0,}},
      {(char*)0}, {(char*)0},
#line 1175 "entities.lst"
      {"horbar;",{226,128,149,0,}},
#line 979 "entities.lst"
      {"dtdot;",{226,139,177,0,}},
#line 175 "entities.lst"
      {"Gbreve;",{196,158,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 973 "entities.lst"
      {"drcorn;",{226,140,159,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 1336 "entities.lst"
      {"lhard;",{226,134,189,0,}},
#line 214 "entities.lst"
      {"Igrave",{195,140,0,}},
#line 1308 "entities.lst"
      {"leftleftarrows;",{226,135,135,0,}},
#line 1377 "entities.lst"
      {"lrcorner;",{226,140,159,0,}},
#line 943 "entities.lst"
      {"dharr;",{226,135,130,0,}},
#line 892 "entities.lst"
      {"ctdot;",{226,139,175,0,}},
      {(char*)0},
#line 1189 "entities.lst"
      {"iexcl;",{194,161,0,}},
#line 942 "entities.lst"
      {"dharl;",{226,135,131,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 793 "entities.lst"
      {"boxtimes;",{226,138,160,0,}},
#line 215 "entities.lst"
      {"Igrave;",{195,140,0,}},
#line 133 "entities.lst"
      {"ETH",{195,144,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 1601 "entities.lst"
      {"nvdash;",{226,138,172,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 2225 "entities.lst"
      {"zeetrf;",{226,132,168,0,}},
      {(char*)0}, {(char*)0},
#line 1140 "entities.lst"
      {"gtcir;",{226,169,186,0,}},
#line 1395 "entities.lst"
      {"ltcir;",{226,169,185,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1585 "entities.lst"
      {"nsupseteqq;",{226,171,134,204,184,0,}},
#line 1161 "entities.lst"
      {"hbar;",{226,132,143,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1208 "entities.lst"
      {"incare;",{226,132,133,0,}},
      {(char*)0},
#line 1577 "entities.lst"
      {"nsubseteqq;",{226,171,133,204,184,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 2212 "entities.lst"
      {"yen",{194,165,0,}},
#line 810 "entities.lst"
      {"bsemi;",{226,129,143,0,}},
#line 1032 "entities.lst"
      {"eqslantgtr;",{226,170,150,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 872 "entities.lst"
      {"commat;",{64,0,}},
      {(char*)0},
#line 2158 "entities.lst"
      {"vert;",{124,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1139 "entities.lst"
      {"gtcc;",{226,170,167,0,}},
#line 1394 "entities.lst"
      {"ltcc;",{226,170,166,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 871 "entities.lst"
      {"comma;",{44,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1045 "entities.lst"
      {"eth",{195,176,0,}},
#line 229 "entities.lst"
      {"Itilde;",{196,168,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 905 "entities.lst"
      {"cups;",{226,136,170,239,184,128,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 691 "entities.lst"
      {"apos;",{39,0,}},
#line 791 "entities.lst"
      {"boxminus;",{226,138,159,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 1367 "entities.lst"
      {"loplus;",{226,168,173,0,}},
#line 671 "entities.lst"
      {"angmsdab;",{226,166,169,0,}},
#line 964 "entities.lst"
      {"dotminus;",{226,136,184,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1561 "entities.lst"
      {"nsce;",{226,170,176,204,184,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 2224 "entities.lst"
      {"zdot;",{197,188,0,}},
#line 1065 "entities.lst"
      {"fltns;",{226,150,177,0,}},
      {(char*)0}, {(char*)0},
#line 1505 "entities.lst"
      {"nharr;",{226,134,174,0,}},
#line 1519 "entities.lst"
      {"nleq;",{226,137,176,0,}},
#line 1133 "entities.lst"
      {"gscr;",{226,132,138,0,}},
#line 1383 "entities.lst"
      {"lscr;",{237,160,181,237,179,129,0,}},
#line 1041 "entities.lst"
      {"escr;",{226,132,175,0,}},
#line 900 "entities.lst"
      {"cupbrcap;",{226,169,136,0,}},
#line 696 "entities.lst"
      {"ascr;",{237,160,181,237,178,182,0,}},
#line 625 "entities.lst"
      {"Yscr;",{237,160,181,237,178,180,0,}},
#line 1092 "entities.lst"
      {"fscr;",{237,160,181,237,178,187,0,}},
      {(char*)0}, {(char*)0},
#line 1176 "entities.lst"
      {"hscr;",{237,160,181,237,178,189,0,}},
      {(char*)0}, {(char*)0},
#line 975 "entities.lst"
      {"dscr;",{237,160,181,237,178,185,0,}},
#line 809 "entities.lst"
      {"bscr;",{237,160,181,237,178,183,0,}},
#line 441 "entities.lst"
      {"Qscr;",{237,160,181,237,178,172,0,}},
      {(char*)0},
#line 636 "entities.lst"
      {"Zscr;",{237,160,181,237,178,181,0,}},
      {(char*)0}, {(char*)0},
#line 1194 "entities.lst"
      {"ii;",{226,133,136,0,}},
      {(char*)0}, {(char*)0},
#line 1285 "entities.lst"
      {"lbarr;",{226,164,140,0,}},
#line 1456 "entities.lst"
      {"nLtv;",{226,137,170,204,184,0,}},
      {(char*)0},
#line 901 "entities.lst"
      {"cupcap;",{226,169,134,0,}},
#line 1379 "entities.lst"
      {"lrhard;",{226,165,173,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 887 "entities.lst"
      {"cscr;",{237,160,181,237,178,184,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 247 "entities.lst"
      {"Kscr;",{237,160,181,237,178,166,0,}},
#line 974 "entities.lst"
      {"drcrop;",{226,140,140,0,}},
#line 807 "entities.lst"
      {"brvbar",{194,166,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 840 "entities.lst"
      {"cedil",{194,184,0,}},
      {(char*)0},
#line 1614 "entities.lst"
      {"nwarr;",{226,134,150,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 808 "entities.lst"
      {"brvbar;",{194,166,0,}},
#line 2182 "entities.lst"
      {"wscr;",{237,160,181,237,179,140,0,}},
#line 1500 "entities.lst"
      {"nges;",{226,169,190,204,184,0,}},
      {(char*)0},
#line 1213 "entities.lst"
      {"intcal;",{226,138,186,0,}},
#line 141 "entities.lst"
      {"Edot;",{196,150,0,}},
      {(char*)0},
#line 1986 "entities.lst"
      {"sup1",{194,185,0,}},
#line 1538 "entities.lst"
      {"notni;",{226,136,140,0,}},
#line 1990 "entities.lst"
      {"sup3",{194,179,0,}},
#line 896 "entities.lst"
      {"cuesc;",{226,139,159,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1524 "entities.lst"
      {"nlsim;",{226,137,180,0,}},
#line 1225 "entities.lst"
      {"iscr;",{237,160,181,237,178,190,0,}},
#line 1545 "entities.lst"
      {"npart;",{226,136,130,204,184,0,}},
#line 1988 "entities.lst"
      {"sup2",{194,178,0,}},
      {(char*)0},
#line 1552 "entities.lst"
      {"nrArr;",{226,135,143,0,}},
#line 1987 "entities.lst"
      {"sup1;",{194,185,0,}},
      {(char*)0},
#line 1991 "entities.lst"
      {"sup3;",{194,179,0,}},
      {(char*)0},
#line 690 "entities.lst"
      {"apid;",{226,137,139,0,}},
#line 1507 "entities.lst"
      {"ni;",{226,136,139,0,}},
#line 862 "entities.lst"
      {"cire;",{226,137,151,0,}},
#line 1146 "entities.lst"
      {"gtrdot;",{226,139,151,0,}},
      {(char*)0}, {(char*)0},
#line 1989 "entities.lst"
      {"sup2;",{194,178,0,}},
      {(char*)0},
#line 1369 "entities.lst"
      {"lowast;",{226,136,151,0,}},
      {(char*)0},
#line 1364 "entities.lst"
      {"looparrowright;",{226,134,172,0,}},
#line 866 "entities.lst"
      {"clubs;",{226,153,163,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1006 "entities.lst"
      {"egsdot;",{226,170,152,0,}},
      {(char*)0},
#line 1404 "entities.lst"
      {"ltrif;",{226,151,130,0,}},
#line 874 "entities.lst"
      {"compfn;",{226,136,152,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 1378 "entities.lst"
      {"lrhar;",{226,135,139,0,}},
#line 1520 "entities.lst"
      {"nleqq;",{226,137,166,204,184,0,}},
#line 2155 "entities.lst"
      {"veeeq;",{226,137,154,0,}},
#line 225 "entities.lst"
      {"Iogon;",{196,174,0,}},
#line 753 "entities.lst"
      {"block;",{226,150,136,0,}},
#line 981 "entities.lst"
      {"dtrif;",{226,150,190,0,}},
      {(char*)0},
#line 1063 "entities.lst"
      {"flat;",{226,153,173,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 950 "entities.lst"
      {"disin;",{226,139,178,0,}},
#line 1951 "entities.lst"
      {"ssmile;",{226,140,163,0,}},
      {(char*)0},
#line 1381 "entities.lst"
      {"lrtri;",{226,138,191,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 983 "entities.lst"
      {"duhar;",{226,165,175,0,}},
#line 785 "entities.lst"
      {"boxdr;",{226,148,140,0,}},
      {(char*)0},
#line 674 "entities.lst"
      {"angmsdae;",{226,166,172,0,}},
#line 1562 "entities.lst"
      {"nscr;",{237,160,181,237,179,131,0,}},
#line 784 "entities.lst"
      {"boxdl;",{226,148,144,0,}},
#line 1996 "entities.lst"
      {"supe;",{226,138,135,0,}},
#line 903 "entities.lst"
      {"cupdot;",{226,138,141,0,}},
#line 917 "entities.lst"
      {"cuwed;",{226,139,143,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 1008 "entities.lst"
      {"elinters;",{226,143,167,0,}},
#line 902 "entities.lst"
      {"cupcup;",{226,169,138,0,}},
#line 1230 "entities.lst"
      {"isinsv;",{226,139,179,0,}},
      {(char*)0}, {(char*)0},
#line 1359 "entities.lst"
      {"longleftarrow;",{226,159,181,0,}},
#line 886 "entities.lst"
      {"cross;",{226,156,151,0,}},
      {(char*)0},
#line 1950 "entities.lst"
      {"ssetmn;",{226,136,150,0,}},
      {(char*)0}, {(char*)0},
#line 841 "entities.lst"
      {"cedil;",{194,184,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 1597 "entities.lst"
      {"numsp;",{226,128,135,0,}},
      {(char*)0},
#line 681 "entities.lst"
      {"angsph;",{226,136,162,0,}},
#line 292 "entities.lst"
      {"Ll;",{226,139,152,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1118 "entities.lst"
      {"gimel;",{226,132,183,0,}},
      {(char*)0}, {(char*)0},
#line 2231 "entities.lst"
      {"zscr;",{237,160,181,237,179,143,0,}},
#line 504 "entities.lst"
      {"Sqrt;",{226,136,154,0,}},
      {(char*)0},
#line 853 "entities.lst"
      {"circ;",{203,134,0,}},
      {(char*)0},
#line 426 "entities.lst"
      {"Pr;",{226,170,187,0,}},
      {(char*)0},
#line 169 "entities.lst"
      {"Fscr;",{226,132,177,0,}},
      {(char*)0}, {(char*)0},
#line 179 "entities.lst"
      {"Gdot;",{196,160,0,}},
#line 1211 "entities.lst"
      {"inodot;",{196,177,0,}},
#line 1558 "entities.lst"
      {"nrtrie;",{226,139,173,0,}},
      {(char*)0},
#line 1945 "entities.lst"
      {"square;",{226,150,161,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 640 "entities.lst"
      {"ac;",{226,136,190,0,}},
#line 1250 "entities.lst"
      {"kgreen;",{196,184,0,}},
#line 1242 "entities.lst"
      {"jscr;",{237,160,181,237,178,191,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 1554 "entities.lst"
      {"nrarrc;",{226,164,179,204,184,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1195 "entities.lst"
      {"iiiint;",{226,168,140,0,}},
#line 1616 "entities.lst"
      {"nwnear;",{226,164,167,0,}},
      {(char*)0},
#line 1504 "entities.lst"
      {"nhArr;",{226,135,142,0,}},
      {(char*)0},
#line 976 "entities.lst"
      {"dscy;",{209,149,0,}},
#line 801 "entities.lst"
      {"boxvR;",{226,149,158,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1957 "entities.lst"
      {"strns;",{194,175,0,}},
#line 155 "entities.lst"
      {"Escr;",{226,132,176,0,}},
#line 749 "entities.lst"
      {"blank;",{226,144,163,0,}},
#line 1924 "entities.lst"
      {"softcy;",{209,140,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 452 "entities.lst"
      {"Re;",{226,132,156,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 1557 "entities.lst"
      {"nrtri;",{226,139,171,0,}},
#line 952 "entities.lst"
      {"divide",{195,183,0,}},
      {(char*)0}, {(char*)0},
#line 1323 "entities.lst"
      {"lesg;",{226,139,154,239,184,128,0,}},
#line 1258 "entities.lst"
      {"lBarr;",{226,164,142,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1952 "entities.lst"
      {"sstarf;",{226,139,134,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 953 "entities.lst"
      {"divide;",{195,183,0,}},
      {(char*)0},
#line 315 "entities.lst"
      {"Mscr;",{226,132,179,0,}},
      {(char*)0}, {(char*)0},
#line 1183 "entities.lst"
      {"ic;",{226,129,163,0,}},
      {(char*)0},
#line 1548 "entities.lst"
      {"nprcue;",{226,139,160,0,}},
      {(char*)0},
#line 1119 "entities.lst"
      {"gjcy;",{209,147,0,}},
#line 1340 "entities.lst"
      {"ljcy;",{209,153,0,}},
#line 733 "entities.lst"
      {"bigoplus;",{226,168,129,0,}},
      {(char*)0},
#line 1612 "entities.lst"
      {"nwArr;",{226,135,150,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 988 "entities.lst"
      {"eDot;",{226,137,145,0,}},
#line 956 "entities.lst"
      {"djcy;",{209,146,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 867 "entities.lst"
      {"clubsuit;",{226,153,163,0,}},
#line 505 "entities.lst"
      {"Square;",{226,150,161,0,}},
#line 1218 "entities.lst"
      {"iocy;",{209,145,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 1486 "entities.lst"
      {"nearr;",{226,134,151,0,}},
#line 1029 "entities.lst"
      {"eqcirc;",{226,137,150,0,}},
#line 524 "entities.lst"
      {"Superset;",{226,138,131,0,}},
      {(char*)0},
#line 1163 "entities.lst"
      {"hearts;",{226,153,165,0,}},
#line 944 "entities.lst"
      {"diam;",{226,139,132,0,}},
#line 1126 "entities.lst"
      {"gnapprox;",{226,170,138,0,}},
#line 1351 "entities.lst"
      {"lnapprox;",{226,170,137,0,}},
      {(char*)0}, {(char*)0},
#line 586 "entities.lst"
      {"Uscr;",{237,160,181,237,178,176,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1295 "entities.lst"
      {"lcub;",{123,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 688 "entities.lst"
      {"apacir;",{226,169,175,0,}},
#line 1946 "entities.lst"
      {"squarf;",{226,150,170,0,}},
      {(char*)0}, {(char*)0},
#line 1458 "entities.lst"
      {"nVDash;",{226,138,175,0,}},
#line 1382 "entities.lst"
      {"lsaquo;",{226,128,185,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 996 "entities.lst"
      {"ecolon;",{226,137,149,0,}},
      {(char*)0},
#line 2003 "entities.lst"
      {"supne;",{226,138,139,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 819 "entities.lst"
      {"bumpE;",{226,170,174,0,}},
#line 1090 "entities.lst"
      {"frasl;",{226,129,132,0,}},
#line 168 "entities.lst"
      {"Fouriertrf;",{226,132,177,0,}},
#line 762 "entities.lst"
      {"boxDR;",{226,149,148,0,}},
#line 54 "entities.lst"
      {"Cdot;",{196,138,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 744 "entities.lst"
      {"blacksquare;",{226,150,170,0,}},
      {(char*)0}, {(char*)0},
#line 1294 "entities.lst"
      {"lceil;",{226,140,136,0,}},
#line 190 "entities.lst"
      {"Gscr;",{237,160,181,237,178,162,0,}},
      {(char*)0},
#line 854 "entities.lst"
      {"circeq;",{226,137,151,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 771 "entities.lst"
      {"boxUR;",{226,149,154,0,}},
#line 237 "entities.lst"
      {"Jscr;",{237,160,181,237,178,165,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 673 "entities.lst"
      {"angmsdad;",{226,166,171,0,}},
#line 682 "entities.lst"
      {"angst;",{195,133,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1397 "entities.lst"
      {"lthree;",{226,139,139,0,}},
      {(char*)0}, {(char*)0},
#line 130 "entities.lst"
      {"Dscr;",{237,160,181,237,178,159,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 2166 "entities.lst"
      {"vscr;",{237,160,181,237,179,139,0,}},
      {(char*)0},
#line 304 "entities.lst"
      {"Lscr;",{226,132,146,0,}},
      {(char*)0},
#line 847 "entities.lst"
      {"chcy;",{209,135,0,}},
      {(char*)0}, {(char*)0},
#line 1511 "entities.lst"
      {"njcy;",{209,154,0,}},
      {(char*)0}, {(char*)0},
#line 2217 "entities.lst"
      {"yscr;",{237,160,181,237,179,142,0,}},
      {(char*)0}, {(char*)0},
#line 613 "entities.lst"
      {"Xi;",{206,158,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 1748 "entities.lst"
      {"qint;",{226,168,140,0,}},
      {(char*)0},
#line 187 "entities.lst"
      {"GreaterLess;",{226,137,183,0,}},
      {(char*)0}, {(char*)0},
#line 1751 "entities.lst"
      {"qscr;",{237,160,181,237,179,134,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 1342 "entities.lst"
      {"llarr;",{226,135,135,0,}},
      {(char*)0},
#line 1196 "entities.lst"
      {"iiint;",{226,136,173,0,}},
      {(char*)0},
#line 1052 "entities.lst"
      {"expectation;",{226,132,176,0,}},
#line 934 "entities.lst"
      {"ddarr;",{226,135,138,0,}},
#line 1480 "entities.lst"
      {"ncup;",{226,169,130,0,}},
#line 1488 "entities.lst"
      {"nedot;",{226,137,144,204,184,0,}},
      {(char*)0}, {(char*)0},
#line 1144 "entities.lst"
      {"gtrapprox;",{226,170,134,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1324 "entities.lst"
      {"lesges;",{226,170,147,0,}},
#line 663 "entities.lst"
      {"andd;",{226,169,156,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1227 "entities.lst"
      {"isinE;",{226,139,185,0,}},
#line 717 "entities.lst"
      {"bcong;",{226,137,140,0,}},
      {(char*)0}, {(char*)0},
#line 907 "entities.lst"
      {"curarrm;",{226,164,188,0,}},
      {(char*)0},
#line 645 "entities.lst"
      {"acute",{194,180,0,}},
#line 615 "entities.lst"
      {"Xscr;",{237,160,181,237,178,179,0,}},
      {(char*)0},
#line 617 "entities.lst"
      {"YIcy;",{208,135,0,}},
      {(char*)0}, {(char*)0},
#line 1490 "entities.lst"
      {"nesear;",{226,164,168,0,}},
      {(char*)0},
#line 1368 "entities.lst"
      {"lotimes;",{226,168,180,0,}},
#line 1027 "entities.lst"
      {"epsilon;",{206,181,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 740 "entities.lst"
      {"bigvee;",{226,139,129,0,}},
      {(char*)0}, {(char*)0},
#line 1405 "entities.lst"
      {"lurdshar;",{226,165,138,0,}},
#line 947 "entities.lst"
      {"diams;",{226,153,166,0,}},
      {(char*)0},
#line 1147 "entities.lst"
      {"gtreqless;",{226,139,155,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 993 "entities.lst"
      {"ecir;",{226,137,150,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 994 "entities.lst"
      {"ecirc",{195,170,0,}},
#line 1297 "entities.lst"
      {"ldca;",{226,164,182,0,}},
#line 643 "entities.lst"
      {"acirc",{195,162,0,}},
#line 1891 "entities.lst"
      {"sext;",{226,156,182,0,}},
      {(char*)0}, {(char*)0},
#line 1339 "entities.lst"
      {"lhblk;",{226,150,132,0,}},
      {(char*)0}, {(char*)0},
#line 1887 "entities.lst"
      {"semi;",{59,0,}},
      {(char*)0},
#line 2165 "entities.lst"
      {"vrtri;",{226,138,179,0,}},
      {(char*)0},
#line 837 "entities.lst"
      {"ccups;",{226,169,140,0,}},
      {(char*)0}, {(char*)0},
#line 1581 "entities.lst"
      {"nsupE;",{226,171,134,204,184,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 75 "entities.lst"
      {"Cscr;",{237,160,181,237,178,158,0,}},
      {(char*)0},
#line 1573 "entities.lst"
      {"nsubE;",{226,171,133,204,184,0,}},
      {(char*)0},
#line 1484 "entities.lst"
      {"neArr;",{226,135,151,0,}},
#line 2131 "entities.lst"
      {"vBar;",{226,171,168,0,}},
      {(char*)0},
#line 431 "entities.lst"
      {"Prime;",{226,128,179,0,}},
#line 1110 "entities.lst"
      {"gesdot;",{226,170,128,0,}},
#line 1320 "entities.lst"
      {"lesdot;",{226,169,191,0,}},
#line 1479 "entities.lst"
      {"ncongdot;",{226,169,173,204,184,0,}},
#line 2228 "entities.lst"
      {"zhcy;",{208,182,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 298 "entities.lst"
      {"Longleftarrow;",{226,159,184,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 405 "entities.lst"
      {"Or;",{226,169,148,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 1514 "entities.lst"
      {"nlarr;",{226,134,154,0,}},
      {(char*)0},
#line 1358 "entities.lst"
      {"lobrk;",{226,159,166,0,}},
#line 212 "entities.lst"
      {"Idot;",{196,176,0,}},
#line 1953 "entities.lst"
      {"star;",{226,152,134,0,}},
      {(char*)0}, {(char*)0},
#line 646 "entities.lst"
      {"acute;",{194,180,0,}},
#line 1478 "entities.lst"
      {"ncong;",{226,137,135,0,}},
      {(char*)0},
#line 1459 "entities.lst"
      {"nVdash;",{226,138,174,0,}},
#line 1184 "entities.lst"
      {"icirc",{195,174,0,}},
#line 1149 "entities.lst"
      {"gtrless;",{226,137,183,0,}},
#line 1228 "entities.lst"
      {"isindot;",{226,139,181,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 427 "entities.lst"
      {"Precedes;",{226,137,186,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 1322 "entities.lst"
      {"lesdotor;",{226,170,131,0,}},
#line 957 "entities.lst"
      {"dlcorn;",{226,140,158,0,}},
      {(char*)0},
#line 1515 "entities.lst"
      {"nldr;",{226,128,165,0,}},
      {(char*)0},
#line 412 "entities.lst"
      {"Ouml",{195,150,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1343 "entities.lst"
      {"llcorner;",{226,140,158,0,}},
#line 1931 "entities.lst"
      {"spar;",{226,136,165,0,}},
      {(char*)0},
#line 385 "entities.lst"
      {"Nscr;",{237,160,181,237,178,169,0,}},
#line 1328 "entities.lst"
      {"lesseqqgtr;",{226,170,139,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 413 "entities.lst"
      {"Ouml;",{195,150,0,}},
      {(char*)0},
#line 1338 "entities.lst"
      {"lharul;",{226,165,170,0,}},
      {(char*)0},
#line 1100 "entities.lst"
      {"gcirc;",{196,157,0,}},
#line 78 "entities.lst"
      {"DD;",{226,133,133,0,}},
#line 995 "entities.lst"
      {"ecirc;",{195,170,0,}},
      {(char*)0},
#line 644 "entities.lst"
      {"acirc;",{195,162,0,}},
#line 621 "entities.lst"
      {"Ycirc;",{197,182,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1162 "entities.lst"
      {"hcirc;",{196,165,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 2218 "entities.lst"
      {"yucy;",{209,142,0,}},
#line 1050 "entities.lst"
      {"excl;",{33,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 1033 "entities.lst"
      {"eqslantless;",{226,170,149,0,}},
#line 577 "entities.lst"
      {"UpTee;",{226,138,165,0,}},
#line 1890 "entities.lst"
      {"setmn;",{226,136,150,0,}},
#line 397 "entities.lst"
      {"Ograve",{195,146,0,}},
      {(char*)0},
#line 2132 "entities.lst"
      {"vBarv;",{226,171,169,0,}},
#line 74 "entities.lst"
      {"Cross;",{226,168,175,0,}},
#line 836 "entities.lst"
      {"ccirc;",{196,137,0,}},
#line 1551 "entities.lst"
      {"npreceq;",{226,170,175,204,184,0,}},
      {(char*)0},
#line 792 "entities.lst"
      {"boxplus;",{226,138,158,0,}},
#line 113 "entities.lst"
      {"DoubleUpArrow;",{226,135,145,0,}},
      {(char*)0},
#line 1363 "entities.lst"
      {"looparrowleft;",{226,134,171,0,}},
      {(char*)0},
#line 398 "entities.lst"
      {"Ograve;",{195,146,0,}},
      {(char*)0},
#line 965 "entities.lst"
      {"dotplus;",{226,136,148,0,}},
#line 1754 "entities.lst"
      {"quest;",{63,0,}},
      {(char*)0},
#line 751 "entities.lst"
      {"blk14;",{226,150,145,0,}},
      {(char*)0},
#line 752 "entities.lst"
      {"blk34;",{226,150,147,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 2172 "entities.lst"
      {"wcirc;",{197,181,0,}},
      {(char*)0},
#line 1150 "entities.lst"
      {"gtrsim;",{226,137,179,0,}},
      {(char*)0},
#line 750 "entities.lst"
      {"blk12;",{226,150,146,0,}},
#line 513 "entities.lst"
      {"Star;",{226,139,134,0,}},
      {(char*)0},
#line 1370 "entities.lst"
      {"lowbar;",{95,0,}},
      {(char*)0}, {(char*)0},
#line 184 "entities.lst"
      {"GreaterEqualLess;",{226,139,155,0,}},
      {(char*)0}, {(char*)0},
#line 1475 "entities.lst"
      {"ncap;",{226,169,131,0,}},
#line 1185 "entities.lst"
      {"icirc;",{195,174,0,}},
      {(char*)0}, {(char*)0},
#line 1948 "entities.lst"
      {"srarr;",{226,134,146,0,}},
      {(char*)0},
#line 1337 "entities.lst"
      {"lharu;",{226,134,188,0,}},
      {(char*)0},
#line 63 "entities.lst"
      {"ClockwiseContourIntegral;",{226,136,178,0,}},
      {(char*)0}, {(char*)0},
#line 2154 "entities.lst"
      {"veebar;",{226,138,187,0,}},
#line 2157 "entities.lst"
      {"verbar;",{124,0,}},
#line 760 "entities.lst"
      {"bowtie;",{226,139,136,0,}},
#line 597 "entities.lst"
      {"Vert;",{226,128,150,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 852 "entities.lst"
      {"cirE;",{226,167,131,0,}},
#line 1583 "entities.lst"
      {"nsupset;",{226,138,131,226,131,146,0,}},
#line 777 "entities.lst"
      {"boxVR;",{226,149,160,0,}},
#line 409 "entities.lst"
      {"Otilde",{195,149,0,}},
#line 151 "entities.lst"
      {"Epsilon;",{206,149,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1575 "entities.lst"
      {"nsubset;",{226,138,130,226,131,146,0,}},
#line 1401 "entities.lst"
      {"ltrPar;",{226,166,150,0,}},
      {(char*)0},
#line 611 "entities.lst"
      {"Wscr;",{237,160,181,237,178,178,0,}},
      {(char*)0}, {(char*)0},
#line 73 "entities.lst"
      {"CounterClockwiseContourIntegral;",{226,136,179,0,}},
#line 410 "entities.lst"
      {"Otilde;",{195,149,0,}},
#line 1261 "entities.lst"
      {"lHar;",{226,165,162,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 922 "entities.lst"
      {"dHar;",{226,165,165,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 484 "entities.lst"
      {"Rscr;",{226,132,155,0,}},
      {(char*)0},
#line 138 "entities.lst"
      {"Ecirc",{195,138,0,}},
#line 1187 "entities.lst"
      {"iecy;",{208,181,0,}},
#line 228 "entities.lst"
      {"Iscr;",{226,132,144,0,}},
      {(char*)0}, {(char*)0},
#line 1344 "entities.lst"
      {"llhard;",{226,165,171,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1993 "entities.lst"
      {"supE;",{226,171,134,0,}},
      {(char*)0},
#line 186 "entities.lst"
      {"GreaterGreater;",{226,170,162,0,}},
      {(char*)0}, {(char*)0},
#line 958 "entities.lst"
      {"dlcrop;",{226,140,141,0,}},
#line 1522 "entities.lst"
      {"nles;",{226,169,189,204,184,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 832 "entities.lst"
      {"ccaps;",{226,169,141,0,}},
#line 1215 "entities.lst"
      {"intercal;",{226,138,186,0,}},
      {(char*)0}, {(char*)0},
#line 369 "entities.lst"
      {"NotSquareSubsetEqual;",{226,139,162,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 864 "entities.lst"
      {"cirmid;",{226,171,175,0,}},
#line 765 "entities.lst"
      {"boxH;",{226,149,144,0,}},
      {(char*)0},
#line 341 "entities.lst"
      {"NotGreater;",{226,137,175,0,}},
#line 1579 "entities.lst"
      {"nsucceq;",{226,170,176,204,184,0,}},
#line 1038 "entities.lst"
      {"eqvparsl;",{226,167,165,0,}},
      {(char*)0},
#line 584 "entities.lst"
      {"Upsilon;",{206,165,0,}},
      {(char*)0},
#line 81 "entities.lst"
      {"DScy;",{208,133,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 987 "entities.lst"
      {"eDDot;",{226,169,183,0,}},
      {(char*)0},
#line 1446 "entities.lst"
      {"mu;",{206,188,0,}},
#line 1985 "entities.lst"
      {"sung;",{226,153,170,0,}},
      {(char*)0},
#line 1512 "entities.lst"
      {"nlArr;",{226,135,141,0,}},
#line 1878 "entities.lst"
      {"sdot;",{226,139,133,0,}},
      {(char*)0},
#line 345 "entities.lst"
      {"NotGreaterLess;",{226,137,185,0,}},
      {(char*)0}, {(char*)0},
#line 1011 "entities.lst"
      {"elsdot;",{226,170,151,0,}},
      {(char*)0}, {(char*)0},
#line 578 "entities.lst"
      {"UpTeeArrow;",{226,134,165,0,}},
      {(char*)0}, {(char*)0},
#line 2173 "entities.lst"
      {"wedbar;",{226,169,159,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1292 "entities.lst"
      {"lcaron;",{196,190,0,}},
#line 992 "entities.lst"
      {"ecaron;",{196,155,0,}},
#line 1443 "entities.lst"
      {"mp;",{226,136,147,0,}},
#line 1057 "entities.lst"
      {"ffilig;",{239,172,131,0,}},
      {(char*)0},
#line 556 "entities.lst"
      {"Ucirc",{195,155,0,}},
      {(char*)0},
#line 1313 "entities.lst"
      {"leftthreetimes;",{226,139,139,0,}},
#line 1237 "entities.lst"
      {"jcirc;",{196,181,0,}},
#line 1933 "entities.lst"
      {"sqcaps;",{226,138,147,239,184,128,0,}},
      {(char*)0},
#line 930 "entities.lst"
      {"dcaron;",{196,143,0,}},
#line 672 "entities.lst"
      {"angmsdac;",{226,166,170,0,}},
      {(char*)0}, {(char*)0},
#line 629 "entities.lst"
      {"Zcaron;",{197,189,0,}},
      {(char*)0},
#line 1254 "entities.lst"
      {"kscr;",{237,160,181,237,179,128,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 1894 "entities.lst"
      {"sharp;",{226,153,175,0,}},
#line 411 "entities.lst"
      {"Otimes;",{226,168,183,0,}},
#line 1345 "entities.lst"
      {"lltri;",{226,151,186,0,}},
      {(char*)0}, {(char*)0},
#line 833 "entities.lst"
      {"ccaron;",{196,141,0,}},
      {(char*)0},
#line 1390 "entities.lst"
      {"lsquor;",{226,128,154,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 139 "entities.lst"
      {"Ecirc;",{195,138,0,}},
      {(char*)0},
#line 914 "entities.lst"
      {"curvearrowleft;",{226,134,182,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1286 "entities.lst"
      {"lbbrk;",{226,157,178,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 82 "entities.lst"
      {"DZcy;",{208,143,0,}},
      {(char*)0},
#line 1445 "entities.lst"
      {"mstpos;",{226,136,190,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 781 "entities.lst"
      {"boxbox;",{226,167,137,0,}},
      {(char*)0}, {(char*)0},
#line 1291 "entities.lst"
      {"lbrkslu;",{226,166,141,0,}},
      {(char*)0},
#line 858 "entities.lst"
      {"circledS;",{226,147,136,0,}},
      {(char*)0},
#line 2015 "entities.lst"
      {"swarr;",{226,134,153,0,}},
#line 200 "entities.lst"
      {"Hscr;",{226,132,139,0,}},
#line 1932 "entities.lst"
      {"sqcap;",{226,138,147,0,}},
#line 437 "entities.lst"
      {"QUOT",{34,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 768 "entities.lst"
      {"boxHd;",{226,149,164,0,}},
      {(char*)0}, {(char*)0},
#line 102 "entities.lst"
      {"DoubleContourIntegral;",{226,136,175,0,}},
#line 1527 "entities.lst"
      {"nltrie;",{226,139,172,0,}},
#line 1198 "entities.lst"
      {"iiota;",{226,132,169,0,}},
      {(char*)0}, {(char*)0},
#line 438 "entities.lst"
      {"QUOT;",{34,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 664 "entities.lst"
      {"andslope;",{226,169,152,0,}},
#line 894 "entities.lst"
      {"cudarrr;",{226,164,181,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 767 "entities.lst"
      {"boxHU;",{226,149,169,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 606 "entities.lst"
      {"Vvdash;",{226,138,170,0,}},
#line 557 "entities.lst"
      {"Ucirc;",{195,155,0,}},
#line 1976 "entities.lst"
      {"succ;",{226,137,187,0,}},
#line 1389 "entities.lst"
      {"lsquo;",{226,128,152,0,}},
      {(char*)0}, {(char*)0},
#line 337 "entities.lst"
      {"NotElement;",{226,136,137,0,}},
#line 241 "entities.lst"
      {"KJcy;",{208,140,0,}},
      {(char*)0}, {(char*)0},
#line 698 "entities.lst"
      {"asymp;",{226,137,136,0,}},
#line 1523 "entities.lst"
      {"nless;",{226,137,174,0,}},
      {(char*)0}, {(char*)0},
#line 1476 "entities.lst"
      {"ncaron;",{197,136,0,}},
      {(char*)0},
#line 1448 "entities.lst"
      {"mumap;",{226,138,184,0,}},
#line 1151 "entities.lst"
      {"gvertneqq;",{226,137,169,239,184,128,0,}},
#line 1407 "entities.lst"
      {"lvertneqq;",{226,137,168,239,184,128,0,}},
      {(char*)0},
#line 857 "entities.lst"
      {"circledR;",{194,174,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 1560 "entities.lst"
      {"nsccue;",{226,139,161,0,}},
      {(char*)0},
#line 797 "entities.lst"
      {"boxur;",{226,148,148,0,}},
#line 1752 "entities.lst"
      {"quaternions;",{226,132,141,0,}},
#line 876 "entities.lst"
      {"complexes;",{226,132,130,0,}},
#line 2175 "entities.lst"
      {"wedgeq;",{226,137,153,0,}},
#line 796 "entities.lst"
      {"boxul;",{226,148,152,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 1217 "entities.lst"
      {"intprod;",{226,168,188,0,}},
#line 766 "entities.lst"
      {"boxHD;",{226,149,166,0,}},
#line 1526 "entities.lst"
      {"nltri;",{226,139,170,0,}},
#line 1910 "entities.lst"
      {"siml;",{226,170,157,0,}},
      {(char*)0}, {(char*)0},
#line 1949 "entities.lst"
      {"sscr;",{237,160,181,237,179,136,0,}},
      {(char*)0},
#line 177 "entities.lst"
      {"Gcirc;",{196,156,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 2222 "entities.lst"
      {"zcaron;",{197,190,0,}},
#line 233 "entities.lst"
      {"Jcirc;",{196,180,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 442 "entities.lst"
      {"RBarr;",{226,164,144,0,}},
      {(char*)0}, {(char*)0},
#line 356 "entities.lst"
      {"NotLessLess;",{226,137,170,204,184,0,}},
      {(char*)0}, {(char*)0},
#line 984 "entities.lst"
      {"dwangle;",{226,166,166,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 783 "entities.lst"
      {"boxdR;",{226,149,146,0,}},
      {(char*)0}, {(char*)0},
#line 1981 "entities.lst"
      {"succneqq;",{226,170,182,0,}},
      {(char*)0}, {(char*)0},
#line 1509 "entities.lst"
      {"nisd;",{226,139,186,0,}},
#line 1499 "entities.lst"
      {"ngeqslant;",{226,169,190,204,184,0,}},
      {(char*)0}, {(char*)0},
#line 1906 "entities.lst"
      {"sime;",{226,137,131,0,}},
#line 2210 "entities.lst"
      {"ycirc;",{197,183,0,}},
#line 28 "entities.lst"
      {"Auml",{195,132,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 567 "entities.lst"
      {"UnderParenthesis;",{226,143,157,0,}},
#line 221 "entities.lst"
      {"Integral;",{226,136,171,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 2174 "entities.lst"
      {"wedge;",{226,136,167,0,}},
      {(char*)0},
#line 29 "entities.lst"
      {"Auml;",{195,132,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 137 "entities.lst"
      {"Ecaron;",{196,154,0,}},
#line 729 "entities.lst"
      {"bigcap;",{226,139,130,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 706 "entities.lst"
      {"bNot;",{226,171,173,0,}},
#line 1880 "entities.lst"
      {"sdote;",{226,169,166,0,}},
      {(char*)0},
#line 591 "entities.lst"
      {"Vbar;",{226,171,171,0,}},
      {(char*)0},
#line 1592 "entities.lst"
      {"ntriangleright;",{226,139,171,0,}},
#line 525 "entities.lst"
      {"SupersetEqual;",{226,138,135,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 14 "entities.lst"
      {"Agrave",{195,128,0,}},
      {(char*)0}, {(char*)0},
#line 1994 "entities.lst"
      {"supdot;",{226,170,190,0,}},
#line 1305 "entities.lst"
      {"leftarrowtail;",{226,134,162,0,}},
      {(char*)0},
#line 969 "entities.lst"
      {"downdownarrows;",{226,135,138,0,}},
      {(char*)0}, {(char*)0},
#line 512 "entities.lst"
      {"Sscr;",{237,160,181,237,178,174,0,}},
#line 1360 "entities.lst"
      {"longleftrightarrow;",{226,159,183,0,}},
#line 422 "entities.lst"
      {"Pi;",{206,160,0,}},
#line 15 "entities.lst"
      {"Agrave;",{195,128,0,}},
#line 511 "entities.lst"
      {"SquareUnion;",{226,138,148,0,}},
      {(char*)0}, {(char*)0},
#line 849 "entities.lst"
      {"checkmark;",{226,156,147,0,}},
#line 378 "entities.lst"
      {"NotSuperset;",{226,138,131,226,131,146,0,}},
#line 1593 "entities.lst"
      {"ntrianglerighteq;",{226,139,173,0,}},
      {(char*)0}, {(char*)0},
#line 692 "entities.lst"
      {"approx;",{226,137,136,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 1361 "entities.lst"
      {"longmapsto;",{226,159,188,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 1252 "entities.lst"
      {"kjcy;",{209,156,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 618 "entities.lst"
      {"YUcy;",{208,174,0,}},
      {(char*)0}, {(char*)0},
#line 1051 "entities.lst"
      {"exist;",{226,136,131,0,}},
      {(char*)0}, {(char*)0},
#line 1979 "entities.lst"
      {"succeq;",{226,170,176,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 2013 "entities.lst"
      {"swArr;",{226,135,153,0,}},
      {(char*)0},
#line 1493 "entities.lst"
      {"nexists;",{226,136,132,0,}},
#line 693 "entities.lst"
      {"approxeq;",{226,137,138,0,}},
      {(char*)0},
#line 1907 "entities.lst"
      {"simeq;",{226,137,131,0,}},
#line 443 "entities.lst"
      {"REG",{194,174,0,}},
#line 111 "entities.lst"
      {"DoubleRightArrow;",{226,135,146,0,}},
#line 435 "entities.lst"
      {"Pscr;",{237,160,181,237,178,171,0,}},
#line 720 "entities.lst"
      {"becaus;",{226,136,181,0,}},
#line 26 "entities.lst"
      {"Atilde",{195,131,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 281 "entities.lst"
      {"LeftVector;",{226,134,188,0,}},
      {(char*)0}, {(char*)0},
#line 52 "entities.lst"
      {"Ccirc;",{196,136,0,}},
#line 25 "entities.lst"
      {"Assign;",{226,137,148,0,}},
#line 22 "entities.lst"
      {"Aring",{195,133,0,}},
#line 1883 "entities.lst"
      {"searr;",{226,134,152,0,}},
      {(char*)0},
#line 27 "entities.lst"
      {"Atilde;",{195,131,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 2005 "entities.lst"
      {"supset;",{226,138,131,0,}},
      {(char*)0},
#line 282 "entities.lst"
      {"LeftVectorBar;",{226,165,146,0,}},
      {(char*)0},
#line 605 "entities.lst"
      {"Vscr;",{237,160,181,237,178,177,0,}},
      {(char*)0}, {(char*)0},
#line 1030 "entities.lst"
      {"eqcolon;",{226,137,149,0,}},
#line 103 "entities.lst"
      {"DoubleDot;",{194,168,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 731 "entities.lst"
      {"bigcup;",{226,139,131,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1864 "entities.lst"
      {"sc;",{226,137,187,0,}},
#line 204 "entities.lst"
      {"IEcy;",{208,149,0,}},
      {(char*)0},
#line 1584 "entities.lst"
      {"nsupseteq;",{226,138,137,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 2006 "entities.lst"
      {"supseteq;",{226,138,135,0,}},
#line 1576 "entities.lst"
      {"nsubseteq;",{226,138,136,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 104 "entities.lst"
      {"DoubleDownArrow;",{226,135,147,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1251 "entities.lst"
      {"khcy;",{209,133,0,}},
      {(char*)0},
#line 86 "entities.lst"
      {"Dcaron;",{196,142,0,}},
#line 659 "entities.lst"
      {"amp",{38,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 1885 "entities.lst"
      {"sect",{194,167,0,}},
      {(char*)0},
#line 256 "entities.lst"
      {"Lcaron;",{196,189,0,}},
      {(char*)0},
#line 878 "entities.lst"
      {"congdot;",{226,169,173,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 723 "entities.lst"
      {"bepsi;",{207,182,0,}},
      {(char*)0},
#line 1886 "entities.lst"
      {"sect;",{194,167,0,}},
      {(char*)0},
#line 1018 "entities.lst"
      {"emsp;",{226,128,131,0,}},
#line 433 "entities.lst"
      {"Proportion;",{226,136,183,0,}},
      {(char*)0}, {(char*)0},
#line 1912 "entities.lst"
      {"simne;",{226,137,134,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 2160 "entities.lst"
      {"vltri;",{226,138,178,0,}},
      {(char*)0}, {(char*)0},
#line 935 "entities.lst"
      {"ddotseq;",{226,169,183,0,}},
      {(char*)0},
#line 786 "entities.lst"
      {"boxh;",{226,148,128,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1332 "entities.lst"
      {"lfloor;",{226,140,138,0,}},
#line 209 "entities.lst"
      {"Icirc",{195,142,0,}},
      {(char*)0},
#line 816 "entities.lst"
      {"bull;",{226,128,162,0,}},
      {(char*)0},
#line 183 "entities.lst"
      {"GreaterEqual;",{226,137,165,0,}},
#line 23 "entities.lst"
      {"Aring;",{195,133,0,}},
#line 1399 "entities.lst"
      {"ltlarr;",{226,165,182,0,}},
      {(char*)0},
#line 954 "entities.lst"
      {"divideontimes;",{226,139,135,0,}},
#line 170 "entities.lst"
      {"GJcy;",{208,131,0,}},
#line 526 "entities.lst"
      {"Supset;",{226,139,145,0,}},
#line 1017 "entities.lst"
      {"emsp14;",{226,128,133,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 972 "entities.lst"
      {"drbkarow;",{226,164,144,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1961 "entities.lst"
      {"sube;",{226,138,134,0,}},
#line 160 "entities.lst"
      {"Exists;",{226,136,131,0,}},
#line 1290 "entities.lst"
      {"lbrksld;",{226,166,143,0,}},
      {(char*)0}, {(char*)0},
#line 491 "entities.lst"
      {"Sc;",{226,170,188,0,}},
#line 1016 "entities.lst"
      {"emsp13;",{226,128,132,0,}},
      {(char*)0}, {(char*)0},
#line 80 "entities.lst"
      {"DJcy;",{208,130,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 248 "entities.lst"
      {"LJcy;",{208,137,0,}},
      {(char*)0},
#line 897 "entities.lst"
      {"cularr;",{226,134,182,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 19 "entities.lst"
      {"Aogon;",{196,132,0,}},
      {(char*)0}, {(char*)0},
#line 1112 "entities.lst"
      {"gesdotol;",{226,170,132,0,}},
      {(char*)0},
#line 582 "entities.lst"
      {"UpperRightArrow;",{226,134,151,0,}},
      {(char*)0},
#line 2002 "entities.lst"
      {"supnE;",{226,171,140,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 869 "entities.lst"
      {"colone;",{226,137,148,0,}},
      {(char*)0}, {(char*)0},
#line 453 "entities.lst"
      {"ReverseElement;",{226,136,139,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 2162 "entities.lst"
      {"vnsup;",{226,138,131,226,131,146,0,}},
      {(char*)0},
#line 607 "entities.lst"
      {"Wcirc;",{197,180,0,}},
      {(char*)0}, {(char*)0},
#line 355 "entities.lst"
      {"NotLessGreater;",{226,137,184,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 1873 "entities.lst"
      {"scnap;",{226,170,186,0,}},
      {(char*)0},
#line 49 "entities.lst"
      {"Ccaron;",{196,140,0,}},
      {(char*)0}, {(char*)0},
#line 1896 "entities.lst"
      {"shcy;",{209,136,0,}},
#line 428 "entities.lst"
      {"PrecedesEqual;",{226,170,175,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1876 "entities.lst"
      {"scsim;",{226,137,191,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 627 "entities.lst"
      {"ZHcy;",{208,150,0,}},
#line 210 "entities.lst"
      {"Icirc;",{195,142,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 1546 "entities.lst"
      {"npolint;",{226,168,148,0,}},
#line 1879 "entities.lst"
      {"sdotb;",{226,138,161,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 789 "entities.lst"
      {"boxhd;",{226,148,172,0,}},
#line 112 "entities.lst"
      {"DoubleRightTee;",{226,138,168,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 240 "entities.lst"
      {"KHcy;",{208,165,0,}},
#line 1881 "entities.lst"
      {"seArr;",{226,135,152,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 868 "entities.lst"
      {"colon;",{58,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 788 "entities.lst"
      {"boxhU;",{226,149,168,0,}},
#line 1889 "entities.lst"
      {"setminus;",{226,136,150,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1177 "entities.lst"
      {"hslash;",{226,132,143,0,}},
      {(char*)0}, {(char*)0},
#line 1441 "entities.lst"
      {"models;",{226,138,167,0,}},
      {(char*)0}, {(char*)0},
#line 1058 "entities.lst"
      {"fflig;",{239,172,128,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1915 "entities.lst"
      {"slarr;",{226,134,144,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 319 "entities.lst"
      {"Ncaron;",{197,135,0,}},
      {(char*)0},
#line 1607 "entities.lst"
      {"nvlt;",{60,226,131,146,0,}},
      {(char*)0}, {(char*)0},
#line 108 "entities.lst"
      {"DoubleLongLeftArrow;",{226,159,184,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 939 "entities.lst"
      {"demptyv;",{226,166,177,0,}},
#line 722 "entities.lst"
      {"bemptyv;",{226,166,176,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 266 "entities.lst"
      {"LeftDownVector;",{226,135,131,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 787 "entities.lst"
      {"boxhD;",{226,149,165,0,}},
#line 9 "entities.lst"
      {"Abreve;",{196,130,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 842 "entities.lst"
      {"cemptyv;",{226,166,178,0,}},
#line 861 "entities.lst"
      {"circleddash;",{226,138,157,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 101 "entities.lst"
      {"DotEqual;",{226,137,144,0,}},
#line 70 "entities.lst"
      {"ContourIntegral;",{226,136,174,0,}},
#line 1180 "entities.lst"
      {"hyphen;",{226,128,144,0,}},
#line 596 "entities.lst"
      {"Verbar;",{226,128,150,0,}},
      {(char*)0},
#line 153 "entities.lst"
      {"EqualTilde;",{226,137,130,0,}},
#line 564 "entities.lst"
      {"UnderBar;",{95,0,}},
#line 1062 "entities.lst"
      {"fjlig;",{102,106,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 1391 "entities.lst"
      {"lstrok;",{197,130,0,}},
      {(char*)0}, {(char*)0},
#line 277 "entities.lst"
      {"LeftUpDownVector;",{226,165,145,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 1178 "entities.lst"
      {"hstrok;",{196,167,0,}},
      {(char*)0},
#line 1606 "entities.lst"
      {"nvle;",{226,137,164,226,131,146,0,}},
#line 978 "entities.lst"
      {"dstrok;",{196,145,0,}},
      {(char*)0}, {(char*)0},
#line 299 "entities.lst"
      {"Longleftrightarrow;",{226,159,186,0,}},
#line 1897 "entities.lst"
      {"shortmid;",{226,136,163,0,}},
      {(char*)0},
#line 1965 "entities.lst"
      {"subne;",{226,138,138,0,}},
#line 1206 "entities.lst"
      {"imped;",{198,181,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1997 "entities.lst"
      {"supedot;",{226,171,132,0,}},
      {(char*)0},
#line 1929 "entities.lst"
      {"spades;",{226,153,160,0,}},
#line 77 "entities.lst"
      {"CupCap;",{226,137,141,0,}},
      {(char*)0}, {(char*)0},
#line 317 "entities.lst"
      {"NJcy;",{208,138,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 817 "entities.lst"
      {"bullet;",{226,128,162,0,}},
      {(char*)0},
#line 195 "entities.lst"
      {"Hcirc;",{196,164,0,}},
      {(char*)0},
#line 732 "entities.lst"
      {"bigodot;",{226,168,128,0,}},
#line 406 "entities.lst"
      {"Oscr;",{237,160,181,237,178,170,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1199 "entities.lst"
      {"ijlig;",{196,179,0,}},
#line 1372 "entities.lst"
      {"lozenge;",{226,151,138,0,}},
#line 856 "entities.lst"
      {"circlearrowright;",{226,134,187,0,}},
#line 1866 "entities.lst"
      {"scap;",{226,170,184,0,}},
      {(char*)0},
#line 2215 "entities.lst"
      {"yicy;",{209,151,0,}},
#line 1380 "entities.lst"
      {"lrm;",{226,128,142,0,}},
      {(char*)0},
#line 1127 "entities.lst"
      {"gne;",{226,170,136,0,}},
#line 1352 "entities.lst"
      {"lne;",{226,170,135,0,}},
#line 1115 "entities.lst"
      {"gfr;",{237,160,181,237,180,164,0,}},
#line 1333 "entities.lst"
      {"lfr;",{237,160,181,237,180,169,0,}},
#line 1001 "entities.lst"
      {"efr;",{237,160,181,237,180,162,0,}},
      {(char*)0},
#line 651 "entities.lst"
      {"afr;",{237,160,181,237,180,158,0,}},
#line 623 "entities.lst"
      {"Yfr;",{237,160,181,237,180,156,0,}},
#line 1060 "entities.lst"
      {"ffr;",{237,160,181,237,180,163,0,}},
#line 1005 "entities.lst"
      {"egs;",{226,170,150,0,}},
#line 697 "entities.lst"
      {"ast;",{42,0,}},
#line 1167 "entities.lst"
      {"hfr;",{237,160,181,237,180,165,0,}},
#line 845 "entities.lst"
      {"centerdot;",{194,183,0,}},
#line 754 "entities.lst"
      {"bne;",{61,226,131,165,0,}},
#line 941 "entities.lst"
      {"dfr;",{237,160,181,237,180,161,0,}},
#line 728 "entities.lst"
      {"bfr;",{237,160,181,237,180,159,0,}},
#line 439 "entities.lst"
      {"Qfr;",{237,160,181,237,180,148,0,}},
#line 449 "entities.lst"
      {"Rcaron;",{197,152,0,}},
#line 634 "entities.lst"
      {"Zfr;",{226,132,168,0,}},
      {(char*)0},
#line 1299 "entities.lst"
      {"ldquor;",{226,128,158,0,}},
      {(char*)0},
#line 145 "entities.lst"
      {"Element;",{226,136,136,0,}},
      {(char*)0}, {(char*)0},
#line 961 "entities.lst"
      {"dot;",{203,153,0,}},
#line 758 "entities.lst"
      {"bot;",{226,138,165,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 689 "entities.lst"
      {"ape;",{226,137,138,0,}},
      {(char*)0},
#line 846 "entities.lst"
      {"cfr;",{237,160,181,237,180,160,0,}},
      {(char*)0}, {(char*)0},
#line 1288 "entities.lst"
      {"lbrack;",{91,0,}},
#line 245 "entities.lst"
      {"Kfr;",{237,160,181,237,180,142,0,}},
#line 353 "entities.lst"
      {"NotLess;",{226,137,174,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 899 "entities.lst"
      {"cup;",{226,136,170,0,}},
      {(char*)0},
#line 268 "entities.lst"
      {"LeftFloor;",{226,140,138,0,}},
#line 1954 "entities.lst"
      {"starf;",{226,152,133,0,}},
      {(char*)0}, {(char*)0},
#line 735 "entities.lst"
      {"bigsqcup;",{226,168,134,0,}},
      {(char*)0},
#line 1871 "entities.lst"
      {"scirc;",{197,157,0,}},
#line 2177 "entities.lst"
      {"wfr;",{237,160,181,237,180,180,0,}},
      {(char*)0},
#line 1107 "entities.lst"
      {"geqslant;",{226,169,190,0,}},
#line 1317 "entities.lst"
      {"leqslant;",{226,169,189,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 1191 "entities.lst"
      {"ifr;",{237,160,181,237,180,166,0,}},
      {(char*)0},
#line 1212 "entities.lst"
      {"int;",{226,136,171,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1190 "entities.lst"
      {"iff;",{226,135,148,0,}},
      {(char*)0},
#line 2004 "entities.lst"
      {"supplus;",{226,171,128,0,}},
#line 1304 "entities.lst"
      {"leftarrow;",{226,134,144,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 573 "entities.lst"
      {"UpArrowBar;",{226,164,146,0,}},
      {(char*)0},
#line 1590 "entities.lst"
      {"ntriangleleft;",{226,139,170,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 509 "entities.lst"
      {"SquareSuperset;",{226,138,144,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1298 "entities.lst"
      {"ldquo;",{226,128,156,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 719 "entities.lst"
      {"bdquo;",{226,128,158,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 262 "entities.lst"
      {"LeftArrowRightArrow;",{226,135,134,0,}},
#line 929 "entities.lst"
      {"dblac;",{203,157,0,}},
      {(char*)0},
#line 2010 "entities.lst"
      {"supsim;",{226,171,136,0,}},
#line 338 "entities.lst"
      {"NotEqual;",{226,137,160,0,}},
#line 271 "entities.lst"
      {"LeftTee;",{226,138,163,0,}},
#line 1494 "entities.lst"
      {"nfr;",{237,160,181,237,180,171,0,}},
      {(char*)0},
#line 1595 "entities.lst"
      {"num;",{35,0,}},
#line 1371 "entities.lst"
      {"loz;",{226,151,138,0,}},
#line 2009 "entities.lst"
      {"supsetneqq;",{226,171,140,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 371 "entities.lst"
      {"NotSquareSupersetEqual;",{226,139,163,0,}},
#line 1496 "entities.lst"
      {"nge;",{226,137,177,0,}},
#line 1531 "entities.lst"
      {"not;",{194,172,0,}},
      {(char*)0},
#line 1908 "entities.lst"
      {"simg;",{226,170,158,0,}},
#line 1502 "entities.lst"
      {"ngt;",{226,137,175,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 1019 "entities.lst"
      {"eng;",{197,139,0,}},
      {(char*)0},
#line 666 "entities.lst"
      {"ang;",{226,136,160,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1547 "entities.lst"
      {"npr;",{226,138,128,0,}},
      {(char*)0},
#line 494 "entities.lst"
      {"Scirc;",{197,156,0,}},
#line 608 "entities.lst"
      {"Wedge;",{226,139,128,0,}},
#line 1117 "entities.lst"
      {"ggg;",{226,139,153,0,}},
      {(char*)0},
#line 726 "entities.lst"
      {"beth;",{226,132,182,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 1535 "entities.lst"
      {"notinva;",{226,136,137,0,}},
#line 1440 "entities.lst"
      {"mnplus;",{226,136,147,0,}},
#line 2227 "entities.lst"
      {"zfr;",{237,160,181,237,180,183,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 769 "entities.lst"
      {"boxHu;",{226,149,167,0,}},
#line 163 "entities.lst"
      {"Ffr;",{237,160,181,237,180,137,0,}},
#line 658 "entities.lst"
      {"amalg;",{226,168,191,0,}},
#line 517 "entities.lst"
      {"Succeeds;",{226,137,187,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1521 "entities.lst"
      {"nleqslant;",{226,169,189,204,184,0,}},
#line 1326 "entities.lst"
      {"lessdot;",{226,139,150,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 1609 "entities.lst"
      {"nvrArr;",{226,164,131,0,}},
      {(char*)0}, {(char*)0},
#line 167 "entities.lst"
      {"ForAll;",{226,136,128,0,}},
#line 1444 "entities.lst"
      {"mscr;",{237,160,181,237,179,130,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1239 "entities.lst"
      {"jfr;",{237,160,181,237,180,167,0,}},
      {(char*)0},
#line 838 "entities.lst"
      {"ccupssm;",{226,169,144,0,}},
      {(char*)0},
#line 648 "entities.lst"
      {"aelig",{195,166,0,}},
      {(char*)0},
#line 1450 "entities.lst"
      {"nGt;",{226,137,171,226,131,146,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 2012 "entities.lst"
      {"supsup;",{226,171,150,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 920 "entities.lst"
      {"cylcty;",{226,140,173,0,}},
      {(char*)0}, {(char*)0},
#line 946 "entities.lst"
      {"diamondsuit;",{226,153,166,0,}},
#line 142 "entities.lst"
      {"Efr;",{237,160,181,237,180,136,0,}},
      {(char*)0}, {(char*)0},
#line 850 "entities.lst"
      {"chi;",{207,135,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 2161 "entities.lst"
      {"vnsub;",{226,138,130,226,131,146,0,}},
      {(char*)0},
#line 1256 "entities.lst"
      {"lArr;",{226,135,144,0,}},
      {(char*)0},
#line 1867 "entities.lst"
      {"scaron;",{197,161,0,}},
#line 380 "entities.lst"
      {"NotTilde;",{226,137,129,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 1153 "entities.lst"
      {"hArr;",{226,135,148,0,}},
#line 966 "entities.lst"
      {"dotsquare;",{226,138,161,0,}},
      {(char*)0},
#line 921 "entities.lst"
      {"dArr;",{226,135,147,0,}},
      {(char*)0}, {(char*)0},
#line 745 "entities.lst"
      {"blacktriangle;",{226,150,180,0,}},
#line 56 "entities.lst"
      {"CenterDot;",{194,183,0,}},
      {(char*)0},
#line 312 "entities.lst"
      {"Mfr;",{237,160,181,237,180,144,0,}},
#line 368 "entities.lst"
      {"NotSquareSubset;",{226,138,143,204,184,0,}},
#line 1012 "entities.lst"
      {"emacr;",{196,147,0,}},
      {(char*)0},
#line 657 "entities.lst"
      {"amacr;",{196,129,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1148 "entities.lst"
      {"gtreqqless;",{226,170,140,0,}},
      {(char*)0}, {(char*)0},
#line 67 "entities.lst"
      {"Colone;",{226,169,180,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 1329 "entities.lst"
      {"lessgtr;",{226,137,182,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 354 "entities.lst"
      {"NotLessEqual;",{226,137,176,0,}},
      {(char*)0}, {(char*)0},
#line 949 "entities.lst"
      {"digamma;",{207,157,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1044 "entities.lst"
      {"eta;",{206,183,0,}},
      {(char*)0},
#line 795 "entities.lst"
      {"boxuR;",{226,149,152,0,}},
      {(char*)0}, {(char*)0},
#line 748 "entities.lst"
      {"blacktriangleright;",{226,150,184,0,}},
      {(char*)0}, {(char*)0},
#line 1941 "entities.lst"
      {"sqsupe;",{226,138,146,0,}},
#line 560 "entities.lst"
      {"Ufr;",{237,160,181,237,180,152,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 379 "entities.lst"
      {"NotSupersetEqual;",{226,138,137,0,}},
      {(char*)0},
#line 1893 "entities.lst"
      {"sfrown;",{226,140,162,0,}},
#line 649 "entities.lst"
      {"aelig;",{195,166,0,}},
#line 131 "entities.lst"
      {"Dstrok;",{196,144,0,}},
#line 1942 "entities.lst"
      {"sqsupset;",{226,138,144,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 1111 "entities.lst"
      {"gesdoto;",{226,170,130,0,}},
#line 1321 "entities.lst"
      {"lesdoto;",{226,170,129,0,}},
#line 306 "entities.lst"
      {"Lstrok;",{197,129,0,}},
      {(char*)0}, {(char*)0},
#line 42 "entities.lst"
      {"CHcy;",{208,167,0,}},
      {(char*)0}, {(char*)0},
#line 1200 "entities.lst"
      {"imacr;",{196,171,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 61 "entities.lst"
      {"CirclePlus;",{226,138,149,0,}},
      {(char*)0},
#line 66 "entities.lst"
      {"Colon;",{226,136,183,0,}},
      {(char*)0}, {(char*)0},
#line 860 "entities.lst"
      {"circledcirc;",{226,138,154,0,}},
      {(char*)0},
#line 1943 "entities.lst"
      {"sqsupseteq;",{226,138,146,0,}},
      {(char*)0}, {(char*)0},
#line 1755 "entities.lst"
      {"questeq;",{226,137,159,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 492 "entities.lst"
      {"Scaron;",{197,160,0,}},
      {(char*)0},
#line 1293 "entities.lst"
      {"lcedil;",{196,188,0,}},
#line 1449 "entities.lst"
      {"nGg;",{226,139,153,204,184,0,}},
#line 1959 "entities.lst"
      {"subE;",{226,171,133,0,}},
#line 180 "entities.lst"
      {"Gfr;",{237,160,181,237,180,138,0,}},
      {(char*)0},
#line 1260 "entities.lst"
      {"lEg;",{226,170,139,0,}},
#line 1872 "entities.lst"
      {"scnE;",{226,170,182,0,}},
      {(char*)0},
#line 1753 "entities.lst"
      {"quatint;",{226,168,150,0,}},
      {(char*)0},
#line 235 "entities.lst"
      {"Jfr;",{237,160,181,237,180,141,0,}},
      {(char*)0}, {(char*)0},
#line 68 "entities.lst"
      {"Congruent;",{226,137,161,0,}},
      {(char*)0},
#line 1940 "entities.lst"
      {"sqsup;",{226,138,144,0,}},
#line 1899 "entities.lst"
      {"shy",{194,173,0,}},
#line 834 "entities.lst"
      {"ccedil",{195,167,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 1283 "entities.lst"
      {"late;",{226,170,173,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 90 "entities.lst"
      {"Dfr;",{237,160,181,237,180,135,0,}},
#line 835 "entities.lst"
      {"ccedil;",{195,167,0,}},
      {(char*)0},
#line 1302 "entities.lst"
      {"ldsh;",{226,134,178,0,}},
#line 216 "entities.lst"
      {"Im;",{226,132,145,0,}},
#line 243 "entities.lst"
      {"Kcedil;",{196,182,0,}},
#line 2159 "entities.lst"
      {"vfr;",{237,160,181,237,180,179,0,}},
      {(char*)0},
#line 291 "entities.lst"
      {"Lfr;",{237,160,181,237,180,143,0,}},
#line 1901 "entities.lst"
      {"sigma;",{207,131,0,}},
#line 41 "entities.lst"
      {"Bumpeq;",{226,137,142,0,}},
#line 99 "entities.lst"
      {"Dot;",{194,168,0,}},
#line 24 "entities.lst"
      {"Ascr;",{237,160,181,237,178,156,0,}},
#line 119 "entities.lst"
      {"DownBreve;",{204,145,0,}},
      {(char*)0},
#line 824 "entities.lst"
      {"capand;",{226,169,132,0,}},
#line 2214 "entities.lst"
      {"yfr;",{237,160,181,237,180,182,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 1747 "entities.lst"
      {"qfr;",{237,160,181,237,180,174,0,}},
      {(char*)0},
#line 985 "entities.lst"
      {"dzcy;",{209,159,0,}},
#line 1905 "entities.lst"
      {"simdot;",{226,169,170,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 1156 "entities.lst"
      {"hamilt;",{226,132,139,0,}},
#line 955 "entities.lst"
      {"divonx;",{226,139,135,0,}},
      {(char*)0}, {(char*)0},
#line 430 "entities.lst"
      {"PrecedesTilde;",{226,137,190,0,}},
#line 1325 "entities.lst"
      {"lessapprox;",{226,170,133,0,}},
      {(char*)0}, {(char*)0},
#line 1108 "entities.lst"
      {"ges;",{226,169,190,0,}},
#line 1318 "entities.lst"
      {"les;",{226,169,189,0,}},
#line 1105 "entities.lst"
      {"geq;",{226,137,165,0,}},
#line 1315 "entities.lst"
      {"leq;",{226,137,164,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 800 "entities.lst"
      {"boxvL;",{226,149,161,0,}},
#line 661 "entities.lst"
      {"and;",{226,136,167,0,}},
#line 507 "entities.lst"
      {"SquareSubset;",{226,138,143,0,}},
#line 959 "entities.lst"
      {"dollar;",{36,0,}},
#line 612 "entities.lst"
      {"Xfr;",{237,160,181,237,180,155,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 968 "entities.lst"
      {"downarrow;",{226,134,147,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 831 "entities.lst"
      {"caron;",{203,135,0,}},
      {(char*)0}, {(char*)0},
#line 1902 "entities.lst"
      {"sigmaf;",{207,130,0,}},
      {(char*)0}, {(char*)0},
#line 392 "entities.lst"
      {"Ocirc",{195,148,0,}},
#line 739 "entities.lst"
      {"biguplus;",{226,168,132,0,}},
#line 1327 "entities.lst"
      {"lesseqgtr;",{226,139,154,0,}},
      {(char*)0},
#line 283 "entities.lst"
      {"Leftarrow;",{226,135,144,0,}},
#line 1301 "entities.lst"
      {"ldrushar;",{226,165,139,0,}},
      {(char*)0},
#line 1179 "entities.lst"
      {"hybull;",{226,129,131,0,}},
#line 575 "entities.lst"
      {"UpDownArrow;",{226,134,149,0,}},
#line 1477 "entities.lst"
      {"ncedil;",{197,134,0,}},
#line 352 "entities.lst"
      {"NotLeftTriangleEqual;",{226,139,172,0,}},
#line 127 "entities.lst"
      {"DownTee;",{226,138,164,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 991 "entities.lst"
      {"easter;",{226,169,174,0,}},
#line 580 "entities.lst"
      {"Updownarrow;",{226,135,149,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 146 "entities.lst"
      {"Emacr;",{196,146,0,}},
      {(char*)0},
#line 501 "entities.lst"
      {"Sigma;",{206,163,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1272 "entities.lst"
      {"larr;",{226,134,144,0,}},
      {(char*)0}, {(char*)0},
#line 57 "entities.lst"
      {"Cfr;",{226,132,173,0,}},
#line 1589 "entities.lst"
      {"ntlg;",{226,137,184,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1158 "entities.lst"
      {"harr;",{226,134,148,0,}},
      {(char*)0}, {(char*)0},
#line 925 "entities.lst"
      {"darr;",{226,134,147,0,}},
#line 157 "entities.lst"
      {"Eta;",{206,151,0,}},
#line 76 "entities.lst"
      {"Cup;",{226,139,147,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 429 "entities.lst"
      {"PrecedesSlantEqual;",{226,137,188,0,}},
      {(char*)0},
#line 342 "entities.lst"
      {"NotGreaterEqual;",{226,137,177,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 1278 "entities.lst"
      {"larrpl;",{226,164,185,0,}},
#line 1284 "entities.lst"
      {"lates;",{226,170,173,239,184,128,0,}},
      {(char*)0},
#line 1615 "entities.lst"
      {"nwarrow;",{226,134,150,0,}},
      {(char*)0},
#line 1277 "entities.lst"
      {"larrlp;",{226,134,171,0,}},
      {(char*)0}, {(char*)0},
#line 1537 "entities.lst"
      {"notinvc;",{226,139,182,0,}},
#line 761 "entities.lst"
      {"boxDL;",{226,149,151,0,}},
#line 189 "entities.lst"
      {"GreaterTilde;",{226,137,179,0,}},
#line 579 "entities.lst"
      {"Uparrow;",{226,135,145,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 563 "entities.lst"
      {"Umacr;",{197,170,0,}},
      {(char*)0},
#line 1064 "entities.lst"
      {"fllig;",{239,172,130,0,}},
      {(char*)0},
#line 1465 "entities.lst"
      {"napid;",{226,137,139,204,184,0,}},
#line 2000 "entities.lst"
      {"suplarr;",{226,165,187,0,}},
#line 945 "entities.lst"
      {"diamond;",{226,139,132,0,}},
#line 393 "entities.lst"
      {"Ocirc;",{195,148,0,}},
      {(char*)0}, {(char*)0},
#line 39 "entities.lst"
      {"Breve;",{203,152,0,}},
      {(char*)0},
#line 770 "entities.lst"
      {"boxUL;",{226,149,157,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 329 "entities.lst"
      {"Nfr;",{237,160,181,237,180,145,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 1314 "entities.lst"
      {"leg;",{226,139,154,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 333 "entities.lst"
      {"Not;",{226,171,172,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 937 "entities.lst"
      {"deg;",{194,176,0,}},
      {(char*)0}, {(char*)0},
#line 915 "entities.lst"
      {"curvearrowright;",{226,134,183,0,}},
#line 1856 "entities.lst"
      {"rtri;",{226,150,185,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 699 "entities.lst"
      {"asympeq;",{226,137,141,0,}},
      {(char*)0},
#line 1466 "entities.lst"
      {"napos;",{197,137,0,}},
#line 279 "entities.lst"
      {"LeftUpVector;",{226,134,191,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 1851 "entities.lst"
      {"rsqb;",{93,0,}},
      {(char*)0}, {(char*)0},
#line 55 "entities.lst"
      {"Cedilla;",{194,184,0,}},
      {(char*)0},
#line 2130 "entities.lst"
      {"vArr;",{226,135,149,0,}},
      {(char*)0},
#line 790 "entities.lst"
      {"boxhu;",{226,148,180,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 602 "entities.lst"
      {"VeryThinSpace;",{226,128,138,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 303 "entities.lst"
      {"LowerRightArrow;",{226,134,152,0,}},
      {(char*)0},
#line 1571 "entities.lst"
      {"nsqsupe;",{226,139,163,0,}},
#line 712 "entities.lst"
      {"barvee;",{226,138,189,0,}},
#line 1439 "entities.lst"
      {"mldr;",{226,128,166,0,}},
#line 36 "entities.lst"
      {"Beta;",{206,146,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 1911 "entities.lst"
      {"simlE;",{226,170,159,0,}},
#line 1255 "entities.lst"
      {"lAarr;",{226,135,154,0,}},
#line 1863 "entities.lst"
      {"sbquo;",{226,128,154,0,}},
      {(char*)0},
#line 64 "entities.lst"
      {"CloseCurlyDoubleQuote;",{226,128,157,0,}},
#line 1980 "entities.lst"
      {"succnapprox;",{226,170,186,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 482 "entities.lst"
      {"RoundImplies;",{226,165,176,0,}},
      {(char*)0},
#line 1960 "entities.lst"
      {"subdot;",{226,170,189,0,}},
#line 1926 "entities.lst"
      {"solb;",{226,167,132,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1154 "entities.lst"
      {"hairsp;",{226,128,138,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 2001 "entities.lst"
      {"supmult;",{226,171,130,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 933 "entities.lst"
      {"ddagger;",{226,128,161,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 1010 "entities.lst"
      {"els;",{226,170,149,0,}},
      {(char*)0}, {(char*)0},
#line 609 "entities.lst"
      {"Wfr;",{237,160,181,237,180,154,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 1438 "entities.lst"
      {"mlcp;",{226,171,155,0,}},
      {(char*)0},
#line 176 "entities.lst"
      {"Gcedil;",{196,162,0,}},
      {(char*)0}, {(char*)0},
#line 107 "entities.lst"
      {"DoubleLeftTee;",{226,171,164,0,}},
#line 1922 "entities.lst"
      {"smte;",{226,170,172,0,}},
      {(char*)0}, {(char*)0},
#line 830 "entities.lst"
      {"caret;",{226,129,129,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 59 "entities.lst"
      {"CircleDot;",{226,138,153,0,}},
      {(char*)0}, {(char*)0},
#line 58 "entities.lst"
      {"Chi;",{206,167,0,}},
      {(char*)0},
#line 456 "entities.lst"
      {"Rfr;",{226,132,156,0,}},
      {(char*)0},
#line 202 "entities.lst"
      {"HumpDownHump;",{226,137,142,0,}},
      {(char*)0},
#line 213 "entities.lst"
      {"Ifr;",{226,132,145,0,}},
      {(char*)0},
#line 220 "entities.lst"
      {"Int;",{226,136,172,0,}},
      {(char*)0},
#line 1346 "entities.lst"
      {"lmidot;",{197,128,0,}},
      {(char*)0}, {(char*)0},
#line 1836 "entities.lst"
      {"rnmid;",{226,171,174,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 257 "entities.lst"
      {"Lcedil;",{196,187,0,}},
      {(char*)0},
#line 928 "entities.lst"
      {"dbkarow;",{226,164,143,0,}},
#line 1968 "entities.lst"
      {"subset;",{226,138,130,0,}},
#line 1280 "entities.lst"
      {"larrtl;",{226,134,162,0,}},
#line 1840 "entities.lst"
      {"ropar;",{226,166,134,0,}},
      {(char*)0},
#line 1937 "entities.lst"
      {"sqsube;",{226,138,145,0,}},
      {(char*)0},
#line 1061 "entities.lst"
      {"filig;",{239,172,129,0,}},
#line 1143 "entities.lst"
      {"gtquest;",{226,169,188,0,}},
#line 1400 "entities.lst"
      {"ltquest;",{226,169,187,0,}},
      {(char*)0}, {(char*)0},
#line 361 "entities.lst"
      {"NotPrecedes;",{226,138,128,0,}},
      {(char*)0}, {(char*)0},
#line 1938 "entities.lst"
      {"sqsubset;",{226,138,143,0,}},
      {(char*)0},
#line 1528 "entities.lst"
      {"nmid;",{226,136,164,0,}},
      {(char*)0},
#line 273 "entities.lst"
      {"LeftTeeVector;",{226,165,154,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 1969 "entities.lst"
      {"subseteq;",{226,138,134,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 1257 "entities.lst"
      {"lAtail;",{226,164,155,0,}},
      {(char*)0}, {(char*)0},
#line 1939 "entities.lst"
      {"sqsubseteq;",{226,138,145,0,}},
      {(char*)0},
#line 572 "entities.lst"
      {"UpArrow;",{226,134,145,0,}},
#line 351 "entities.lst"
      {"NotLeftTriangleBar;",{226,167,143,204,184,0,}},
      {(char*)0}, {(char*)0},
#line 1455 "entities.lst"
      {"nLt;",{226,137,170,226,131,146,0,}},
      {(char*)0}, {(char*)0},
#line 1430 "entities.lst"
      {"midast;",{42,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 1487 "entities.lst"
      {"nearrow;",{226,134,151,0,}},
      {(char*)0},
#line 855 "entities.lst"
      {"circlearrowleft;",{226,134,186,0,}},
#line 201 "entities.lst"
      {"Hstrok;",{196,166,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 1249 "entities.lst"
      {"kfr;",{237,160,181,237,180,168,0,}},
#line 1936 "entities.lst"
      {"sqsub;",{226,138,143,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 134 "entities.lst"
      {"ETH;",{195,144,0,}},
      {(char*)0},
#line 552 "entities.lst"
      {"Uarr;",{226,134,159,0,}},
#line 1559 "entities.lst"
      {"nsc;",{226,138,129,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 1516 "entities.lst"
      {"nle;",{226,137,176,0,}},
#line 129 "entities.lst"
      {"Downarrow;",{226,135,147,0,}},
      {(char*)0},
#line 1978 "entities.lst"
      {"succcurlyeq;",{226,137,189,0,}},
#line 1525 "entities.lst"
      {"nlt;",{226,137,174,0,}},
      {(char*)0}, {(char*)0},
#line 2153 "entities.lst"
      {"vee;",{226,136,168,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 680 "entities.lst"
      {"angrtvbd;",{226,166,157,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 72 "entities.lst"
      {"Coproduct;",{226,136,144,0,}},
      {(char*)0},
#line 515 "entities.lst"
      {"Subset;",{226,139,144,0,}},
      {(char*)0},
#line 1855 "entities.lst"
      {"rtimes;",{226,139,138,0,}},
#line 2213 "entities.lst"
      {"yen;",{194,165,0,}},
      {(char*)0},
#line 50 "entities.lst"
      {"Ccedil",{195,135,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 1539 "entities.lst"
      {"notniva;",{226,136,140,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 488 "entities.lst"
      {"SHcy;",{208,168,0,}},
      {(char*)0},
#line 51 "entities.lst"
      {"Ccedil;",{195,135,0,}},
#line 1857 "entities.lst"
      {"rtrie;",{226,138,181,0,}},
      {(char*)0}, {(char*)0},
#line 196 "entities.lst"
      {"Hfr;",{226,132,140,0,}},
      {(char*)0}, {(char*)0},
#line 721 "entities.lst"
      {"because;",{226,136,181,0,}},
#line 1046 "entities.lst"
      {"eth;",{195,176,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 1384 "entities.lst"
      {"lsh;",{226,134,176,0,}},
#line 1563 "entities.lst"
      {"nshortmid;",{226,136,164,0,}},
#line 1923 "entities.lst"
      {"smtes;",{226,170,172,239,184,128,0,}},
      {(char*)0},
#line 670 "entities.lst"
      {"angmsdaa;",{226,166,168,0,}},
#line 10 "entities.lst"
      {"Acirc",{195,130,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1165 "entities.lst"
      {"hellip;",{226,128,166,0,}},
#line 948 "entities.lst"
      {"die;",{194,168,0,}},
      {(char*)0},
#line 84 "entities.lst"
      {"Darr;",{226,134,161,0,}},
      {(char*)0},
#line 457 "entities.lst"
      {"Rho;",{206,161,0,}},
      {(char*)0},
#line 1964 "entities.lst"
      {"subnE;",{226,171,139,0,}},
      {(char*)0},
#line 2141 "entities.lst"
      {"varr;",{226,134,149,0,}},
      {(char*)0},
#line 255 "entities.lst"
      {"Larr;",{226,134,158,0,}},
      {(char*)0}, {(char*)0},
#line 776 "entities.lst"
      {"boxVL;",{226,149,163,0,}},
      {(char*)0}, {(char*)0},
#line 109 "entities.lst"
      {"DoubleLongLeftRightArrow;",{226,159,186,0,}},
      {(char*)0},
#line 1819 "entities.lst"
      {"rhov;",{207,177,0,}},
#line 851 "entities.lst"
      {"cir;",{226,151,139,0,}},
#line 2011 "entities.lst"
      {"supsub;",{226,171,148,0,}},
#line 559 "entities.lst"
      {"Udblac;",{197,176,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 2007 "entities.lst"
      {"supseteqq;",{226,171,134,0,}},
#line 1898 "entities.lst"
      {"shortparallel;",{226,136,165,0,}},
#line 518 "entities.lst"
      {"SucceedsEqual;",{226,170,176,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 260 "entities.lst"
      {"LeftArrow;",{226,134,144,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 320 "entities.lst"
      {"Ncedil;",{197,133,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 96 "entities.lst"
      {"Diamond;",{226,139,132,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 1913 "entities.lst"
      {"simplus;",{226,168,164,0,}},
      {(char*)0},
#line 1892 "entities.lst"
      {"sfr;",{237,160,181,237,180,176,0,}},
      {(char*)0},
#line 1984 "entities.lst"
      {"sum;",{226,136,145,0,}},
#line 938 "entities.lst"
      {"delta;",{206,180,0,}},
#line 327 "entities.lst"
      {"NestedLessLess;",{226,137,170,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 434 "entities.lst"
      {"Proportional;",{226,136,157,0,}},
      {(char*)0},
#line 1992 "entities.lst"
      {"sup;",{226,138,131,0,}},
      {(char*)0},
#line 1790 "entities.lst"
      {"rbrace;",{125,0,}},
#line 1409 "entities.lst"
      {"mDDot;",{226,136,186,0,}},
#line 825 "entities.lst"
      {"capbrcup;",{226,169,137,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 1920 "entities.lst"
      {"smile;",{226,140,163,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1977 "entities.lst"
      {"succapprox;",{226,170,184,0,}},
      {(char*)0}, {(char*)0},
#line 217 "entities.lst"
      {"Imacr;",{196,170,0,}},
#line 381 "entities.lst"
      {"NotTildeEqual;",{226,137,132,0,}},
#line 1536 "entities.lst"
      {"notinvb;",{226,139,183,0,}},
      {(char*)0}, {(char*)0},
#line 11 "entities.lst"
      {"Acirc;",{195,130,0,}},
#line 1935 "entities.lst"
      {"sqcups;",{226,138,148,239,184,128,0,}},
#line 2229 "entities.lst"
      {"zigrarr;",{226,135,157,0,}},
      {(char*)0},
#line 1122 "entities.lst"
      {"gla;",{226,170,165,0,}},
      {(char*)0}, {(char*)0},
#line 1508 "entities.lst"
      {"nis;",{226,139,188,0,}},
      {(char*)0},
#line 499 "entities.lst"
      {"ShortRightArrow;",{226,134,146,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1944 "entities.lst"
      {"squ;",{226,150,161,0,}},
      {(char*)0},
#line 1266 "entities.lst"
      {"lang;",{226,159,168,0,}},
#line 1201 "entities.lst"
      {"image;",{226,132,145,0,}},
#line 360 "entities.lst"
      {"NotNestedLessLess;",{226,170,161,204,184,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1164 "entities.lst"
      {"heartsuit;",{226,153,165,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1097 "entities.lst"
      {"gammad;",{207,157,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 898 "entities.lst"
      {"cularrp;",{226,164,189,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 870 "entities.lst"
      {"coloneq;",{226,137,148,0,}},
      {(char*)0},
#line 1282 "entities.lst"
      {"latail;",{226,164,153,0,}},
      {(char*)0},
#line 496 "entities.lst"
      {"Sfr;",{237,160,181,237,180,150,0,}},
      {(char*)0},
#line 522 "entities.lst"
      {"Sum;",{226,136,145,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 1934 "entities.lst"
      {"sqcup;",{226,138,148,0,}},
#line 523 "entities.lst"
      {"Sup;",{226,139,145,0,}},
      {(char*)0}, {(char*)0},
#line 1273 "entities.lst"
      {"larrb;",{226,135,164,0,}},
      {(char*)0}, {(char*)0},
#line 450 "entities.lst"
      {"Rcedil;",{197,150,0,}},
#line 1962 "entities.lst"
      {"subedot;",{226,171,131,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1427 "entities.lst"
      {"micro",{194,181,0,}},
#line 1268 "entities.lst"
      {"langle;",{226,159,168,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 43 "entities.lst"
      {"COPY",{194,169,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 2054 "entities.lst"
      {"tosa;",{226,164,169,0,}},
#line 951 "entities.lst"
      {"div;",{195,183,0,}},
#line 40 "entities.lst"
      {"Bscr;",{226,132,172,0,}},
      {(char*)0},
#line 1837 "entities.lst"
      {"roang;",{226,159,173,0,}},
#line 2048 "entities.lst"
      {"toea;",{226,164,168,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 44 "entities.lst"
      {"COPY;",{194,169,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 420 "entities.lst"
      {"Pfr;",{237,160,181,237,180,147,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 1464 "entities.lst"
      {"napE;",{226,169,176,204,184,0,}},
      {(char*)0},
#line 1096 "entities.lst"
      {"gamma;",{206,179,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 294 "entities.lst"
      {"Lmidot;",{196,191,0,}},
#line 1903 "entities.lst"
      {"sigmav;",{207,130,0,}},
#line 358 "entities.lst"
      {"NotLessTilde;",{226,137,180,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 603 "entities.lst"
      {"Vfr;",{237,160,181,237,180,153,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 118 "entities.lst"
      {"DownArrowUpArrow;",{226,135,181,0,}},
#line 707 "entities.lst"
      {"backcong;",{226,137,140,0,}},
      {(char*)0},
#line 574 "entities.lst"
      {"UpArrowDownArrow;",{226,135,133,0,}},
#line 1844 "entities.lst"
      {"rpar;",{41,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 1267 "entities.lst"
      {"langd;",{226,166,145,0,}},
      {(char*)0}, {(char*)0},
#line 1462 "entities.lst"
      {"nang;",{226,136,160,226,131,146,0,}},
      {(char*)0},
#line 616 "entities.lst"
      {"YAcy;",{208,175,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 310 "entities.lst"
      {"MediumSpace;",{226,129,159,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 829 "entities.lst"
      {"caps;",{226,136,169,239,184,128,0,}},
#line 1247 "entities.lst"
      {"kcedil;",{196,183,0,}},
#line 436 "entities.lst"
      {"Psi;",{206,168,0,}},
      {(char*)0},
#line 280 "entities.lst"
      {"LeftUpVectorBar;",{226,165,152,0,}},
      {(char*)0},
#line 242 "entities.lst"
      {"Kappa;",{206,154,0,}},
      {(char*)0}, {(char*)0},
#line 370 "entities.lst"
      {"NotSquareSuperset;",{226,138,144,204,184,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 1810 "entities.lst"
      {"reg",{194,174,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 1428 "entities.lst"
      {"micro;",{194,181,0,}},
      {(char*)0},
#line 2055 "entities.lst"
      {"tprime;",{226,128,180,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 2065 "entities.lst"
      {"trie;",{226,137,156,0,}},
      {(char*)0}, {(char*)0},
#line 1966 "entities.lst"
      {"subplus;",{226,170,191,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1792 "entities.lst"
      {"rbrke;",{226,166,140,0,}},
#line 1510 "entities.lst"
      {"niv;",{226,136,139,0,}},
#line 782 "entities.lst"
      {"boxdL;",{226,149,149,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 2050 "entities.lst"
      {"topbot;",{226,140,182,0,}},
#line 548 "entities.lst"
      {"Tscr;",{237,160,181,237,178,175,0,}},
#line 656 "entities.lst"
      {"alpha;",{206,177,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1847 "entities.lst"
      {"rrarr;",{226,135,137,0,}},
      {(char*)0}, {(char*)0},
#line 826 "entities.lst"
      {"capcap;",{226,169,139,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 447 "entities.lst"
      {"Rarr;",{226,134,160,0,}},
#line 1838 "entities.lst"
      {"roarr;",{226,135,190,0,}},
      {(char*)0},
#line 347 "entities.lst"
      {"NotGreaterTilde;",{226,137,181,0,}},
#line 1956 "entities.lst"
      {"straightphi;",{207,149,0,}},
#line 1973 "entities.lst"
      {"subsim;",{226,171,135,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1874 "entities.lst"
      {"scnsim;",{226,139,169,0,}},
      {(char*)0}, {(char*)0},
#line 1972 "entities.lst"
      {"subsetneqq;",{226,171,139,0,}},
      {(char*)0}, {(char*)0},
#line 1541 "entities.lst"
      {"notnivc;",{226,139,189,0,}},
#line 205 "entities.lst"
      {"IJlig;",{196,178,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 986 "entities.lst"
      {"dzigrarr;",{226,159,191,0,}},
      {(char*)0}, {(char*)0},
#line 334 "entities.lst"
      {"NotCongruent;",{226,137,162,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 539 "entities.lst"
      {"Theta;",{206,152,0,}},
#line 2198 "entities.lst"
      {"xotime;",{226,168,130,0,}},
      {(char*)0},
#line 2156 "entities.lst"
      {"vellip;",{226,139,174,0,}},
#line 305 "entities.lst"
      {"Lsh;",{226,134,176,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 116 "entities.lst"
      {"DownArrow;",{226,134,147,0,}},
#line 1142 "entities.lst"
      {"gtlPar;",{226,166,149,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 1718 "entities.lst"
      {"pr;",{226,137,186,0,}},
      {(char*)0}, {(char*)0},
#line 1845 "entities.lst"
      {"rpargt;",{226,166,148,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 2205 "entities.lst"
      {"xvee;",{226,139,129,0,}},
#line 1870 "entities.lst"
      {"scedil;",{197,159,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 421 "entities.lst"
      {"Phi;",{206,166,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 53 "entities.lst"
      {"Cconint;",{226,136,176,0,}},
#line 407 "entities.lst"
      {"Oslash",{195,152,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 506 "entities.lst"
      {"SquareIntersection;",{226,138,147,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 89 "entities.lst"
      {"Delta;",{206,148,0,}},
      {(char*)0}, {(char*)0},
#line 1059 "entities.lst"
      {"ffllig;",{239,172,132,0,}},
#line 408 "entities.lst"
      {"Oslash;",{195,152,0,}},
      {(char*)0}, {(char*)0},
#line 828 "entities.lst"
      {"capdot;",{226,169,128,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1975 "entities.lst"
      {"subsup;",{226,171,147,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 827 "entities.lst"
      {"capcup;",{226,169,135,0,}},
#line 1570 "entities.lst"
      {"nsqsube;",{226,139,162,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 1909 "entities.lst"
      {"simgE;",{226,170,160,0,}},
      {(char*)0}, {(char*)0},
#line 1591 "entities.lst"
      {"ntrianglelefteq;",{226,139,172,0,}},
      {(char*)0},
#line 923 "entities.lst"
      {"dagger;",{226,128,160,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1740 "entities.lst"
      {"prop;",{226,136,157,0,}},
      {(char*)0},
#line 1157 "entities.lst"
      {"hardcy;",{209,138,0,}},
      {(char*)0},
#line 2008 "entities.lst"
      {"supsetneq;",{226,138,139,0,}},
      {(char*)0},
#line 1805 "entities.lst"
      {"real;",{226,132,156,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 553 "entities.lst"
      {"Uarrocir;",{226,165,137,0,}},
      {(char*)0}, {(char*)0},
#line 2016 "entities.lst"
      {"swarrow;",{226,134,153,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 1861 "entities.lst"
      {"rx;",{226,132,158,0,}},
#line 1815 "entities.lst"
      {"rhard;",{226,135,129,0,}},
      {(char*)0}, {(char*)0},
#line 2036 "entities.lst"
      {"thinsp;",{226,128,137,0,}},
      {(char*)0},
#line 679 "entities.lst"
      {"angrtvb;",{226,138,190,0,}},
      {(char*)0}, {(char*)0},
#line 1927 "entities.lst"
      {"solbar;",{226,140,191,0,}},
#line 174 "entities.lst"
      {"Gammad;",{207,156,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 374 "entities.lst"
      {"NotSucceeds;",{226,138,129,0,}},
      {(char*)0}, {(char*)0},
#line 493 "entities.lst"
      {"Scedil;",{197,158,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 1489 "entities.lst"
      {"nequiv;",{226,137,162,0,}},
#line 253 "entities.lst"
      {"Lang;",{226,159,170,0,}},
#line 2022 "entities.lst"
      {"tbrk;",{226,142,180,0,}},
      {(char*)0},
#line 1264 "entities.lst"
      {"lagran;",{226,132,146,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 1716 "entities.lst"
      {"pound",{194,163,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 1275 "entities.lst"
      {"larrfs;",{226,164,157,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 65 "entities.lst"
      {"CloseCurlyQuote;",{226,128,153,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 344 "entities.lst"
      {"NotGreaterGreater;",{226,137,171,204,184,0,}},
#line 62 "entities.lst"
      {"CircleTimes;",{226,138,151,0,}},
#line 1734 "entities.lst"
      {"prnap;",{226,170,185,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 1742 "entities.lst"
      {"prsim;",{226,137,190,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 448 "entities.lst"
      {"Rarrtl;",{226,164,150,0,}},
#line 173 "entities.lst"
      {"Gamma;",{206,147,0,}},
#line 2039 "entities.lst"
      {"thorn",{195,190,0,}},
      {(char*)0},
#line 261 "entities.lst"
      {"LeftArrowBar;",{226,135,164,0,}},
      {(char*)0},
#line 396 "entities.lst"
      {"Ofr;",{237,160,181,237,180,146,0,}},
      {(char*)0}, {(char*)0},
#line 5 "entities.lst"
      {"AMP",{38,0,}},
#line 1723 "entities.lst"
      {"prec;",{226,137,186,0,}},
#line 192 "entities.lst"
      {"HARDcy;",{208,170,0,}},
#line 893 "entities.lst"
      {"cudarrl;",{226,164,184,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1842 "entities.lst"
      {"roplus;",{226,168,174,0,}},
      {(char*)0}, {(char*)0},
#line 339 "entities.lst"
      {"NotEqualTilde;",{226,137,130,204,184,0,}},
#line 350 "entities.lst"
      {"NotLeftTriangle;",{226,139,170,0,}},
#line 730 "entities.lst"
      {"bigcirc;",{226,151,175,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 416 "entities.lst"
      {"OverBracket;",{226,142,180,0,}},
#line 1265 "entities.lst"
      {"lambda;",{206,187,0,}},
#line 362 "entities.lst"
      {"NotPrecedesEqual;",{226,170,175,204,184,0,}},
      {(char*)0},
#line 372 "entities.lst"
      {"NotSubset;",{226,138,130,226,131,146,0,}},
      {(char*)0}, {(char*)0},
#line 1849 "entities.lst"
      {"rscr;",{237,160,181,237,179,135,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 1431 "entities.lst"
      {"midcir;",{226,171,176,0,}},
      {(char*)0},
#line 363 "entities.lst"
      {"NotPrecedesSlantEqual;",{226,139,160,0,}},
#line 2134 "entities.lst"
      {"vangrt;",{226,166,156,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 2139 "entities.lst"
      {"varpi;",{207,150,0,}},
      {(char*)0},
#line 105 "entities.lst"
      {"DoubleLeftArrow;",{226,135,144,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 1788 "entities.lst"
      {"rbarr;",{226,164,141,0,}},
#line 1717 "entities.lst"
      {"pound;",{194,163,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 747 "entities.lst"
      {"blacktriangleleft;",{226,151,130,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 520 "entities.lst"
      {"SucceedsTilde;",{226,137,191,0,}},
#line 1808 "entities.lst"
      {"reals;",{226,132,157,0,}},
      {(char*)0}, {(char*)0},
#line 1037 "entities.lst"
      {"equivDD;",{226,169,184,0,}},
#line 389 "entities.lst"
      {"OElig;",{197,146,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 1728 "entities.lst"
      {"precneqq;",{226,170,181,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 1732 "entities.lst"
      {"primes;",{226,132,153,0,}},
#line 642 "entities.lst"
      {"acd;",{226,136,191,0,}},
#line 595 "entities.lst"
      {"Vee;",{226,139,129,0,}},
      {(char*)0},
#line 2040 "entities.lst"
      {"thorn;",{195,190,0,}},
      {(char*)0},
#line 1347 "entities.lst"
      {"lmoust;",{226,142,176,0,}},
      {(char*)0},
#line 365 "entities.lst"
      {"NotRightTriangle;",{226,139,171,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 1919 "entities.lst"
      {"smid;",{226,136,163,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1746 "entities.lst"
      {"puncsp;",{226,128,136,0,}},
#line 1025 "entities.lst"
      {"eplus;",{226,169,177,0,}},
      {(char*)0},
#line 531 "entities.lst"
      {"TScy;",{208,166,0,}},
      {(char*)0},
#line 424 "entities.lst"
      {"Poincareplane;",{226,132,140,0,}},
#line 1432 "entities.lst"
      {"middot",{194,183,0,}},
      {(char*)0},
#line 2135 "entities.lst"
      {"varepsilon;",{207,181,0,}},
      {(char*)0},
#line 1858 "entities.lst"
      {"rtrif;",{226,150,184,0,}},
#line 1741 "entities.lst"
      {"propto;",{226,136,157,0,}},
#line 485 "entities.lst"
      {"Rsh;",{226,134,177,0,}},
      {(char*)0}, {(char*)0},
#line 367 "entities.lst"
      {"NotRightTriangleEqual;",{226,139,173,0,}},
      {(char*)0},
#line 383 "entities.lst"
      {"NotTildeTilde;",{226,137,137,0,}},
#line 1433 "entities.lst"
      {"middot;",{194,183,0,}},
#line 295 "entities.lst"
      {"LongLeftArrow;",{226,159,181,0,}},
      {(char*)0},
#line 569 "entities.lst"
      {"UnionPlus;",{226,138,142,0,}},
      {(char*)0},
#line 2029 "entities.lst"
      {"there4;",{226,136,180,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 265 "entities.lst"
      {"LeftDownTeeVector;",{226,165,161,0,}},
#line 1982 "entities.lst"
      {"succnsim;",{226,139,169,0,}},
#line 1859 "entities.lst"
      {"rtriltri;",{226,167,142,0,}},
      {(char*)0},
#line 1884 "entities.lst"
      {"searrow;",{226,134,152,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1914 "entities.lst"
      {"simrarr;",{226,165,178,0,}},
      {(char*)0}, {(char*)0},
#line 1654 "entities.lst"
      {"or;",{226,136,168,0,}},
      {(char*)0},
#line 1720 "entities.lst"
      {"prap;",{226,170,183,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 1731 "entities.lst"
      {"prime;",{226,128,178,0,}},
#line 1421 "entities.lst"
      {"mcomma;",{226,168,169,0,}},
      {(char*)0}, {(char*)0},
#line 1895 "entities.lst"
      {"shchcy;",{209,137,0,}},
      {(char*)0},
#line 519 "entities.lst"
      {"SucceedsSlantEqual;",{226,137,189,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 263 "entities.lst"
      {"LeftCeiling;",{226,140,136,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1693 "entities.lst"
      {"phiv;",{207,149,0,}},
      {(char*)0}, {(char*)0},
#line 1726 "entities.lst"
      {"preceq;",{226,170,175,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 1675 "entities.lst"
      {"ouml",{195,182,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 330 "entities.lst"
      {"NoBreak;",{226,129,160,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 1540 "entities.lst"
      {"notnivb;",{226,139,190,0,}},
#line 1676 "entities.lst"
      {"ouml;",{195,182,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 1425 "entities.lst"
      {"mfr;",{237,160,181,237,180,170,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 1670 "entities.lst"
      {"osol;",{226,138,152,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1633 "entities.lst"
      {"ogon;",{203,155,0,}},
      {(char*)0}, {(char*)0},
#line 1634 "entities.lst"
      {"ograve",{195,178,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 83 "entities.lst"
      {"Dagger;",{226,128,161,0,}},
#line 1131 "entities.lst"
      {"gopf;",{237,160,181,237,181,152,0,}},
#line 1366 "entities.lst"
      {"lopf;",{237,160,181,237,181,157,0,}},
#line 1022 "entities.lst"
      {"eopf;",{237,160,181,237,181,150,0,}},
      {(char*)0},
#line 685 "entities.lst"
      {"aopf;",{237,160,181,237,181,146,0,}},
#line 624 "entities.lst"
      {"Yopf;",{237,160,181,237,181,144,0,}},
#line 1067 "entities.lst"
      {"fopf;",{237,160,181,237,181,151,0,}},
#line 1635 "entities.lst"
      {"ograve;",{195,178,0,}},
      {(char*)0},
#line 1174 "entities.lst"
      {"hopf;",{237,160,181,237,181,153,0,}},
#line 746 "entities.lst"
      {"blacktriangledown;",{226,150,190,0,}},
#line 399 "entities.lst"
      {"Omacr;",{197,140,0,}},
#line 960 "entities.lst"
      {"dopf;",{237,160,181,237,181,149,0,}},
#line 757 "entities.lst"
      {"bopf;",{237,160,181,237,181,147,0,}},
#line 440 "entities.lst"
      {"Qopf;",{226,132,154,0,}},
#line 1066 "entities.lst"
      {"fnof;",{198,146,0,}},
#line 635 "entities.lst"
      {"Zopf;",{226,132,164,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 446 "entities.lst"
      {"Rang;",{226,159,171,0,}},
      {(char*)0}, {(char*)0},
#line 1809 "entities.lst"
      {"rect;",{226,150,173,0,}},
      {(char*)0}, {(char*)0},
#line 222 "entities.lst"
      {"Intersection;",{226,139,130,0,}},
      {(char*)0}, {(char*)0},
#line 1761 "entities.lst"
      {"rBarr;",{226,164,143,0,}},
#line 880 "entities.lst"
      {"copf;",{237,160,181,237,181,148,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 246 "entities.lst"
      {"Kopf;",{237,160,181,237,181,130,0,}},
      {(char*)0}, {(char*)0},
#line 1467 "entities.lst"
      {"napprox;",{226,137,137,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 1695 "entities.lst"
      {"phone;",{226,152,142,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1743 "entities.lst"
      {"prurel;",{226,138,176,0,}},
      {(char*)0}, {(char*)0},
#line 2178 "entities.lst"
      {"wopf;",{237,160,181,237,181,168,0,}},
      {(char*)0}, {(char*)0},
#line 1671 "entities.lst"
      {"otilde",{195,181,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1689 "entities.lst"
      {"perp;",{226,138,165,0,}},
#line 364 "entities.lst"
      {"NotReverseElement;",{226,136,140,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 2200 "entities.lst"
      {"xrarr;",{226,159,182,0,}},
#line 1220 "entities.lst"
      {"iopf;",{237,160,181,237,181,154,0,}},
#line 1672 "entities.lst"
      {"otilde;",{195,181,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 1963 "entities.lst"
      {"submult;",{226,171,129,0,}},
#line 2026 "entities.lst"
      {"tdot;",{226,131,155,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 1617 "entities.lst"
      {"oS;",{226,147,136,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1687 "entities.lst"
      {"period;",{46,0,}},
      {(char*)0}, {(char*)0},
#line 1798 "entities.lst"
      {"rcub;",{125,0,}},
      {(char*)0},
#line 2209 "entities.lst"
      {"yacy;",{209,143,0,}},
#line 1091 "entities.lst"
      {"frown;",{226,140,162,0,}},
#line 1171 "entities.lst"
      {"homtht;",{226,136,187,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 117 "entities.lst"
      {"DownArrowBar;",{226,164,147,0,}},
#line 743 "entities.lst"
      {"blacklozenge;",{226,167,171,0,}},
      {(char*)0},
#line 1848 "entities.lst"
      {"rsaquo;",{226,128,186,0,}},
#line 1904 "entities.lst"
      {"sim;",{226,136,188,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1373 "entities.lst"
      {"lozf;",{226,167,171,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 1529 "entities.lst"
      {"nopf;",{237,160,181,237,181,159,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 328 "entities.lst"
      {"NewLine;",{10,0,}},
      {(char*)0}, {(char*)0},
#line 1797 "entities.lst"
      {"rceil;",{226,140,137,0,}},
#line 3 "entities.lst"
      {"AElig",{195,134,0,}},
      {(char*)0}, {(char*)0},
#line 967 "entities.lst"
      {"doublebarwedge;",{226,140,134,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 278 "entities.lst"
      {"LeftUpTeeVector;",{226,165,160,0,}},
#line 1426 "entities.lst"
      {"mho;",{226,132,167,0,}},
      {(char*)0},
#line 489 "entities.lst"
      {"SOFTcy;",{208,172,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 1967 "entities.lst"
      {"subrarr;",{226,165,185,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1854 "entities.lst"
      {"rthree;",{226,139,140,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 252 "entities.lst"
      {"Lambda;",{206,155,0,}},
      {(char*)0}, {(char*)0},
#line 2230 "entities.lst"
      {"zopf;",{237,160,181,237,181,171,0,}},
#line 13 "entities.lst"
      {"Afr;",{237,160,181,237,180,132,0,}},
#line 359 "entities.lst"
      {"NotNestedGreaterGreater;",{226,170,162,204,184,0,}},
#line 1664 "entities.lst"
      {"oror;",{226,169,150,0,}},
      {(char*)0}, {(char*)0},
#line 288 "entities.lst"
      {"LessLess;",{226,170,161,0,}},
#line 166 "entities.lst"
      {"Fopf;",{237,160,181,237,180,189,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 1673 "entities.lst"
      {"otimes;",{226,138,151,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 859 "entities.lst"
      {"circledast;",{226,138,155,0,}},
#line 459 "entities.lst"
      {"RightArrow;",{226,134,146,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 79 "entities.lst"
      {"DDotrahd;",{226,164,145,0,}},
#line 1241 "entities.lst"
      {"jopf;",{237,160,181,237,181,155,0,}},
#line 1831 "entities.lst"
      {"rlarr;",{226,135,132,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 254 "entities.lst"
      {"Laplacetrf;",{226,132,146,0,}},
#line 460 "entities.lst"
      {"RightArrowBar;",{226,135,165,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 547 "entities.lst"
      {"TripleDot;",{226,131,155,0,}},
#line 2195 "entities.lst"
      {"xodot;",{226,168,128,0,}},
      {(char*)0}, {(char*)0},
#line 1245 "entities.lst"
      {"kappa;",{206,186,0,}},
#line 2189 "entities.lst"
      {"xharr;",{226,159,183,0,}},
#line 1916 "entities.lst"
      {"smallsetminus;",{226,136,150,0,}},
      {(char*)0}, {(char*)0},
#line 1203 "entities.lst"
      {"imagpart;",{226,132,145,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 150 "entities.lst"
      {"Eopf;",{237,160,181,237,180,188,0,}},
      {(char*)0},
#line 802 "entities.lst"
      {"boxvh;",{226,148,188,0,}},
      {(char*)0}, {(char*)0},
#line 122 "entities.lst"
      {"DownLeftVector;",{226,134,189,0,}},
#line 1843 "entities.lst"
      {"rotimes;",{226,168,181,0,}},
      {(char*)0}, {(char*)0},
#line 4 "entities.lst"
      {"AElig;",{195,134,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 2047 "entities.lst"
      {"tint;",{226,136,173,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 2071 "entities.lst"
      {"tscr;",{237,160,181,237,179,137,0,}},
      {(char*)0},
#line 461 "entities.lst"
      {"RightArrowLeftArrow;",{226,135,132,0,}},
#line 2051 "entities.lst"
      {"topcir;",{226,171,177,0,}},
      {(char*)0}, {(char*)0},
#line 414 "entities.lst"
      {"OverBar;",{226,128,190,0,}},
      {(char*)0},
#line 314 "entities.lst"
      {"Mopf;",{237,160,181,237,181,132,0,}},
#line 2066 "entities.lst"
      {"triminus;",{226,168,186,0,}},
#line 1436 "entities.lst"
      {"minusd;",{226,136,184,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1800 "entities.lst"
      {"rdca;",{226,164,183,0,}},
#line 1733 "entities.lst"
      {"prnE;",{226,170,181,0,}},
#line 534 "entities.lst"
      {"Tcaron;",{197,164,0,}},
      {(char*)0},
#line 1270 "entities.lst"
      {"laquo",{194,171,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 1652 "entities.lst"
      {"operp;",{226,166,185,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 794 "entities.lst"
      {"boxuL;",{226,149,155,0,}},
      {(char*)0},
#line 2199 "entities.lst"
      {"xrArr;",{226,159,185,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 2190 "entities.lst"
      {"xi;",{206,190,0,}},
#line 206 "entities.lst"
      {"IOcy;",{208,129,0,}},
#line 444 "entities.lst"
      {"REG;",{194,174,0,}},
      {(char*)0}, {(char*)0},
#line 571 "entities.lst"
      {"Uopf;",{237,160,181,237,181,140,0,}},
#line 60 "entities.lst"
      {"CircleMinus;",{226,138,150,0,}},
#line 1974 "entities.lst"
      {"subsub;",{226,171,149,0,}},
#line 2031 "entities.lst"
      {"theta;",{206,184,0,}},
      {(char*)0},
#line 1686 "entities.lst"
      {"percnt;",{37,0,}},
      {(char*)0},
#line 1970 "entities.lst"
      {"subseteqq;",{226,171,133,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 2194 "entities.lst"
      {"xnis;",{226,139,187,0,}},
#line 2140 "entities.lst"
      {"varpropto;",{226,136,157,0,}},
#line 2037 "entities.lst"
      {"thkap;",{226,137,136,0,}},
#line 193 "entities.lst"
      {"Hacek;",{203,135,0,}},
#line 2203 "entities.lst"
      {"xuplus;",{226,168,132,0,}},
      {(char*)0}, {(char*)0},
#line 185 "entities.lst"
      {"GreaterFullEqual;",{226,137,167,0,}},
#line 2197 "entities.lst"
      {"xoplus;",{226,168,129,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1839 "entities.lst"
      {"robrk;",{226,159,167,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 1434 "entities.lst"
      {"minus;",{226,136,146,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 2201 "entities.lst"
      {"xscr;",{237,160,181,237,179,141,0,}},
      {(char*)0}, {(char*)0},
#line 1869 "entities.lst"
      {"sce;",{226,170,176,0,}},
      {(char*)0}, {(char*)0},
#line 182 "entities.lst"
      {"Gopf;",{237,160,181,237,180,190,0,}},
#line 1958 "entities.lst"
      {"sub;",{226,138,130,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 395 "entities.lst"
      {"Odblac;",{197,144,0,}},
#line 736 "entities.lst"
      {"bigstar;",{226,152,133,0,}},
#line 236 "entities.lst"
      {"Jopf;",{237,160,181,237,181,129,0,}},
      {(char*)0}, {(char*)0},
#line 2042 "entities.lst"
      {"times",{195,151,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1918 "entities.lst"
      {"smeparsl;",{226,167,164,0,}},
      {(char*)0}, {(char*)0},
#line 660 "entities.lst"
      {"amp;",{38,0,}},
      {(char*)0},
#line 1661 "entities.lst"
      {"ordm",{194,186,0,}},
      {(char*)0},
#line 1817 "entities.lst"
      {"rharul;",{226,165,172,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 98 "entities.lst"
      {"Dopf;",{237,160,181,237,180,187,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 502 "entities.lst"
      {"SmallCircle;",{226,136,152,0,}},
#line 1271 "entities.lst"
      {"laquo;",{194,171,0,}},
#line 2163 "entities.lst"
      {"vopf;",{237,160,181,237,181,167,0,}},
#line 1662 "entities.lst"
      {"ordm;",{194,186,0,}},
#line 301 "entities.lst"
      {"Lopf;",{237,160,181,237,181,131,0,}},
#line 2064 "entities.lst"
      {"tridot;",{226,151,172,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 2046 "entities.lst"
      {"timesd;",{226,168,176,0,}},
      {(char*)0},
#line 2216 "entities.lst"
      {"yopf;",{237,160,181,237,181,170,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 1749 "entities.lst"
      {"qopf;",{237,160,181,237,181,162,0,}},
      {(char*)0}, {(char*)0},
#line 1995 "entities.lst"
      {"supdsub;",{226,171,152,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 375 "entities.lst"
      {"NotSucceedsEqual;",{226,170,176,204,184,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 17 "entities.lst"
      {"Amacr;",{196,128,0,}},
#line 708 "entities.lst"
      {"backepsilon;",{207,182,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 376 "entities.lst"
      {"NotSucceedsSlantEqual;",{226,139,161,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 2202 "entities.lst"
      {"xsqcup;",{226,168,134,0,}},
      {(char*)0}, {(char*)0},
#line 2188 "entities.lst"
      {"xhArr;",{226,159,186,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 614 "entities.lst"
      {"Xopf;",{237,160,181,237,181,143,0,}},
      {(char*)0},
#line 1696 "entities.lst"
      {"pi;",{207,128,0,}},
#line 1816 "entities.lst"
      {"rharu;",{226,135,128,0,}},
      {(char*)0},
#line 432 "entities.lst"
      {"Product;",{226,136,143,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 514 "entities.lst"
      {"Sub;",{226,139,144,0,}},
#line 815 "entities.lst"
      {"bsolhsub;",{226,159,136,0,}},
      {(char*)0}, {(char*)0},
#line 1930 "entities.lst"
      {"spadesuit;",{226,153,160,0,}},
#line 2072 "entities.lst"
      {"tscy;",{209,134,0,}},
#line 1263 "entities.lst"
      {"laemptyv;",{226,166,180,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 2043 "entities.lst"
      {"times;",{195,151,0,}},
#line 2204 "entities.lst"
      {"xutri;",{226,150,179,0,}},
      {(char*)0},
#line 1651 "entities.lst"
      {"opar;",{226,166,183,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1829 "entities.lst"
      {"ring;",{203,154,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1762 "entities.lst"
      {"rHar;",{226,165,164,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 349 "entities.lst"
      {"NotHumpEqual;",{226,137,143,204,184,0,}},
      {(char*)0},
#line 1420 "entities.lst"
      {"marker;",{226,150,174,0,}},
#line 521 "entities.lst"
      {"SuchThat;",{226,136,139,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 1744 "entities.lst"
      {"pscr;",{237,160,181,237,179,133,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 346 "entities.lst"
      {"NotGreaterSlantEqual;",{226,169,190,204,184,0,}},
      {(char*)0}, {(char*)0},
#line 1674 "entities.lst"
      {"otimesas;",{226,168,182,0,}},
#line 259 "entities.lst"
      {"LeftAngleBracket;",{226,159,168,0,}},
#line 1736 "entities.lst"
      {"prod;",{226,136,143,0,}},
      {(char*)0},
#line 71 "entities.lst"
      {"Copf;",{226,132,130,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 742 "entities.lst"
      {"bkarow;",{226,164,141,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 1468 "entities.lst"
      {"natur;",{226,153,174,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 1694 "entities.lst"
      {"phmmat;",{226,132,179,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 908 "entities.lst"
      {"curlyeqprec;",{226,139,158,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1605 "entities.lst"
      {"nvlArr;",{226,164,130,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 1655 "entities.lst"
      {"orarr;",{226,134,187,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1657 "entities.lst"
      {"order;",{226,132,180,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 1094 "entities.lst"
      {"gEl;",{226,170,140,0,}},
#line 415 "entities.lst"
      {"OverBrace;",{226,143,158,0,}},
      {(char*)0},
#line 1795 "entities.lst"
      {"rcaron;",{197,153,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 538 "entities.lst"
      {"Therefore;",{226,136,180,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1832 "entities.lst"
      {"rlhar;",{226,135,140,0,}},
#line 332 "entities.lst"
      {"Nopf;",{226,132,149,0,}},
      {(char*)0},
#line 455 "entities.lst"
      {"ReverseUpEquilibrium;",{226,165,175,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 110 "entities.lst"
      {"DoubleLongRightArrow;",{226,159,185,0,}},
      {(char*)0},
#line 1160 "entities.lst"
      {"harrw;",{226,134,173,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 1868 "entities.lst"
      {"sccue;",{226,137,189,0,}},
#line 1853 "entities.lst"
      {"rsquor;",{226,128,153,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 18 "entities.lst"
      {"And;",{226,169,147,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 1789 "entities.lst"
      {"rbbrk;",{226,157,179,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 1124 "entities.lst"
      {"gnE;",{226,137,169,0,}},
#line 1349 "entities.lst"
      {"lnE;",{226,137,168,0,}},
      {(char*)0}, {(char*)0},
#line 2124 "entities.lst"
      {"utri;",{226,150,181,0,}},
      {(char*)0},
#line 2127 "entities.lst"
      {"uuml",{195,188,0,}},
      {(char*)0}, {(char*)0},
#line 2206 "entities.lst"
      {"xwedge;",{226,139,128,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1335 "entities.lst"
      {"lgE;",{226,170,145,0,}},
      {(char*)0}, {(char*)0},
#line 1794 "entities.lst"
      {"rbrkslu;",{226,166,144,0,}},
      {(char*)0},
#line 2185 "entities.lst"
      {"xcup;",{226,139,131,0,}},
#line 2128 "entities.lst"
      {"uuml;",{195,188,0,}},
      {(char*)0}, {(char*)0},
#line 1460 "entities.lst"
      {"nabla;",{226,136,135,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 2112 "entities.lst"
      {"upsi;",{207,133,0,}},
      {(char*)0},
#line 687 "entities.lst"
      {"apE;",{226,169,176,0,}},
      {(char*)0}, {(char*)0},
#line 1628 "entities.lst"
      {"odot;",{226,138,153,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 2018 "entities.lst"
      {"szlig",{195,159,0,}},
#line 1629 "entities.lst"
      {"odsold;",{226,166,188,0,}},
      {(char*)0}, {(char*)0},
#line 1274 "entities.lst"
      {"larrbfs;",{226,164,159,0,}},
      {(char*)0}, {(char*)0},
#line 2093 "entities.lst"
      {"ugrave",{195,185,0,}},
#line 926 "entities.lst"
      {"dash;",{226,128,144,0,}},
      {(char*)0}, {(char*)0},
#line 1852 "entities.lst"
      {"rsquo;",{226,128,153,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 778 "entities.lst"
      {"boxVh;",{226,149,171,0,}},
#line 2094 "entities.lst"
      {"ugrave;",{195,185,0,}},
#line 610 "entities.lst"
      {"Wopf;",{237,160,181,237,181,142,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 581 "entities.lst"
      {"UpperLeftArrow;",{226,134,150,0,}},
      {(char*)0},
#line 417 "entities.lst"
      {"OverParenthesis;",{226,143,156,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 481 "entities.lst"
      {"Ropf;",{226,132,157,0,}},
#line 219 "entities.lst"
      {"Implies;",{226,135,146,0,}},
      {(char*)0}, {(char*)0},
#line 226 "entities.lst"
      {"Iopf;",{237,160,181,237,181,128,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 311 "entities.lst"
      {"Mellintrf;",{226,132,179,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1631 "entities.lst"
      {"ofcir;",{226,166,191,0,}},
#line 2123 "entities.lst"
      {"utilde;",{197,169,0,}},
#line 1971 "entities.lst"
      {"subsetneq;",{226,138,138,0,}},
      {(char*)0}, {(char*)0},
#line 1053 "entities.lst"
      {"exponentiale;",{226,133,135,0,}},
      {(char*)0},
#line 1447 "entities.lst"
      {"multimap;",{226,138,184,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 2192 "entities.lst"
      {"xlarr;",{226,159,181,0,}},
#line 1495 "entities.lst"
      {"ngE;",{226,137,167,204,184,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1071 "entities.lst"
      {"fpartint;",{226,168,141,0,}},
      {(char*)0},
#line 2068 "entities.lst"
      {"trisb;",{226,167,141,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 2019 "entities.lst"
      {"szlig;",{195,159,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1688 "entities.lst"
      {"permil;",{226,128,176,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 927 "entities.lst"
      {"dashv;",{226,138,163,0,}},
#line 529 "entities.lst"
      {"TRADE;",{226,132,162,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 2056 "entities.lst"
      {"trade;",{226,132,162,0,}},
#line 296 "entities.lst"
      {"LongLeftRightArrow;",{226,159,183,0,}},
      {(char*)0},
#line 655 "entities.lst"
      {"aleph;",{226,132,181,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1104 "entities.lst"
      {"gel;",{226,139,155,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1253 "entities.lst"
      {"kopf;",{237,160,181,237,181,156,0,}},
#line 554 "entities.lst"
      {"Ubrcy;",{208,142,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 1627 "entities.lst"
      {"odiv;",{226,168,184,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1807 "entities.lst"
      {"realpart;",{226,132,156,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 1639 "entities.lst"
      {"oint;",{226,136,174,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 1667 "entities.lst"
      {"oscr;",{226,132,180,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 2119 "entities.lst"
      {"uring;",{197,175,0,}},
      {(char*)0}, {(char*)0},
#line 37 "entities.lst"
      {"Bfr;",{237,160,181,237,180,133,0,}},
      {(char*)0}, {(char*)0},
#line 272 "entities.lst"
      {"LeftTeeArrow;",{226,134,164,0,}},
      {(char*)0}, {(char*)0},
#line 198 "entities.lst"
      {"Hopf;",{226,132,141,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 1663 "entities.lst"
      {"origof;",{226,138,182,0,}},
      {(char*)0}, {(char*)0},
#line 2183 "entities.lst"
      {"xcap;",{226,139,130,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 2137 "entities.lst"
      {"varnothing;",{226,136,133,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 2105 "entities.lst"
      {"uogon;",{197,179,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 549 "entities.lst"
      {"Tstrok;",{197,166,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 2067 "entities.lst"
      {"triplus;",{226,168,185,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 527 "entities.lst"
      {"THORN",{195,158,0,}},
#line 704 "entities.lst"
      {"awconint;",{226,136,179,0,}},
      {(char*)0}, {(char*)0},
#line 1331 "entities.lst"
      {"lfisht;",{226,165,188,0,}},
#line 2184 "entities.lst"
      {"xcirc;",{226,151,175,0,}},
#line 1246 "entities.lst"
      {"kappav;",{207,176,0,}},
#line 114 "entities.lst"
      {"DoubleUpDownArrow;",{226,135,149,0,}},
#line 400 "entities.lst"
      {"Omega;",{206,169,0,}},
#line 1928 "entities.lst"
      {"sopf;",{237,160,181,237,181,164,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1435 "entities.lst"
      {"minusb;",{226,138,159,0,}},
      {(char*)0},
#line 940 "entities.lst"
      {"dfisht;",{226,165,191,0,}},
      {(char*)0},
#line 2034 "entities.lst"
      {"thickapprox;",{226,137,136,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 1643 "entities.lst"
      {"oline;",{226,128,190,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 918 "entities.lst"
      {"cwconint;",{226,136,178,0,}},
#line 487 "entities.lst"
      {"SHCHcy;",{208,169,0,}},
      {(char*)0}, {(char*)0},
#line 401 "entities.lst"
      {"Omicron;",{206,159,0,}},
#line 1234 "entities.lst"
      {"iukcy;",{209,150,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 1281 "entities.lst"
      {"lat;",{226,170,171,0,}},
#line 537 "entities.lst"
      {"Tfr;",{237,160,181,237,180,151,0,}},
#line 1098 "entities.lst"
      {"gap;",{226,170,134,0,}},
#line 1269 "entities.lst"
      {"lap;",{226,170,133,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 161 "entities.lst"
      {"ExponentialE;",{226,133,135,0,}},
      {(char*)0},
#line 2191 "entities.lst"
      {"xlArr;",{226,159,184,0,}},
      {(char*)0}, {(char*)0},
#line 1813 "entities.lst"
      {"rfloor;",{226,140,139,0,}},
      {(char*)0}, {(char*)0},
#line 343 "entities.lst"
      {"NotGreaterFullEqual;",{226,137,167,204,184,0,}},
      {(char*)0}, {(char*)0},
#line 1947 "entities.lst"
      {"squf;",{226,150,170,0,}},
      {(char*)0}, {(char*)0},
#line 1727 "entities.lst"
      {"precnapprox;",{226,170,185,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 1168 "entities.lst"
      {"hksearow;",{226,164,165,0,}},
      {(char*)0},
#line 106 "entities.lst"
      {"DoubleLeftRightArrow;",{226,135,148,0,}},
#line 823 "entities.lst"
      {"cap;",{226,136,169,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 601 "entities.lst"
      {"VerticalTilde;",{226,137,128,0,}},
#line 683 "entities.lst"
      {"angzarr;",{226,141,188,0,}},
      {(char*)0},
#line 1793 "entities.lst"
      {"rbrksld;",{226,166,142,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 924 "entities.lst"
      {"daleth;",{226,132,184,0,}},
#line 218 "entities.lst"
      {"ImaginaryI;",{226,133,136,0,}},
      {(char*)0},
#line 2033 "entities.lst"
      {"thetav;",{207,145,0,}},
      {(char*)0},
#line 2084 "entities.lst"
      {"ubreve;",{197,173,0,}},
#line 377 "entities.lst"
      {"NotSucceedsTilde;",{226,137,191,204,184,0,}},
#line 2023 "entities.lst"
      {"tcaron;",{197,165,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 528 "entities.lst"
      {"THORN;",{195,158,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 503 "entities.lst"
      {"Sopf;",{237,160,181,237,181,138,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 1009 "entities.lst"
      {"ell;",{226,132,147,0,}},
      {(char*)0}, {(char*)0},
#line 1900 "entities.lst"
      {"shy;",{194,173,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 565 "entities.lst"
      {"UnderBrace;",{226,143,159,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 1543 "entities.lst"
      {"nparallel;",{226,136,166,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 2044 "entities.lst"
      {"timesb;",{226,138,160,0,}},
#line 1101 "entities.lst"
      {"gcy;",{208,179,0,}},
#line 1296 "entities.lst"
      {"lcy;",{208,187,0,}},
#line 997 "entities.lst"
      {"ecy;",{209,141,0,}},
      {(char*)0},
#line 647 "entities.lst"
      {"acy;",{208,176,0,}},
#line 622 "entities.lst"
      {"Ycy;",{208,171,0,}},
#line 1055 "entities.lst"
      {"fcy;",{209,132,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 931 "entities.lst"
      {"dcy;",{208,180,0,}},
#line 718 "entities.lst"
      {"bcy;",{208,177,0,}},
#line 425 "entities.lst"
      {"Popf;",{226,132,153,0,}},
      {(char*)0},
#line 630 "entities.lst"
      {"Zcy;",{208,151,0,}},
      {(char*)0},
#line 1244 "entities.lst"
      {"jukcy;",{209,148,0,}},
#line 404 "entities.lst"
      {"OpenCurlyQuote;",{226,128,152,0,}},
      {(char*)0},
#line 1463 "entities.lst"
      {"nap;",{226,137,137,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 510 "entities.lst"
      {"SquareSupersetEqual;",{226,138,146,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 244 "entities.lst"
      {"Kcy;",{208,154,0,}},
      {(char*)0},
#line 604 "entities.lst"
      {"Vopf;",{237,160,181,237,181,141,0,}},
      {(char*)0},
#line 2147 "entities.lst"
      {"varsupsetneqq;",{226,171,140,239,184,128,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 468 "entities.lst"
      {"RightTee;",{226,138,162,0,}},
#line 1454 "entities.lst"
      {"nLl;",{226,139,152,204,184,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1186 "entities.lst"
      {"icy;",{208,184,0,}},
#line 85 "entities.lst"
      {"Dashv;",{226,171,164,0,}},
#line 2186 "entities.lst"
      {"xdtri;",{226,150,189,0,}},
#line 1410 "entities.lst"
      {"macr",{194,175,0,}},
      {(char*)0},
#line 1735 "entities.lst"
      {"prnsim;",{226,139,168,0,}},
#line 478 "entities.lst"
      {"RightVector;",{226,135,128,0,}},
      {(char*)0}, {(char*)0},
#line 1424 "entities.lst"
      {"measuredangle;",{226,136,161,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 1725 "entities.lst"
      {"preccurlyeq;",{226,137,188,0,}},
#line 1411 "entities.lst"
      {"macr;",{194,175,0,}},
#line 1702 "entities.lst"
      {"plus;",{43,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 88 "entities.lst"
      {"Del;",{226,136,135,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 274 "entities.lst"
      {"LeftTriangle;",{226,138,178,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 911 "entities.lst"
      {"curlywedge;",{226,139,143,0,}},
#line 909 "entities.lst"
      {"curlyeqsucc;",{226,139,159,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 989 "entities.lst"
      {"eacute",{195,169,0,}},
      {(char*)0},
#line 637 "entities.lst"
      {"aacute",{195,161,0,}},
#line 619 "entities.lst"
      {"Yacute",{195,157,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 1481 "entities.lst"
      {"ncy;",{208,189,0,}},
#line 1095 "entities.lst"
      {"gacute;",{199,181,0,}},
#line 1262 "entities.lst"
      {"lacute;",{196,186,0,}},
#line 990 "entities.lst"
      {"eacute;",{195,169,0,}},
#line 128 "entities.lst"
      {"DownTeeArrow;",{226,134,167,0,}},
#line 638 "entities.lst"
      {"aacute;",{195,161,0,}},
#line 620 "entities.lst"
      {"Yacute;",{195,157,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1706 "entities.lst"
      {"plusdo;",{226,136,148,0,}},
      {(char*)0}, {(char*)0},
#line 628 "entities.lst"
      {"Zacute;",{197,185,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1665 "entities.lst"
      {"orslope;",{226,169,151,0,}},
      {(char*)0},
#line 308 "entities.lst"
      {"Map;",{226,164,133,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 822 "entities.lst"
      {"cacute;",{196,135,0,}},
      {(char*)0},
#line 1677 "entities.lst"
      {"ovbar;",{226,140,189,0,}},
#line 1709 "entities.lst"
      {"plusmn",{194,177,0,}},
      {(char*)0},
#line 2126 "entities.lst"
      {"uuarr;",{226,135,136,0,}},
      {(char*)0},
#line 2223 "entities.lst"
      {"zcy;",{208,183,0,}},
      {(char*)0}, {(char*)0},
#line 1640 "entities.lst"
      {"olarr;",{226,134,186,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 162 "entities.lst"
      {"Fcy;",{208,164,0,}},
#line 1710 "entities.lst"
      {"plusmn;",{194,177,0,}},
      {(char*)0},
#line 239 "entities.lst"
      {"Jukcy;",{208,132,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1181 "entities.lst"
      {"iacute",{195,173,0,}},
      {(char*)0},
#line 716 "entities.lst"
      {"bbrktbrk;",{226,142,182,0,}},
      {(char*)0}, {(char*)0},
#line 1814 "entities.lst"
      {"rfr;",{237,160,181,237,180,175,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 1182 "entities.lst"
      {"iacute;",{195,173,0,}},
      {(char*)0}, {(char*)0},
#line 199 "entities.lst"
      {"HorizontalLine;",{226,148,128,0,}},
      {(char*)0},
#line 1238 "entities.lst"
      {"jcy;",{208,185,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1429 "entities.lst"
      {"mid;",{226,136,163,0,}},
#line 1803 "entities.lst"
      {"rdquor;",{226,128,157,0,}},
      {(char*)0}, {(char*)0},
#line 910 "entities.lst"
      {"curlyvee;",{226,139,142,0,}},
#line 31 "entities.lst"
      {"Barv;",{226,171,167,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 1556 "entities.lst"
      {"nrightarrow;",{226,134,155,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1791 "entities.lst"
      {"rbrack;",{93,0,}},
      {(char*)0},
#line 1921 "entities.lst"
      {"smt;",{226,170,170,0,}},
      {(char*)0}, {(char*)0},
#line 480 "entities.lst"
      {"Rightarrow;",{226,135,146,0,}},
#line 1925 "entities.lst"
      {"sol;",{47,0,}},
      {(char*)0},
#line 140 "entities.lst"
      {"Ecy;",{208,173,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 1621 "entities.lst"
      {"ocir;",{226,138,154,0,}},
#line 1121 "entities.lst"
      {"glE;",{226,170,146,0,}},
      {(char*)0},
#line 1724 "entities.lst"
      {"precapprox;",{226,170,183,0,}},
#line 1622 "entities.lst"
      {"ocirc",{195,180,0,}},
      {(char*)0},
#line 535 "entities.lst"
      {"Tcedil;",{197,162,0,}},
      {(char*)0}, {(char*)0},
#line 1637 "entities.lst"
      {"ohbar;",{226,166,181,0,}},
      {(char*)0},
#line 1416 "entities.lst"
      {"mapsto;",{226,134,166,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 1461 "entities.lst"
      {"nacute;",{197,132,0,}},
#line 2030 "entities.lst"
      {"therefore;",{226,136,180,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 309 "entities.lst"
      {"Mcy;",{208,156,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1955 "entities.lst"
      {"straightepsilon;",{207,181,0,}},
      {(char*)0}, {(char*)0},
#line 16 "entities.lst"
      {"Alpha;",{206,145,0,}},
      {(char*)0},
#line 1802 "entities.lst"
      {"rdquo;",{226,128,157,0,}},
#line 469 "entities.lst"
      {"RightTeeArrow;",{226,134,166,0,}},
      {(char*)0},
#line 2122 "entities.lst"
      {"utdot;",{226,139,176,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 2221 "entities.lst"
      {"zacute;",{197,186,0,}},
      {(char*)0}, {(char*)0},
#line 2116 "entities.lst"
      {"urcorn;",{226,140,157,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 558 "entities.lst"
      {"Ucy;",{208,163,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 2096 "entities.lst"
      {"uharr;",{226,134,190,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 2095 "entities.lst"
      {"uharl;",{226,134,191,0,}},
      {(char*)0},
#line 287 "entities.lst"
      {"LessGreater;",{226,137,182,0,}},
      {(char*)0}, {(char*)0},
#line 2045 "entities.lst"
      {"timesbar;",{226,168,177,0,}},
#line 2117 "entities.lst"
      {"urcorner;",{226,140,157,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 2069 "entities.lst"
      {"tritime;",{226,168,187,0,}},
      {(char*)0},
#line 1707 "entities.lst"
      {"plusdu;",{226,168,165,0,}},
      {(char*)0},
#line 326 "entities.lst"
      {"NestedGreaterGreater;",{226,137,171,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 600 "entities.lst"
      {"VerticalSeparator;",{226,157,152,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 1708 "entities.lst"
      {"pluse;",{226,169,178,0,}},
      {(char*)0},
#line 135 "entities.lst"
      {"Eacute",{195,137,0,}},
#line 1623 "entities.lst"
      {"ocirc;",{195,180,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 178 "entities.lst"
      {"Gcy;",{208,147,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 1701 "entities.lst"
      {"plankv;",{226,132,143,0,}},
#line 136 "entities.lst"
      {"Eacute;",{195,137,0,}},
#line 234 "entities.lst"
      {"Jcy;",{208,153,0,}},
#line 1818 "entities.lst"
      {"rho;",{207,129,0,}},
#line 1419 "entities.lst"
      {"mapstoup;",{226,134,165,0,}},
#line 1641 "entities.lst"
      {"olcir;",{226,166,190,0,}},
#line 1513 "entities.lst"
      {"nlE;",{226,137,166,204,184,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 373 "entities.lst"
      {"NotSubsetEqual;",{226,138,136,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 87 "entities.lst"
      {"Dcy;",{208,148,0,}},
#line 402 "entities.lst"
      {"Oopf;",{237,160,181,237,181,134,0,}},
      {(char*)0}, {(char*)0},
#line 1610 "entities.lst"
      {"nvrtrie;",{226,138,181,226,131,146,0,}},
      {(char*)0},
#line 2151 "entities.lst"
      {"vcy;",{208,178,0,}},
      {(char*)0},
#line 258 "entities.lst"
      {"Lcy;",{208,155,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 2211 "entities.lst"
      {"ycy;",{209,139,0,}},
#line 132 "entities.lst"
      {"ENG;",{197,138,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 154 "entities.lst"
      {"Equilibrium;",{226,135,140,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 46 "entities.lst"
      {"Cap;",{226,139,146,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 2115 "entities.lst"
      {"upuparrows;",{226,135,136,0,}},
#line 550 "entities.lst"
      {"Uacute",{195,154,0,}},
#line 454 "entities.lst"
      {"ReverseEquilibrium;",{226,135,139,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1759 "entities.lst"
      {"rArr;",{226,135,146,0,}},
      {(char*)0}, {(char*)0},
#line 551 "entities.lst"
      {"Uacute;",{195,154,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 2121 "entities.lst"
      {"uscr;",{237,160,181,237,179,138,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 1457 "entities.lst"
      {"nRightarrow;",{226,135,143,0,}},
      {(char*)0}, {(char*)0},
#line 286 "entities.lst"
      {"LessFullEqual;",{226,137,166,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 289 "entities.lst"
      {"LessSlantEqual;",{226,169,189,0,}},
      {(char*)0},
#line 2118 "entities.lst"
      {"urcrop;",{226,140,142,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 331 "entities.lst"
      {"NonBreakingSpace;",{194,160,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 302 "entities.lst"
      {"LowerLeftArrow;",{226,134,153,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1437 "entities.lst"
      {"minusdu;",{226,168,170,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 2207 "entities.lst"
      {"yacute",{195,189,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 251 "entities.lst"
      {"Lacute;",{196,185,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 2208 "entities.lst"
      {"yacute;",{195,189,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 1999 "entities.lst"
      {"suphsub;",{226,171,151,0,}},
      {(char*)0},
#line 2125 "entities.lst"
      {"utrif;",{226,150,180,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1796 "entities.lst"
      {"rcedil;",{197,151,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 230 "entities.lst"
      {"Iukcy;",{208,134,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 470 "entities.lst"
      {"RightTeeVector;",{226,165,155,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 348 "entities.lst"
      {"NotHumpDownHump;",{226,137,142,204,184,0,}},
#line 500 "entities.lst"
      {"ShortUpArrow;",{226,134,145,0,}},
      {(char*)0},
#line 2120 "entities.lst"
      {"urtri;",{226,151,185,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 1713 "entities.lst"
      {"pm;",{194,177,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 1804 "entities.lst"
      {"rdsh;",{226,134,179,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1806 "entities.lst"
      {"realine;",{226,132,155,0,}},
#line 508 "entities.lst"
      {"SquareSubsetEqual;",{226,138,145,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 321 "entities.lst"
      {"Ncy;",{208,157,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 2074 "entities.lst"
      {"tstrok;",{197,167,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 1216 "entities.lst"
      {"intlarhk;",{226,168,151,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 1442 "entities.lst"
      {"mopf;",{237,160,181,237,181,158,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 1197 "entities.lst"
      {"iinfin;",{226,167,156,0,}},
      {(char*)0},
#line 1786 "entities.lst"
      {"ratio;",{226,136,182,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1307 "entities.lst"
      {"leftharpoonup;",{226,134,188,0,}},
      {(char*)0}, {(char*)0},
#line 34 "entities.lst"
      {"Because;",{226,136,181,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 1704 "entities.lst"
      {"plusb;",{226,138,158,0,}},
      {(char*)0},
#line 45 "entities.lst"
      {"Cacute;",{196,134,0,}},
      {(char*)0}, {(char*)0},
#line 275 "entities.lst"
      {"LeftTriangleBar;",{226,167,143,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 2028 "entities.lst"
      {"tfr;",{237,160,181,237,180,177,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 2038 "entities.lst"
      {"thksim;",{226,136,188,0,}},
#line 1312 "entities.lst"
      {"leftrightsquigarrow;",{226,134,173,0,}},
#line 641 "entities.lst"
      {"acE;",{226,136,190,204,179,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 2049 "entities.lst"
      {"top;",{226,138,164,0,}},
      {(char*)0},
#line 1348 "entities.lst"
      {"lmoustache;",{226,142,176,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 1658 "entities.lst"
      {"orderof;",{226,132,180,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 741 "entities.lst"
      {"bigwedge;",{226,139,128,0,}},
      {(char*)0}, {(char*)0},
#line 1773 "entities.lst"
      {"rarr;",{226,134,146,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 318 "entities.lst"
      {"Nacute;",{197,131,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 451 "entities.lst"
      {"Rcy;",{208,160,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 211 "entities.lst"
      {"Icy;",{208,152,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 599 "entities.lst"
      {"VerticalLine;",{124,0,}},
      {(char*)0},
#line 2017 "entities.lst"
      {"swnwar;",{226,164,170,0,}},
#line 2110 "entities.lst"
      {"upharpoonright;",{226,134,190,0,}},
#line 2145 "entities.lst"
      {"varsubsetneqq;",{226,171,139,239,184,128,0,}},
#line 1781 "entities.lst"
      {"rarrpl;",{226,165,133,0,}},
#line 120 "entities.lst"
      {"DownLeftRightVector;",{226,165,144,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1780 "entities.lst"
      {"rarrlp;",{226,134,172,0,}},
      {(char*)0},
#line 1417 "entities.lst"
      {"mapstodown;",{226,134,167,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 2187 "entities.lst"
      {"xfr;",{237,160,181,237,180,181,0,}},
      {(char*)0},
#line 2193 "entities.lst"
      {"xmap;",{226,159,188,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 194 "entities.lst"
      {"Hat;",{94,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1811 "entities.lst"
      {"reg;",{194,174,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 727 "entities.lst"
      {"between;",{226,137,172,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 20 "entities.lst"
      {"Aopf;",{237,160,181,237,180,184,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1248 "entities.lst"
      {"kcy;",{208,186,0,}},
      {(char*)0},
#line 1777 "entities.lst"
      {"rarrc;",{226,164,179,0,}},
      {(char*)0},
#line 483 "entities.lst"
      {"Rrightarrow;",{226,135,155,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 2035 "entities.lst"
      {"thicksim;",{226,136,188,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 207 "entities.lst"
      {"Iacute",{195,141,0,}},
      {(char*)0}, {(char*)0},
#line 1758 "entities.lst"
      {"rAarr;",{226,135,155,0,}},
      {(char*)0},
#line 498 "entities.lst"
      {"ShortLeftArrow;",{226,134,144,0,}},
      {(char*)0}, {(char*)0},
#line 445 "entities.lst"
      {"Racute;",{197,148,0,}},
      {(char*)0}, {(char*)0},
#line 2088 "entities.lst"
      {"udarr;",{226,135,133,0,}},
#line 208 "entities.lst"
      {"Iacute;",{195,141,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 203 "entities.lst"
      {"HumpEqual;",{226,137,143,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 121 "entities.lst"
      {"DownLeftTeeVector;",{226,165,158,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 1729 "entities.lst"
      {"precnsim;",{226,139,168,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 1833 "entities.lst"
      {"rlm;",{226,128,143,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 35 "entities.lst"
      {"Bernoullis;",{226,132,172,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 2114 "entities.lst"
      {"upsilon;",{207,133,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 1722 "entities.lst"
      {"pre;",{226,170,175,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1691 "entities.lst"
      {"pfr;",{237,160,181,237,180,173,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1482 "entities.lst"
      {"ndash;",{226,128,147,0,}},
      {(char*)0},
#line 2085 "entities.lst"
      {"ucirc",{195,187,0,}},
      {(char*)0},
#line 1783 "entities.lst"
      {"rarrtl;",{226,134,163,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 2097 "entities.lst"
      {"uhblk;",{226,150,128,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 1877 "entities.lst"
      {"scy;",{209,129,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1745 "entities.lst"
      {"psi;",{207,136,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1888 "entities.lst"
      {"seswar;",{226,164,169,0,}},
      {(char*)0},
#line 1760 "entities.lst"
      {"rAtail;",{226,164,156,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 471 "entities.lst"
      {"RightTriangle;",{226,138,179,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 472 "entities.lst"
      {"RightTriangleBar;",{226,167,144,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 2098 "entities.lst"
      {"ulcorn;",{226,140,156,0,}},
      {(char*)0},
#line 1014 "entities.lst"
      {"emptyset;",{226,136,133,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 2024 "entities.lst"
      {"tcedil;",{197,163,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 2099 "entities.lst"
      {"ulcorner;",{226,140,156,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 2086 "entities.lst"
      {"ucirc;",{195,187,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1875 "entities.lst"
      {"scpolint;",{226,168,147,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 495 "entities.lst"
      {"Scy;",{208,161,0,}},
#line 1013 "entities.lst"
      {"empty;",{226,136,133,0,}},
#line 738 "entities.lst"
      {"bigtriangleup;",{226,150,179,0,}},
#line 1765 "entities.lst"
      {"radic;",{226,136,154,0,}},
#line 264 "entities.lst"
      {"LeftDoubleBracket;",{226,159,166,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 267 "entities.lst"
      {"LeftDownVectorBar;",{226,165,153,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 1850 "entities.lst"
      {"rsh;",{226,134,177,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1205 "entities.lst"
      {"imof;",{226,138,183,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 1862 "entities.lst"
      {"sacute;",{197,155,0,}},
      {(char*)0},
#line 654 "entities.lst"
      {"alefsym;",{226,132,181,0,}},
#line 6 "entities.lst"
      {"AMP;",{38,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 1668 "entities.lst"
      {"oslash",{195,184,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1669 "entities.lst"
      {"oslash;",{195,184,0,}},
      {(char*)0}, {(char*)0},
#line 419 "entities.lst"
      {"Pcy;",{208,159,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 1692 "entities.lst"
      {"phi;",{207,134,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 592 "entities.lst"
      {"Vcy;",{208,146,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 476 "entities.lst"
      {"RightUpVector;",{226,134,190,0,}},
#line 1690 "entities.lst"
      {"pertenk;",{226,128,177,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 2079 "entities.lst"
      {"uHar;",{226,165,163,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 477 "entities.lst"
      {"RightUpVectorBar;",{226,165,148,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 1721 "entities.lst"
      {"prcue;",{226,137,188,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 2100 "entities.lst"
      {"ulcrop;",{226,140,143,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 541 "entities.lst"
      {"ThinSpace;",{226,128,137,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 490 "entities.lst"
      {"Sacute;",{197,154,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 2152 "entities.lst"
      {"vdash;",{226,138,162,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 1311 "entities.lst"
      {"leftrightharpoons;",{226,135,139,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 1679 "entities.lst"
      {"para",{194,182,0,}},
      {(char*)0},
#line 1767 "entities.lst"
      {"rang;",{226,159,169,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 1684 "entities.lst"
      {"part;",{226,136,130,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1680 "entities.lst"
      {"para;",{194,182,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 475 "entities.lst"
      {"RightUpTeeVector;",{226,165,156,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 2090 "entities.lst"
      {"udhar;",{226,165,174,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1785 "entities.lst"
      {"ratail;",{226,164,154,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 1632 "entities.lst"
      {"ofr;",{237,160,181,237,180,172,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1763 "entities.lst"
      {"race;",{226,136,189,204,177,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 1775 "entities.lst"
      {"rarrb;",{226,135,165,0,}},
#line 2101 "entities.lst"
      {"ultri;",{226,151,184,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1636 "entities.lst"
      {"ogt;",{226,167,129,0,}},
      {(char*)0},
#line 1054 "entities.lst"
      {"fallingdotseq;",{226,137,146,0,}},
      {(char*)0},
#line 1770 "entities.lst"
      {"rangle;",{226,159,169,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 755 "entities.lst"
      {"bnequiv;",{226,137,161,226,131,165,0,}},
      {(char*)0},
#line 2146 "entities.lst"
      {"varsupsetneq;",{226,138,139,239,184,128,0,}},
#line 1452 "entities.lst"
      {"nLeftarrow;",{226,135,141,0,}},
#line 1413 "entities.lst"
      {"malt;",{226,156,160,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 48 "entities.lst"
      {"Cayleys;",{226,132,173,0,}},
#line 1826 "entities.lst"
      {"rightrightarrows;",{226,135,137,0,}},
#line 2109 "entities.lst"
      {"upharpoonleft;",{226,134,191,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 1453 "entities.lst"
      {"nLeftrightarrow;",{226,135,142,0,}},
      {(char*)0}, {(char*)0},
#line 598 "entities.lst"
      {"VerticalBar;",{226,136,163,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 1998 "entities.lst"
      {"suphsol;",{226,159,137,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1517 "entities.lst"
      {"nleftarrow;",{226,134,154,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 1518 "entities.lst"
      {"nleftrightarrow;",{226,134,174,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1604 "entities.lst"
      {"nvinfin;",{226,167,158,0,}},
      {(char*)0},
#line 1768 "entities.lst"
      {"rangd;",{226,166,146,0,}},
      {(char*)0}, {(char*)0},
#line 1703 "entities.lst"
      {"plusacir;",{226,168,163,0,}},
#line 1412 "entities.lst"
      {"male;",{226,153,130,0,}},
#line 313 "entities.lst"
      {"MinusPlus;",{226,136,147,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1830 "entities.lst"
      {"risingdotseq;",{226,137,147,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 2136 "entities.lst"
      {"varkappa;",{207,176,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1638 "entities.lst"
      {"ohm;",{206,169,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 2129 "entities.lst"
      {"uwangle;",{226,166,167,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1774 "entities.lst"
      {"rarrap;",{226,165,181,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 632 "entities.lst"
      {"ZeroWidthSpace;",{226,128,139,0,}},
      {(char*)0},
#line 1666 "entities.lst"
      {"orv;",{226,169,155,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1204 "entities.lst"
      {"imath;",{196,177,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 1769 "entities.lst"
      {"range;",{226,166,165,0,}},
      {(char*)0}, {(char*)0},
#line 394 "entities.lst"
      {"Ocy;",{208,158,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 366 "entities.lst"
      {"NotRightTriangleBar;",{226,167,144,204,184,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 38 "entities.lst"
      {"Bopf;",{237,160,181,237,180,185,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 1330 "entities.lst"
      {"lesssim;",{226,137,178,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 1645 "entities.lst"
      {"omacr;",{197,141,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 403 "entities.lst"
      {"OpenCurlyDoubleQuote;",{226,128,156,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 497 "entities.lst"
      {"ShortDownArrow;",{226,134,147,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1620 "entities.lst"
      {"oast;",{226,138,155,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1630 "entities.lst"
      {"oelig;",{197,147,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 1823 "entities.lst"
      {"rightharpoonup;",{226,135,128,0,}},
#line 293 "entities.lst"
      {"Lleftarrow;",{226,135,154,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 340 "entities.lst"
      {"NotExists;",{226,136,132,0,}},
#line 1240 "entities.lst"
      {"jmath;",{200,183,0,}},
#line 390 "entities.lst"
      {"Oacute",{195,147,0,}},
      {(char*)0},
#line 1415 "entities.lst"
      {"map;",{226,134,166,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 391 "entities.lst"
      {"Oacute;",{195,147,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 1712 "entities.lst"
      {"plustwo;",{226,168,167,0,}},
      {(char*)0}, {(char*)0},
#line 542 "entities.lst"
      {"Tilde;",{226,136,188,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1865 "entities.lst"
      {"scE;",{226,170,180,0,}},
#line 546 "entities.lst"
      {"Topf;",{237,160,181,237,181,139,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 1778 "entities.lst"
      {"rarrfs;",{226,164,158,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 2027 "entities.lst"
      {"telrec;",{226,140,149,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1699 "entities.lst"
      {"planck;",{226,132,143,0,}},
      {(char*)0}, {(char*)0},
#line 2133 "entities.lst"
      {"vDash;",{226,138,168,0,}},
#line 2232 "entities.lst"
      {"zwj;",{226,128,141,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 382 "entities.lst"
      {"NotTildeFullEqual;",{226,137,135,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 1656 "entities.lst"
      {"ord;",{226,169,157,0,}},
      {(char*)0}, {(char*)0},
#line 709 "entities.lst"
      {"backprime;",{226,128,181,0,}},
      {(char*)0}, {(char*)0},
#line 1422 "entities.lst"
      {"mcy;",{208,188,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 473 "entities.lst"
      {"RightTriangleEqual;",{226,138,181,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 336 "entities.lst"
      {"NotDoubleVerticalBar;",{226,136,166,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 1642 "entities.lst"
      {"olcross;",{226,166,187,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 713 "entities.lst"
      {"barwed;",{226,140,133,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 1834 "entities.lst"
      {"rmoust;",{226,142,177,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 1015 "entities.lst"
      {"emptyv;",{226,136,133,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 2057 "entities.lst"
      {"triangle;",{226,150,181,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 1564 "entities.lst"
      {"nshortparallel;",{226,136,166,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 1613 "entities.lst"
      {"nwarhk;",{226,164,163,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1649 "entities.lst"
      {"ominus;",{226,138,150,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 594 "entities.lst"
      {"Vdashl;",{226,171,166,0,}},
      {(char*)0},
#line 1626 "entities.lst"
      {"odblac;",{197,145,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 325 "entities.lst"
      {"NegativeVeryThinSpace;",{226,128,139,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 971 "entities.lst"
      {"downharpoonright;",{226,135,130,0,}},
#line 1306 "entities.lst"
      {"leftharpoondown;",{226,134,189,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1648 "entities.lst"
      {"omid;",{226,166,182,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 734 "entities.lst"
      {"bigotimes;",{226,168,130,0,}},
#line 12 "entities.lst"
      {"Acy;",{208,144,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 165 "entities.lst"
      {"FilledVerySmallSquare;",{226,150,170,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 1841 "entities.lst"
      {"ropf;",{237,160,181,237,181,163,0,}},
      {(char*)0}, {(char*)0},
#line 865 "entities.lst"
      {"cirscir;",{226,167,130,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 2020 "entities.lst"
      {"target;",{226,140,150,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 593 "entities.lst"
      {"Vdash;",{226,138,169,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 2092 "entities.lst"
      {"ufr;",{237,160,181,237,180,178,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1644 "entities.lst"
      {"olt;",{226,167,128,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 540 "entities.lst"
      {"ThickSpace;",{226,129,159,226,128,138,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 2144 "entities.lst"
      {"varsubsetneq;",{226,138,138,239,184,128,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 1123 "entities.lst"
      {"glj;",{226,170,164,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 1698 "entities.lst"
      {"piv;",{207,150,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 1681 "entities.lst"
      {"parallel;",{226,136,165,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 1846 "entities.lst"
      {"rppolint;",{226,168,146,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 7 "entities.lst"
      {"Aacute",{195,129,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 8 "entities.lst"
      {"Aacute;",{195,129,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 21 "entities.lst"
      {"ApplyFunction;",{226,129,161,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 1983 "entities.lst"
      {"succsim;",{226,137,191,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1173 "entities.lst"
      {"hookrightarrow;",{226,134,170,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 1485 "entities.lst"
      {"nearhk;",{226,164,164,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 467 "entities.lst"
      {"RightFloor;",{226,140,139,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 2108 "entities.lst"
      {"updownarrow;",{226,134,149,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 462 "entities.lst"
      {"RightCeiling;",{226,140,137,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 1683 "entities.lst"
      {"parsl;",{226,171,189,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 2078 "entities.lst"
      {"uArr;",{226,135,145,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1771 "entities.lst"
      {"raquo",{194,187,0,}},
#line 2107 "entities.lst"
      {"uparrow;",{226,134,145,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 2102 "entities.lst"
      {"umacr;",{197,171,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 2142 "entities.lst"
      {"varrho;",{207,177,0,}},
      {(char*)0},
#line 530 "entities.lst"
      {"TSHcy;",{208,139,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 1822 "entities.lst"
      {"rightharpoondown;",{226,135,129,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1772 "entities.lst"
      {"raquo;",{194,187,0,}},
#line 737 "entities.lst"
      {"bigtriangledown;",{226,150,189,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 543 "entities.lst"
      {"TildeEqual;",{226,137,131,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 474 "entities.lst"
      {"RightUpDownVector;",{226,165,143,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 714 "entities.lst"
      {"barwedge;",{226,140,133,0,}},
      {(char*)0}, {(char*)0},
#line 2041 "entities.lst"
      {"tilde;",{203,156,0,}},
#line 1766 "entities.lst"
      {"raemptyv;",{226,166,179,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 2052 "entities.lst"
      {"topf;",{237,160,181,237,181,165,0,}},
      {(char*)0}, {(char*)0},
#line 590 "entities.lst"
      {"VDash;",{226,138,171,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 97 "entities.lst"
      {"DifferentialD;",{226,133,134,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 1646 "entities.lst"
      {"omega;",{207,137,0,}},
#line 124 "entities.lst"
      {"DownRightTeeVector;",{226,165,159,0,}},
#line 2082 "entities.lst"
      {"uarr;",{226,134,145,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 1309 "entities.lst"
      {"leftrightarrow;",{226,134,148,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 335 "entities.lst"
      {"NotCupCap;",{226,137,173,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 1608 "entities.lst"
      {"nvltrie;",{226,138,180,226,131,146,0,}},
      {(char*)0},
#line 1647 "entities.lst"
      {"omicron;",{206,191,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 2196 "entities.lst"
      {"xopf;",{237,160,181,237,181,169,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 1827 "entities.lst"
      {"rightsquigarrow;",{226,134,157,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 30 "entities.lst"
      {"Backslash;",{226,136,150,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 1423 "entities.lst"
      {"mdash;",{226,128,148,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 1784 "entities.lst"
      {"rarrw;",{226,134,157,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 1820 "entities.lst"
      {"rightarrow;",{226,134,146,0,}},
#line 384 "entities.lst"
      {"NotVerticalBar;",{226,136,164,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 188 "entities.lst"
      {"GreaterSlantEqual;",{226,169,190,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 2089 "entities.lst"
      {"udblac;",{197,177,0,}},
      {(char*)0},
#line 2075 "entities.lst"
      {"twixt;",{226,137,172,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 1202 "entities.lst"
      {"imagline;",{226,132,144,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 33 "entities.lst"
      {"Bcy;",{208,145,0,}},
      {(char*)0}, {(char*)0},
#line 1776 "entities.lst"
      {"rarrbfs;",{226,164,160,0,}},
#line 224 "entities.lst"
      {"InvisibleTimes;",{226,129,162,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 1470 "entities.lst"
      {"naturals;",{226,132,149,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 464 "entities.lst"
      {"RightDownTeeVector;",{226,165,157,0,}},
      {(char*)0},
#line 164 "entities.lst"
      {"FilledSmallSquare;",{226,151,188,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 126 "entities.lst"
      {"DownRightVectorBar;",{226,165,151,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1715 "entities.lst"
      {"popf;",{237,160,181,237,181,161,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 322 "entities.lst"
      {"NegativeMediumSpace;",{226,128,139,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 533 "entities.lst"
      {"Tau;",{206,164,0,}},
#line 2014 "entities.lst"
      {"swarhk;",{226,164,166,0,}},
#line 1825 "entities.lst"
      {"rightleftharpoons;",{226,135,140,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 970 "entities.lst"
      {"downharpoonleft;",{226,135,131,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 536 "entities.lst"
      {"Tcy;",{208,162,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 2062 "entities.lst"
      {"triangleright;",{226,150,185,0,}},
      {(char*)0}, {(char*)0},
#line 1362 "entities.lst"
      {"longrightarrow;",{226,159,182,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 2060 "entities.lst"
      {"trianglelefteq;",{226,138,180,0,}},
#line 1414 "entities.lst"
      {"maltese;",{226,156,160,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 1682 "entities.lst"
      {"parsim;",{226,171,179,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 466 "entities.lst"
      {"RightDownVectorBar;",{226,165,149,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 479 "entities.lst"
      {"RightVectorBar;",{226,165,147,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1418 "entities.lst"
      {"mapstoleft;",{226,134,164,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 1653 "entities.lst"
      {"oplus;",{226,138,149,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 284 "entities.lst"
      {"Leftrightarrow;",{226,135,148,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 1787 "entities.lst"
      {"rationals;",{226,132,154,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 1812 "entities.lst"
      {"rfisht;",{226,165,189,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 115 "entities.lst"
      {"DoubleVerticalBar;",{226,136,165,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 1300 "entities.lst"
      {"ldrdhar;",{226,165,167,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1882 "entities.lst"
      {"searhk;",{226,164,165,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 1714 "entities.lst"
      {"pointint;",{226,168,149,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 2032 "entities.lst"
      {"thetasym;",{207,145,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 1739 "entities.lst"
      {"profsurf;",{226,140,147,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 1650 "entities.lst"
      {"oopf;",{237,160,181,237,181,160,0,}},
#line 270 "entities.lst"
      {"LeftRightVector;",{226,165,142,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1799 "entities.lst"
      {"rcy;",{209,128,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 197 "entities.lst"
      {"HilbertSpace;",{226,132,139,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 1406 "entities.lst"
      {"luruhar;",{226,165,166,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 2143 "entities.lst"
      {"varsigma;",{207,130,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 276 "entities.lst"
      {"LeftTriangleEqual;",{226,138,180,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 2061 "entities.lst"
      {"triangleq;",{226,137,156,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1917 "entities.lst"
      {"smashp;",{226,168,179,0,}},
#line 486 "entities.lst"
      {"RuleDelayed;",{226,167,180,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 357 "entities.lst"
      {"NotLessSlantEqual;",{226,169,189,204,184,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 2058 "entities.lst"
      {"triangledown;",{226,150,191,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 1159 "entities.lst"
      {"harrcir;",{226,165,136,0,}},
      {(char*)0},
#line 300 "entities.lst"
      {"Longrightarrow;",{226,159,185,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 123 "entities.lst"
      {"DownLeftVectorBar;",{226,165,150,0,}},
      {(char*)0},
#line 1764 "entities.lst"
      {"racute;",{197,149,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 516 "entities.lst"
      {"SubsetEqual;",{226,138,134,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 1279 "entities.lst"
      {"larrsim;",{226,165,179,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 285 "entities.lst"
      {"LessEqualGreater;",{226,139,154,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1719 "entities.lst"
      {"prE;",{226,170,179,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 2076 "entities.lst"
      {"twoheadleftarrow;",{226,134,158,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 125 "entities.lst"
      {"DownRightVector;",{226,135,129,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1659 "entities.lst"
      {"ordf",{194,170,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 1660 "entities.lst"
      {"ordf;",{194,170,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 1821 "entities.lst"
      {"rightarrowtail;",{226,134,163,0,}},
      {(char*)0},
#line 423 "entities.lst"
      {"PlusMinus;",{194,177,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 2021 "entities.lst"
      {"tau;",{207,132,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 269 "entities.lst"
      {"LeftRightArrow;",{226,134,148,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 2073 "entities.lst"
      {"tshcy;",{209,155,0,}},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 2025 "entities.lst"
      {"tcy;",{209,130,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 465 "entities.lst"
      {"RightDownVector;",{226,135,130,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 545 "entities.lst"
      {"TildeTilde;",{226,137,136,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 2111 "entities.lst"
      {"uplus;",{226,138,142,0,}},
#line 2059 "entities.lst"
      {"triangleleft;",{226,151,131,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1678 "entities.lst"
      {"par;",{226,136,165,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 2106 "entities.lst"
      {"uopf;",{237,160,181,237,181,166,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 1835 "entities.lst"
      {"rmoustache;",{226,142,177,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 1737 "entities.lst"
      {"profalar;",{226,140,174,0,}},
#line 2103 "entities.lst"
      {"uml",{194,168,0,}},
      {(char*)0}, {(char*)0},
#line 1155 "entities.lst"
      {"half;",{194,189,0,}},
      {(char*)0},
#line 710 "entities.lst"
      {"backsim;",{226,136,189,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 297 "entities.lst"
      {"LongRightArrow;",{226,159,182,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 1310 "entities.lst"
      {"leftrightarrows;",{226,135,134,0,}},
      {(char*)0},
#line 418 "entities.lst"
      {"PartialD;",{226,136,130,0,}},
      {(char*)0},
#line 532 "entities.lst"
      {"Tab;",{9,0,}},
#line 1685 "entities.lst"
      {"pcy;",{208,191,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 324 "entities.lst"
      {"NegativeThinSpace;",{226,128,139,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 2113 "entities.lst"
      {"upsih;",{207,146,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 1700 "entities.lst"
      {"planckh;",{226,132,142,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 458 "entities.lst"
      {"RightAngleBracket;",{226,159,169,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 1469 "entities.lst"
      {"natural;",{226,153,174,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 223 "entities.lst"
      {"InvisibleComma;",{226,129,163,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1276 "entities.lst"
      {"larrhk;",{226,134,169,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 2171 "entities.lst"
      {"vzigzag;",{226,166,154,0,}},
      {(char*)0},
#line 1169 "entities.lst"
      {"hkswarow;",{226,164,166,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 863 "entities.lst"
      {"cirfnint;",{226,168,144,0,}},
#line 2150 "entities.lst"
      {"vartriangleright;",{226,138,179,0,}},
      {(char*)0},
#line 2063 "entities.lst"
      {"trianglerighteq;",{226,138,181,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 1624 "entities.lst"
      {"ocy;",{208,190,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1730 "entities.lst"
      {"precsim;",{226,137,190,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 711 "entities.lst"
      {"backsimeq;",{226,139,141,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 2083 "entities.lst"
      {"ubrcy;",{209,158,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 1618 "entities.lst"
      {"oacute",{195,179,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1619 "entities.lst"
      {"oacute;",{195,179,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 92 "entities.lst"
      {"DiacriticalDot;",{203,153,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 32 "entities.lst"
      {"Barwed;",{226,140,134,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 2053 "entities.lst"
      {"topfork;",{226,171,154,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 2091 "entities.lst"
      {"ufisht;",{226,165,190,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 2087 "entities.lst"
      {"ucy;",{209,131,0,}},
      {(char*)0},
#line 94 "entities.lst"
      {"DiacriticalGrave;",{96,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 2148 "entities.lst"
      {"vartheta;",{207,145,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 2149 "entities.lst"
      {"vartriangleleft;",{226,138,178,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1625 "entities.lst"
      {"odash;",{226,138,157,0,}},
      {(char*)0},
#line 2080 "entities.lst"
      {"uacute",{195,186,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 2081 "entities.lst"
      {"uacute;",{195,186,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 566 "entities.lst"
      {"UnderBracket;",{226,142,181,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 148 "entities.lst"
      {"EmptyVerySmallSquare;",{226,150,171,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 290 "entities.lst"
      {"LessTilde;",{226,137,178,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 1697 "entities.lst"
      {"pitchfork;",{226,139,148,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 1824 "entities.lst"
      {"rightleftarrows;",{226,135,132,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 47 "entities.lst"
      {"CapitalDifferentialD;",{226,133,133,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 1705 "entities.lst"
      {"pluscir;",{226,168,162,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1711 "entities.lst"
      {"plussim;",{226,168,166,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 95 "entities.lst"
      {"DiacriticalTilde;",{203,156,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 91 "entities.lst"
      {"DiacriticalAcute;",{194,180,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 1828 "entities.lst"
      {"rightthreetimes;",{226,139,140,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 147 "entities.lst"
      {"EmptySmallSquare;",{226,151,187,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 2104 "entities.lst"
      {"uml;",{194,168,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 2138 "entities.lst"
      {"varphi;",{207,149,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 463 "entities.lst"
      {"RightDoubleBracket;",{226,159,167,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 1782 "entities.lst"
      {"rarrsim;",{226,165,180,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 544 "entities.lst"
      {"TildeFullEqual;",{226,137,133,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 2077 "entities.lst"
      {"twoheadrightarrow;",{226,134,160,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
#line 1779 "entities.lst"
      {"rarrhk;",{226,134,170,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0},
#line 1738 "entities.lst"
      {"profline;",{226,140,146,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 93 "entities.lst"
      {"DiacriticalDoubleAcute;",{203,157,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 576 "entities.lst"
      {"UpEquilibrium;",{226,165,174,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 1801 "entities.lst"
      {"rdldhar;",{226,165,169,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 1860 "entities.lst"
      {"ruluhar;",{226,165,168,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0},
#line 2070 "entities.lst"
      {"trpezium;",{226,143,162,0,}},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0}, {(char*)0}, {(char*)0},
      {(char*)0}, {(char*)0},
#line 323 "entities.lst"
      {"NegativeThickSpace;",{226,128,139,0,}}
    };

  if (len <= MAX_WORD_LENGTH && len >= MIN_WORD_LENGTH)
    {
      register unsigned int key = entity_hash (str, len);

      if (key <= MAX_HASH_VALUE)
        {
          register const char *s = wordlist[key].Name;

          if (s && *str == *s && !strncmp (str + 1, s + 1, len - 1) && s[len] == '\0')
            return &wordlist[key];
        }
    }
  return 0;
}
