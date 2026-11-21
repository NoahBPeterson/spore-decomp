// Slice s0090f980: expat 2.0.1 xmltok.c / xmltok_impl.c, as linked into SporeApp.exe
// (UTFSpore_Win32/xmltok.obj) -- the normal_ single-byte scanners' skipS/updatePosition, the
// UTF-8/Latin-1/ASCII and little2/big2 encoding converters from xmltok.c, and the little2
// comment/decl/PI/CDATA scanners.  MIT license, see expat's COPYING.
//
// The original object is one translation unit (xmltok.c) that includes xmltok_impl.c once for
// the normal_ encodings and once each for little2/big2; this file reproduces the whole little2
// instantiation plus the individual xmltok.c functions this slice covers, because the static
// scanners only get MSVC's register calling convention from same-TU callers.  The converters and
// normal_skipS/normal_updatePosition are address-taken by the encoding tables in the original
// (standard calling convention), so they are non-static here.  The trailing little2_prologTok &
// friends are roots from the neighbouring slice s00911f60 that must stay emitted so that the
// static same-TU scanners they reach (little2_scanDecl in particular) are still generated; they
// are annotated with `// 0x<va>` rather than a `// @` marker to keep each slice's markers unique.
#include "types.h"
#include <stddef.h>

// ---- expat 2.0.1 winconfig.h settings used by Spore ----
#define XML_NS 1
#define XML_DTD 1
#define XML_CONTEXT_BYTES 1024
#define BYTEORDER 1234
#define HAVE_MEMMOVE
#define XML_STATIC
#define XML_BUILDING_EXPAT 1

typedef char XML_Char;
typedef unsigned long XML_Size;
typedef int XML_Bool; /* XML_Bool is unsigned char in expat; only the size matters here */

// ---- ascii.h ----
#define ASCII_A 0x41
#define ASCII_B 0x42
#define ASCII_C 0x43
#define ASCII_D 0x44
#define ASCII_E 0x45
#define ASCII_F 0x46
#define ASCII_G 0x47
#define ASCII_H 0x48
#define ASCII_I 0x49
#define ASCII_J 0x4A
#define ASCII_K 0x4B
#define ASCII_L 0x4C
#define ASCII_M 0x4D
#define ASCII_N 0x4E
#define ASCII_O 0x4F
#define ASCII_P 0x50
#define ASCII_Q 0x51
#define ASCII_R 0x52
#define ASCII_S 0x53
#define ASCII_T 0x54
#define ASCII_U 0x55
#define ASCII_V 0x56
#define ASCII_W 0x57
#define ASCII_X 0x58
#define ASCII_Y 0x59
#define ASCII_Z 0x5A

#define ASCII_a 0x61
#define ASCII_b 0x62
#define ASCII_c 0x63
#define ASCII_d 0x64
#define ASCII_e 0x65
#define ASCII_f 0x66
#define ASCII_g 0x67
#define ASCII_h 0x68
#define ASCII_i 0x69
#define ASCII_j 0x6A
#define ASCII_k 0x6B
#define ASCII_l 0x6C
#define ASCII_m 0x6D
#define ASCII_n 0x6E
#define ASCII_o 0x6F
#define ASCII_p 0x70
#define ASCII_q 0x71
#define ASCII_r 0x72
#define ASCII_s 0x73
#define ASCII_t 0x74
#define ASCII_u 0x75
#define ASCII_v 0x76
#define ASCII_w 0x77
#define ASCII_x 0x78
#define ASCII_y 0x79
#define ASCII_z 0x7A

#define ASCII_0 0x30
#define ASCII_1 0x31
#define ASCII_2 0x32
#define ASCII_3 0x33
#define ASCII_4 0x34
#define ASCII_5 0x35
#define ASCII_6 0x36
#define ASCII_7 0x37
#define ASCII_8 0x38
#define ASCII_9 0x39

#define ASCII_TAB 0x09
#define ASCII_SPACE 0x20
#define ASCII_EXCL 0x21
#define ASCII_QUOT 0x22
#define ASCII_AMP 0x26
#define ASCII_APOS 0x27
#define ASCII_MINUS 0x2D
#define ASCII_PERIOD 0x2E
#define ASCII_COLON 0x3A
#define ASCII_SEMI 0x3B
#define ASCII_LT 0x3C
#define ASCII_EQUALS 0x3D
#define ASCII_GT 0x3E
#define ASCII_LSQB 0x5B
#define ASCII_RSQB 0x5D
#define ASCII_UNDERSCORE 0x5F
#define ASCII_LPAREN 0x28
#define ASCII_RPAREN 0x29
#define ASCII_FF 0x0C
#define ASCII_SLASH 0x2F
#define ASCII_HASH 0x23
#define ASCII_PIPE 0x7C
#define ASCII_COMMA 0x2C

