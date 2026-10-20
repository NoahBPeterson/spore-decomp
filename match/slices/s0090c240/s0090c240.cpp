// Slice s0090c240: expat 2.0.1 xmlrole.c prolog state machine (internalSubset, doctype1,
// prolog1, externalSubset, XmlPrologStateInit/ExternalEntity), the xmltok.c UTF-8
// naming/validity helpers and the normal_ (single-byte) scanner statics used by the prolog
// tokenizer.  MIT license: Copyright (c) 1998-2000 Thai Open Source Software Center Ltd and
// Clark Cooper.
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
/* Copyright (c) 1998, 1999 Thai Open Source Software Center Ltd
   See the file COPYING for copying permission.
*/

/* This file is included! */
#ifdef XML_TOK_IMPL_C

#ifndef IS_INVALID_CHAR
#define IS_INVALID_CHAR(enc, ptr, n) (0)
#endif

#define INVALID_LEAD_CASE(n, ptr, nextTokPtr) \
    case BT_LEAD ## n: \
      if (end - ptr < n) \
        return XML_TOK_PARTIAL_CHAR; \
      if (IS_INVALID_CHAR(enc, ptr, n)) { \
        *(nextTokPtr) = (ptr); \
        return XML_TOK_INVALID; \
      } \
      ptr += n; \
      break;

#define INVALID_CASES(ptr, nextTokPtr) \
  INVALID_LEAD_CASE(2, ptr, nextTokPtr) \
  INVALID_LEAD_CASE(3, ptr, nextTokPtr) \
  INVALID_LEAD_CASE(4, ptr, nextTokPtr) \
  case BT_NONXML: \
  case BT_MALFORM: \
  case BT_TRAIL: \
    *(nextTokPtr) = (ptr); \
    return XML_TOK_INVALID;

#define CHECK_NAME_CASE(n, enc, ptr, end, nextTokPtr) \
   case BT_LEAD ## n: \
     if (end - ptr < n) \
       return XML_TOK_PARTIAL_CHAR; \
     if (!IS_NAME_CHAR(enc, ptr, n)) { \
       *nextTokPtr = ptr; \
       return XML_TOK_INVALID; \
     } \
     ptr += n; \
     break;

#define CHECK_NAME_CASES(enc, ptr, end, nextTokPtr) \
  case BT_NONASCII: \
    if (!IS_NAME_CHAR_MINBPC(enc, ptr)) { \
      *nextTokPtr = ptr; \
      return XML_TOK_INVALID; \
    } \
  case BT_NMSTRT: \
  case BT_HEX: \
  case BT_DIGIT: \
  case BT_NAME: \
  case BT_MINUS: \
    ptr += MINBPC(enc); \
    break; \
  CHECK_NAME_CASE(2, enc, ptr, end, nextTokPtr) \
  CHECK_NAME_CASE(3, enc, ptr, end, nextTokPtr) \
  CHECK_NAME_CASE(4, enc, ptr, end, nextTokPtr)

#define CHECK_NMSTRT_CASE(n, enc, ptr, end, nextTokPtr) \
   case BT_LEAD ## n: \
     if (end - ptr < n) \
       return XML_TOK_PARTIAL_CHAR; \
     if (!IS_NMSTRT_CHAR(enc, ptr, n)) { \
       *nextTokPtr = ptr; \
       return XML_TOK_INVALID; \
     } \
     ptr += n; \
     break;

#define CHECK_NMSTRT_CASES(enc, ptr, end, nextTokPtr) \
  case BT_NONASCII: \
    if (!IS_NMSTRT_CHAR_MINBPC(enc, ptr)) { \
      *nextTokPtr = ptr; \
      return XML_TOK_INVALID; \
    } \
  case BT_NMSTRT: \
  case BT_HEX: \
    ptr += MINBPC(enc); \
    break; \
  CHECK_NMSTRT_CASE(2, enc, ptr, end, nextTokPtr) \
  CHECK_NMSTRT_CASE(3, enc, ptr, end, nextTokPtr) \
  CHECK_NMSTRT_CASE(4, enc, ptr, end, nextTokPtr)

#ifndef PREFIX
#define PREFIX(ident) ident
#endif

/* ptr points to character following "<!-" */

