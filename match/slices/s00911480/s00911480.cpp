// Slice s00911480 (hk2 slice 32). little2_scanPercent at 0x00911ae0 (expat UTF-16LE scanner).
// Byte-type helpers and naming tables are the same ones used by the sibling big2/little2 slices.
#include "types.h"

enum {
  BT_NONXML, BT_MALFORM, BT_LT, BT_AMP, BT_RSQB, BT_LEAD2, BT_LEAD3, BT_LEAD4,
  BT_TRAIL, BT_CR, BT_LF, BT_GT, BT_QUOT, BT_APOS, BT_EQUALS, BT_QUEST,
  BT_EXCL, BT_SOL, BT_SEMI, BT_NUM, BT_LSQB, BT_S, BT_NMSTRT, BT_COLON,
  BT_HEX, BT_DIGIT, BT_NAME, BT_MINUS, BT_OTHER, BT_NONASCII, BT_PERCNT,
  BT_LPAR, BT_RPAR, BT_AST, BT_PLUS, BT_COMMA, BT_VERBAR
};

extern const unsigned char namePages[256];      // 0x143b428
extern const unsigned char nmstrtPages[256];    // 0x143b328
extern const unsigned int  namingBitmap[];      // 0x143ae28

// enc->type[] sits at +0x4c in the ENCODING layout (see normal_encoding in the sibling slice).
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

// Little-endian UTF-16: the low byte is p[0], the high byte p[1].
static int byteType(const void* enc, const char* p) {
  if (p[1] == 0)
    return ENC_TYPE(enc, p[0]);
  return unicode_byte_type(p[1], p[0]);
}

// 0x00911ae0
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

// Non-static entry so the register-convention static above is emitted (the object keeps only referenced statics).
int little2_scanPercent_entry(const void* enc, const char* p, const char* e, const char** nextTokPtr) {
  return little2_scanPercent(enc, p, e, nextTokPtr);
}
