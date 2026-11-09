// src/game/UTFSpore_Win32/xmltok.cpp -- migrated from slice(s) s00916960, s0090dd30, s0090d100, s009159b0, s00911480 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/xmltok.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <stddef.h>
#include <string.h>

// unnamed retail callees and globals (address in the comment)
extern const unsigned char namePages[256];      // 0x143b428
extern const unsigned char nmstrtPages[256];    // 0x143b328
extern const unsigned int  namingBitmap[];      // 0x143ae28

// ---- items of slice s00911480 begin (TODO(rewrite): local stubs, replace by canonical classes)
enum {
  BT_NONXML, BT_MALFORM, BT_LT, BT_AMP, BT_RSQB, BT_LEAD2, BT_LEAD3, BT_LEAD4,
  BT_TRAIL, BT_CR, BT_LF, BT_GT, BT_QUOT, BT_APOS, BT_EQUALS, BT_QUEST,
  BT_EXCL, BT_SOL, BT_SEMI, BT_NUM, BT_LSQB, BT_S, BT_NMSTRT, BT_COLON,
  BT_HEX, BT_DIGIT, BT_NAME, BT_MINUS, BT_OTHER, BT_NONASCII, BT_PERCNT,
  BT_LPAR, BT_RPAR, BT_AST, BT_PLUS, BT_COMMA, BT_VERBAR
};
#define ENC_TYPE(enc, c) (((const unsigned char*)(enc))[0x4c + (unsigned char)(c)])
#define UCS2_GET_NAMING(pages, hi, lo) \
   (namingBitmap[((pages)[(unsigned char)(hi)] << 3) + (((unsigned char)(lo)) >> 5)] & (1u << (((unsigned char)(lo)) & 0x1F)))
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
static int byteType(const void* enc, const char* p) {
  if (p[1] == 0)
    return ENC_TYPE(enc, p[0]);
  return unicode_byte_type(p[1], p[0]);
}
// ---- items of slice s00911480 end