// @ 0x0090cb20
__declspec(noinline) int PTRCALL
PREFIX(scanComment)(const ENCODING *enc, const char *ptr,
                    const char *end, const char **nextTokPtr)
{
  if (ptr != end) {
    if (!CHAR_MATCHES(enc, ptr, ASCII_MINUS)) {
      *nextTokPtr = ptr;
      return XML_TOK_INVALID;
    }
    ptr += MINBPC(enc);
    while (ptr != end) {
      switch (BYTE_TYPE(enc, ptr)) {
      INVALID_CASES(ptr, nextTokPtr)
      case BT_MINUS:
        if ((ptr += MINBPC(enc)) == end)
          return XML_TOK_PARTIAL;
        if (CHAR_MATCHES(enc, ptr, ASCII_MINUS)) {
          if ((ptr += MINBPC(enc)) == end)
            return XML_TOK_PARTIAL;
          if (!CHAR_MATCHES(enc, ptr, ASCII_GT)) {
            *nextTokPtr = ptr;
            return XML_TOK_INVALID;
          }
          *nextTokPtr = ptr + MINBPC(enc);
          return XML_TOK_COMMENT;
        }
        break;
      default:
        ptr += MINBPC(enc);
        break;
      }
    }
  }
  return XML_TOK_PARTIAL;
}

/* ptr points to character following "<!" */

// @ 0x0090cc60
__declspec(noinline) int PTRCALL
PREFIX(scanDecl)(const ENCODING *enc, const char *ptr,
                 const char *end, const char **nextTokPtr)
{
  if (ptr == end)
    return XML_TOK_PARTIAL;
  switch (BYTE_TYPE(enc, ptr)) {
  case BT_MINUS:
    return PREFIX(scanComment)(enc, ptr + MINBPC(enc), end, nextTokPtr);
  case BT_LSQB:
    *nextTokPtr = ptr + MINBPC(enc);
    return XML_TOK_COND_SECT_OPEN;
  case BT_NMSTRT:
  case BT_HEX:
    ptr += MINBPC(enc);
    break;
  default:
    *nextTokPtr = ptr;
    return XML_TOK_INVALID;
  }
  while (ptr != end) {
    switch (BYTE_TYPE(enc, ptr)) {
    case BT_PERCNT:
      if (ptr + MINBPC(enc) == end)
        return XML_TOK_PARTIAL;
      /* don't allow <!ENTITY% foo "whatever"> */
      switch (BYTE_TYPE(enc, ptr + MINBPC(enc))) {
      case BT_S: case BT_CR: case BT_LF: case BT_PERCNT:
        *nextTokPtr = ptr;
        return XML_TOK_INVALID;
      }
      /* fall through */
    case BT_S: case BT_CR: case BT_LF:
      *nextTokPtr = ptr;
      return XML_TOK_DECL_OPEN;
    case BT_NMSTRT:
    case BT_HEX:
      ptr += MINBPC(enc);
      break;
    default:
      *nextTokPtr = ptr;
      return XML_TOK_INVALID;
    }
  }
  return XML_TOK_PARTIAL;
}

// @ 0x0090cd70
__declspec(noinline) int PTRCALL
PREFIX(checkPiTarget)(const ENCODING *enc, const char *ptr,
                      const char *end, int *tokPtr)
{
  int upper = 0;
  *tokPtr = XML_TOK_PI;
  if (end - ptr != MINBPC(enc)*3)
    return 1;
  switch (BYTE_TO_ASCII(enc, ptr)) {
  case ASCII_x:
    break;
  case ASCII_X:
    upper = 1;
    break;
  default:
    return 1;
  }
  ptr += MINBPC(enc);
  switch (BYTE_TO_ASCII(enc, ptr)) {
  case ASCII_m:
    break;
  case ASCII_M:
    upper = 1;
    break;
  default:
    return 1;
  }
  ptr += MINBPC(enc);
  switch (BYTE_TO_ASCII(enc, ptr)) {
  case ASCII_l:
    break;
  case ASCII_L:
    upper = 1;
    break;
  default:
    return 1;
  }
  if (upper)
    return 0;
  *tokPtr = XML_TOK_XML_DECL;
  return 1;
}

/* ptr points to character following "<?" */