// ---- xmltok.h types ----
#define PTRCALL
#define PTRFASTCALL
#define FASTCALL

#ifndef NULL
#define NULL 0
#endif

enum {
  BT_NONXML,
  BT_MALFORM,
  BT_LT,
  BT_AMP,
  BT_RSQB,
  BT_LEAD2,
  BT_LEAD3,
  BT_LEAD4,
  BT_TRAIL,
  BT_CR,
  BT_LF,
  BT_GT,
  BT_QUOT,
  BT_APOS,
  BT_EQUALS,
  BT_QUEST,
  BT_EXCL,
  BT_SOL,
  BT_SEMI,
  BT_NUM,
  BT_LSQB,
  BT_S,
  BT_NMSTRT,
  BT_COLON,
  BT_HEX,
  BT_DIGIT,
  BT_NAME,
  BT_MINUS,
  BT_OTHER, /* known not to be a name or name start character */
  BT_NONASCII, /* might be a name or name start character */
  BT_PERCNT,
  BT_LPAR,
  BT_RPAR,
  BT_AST,
  BT_PLUS,
  BT_COMMA,
  BT_VERBAR
};

typedef struct position {
  XML_Size lineNumber;
  XML_Size columnNumber;
} POSITION;

typedef struct {
  const char *name;
  const char *valuePtr;
  const char *valueEnd;
  char normalized;
} ATTRIBUTE;

struct encoding;
typedef struct encoding ENCODING;

typedef int (PTRCALL *SCANNER)(const ENCODING *,
                               const char *,
                               const char *,
                               const char **);

struct encoding {
  SCANNER scanners[4];
  SCANNER literalScanners[2];
  int (PTRCALL *sameName)(const ENCODING *,
                          const char *,
                          const char *);
  int (PTRCALL *nameMatchesAscii)(const ENCODING *,
                                  const char *,
                                  const char *,
                                  const char *);
  int (PTRFASTCALL *nameLength)(const ENCODING *, const char *);
  const char *(PTRFASTCALL *skipS)(const ENCODING *, const char *);
  int (PTRCALL *getAtts)(const ENCODING *enc,
                         const char *ptr,
                         int attsMax,
                         ATTRIBUTE *atts);
  int (PTRFASTCALL *charRefNumber)(const ENCODING *enc, const char *ptr);
  int (PTRCALL *predefinedEntityName)(const ENCODING *,
                                      const char *,
                                      const char *);
  void (PTRCALL *updatePosition)(const ENCODING *,
                                 const char *ptr,
                                 const char *end,
                                 POSITION *);
  int (PTRCALL *isPublicId)(const ENCODING *enc,
                            const char *ptr,
                            const char *end,
                            const char **badPtr);
  void (PTRCALL *utf8Convert)(const ENCODING *enc,
                              const char **fromP,
                              const char *fromLim,
                              char **toP,
                              const char *toLim);
  void (PTRCALL *utf16Convert)(const ENCODING *enc,
                               const char **fromP,
                               const char *fromLim,
                               unsigned short **toP,
                               const unsigned short *toLim);
  int minBytesPerChar;
  char isUtf8;
  char isUtf16;
};

struct normal_encoding {
  ENCODING enc;
  unsigned char type[256];
  int (PTRCALL *isName2)(const ENCODING *, const char *);
  int (PTRCALL *isName3)(const ENCODING *, const char *);
  int (PTRCALL *isName4)(const ENCODING *, const char *);
  int (PTRCALL *isNmstrt2)(const ENCODING *, const char *);
  int (PTRCALL *isNmstrt3)(const ENCODING *, const char *);
  int (PTRCALL *isNmstrt4)(const ENCODING *, const char *);
  int (PTRCALL *isInvalid2)(const ENCODING *, const char *);
  int (PTRCALL *isInvalid3)(const ENCODING *, const char *);
  int (PTRCALL *isInvalid4)(const ENCODING *, const char *);
};