// ---- items of slice s009159b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#ifndef NULL
#define NULL 0
#endif
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
#define UTF8_cval1 0x00
#define UTF8_cval2 0xc0
#define UTF8_cval3 0xe0
#define UTF8_cval4 0xf0
struct position_s0091_59b0 { XML_Size lineNumber; XML_Size columnNumber; };
typedef struct position_s0091_59b0 POSITION;
typedef struct { const char *name; const char *valuePtr; const char *valueEnd; char normalized; } ATTRIBUTE;
struct encoding_s0091_59b0;
typedef struct encoding_s0091_59b0 ENCODING;
typedef int (PTRCALL *SCANNER)(const ENCODING *, const char *, const char *, const char **);
struct encoding_s0091_59b0 {
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
extern const struct normal_encoding utf8_encoding;     // 0x143b6a0
extern const struct normal_encoding latin1_encoding;   // 0x143bc60
#define UCS2_GET_NAMING_s0091_59b0(pages, hi, lo) \
   (namingBitmap[((pages)[hi] << 3) + ((lo) >> 5)] & (1 << ((lo) & 0x1F)))
#define MINBPC(enc) 2
#define BYTE_TYPE(enc, p) \
  ((p)[0] == 0 \
   ? ((const struct normal_encoding *)(enc))->type[(unsigned char)(p)[1]] \
   : unicode_byte_type((p)[0], (p)[1]))
#define BYTE_TO_ASCII(enc, p) ((p)[0] == 0 ? (p)[1] : -1)
#define CHAR_MATCHES(enc, p, c) ((p)[0] == 0 && (p)[1] == c)
extern void PTRCALL normal_updatePosition(const ENCODING *enc, const char *ptr, const char *end, POSITION *pos); // 0x90f9b0
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
// ---- items of slice s009159b0 end

// ---- items of slice s0090d100 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char byte;
typedef int (__cdecl *CharHandler)(void* parser, const byte* p);
int FUN_0090d100(void* parser, const byte* begin, const byte* end, const byte** out);
int FUN_0090d320(void* parser, const byte* cur, const byte* end, const byte** out);
int FUN_0090d580(void* parser, const byte* cur, const byte* end, const byte** out);
int FUN_0090d5d0(void* parser, const byte* cur, const byte* end, const byte** out);
int FUN_0090d630(void* parser, const byte* cur, const byte* end, const byte** out);
int FUN_0090d830(void* parser, const byte* cur, const byte* end, const byte** out);
// ---- items of slice s0090d100 end

// ---- items of slice s0090dd30 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct NormalScanner;
typedef int (__cdecl* ScanCallback)(NormalScanner*, const byte*);
struct NormalScanner {
    byte          m_00[0x4c];
    byte          m_class[256];                 // +0x04c
    ScanCallback  m_14c;                        // +0x14c
    ScanCallback  m_150;                        // +0x150
    ScanCallback  m_154;                        // +0x154
    ScanCallback  m_158;                        // +0x158
    ScanCallback  m_15c;                        // +0x15c
    ScanCallback  m_160;                        // +0x160
    ScanCallback  m_164;                        // +0x164
    ScanCallback  m_168;                        // +0x168
    ScanCallback  m_16c;                        // +0x16c
};
extern "C" int normal_scanComment(NormalScanner*, const byte* cur,
                                  const byte* end, const byte** out); // 0x0090cb20
extern "C" int normal_scanAtts(NormalScanner*, const byte* cur,
                               const byte* end, const byte** out);    // 0x0090cdd0
static const byte kCDataPrefix[6] = { 'C', 'D', 'A', 'T', 'A', '[' };
// ---- items of slice s0090dd30 end

// ---- items of slice s00916960 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const unsigned char latin1_type[];                        // 0x0143bcac  (latin1_encoding.type)
extern const void *const encodingListDefault[];                  // 0x0154dc54  (6 entries)
extern const void *const encodingListNS[];                       // 0x0154dc70  (6 entries)
extern const void *const encodingNames[];                        // 0x0154dc3c  (6 char* names)
extern const char kUTF16Name[];                                  // 0x0143c9a8  "UTF-16"
__declspec(noinline)
static int streqci(const char *s1, const char *s2)
{
  for (;;) {
    char c1 = *s1++;
    char c2 = *s2++;
    if (c1 >= 'a' && c1 <= 'z')
      c1 -= 0x20;
    if (c2 >= 'a' && c2 <= 'z')
      c2 -= 0x20;
    if (c1 != c2)
      return 0;
    if (c1 == 0)
      return 1;
  }
}
typedef int (PTRCALL *SCANNER_s0091_6960)(const void *, const char *, const char *, const char **);
typedef unsigned short XML_Char;
struct position_s0091_6960 { XML_Size lineNumber; XML_Size columnNumber; };
typedef struct position_s0091_6960 POSITION_s0091_6960;
typedef struct encoding_s0091_6960 ENCODING_s0091_6960;
struct encoding_s0091_6960 {
  SCANNER_s0091_6960 scanners[4];
  SCANNER_s0091_6960 literalScanners[2];
  int (PTRCALL *sameName)(const ENCODING_s0091_6960 *, const char *, const char *);
  int (PTRCALL *nameMatchesAscii)(const ENCODING_s0091_6960 *, const char *, const char *, const char *);
  int (PTRFASTCALL *nameLength)(const ENCODING_s0091_6960 *, const char *);
  const char *(PTRFASTCALL *skipS)(const ENCODING_s0091_6960 *, const char *);
  int (PTRCALL *getAtts)(const ENCODING_s0091_6960 *enc, const char *ptr, int attsMax, ATTRIBUTE *atts);
  int (PTRFASTCALL *charRefNumber)(const ENCODING_s0091_6960 *enc, const char *ptr);
  int (PTRCALL *predefinedEntityName)(const ENCODING_s0091_6960 *, const char *, const char *);
  void (PTRCALL *updatePosition)(const ENCODING_s0091_6960 *, const char *ptr, const char *end, POSITION_s0091_6960 *);
  int (PTRCALL *isPublicId)(const ENCODING_s0091_6960 *enc, const char *ptr, const char *end, const char **badPtr);
  void (PTRCALL *utf8Convert)(const ENCODING_s0091_6960 *enc, const char **fromP, const char *fromLim, char **toP, const char *toLim);
  void (PTRCALL *utf16Convert)(const ENCODING_s0091_6960 *enc, const char **fromP, const char *fromLim, XML_Char **toP, const XML_Char *toLim);
  int minBytesPerChar;
  char isUtf16;
  char isUtf8;
};
struct init_encoding_s0091_6960 {
  ENCODING_s0091_6960 enc;
  ENCODING_s0091_6960 **out;
};
struct normal_encoding_6960 {
  ENCODING_s0091_6960 enc;
  unsigned char type[256];
  int (PTRCALL *isName2)(const ENCODING_s0091_6960 *, const char *);
  int (PTRCALL *isName3)(const ENCODING_s0091_6960 *, const char *);
  int (PTRCALL *isName4)(const ENCODING_s0091_6960 *, const char *);
  int (PTRCALL *isNmstrt2)(const ENCODING_s0091_6960 *, const char *);
  int (PTRCALL *isNmstrt3)(const ENCODING_s0091_6960 *, const char *);
  int (PTRCALL *isNmstrt4)(const ENCODING_s0091_6960 *, const char *);
  int (PTRCALL *isInvalid2)(const ENCODING_s0091_6960 *, const char *);
  int (PTRCALL *isInvalid3)(const ENCODING_s0091_6960 *, const char *);
  int (PTRCALL *isInvalid4)(const ENCODING_s0091_6960 *, const char *);
};
struct unknown_encoding_6960 {
  struct normal_encoding_6960 normal;
  CONVERTER convert;
  void *userData;
  XML_Char utf16[256];
  char utf8[256][4];
};
extern const struct normal_encoding_6960 latin1_encoding_6960;   // 0x0143bc60
extern int doParseXmlDecl(const ENCODING_s0091_6960 *(*encodingFinder)(const ENCODING_s0091_6960 *, const char *, const char *),
                          int isGeneralTextEntity, const ENCODING_s0091_6960 *enc, const char *ptr,
                          const char *end, const char **badPtr, const char **versionPtr,
                          const char **versionEndPtr, const char **encodingName,
                          const ENCODING_s0091_6960 **encoding, int *standalone);   // 0x00916460
#define UCS2_GET_NAMING_6960(pages, hi, lo) \
   (namingBitmap[((pages)[lo] << 3) + ((hi) >> 5)] & (1u << ((hi) & 0x1F)))
#define XML_UTF8_ENCODE_MAX 4
extern void PTRCALL pushPosition(const ENCODING_s0091_6960 *enc, const char *ptr, const char *end, POSITION_s0091_6960 *pos); // 0x009160a0
int FASTCALL XmlUtf8Encode(int c, char *buf);                    // 0x00916700
static int PTRFASTCALL unknown_isName_s0091_6960(const ENCODING_s0091_6960 *enc, const char *p);      // 0x00916830
static int PTRFASTCALL unknown_isNmstrt_s0091_6960(const ENCODING_s0091_6960 *enc, const char *p);    // 0x00916890
static int PTRFASTCALL unknown_isInvalid_s0091_6960(const ENCODING_s0091_6960 *enc, const char *p);   // 0x009168f0
static int unknown_encodingIndex(const char *name);                             // 0x00916cb0
static int PTRCALL checkCharRefNumber_s0091_6960(int result)
{
  switch (result >> 8) {
  case 0xD8: case 0xD9: case 0xDA: case 0xDB:
  case 0xDC: case 0xDD: case 0xDE: case 0xDF:
    return -1;
  case 0:
    if (latin1_type[result] == BT_NONXML)
      return -1;
    break;
  case 0xFF:
    switch (result) {
    case 0xFFFE: case 0xFFFF:
      return -1;
    }
    break;
  }
  return result;
}
static int PTRFASTCALL unknown_isName_s0091_6960(const ENCODING_s0091_6960 *enc, const char *p)
{
  const struct unknown_encoding_6960 *uenc = (const struct unknown_encoding_6960 *)enc;
  int c = uenc->convert(uenc->userData, p);
  if (c & ~0xFFFF)
    return 0;
  return UCS2_GET_NAMING_6960(namePages, c >> 8, c & 0xFF);
}
static int PTRFASTCALL unknown_isNmstrt_s0091_6960(const ENCODING_s0091_6960 *enc, const char *p)
{
  const struct unknown_encoding_6960 *uenc = (const struct unknown_encoding_6960 *)enc;
  int c = uenc->convert(uenc->userData, p);
  if (c & ~0xFFFF)
    return 0;
  return UCS2_GET_NAMING_6960(nmstrtPages, c >> 8, c & 0xFF);
}
static int PTRFASTCALL unknown_isInvalid_s0091_6960(const ENCODING_s0091_6960 *enc, const char *p)
{
  const struct unknown_encoding_6960 *uenc = (const struct unknown_encoding_6960 *)enc;
  int c = uenc->convert(uenc->userData, p);
  return (c & ~0xFFFF) || checkCharRefNumber_s0091_6960(c) < 0;
}
// ---- items of slice s00916960 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
void PTRCALL unknown_toUtf16(const ENCODING_s0091_6960 *enc, const char **fromP, const char *fromLim, XML_Char **toP, const XML_Char *toLim);  // 0x00916a00 (stays in the slice: not this object's)

// @ 0x0090d100
int FUN_0090d100(void* parser, const byte* begin, const byte* end, const byte** out)
{
    const byte* p = begin;
    const byte* pb;

    if (p == end)
        return -4;

    switch (((const byte*)parser)[0x4c + *p]) {
    case 4:
        p++;
        if (p == end)
            return -1;
        if (*p == ']') {
            p++;
            if (p == end)
                return -1;
            if (*p != '>') {
                p--;
                break;
            }
            *out = p + 1;
            return 0x28;
        }
        break;
    case 9:
        p++;
        if (p == end)
            return -1;
        if (((const byte*)parser)[0x4c + *p] == 10)
            p++;
        *out = p;
        return 7;
    case 10:
        *out = p + 1;
        return 7;
    case 5:
        if (end - p < 2)
            return -2;
        if ((*(CharHandler*)((char*)parser + 0x164))(parser, p) != 0) {
            *out = p;
            return 0;
        }
        p += 2;
        break;
    case 6:
        if (end - p < 3)
            return -2;
        if ((*(CharHandler*)((char*)parser + 0x168))(parser, p) != 0) {
            *out = p;
            return 0;
        }
        p += 3;
        break;
    case 7:
        if (end - p < 4)
            return -2;
        if ((*(CharHandler*)((char*)parser + 0x16c))(parser, p) != 0) {
            *out = p;
            return 0;
        }
        p += 4;
        break;
    case 0:
    case 1:
    case 8:
        *out = p;
        return 0;
    default:
        p++;
        break;
    }

    if (p != end) {
        int rem = (int)(end - p);
        do {
            switch (((const byte*)parser)[0x4c + *p]) {
            case 5:
                if (rem < 2) {
                    *out = p;
                    return 6;
                }
                if ((*(CharHandler*)((char*)parser + 0x164))(parser, p) != 0) {
                    *out = p;
                    return 6;
                }
                p += 2;
                rem -= 2;
                break;
            case 6:
                if (rem < 3) {
                    *out = p;
                    return 6;
                }
                if ((*(CharHandler*)((char*)parser + 0x168))(parser, p) != 0) {
                    *out = p;
                    return 6;
                }
                p += 3;
                rem -= 3;
                break;
            case 7:
                if (rem < 4) {
                    *out = p;
                    return 6;
                }
                if ((*(CharHandler*)((char*)parser + 0x16c))(parser, p) != 0) {
                    *out = p;
                    return 6;
                }
                p += 4;
                rem -= 4;
                break;
            case 0:
            case 1:
            case 4:
            case 8:
            case 9:
            case 10:
                *out = p;
                return 6;
            default:
                p++;
                rem--;
                break;
            }
        } while (p != end);
    }
    *out = p;
    return 6;
}

// @ 0x0090d320
int FUN_0090d320(void* parser, const byte* cur, const byte* end, const byte** out)
{
    const byte* pb;

    if (cur == end)
        return -1;

    switch (((const byte*)parser)[0x4c + *cur]) {
    case 5:
        if (end - cur < 2)
            return -2;
        if ((*(CharHandler*)((char*)parser + 0x158))(parser, cur) == 0) {
            *out = cur;
            return 0;
        }
        pb = cur + 2;
        break;
    case 6:
        if (end - cur < 3)
            return -2;
        if ((*(CharHandler*)((char*)parser + 0x15c))(parser, cur) == 0) {
            *out = cur;
            return 0;
        }
        pb = cur + 3;
        break;
    case 7:
        if (end - cur < 4)
            return -2;
        if ((*(CharHandler*)((char*)parser + 0x160))(parser, cur) == 0) {
            *out = cur;
            return 0;
        }
        pb = cur + 4;
        break;
    case 0x16:
    case 0x18:
        pb = cur + 1;
        break;
    default:
        *out = cur;
        return 0;
    }

    if (pb == end)
        return -1;

    for (;;) {
        int rem = (int)(end - pb);
        switch (((const byte*)parser)[0x4c + *pb]) {
        case 5:
            if (rem < 2)
                return -2;
            if ((*(CharHandler*)((char*)parser + 0x14c))(parser, pb) != 0) {
                pb += 2;
                rem -= 2;
                break;
            }
            *out = pb;
            return 0;
        case 6:
            if (rem < 3)
                return -2;
            if ((*(CharHandler*)((char*)parser + 0x150))(parser, pb) != 0) {
                pb += 3;
                rem -= 3;
                break;
            }
            *out = pb;
            return 0;
        case 7:
            if (rem < 4)
                return -2;
            if ((*(CharHandler*)((char*)parser + 0x154))(parser, pb) != 0) {
                pb += 4;
                rem -= 4;
                break;
            }
            *out = pb;
            return 0;
        case 9:
        case 10:
        case 0x15:
            pb++;
            if (pb == end)
                return -1;
            for (;;) {
                int c = ((const byte*)parser)[0x4c + *pb];
                if (c == 9 || c == 10 || c == 0x15) {
                    pb++;
                    if (pb == end)
                        return -1;
                    continue;
                }
                if (c == 0xb) {
                    *out = pb + 1;
                    return 5;
                }
                *out = pb;
                return 0;
            }
        case 0xb:
            *out = pb + 1;
            return 5;
        case 0x16:
        case 0x17:
        case 0x18:
        case 0x19:
        case 0x1a:
        case 0x1b:
            pb++;
            rem--;
            break;
        default:
            *out = pb;
            return 0;
        }
        if (pb == end)
            return -1;
    }
}

// @ 0x0090d580
int FUN_0090d580(void* parser, const byte* cur, const byte* end, const byte** out)
{
    int c;

    if (cur == end)
        return -1;

    for (;;) {
        c = ((const byte*)parser)[0x4c + *cur];
        if ((byte)(c - 0x18) > 1) {
            *out = cur;
            return 0;
        }
        cur++;
        if (cur == end)
            return -1;
        c = ((const byte*)parser)[0x4c + *cur];
        if (c == 0x12) {
            *out = cur + 1;
            return 10;
        }
        if ((byte)(c - 0x18) > 1) {
            *out = cur;
            return 0;
        }
        cur++;
        if (cur == end)
            return -1;
    }
}

// @ 0x0090d5d0
int FUN_0090d5d0(void* parser, const byte* cur, const byte* end, const byte** out)
{
    int c;

    if (cur == end)
        return -1;

    if (*cur == 'x')
        return FUN_0090d580(parser, cur + 1, end, out);

    for (;;) {
        c = ((const byte*)parser)[0x4c + *cur];
        if (c != 0x19) {
            *out = cur;
            return 0;
        }
        cur++;
        if (cur == end)
            return -1;
        c = ((const byte*)parser)[0x4c + *cur];
        if (c == 0x12) {
            *out = cur + 1;
            return 10;
        }
    }
}

// @ 0x0090d630
int FUN_0090d630(void* parser, const byte* cur, const byte* end, const byte** out)
{
    const byte* pb;
    int c;

    if (cur == end)
        return -1;

    switch (((const byte*)parser)[0x4c + *cur]) {
    case 5:
        if (end - cur < 2)
            return -2;
        if ((*(CharHandler*)((char*)parser + 0x158))(parser, cur) == 0) {
            *out = cur;
            return 0;
        }
        pb = cur + 2;
        break;
    case 6:
        if (end - cur < 3)
            return -2;
        if ((*(CharHandler*)((char*)parser + 0x15c))(parser, cur) == 0) {
            *out = cur;
            return 0;
        }
        pb = cur + 3;
        break;
    case 7:
        if (end - cur < 4)
            return -2;
        if ((*(CharHandler*)((char*)parser + 0x160))(parser, cur) == 0) {
            *out = cur;
            return 0;
        }
        pb = cur + 4;
        break;
    case 0x13:
        return FUN_0090d5d0(parser, cur, end, out);
    case 0x16:
    case 0x18:
        pb = cur + 1;
        break;
    default:
        *out = cur;
        return 0;
    }

    if (pb == end)
        return -1;

    for (;;) {
        int rem = (int)(end - pb);
        switch (((const byte*)parser)[0x4c + *pb]) {
        case 5:
            if (rem < 2)
                return -2;
            if ((*(CharHandler*)((char*)parser + 0x14c))(parser, pb) != 0) {
                pb += 2;
                rem -= 2;
                break;
            }
            *out = pb;
            return 0;
        case 6:
            if (rem < 3)
                return -2;
            if ((*(CharHandler*)((char*)parser + 0x150))(parser, pb) != 0) {
                pb += 3;
                rem -= 3;
                break;
            }
            *out = pb;
            return 0;
        case 7:
            if (rem < 4)
                return -2;
            if ((*(CharHandler*)((char*)parser + 0x154))(parser, pb) != 0) {
                pb += 4;
                rem -= 4;
                break;
            }
            *out = pb;
            return 0;
        case 0x12:
            *out = pb + 1;
            return 9;
        case 0x16:
        case 0x18:
        case 0x19:
        case 0x1a:
        case 0x1b:
            pb++;
            rem--;
            break;
        default:
            *out = pb;
            return 0;
        }
        if (pb == end)
            return -1;
    }
}

// @ 0x0090d830
int FUN_0090d830(void* parser, const byte* cur, const byte* end, const byte** out)
{
    const byte* pb;
    const byte* pb2;
    int c;
    int seen;

    if (cur == end)
        return -1;

    seen = 0;
    for (;;) {
        switch (((const byte*)parser)[0x4c + *cur]) {
        case 5:
            if (end - cur < 2)
                return -2;
            if ((*(CharHandler*)((char*)parser + 0x14c))(parser, cur) == 0) {
                *out = cur;
                return 0;
            }
            cur += 2;
            break;
        case 6:
            if (end - cur < 3)
                return -2;
            if ((*(CharHandler*)((char*)parser + 0x150))(parser, cur) == 0) {
                *out = cur;
                return 0;
            }
            cur += 3;
            break;
        case 7:
            if (end - cur < 4)
                return -2;
            if ((*(CharHandler*)((char*)parser + 0x154))(parser, cur) != 0) {
                cur += 4;
                break;
            }
            *out = cur;
            return 0;
        case 9:
        case 10:
        case 0x15:
            for (;;) {
                cur++;
                if (cur == end)
                    return -1;
                c = ((const byte*)parser)[0x4c + *cur];
                if (c == 0xe)
                    goto scan_name;
                if (c < 9 || c > 10)
                    if (c != 0x15) {
                        *out = cur;
                        return 0;
                    }
            }
        case 0xe:
scan_name:
            seen = 0;
            for (;;) {
                cur++;
                if (cur == end)
                    return -1;
                c = ((const byte*)parser)[0x4c + *cur];
                if (c == 0xc || c == 0xd)
                    break;
                if (c < 9 || c > 10)
                    if (c != 0x15) {
                        *out = cur;
                        return 0;
                    }
            }
            for (;;) {
                cur++;
                if (cur == end)
                    return -1;
                c = ((const byte*)parser)[0x4c + *cur];
                if (c == 0xc || c == 0xd) {
                    pb2 = cur + 1;
                    if (pb2 == end)
                        return -1;
                    c = ((const byte*)parser)[0x4c + *pb2];
                    if (c == 9 || c == 10 || c == 0x15) {
                        cur = pb2;
                        break;
                    }
                    if (c == 0xb) {
                        *out = pb2 + 1;
                        return 1;
                    }
                    if (c == 0x11) {
                        pb = pb2 + 1;
                        if (pb == end)
                            return -1;
                        if (*pb == '>') {
                            *out = pb2 + 2;
                            return 3;
                        }
                        *out = pb;
                        return 0;
                    }
                    *out = pb2;
                    return 0;
                }
                if (c == 0) {
                    *out = cur;
                    return 0;
                }
                if (c == 1) {
                    *out = cur;
                    return 0;
                }
                if (c == 8) {
                    *out = cur;
                    return 0;
                }
                if (c == 2) {
                    *out = cur;
                    return 0;
                }
                if (c == 3) {
                    int r = FUN_0090d630(parser, cur + 1, end, &cur);
                    if (r == 0) {
                        *out = cur;
                        return 0;
                    }
                    if (r < 0)
                        return r;
                    break;
                }
                if (c == 5) {
                    if (end - cur < 2)
                        return -2;
                    if ((*(CharHandler*)((char*)parser + 0x164))(parser, cur) != 0) {
                        *out = cur;
                        return 0;
                    }
                    cur += 2;
                    break;
                }
                if (c == 6) {
                    if (end - cur < 3)
                        return -2;
                    if ((*(CharHandler*)((char*)parser + 0x168))(parser, cur) != 0) {
                        *out = cur;
                        return 0;
                    }
                    cur += 3;
                    break;
                }
                if (c == 7) {
                    if (end - cur < 4)
                        return -2;
                    if ((*(CharHandler*)((char*)parser + 0x16c))(parser, cur) == 0) {
                        *out = cur;
                        return 0;
                    }
                    cur += 4;
                    break;
                }
            }
            break;
        case 0x16:
        case 0x18:
        case 0x19:
        case 0x1a:
        case 0x1b:
            cur++;
            break;
        case 0x17:
            if (seen != 0) {
                *out = cur;
                return 0;
            }
            seen = 1;
            cur++;
            if (cur == end)
                return -1;
            switch (((const byte*)parser)[0x4c + *cur]) {
            case 5:
                if (end - cur < 2)
                    return -2;
                if ((*(CharHandler*)((char*)parser + 0x158))(parser, cur) == 0) {
                    *out = cur;
                    return 0;
                }
                cur += 2;
                break;
            case 6:
                if (end - cur < 3)
                    return -2;
                if ((*(CharHandler*)((char*)parser + 0x15c))(parser, cur) == 0) {
                    *out = cur;
                    return 0;
                }
                cur += 3;
                break;
            case 7:
                if (end - cur < 4)
                    return -2;
                if ((*(CharHandler*)((char*)parser + 0x160))(parser, cur) == 0) {
                    *out = cur;
                    return 0;
                }
                cur += 4;
                break;
            case 0x16:
            case 0x18:
                cur++;
                break;
            default:
                *out = cur;
                return 0;
            }
            break;
        default:
            *out = cur;
            return 0;
        }
        if (cur == end)
            return -1;
    }
}

// @ 0x0090dd30
int normalScanText(NormalScanner* s, const byte* cur, const byte* end, const byte** out)
{
    const byte* p5;
    const byte* p6;
    int rem;
    int rem8;
    bool flag;

    if (cur == end)
        return -1;

    switch (s->m_class[*cur]) {
    case 5:
        if (end - cur < 2)
            return -2;
        if (!s->m_158(s, cur)) {
            *out = cur;
            return 0;
        }
        cur += 2;
        break;
    case 6:
        if (end - cur < 3)
            return -2;
        if (!s->m_15c(s, cur)) {
            *out = cur;
            return 0;
        }
        cur += 3;
        break;
    case 7:
        if (end - cur < 4)
            return -2;
        if (!s->m_160(s, cur)) {
            *out = cur;
            return 0;
        }
        cur += 4;
        break;
    case 0x0f:
        return normal_scanAtts(s, cur, end, out);
    case 0x10: {
        int c2;
        int i;

        ++cur;
        if (cur == end)
            return -1;
        c2 = s->m_class[*cur];
        if (c2 == 0x14) {
            ++cur;
            if (end - cur < 6)
                return -1;
            i = 0;
            do {
                if (*cur != kCDataPrefix[i]) {
                    *out = cur;
                    return 0;
                }
                ++i;
                ++cur;
            } while (i < 6);
            *out = cur;
            return 8;
        }
        if (c2 == 0x1b)
            return normal_scanComment(s, cur, end, out);
        *out = cur;
        return 0;
    }
    case 0x11:
        return FUN_0090d320(s, cur, end, out);
    case 0x16:
    case 0x18:
        ++cur;
        break;
    default:
        *out = cur;
        return 0;
    }

    flag = false;
    if (cur == end)
        return -1;
    rem = (int)(end - cur);

    for (;;) {
        p5 = cur;
        rem8 = rem;
        p6 = cur;

        switch (s->m_class[*cur]) {
        case 5:
            if (rem < 2)
                return -2;
            if (!s->m_14c(s, cur)) {
                *out = cur;
                return 0;
            }
            cur += 2;
            rem -= 2;
            break;
        case 6:
            if (rem < 3)
                return -2;
            if (!s->m_150(s, cur)) {
                *out = cur;
                return 0;
            }
            cur += 3;
            rem -= 3;
            break;
        case 7:
            if (rem < 4)
                return -2;
            if (!s->m_154(s, cur)) {
                *out = cur;
                return 0;
            }
            cur += 4;
            rem -= 4;
            break;
        case 9:
        case 10:
        case 0x15:
            p5 = cur + 1;
            if (p5 == end)
                return -1;
            goto tail_dispatch;
        case 0x0b:
            *out = cur + 1;
            return 2;
        case 0x11:
            p6 = cur + 1;
            if (p6 == end)
                return -1;
            if (*p6 == '>') {
                *out = cur + 2;
                return 4;
            }
            *out = p6;
            return 0;
        case 0x16:
        case 0x18:
        case 0x19:
        case 0x1a:
        case 0x1b:
            cur = p5 + 1;
            rem = rem8 - 1;
            break;
        case 0x17:
            if (flag) {
                *out = cur;
                return 0;
            }
            p5 = cur + 1;
            rem8 = rem - 1;
            flag = true;
            if (p5 == end)
                return -1;
            switch (s->m_class[*p5]) {
            case 5:
                if (rem8 < 2)
                    return -2;
                if (!s->m_158(s, p5)) {
                    *out = p5;
                    return 0;
                }
                cur = p5 + 2;
                rem = rem8 - 2;
                break;
            case 6:
                if (rem8 < 3)
                    return -2;
                p6 = p5;
                if (!s->m_15c(s, p5)) {
                    *out = p6;
                    return 0;
                }
                cur = p5 + 3;
                rem = rem8 - 3;
                break;
            case 7:
                if (rem8 < 4)
                    return -2;
                if (!s->m_160(s, p5)) {
                    *out = p5;
                    return 0;
                }
                cur = p5 + 4;
                rem = rem8 - 4;
                break;
            case 0x16:
            case 0x18:
                cur = p5 + 1;
                rem = rem8 - 1;
                break;
            case 0x1d:
                *out = p5;
                return 0;
            default:
                *out = p5;
                return 0;
            }
            break;
        default:
            *out = cur;
            return 0;
        }

        if (cur == end)
            return -1;
    }

tail_dispatch:
    for (;;) {
        switch (s->m_class[*p5]) {
        case 5:
            if (end - p5 < 2)
                return -2;
            if (!s->m_158(s, p5)) {
                *out = p5;
                return 0;
            }
            p5 += 2;
            break;
        case 6:
            if (end - p5 < 3)
                return -2;
            if (!s->m_15c(s, p5)) {
                *out = p5;
                return 0;
            }
            p5 += 3;
            break;
        case 7:
            if (end - p5 < 4)
                return -2;
            if (!s->m_160(s, p5)) {
                *out = p5;
                return 0;
            }
            p5 += 4;
            break;
        case 9:
        case 10:
        case 0x15:
            p5 += 1;
            if (p5 == end)
                return -1;
            continue;
        case 0x0b:
            *out = p5 + 1;
            return 2;
        case 0x11:
            p6 = p5 + 1;
            if (p6 == end)
                return -1;
            if (*p6 == '>') {
                *out = p5 + 2;
                return 4;
            }
            *out = p6;
            return 0;
        case 0x16:
        case 0x18:
            p5 += 1;
            break;
        case 0x1d:
            *out = p5;
            return 0;
        default:
            *out = p5;
            return 0;
        }
        return FUN_0090d830(s, p5, end, out);
    }
}

// @ 0x0090e1f0
int normalScanElement(NormalScanner* s, const byte* cur, const byte* end, const byte** out)
{
    const byte* p5;
    const byte* pbA;
    const byte* pbB;
    int rem;

    if (cur == end)
        return -4;

    p5 = cur;
    switch (s->m_class[*cur]) {
    case 0:
    case 1:
    case 8:
        *out = cur;
        return 0;
    case 2:
        return normalScanText(s, cur + 1, end, out);
    case 3:
        return FUN_0090d630(s, cur + 1, end, out);
    case 4:
        p5 = cur + 1;
        if (p5 == end)
            return -5;
        if (*p5 == ']') {
            p5 = cur + 2;
            if (p5 == end)
                return -5;
            if (*p5 == '>') {
                *out = p5;
                return 0;
            }
            p5 = cur + 1;
        }
        break;
    case 5:
        if (end - cur < 2)
            return -2;
        if (s->m_164(s, cur) != 0) {
            *out = cur;
            return 0;
        }
        p5 = cur + 2;
        break;
    case 6:
        if (end - cur < 3)
            return -2;
        if (s->m_168(s, cur) != 0) {
            *out = cur;
            return 0;
        }
        p5 = cur + 3;
        break;
    case 7:
        if (end - cur < 4)
            return -2;
        if (s->m_16c(s, cur) != 0) {
            *out = cur;
            return 0;
        }
        p5 = cur + 4;
        break;
    case 9:
        p5 = cur + 1;
        if (p5 == end)
            return -3;
        if (s->m_class[*p5] == 0x0a)
            p5 = cur + 2;
        *out = p5;
        return 7;
    case 10:
        *out = cur + 1;
        return 7;
    default:
        p5 = cur + 1;
        break;
    }

    if (p5 != end) {
        pbA = p5 + 2;
        pbB = p5 + 1;
        rem = (int)(end - p5);
        do {
            switch (s->m_class[*p5]) {
            case 0:
            case 1:
            case 2:
            case 3:
            case 8:
            case 9:
            case 10:
                *out = p5;
                return 6;
            case 4:
                if (pbB == end) {
                    *out = p5;
                    return 6;
                }
                if (*pbB == ']') {
                    if (pbA == end) {
                        *out = p5;
                        return 6;
                    }
                    if (*pbA == '>') {
                        *out = p5 + 2;
                        return 0;
                    }
                }
                p5 += 1;
                rem -= 1;
                pbB += 1;
                pbA += 1;
                break;
            case 5:
                if (rem < 2 || s->m_164(s, p5) != 0) {
                    *out = p5;
                    return 6;
                }
                p5 += 2;
                rem -= 2;
                pbB += 2;
                pbA += 2;
                break;
            case 6:
                if (rem < 3 || s->m_168(s, p5) != 0) {
                    *out = p5;
                    return 6;
                }
                p5 += 3;
                rem -= 3;
                pbB += 3;
                pbA += 3;
                break;
            case 7:
                if (rem < 4 || s->m_16c(s, p5) != 0) {
                    *out = p5;
                    return 6;
                }
                p5 += 4;
                rem -= 4;
                pbB += 4;
                pbA += 4;
                break;
            default:
                p5 += 1;
                rem -= 1;
                pbB += 1;
                pbA += 1;
                break;
            }
        } while (p5 != end);
    }

    *out = p5;
    return 6;
}

// @ 0x0090e490
int normalScanContent(NormalScanner* s, const byte* cur, const byte* end, const byte** out)
{
    int rem;

    if (cur == end)
        return -0x16;

    switch (s->m_class[*cur]) {
    case 5:
        if (end - cur < 2)
            return -2;
        if (!s->m_158(s, cur)) {
            *out = cur;
            return 0;
        }
        cur += 2;
        break;
    case 6:
        if (end - cur < 3)
            return -2;
        if (!s->m_15c(s, cur)) {
            *out = cur;
            return 0;
        }
        cur += 3;
        break;
    case 7:
        if (end - cur < 4)
            return -2;
        if (!s->m_160(s, cur)) {
            *out = cur;
            return 0;
        }
        cur += 4;
        break;
    case 9:
    case 10:
    case 0x15:
    case 0x1e:
        *out = cur;
        return 0x16;
    case 0x16:
    case 0x18:
        cur += 1;
        break;
    case 0x1d:
        *out = cur;
        return 0;
    default:
        *out = cur;
        return 0;
    }

    if (cur != end) {
        rem = (int)(end - cur);
        do {
            switch (s->m_class[*cur]) {
            case 5:
                if (rem < 2)
                    return -2;
                if (!s->m_14c(s, cur)) {
                    *out = cur;
                    return 0;
                }
                cur += 2;
                rem -= 2;
                break;
            case 6:
                if (rem < 3)
                    return -2;
                if (!s->m_150(s, cur)) {
                    *out = cur;
                    return 0;
                }
                cur += 3;
                rem -= 3;
                break;
            case 7:
                if (rem < 4)
                    return -2;
                if (!s->m_154(s, cur)) {
                    *out = cur;
                    return 0;
                }
                cur += 4;
                rem -= 4;
                break;
            case 0x12:
                *out = cur + 1;
                return 0x1c;
            case 0x16:
            case 0x18:
            case 0x19:
            case 0x1a:
            case 0x1b:
                cur += 1;
                rem -= 1;
                break;
            case 0x1d:
                *out = cur;
                return 0;
            default:
                *out = cur;
                return 0;
            }
        } while (cur != end);
    }
    return -1;
}

// @ 0x0090e6a0
int normalScanAttValue(NormalScanner* s, const byte* cur, const byte* end, const byte** out)
{
    int rem;

    if (cur == end)
        return -1;

    switch (s->m_class[*cur]) {
    case 5:
        if (end - cur < 2)
            return -2;
        if (!s->m_158(s, cur)) {
            *out = cur;
            return 0;
        }
        cur += 2;
        break;
    case 6:
        if (end - cur < 3)
            return -2;
        if (!s->m_15c(s, cur)) {
            *out = cur;
            return 0;
        }
        cur += 3;
        break;
    case 7:
        if (end - cur < 4)
            return -2;
        if (!s->m_160(s, cur)) {
            *out = cur;
            return 0;
        }
        cur += 4;
        break;
    case 0x16:
    case 0x18:
        cur += 1;
        break;
    default:
        *out = cur;
        return 0;
    }

    if (cur != end) {
        rem = (int)(end - cur);
        do {
            switch (s->m_class[*cur]) {
            case 5:
                if (rem < 2)
                    return -2;
                if (!s->m_14c(s, cur)) {
                    *out = cur;
                    return 0;
                }
                cur += 2;
                rem -= 2;
                break;
            case 6:
                if (rem < 3)
                    return -2;
                if (!s->m_150(s, cur)) {
                    *out = cur;
                    return 0;
                }
                cur += 3;
                rem -= 3;
                break;
            case 7:
                if (rem < 4)
                    return -2;
                if (!s->m_154(s, cur)) {
                    *out = cur;
                    return 0;
                }
                cur += 4;
                rem -= 4;
                break;
            case 9:
            case 10:
            case 0x0b:
            case 0x15:
            case 0x1e:
            case 0x20:
            case 0x24:
                *out = cur;
                return 0x14;
            case 0x16:
            case 0x18:
            case 0x19:
            case 0x1a:
            case 0x1b:
                cur += 1;
                rem -= 1;
                break;
            case 0x1d:
                *out = cur;
                return 0;
            default:
                *out = cur;
                return 0;
            }
        } while (cur != end);
    }
    return -0x14;
}

// @ 0x0090e890
int normalScanPast(NormalScanner* s, const byte* cur, const byte* end, unsigned matchClass, const byte** out)
{
    int rem;
    unsigned cls;

    if (cur == end)
        return -1;

    rem = (int)(end - cur);
    do {
        cls = s->m_class[*cur];
        switch (cls) {
        case 0:
        case 1:
        case 8:
            *out = cur;
            return 0;
        case 5:
            if (rem < 2)
                return -2;
            if (s->m_164(s, cur) != 0) {
                *out = cur;
                return 0;
            }
            cur += 2;
            rem -= 2;
            break;
        case 6:
            if (rem < 3)
                return -2;
            if (s->m_168(s, cur) != 0) {
                *out = cur;
                return 0;
            }
            cur += 3;
            rem -= 3;
            break;
        case 7:
            if (rem < 4)
                return -2;
            if (s->m_16c(s, cur) != 0) {
                *out = cur;
                return 0;
            }
            cur += 4;
            rem -= 4;
            break;
        case 0x0c:
        case 0x0d:
            cur += 1;
            rem -= 1;
            if (cls == matchClass) {
                if (cur != end) {
                    *out = cur;
                    switch (s->m_class[*cur]) {
                    case 9:
                    case 10:
                    case 0x0b:
                    case 0x14:
                    case 0x15:
                    case 0x1e:
                        return 0x1b;
                    default:
                        return 0;
                    }
                }
                return -0x1b;
            }
            break;
        default:
            cur += 1;
            rem -= 1;
            break;
        }
    } while (cur != end);

    return -1;
}

// @ 0x00911ae0
static int little2_scanPercent(const void* enc, const char* p, const char* e, const char** nextTokPtr)
{
  int t;
  if (p == e)
    return -22;
  t = byteType(enc, p);
  switch (t) {
  case BT_LEAD2:
    if (e - p < 2) return -2;
    break;
  case BT_LEAD3:
    if (e - p < 3) return -2;
    break;
  case BT_LEAD4:
    if (e - p < 4) return -2;
    break;
  case BT_TRAIL:
  case BT_GT: case BT_QUOT: case BT_APOS: case BT_EQUALS: case BT_QUEST:
  case BT_EXCL: case BT_SOL: case BT_SEMI: case BT_NUM: case BT_LSQB:
  case BT_COLON: case BT_DIGIT: case BT_NAME: case BT_MINUS: case BT_OTHER:
    break;
  case BT_CR:
  case BT_LF:
  case BT_S:
  case BT_PERCNT:
    *nextTokPtr = p;
    return 22;
  case BT_NMSTRT:
  case BT_HEX:
    goto consumed;
  case BT_NONASCII:
    if (UCS2_GET_NAMING(nmstrtPages, p[1], p[0]))
      goto consumed;
    break;
  default:
    break;
  }
  *nextTokPtr = p;
  return 0;

consumed:
  p += 2;
  if (p == e)
    return -1;
  for (;;) {
    t = byteType(enc, p);
    switch (t) {
    case BT_LEAD2:
      if (e - p < 2) return -2;
      goto invalid;
    case BT_LEAD3:
      if (e - p < 3) return -2;
      goto invalid;
    case BT_LEAD4:
      if (e - p < 4) return -2;
      goto invalid;
    case BT_SEMI:
      *nextTokPtr = p + 2;
      return 28;
    case BT_NMSTRT:
    case BT_HEX:
    case BT_DIGIT:
    case BT_NAME:
    case BT_MINUS:
      break;
    case BT_NONASCII:
      if (!UCS2_GET_NAMING(namePages, p[1], p[0]))
        goto invalid;
      break;
    default:
      goto invalid;
    }
    p += 2;
    if (p == e)
      return -1;
  }
invalid:
  *nextTokPtr = p;
  return 0;
}

// @ 0x00911c90
static int little2_scanPoundName(const void* enc, const char* p, const char* e, const char** nextTokPtr)
{
  int t;
  if (p == e)
    return -1;
  t = byteType(enc, p);
  switch (t) {
  case BT_DIGIT: case BT_NAME: case BT_MINUS: case BT_NMSTRT: case BT_HEX:
    break;
  case BT_NONASCII:
    if (!UCS2_GET_NAMING(nmstrtPages, p[1], p[0]))
      goto notName;
    break;
  case BT_LEAD2:
    if (e - p < 2) return -2;
    goto notName;
  case BT_LEAD3:
    if (e - p < 3) return -2;
    goto notName;
  case BT_LEAD4:
    if (e - p < 4) return -2;
    goto notName;
  default:
    goto notName;
  }
  for (;;) {
    p += 2;
    if (p == e)
      return -20;                               /* -XML_TOK_POUND_NAME */
    t = byteType(enc, p);
    switch (t) {
    case BT_DIGIT: case BT_NAME: case BT_MINUS: case BT_NMSTRT: case BT_HEX:
      break;
    case BT_NONASCII:
      if (!UCS2_GET_NAMING(namePages, p[1], p[0]))
        goto notName;
      break;
    case BT_LEAD2:
      if (e - p < 2) return -2;
      goto notName;
    case BT_LEAD3:
      if (e - p < 3) return -2;
      goto notName;
    case BT_LEAD4:
      if (e - p < 4) return -2;
      goto notName;
    default:
      goto notName;
    }
  }

notName:
  *nextTokPtr = p;
  return 20;                                    /* XML_TOK_POUND_NAME */
}

// @ 0x00911e40
static int little2_scanLit(int open, const void* enc, const char* p, const char* e, const char** nextTokPtr)
{
  while (p != e) {
    int t = byteType(enc, p);
    switch (t) {
    case BT_LEAD2:
      if (e - p < 2) return -2;
      goto invalid;
    case BT_LEAD3:
      if (e - p < 3) return -2;
      goto invalid;
    case BT_LEAD4:
      if (e - p < 4) return -2;
      goto invalid;
    case BT_QUOT:
    case BT_APOS:
      p += 2;
      if (t != open)
        break;
      if (p == e)
        return -27;                             /* -XML_TOK_LITERAL */
      *nextTokPtr = p;
      switch (byteType(enc, p)) {
      case BT_S: case BT_CR: case BT_LF:
      case BT_GT: case BT_PERCNT: case BT_LSQB:
        return 27;                              /* XML_TOK_OPEN_LIT */
      default:
        return 0;
      }
    case BT_LF:
    case BT_CR:
    case BT_GT:
    case BT_PERCNT:
    case BT_LSQB:
      goto invalid;
    default:
      p += 2;
      break;
    }
  }
  return -27;

invalid:
  *nextTokPtr = p;
  return 0;
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

// @ 0x009160a0
static void PTRCALL initUpdatePosition(const ENCODING *enc, const char *ptr, const char *end, POSITION *pos)
{
  normal_updatePosition(&utf8_encoding.enc, ptr, end, pos);
}

// @ 0x00916460
static int doParseXmlDecl(const ENCODING *(*encodingFinder)(const ENCODING *, const char *, const char *), int isGeneralTextEntity, const ENCODING *enc, const char *ptr, const char *end, const char **badPtr, const char **versionPtr, const char **versionEndPtr, const char **encodingName, const ENCODING **encoding_s0091_59b0, int *standalone)
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
    if (encoding_s0091_59b0)
      *encoding_s0091_59b0 = encodingFinder(enc, val, ptr - enc->minBytesPerChar);
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
  return UCS2_GET_NAMING_s0091_59b0(namePages, c >> 8, c & 0xFF);
}

// @ 0x00916890
static int PTRFASTCALL unknown_isNmstrt(const ENCODING *enc, const char *p)
{
  const struct unknown_encoding *uenc = (const struct unknown_encoding *)enc;
  int c = uenc->convert(uenc->userData, p);
  if (c & ~0xFFFF)
    return 0;
  return UCS2_GET_NAMING_s0091_59b0(nmstrtPages, c >> 8, c & 0xFF);
}

// @ 0x009168f0
static int PTRFASTCALL unknown_isInvalid(const ENCODING *enc, const char *p)
{
  const struct unknown_encoding *uenc = (const struct unknown_encoding *)enc;
  int c = uenc->convert(uenc->userData, p);
  return (c & ~0xFFFF) || checkCharRefNumber(c) < 0;
}

// @ 0x00916960
static void PTRCALL unknown_toUtf8(const ENCODING_s0091_6960 *enc, const char **fromP, const char *fromLim, char **toP, const char *toLim)
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

// @ 0x00916a70
ENCODING_s0091_6960 *XmlInitUnknownEncoding(void *mem, int *table, CONVERTER convert, void *userData)
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
    e->normal.isName2 = unknown_isName_s0091_6960;
    e->normal.isName3 = unknown_isName_s0091_6960;
    e->normal.isName4 = unknown_isName_s0091_6960;
    e->normal.isNmstrt2 = unknown_isNmstrt_s0091_6960;
    e->normal.isNmstrt3 = unknown_isNmstrt_s0091_6960;
    e->normal.isNmstrt4 = unknown_isNmstrt_s0091_6960;
    e->normal.isInvalid2 = unknown_isInvalid_s0091_6960;
    e->normal.isInvalid3 = unknown_isInvalid_s0091_6960;
    e->normal.isInvalid4 = unknown_isInvalid_s0091_6960;
  }
  e->normal.enc.utf8Convert = unknown_toUtf8;
  e->normal.enc.utf16Convert = unknown_toUtf16;
  return (ENCODING_s0091_6960 *)e;
}