static int PTRCALL
PREFIX(scanPi)(const ENCODING *enc, const char *ptr,
               const char *end, const char **nextTokPtr)
{
  int tok;
  const char *target = ptr;
  if (ptr == end)
    return XML_TOK_PARTIAL;
  switch (BYTE_TYPE(enc, ptr)) {
  CHECK_NMSTRT_CASES(enc, ptr, end, nextTokPtr)
  default:
    *nextTokPtr = ptr;
    return XML_TOK_INVALID;
  }
  while (ptr != end) {
    switch (BYTE_TYPE(enc, ptr)) {
    CHECK_NAME_CASES(enc, ptr, end, nextTokPtr)
    case BT_S: case BT_CR: case BT_LF:
      if (!PREFIX(checkPiTarget)(enc, target, ptr, &tok)) {
        *nextTokPtr = ptr;
        return XML_TOK_INVALID;
      }
      ptr += MINBPC(enc);
      while (ptr != end) {
        switch (BYTE_TYPE(enc, ptr)) {
        INVALID_CASES(ptr, nextTokPtr)
        case BT_QUEST:
          ptr += MINBPC(enc);
          if (ptr == end)
            return XML_TOK_PARTIAL;
          if (CHAR_MATCHES(enc, ptr, ASCII_GT)) {
            *nextTokPtr = ptr + MINBPC(enc);
            return tok;
          }
          break;
        default:
          ptr += MINBPC(enc);
          break;
        }
      }
      return XML_TOK_PARTIAL;
    case BT_QUEST:
      if (!PREFIX(checkPiTarget)(enc, target, ptr, &tok)) {
        *nextTokPtr = ptr;
        return XML_TOK_INVALID;
      }
      ptr += MINBPC(enc);
      if (ptr == end)
        return XML_TOK_PARTIAL;
      if (CHAR_MATCHES(enc, ptr, ASCII_GT)) {
        *nextTokPtr = ptr + MINBPC(enc);
        return tok;
      }
      /* fall through */
    default:
      *nextTokPtr = ptr;
      return XML_TOK_INVALID;
    }
  }
  return XML_TOK_PARTIAL;
}

static int PTRCALL
PREFIX(scanCdataSection)(const ENCODING *enc, const char *ptr,
                         const char *end, const char **nextTokPtr)
{
  static const char CDATA_LSQB[] = { ASCII_C, ASCII_D, ASCII_A,
                                     ASCII_T, ASCII_A, ASCII_LSQB };
  int i;
  /* CDATA[ */
  if (end - ptr < 6 * MINBPC(enc))
    return XML_TOK_PARTIAL;
  for (i = 0; i < 6; i++, ptr += MINBPC(enc)) {
    if (!CHAR_MATCHES(enc, ptr, CDATA_LSQB[i])) {
      *nextTokPtr = ptr;
      return XML_TOK_INVALID;
    }
  }
  *nextTokPtr = ptr;
  return XML_TOK_CDATA_SECT_OPEN;
}

