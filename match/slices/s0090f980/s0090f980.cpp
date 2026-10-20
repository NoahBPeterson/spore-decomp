// Slice s0090f980: expat 2.0.1 xmltok.c / xmltok_impl.c, as linked into SporeApp.exe
// (UTFSpore_Win32/xmltok.obj) -- the normal_ single-byte scanners' skipS/updatePosition, the
// UTF-8/Latin-1/ASCII and little2/big2 encoding converters from xmltok.c, and the little2
// comment/decl/PI/CDATA scanners.  MIT license: Copyright (c) 1998-2000 Thai Open Source
// Software Center Ltd and Clark Cooper.
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

// @ 0x00910290
static int PTRCALL
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

// @ 0x009103a0
static int PTRCALL
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

// @ 0x009104f0
static int PTRCALL
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

// @ 0x00910570
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

// @ 0x00910890
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

static int PTRCALL
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

static int PTRCALL
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

// 0x00911880 little2_contentTok (root from a neighbouring slice; kept so scanLt ->
// scanCdataSection stay emitted -- the encoding vtable that reaches it in the original
// is not part of this file)
int PTRCALL
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

// 0x00911f60 little2_prologTok (root from slice s00911f60; kept for reachability)
int PTRCALL
PREFIX(prologTok)(const ENCODING *enc, const char *ptr, const char *end,
                  const char **nextTokPtr)
{
  int tok;
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
  case BT_QUOT:
    return PREFIX(scanLit)(BT_QUOT, enc, ptr + MINBPC(enc), end, nextTokPtr);
  case BT_APOS:
    return PREFIX(scanLit)(BT_APOS, enc, ptr + MINBPC(enc), end, nextTokPtr);
  case BT_LT:
    {
      ptr += MINBPC(enc);
      if (ptr == end)
        return XML_TOK_PARTIAL;
      switch (BYTE_TYPE(enc, ptr)) {
      case BT_EXCL:
        return PREFIX(scanDecl)(enc, ptr + MINBPC(enc), end, nextTokPtr);
      case BT_QUEST:
        return PREFIX(scanPi)(enc, ptr + MINBPC(enc), end, nextTokPtr);
      case BT_NMSTRT:
      case BT_HEX:
      case BT_NONASCII:
      case BT_LEAD2:
      case BT_LEAD3:
      case BT_LEAD4:
        *nextTokPtr = ptr - MINBPC(enc);
        return XML_TOK_INSTANCE_START;
      }
      *nextTokPtr = ptr;
      return XML_TOK_INVALID;
    }
  case BT_CR:
    if (ptr + MINBPC(enc) == end) {
      *nextTokPtr = end;
      /* indicate that this might be part of a CR/LF pair */
      return -XML_TOK_PROLOG_S;
    }
    /* fall through */
  case BT_S: case BT_LF:
    for (;;) {
      ptr += MINBPC(enc);
      if (ptr == end)
        break;
      switch (BYTE_TYPE(enc, ptr)) {
      case BT_S: case BT_LF:
        break;
      case BT_CR:
        /* don't split CR/LF pair */
        if (ptr + MINBPC(enc) != end)
          break;
        /* fall through */
      default:
        *nextTokPtr = ptr;
        return XML_TOK_PROLOG_S;
      }
    }
    *nextTokPtr = ptr;
    return XML_TOK_PROLOG_S;
  case BT_PERCNT:
    return PREFIX(scanPercent)(enc, ptr + MINBPC(enc), end, nextTokPtr);
  case BT_COMMA:
    *nextTokPtr = ptr + MINBPC(enc);
    return XML_TOK_COMMA;
  case BT_LSQB:
    *nextTokPtr = ptr + MINBPC(enc);
    return XML_TOK_OPEN_BRACKET;
  case BT_RSQB:
    ptr += MINBPC(enc);
    if (ptr == end)
      return -XML_TOK_CLOSE_BRACKET;
    if (CHAR_MATCHES(enc, ptr, ASCII_RSQB)) {
      if (ptr + MINBPC(enc) == end)
        return XML_TOK_PARTIAL;
      if (CHAR_MATCHES(enc, ptr + MINBPC(enc), ASCII_GT)) {
        *nextTokPtr = ptr + 2*MINBPC(enc);
        return XML_TOK_COND_SECT_CLOSE;
      }
    }
    *nextTokPtr = ptr;
    return XML_TOK_CLOSE_BRACKET;
  case BT_LPAR:
    *nextTokPtr = ptr + MINBPC(enc);
    return XML_TOK_OPEN_PAREN;
  case BT_RPAR:
    ptr += MINBPC(enc);
    if (ptr == end)
      return -XML_TOK_CLOSE_PAREN;
    switch (BYTE_TYPE(enc, ptr)) {
    case BT_AST:
      *nextTokPtr = ptr + MINBPC(enc);
      return XML_TOK_CLOSE_PAREN_ASTERISK;
    case BT_QUEST:
      *nextTokPtr = ptr + MINBPC(enc);
      return XML_TOK_CLOSE_PAREN_QUESTION;
    case BT_PLUS:
      *nextTokPtr = ptr + MINBPC(enc);
      return XML_TOK_CLOSE_PAREN_PLUS;
    case BT_CR: case BT_LF: case BT_S:
    case BT_GT: case BT_COMMA: case BT_VERBAR:
    case BT_RPAR:
      *nextTokPtr = ptr;
      return XML_TOK_CLOSE_PAREN;
    }
    *nextTokPtr = ptr;
    return XML_TOK_INVALID;
  case BT_VERBAR:
    *nextTokPtr = ptr + MINBPC(enc);
    return XML_TOK_OR;
  case BT_GT:
    *nextTokPtr = ptr + MINBPC(enc);
    return XML_TOK_DECL_CLOSE;
  case BT_NUM:
    return PREFIX(scanPoundName)(enc, ptr + MINBPC(enc), end, nextTokPtr);
#define LEAD_CASE(n) \
  case BT_LEAD ## n: \
    if (end - ptr < n) \
      return XML_TOK_PARTIAL_CHAR; \
    if (IS_NMSTRT_CHAR(enc, ptr, n)) { \
      ptr += n; \
      tok = XML_TOK_NAME; \
      break; \
    } \
    if (IS_NAME_CHAR(enc, ptr, n)) { \
      ptr += n; \
      tok = XML_TOK_NMTOKEN; \
      break; \
    } \
    *nextTokPtr = ptr; \
    return XML_TOK_INVALID;
    LEAD_CASE(2) LEAD_CASE(3) LEAD_CASE(4)
#undef LEAD_CASE
  case BT_NMSTRT:
  case BT_HEX:
    tok = XML_TOK_NAME;
    ptr += MINBPC(enc);
    break;
  case BT_DIGIT:
  case BT_NAME:
  case BT_MINUS:
#ifdef XML_NS
  case BT_COLON:
#endif
    tok = XML_TOK_NMTOKEN;
    ptr += MINBPC(enc);
    break;
  case BT_NONASCII:
    if (IS_NMSTRT_CHAR_MINBPC(enc, ptr)) {
      ptr += MINBPC(enc);
      tok = XML_TOK_NAME;
      break;
    }
    if (IS_NAME_CHAR_MINBPC(enc, ptr)) {
      ptr += MINBPC(enc);
      tok = XML_TOK_NMTOKEN;
      break;
    }
    /* fall through */
  default:
    *nextTokPtr = ptr;
    return XML_TOK_INVALID;
  }
  while (ptr != end) {
    switch (BYTE_TYPE(enc, ptr)) {
    CHECK_NAME_CASES(enc, ptr, end, nextTokPtr)
    case BT_GT: case BT_RPAR: case BT_COMMA:
    case BT_VERBAR: case BT_LSQB: case BT_PERCNT:
    case BT_S: case BT_CR: case BT_LF:
      *nextTokPtr = ptr;
      return tok;
#ifdef XML_NS
    case BT_COLON:
      ptr += MINBPC(enc);
      switch (tok) {
      case XML_TOK_NAME:
        if (ptr == end)
          return XML_TOK_PARTIAL;
        tok = XML_TOK_PREFIXED_NAME;
        switch (BYTE_TYPE(enc, ptr)) {
        CHECK_NAME_CASES(enc, ptr, end, nextTokPtr)
        default:
          tok = XML_TOK_NMTOKEN;
          break;
        }
        break;
      case XML_TOK_PREFIXED_NAME:
        tok = XML_TOK_NMTOKEN;
        break;
      }
      break;
#endif
    case BT_PLUS:
      if (tok == XML_TOK_NMTOKEN)  {
        *nextTokPtr = ptr;
        return XML_TOK_INVALID;
      }
      *nextTokPtr = ptr + MINBPC(enc);
      return XML_TOK_NAME_PLUS;
    case BT_AST:
      if (tok == XML_TOK_NMTOKEN)  {
        *nextTokPtr = ptr;
        return XML_TOK_INVALID;
      }
      *nextTokPtr = ptr + MINBPC(enc);
      return XML_TOK_NAME_ASTERISK;
    case BT_QUEST:
      if (tok == XML_TOK_NMTOKEN)  {
        *nextTokPtr = ptr;
        return XML_TOK_INVALID;
      }
      *nextTokPtr = ptr + MINBPC(enc);
      return XML_TOK_NAME_QUESTION;
    default:
      *nextTokPtr = ptr;
      return XML_TOK_INVALID;
    }
  }
  return -tok;
}