// @ 0x00916cb0
static int unknown_encodingIndex(const char *name)
{
  int i;
  if (name == 0)
    return 6;
  for (i = 0; i < 6; ++i)
    if (streqci(name, (const char *)encodingNames[i]))
      return i;
  return -1;
}

// @ 0x00916cf0
static int unknown_scanProlog_body(const void *const *table, init_encoding_s0091_6960 *p, const char *ptr, const char *end, const char **nextTokPtr, int isGeneralTextEntity)
{
  const ENCODING_s0091_6960 *enc = &p->enc;
  ENCODING_s0091_6960 **out;
  const ENCODING_s0091_6960 *e2;
  SCANNER_s0091_6960 scan;
  unsigned int c;
  if (ptr == end)
    return -4;
  out = p->out;
  if (ptr + 1 == end) {
    unsigned char isUtf8 = (unsigned char)enc->isUtf8;
    if ((unsigned char)(isUtf8 - 3) <= 2)
      return -1;
    c = (unsigned char)ptr[0];
    if (c <= 0xEF) {
      if (c == 0xEF)
        goto oneLead;
      if (c == 0)
        return -1;
      if (c == 0x3C)
        return -1;
      goto dispatch;
    }
    if ((unsigned int)(c - 0xFE) > 1)
      goto dispatch;
  oneLead:
    if (enc->isUtf8 != 0)
      return -1;
    if (isGeneralTextEntity == 1)
      goto dispatch;
    return -1;
  }
  c = ((unsigned int)(unsigned char)ptr[0] << 8) | (unsigned char)ptr[1];
  if (c > 0xFEFF)
    goto gtFEFF;
  if (c == 0xFEFF)
    goto feff;
  if (c == 0x3C00)
    goto c3c00;
  if (c != 0xEFBB)
    goto def2;
  if (isGeneralTextEntity == 1) {
    int u = (signed char)enc->isUtf8;
    if (u == 0 || u == 3 || u == 4 || u == 5)
      goto dispatch;
  }
  if (ptr + 2 == end)
    return -1;
  if ((unsigned char)ptr[2] != 0xBF)
    goto dispatch;
  *nextTokPtr = ptr + 3;
  *out = (ENCODING_s0091_6960 *)table[2];
  return 0x0e;

c3c00:
  if (enc->isUtf8 == 3 || enc->isUtf8 == 4) {
    if (isGeneralTextEntity == 1)
      goto dispatch;
  }
  goto scan5;

feff:
  if (enc->isUtf8 == 0) {
    if (isGeneralTextEntity == 1)
      goto dispatch;
  }
  *nextTokPtr = ptr + 2;
  *out = (ENCODING_s0091_6960 *)table[4];
  return 0x0e;

gtFEFF:
  if (c == 0xFFFE)
    goto fffe;
def2:
  if ((unsigned char)ptr[0] == 0) {
    if (!(isGeneralTextEntity == 1 && enc->isUtf8 == 5))
      goto scan4;
    goto dispatch;
  }
  if ((unsigned char)ptr[1] == 0) {
    if (isGeneralTextEntity != 1)
      goto scan5;
  }
  goto dispatch;

fffe:
  if (enc->isUtf8 == 0 && isGeneralTextEntity == 1)
    goto dispatch;
  *nextTokPtr = ptr + 2;
  *out = (ENCODING_s0091_6960 *)table[5];
  return 0x0e;

scan4:
  e2 = (const ENCODING_s0091_6960 *)table[4];
  *out = (ENCODING_s0091_6960 *)e2;
  scan = e2->scanners[isGeneralTextEntity];
  return ((int (PTRCALL *)(const ENCODING_s0091_6960 *, const char *, const char *, const char **))scan)(e2, ptr, end, nextTokPtr);

scan5:
  e2 = (const ENCODING_s0091_6960 *)table[5];
  *out = (ENCODING_s0091_6960 *)e2;
  scan = e2->scanners[isGeneralTextEntity];
  return ((int (PTRCALL *)(const ENCODING_s0091_6960 *, const char *, const char *, const char **))scan)(e2, ptr, end, nextTokPtr);

dispatch:
  e2 = (const ENCODING_s0091_6960 *)table[(signed char)enc->isUtf8];
  *out = (ENCODING_s0091_6960 *)e2;
  scan = e2->scanners[isGeneralTextEntity];
  return ((int (PTRCALL *)(const ENCODING_s0091_6960 *, const char *, const char *, const char **))scan)(e2, ptr, end, nextTokPtr);
}