static int PTRCALL
PREFIX(cdataSectionTok)(const ENCODING *enc, const char *ptr,
                        const char *end, const char **nextTokPtr)
{
  if (ptr == end)
    return XML_TOK_NONE;
  if (MINBPC(enc) > 1) {
    size_t n = end - ptr;
    if (n & (MINBPC(enc) - 1)) {
      n &= ~(MINBPC(enc) - 1);
      if (n == 0)
        return XML_TOK_PARTIAL;
      end = ptr + n;
    }
  }
  switch (BYTE_TYPE(enc, ptr)) {
  case BT_RSQB:
    ptr += MINBPC(enc);
    if (ptr == end)
      return XML_TOK_PARTIAL;
    if (!CHAR_MATCHES(enc, ptr, ASCII_RSQB))
      break;
    ptr += MINBPC(enc);
    if (ptr == end)
      return XML_TOK_PARTIAL;
    if (!CHAR_MATCHES(enc, ptr, ASCII_GT)) {
      ptr -= MINBPC(enc);
      break;
    }
    *nextTokPtr = ptr + MINBPC(enc);
    return XML_TOK_CDATA_SECT_CLOSE;
  case BT_CR:
    ptr += MINBPC(enc);
    if (ptr == end)
      return XML_TOK_PARTIAL;
    if (BYTE_TYPE(enc, ptr) == BT_LF)
      ptr += MINBPC(enc);
    *nextTokPtr = ptr;
    return XML_TOK_DATA_NEWLINE;
  case BT_LF:
    *nextTokPtr = ptr + MINBPC(enc);
    return XML_TOK_DATA_NEWLINE;
  INVALID_CASES(ptr, nextTokPtr)
  default:
    ptr += MINBPC(enc);
    break;
  }
  while (ptr != end) {
    switch (BYTE_TYPE(enc, ptr)) {
#define LEAD_CASE(n) \
    case BT_LEAD ## n: \
      if (end - ptr < n || IS_INVALID_CHAR(enc, ptr, n)) { \
        *nextTokPtr = ptr; \
        return XML_TOK_DATA_CHARS; \
      } \
      ptr += n; \
      break;
    LEAD_CASE(2) LEAD_CASE(3) LEAD_CASE(4)
#undef LEAD_CASE
    case BT_NONXML:
    case BT_MALFORM:
    case BT_TRAIL:
    case BT_CR:
    case BT_LF:
    case BT_RSQB:
      *nextTokPtr = ptr;
      return XML_TOK_DATA_CHARS;
    default:
      ptr += MINBPC(enc);
      break;
    }
  }
  *nextTokPtr = ptr;
  return XML_TOK_DATA_CHARS;
}

/* ptr points to character following "</" */

static int PTRCALL
PREFIX(scanEndTag)(const ENCODING *enc, const char *ptr,
                   const char *end, const char **nextTokPtr)
{
  if (ptr == end)
    return XML_TOK_PARTIAL;
  switch (BYTE_TYPE(enc, ptr)) {
  CHECK_NMSTRT_CASES(enc, ptr, end, nextTokPtr)
  default:
    *nextTokPtr = ptr;
    return XML_TOK_INVALID;
  }
  while (ptr != end) {
    switch (BYTE_TYPE(enc, ptr)) {
    CHECK_NAME_CASES(enc, ptr, end, nextTokPtr)
    case BT_S: case BT_CR: case BT_LF:
      for (ptr += MINBPC(enc); ptr != end; ptr += MINBPC(enc)) {
        switch (BYTE_TYPE(enc, ptr)) {
        case BT_S: case BT_CR: case BT_LF:
          break;
        case BT_GT:
          *nextTokPtr = ptr + MINBPC(enc);
          return XML_TOK_END_TAG;
        default:
          *nextTokPtr = ptr;
          return XML_TOK_INVALID;
        }
      }
      return XML_TOK_PARTIAL;
#ifdef XML_NS
    case BT_COLON:
      /* no need to check qname syntax here,
         since end-tag must match exactly */
      ptr += MINBPC(enc);
      break;
#endif
    case BT_GT:
      *nextTokPtr = ptr + MINBPC(enc);
      return XML_TOK_END_TAG;
    default:
      *nextTokPtr = ptr;
      return XML_TOK_INVALID;
    }
  }
  return XML_TOK_PARTIAL;
}

/* ptr points to character following "&#X" */

static int PTRCALL
PREFIX(scanHexCharRef)(const ENCODING *enc, const char *ptr,
                       const char *end, const char **nextTokPtr)
{
  if (ptr != end) {
    switch (BYTE_TYPE(enc, ptr)) {
    case BT_DIGIT:
    case BT_HEX:
      break;
    default:
      *nextTokPtr = ptr;
      return XML_TOK_INVALID;
    }
    for (ptr += MINBPC(enc); ptr != end; ptr += MINBPC(enc)) {
      switch (BYTE_TYPE(enc, ptr)) {
      case BT_DIGIT:
      case BT_HEX:
        break;
      case BT_SEMI:
        *nextTokPtr = ptr + MINBPC(enc);
        return XML_TOK_CHAR_REF;
      default:
        *nextTokPtr = ptr;
        return XML_TOK_INVALID;
      }
    }
  }
  return XML_TOK_PARTIAL;
}

/* ptr points to character following "&#" */

