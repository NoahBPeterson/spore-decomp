// Slice s009159b0: expat 2.0.1 xmltok.c / xmltok_impl.c big2 (UTF-16BE) encoding functions,
// parsePseudoAttribute/doParseXmlDecl and the Utf8/Utf16 encoders, plus unknown-encoding
// name predicates. MIT license (Thai Open Source Software Center Ltd / Clark Cooper).
#include "types.h"
#include <stddef.h>
#define PTRCALL
#define PTRFASTCALL
#define FASTCALL
#define XMLCALL __cdecl
typedef unsigned long XML_Size;
enum {
  ASCII_0 = 0x30, ASCII_9 = 0x39, ASCII_A = 0x41, ASCII_Z = 0x5A,
  ASCII_a = 0x61, ASCII_d = 0x64, ASCII_e = 0x65, ASCII_g = 0x67, ASCII_i = 0x69, ASCII_l = 0x6C,
  ASCII_m = 0x6D, ASCII_n = 0x6E, ASCII_o = 0x6F, ASCII_p = 0x70, ASCII_q = 0x71, ASCII_r = 0x72,
  ASCII_s = 0x73, ASCII_t = 0x74, ASCII_u = 0x75, ASCII_v = 0x76, ASCII_y = 0x79, ASCII_z = 0x7A,
  ASCII_c = 0x63,
  ASCII_SPACE = 0x20, ASCII_AMP = 0x26, ASCII_APOS = 0x27, ASCII_GT = 0x3E, ASCII_LT = 0x3C,
  ASCII_QUOT = 0x22, ASCII_MINUS = 0x2D, ASCII_PERIOD = 0x2E, ASCII_EQUALS = 0x3D, ASCII_UNDERSCORE = 0x5F
};
#define ASCII_b 0x62
#define ASCII_f 0x66
#define ASCII_h 0x68
#define ASCII_j 0x6A
#define ASCII_k 0x6B
#define ASCII_w 0x77
#define ASCII_x 0x78
#define UTF8_cval1 0x00
#define UTF8_cval2 0xc0
#define UTF8_cval3 0xe0
#define UTF8_cval4 0xf0

struct position { XML_Size lineNumber; XML_Size columnNumber; };
typedef struct position POSITION;
typedef struct { const char *name; const char *valuePtr; const char *valueEnd; char normalized; } ATTRIBUTE;
struct encoding;
typedef struct encoding ENCODING;
typedef int (PTRCALL *SCANNER)(const ENCODING *, const char *, const char *, const char **);
struct encoding {
  SCANNER scanners[4];
  SCANNER literalScanners[2];
  int (PTRCALL *sameName)(const ENCODING *, const char *, const char *);
  int (PTRCALL *nameMatchesAscii)(const ENCODING *, const char *, const char *, const char *);
  int (PTRFASTCALL *nameLength)(const ENCODING *, const char *);
  const char *(PTRFASTCALL *skipS)(const ENCODING *, const char *);
  int (PTRCALL *getAtts)(const ENCODING *enc, const char *ptr, int attsMax, ATTRIBUTE *atts);
  int (PTRFASTCALL *charRefNumber)(const ENCODING *enc, const char *ptr);
  int (PTRCALL *predefinedEntityName)(const ENCODING *, const char *, const char *);
  void (PTRCALL *updatePosition)(const ENCODING *, const char *ptr, const char *end, POSITION *);
  int (PTRCALL *isPublicId)(const ENCODING *enc, const char *ptr, const char *end, const char **badPtr);
  void (PTRCALL *utf8Convert)(const ENCODING *enc, const char **fromP, const char *fromLim, char **toP, const char *toLim);
  void (PTRCALL *utf16Convert)(const ENCODING *enc, const char **fromP, const char *fromLim, unsigned short **toP, const unsigned short *toLim);
  int minBytesPerChar;
  char isUtf8;
  char isUtf16;
};
typedef int (XMLCALL *CONVERTER)(void *userData, const char *p);
#define XmlUtf8Convert(enc, fromP, fromLim, toP, toLim) \
  (((enc)->utf8Convert)(enc, fromP, fromLim, toP, toLim))
#define XmlNameMatchesAscii(enc, ptr1, end1, ptr2) \
  (((enc)->nameMatchesAscii)(enc, ptr1, end1, ptr2))

