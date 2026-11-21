// Slice s0090c240: expat 2.0.1 xmlrole.c prolog state machine (internalSubset, doctype1,
// prolog1, externalSubset, XmlPrologStateInit/ExternalEntity), the xmltok.c UTF-8
// naming/validity helpers and the normal_ (single-byte) scanner statics used by the prolog
// tokenizer.  MIT license, see expat's COPYING.
//
// The role handlers are cdecl callbacks (their addresses are stored in PROLOG_STATE) and the
// utf8_* helpers are cdecl; both reproduce byte-for-byte.  The normal_scan*/normal_checkPiTarget
// statics were compiled by the original build with whole-program register conventions (enc in
// ebx, ptr in eax, ...), which cl.exe only emits under /GL; those four are behaviourally
// equivalent only (see nonmatching.txt).  The helper scanners above are kept from the same
// xmltok.c translation unit so the four target functions keep their original call structure.
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

// ---- xmltok.c data referenced by the normal_ scanners ----
extern const unsigned char namePages[256];     // 0x143b428
extern const unsigned char nmstrtPages[256];   // 0x143b328
extern const unsigned int  namingBitmap[];     // 0x143ae28
extern const struct normal_encoding latin1_encoding;  // 0x143bc60

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

// ---- xmltok.c normal_ (single-byte) macro instantiation ----
#define AS_NORMAL_ENCODING(enc)   ((const struct normal_encoding *) (enc))

/* minimum bytes per character */
#define MINBPC(enc) 1

#define BYTE_TYPE(enc, p) \
  (((struct normal_encoding *)(enc))->type[(unsigned char)*(p)])