static int PTRCALL
PREFIX(scanCharRef)(const ENCODING *enc, const char *ptr,
                    const char *end, const char **nextTokPtr)
{
  if (ptr != end) {
    if (CHAR_MATCHES(enc, ptr, ASCII_x))
      return PREFIX(scanHexCharRef)(enc, ptr + MINBPC(enc), end, nextTokPtr);
    switch (BYTE_TYPE(enc, ptr)) {
    case BT_DIGIT:
      break;
    default:
      *nextTokPtr = ptr;
      return XML_TOK_INVALID;
    }
    for (ptr += MINBPC(enc); ptr != end; ptr += MINBPC(enc)) {
      switch (BYTE_TYPE(enc, ptr)) {
      case BT_DIGIT:
        break;
      case BT_SEMI:
        *nextTokPtr = ptr + MINBPC(enc);
        return XML_TOK_CHAR_REF;
      default:
        *nextTokPtr = ptr;
        return XML_TOK_INVALID;
      }
    }
  }
  return XML_TOK_PARTIAL;
}

/* ptr points to character following "&" */

__declspec(noinline) static int PTRCALL
PREFIX(scanRef)(const ENCODING *enc, const char *ptr, const char *end,
                const char **nextTokPtr)
{
  if (ptr == end)
    return XML_TOK_PARTIAL;
  switch (BYTE_TYPE(enc, ptr)) {
  CHECK_NMSTRT_CASES(enc, ptr, end, nextTokPtr)
  case BT_NUM:
    return PREFIX(scanCharRef)(enc, ptr + MINBPC(enc), end, nextTokPtr);
  default:
    *nextTokPtr = ptr;
    return XML_TOK_INVALID;
  }
  while (ptr != end) {
    switch (BYTE_TYPE(enc, ptr)) {
    CHECK_NAME_CASES(enc, ptr, end, nextTokPtr)
    case BT_SEMI:
      *nextTokPtr = ptr + MINBPC(enc);
      return XML_TOK_ENTITY_REF;
    default:
      *nextTokPtr = ptr;
      return XML_TOK_INVALID;
    }
  }
  return XML_TOK_PARTIAL;
}

/* ptr points to character following first character of attribute name */