enum {
  BT_NONXML, BT_MALFORM, BT_LT, BT_AMP, BT_RSQB, BT_LEAD2, BT_LEAD3, BT_LEAD4,
  BT_TRAIL, BT_CR, BT_LF, BT_GT, BT_QUOT, BT_APOS, BT_EQUALS, BT_QUEST,
  BT_EXCL, BT_SOL, BT_SEMI, BT_NUM, BT_LSQB, BT_S, BT_NMSTRT, BT_COLON,
  BT_HEX, BT_DIGIT, BT_NAME, BT_MINUS, BT_OTHER, BT_NONASCII, BT_PERCNT,
  BT_LPAR, BT_RPAR, BT_AST, BT_PLUS, BT_COMMA, BT_VERBAR
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

struct unknown_encoding {
  struct normal_encoding normal;
  CONVERTER convert;
  void *userData;
  unsigned short utf16[256];
  char utf8[256][4];
};

extern const unsigned char namePages[256];
extern const unsigned char nmstrtPages[256];
extern const unsigned int namingBitmap[];
extern const struct normal_encoding utf8_encoding;     // 0x143b6a0
extern const struct normal_encoding latin1_encoding;   // 0x143bc60

#define UCS2_GET_NAMING(pages, hi, lo) \
   (namingBitmap[((pages)[hi] << 3) + ((lo) >> 5)] & (1 << ((lo) & 0x1F)))

#define MINBPC(enc) 2
#define BYTE_TYPE(enc, p) \
  ((p)[0] == 0 \
   ? ((const struct normal_encoding *)(enc))->type[(unsigned char)(p)[1]] \
   : unicode_byte_type((p)[0], (p)[1]))
#define BYTE_TO_ASCII(enc, p) ((p)[0] == 0 ? (p)[1] : -1)
#define CHAR_MATCHES(enc, p, c) ((p)[0] == 0 && (p)[1] == c)

static int unicode_byte_type(char hi, char lo)   // 0x90fcb0
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

// @ 0x009159b0
int big2_getAtts(const ENCODING *enc, const char *ptr, int attsMax, ATTRIBUTE *atts)
{
  enum { other, inName, inValue } state = inName;
  int nAtts = 0;
  int open = 0;

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
}

// @ 0x00915c50
int big2_predefinedEntityName(const ENCODING *enc, const char *ptr, const char *end)
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

// @ 0x00915d70
int big2_sameName(const ENCODING *enc, const char *ptr1, const char *ptr2)
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
    case BT_COLON:
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
      case BT_COLON:
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
}

// @ 0x00915e90
int big2_nameMatchesAscii(const ENCODING *enc, const char *ptr1, const char *end1, const char *ptr2)
{
  for (; *ptr2; ptr1 += MINBPC(enc), ptr2++) {
    if (ptr1 == end1)
      return 0;
    if (!CHAR_MATCHES(enc, ptr1, *ptr2))
      return 0;
  }
  return ptr1 == end1;
}

// @ 0x00915ed0
int big2_nameLength(const ENCODING *enc, const char *ptr)
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
    case BT_COLON:
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

// @ 0x00915f60
const char *big2_skipS(const ENCODING *enc, const char *ptr)
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