// @ 0x00916f10
static int PTRCALL unknown_scanS_default(const ENCODING_s0091_6960 *enc, const char *ptr, const char *end, const char **nextTokPtr)
{
  return unknown_scanProlog_body((const void *const *)encodingListDefault,
                                 (init_encoding_s0091_6960 *)enc, ptr, end, nextTokPtr, 0);
}

// @ 0x00916f40
static int PTRCALL unknown_scanS_ns(const ENCODING_s0091_6960 *enc, const char *ptr, const char *end, const char **nextTokPtr)
{
  return unknown_scanProlog_body((const void *const *)encodingListDefault,
                                 (init_encoding_s0091_6960 *)enc, ptr, end, nextTokPtr, 1);
}

// @ 0x00916f70
int XmlInitEncoding(init_encoding_s0091_6960 *p, ENCODING_s0091_6960 **encoding, const char *name)
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
  p->enc.isUtf8 = (char)i;
  p->enc.scanners[0] = (SCANNER_s0091_6960)unknown_scanS_default;
  p->enc.scanners[1] = (SCANNER_s0091_6960)unknown_scanS_ns;
  p->enc.updatePosition = pushPosition;
  p->out = encoding;
  *encoding = &p->enc;
  return 1;
}

// @ 0x00916fe0
const ENCODING_s0091_6960 *findEncodingDefault(const ENCODING_s0091_6960 *enc, const char *ptr, const char *end)
{
  char name[128];
  char *nameEnd = name;
  enc->utf8Convert(enc, &ptr, end, &nameEnd, name + sizeof(name) - 1);
  if (ptr == end) {
    int i;
    *nameEnd = 0;
    if (streqci(name, kUTF16Name) != 0 && enc->minBytesPerChar == 2)
      return enc;
    i = unknown_encodingIndex(name);
    if (i != -1)
      return (const ENCODING_s0091_6960 *)encodingListDefault[i];
  }
  return 0;
}