// @ 0x0090cdd0
__declspec(noinline) int PTRCALL
PREFIX(scanAtts)(const ENCODING *enc, const char *ptr, const char *end,
                 const char **nextTokPtr)
{
#ifdef XML_NS
  int hadColon = 0;
#endif
  while (ptr != end) {
    switch (BYTE_TYPE(enc, ptr)) {
    CHECK_NAME_CASES(enc, ptr, end, nextTokPtr)
#ifdef XML_NS
    case BT_COLON:
      if (hadColon) {
        *nextTokPtr = ptr;
        return XML_TOK_INVALID;
      }
      hadColon = 1;
      ptr += MINBPC(enc);
      if (ptr == end)
        return XML_TOK_PARTIAL;
      switch (BYTE_TYPE(enc, ptr)) {
      CHECK_NMSTRT_CASES(enc, ptr, end, nextTokPtr)
      default:
        *nextTokPtr = ptr;
        return XML_TOK_INVALID;
      }
      break;
#endif
    case BT_S: case BT_CR: case BT_LF:
      for (;;) {
        int t;

        ptr += MINBPC(enc);
        if (ptr == end)
          return XML_TOK_PARTIAL;
        t = BYTE_TYPE(enc, ptr);
        if (t == BT_EQUALS)
          break;
        switch (t) {
        case BT_S:
        case BT_LF:
        case BT_CR:
          break;
        default:
          *nextTokPtr = ptr;
          return XML_TOK_INVALID;
        }
      }
    /* fall through */
    case BT_EQUALS:
      {
        int open;
#ifdef XML_NS
        hadColon = 0;
#endif
        for (;;) {
          ptr += MINBPC(enc);
          if (ptr == end)
            return XML_TOK_PARTIAL;
          open = BYTE_TYPE(enc, ptr);
          if (open == BT_QUOT || open == BT_APOS)
            break;
          switch (open) {
          case BT_S:
          case BT_LF:
          case BT_CR:
            break;
          default:
            *nextTokPtr = ptr;
            return XML_TOK_INVALID;
          }
        }
        ptr += MINBPC(enc);
        /* in attribute value */
        for (;;) {
          int t;
          if (ptr == end)
            return XML_TOK_PARTIAL;
          t = BYTE_TYPE(enc, ptr);
          if (t == open)
            break;
          switch (t) {
          INVALID_CASES(ptr, nextTokPtr)
          case BT_AMP:
            {
              int tok = PREFIX(scanRef)(enc, ptr + MINBPC(enc), end, &ptr);
              if (tok <= 0) {
                if (tok == XML_TOK_INVALID)
                  *nextTokPtr = ptr;
                return tok;
              }
              break;
            }
          case BT_LT:
            *nextTokPtr = ptr;
            return XML_TOK_INVALID;
          default:
            ptr += MINBPC(enc);
            break;
          }
        }
        ptr += MINBPC(enc);
        if (ptr == end)
          return XML_TOK_PARTIAL;
        switch (BYTE_TYPE(enc, ptr)) {
        case BT_S:
        case BT_CR:
        case BT_LF:
          break;
        case BT_SOL:
          goto sol;
        case BT_GT:
          goto gt;
        default:
          *nextTokPtr = ptr;
          return XML_TOK_INVALID;
        }
        /* ptr points to closing quote */
        for (;;) {
          ptr += MINBPC(enc);
          if (ptr == end)
            return XML_TOK_PARTIAL;
          switch (BYTE_TYPE(enc, ptr)) {
          CHECK_NMSTRT_CASES(enc, ptr, end, nextTokPtr)
          case BT_S: case BT_CR: case BT_LF:
            continue;
          case BT_GT:
          gt:
            *nextTokPtr = ptr + MINBPC(enc);
            return XML_TOK_START_TAG_WITH_ATTS;
          case BT_SOL:
          sol:
            ptr += MINBPC(enc);
            if (ptr == end)
              return XML_TOK_PARTIAL;
            if (!CHAR_MATCHES(enc, ptr, ASCII_GT)) {
              *nextTokPtr = ptr;
              return XML_TOK_INVALID;
            }
            *nextTokPtr = ptr + MINBPC(enc);
            return XML_TOK_EMPTY_ELEMENT_WITH_ATTS;
          default:
            *nextTokPtr = ptr;
            return XML_TOK_INVALID;
          }
          break;
        }
        break;
      }
    default:
      *nextTokPtr = ptr;
      return XML_TOK_INVALID;
    }
  }
  return XML_TOK_PARTIAL;
}

/* ptr points to character following "<" */

static int PTRCALL
PREFIX(scanLt)(const ENCODING *enc, const char *ptr, const char *end,
               const char **nextTokPtr)
{
#ifdef XML_NS
  int hadColon;
#endif
  if (ptr == end)
    return XML_TOK_PARTIAL;
  switch (BYTE_TYPE(enc, ptr)) {
  CHECK_NMSTRT_CASES(enc, ptr, end, nextTokPtr)
  case BT_EXCL:
    if ((ptr += MINBPC(enc)) == end)
      return XML_TOK_PARTIAL;
    switch (BYTE_TYPE(enc, ptr)) {
    case BT_MINUS:
      return PREFIX(scanComment)(enc, ptr + MINBPC(enc), end, nextTokPtr);
    case BT_LSQB:
      return PREFIX(scanCdataSection)(enc, ptr + MINBPC(enc),
                                      end, nextTokPtr);
    }
    *nextTokPtr = ptr;
    return XML_TOK_INVALID;
  case BT_QUEST:
    return PREFIX(scanPi)(enc, ptr + MINBPC(enc), end, nextTokPtr);
  case BT_SOL:
    return PREFIX(scanEndTag)(enc, ptr + MINBPC(enc), end, nextTokPtr);
  default:
    *nextTokPtr = ptr;
    return XML_TOK_INVALID;
  }
#ifdef XML_NS
  hadColon = 0;
#endif
  /* we have a start-tag */
  while (ptr != end) {
    switch (BYTE_TYPE(enc, ptr)) {
    CHECK_NAME_CASES(enc, ptr, end, nextTokPtr)
#ifdef XML_NS
    case BT_COLON:
      if (hadColon) {
        *nextTokPtr = ptr;
        return XML_TOK_INVALID;
      }
      hadColon = 1;
      ptr += MINBPC(enc);
      if (ptr == end)
        return XML_TOK_PARTIAL;
      switch (BYTE_TYPE(enc, ptr)) {
      CHECK_NMSTRT_CASES(enc, ptr, end, nextTokPtr)
      default:
        *nextTokPtr = ptr;
        return XML_TOK_INVALID;
      }
      break;
#endif
    case BT_S: case BT_CR: case BT_LF:
      {
        ptr += MINBPC(enc);
        while (ptr != end) {
          switch (BYTE_TYPE(enc, ptr)) {
          CHECK_NMSTRT_CASES(enc, ptr, end, nextTokPtr)
          case BT_GT:
            goto gt;
          case BT_SOL:
            goto sol;
          case BT_S: case BT_CR: case BT_LF:
            ptr += MINBPC(enc);
            continue;
          default:
            *nextTokPtr = ptr;
            return XML_TOK_INVALID;
          }
          return PREFIX(scanAtts)(enc, ptr, end, nextTokPtr);
        }
        return XML_TOK_PARTIAL;
      }
    case BT_GT:
    gt:
      *nextTokPtr = ptr + MINBPC(enc);
      return XML_TOK_START_TAG_NO_ATTS;
    case BT_SOL:
    sol:
      ptr += MINBPC(enc);
      if (ptr == end)
        return XML_TOK_PARTIAL;
      if (!CHAR_MATCHES(enc, ptr, ASCII_GT)) {
        *nextTokPtr = ptr;
        return XML_TOK_INVALID;
      }
      *nextTokPtr = ptr + MINBPC(enc);
      return XML_TOK_EMPTY_ELEMENT_NO_ATTS;
    default:
      *nextTokPtr = ptr;
      return XML_TOK_INVALID;
    }
  }
  return XML_TOK_PARTIAL;
}

