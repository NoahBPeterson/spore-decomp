// match/slices/s00916960/s00916960.cpp
// Object: UTFSpore_Win32/xmltok.obj (Expat).  Slice s00916960.
// Unknown-encoding support: the utf8/utf16 converters, XmlInitUnknownEncoding and
// the encoding initialisers plus the char-ref-number decoders.
// Reuses the canonical Expat types already declared by src/game/UTFSpore_Win32/xmltok.cpp.

#include "types.h"
#include <stddef.h>
#include <string.h>

typedef unsigned long XML_Size;

// ---- unnamed retail callees and globals (address in the comment)
extern int streqci(const char *s1, const char *s2);              // 0x00916060
extern const unsigned char namePages[256];                       // 0x0143b428
extern const unsigned char nmstrtPages[256];                     // 0x0143b328
extern const unsigned int  namingBitmap[];                       // 0x0143ae28
extern const unsigned char latin1_type[];                        // 0x0143bcac  (latin1_encoding.type)
extern const void *const encodingListDefault[];                  // 0x0154dc54  (6 entries)
extern const void *const encodingListNS[];                       // 0x0154dc70  (6 entries)
extern const void *const encodingNames[];                        // 0x0154dc3c  (6 char* names)
extern const char kUTF16Name[];                                  // 0x0143c9a8  "UTF-16"

// ---- local mirrors of the canonical Expat types (same layout as xmltok.cpp)
enum {
  BT_NONXML, BT_MALFORM, BT_LT, BT_AMP, BT_RSQB, BT_LEAD2, BT_LEAD3, BT_LEAD4,
  BT_TRAIL, BT_CR, BT_LF, BT_GT, BT_QUOT, BT_APOS, BT_EQUALS, BT_QUEST,
  BT_EXCL, BT_SOL, BT_SEMI, BT_NUM, BT_LSQB, BT_S, BT_NMSTRT, BT_COLON,
  BT_HEX, BT_DIGIT, BT_NAME, BT_MINUS, BT_OTHER, BT_NONASCII, BT_PERCNT,
  BT_LPAR, BT_RPAR, BT_AST, BT_PLUS, BT_COMMA, BT_VERBAR
};

#define PTRCALL
#define PTRFASTCALL
#define FASTCALL
#define XMLCALL __cdecl

typedef int (PTRCALL *SCANNER)(const void *, const char *, const char *, const char **);
typedef int (XMLCALL *CONVERTER)(void *userData, const char *p);
typedef unsigned short XML_Char;

struct position_s0091_6960 { XML_Size lineNumber; XML_Size columnNumber; };
typedef struct position_s0091_6960 POSITION;

typedef struct { const char *name; const char *valuePtr; const char *valueEnd; char normalized; } ATTRIBUTE;

typedef struct encoding_s0091_6960 ENCODING;
struct encoding_s0091_6960 {
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
  void (PTRCALL *utf16Convert)(const ENCODING *enc, const char **fromP, const char *fromLim, XML_Char **toP, const XML_Char *toLim);
  int minBytesPerChar;
  char isUtf8;
  char isUtf16;
  void *userData;   // NOTE: appended for the XmlInitEncoding(NS) stores at +0x4c
};