// @ 0x00915fb0
void big2_updatePosition(const ENCODING *enc, const char *ptr, const char *end, POSITION *pos)
{
  while (ptr != end) {
    switch (BYTE_TYPE(enc, ptr)) {
#define LEAD_CASE(n) \
    case BT_LEAD ## n: ptr += n; break;
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

// ---- xmltok.c helpers
static int streqci(const char *s1, const char *s2)
{
  for (;;) {
    char c1 = *s1++;
    char c2 = *s2++;
    if (ASCII_a <= c1 && c1 <= ASCII_z)
      c1 += ASCII_A - ASCII_a;
    if (ASCII_a <= c2 && c2 <= ASCII_z)
      c2 += ASCII_A - ASCII_a;
    if (c1 != c2)
      return 0;
    if (!c1)
      break;
  }
  return 1;
}

extern void PTRCALL normal_updatePosition(const ENCODING *enc, const char *ptr, const char *end, POSITION *pos); // 0x90f9b0

// @ 0x009160a0
static void PTRCALL initUpdatePosition(const ENCODING *enc, const char *ptr, const char *end, POSITION *pos)
{
  normal_updatePosition(&utf8_encoding.enc, ptr, end, pos);
}

static int toAscii(const ENCODING *enc, const char *ptr, const char *end)
{
  char buf[1];
  char *p = buf;
  XmlUtf8Convert(enc, &ptr, end, &p, p + 1);
  if (p == buf)
    return -1;
  else
    return buf[0];
}

static int isSpace(int c)
{
  switch (c) {
  case 0x20:
  case 0xD:
  case 0xA:
  case 0x9:
    return 1;
  }
  return 0;
}

static int parsePseudoAttribute(const ENCODING *enc,
                                const char *ptr,
                                const char *end,
                                const char **namePtr,
                                const char **nameEndPtr,
                                const char **valPtr,
                                const char **nextTokPtr)
{
  int c;
  char open;
  if (ptr == end) {
    *namePtr = NULL;
    return 1;
  }
  if (!isSpace(toAscii(enc, ptr, end))) {
    *nextTokPtr = ptr;
    return 0;
  }
  do {
    ptr += enc->minBytesPerChar;
  } while (isSpace(toAscii(enc, ptr, end)));
  if (ptr == end) {
    *namePtr = NULL;
    return 1;
  }
  *namePtr = ptr;
  for (;;) {
    c = toAscii(enc, ptr, end);
    if (c == -1) {
      *nextTokPtr = ptr;
      return 0;
    }
    if (c == ASCII_EQUALS) {
      *nameEndPtr = ptr;
      break;
    }
    if (isSpace(c)) {
      *nameEndPtr = ptr;
      do {
        ptr += enc->minBytesPerChar;
      } while (isSpace(c = toAscii(enc, ptr, end)));
      if (c != ASCII_EQUALS) {
        *nextTokPtr = ptr;
        return 0;
      }
      break;
    }
    ptr += enc->minBytesPerChar;
  }
  if (ptr == *namePtr) {
    *nextTokPtr = ptr;
    return 0;
  }
  ptr += enc->minBytesPerChar;
  c = toAscii(enc, ptr, end);
  while (isSpace(c)) {
    ptr += enc->minBytesPerChar;
    c = toAscii(enc, ptr, end);
  }
  if (c != ASCII_QUOT && c != ASCII_APOS) {
    *nextTokPtr = ptr;
    return 0;
  }
  open = (char)c;
  ptr += enc->minBytesPerChar;
  *valPtr = ptr;
  for (;;) {
    c = toAscii(enc, ptr, end);
    if (c == open)
      break;
    if (!(ASCII_a <= c && c <= ASCII_z)
        && !(ASCII_A <= c && c <= ASCII_Z)
        && !(ASCII_0 <= c && c <= ASCII_9)
        && c != ASCII_PERIOD
        && c != ASCII_MINUS
        && c != ASCII_UNDERSCORE) {
      *nextTokPtr = ptr;
      return 0;
    }
    ptr += enc->minBytesPerChar;
  }
  *nextTokPtr = ptr + enc->minBytesPerChar;
  return 1;
}

static const char KW_version[] = { ASCII_v, ASCII_e, ASCII_r, ASCII_s, ASCII_i, ASCII_o, ASCII_n, '\0' };
static const char KW_encoding[] = { ASCII_e, ASCII_n, ASCII_c, ASCII_o, ASCII_d, ASCII_i, ASCII_n, ASCII_g, '\0' };
static const char KW_standalone[] = { ASCII_s, ASCII_t, ASCII_a, ASCII_n, ASCII_d, ASCII_a, ASCII_l, ASCII_o, ASCII_n, ASCII_e, '\0' };
static const char KW_yes[] = { ASCII_y, ASCII_e, ASCII_s, '\0' };
static const char KW_no[] = { ASCII_n, ASCII_o, '\0' };

// @ 0x00916460
static int doParseXmlDecl(const ENCODING *(*encodingFinder)(const ENCODING *, const char *, const char *),
                          int isGeneralTextEntity,
                          const ENCODING *enc,
                          const char *ptr,
                          const char *end,
                          const char **badPtr,
                          const char **versionPtr,
                          const char **versionEndPtr,
                          const char **encodingName,
                          const ENCODING **encoding,
                          int *standalone)
{
  const char *val = NULL;
  const char *name = NULL;
  const char *nameEnd = NULL;
  ptr += 5 * enc->minBytesPerChar;
  end -= 2 * enc->minBytesPerChar;
  if (!parsePseudoAttribute(enc, ptr, end, &name, &nameEnd, &val, &ptr) || !name) {
    *badPtr = ptr;
    return 0;
  }
  if (!XmlNameMatchesAscii(enc, name, nameEnd, KW_version)) {
    if (!isGeneralTextEntity) {
      *badPtr = name;
      return 0;
    }
  }
  else {
    if (versionPtr)
      *versionPtr = val;
    if (versionEndPtr)
      *versionEndPtr = ptr;
    if (!parsePseudoAttribute(enc, ptr, end, &name, &nameEnd, &val, &ptr)) {
      *badPtr = ptr;
      return 0;
    }
    if (!name) {
      if (isGeneralTextEntity) {
        *badPtr = ptr;
        return 0;
      }
      return 1;
    }
  }
  if (XmlNameMatchesAscii(enc, name, nameEnd, KW_encoding)) {
    int c = toAscii(enc, val, end);
    if (!(ASCII_a <= c && c <= ASCII_z) && !(ASCII_A <= c && c <= ASCII_Z)) {
      *badPtr = val;
      return 0;
    }
    if (encodingName)
      *encodingName = val;
    if (encoding)
      *encoding = encodingFinder(enc, val, ptr - enc->minBytesPerChar);
    if (!parsePseudoAttribute(enc, ptr, end, &name, &nameEnd, &val, &ptr)) {
      *badPtr = ptr;
      return 0;
    }
    if (!name)
      return 1;
  }
  if (!XmlNameMatchesAscii(enc, name, nameEnd, KW_standalone) || isGeneralTextEntity) {
    *badPtr = name;
    return 0;
  }
  if (XmlNameMatchesAscii(enc, val, ptr - enc->minBytesPerChar, KW_yes)) {
    if (standalone)
      *standalone = 1;
  }
  else if (XmlNameMatchesAscii(enc, val, ptr - enc->minBytesPerChar, KW_no)) {
    if (standalone)
      *standalone = 0;
  }
  else {
    *badPtr = val;
    return 0;
  }
  while (isSpace(toAscii(enc, ptr, end)))
    ptr += enc->minBytesPerChar;
  if (ptr != end) {
    *badPtr = ptr;
    return 0;
  }
  return 1;
}

// @ 0x00916700
int FASTCALL XmlUtf8Encode(int c, char *buf)
{
  if (c < 0)
    return 0;
  if (c < 0x80) {
    buf[0] = (char)(c | UTF8_cval1);
    return 1;
  }
  if (c < 0x800) {
    buf[0] = (char)((c >> 6) | UTF8_cval2);
    buf[1] = (char)((c & 0x3f) | 0x80);
    return 2;
  }
  if (c < 0x10000) {
    buf[0] = (char)((c >> 12) | UTF8_cval3);
    buf[1] = (char)(((c >> 6) & 0x3f) | 0x80);
    buf[2] = (char)((c & 0x3f) | 0x80);
    return 3;
  }
  if (c < 0x110000) {
    buf[0] = (char)((c >> 18) | UTF8_cval4);
    buf[1] = (char)(((c >> 12) & 0x3f) | 0x80);
    buf[2] = (char)(((c >> 6) & 0x3f) | 0x80);
    buf[3] = (char)((c & 0x3f) | 0x80);
    return 4;
  }
  return 0;
}

// @ 0x009167c0
int FASTCALL XmlUtf16Encode(int charNum, unsigned short *buf)
{
  if (charNum < 0)
    return 0;
  if (charNum < 0x10000) {
    buf[0] = (unsigned short)charNum;
    return 1;
  }
  if (charNum < 0x110000) {
    charNum -= 0x10000;
    buf[0] = (unsigned short)((charNum >> 10) + 0xD800);
    buf[1] = (unsigned short)((charNum & 0x3FF) + 0xDC00);
    return 2;
  }
  return 0;
}

// @ 0x00916830
static int PTRFASTCALL unknown_isName(const ENCODING *enc, const char *p)
{
  const struct unknown_encoding *uenc = (const struct unknown_encoding *)enc;
  int c = uenc->convert(uenc->userData, p);
  if (c & ~0xFFFF)
    return 0;
  return UCS2_GET_NAMING(namePages, c >> 8, c & 0xFF);
}

// @ 0x00916890
static int PTRFASTCALL unknown_isNmstrt(const ENCODING *enc, const char *p)
{
  const struct unknown_encoding *uenc = (const struct unknown_encoding *)enc;
  int c = uenc->convert(uenc->userData, p);
  if (c & ~0xFFFF)
    return 0;
  return UCS2_GET_NAMING(nmstrtPages, c >> 8, c & 0xFF);
}

static int PTRFASTCALL checkCharRefNumber(int result)
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

// @ 0x009168f0
static int PTRFASTCALL unknown_isInvalid(const ENCODING *enc, const char *p)
{
  const struct unknown_encoding *uenc = (const struct unknown_encoding *)enc;
  int c = uenc->convert(uenc->userData, p);
  return (c & ~0xFFFF) || checkCharRefNumber(c) < 0;
}

// Callers that live in the neighbouring part of xmltok.c; they give the statics above their
// register calling conventions.
extern const ENCODING *findEncoding(const ENCODING *enc, const char *ptr, const char *end);

int streqci_caller(const char *a, const char *b)
{
  return streqci(a, b);
}

int XmlParseXmlDecl(int isGeneralTextEntity,
                    const ENCODING *enc,
                    const char *ptr,
                    const char *end,
                    const char **badPtr,
                    const char **versionPtr,
                    const char **versionEndPtr,
                    const char **encodingNamePtr,
                    const ENCODING **namedEncodingPtr,
                    int *standalonePtr)
{
  return doParseXmlDecl(findEncoding, isGeneralTextEntity, enc, ptr, end, badPtr, versionPtr,
                        versionEndPtr, encodingNamePtr, namedEncodingPtr, standalonePtr);
}

void *g_s009159b0_keep[] = { (void*)initUpdatePosition,
  (void*)unknown_isName, (void*)unknown_isNmstrt, (void*)unknown_isInvalid };