static int PTRCALL
PREFIX(contentTok)(const ENCODING *enc, const char *ptr, const char *end,
                   const char **nextTokPtr)
{
  if (ptr == end)
    return XML_TOK_NONE;
  if (MINBPC(enc) > 1) {
    size_t n = end - ptr;
    if (n & (MINBPC(enc) - 1)) {
      n &= ~(MINBPC(enc) - 1);
      if (n == 0)
        return XML_TOK_PARTIAL;
      end = ptr + n;
    }
  }
  switch (BYTE_TYPE(enc, ptr)) {
  case BT_LT:
    return PREFIX(scanLt)(enc, ptr + MINBPC(enc), end, nextTokPtr);
  case BT_AMP:
    return PREFIX(scanRef)(enc, ptr + MINBPC(enc), end, nextTokPtr);
  case BT_CR:
    ptr += MINBPC(enc);
    if (ptr == end)
      return XML_TOK_TRAILING_CR;
    if (BYTE_TYPE(enc, ptr) == BT_LF)
      ptr += MINBPC(enc);
    *nextTokPtr = ptr;
    return XML_TOK_DATA_NEWLINE;
  case BT_LF:
    *nextTokPtr = ptr + MINBPC(enc);
    return XML_TOK_DATA_NEWLINE;
  case BT_RSQB:
    ptr += MINBPC(enc);
    if (ptr == end)
      return XML_TOK_TRAILING_RSQB;
    if (!CHAR_MATCHES(enc, ptr, ASCII_RSQB))
      break;
    ptr += MINBPC(enc);
    if (ptr == end)
      return XML_TOK_TRAILING_RSQB;
    if (!CHAR_MATCHES(enc, ptr, ASCII_GT)) {
      ptr -= MINBPC(enc);
      break;
    }
    *nextTokPtr = ptr;
    return XML_TOK_INVALID;
  INVALID_CASES(ptr, nextTokPtr)
  default:
    ptr += MINBPC(enc);
    break;
  }
  while (ptr != end) {
    switch (BYTE_TYPE(enc, ptr)) {
#define LEAD_CASE(n) \
    case BT_LEAD ## n: \
      if (end - ptr < n || IS_INVALID_CHAR(enc, ptr, n)) { \
        *nextTokPtr = ptr; \
        return XML_TOK_DATA_CHARS; \
      } \
      ptr += n; \
      break;
    LEAD_CASE(2) LEAD_CASE(3) LEAD_CASE(4)
#undef LEAD_CASE
    case BT_RSQB:
      if (ptr + MINBPC(enc) != end) {
         if (!CHAR_MATCHES(enc, ptr + MINBPC(enc), ASCII_RSQB)) {
           ptr += MINBPC(enc);
           break;
         }
         if (ptr + 2*MINBPC(enc) != end) {
           if (!CHAR_MATCHES(enc, ptr + 2*MINBPC(enc), ASCII_GT)) {
             ptr += MINBPC(enc);
             break;
           }
           *nextTokPtr = ptr + 2*MINBPC(enc);
           return XML_TOK_INVALID;
         }
      }
      /* fall through */
    case BT_AMP:
    case BT_LT:
    case BT_NONXML:
    case BT_MALFORM:
    case BT_TRAIL:
    case BT_CR:
    case BT_LF:
      *nextTokPtr = ptr;
      return XML_TOK_DATA_CHARS;
    default:
      ptr += MINBPC(enc);
      break;
    }
  }
  *nextTokPtr = ptr;
  return XML_TOK_DATA_CHARS;
}