#define XML_TOK_TRAILING_RSQB -5
#define XML_TOK_NONE -4
#define XML_TOK_TRAILING_CR -3
#define XML_TOK_PARTIAL_CHAR -2
#define XML_TOK_PARTIAL -1
#define XML_TOK_INVALID 0
#define XML_TOK_START_TAG_WITH_ATTS 1
#define XML_TOK_START_TAG_NO_ATTS 2
#define XML_TOK_EMPTY_ELEMENT_WITH_ATTS 3
#define XML_TOK_EMPTY_ELEMENT_NO_ATTS 4
#define XML_TOK_END_TAG 5
#define XML_TOK_DATA_CHARS 6
#define XML_TOK_DATA_NEWLINE 7
#define XML_TOK_CDATA_SECT_OPEN 8
#define XML_TOK_ENTITY_REF 9
#define XML_TOK_CHAR_REF 10
#define XML_TOK_PI 11
#define XML_TOK_XML_DECL 12
#define XML_TOK_COMMENT 13
#define XML_TOK_BOM 14
#define XML_TOK_PROLOG_S 15
#define XML_TOK_DECL_OPEN 16
#define XML_TOK_DECL_CLOSE 17
#define XML_TOK_NAME 18
#define XML_TOK_NMTOKEN 19
#define XML_TOK_POUND_NAME 20
#define XML_TOK_OR 21
#define XML_TOK_PERCENT 22
#define XML_TOK_OPEN_PAREN 23
#define XML_TOK_CLOSE_PAREN 24
#define XML_TOK_OPEN_BRACKET 25
#define XML_TOK_CLOSE_BRACKET 26
#define XML_TOK_LITERAL 27
#define XML_TOK_PARAM_ENTITY_REF 28
#define XML_TOK_INSTANCE_START 29
#define XML_TOK_NAME_QUESTION 30
#define XML_TOK_NAME_ASTERISK 31
#define XML_TOK_NAME_PLUS 32
#define XML_TOK_COND_SECT_OPEN 33
#define XML_TOK_COND_SECT_CLOSE 34
#define XML_TOK_CLOSE_PAREN_QUESTION 35
#define XML_TOK_CLOSE_PAREN_ASTERISK 36
#define XML_TOK_CLOSE_PAREN_PLUS 37
#define XML_TOK_COMMA 38
#define XML_TOK_ATTRIBUTE_VALUE_S 39
#define XML_TOK_CDATA_SECT_CLOSE 40
#define XML_TOK_PREFIXED_NAME 41
#define XML_TOK_IGNORE_SECT 42

// ---- xmltok.c data referenced by the little2 scanners ----
extern const unsigned char namePages[256];     // 0x143b428
extern const unsigned char nmstrtPages[256];   // 0x143b328
extern const unsigned int  namingBitmap[];     // 0x143ae28
extern const struct normal_encoding latin1_encoding;  // 0x143bc60

// @ 0x0090fcb0
static int PTRFASTCALL unicode_byte_type(char hi, char lo)
{
  switch ((unsigned char)hi) {
  case 0xD8: case 0xD9: case 0xDA: case 0xDB:
    return BT_LEAD4;
  case 0xDC: case 0xDD: case 0xDE: case 0xDF:
    return BT_TRAIL;
  case 0xFF:
    switch ((unsigned char)lo) {
    case 0xFF:
    case 0xFE:
      return BT_NONXML;
    }
    break;
  }
  return BT_NONASCII;
}

#define UCS2_GET_NAMING(pages, hi, lo) \
   (namingBitmap[(pages[hi] << 3) + ((lo) >> 5)] & (1 << ((lo) & 0x1F)))

static int FASTCALL checkCharRefNumber(int result)
{
  switch (result >> 8) {
  case 0xD8: case 0xD9: case 0xDA: case 0xDB:
  case 0xDC: case 0xDD: case 0xDE: case 0xDF:
    return -1;
  case 0:
    if (latin1_encoding.type[result] == BT_NONXML)
      return -1;
    break;
  case 0xFF:
    if (result == 0xFFFE || result == 0xFFFF)
      return -1;
    break;
  }
  return result;
}

// ---- xmltok.c little2 macro instantiation ----
#define LITTLE2_BYTE_TYPE(enc, p) \
 ((p)[1] == 0 \
  ? ((struct normal_encoding *)(enc))->type[(unsigned char)*(p)] \
  : unicode_byte_type((p)[1], (p)[0]))