// @ 0x00917080
int XmlInitEncodingNS_x(int isGeneralTextEntity, const ENCODING_s0091_6960 *enc, const char *ptr, const char *end, const char **badPtr, const char **versionPtr, const char **versionEndPtr, const char **encodingName, const ENCODING_s0091_6960 **encoding, int *standalone)
{
  return doParseXmlDecl(findEncodingDefault, isGeneralTextEntity, enc, ptr, end, badPtr,
                        versionPtr, versionEndPtr, encodingName, encoding, standalone);
}

// @ 0x009170d0
static int PTRCALL unknown_scanPD_default(const ENCODING_s0091_6960 *enc, const char *ptr, const char *end, const char **nextTokPtr)
{
  return unknown_scanProlog_body((const void *const *)encodingListNS,
                                 (init_encoding_s0091_6960 *)enc, ptr, end, nextTokPtr, 0);
}

// @ 0x00917100
static int PTRCALL unknown_scanPD_ns(const ENCODING_s0091_6960 *enc, const char *ptr, const char *end, const char **nextTokPtr)
{
  return unknown_scanProlog_body((const void *const *)encodingListNS,
                                 (init_encoding_s0091_6960 *)enc, ptr, end, nextTokPtr, 1);
}

// @ 0x00917130
int XmlInitEncodingNS(init_encoding_s0091_6960 *p, ENCODING_s0091_6960 **encoding, const char *name)
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
  p->enc.isUtf8 = (char)i;
  p->enc.scanners[0] = (SCANNER_s0091_6960)unknown_scanPD_default;
  p->enc.scanners[1] = (SCANNER_s0091_6960)unknown_scanPD_ns;
  p->enc.updatePosition = pushPosition;
  p->out = encoding;
  *encoding = &p->enc;
  return 1;
}