// 0x009125f0 little2_attributeValueTok (root from slice s00911f60)
int PTRCALL
PREFIX(attributeValueTok)(const ENCODING *enc, const char *ptr,
                          const char *end, const char **nextTokPtr)
{
  const char *start;
  if (ptr == end)
    return XML_TOK_NONE;
  start = ptr;
  while (ptr != end) {
    switch (BYTE_TYPE(enc, ptr)) {
#define LEAD_CASE(n) \
    case BT_LEAD ## n: ptr += n; break;
    LEAD_CASE(2) LEAD_CASE(3) LEAD_CASE(4)
#undef LEAD_CASE
    case BT_AMP:
      if (ptr == start)
        return PREFIX(scanRef)(enc, ptr + MINBPC(enc), end, nextTokPtr);
      *nextTokPtr = ptr;
      return XML_TOK_DATA_CHARS;
    case BT_LT:
      /* this is for inside entity references */
      *nextTokPtr = ptr;
      return XML_TOK_INVALID;
    case BT_LF:
      if (ptr == start) {
        *nextTokPtr = ptr + MINBPC(enc);
        return XML_TOK_DATA_NEWLINE;
      }
      *nextTokPtr = ptr;
      return XML_TOK_DATA_CHARS;
    case BT_CR:
      if (ptr == start) {
        ptr += MINBPC(enc);
        if (ptr == end)
          return XML_TOK_TRAILING_CR;
        if (BYTE_TYPE(enc, ptr) == BT_LF)
          ptr += MINBPC(enc);
        *nextTokPtr = ptr;
        return XML_TOK_DATA_NEWLINE;
      }
      *nextTokPtr = ptr;
      return XML_TOK_DATA_CHARS;
    case BT_S:
      if (ptr == start) {
        *nextTokPtr = ptr + MINBPC(enc);
        return XML_TOK_ATTRIBUTE_VALUE_S;
      }
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

// 0x00912750 little2_entityValueTok (root from slice s00911f60)
int PTRCALL
PREFIX(entityValueTok)(const ENCODING *enc, const char *ptr,
                       const char *end, const char **nextTokPtr)
{
  const char *start;
  if (ptr == end)
    return XML_TOK_NONE;
  start = ptr;
  while (ptr != end) {
    switch (BYTE_TYPE(enc, ptr)) {
#define LEAD_CASE(n) \
    case BT_LEAD ## n: ptr += n; break;
    LEAD_CASE(2) LEAD_CASE(3) LEAD_CASE(4)
#undef LEAD_CASE
    case BT_AMP:
      if (ptr == start)
        return PREFIX(scanRef)(enc, ptr + MINBPC(enc), end, nextTokPtr);
      *nextTokPtr = ptr;
      return XML_TOK_DATA_CHARS;
    case BT_PERCNT:
      if (ptr == start) {
        int tok =  PREFIX(scanPercent)(enc, ptr + MINBPC(enc),
                                       end, nextTokPtr);
        return (tok == XML_TOK_PERCENT) ? XML_TOK_INVALID : tok;
      }
      *nextTokPtr = ptr;
      return XML_TOK_DATA_CHARS;
    case BT_LF:
      if (ptr == start) {
        *nextTokPtr = ptr + MINBPC(enc);
        return XML_TOK_DATA_NEWLINE;
      }
      *nextTokPtr = ptr;
      return XML_TOK_DATA_CHARS;
    case BT_CR:
      if (ptr == start) {
        ptr += MINBPC(enc);
        if (ptr == end)
          return XML_TOK_TRAILING_CR;
        if (BYTE_TYPE(enc, ptr) == BT_LF)
          ptr += MINBPC(enc);
        *nextTokPtr = ptr;
        return XML_TOK_DATA_NEWLINE;
      }
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

#ifdef XML_DTD

// 0x009128b0 little2_ignoreSectionTok (root from slice s00911f60)
int PTRCALL
PREFIX(ignoreSectionTok)(const ENCODING *enc, const char *ptr,
                         const char *end, const char **nextTokPtr)
{
  int level = 0;
  if (MINBPC(enc) > 1) {
    size_t n = end - ptr;
    if (n & (MINBPC(enc) - 1)) {
      n &= ~(MINBPC(enc) - 1);
      end = ptr + n;
    }
  }
  while (ptr != end) {
    switch (BYTE_TYPE(enc, ptr)) {
    INVALID_CASES(ptr, nextTokPtr)
    case BT_LT:
      if ((ptr += MINBPC(enc)) == end)
        return XML_TOK_PARTIAL;
      if (CHAR_MATCHES(enc, ptr, ASCII_EXCL)) {
        if ((ptr += MINBPC(enc)) == end)
          return XML_TOK_PARTIAL;
        if (CHAR_MATCHES(enc, ptr, ASCII_LSQB)) {
          ++level;
          ptr += MINBPC(enc);
        }
      }
      break;
    case BT_RSQB:
      if ((ptr += MINBPC(enc)) == end)
        return XML_TOK_PARTIAL;
      if (CHAR_MATCHES(enc, ptr, ASCII_RSQB)) {
        if ((ptr += MINBPC(enc)) == end)
          return XML_TOK_PARTIAL;
        if (CHAR_MATCHES(enc, ptr, ASCII_GT)) {
          ptr += MINBPC(enc);
          if (level == 0) {
            *nextTokPtr = ptr;
            return XML_TOK_IGNORE_SECT;
          }
          --level;
        }
      }
      break;
    default:
      ptr += MINBPC(enc);
      break;
    }
  }
  return XML_TOK_PARTIAL;
}

#endif /* XML_DTD */

// 0x009129f0 little2_isPublicId (root from slice s00911f60)
int PTRCALL
PREFIX(isPublicId)(const ENCODING *enc, const char *ptr, const char *end,
                   const char **badPtr)
{
  ptr += MINBPC(enc);
  end -= MINBPC(enc);
  for (; ptr != end; ptr += MINBPC(enc)) {
    switch (BYTE_TYPE(enc, ptr)) {
    case BT_DIGIT:
    case BT_HEX:
    case BT_MINUS:
    case BT_APOS:
    case BT_LPAR:
    case BT_RPAR:
    case BT_PLUS:
    case BT_COMMA:
    case BT_SOL:
    case BT_EQUALS:
    case BT_QUEST:
    case BT_CR:
    case BT_LF:
    case BT_SEMI:
    case BT_EXCL:
    case BT_AST:
    case BT_PERCNT:
    case BT_NUM:
#ifdef XML_NS
    case BT_COLON:
#endif
      break;
    case BT_S:
      if (CHAR_MATCHES(enc, ptr, ASCII_TAB)) {
        *badPtr = ptr;
        return 0;
      }
      break;
    case BT_NAME:
    case BT_NMSTRT:
      if (!(BYTE_TO_ASCII(enc, ptr) & ~0x7f))
        break;
    default:
      switch (BYTE_TO_ASCII(enc, ptr)) {
      case 0x24: /* $ */
      case 0x40: /* @ */
        break;
      default:
        *badPtr = ptr;
        return 0;
      }
      break;
    }
  }
  return 1;
}

/* This must only be called for a well-formed start-tag or empty
   element tag.  Returns the number of attributes.  Pointers to the
   first attsMax attributes are stored in atts.
*/

// 0x00912ad0 little2_getAtts (root from slice s00911f60)
int PTRCALL
PREFIX(getAtts)(const ENCODING *enc, const char *ptr,
                int attsMax, ATTRIBUTE *atts)
{
  enum { other, inName, inValue } state = inName;
  int nAtts = 0;
  int open = 0; /* defined when state == inValue;
                   initialization just to shut up compilers */

  for (ptr += MINBPC(enc);; ptr += MINBPC(enc)) {
    switch (BYTE_TYPE(enc, ptr)) {
#define START_NAME \
      if (state == other) { \
        if (nAtts < attsMax) { \
          atts[nAtts].name = ptr; \
          atts[nAtts].normalized = 1; \
        } \
        state = inName; \
      }
#define LEAD_CASE(n) \
    case BT_LEAD ## n: START_NAME ptr += (n - MINBPC(enc)); break;
    LEAD_CASE(2) LEAD_CASE(3) LEAD_CASE(4)
#undef LEAD_CASE
    case BT_NONASCII:
    case BT_NMSTRT:
    case BT_HEX:
      START_NAME
      break;
#undef START_NAME
    case BT_QUOT:
      if (state != inValue) {
        if (nAtts < attsMax)
          atts[nAtts].valuePtr = ptr + MINBPC(enc);
        state = inValue;
        open = BT_QUOT;
      }
      else if (open == BT_QUOT) {
        state = other;
        if (nAtts < attsMax)
          atts[nAtts].valueEnd = ptr;
        nAtts++;
      }
      break;
    case BT_APOS:
      if (state != inValue) {
        if (nAtts < attsMax)
          atts[nAtts].valuePtr = ptr + MINBPC(enc);
        state = inValue;
        open = BT_APOS;
      }
      else if (open == BT_APOS) {
        state = other;
        if (nAtts < attsMax)
          atts[nAtts].valueEnd = ptr;
        nAtts++;
      }
      break;
    case BT_AMP:
      if (nAtts < attsMax)
        atts[nAtts].normalized = 0;
      break;
    case BT_S:
      if (state == inName)
        state = other;
      else if (state == inValue
               && nAtts < attsMax
               && atts[nAtts].normalized
               && (ptr == atts[nAtts].valuePtr
                   || BYTE_TO_ASCII(enc, ptr) != ASCII_SPACE
                   || BYTE_TO_ASCII(enc, ptr + MINBPC(enc)) == ASCII_SPACE
                   || BYTE_TYPE(enc, ptr + MINBPC(enc)) == open))
        atts[nAtts].normalized = 0;
      break;
    case BT_CR: case BT_LF:
      /* This case ensures that the first attribute name is counted
         Apart from that we could just change state on the quote. */
      if (state == inName)
        state = other;
      else if (state == inValue && nAtts < attsMax)
        atts[nAtts].normalized = 0;
      break;
    case BT_GT:
    case BT_SOL:
      if (state != inValue)
        return nAtts;
      break;
    default:
      break;
    }
  }
  /* not reached */
}

static int PTRFASTCALL
PREFIX(charRefNumber)(const ENCODING *enc, const char *ptr)
{
  int result = 0;
  /* skip &# */
  ptr += 2*MINBPC(enc);
  if (CHAR_MATCHES(enc, ptr, ASCII_x)) {
    for (ptr += MINBPC(enc);
         !CHAR_MATCHES(enc, ptr, ASCII_SEMI);
         ptr += MINBPC(enc)) {
      int c = BYTE_TO_ASCII(enc, ptr);
      switch (c) {
      case ASCII_0: case ASCII_1: case ASCII_2: case ASCII_3: case ASCII_4:
      case ASCII_5: case ASCII_6: case ASCII_7: case ASCII_8: case ASCII_9:
        result <<= 4;
        result |= (c - ASCII_0);
        break;
      case ASCII_A: case ASCII_B: case ASCII_C:
      case ASCII_D: case ASCII_E: case ASCII_F:
        result <<= 4;
        result += 10 + (c - ASCII_A);
        break;
      case ASCII_a: case ASCII_b: case ASCII_c:
      case ASCII_d: case ASCII_e: case ASCII_f:
        result <<= 4;
        result += 10 + (c - ASCII_a);
        break;
      }
      if (result >= 0x110000)
        return -1;
    }
  }
  else {
    for (; !CHAR_MATCHES(enc, ptr, ASCII_SEMI); ptr += MINBPC(enc)) {
      int c = BYTE_TO_ASCII(enc, ptr);
      result *= 10;
      result += (c - ASCII_0);
      if (result >= 0x110000)
        return -1;
    }
  }
  return checkCharRefNumber(result);
}

// 0x00912d70 little2_predefinedEntityName (root from slice s00911f60)
int PTRCALL
PREFIX(predefinedEntityName)(const ENCODING *enc, const char *ptr,
                             const char *end)
{
  switch ((end - ptr)/MINBPC(enc)) {
  case 2:
    if (CHAR_MATCHES(enc, ptr + MINBPC(enc), ASCII_t)) {
      switch (BYTE_TO_ASCII(enc, ptr)) {
      case ASCII_l:
        return ASCII_LT;
      case ASCII_g:
        return ASCII_GT;
      }
    }
    break;
  case 3:
    if (CHAR_MATCHES(enc, ptr, ASCII_a)) {
      ptr += MINBPC(enc);
      if (CHAR_MATCHES(enc, ptr, ASCII_m)) {
        ptr += MINBPC(enc);
        if (CHAR_MATCHES(enc, ptr, ASCII_p))
          return ASCII_AMP;
      }
    }
    break;
  case 4:
    switch (BYTE_TO_ASCII(enc, ptr)) {
    case ASCII_q:
      ptr += MINBPC(enc);
      if (CHAR_MATCHES(enc, ptr, ASCII_u)) {
        ptr += MINBPC(enc);
        if (CHAR_MATCHES(enc, ptr, ASCII_o)) {
          ptr += MINBPC(enc);
          if (CHAR_MATCHES(enc, ptr, ASCII_t))
            return ASCII_QUOT;
        }
      }
      break;
    case ASCII_a:
      ptr += MINBPC(enc);
      if (CHAR_MATCHES(enc, ptr, ASCII_p)) {
        ptr += MINBPC(enc);
        if (CHAR_MATCHES(enc, ptr, ASCII_o)) {
          ptr += MINBPC(enc);
          if (CHAR_MATCHES(enc, ptr, ASCII_s))
            return ASCII_APOS;
        }
      }
      break;
    }
  }
  return 0;
}

static int PTRCALL
PREFIX(sameName)(const ENCODING *enc, const char *ptr1, const char *ptr2)
{
  for (;;) {
    switch (BYTE_TYPE(enc, ptr1)) {
#define LEAD_CASE(n) \
    case BT_LEAD ## n: \
      if (*ptr1++ != *ptr2++) \
        return 0;
    LEAD_CASE(4) LEAD_CASE(3) LEAD_CASE(2)
#undef LEAD_CASE
      /* fall through */
      if (*ptr1++ != *ptr2++)
        return 0;
      break;
    case BT_NONASCII:
    case BT_NMSTRT:
#ifdef XML_NS
    case BT_COLON:
#endif
    case BT_HEX:
    case BT_DIGIT:
    case BT_NAME:
    case BT_MINUS:
      if (*ptr2++ != *ptr1++)
        return 0;
      if (MINBPC(enc) > 1) {
        if (*ptr2++ != *ptr1++)
          return 0;
        if (MINBPC(enc) > 2) {
          if (*ptr2++ != *ptr1++)
            return 0;
          if (MINBPC(enc) > 3) {
            if (*ptr2++ != *ptr1++)
              return 0;
          }
        }
      }
      break;
    default:
      if (MINBPC(enc) == 1 && *ptr1 == *ptr2)
        return 1;
      switch (BYTE_TYPE(enc, ptr2)) {
      case BT_LEAD2:
      case BT_LEAD3:
      case BT_LEAD4:
      case BT_NONASCII:
      case BT_NMSTRT:
#ifdef XML_NS
      case BT_COLON:
#endif
      case BT_HEX:
      case BT_DIGIT:
      case BT_NAME:
      case BT_MINUS:
        return 0;
      default:
        return 1;
      }
    }
  }
  /* not reached */
}

static int PTRCALL
PREFIX(nameMatchesAscii)(const ENCODING *enc, const char *ptr1,
                         const char *end1, const char *ptr2)
{
  for (; *ptr2; ptr1 += MINBPC(enc), ptr2++) {
    if (ptr1 == end1)
      return 0;
    if (!CHAR_MATCHES(enc, ptr1, *ptr2))
      return 0;
  }
  return ptr1 == end1;
}

static int PTRFASTCALL
PREFIX(nameLength)(const ENCODING *enc, const char *ptr)
{
  const char *start = ptr;
  for (;;) {
    switch (BYTE_TYPE(enc, ptr)) {
#define LEAD_CASE(n) \
    case BT_LEAD ## n: ptr += n; break;
    LEAD_CASE(2) LEAD_CASE(3) LEAD_CASE(4)
#undef LEAD_CASE
    case BT_NONASCII:
    case BT_NMSTRT:
#ifdef XML_NS
    case BT_COLON:
#endif
    case BT_HEX:
    case BT_DIGIT:
    case BT_NAME:
    case BT_MINUS:
      ptr += MINBPC(enc);
      break;
    default:
      return (int)(ptr - start);
    }
  }
}

static const char * PTRFASTCALL
PREFIX(skipS)(const ENCODING *enc, const char *ptr)
{
  for (;;) {
    switch (BYTE_TYPE(enc, ptr)) {
    case BT_LF:
    case BT_CR:
    case BT_S:
      ptr += MINBPC(enc);
      break;
    default:
      return ptr;
    }
  }
}

static void PTRCALL
PREFIX(updatePosition)(const ENCODING *enc,
                       const char *ptr,
                       const char *end,
                       POSITION *pos)
{
  while (ptr != end) {
    switch (BYTE_TYPE(enc, ptr)) {
#define LEAD_CASE(n) \
    case BT_LEAD ## n: \
      ptr += n; \
      break;
    LEAD_CASE(2) LEAD_CASE(3) LEAD_CASE(4)
#undef LEAD_CASE
    case BT_LF:
      pos->columnNumber = (XML_Size)-1;
      pos->lineNumber++;
      ptr += MINBPC(enc);
      break;
    case BT_CR:
      pos->lineNumber++;
      ptr += MINBPC(enc);
      if (ptr != end && BYTE_TYPE(enc, ptr) == BT_LF)
        ptr += MINBPC(enc);
      pos->columnNumber = (XML_Size)-1;
      break;
    default:
      ptr += MINBPC(enc);
      break;
    }
    pos->columnNumber++;
  }
}

#undef DO_LEAD_CASE
#undef MULTIBYTE_CASES
#undef INVALID_CASES
#undef CHECK_NAME_CASE
#undef CHECK_NAME_CASES
#undef CHECK_NMSTRT_CASE
#undef CHECK_NMSTRT_CASES

#endif /* XML_TOK_IMPL_C */

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