#define LITTLE2_BYTE_TO_ASCII(enc, p) ((p)[1] == 0 ? (p)[0] : -1)
#define LITTLE2_CHAR_MATCHES(enc, p, c) ((p)[1] == 0 && (p)[0] == c)
#define LITTLE2_IS_NAME_CHAR_MINBPC(enc, p) \
  UCS2_GET_NAMING(namePages, (unsigned char)p[1], (unsigned char)p[0])
#define LITTLE2_IS_NMSTRT_CHAR_MINBPC(enc, p) \
  UCS2_GET_NAMING(nmstrtPages, (unsigned char)p[1], (unsigned char)p[0])

#define PREFIX(ident) little2_ ## ident
#define MINBPC(enc) 2
/* CHAR_MATCHES is guaranteed to have MINBPC bytes available. */
#define BYTE_TYPE(enc, p) LITTLE2_BYTE_TYPE(enc, p)
#define BYTE_TO_ASCII(enc, p) LITTLE2_BYTE_TO_ASCII(enc, p)
#define CHAR_MATCHES(enc, p, c) LITTLE2_CHAR_MATCHES(enc, p, c)
#define IS_NAME_CHAR(enc, p, n) 0
#define IS_NAME_CHAR_MINBPC(enc, p) LITTLE2_IS_NAME_CHAR_MINBPC(enc, p)
#define IS_NMSTRT_CHAR(enc, p, n) (0)
#define IS_NMSTRT_CHAR_MINBPC(enc, p) LITTLE2_IS_NMSTRT_CHAR_MINBPC(enc, p)

#define XML_TOK_IMPL_C
// Upstream xmltok_impl.c (expat 2.0.1) with this slice's changes (tools/ci/oss/expat-retail.patch); the
// patched copy is built by tools/ci/setup_oss.sh.  Notes and markers from the original pasted copy:
// @ 0x00910290
// @ 0x009103a0
// @ 0x009104f0
// @ 0x00910570
// @ 0x00910890
// 0x00911880 little2_contentTok (root from a neighbouring slice; kept so scanLt ->
// scanCdataSection stay emitted -- the encoding vtable that reaches it in the original
// is not part of this file)
// 0x00911f60 little2_prologTok (root from slice s00911f60; kept for reachability)
// 0x009125f0 little2_attributeValueTok (root from slice s00911f60)
// 0x00912750 little2_entityValueTok (root from slice s00911f60)
// 0x009128b0 little2_ignoreSectionTok (root from slice s00911f60)
// 0x009129f0 little2_isPublicId (root from slice s00911f60)
// 0x00912ad0 little2_getAtts (root from slice s00911f60)
// 0x00912d70 little2_predefinedEntityName (root from slice s00911f60)
#include "../../../work/third_party/build/expat-retail/xmltok_impl_s0090f980_1.c"

// =====================================================================================
// xmltok.c: the normal_ (single-byte) instantiation's skipS/updatePosition, plus the
// UTF-8 / Latin-1 / ASCII / little2 / big2 encoding converters.  In the original every one
// of these has its address taken by an encoding table, so it uses the standard calling
// convention; they are non-static here for the same reason (a static, address-not-taken
// function would get MSVC's internal register convention instead).
// =====================================================================================

// @ 0x0090f980  normal_skipS  (xmltok_impl.c skipS; MINBPC(enc)==1, type byte from the table)
const char * PTRFASTCALL
normal_skipS(const ENCODING *enc, const char *ptr)
{
  for (;;) {
    switch (((const struct normal_encoding *)enc)->type[(unsigned char)*ptr]) {
    case BT_LF:
    case BT_CR:
    case BT_S:
      ptr += 1;
      break;
    default:
      return ptr;
    }
  }
}

// @ 0x0090f9b0  normal_updatePosition
void PTRCALL
normal_updatePosition(const ENCODING *enc,
                      const char *ptr,
                      const char *end,
                      POSITION *pos)
{
  while (ptr != end) {
    switch (((const struct normal_encoding *)enc)->type[(unsigned char)*ptr]) {
#define LEAD_CASE(n) \
    case BT_LEAD ## n: \
      ptr += n; \
      break;
    LEAD_CASE(2) LEAD_CASE(3) LEAD_CASE(4)
#undef LEAD_CASE
    case BT_LF:
      pos->columnNumber = (XML_Size)-1;
      pos->lineNumber++;
      ptr += 1;
      break;
    case BT_CR:
      pos->lineNumber++;
      ptr += 1;
      if (ptr != end
          && ((const struct normal_encoding *)enc)->type[(unsigned char)*ptr] == BT_LF)
        ptr += 1;
      pos->columnNumber = (XML_Size)-1;
      break;
    default:
      ptr += 1;
      break;
    }
    pos->columnNumber++;
  }
}