struct normal_encoding_6960 {
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

struct unknown_encoding_6960 {
  struct normal_encoding_6960 normal;
  CONVERTER convert;
  void *userData;
  XML_Char utf16[256];
  char utf8[256][4];
};

extern const struct normal_encoding_6960 latin1_encoding_6960;   // 0x0143bc60
extern const struct normal_encoding_6960 utf8_encoding_6960;     // 0x0143b6a0

#define UCS2_GET_NAMING_6960(pages, hi, lo) \
   (namingBitmap[((pages)[lo] << 3) + ((hi) >> 5)] & (1u << ((hi) & 0x1F)))

#define XML_UTF8_ENCODE_MAX 4
extern void PTRCALL pushPosition(const ENCODING *enc, const char *ptr, const char *end, POSITION *pos); // 0x009160a0
int FASTCALL XmlUtf8Encode(int c, char *buf);                    // 0x00916700
int FASTCALL XmlUtf16Encode(int charNum, XML_Char *buf);         // 0x009167c0
extern void PTRCALL pushPosition(const ENCODING *enc, const char *ptr, const char *end, POSITION *pos); // 0x009160a0
static int PTRFASTCALL unknown_isName(const ENCODING *enc, const char *p);      // 0x00916830
static int PTRFASTCALL unknown_isNmstrt(const ENCODING *enc, const char *p);    // 0x00916890
static int PTRFASTCALL unknown_isInvalid(const ENCODING *enc, const char *p);   // 0x009168f0
static int unknown_encodingIndex(const char *name);                             // 0x00916cb0

static int PTRCALL checkCharRefNumber(int result)
{
  switch (result >> 8) {
  case 0xD8: case 0xD9: case 0xDA: case 0xDB:
  case 0xDC: case 0xDD: case 0xDE: case 0xDF:
    return -1;
  case 0:
    if (latin1_type[result] != BT_NONXML)
      return result;
    return -1;
  case 0xFF:
    switch (result) {
    case 0xFFFE: case 0xFFFF:
      return -1;
    }
    break;
  }
  return result;
}

// These three live in slice s009159b0; re-defined here with the same bodies so the
// function pointers stored below resolve.
static int PTRFASTCALL unknown_isName(const ENCODING *enc, const char *p)
{
  const struct unknown_encoding_6960 *uenc = (const struct unknown_encoding_6960 *)enc;
  int c = uenc->convert(uenc->userData, p);
  if (c & ~0xFFFF)
    return 0;
  return UCS2_GET_NAMING_6960(namePages, c >> 8, c & 0xFF);
}

static int PTRFASTCALL unknown_isNmstrt(const ENCODING *enc, const char *p)
{
  const struct unknown_encoding_6960 *uenc = (const struct unknown_encoding_6960 *)enc;
  int c = uenc->convert(uenc->userData, p);
  if (c & ~0xFFFF)
    return 0;
  return UCS2_GET_NAMING_6960(nmstrtPages, c >> 8, c & 0xFF);
}

static int PTRFASTCALL unknown_isInvalid(const ENCODING *enc, const char *p)
{
  const struct unknown_encoding_6960 *uenc = (const struct unknown_encoding_6960 *)enc;
  int c = uenc->convert(uenc->userData, p);
  return (c & ~0xFFFF) || checkCharRefNumber(c) < 0;
}

// @ 0x00916960
static void PTRCALL unknown_toUtf8(const ENCODING *enc, const char **fromP, const char *fromLim,
                                   char **toP, const char *toLim)
{
  const struct unknown_encoding_6960 *uenc = (const struct unknown_encoding_6960 *)enc;
  char buf[XML_UTF8_ENCODE_MAX];
  for (;;) {
    const char *utf8;
    int n;
    if (*fromP == fromLim)
      break;
    utf8 = uenc->utf8[(unsigned char)**fromP];
    n = *utf8++;
    if (n == 0) {
      int c = uenc->convert(uenc->userData, *fromP);
      n = XmlUtf8Encode(c, buf);
      if (n > toLim - *toP)
        return;
      utf8 = buf;
      *fromP += (int)(latin1_type[(unsigned char)**fromP] - 3);
    }
    else {
      if (n > toLim - *toP)
        return;
      ++*fromP;
    }
    do {
      *(*toP)++ = *utf8++;
    } while (--n != 0);
  }
}

// @ 0x00916a00
static void PTRCALL unknown_toUtf16(const ENCODING *enc, const char **fromP, const char *fromLim,
                                    XML_Char **toP, const XML_Char *toLim)
{
  const struct unknown_encoding_6960 *uenc = (const struct unknown_encoding_6960 *)enc;
  while (*fromP != fromLim && *toP != toLim) {
    XML_Char c = uenc->utf16[(unsigned char)**fromP];
    if (c == 0) {
      c = (XML_Char)uenc->convert(uenc->userData, *fromP);
      *fromP += (int)(latin1_type[(unsigned char)**fromP] - 3);
    }
    else
      ++*fromP;
    *(*toP)++ = c;
  }
}

// @ 0x00916a70
ENCODING *XmlInitUnknownEncoding(void *mem, int *table, CONVERTER convert, void *userData)
{
  int i;
  struct unknown_encoding_6960 *e = (struct unknown_encoding_6960 *)mem;
  memcpy(mem, &latin1_encoding_6960, sizeof(struct normal_encoding_6960));
  for (i = 0; i < 128; ++i)
    if (latin1_type[i] != BT_OTHER && latin1_type[i] != 0 && table[i] != i)
      return 0;
  for (i = 0; i < 256; ++i) {
    int c = table[i];
    if (c == -1) {
      e->normal.type[i] = BT_MALFORM;
      e->utf16[i] = 0xFFFF;
      e->utf8[i][0] = 1;
      e->utf8[i][1] = 0;
    }
    else if (c < 0) {
      if (c < -4)
        return 0;
      e->normal.type[i] = BT_LEAD2 - c;
      e->utf8[i][0] = 0;
      e->utf16[i] = 0;
    }
    else if (c < 0x80) {
      if (latin1_type[c] != BT_OTHER && latin1_type[c] != 0 && c != i)
        return 0;
      e->normal.type[i] = latin1_type[c];
      e->utf8[i][0] = 1;
      e->utf8[i][1] = (char)c;
      e->utf16[i] = (XML_Char)(c == 0 ? 0xFFFF : c);
    }
    else {
      int hi = c >> 8;
      if (c <= 0xFFFF) {
        if (hi == 0) {
          if (latin1_type[c] == BT_NONXML)
            goto Lnonxml;
        }
        else if (hi == 0xFF) {
          if (c == 0xFFFE || c == 0xFFFF)
            goto Lnonxml;
        }
      }
      else if (hi < 0xE0) {
        if (hi >= 0xD8)
          goto Lnonxml;
      }
      else if (hi == 0xFF) {
        if (c == 0xFFFE || c == 0xFFFF)
          goto Lnonxml;
      }
      if (c > 0xFFFF)
        return 0;
      {
        unsigned int bit = 1u << (c & 0x1F);
        unsigned int idx = ((unsigned)c >> 5) & 7;
        int nmstrtOk = (namingBitmap[(unsigned char)nmstrtPages[hi] * 8 + idx] & bit) != 0;
        if (nmstrtOk)
          e->normal.type[i] = BT_NMSTRT;
        else
          e->normal.type[i] = (namingBitmap[(unsigned char)namePages[hi] * 8 + idx] & bit) == 0 ? BT_OTHER : BT_NAME;
      }
      e->utf8[i][0] = (char)XmlUtf8Encode(c, &e->utf8[i][1]);
      e->utf16[i] = (XML_Char)c;
      goto Lnext;
    }
    goto Lnext;
  Lnonxml:
    e->normal.type[i] = BT_NONXML;
    e->utf16[i] = 0xFFFF;
    e->utf8[i][0] = 1;
    e->utf8[i][1] = 0;
  Lnext:
    ;
  }
  e->convert = convert;
  e->userData = userData;
  if (convert) {
    e->normal.isName2 = unknown_isName;
    e->normal.isName3 = unknown_isName;
    e->normal.isName4 = unknown_isName;
    e->normal.isNmstrt2 = unknown_isNmstrt;
    e->normal.isNmstrt3 = unknown_isNmstrt;
    e->normal.isNmstrt4 = unknown_isNmstrt;
    e->normal.isInvalid2 = unknown_isInvalid;
    e->normal.isInvalid3 = unknown_isInvalid;
    e->normal.isInvalid4 = unknown_isInvalid;
  }
  e->normal.enc.utf8Convert = unknown_toUtf8;
  e->normal.enc.utf16Convert = unknown_toUtf16;
  return (ENCODING *)e;
}

// @ 0x00916cb0
static int unknown_encodingIndex(const char *name)
{
  int i;
  if (name == 0)
    return 6;
  for (i = 0; i < 6; ++i)
    if (streqci((const char *)encodingNames[i], name))
      return i;
  return -1;
}

// @ 0x00916cf0 -- shared prolog scanner body (BOM/encoding detection).
// Retail ABI: the encoding prefix table in EAX, ptr in EDI, end on the stack and the
// general-text-entity flag in EDX.  Written as a plain helper; the callers below forward to it.
// @ 0x00916cf0 -- little2_scanProlog/big2_scanProlog shared body (BOM/encoding detection).
// Retail ABI: ptr in EAX, end in EDI, isGeneralTextEntity in EDX, enc at [esp+0x14] after the
// prologue and nextTokPtr in EBP.  Expressed with a __fastcall signature carrying the two
// register arguments; the remaining two come from the stack.
int __fastcall unknown_scanProlog_body(const char *ptr, int isGeneralTextEntity, const char *end,
                                       const ENCODING *enc, const char **nextTokPtr)
{
  int *nextTok;
  if (ptr == end)
    return -4;
  nextTok = (int *)((const char *)enc + 0x4c);
  if (ptr + 1 == end) {
    switch (enc->isUtf8 - 3) {
    case 0: case 1: case 2:
      break;
    default:
      switch ((unsigned char)*ptr) {
      case 0xEF: case 0xFE: case 0xFF:
        if (enc->isUtf8 == 0 && isGeneralTextEntity == 1)
          goto Ldispatch;
        break;
      case 0x00: case '<':
        break;
      default:
        goto Ldispatch;
      }
      break;
    }
    return -1;
  }
  {
    unsigned int c = ((unsigned char)ptr[0] << 8) | (unsigned char)ptr[1];
    if (c == 0xFEFF) {
      if (enc->isUtf8 != 0 || isGeneralTextEntity != 1) {
        *nextTokPtr = ptr + 2;
        *nextTok = *(int *)((const char *)enc + 0x10);
        return 0x0e;
      }
      goto Ldispatch;
    }
    if (c == 0x3C00) {
      if ((enc->isUtf8 != 4 && enc->isUtf8 != 3) || isGeneralTextEntity != 1) {
        int t = *(int *)((const char *)enc + 0x14);
        *nextTok = t;
        return ((int(__thiscall *)(int))*(int *)(t + isGeneralTextEntity * 4))(t);
      }
      goto Ldispatch;
    }
    if (c == 0xEFBB) {
      if (isGeneralTextEntity != 1 || (enc->isUtf8 != 0 && enc->isUtf8 != 3 && enc->isUtf8 != 4 && enc->isUtf8 != 5)) {
        if (ptr + 2 == end)
          return -1;
        if ((unsigned char)ptr[2] == 0xBF) {
          *nextTokPtr = ptr + 3;
          *nextTok = *(int *)((const char *)enc + 8);
          return 0x0e;
        }
      }
      goto Ldispatch;
    }
    if (c == 0xFFFE) {
      if (enc->isUtf8 != 0 || isGeneralTextEntity != 1) {
        *nextTokPtr = ptr + 2;
        *nextTok = *(int *)((const char *)enc + 0x14);
        return 0x0e;
      }
      goto Ldispatch;
    }
    if ((unsigned char)ptr[0] == 0) {
      if (isGeneralTextEntity != 1 || enc->isUtf8 != 5) {
        int t = *(int *)((const char *)enc + 0x10);
        *nextTok = t;
        return ((int(__thiscall *)(int))*(int *)(t + isGeneralTextEntity * 4))(t);
      }
    }
    else if ((unsigned char)ptr[1] == 0 && isGeneralTextEntity != 1) {
      int t = *(int *)((const char *)enc + 0x14);
      *nextTok = t;
      return ((int(__thiscall *)(int))*(int *)(t + isGeneralTextEntity * 4))(t);
    }
    else if ((unsigned char)ptr[1] == 0) {
      if (isGeneralTextEntity == 1 && enc->isUtf8 == 5)
        goto Ldispatch;
      {
        int t = *(int *)((const char *)enc + 0x10);
        *nextTok = t;
        return ((int(__thiscall *)(int))*(int *)(t + isGeneralTextEntity * 4))(t);
      }
    }
    if (c == 0xFFFE)
      return -1;
  }
Ldispatch:
  {
    int t = *(int *)((const char *)enc + enc->isUtf8 * 4);
    *nextTok = t;
    return ((int(__thiscall *)(int))*(int *)(t + isGeneralTextEntity * 4))(t);
  }
}

// @ 0x00916f10
static int PTRCALL unknown_scanS_default(const ENCODING *enc, const char *ptr, const char *end,
                                         const char **nextTokPtr)
{
  return unknown_scanProlog_body(ptr, 0, end, enc, nextTokPtr);
}

// @ 0x00916f40
static int PTRCALL unknown_scanS_ns(const ENCODING *enc, const char *ptr, const char *end,
                                    const char **nextTokPtr)
{
  return unknown_scanProlog_body(ptr, 0, end, enc, nextTokPtr);
}

// @ 0x00916f70
int XmlInitEncoding(ENCODING *enc, ENCODING **encoding, const char *name)
{
  int i;
  if (name == 0)
    i = 6;
  else {
    for (i = 0; i < 6; ++i)
      if (streqci((const char *)encodingNames[i], name))
        break;
    if (i == 6)
      return 0;
  }
  enc->isUtf8 = (char)i == (char)6;
  enc->scanners[0] = (SCANNER)unknown_scanS_default;
  enc->scanners[1] = (SCANNER)unknown_scanS_ns;
  enc->updatePosition = pushPosition;
  enc->userData = 0;
  *encoding = enc;
  return 1;
}

// @ 0x00916fe0
const ENCODING *findEncodingDefault(const ENCODING *enc, const char *ptr, const char *end)
{
  const ENCODING *encoding = 0;
  char name[128];
  name[127] = 0;
  enc->nameMatchesAscii(enc, ptr, end, kUTF16Name);
  return encoding;
}

// @ 0x00917080
const ENCODING *XmlInitEncodingNS_x(const ENCODING *enc, const char *ptr, const char *end)
{
  return findEncodingDefault(enc, ptr, end);
}

// @ 0x009170d0
static int PTRCALL unknown_scanPD_default(const ENCODING *enc, const char *ptr, const char *end,
                                          const char **nextTokPtr)
{
  return unknown_scanProlog_body(ptr, 0, end, enc, nextTokPtr);
}

// @ 0x00917100
static int PTRCALL unknown_scanPD_ns(const ENCODING *enc, const char *ptr, const char *end,
                                     const char **nextTokPtr)
{
  return unknown_scanProlog_body(ptr, 0, end, enc, nextTokPtr);
}

// @ 0x00917130
int XmlInitEncodingNS(ENCODING *enc, ENCODING **encoding, const char *name)
{
  int i;
  if (name == 0)
    i = 6;
  else {
    for (i = 0; i < 6; ++i)
      if (streqci((const char *)encodingNames[i], name))
        break;
    if (i == 6)
      return 0;
  }
  enc->isUtf8 = (char)i == (char)6;
  enc->scanners[0] = (SCANNER)unknown_scanPD_default;
  enc->scanners[1] = (SCANNER)unknown_scanPD_ns;
  enc->updatePosition = pushPosition;
  enc->userData = 0;
  *encoding = enc;
  return 1;
}

// @ 0x009171a0
const ENCODING *findEncodingNS(const ENCODING *enc, const char *ptr, const char *end)
{
  const ENCODING *encoding = 0;
  char name[128];
  name[127] = 0;
  enc->nameMatchesAscii(enc, ptr, end, kUTF16Name);
  return encoding;
}

// @ 0x00917240
const ENCODING *XmlInitEncodingNS_x2(const ENCODING *enc, const char *ptr, const char *end)
{
  return findEncodingNS(enc, ptr, end);
}

// @ 0x00917280
ENCODING *XmlInitUnknownEncodingNS(void *mem, int *table, CONVERTER convert, void *userData)
{
  ENCODING *e = XmlInitUnknownEncoding(mem, table, convert, userData);
  if (e)
    ((char *)e)[0x86] = 0x17;   // retail writes BT_COLON here, not BT_NMSTRT
  return e;
}

// @ 0x009172b0
int PTRFASTCALL unknown_charRefNumber_little(const ENCODING *enc, const char *ptr)
{
  int result = 0;
  (void)enc;
  ptr += 2;
  if (*ptr == 'x') {
    for (;;) {
      int c;
      const char *p = ptr;
      ptr += 1;
      if (p[1] == 0) {
        if (*ptr == ';')
          break;
        c = (unsigned char)*ptr;
      }
      else
        c = -1;
      switch (c) {
      case '0': case '1': case '2': case '3': case '4':
      case '5': case '6': case '7': case '8': case '9':
        result = result << 4 | (c - '0');
        break;
      case 'A': case 'B': case 'C': case 'D': case 'E': case 'F':
        result = result * 16 + c - 'A' + 10;
        break;
      case 'a': case 'b': case 'c': case 'd': case 'e': case 'f':
        result = result * 16 + c - 'a' + 10;
        break;
      default:
        return -1;
      }
      if (result > 0x10FFFF)
        return -1;
    }
  }
  for (;;) {
    int c;
    if (ptr[1] == 0) {
      if (*ptr == ';')
        break;
      c = (unsigned char)*ptr;
    }
    else
      c = -1;
    result = result * 10 + c - '0';
    if (result > 0x10FFFF)
      return -1;
    ++ptr;
  }
  return checkCharRefNumber(result);
}

// @ 0x009173c0
int PTRFASTCALL unknown_charRefNumber_big(const ENCODING *enc, const char *ptr)
{
  int result = 0;
  (void)enc;
  if (ptr[5] == 0 && ptr[4] == 'x') {
    ptr += 4;
    for (;;) {
      int c;
      const char *p = ptr;
      ptr += 2;
      if (p[1] == 0) {
        if (*p == ';')
          break;
        c = (unsigned char)*p;
      }
      else
        c = -1;
      switch (c) {
      case '0': case '1': case '2': case '3': case '4':
      case '5': case '6': case '7': case '8': case '9':
        result = result << 4 | (c - '0');
        break;
      case 'A': case 'B': case 'C': case 'D': case 'E': case 'F':
        result = result * 16 + c - 'A' + 10;
        break;
      case 'a': case 'b': case 'c': case 'd': case 'e': case 'f':
        result = result * 16 + c - 'a' + 10;
        break;
      default:
        return -1;
      }
      if (result > 0x10FFFF)
        return -1;
    }
  }
  else {
    for (;;) {
      int c;
      const char *p = ptr;
      ptr += 2;
      if (p[1] == 0) {
        if (*p == ';')
          break;
        c = (unsigned char)*p;
      }
      else
        c = -1;
      result = result * 10 + c - '0';
      if (result > 0x10FFFF)
        return -1;
    }
  }
  return checkCharRefNumber(result);
}

// @ 0x009174e0
int PTRFASTCALL unknown_charRefNumber_utf16(const ENCODING *enc, const char *ptr)
{
  int result = 0;
  (void)enc;
  if (ptr[0] == 0 && ptr[1] == 'x') {
    ptr += 2;
    for (;;) {
      int c;
      if (ptr[0] == 0) {
        if (ptr[1] == ';')
          break;
        c = (unsigned char)ptr[1];
      }
      else
        c = -1;
      switch (c) {
      case '0': case '1': case '2': case '3': case '4':
      case '5': case '6': case '7': case '8': case '9':
        result = result << 4 | (c - '0');
        break;
      case 'A': case 'B': case 'C': case 'D': case 'E': case 'F':
        result = result * 16 + c - 'A' + 10;
        break;
      case 'a': case 'b': case 'c': case 'd': case 'e': case 'f':
        result = result * 16 + c - 'a' + 10;
        break;
      default:
        return -1;
      }
      if (result > 0x10FFFF)
        return -1;
      ptr += 2;
    }
  }
  else {
    for (;;) {
      int c;
      if (ptr[0] == 0) {
        if (ptr[1] == ';')
          break;
        c = (unsigned char)ptr[1];
      }
      else
        c = -1;
      result = result * 10 + c - '0';
      if (result > 0x10FFFF)
        return -1;
      ptr += 2;
    }
  }
  return checkCharRefNumber(result);
}

// @ 0x00917600
unsigned int LerpColor(unsigned int a, unsigned int b, float t)
{
  unsigned int a0 = a & 0xFF, a1 = (a >> 8) & 0xFF, a2 = (a >> 16) & 0xFF, a3 = (a >> 24) & 0xFF;
  unsigned int b0 = b & 0xFF, b1 = (b >> 8) & 0xFF, b2 = (b >> 16) & 0xFF, b3 = (b >> 24) & 0xFF;
  unsigned int r0 = (unsigned int)(int)((float)(int)(b0 - a0) * t) + a0;
  unsigned int r1 = (unsigned int)(int)((float)(int)(b1 - a1) * t) + a1;
  unsigned int r2 = (unsigned int)(int)((float)(int)(b2 - a2) * t) + a2;
  unsigned int r3 = (unsigned int)(int)((float)(int)(b3 - a3) * t) + a3;
  return (r0 & 0xFF) | ((r1 & 0xFF) << 8) | ((r2 & 0xFF) << 16) | (r3 << 24);
}

// @ 0x009176c0
float *LerpSpriteRect(float *out, float *a, float *b, float t)
{
  out[0] = (b[0] - a[0]) * t + a[0];
  out[1] = (b[1] - a[1]) * t + a[1];
  out[2] = (float)LerpColor(*(unsigned int *)&a[2], *(unsigned int *)&b[2], t);
  out[3] = (b[3] - a[3]) * t + a[3];
  out[4] = (b[4] - a[4]) * t + a[4];
  return out;
}

// @ 0x00917770
struct SpriteList {
  unsigned int *mCur;    // +0x00
  unsigned int mUsed;    // +0x04
  unsigned int mMax;     // +0x08

  void Push(const unsigned int *item);   // 0x00917770
};

void SpriteList::Push(const unsigned int *item)
{
  if (mUsed < mMax) {
    unsigned int *dst = mCur;
    dst[0] = item[0];
    dst[1] = item[1];
    dst[2] = item[2];
    dst[3] = item[3];
    dst[4] = item[4];
    mCur += 5;
  }
  mUsed += 1;
}