// @ 0x009171a0
const ENCODING_s0091_6960 *findEncodingNS(const ENCODING_s0091_6960 *enc, const char *ptr, const char *end)
{
  char name[128];
  char *nameEnd = name;
  enc->utf8Convert(enc, &ptr, end, &nameEnd, name + sizeof(name) - 1);
  if (ptr == end) {
    int i;
    *nameEnd = 0;
    if (streqci(name, kUTF16Name) != 0 && enc->minBytesPerChar == 2)
      return enc;
    i = unknown_encodingIndex(name);
    if (i != -1)
      return (const ENCODING_s0091_6960 *)encodingListNS[i];
  }
  return 0;
}

// @ 0x00917240
int XmlInitEncodingNS_x2(int isGeneralTextEntity, const ENCODING_s0091_6960 *enc, const char *ptr, const char *end, const char **badPtr, const char **versionPtr, const char **versionEndPtr, const char **encodingName, const ENCODING_s0091_6960 **encoding, int *standalone)
{
  return doParseXmlDecl(findEncodingNS, isGeneralTextEntity, enc, ptr, end, badPtr,
                        versionPtr, versionEndPtr, encodingName, encoding, standalone);
}

// @ 0x00917280
ENCODING_s0091_6960 *XmlInitUnknownEncodingNS(void *mem, int *table, CONVERTER convert, void *userData)
{
  ENCODING_s0091_6960 *e = XmlInitUnknownEncoding(mem, table, convert, userData);
  if (e)
    ((char *)e)[0x86] = 0x17;   // retail writes BT_COLON here, not BT_NMSTRT
  return e;
}

// @ 0x009172b0
int PTRFASTCALL unknown_charRefNumber_little(const ENCODING_s0091_6960 *enc, const char *ptr)
{
  int result = 0;
  (void)enc;
  ptr += 2;
  if (*ptr == 'x') {
    for (;;) {
      char c;
      ptr += 1;
      c = *ptr;
      if (c == ';')
        break;
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
      }
      if (result >= 0x110000)
        return -1;
    }
  }
  else {
    for (;;) {
      char c = *ptr;
      if (c == ';')
        break;
      result = result * 10 + c - '0';
      if (result >= 0x110000)
        return -1;
      ptr += 1;
    }
  }
  return checkCharRefNumber_s0091_6960(result);
}

// @ 0x009173c0
int PTRFASTCALL unknown_charRefNumber_big(const ENCODING_s0091_6960 *enc, const char *ptr)
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
  return checkCharRefNumber_s0091_6960(result);
}

// @ 0x009174e0
int PTRFASTCALL unknown_charRefNumber_utf16(const ENCODING_s0091_6960 *enc, const char *ptr)
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
  return checkCharRefNumber_s0091_6960(result);
}