// ---- xmltok.c: UTF-8 conversions ----

enum {  /* UTF8_cvalN is the value of the masked first byte of an N byte sequence */
  UTF8_cval1 = 0x00,
  UTF8_cval2 = 0xc0,
  UTF8_cval3 = 0xe0,
  UTF8_cval4 = 0xf0
};

// @ 0x0090fa40  utf8_toUtf8
void PTRCALL
utf8_toUtf8(const ENCODING *enc,
            const char **fromP, const char *fromLim,
            char **toP, const char *toLim)
{
  char *to;
  const char *from;
  if (fromLim - *fromP > toLim - *toP) {
    /* Avoid copying partial characters. */
    for (fromLim = *fromP + (toLim - *toP); fromLim > *fromP; fromLim--)
      if (((unsigned char)fromLim[-1] & 0xc0) != 0x80)
        break;
  }
  for (to = *toP, from = *fromP; from != fromLim; from++, to++)
    *to = *from;
  *fromP = from;
  *toP = to;
}

// @ 0x0090fab0  utf8_toUtf16
void PTRCALL
utf8_toUtf16(const ENCODING *enc,
             const char **fromP, const char *fromLim,
             unsigned short **toP, const unsigned short *toLim)
{
  unsigned short *to = *toP;
  const char *from = *fromP;
  while (from != fromLim && to != toLim) {
    switch (((struct normal_encoding *)enc)->type[(unsigned char)*from]) {
    case BT_LEAD2:
      *to++ = (unsigned short)(((from[0] & 0x1f) << 6) | (from[1] & 0x3f));
      from += 2;
      break;
    case BT_LEAD3:
      *to++ = (unsigned short)(((from[0] & 0xf) << 12)
                               | ((from[1] & 0x3f) << 6) | (from[2] & 0x3f));
      from += 3;
      break;
    case BT_LEAD4:
      {
        unsigned long n;
        if (to + 1 == toLim)
          goto after;
        n = ((from[0] & 0x7) << 18) | ((from[1] & 0x3f) << 12)
            | ((from[2] & 0x3f) << 6) | (from[3] & 0x3f);
        n -= 0x10000;
        to[0] = (unsigned short)((n >> 10) | 0xD800);
        to[1] = (unsigned short)((n & 0x3FF) | 0xDC00);
        to += 2;
        from += 4;
      }
      break;
    default:
      *to++ = *from++;
      break;
    }
  }
after:
  *fromP = from;
  *toP = to;
}

// @ 0x0090fbe0  latin1_toUtf8
void PTRCALL
latin1_toUtf8(const ENCODING *enc,
              const char **fromP, const char *fromLim,
              char **toP, const char *toLim)
{
  for (;;) {
    unsigned char c;
    if (*fromP == fromLim)
      break;
    c = (unsigned char)**fromP;
    if (c & 0x80) {
      if (toLim - *toP < 2)
        break;
      *(*toP)++ = (char)((c >> 6) | UTF8_cval2);
      *(*toP)++ = (char)((c & 0x3f) | 0x80);
      (*fromP)++;
    }
    else {
      if (*toP == toLim)
        break;
      *(*toP)++ = *(*fromP)++;
    }
  }
}

// @ 0x0090fc40  latin1_toUtf16
void PTRCALL
latin1_toUtf16(const ENCODING *enc,
               const char **fromP, const char *fromLim,
               unsigned short **toP, const unsigned short *toLim)
{
  while (*fromP != fromLim && *toP != toLim)
    *(*toP)++ = (unsigned char)*(*fromP)++;
}

// @ 0x0090fc80  ascii_toUtf8
void PTRCALL
ascii_toUtf8(const ENCODING *enc,
             const char **fromP, const char *fromLim,
             char **toP, const char *toLim)
{
  while (*fromP != fromLim && *toP != toLim)
    *(*toP)++ = *(*fromP)++;
}

// ---- xmltok.c: UTF-16 <-> UTF-8/UTF-16 conversions (little2 / big2) ----
// These are macro instantiations of DEFINE_UTF16_TO_UTF8/UTF16 in the original, so each
// `// @` marker sits on the invocation that expands to the function it names.