/* ptr points to character following "%" */

static int PTRCALL
PREFIX(scanPercent)(const ENCODING *enc, const char *ptr, const char *end,
                    const char **nextTokPtr)
{
  if (ptr == end)
    return -XML_TOK_PERCENT;
  switch (BYTE_TYPE(enc, ptr)) {
  CHECK_NMSTRT_CASES(enc, ptr, end, nextTokPtr)
  case BT_S: case BT_LF: case BT_CR: case BT_PERCNT:
    *nextTokPtr = ptr;
    return XML_TOK_PERCENT;
  default:
    *nextTokPtr = ptr;
    return XML_TOK_INVALID;
  }
  while (ptr != end) {
    switch (BYTE_TYPE(enc, ptr)) {
    CHECK_NAME_CASES(enc, ptr, end, nextTokPtr)
    case BT_SEMI:
      *nextTokPtr = ptr + MINBPC(enc);
      return XML_TOK_PARAM_ENTITY_REF;
    default:
      *nextTokPtr = ptr;
      return XML_TOK_INVALID;
    }
  }
  return XML_TOK_PARTIAL;
}

static int PTRCALL
PREFIX(scanPoundName)(const ENCODING *enc, const char *ptr, const char *end,
                      const char **nextTokPtr)
{
  if (ptr == end)
    return XML_TOK_PARTIAL;
  switch (BYTE_TYPE(enc, ptr)) {
  CHECK_NMSTRT_CASES(enc, ptr, end, nextTokPtr)
  default:
    *nextTokPtr = ptr;
    return XML_TOK_INVALID;
  }
  while (ptr != end) {
    switch (BYTE_TYPE(enc, ptr)) {
    CHECK_NAME_CASES(enc, ptr, end, nextTokPtr)
    case BT_CR: case BT_LF: case BT_S:
    case BT_RPAR: case BT_GT: case BT_PERCNT: case BT_VERBAR:
      *nextTokPtr = ptr;
      return XML_TOK_POUND_NAME;
    default:
      *nextTokPtr = ptr;
      return XML_TOK_INVALID;
    }
  }
  return -XML_TOK_POUND_NAME;
}

static int PTRCALL
PREFIX(scanLit)(int open, const ENCODING *enc,
                const char *ptr, const char *end,
                const char **nextTokPtr)
{
  while (ptr != end) {
    int t = BYTE_TYPE(enc, ptr);
    switch (t) {
    INVALID_CASES(ptr, nextTokPtr)
    case BT_QUOT:
    case BT_APOS:
      ptr += MINBPC(enc);
      if (t != open)
        break;
      if (ptr == end)
        return -XML_TOK_LITERAL;
      *nextTokPtr = ptr;
      switch (BYTE_TYPE(enc, ptr)) {
      case BT_S: case BT_CR: case BT_LF:
      case BT_GT: case BT_PERCNT: case BT_LSQB:
        return XML_TOK_LITERAL;
      default:
        return XML_TOK_INVALID;
      }
    default:
      ptr += MINBPC(enc);
      break;
    }
  }
  return XML_TOK_PARTIAL;
}

// ============================================================================
// xmltok.c: UTF-8 naming/validity helpers (address-taken by the utf8 encoding)
// ============================================================================

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

#endif /* XML_TOK_IMPL_C */