#define BYTE_TO_ASCII(enc, p) (*(p))
#define IS_NAME_CHAR(enc, p, n) \
 (AS_NORMAL_ENCODING(enc)->isName ## n(enc, p))
#define IS_NMSTRT_CHAR(enc, p, n) \
 (AS_NORMAL_ENCODING(enc)->isNmstrt ## n(enc, p))
#define IS_INVALID_CHAR(enc, p, n) \
 (AS_NORMAL_ENCODING(enc)->isInvalid ## n(enc, p))
#define IS_NAME_CHAR_MINBPC(enc, p) (0)
#define IS_NMSTRT_CHAR_MINBPC(enc, p) (0)
/* c is an ASCII character */
#define CHAR_MATCHES(enc, p, c) (*(p) == c)

#define PREFIX(ident) normal_ ## ident

#define XML_TOK_IMPL_C
// Upstream xmltok_impl.c (expat 2.0.1) with this slice's changes (tools/ci/oss/expat-retail.patch); the
// patched copy is built by tools/ci/setup_oss.sh.  Notes and markers from the original pasted copy:
// @ 0x0090cb20
// @ 0x0090cc60
// @ 0x0090cd70
// @ 0x0090cdd0
// ============================================================================
// xmltok.c: UTF-8 naming/validity helpers (address-taken by the utf8 encoding)
// ============================================================================
#include "../../../work/third_party/build/expat-retail/xmltok_impl_s0090c240_1.c"

/* A 2 byte UTF-8 representation splits the character into 11 bits.
   The index will be 5 bits from the first byte and 3 bits from the second.
*/
#define UTF8_GET_NAMING2(pages, byte) \
    (namingBitmap[((pages)[(((byte)[0]) >> 2) & 7] << 3) \
                      + ((((byte)[0]) & 3) << 1) \
                      + ((((byte)[1]) >> 5) & 1)] \
         & (1 << (((byte)[1]) & 0x1F)))

/* A 3 byte UTF-8 representation splits the character into 16 bits
   between the first two bytes.
*/
#define UTF8_GET_NAMING3(pages, byte) \
  (namingBitmap[((pages)[((((byte)[0]) & 0xF) << 4) \
                             + ((((byte)[1]) >> 2) & 0xF)] \
                       << 3) \
                      + ((((byte)[1]) & 3) << 1) \
                      + ((((byte)[2]) >> 5) & 1)] \
         & (1 << (((byte)[2]) & 0x1F)))

/* Detection of invalid UTF-8 sequences (Unicode 3.2 table 3.1B, with the
   extra restriction of not allowing U+FFFE and U+FFFF).
*/
#define UTF8_INVALID2(p) \
  ((*p) < 0xC2 || ((p)[1] & 0x80) == 0 || ((p)[1] & 0xC0) == 0xC0)

#define UTF8_INVALID3(p) \
  (((p)[2] & 0x80) == 0 \
  || \
  ((*p) == 0xEF && (p)[1] == 0xBF \
    ? \
    (p)[2] > 0xBD \
    : \
    ((p)[2] & 0xC0) == 0xC0) \
  || \
  ((*p) == 0xE0 \
    ? \
    (p)[1] < 0xA0 || ((p)[1] & 0xC0) == 0xC0 \
    : \
    ((p)[1] & 0x80) == 0 \
    || \
    ((*p) == 0xED ? (p)[1] > 0x9F : ((p)[1] & 0xC0) == 0xC0)))

#define UTF8_INVALID4(p) \
  (((p)[3] & 0x80) == 0 || ((p)[3] & 0xC0) == 0xC0 \
  || \
  ((p)[2] & 0x80) == 0 || ((p)[2] & 0xC0) == 0xC0 \
  || \
  ((*p) == 0xF0 \
    ? \
    (p)[1] < 0x90 || ((p)[1] & 0xC0) == 0xC0 \
    : \
    ((p)[1] & 0x80) == 0 \
    || \
    ((*p) == 0xF4 ? (p)[1] > 0x8F : ((p)[1] & 0xC0) == 0xC0)))

// @ 0x0090c8f0
int PTRFASTCALL
utf8_isName2(const ENCODING *enc, const char *p)
{
  return UTF8_GET_NAMING2(namePages, (const unsigned char *)p);
}

// @ 0x0090c930
int PTRFASTCALL
utf8_isName3(const ENCODING *enc, const char *p)
{
  return UTF8_GET_NAMING3(namePages, (const unsigned char *)p);
}

// @ 0x0090c980
int PTRFASTCALL
utf8_isNmstrt2(const ENCODING *enc, const char *p)
{
  return UTF8_GET_NAMING2(nmstrtPages, (const unsigned char *)p);
}

// @ 0x0090c9c0
int PTRFASTCALL
utf8_isNmstrt3(const ENCODING *enc, const char *p)
{
  return UTF8_GET_NAMING3(nmstrtPages, (const unsigned char *)p);
}

// @ 0x0090ca10
int PTRFASTCALL
utf8_isInvalid2(const ENCODING *enc, const char *p)
{
  return UTF8_INVALID2((const unsigned char *)p);
}

// @ 0x0090ca30
int PTRFASTCALL
utf8_isInvalid3(const ENCODING *enc, const char *p)
{
  return UTF8_INVALID3((const unsigned char *)p);
}

// @ 0x0090cab0
int PTRFASTCALL
utf8_isInvalid4(const ENCODING *enc, const char *p)
{
  return UTF8_INVALID4((const unsigned char *)p);
}

// ============================================================================
// xmlrole.c: prolog state machine
// ============================================================================

// ---- xmlrole.h ----
enum {
  XML_ROLE_ERROR = -1,
  XML_ROLE_NONE = 0,
  XML_ROLE_XML_DECL,
  XML_ROLE_INSTANCE_START,
  XML_ROLE_DOCTYPE_NONE,
  XML_ROLE_DOCTYPE_NAME,
  XML_ROLE_DOCTYPE_SYSTEM_ID,
  XML_ROLE_DOCTYPE_PUBLIC_ID,
  XML_ROLE_DOCTYPE_INTERNAL_SUBSET,
  XML_ROLE_DOCTYPE_CLOSE,
  XML_ROLE_GENERAL_ENTITY_NAME,
  XML_ROLE_PARAM_ENTITY_NAME,
  XML_ROLE_ENTITY_NONE,
  XML_ROLE_ENTITY_VALUE,
  XML_ROLE_ENTITY_SYSTEM_ID,
  XML_ROLE_ENTITY_PUBLIC_ID,
  XML_ROLE_ENTITY_COMPLETE,
  XML_ROLE_ENTITY_NOTATION_NAME,
  XML_ROLE_NOTATION_NONE,
  XML_ROLE_NOTATION_NAME,
  XML_ROLE_NOTATION_SYSTEM_ID,
  XML_ROLE_NOTATION_NO_SYSTEM_ID,
  XML_ROLE_NOTATION_PUBLIC_ID,
  XML_ROLE_ATTRIBUTE_NAME,
  XML_ROLE_ATTRIBUTE_TYPE_CDATA,
  XML_ROLE_ATTRIBUTE_TYPE_ID,
  XML_ROLE_ATTRIBUTE_TYPE_IDREF,
  XML_ROLE_ATTRIBUTE_TYPE_IDREFS,
  XML_ROLE_ATTRIBUTE_TYPE_ENTITY,
  XML_ROLE_ATTRIBUTE_TYPE_ENTITIES,
  XML_ROLE_ATTRIBUTE_TYPE_NMTOKEN,
  XML_ROLE_ATTRIBUTE_TYPE_NMTOKENS,
  XML_ROLE_ATTRIBUTE_ENUM_VALUE,
  XML_ROLE_ATTRIBUTE_NOTATION_VALUE,
  XML_ROLE_ATTLIST_NONE,
  XML_ROLE_ATTLIST_ELEMENT_NAME,
  XML_ROLE_IMPLIED_ATTRIBUTE_VALUE,
  XML_ROLE_REQUIRED_ATTRIBUTE_VALUE,
  XML_ROLE_DEFAULT_ATTRIBUTE_VALUE,
  XML_ROLE_FIXED_ATTRIBUTE_VALUE,
  XML_ROLE_ELEMENT_NONE,
  XML_ROLE_ELEMENT_NAME,
  XML_ROLE_CONTENT_ANY,
  XML_ROLE_CONTENT_EMPTY,
  XML_ROLE_CONTENT_PCDATA,
  XML_ROLE_GROUP_OPEN,
  XML_ROLE_GROUP_CLOSE,
  XML_ROLE_GROUP_CLOSE_REP,
  XML_ROLE_GROUP_CLOSE_OPT,
  XML_ROLE_GROUP_CLOSE_PLUS,
  XML_ROLE_GROUP_CHOICE,
  XML_ROLE_GROUP_SEQUENCE,
  XML_ROLE_CONTENT_ELEMENT,
  XML_ROLE_CONTENT_ELEMENT_REP,
  XML_ROLE_CONTENT_ELEMENT_OPT,
  XML_ROLE_CONTENT_ELEMENT_PLUS,
  XML_ROLE_PI,
  XML_ROLE_COMMENT,
  XML_ROLE_TEXT_DECL,
  XML_ROLE_IGNORE_SECT,
  XML_ROLE_INNER_PARAM_ENTITY_REF,
  XML_ROLE_PARAM_ENTITY_REF
};

typedef struct prolog_state {
  int (PTRCALL *handler)(struct prolog_state *state,
                         int tok,
                         const char *ptr,
                         const char *end,
                         const ENCODING *enc);
  unsigned level;
  int role_none;
  unsigned includeLevel;
  int documentEntity;
  int inEntityValue;
} PROLOG_STATE;

#define MIN_BYTES_PER_CHAR(enc) ((enc)->minBytesPerChar)

#define XmlNameMatchesAscii(enc, ptr1, end1, ptr2) \
  (((enc)->nameMatchesAscii)(enc, ptr1, end1, ptr2))

// Remaining handlers of the same xmlrole.c translation unit, outside this slice.
int PTRCALL error(PROLOG_STATE *, int, const char *, const char *, const ENCODING *);     // 0x00e31100
int PTRCALL entity0(PROLOG_STATE *, int, const char *, const char *, const ENCODING *);   // 0x0090c0a0
int PTRCALL attlist0(PROLOG_STATE *, int, const char *, const char *, const ENCODING *);  // 0x0090c1f0
int PTRCALL element0(PROLOG_STATE *, int, const char *, const char *, const ENCODING *);  // 0x0090c1a0
int PTRCALL notation0(PROLOG_STATE *, int, const char *, const char *, const ENCODING *); // 0x0090bc90
int PTRCALL doctype0(PROLOG_STATE *, int, const char *, const char *, const ENCODING *);  // 0x0090c6b0
int PTRCALL doctype2(PROLOG_STATE *, int, const char *, const char *, const ENCODING *);  // 0x0090c570
int PTRCALL doctype3(PROLOG_STATE *, int, const char *, const char *, const ENCODING *);  // 0x0090c530
int PTRCALL doctype4(PROLOG_STATE *, int, const char *, const char *, const ENCODING *);  // 0x0090c480
int PTRCALL doctype5(PROLOG_STATE *, int, const char *, const char *, const ENCODING *);  // 0x0090aff0
int PTRCALL prolog0(PROLOG_STATE *, int, const char *, const char *, const ENCODING *);   // 0x0090c7d0
int PTRCALL prolog2(PROLOG_STATE *, int, const char *, const char *, const ENCODING *);   // 0x0090af70
int PTRCALL condSect0(PROLOG_STATE *, int, const char *, const char *, const ENCODING *); // 0x0090c3d0

// ---- xmlrole.c keyword names ----
#define KW_ENTITY   "ENTITY"
#define KW_ATTLIST  "ATTLIST"
#define KW_ELEMENT  "ELEMENT"
#define KW_NOTATION "NOTATION"
#define KW_DOCTYPE  "DOCTYPE"
#define KW_SYSTEM   "SYSTEM"
#define KW_PUBLIC   "PUBLIC"

static __forceinline int PTRCALL
common(PROLOG_STATE *state, int tok)
{
  if (!state->documentEntity && tok == XML_TOK_PARAM_ENTITY_REF)
    return XML_ROLE_INNER_PARAM_ENTITY_REF;
  state->handler = error;
  return XML_ROLE_ERROR;
}

// @ 0x0090c240
int PTRCALL
internalSubset(PROLOG_STATE *state,
               int tok,
               const char *ptr,
               const char *end,
               const ENCODING *enc)
{
  switch (tok) {
  case XML_TOK_DECL_OPEN:
    if (XmlNameMatchesAscii(enc,
                            ptr + 2 * MIN_BYTES_PER_CHAR(enc),
                            end,
                            KW_ENTITY)) {
      state->handler = entity0;
      return XML_ROLE_ENTITY_NONE;
    }
    if (XmlNameMatchesAscii(enc,
                            ptr + 2 * MIN_BYTES_PER_CHAR(enc),
                            end,
                            KW_ATTLIST)) {
      state->handler = attlist0;
      return XML_ROLE_ATTLIST_NONE;
    }
    if (XmlNameMatchesAscii(enc,
                            ptr + 2 * MIN_BYTES_PER_CHAR(enc),
                            end,
                            KW_ELEMENT)) {
      state->handler = element0;
      return XML_ROLE_ELEMENT_NONE;
    }
    if (XmlNameMatchesAscii(enc,
                            ptr + 2 * MIN_BYTES_PER_CHAR(enc),
                            end,
                            KW_NOTATION)) {
      state->handler = notation0;
      return XML_ROLE_NOTATION_NONE;
    }
    break;
  case XML_TOK_PI:
    return XML_ROLE_PI;
  case XML_TOK_COMMENT:
    return XML_ROLE_COMMENT;
  case XML_TOK_PARAM_ENTITY_REF:
    return XML_ROLE_PARAM_ENTITY_REF;
  case XML_TOK_CLOSE_BRACKET:
    state->handler = doctype5;
    return XML_ROLE_DOCTYPE_NONE;
  case XML_TOK_NONE:
    return XML_ROLE_NONE;
  }
  return common(state, tok);
}

// @ 0x0090c5b0
int PTRCALL
doctype1(PROLOG_STATE *state,
         int tok,
         const char *ptr,
         const char *end,
         const ENCODING *enc)
{
  switch (tok) {
  case XML_TOK_PROLOG_S:
    return XML_ROLE_DOCTYPE_NONE;
  case XML_TOK_OPEN_BRACKET:
    state->handler = internalSubset;
    return XML_ROLE_DOCTYPE_INTERNAL_SUBSET;
  case XML_TOK_DECL_CLOSE:
    state->handler = prolog2;
    return XML_ROLE_DOCTYPE_CLOSE;
  case XML_TOK_NAME:
    if (XmlNameMatchesAscii(enc, ptr, end, KW_SYSTEM)) {
      state->handler = doctype3;
      return XML_ROLE_DOCTYPE_NONE;
    }
    if (XmlNameMatchesAscii(enc, ptr, end, KW_PUBLIC)) {
      state->handler = doctype2;
      return XML_ROLE_DOCTYPE_NONE;
    }
    break;
  }
  return common(state, tok);
}

// @ 0x0090c700
int PTRCALL
prolog1(PROLOG_STATE *state,
        int tok,
        const char *ptr,
        const char *end,
        const ENCODING *enc)
{
  switch (tok) {
  case XML_TOK_PROLOG_S:
    return XML_ROLE_NONE;
  case XML_TOK_PI:
    return XML_ROLE_PI;
  case XML_TOK_COMMENT:
    return XML_ROLE_COMMENT;
  case XML_TOK_BOM:
    return XML_ROLE_NONE;
  case XML_TOK_DECL_OPEN:
    if (!XmlNameMatchesAscii(enc,
                             ptr + 2 * MIN_BYTES_PER_CHAR(enc),
                             end,
                             KW_DOCTYPE))
      break;
    state->handler = doctype0;
    return XML_ROLE_DOCTYPE_NONE;
  case XML_TOK_INSTANCE_START:
    state->handler = error;
    return XML_ROLE_INSTANCE_START;
  }
  return common(state, tok);
}

// @ 0x0090c4e0
int PTRCALL
externalSubset(PROLOG_STATE *state,
               int tok,
               const char *ptr,
               const char *end,
               const ENCODING *enc)
{
  state->handler = condSect0;
  if (tok == XML_TOK_XML_DECL)
    return XML_ROLE_TEXT_DECL;
  return condSect0(state, tok, ptr, end, enc);
}

// @ 0x0090c510
void
XmlPrologStateInitExternalEntity(PROLOG_STATE *state)
{
  state->handler = externalSubset;
  state->documentEntity = 0;
  state->includeLevel = 0;
}

// @ 0x0090c8d0
void
XmlPrologStateInit(PROLOG_STATE *state)
{
  state->handler = prolog0;
  state->documentEntity = 1;
  state->includeLevel = 0;
  state->inEntityValue = 0;
}