#define SET2(ptr, ch) \
  (((ptr)[0] = ((ch) & 0xff)), ((ptr)[1] = ((ch) >> 8)))
#define GET_LO(ptr) ((unsigned char)(ptr)[0])
#define GET_HI(ptr) ((unsigned char)(ptr)[1])

#define DEFINE_UTF16_TO_UTF8(E) \
void PTRCALL \
E ## toUtf8(const ENCODING *enc, \
            const char **fromP, const char *fromLim, \
            char **toP, const char *toLim) \
{ \
  const char *from; \
  for (from = *fromP; from != fromLim; from += 2) { \
    int plane; \
    unsigned char lo2; \
    unsigned char lo = GET_LO(from); \
    unsigned char hi = GET_HI(from); \
    switch (hi) { \
    case 0: \
      if (lo < 0x80) { \
        if (*toP == toLim) { \
          *fromP = from; \
          return; \
        } \
        *(*toP)++ = lo; \
        break; \
      } \
      /* fall through */ \
    case 0x1: case 0x2: case 0x3: \
    case 0x4: case 0x5: case 0x6: case 0x7: \
      if (toLim -  *toP < 2) { \
        *fromP = from; \
        return; \
      } \
      *(*toP)++ = ((lo >> 6) | (hi << 2) |  UTF8_cval2); \
      *(*toP)++ = ((lo & 0x3f) | 0x80); \
      break; \
    default: \
      if (toLim -  *toP < 3)  { \
        *fromP = from; \
        return; \
      } \
      /* 16 bits divided 4, 6, 6 amongst 3 bytes */ \
      *(*toP)++ = ((hi >> 4) | UTF8_cval3); \
      *(*toP)++ = (((hi & 0xf) << 2) | (lo >> 6) | 0x80); \
      *(*toP)++ = ((lo & 0x3f) | 0x80); \
      break; \
    case 0xD8: case 0xD9: case 0xDA: case 0xDB: \
      if (toLim -  *toP < 4) { \
        *fromP = from; \
        return; \
      } \
      plane = (((hi & 0x3) << 2) | ((lo >> 6) & 0x3)) + 1; \
      *(*toP)++ = ((plane >> 2) | UTF8_cval4); \
      *(*toP)++ = (((lo >> 2) & 0xF) | ((plane & 0x3) << 4) | 0x80); \
      from += 2; \
      lo2 = GET_LO(from); \
      *(*toP)++ = (((lo & 0x3) << 4) \
                   | ((GET_HI(from) & 0x3) << 2) \
                   | (lo2 >> 6) \
                   | 0x80); \
      *(*toP)++ = ((lo2 & 0x3f) | 0x80); \
      break; \
    } \
  } \
  *fromP = from; \
}

#define DEFINE_UTF16_TO_UTF16(E) \
void PTRCALL \
E ## toUtf16(const ENCODING *enc, \
             const char **fromP, const char *fromLim, \
             unsigned short **toP, const unsigned short *toLim) \
{ \
  /* Avoid copying first half only of surrogate */ \
  if (fromLim - *fromP > ((toLim - *toP) << 1) \
      && (GET_HI(fromLim - 2) & 0xF8) == 0xD8) \
    fromLim -= 2; \
  for (; *fromP != fromLim && *toP != toLim; *fromP += 2) \
    *(*toP)++ = (GET_HI(*fromP) << 8) | GET_LO(*fromP); \
}

// @ 0x0090fd30  little2_toUtf8
DEFINE_UTF16_TO_UTF8(little2_)

// @ 0x0090ff70  little2_toUtf16
DEFINE_UTF16_TO_UTF16(little2_)

#undef SET2
#undef GET_LO
#undef GET_HI

#define SET2(ptr, ch) \
  (((ptr)[0] = ((ch) >> 8)), ((ptr)[1] = ((ch) & 0xFF)))
#define GET_LO(ptr) ((unsigned char)(ptr)[1])
#define GET_HI(ptr) ((unsigned char)(ptr)[0])

// @ 0x0090ffe0  big2_toUtf8
DEFINE_UTF16_TO_UTF8(big2_)

// @ 0x00910220  big2_toUtf16
DEFINE_UTF16_TO_UTF16(big2_)

#undef SET2
#undef GET_LO
#undef GET_HI
#undef DEFINE_UTF16_TO_UTF8
#undef DEFINE_UTF16_TO_UTF16
