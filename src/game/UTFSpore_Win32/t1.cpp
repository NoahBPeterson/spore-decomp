// src/game/UTFSpore_Win32/t1.cpp -- migrated from slice(s) s008bad10, s008b9e10, s008b81a0, s008b6400, s008b8f30, s008b71c0 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/t1.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern "C" int   util_FixMul(int a, int b);                                    // 0x008d1590
extern "C" void Delete_GlyphClass(void* g);                                    // 0x008b0280

// ---- items of slice s008b71c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef uint8_t uint8;
typedef int16_t int16;
typedef uint32_t uint32;
struct tsiMemObject;
extern "C" void* tsi_AllocMem(tsiMemObject* mem, uint32 size);                 // 0x008d1260
extern "C" void* tsi_ReAllocMem(tsiMemObject* mem, void* p, uint32 size);      // 0x008d1330
extern "C" int   util_FixMul(int a, int b);                                    // 0x008d1590
struct GlyphBuilder {
    char   pad0[0x36];
    int16  compFlag;             // 0x36
    int16  contour;              // 0x38
    char   pad3a[0x44 - 0x3a];
    int16* xPts;                 // 0x44
    int16* yPts;                 // 0x48
    char   pad4c[0x58 - 0x4c];
    int16* compData;             // 0x58
    int    compCount;            // 0x5c
    int    compCap;              // 0x60
};
extern "C" void glyph_AddPoint(GlyphBuilder* g, int x, int y, int onCurve);    // 0x008b0320
extern "C" void glyph_CloseContour(GlyphBuilder* g);                           // 0x008afde0
extern "C" void glyph_StartLine(GlyphBuilder* g, int x, int y);                // 0x008b0440 (FUN_008b0440)
extern "C" void Delete_GlyphClass(void* g);                                    // 0x008b0280
struct T1Outline {
    tsiMemObject* mem;           // 0x000
    char   pad4[0x2c0 - 4];
    int16* xAll;                 // 0x2c0
    int16  capXAll, pad2c6;      // 0x2c4
    int16* yAll;                 // 0x2c8
    int16  capYAll, pad2ce;      // 0x2cc
    char   pad2d0[0x2e0 - 0x2d0];
    int16* xPts;                 // 0x2e0
    int16  capXPts, cntXPts;     // 0x2e4, 0x2e6
    int16* yPts;                 // 0x2e8
    int16  capYPts, cntYPts;     // 0x2ec, 0x2ee
};
struct T1Class {
    tsiMemObject* mem;           // 0x00
    char   pad04[0x18 - 4];
    int    curX;                 // 0x18
    int    curY;                 // 0x1c
    int    inFlex;               // 0x20
    int    flexCount;            // 0x24
    int16  charBase;             // 0x28
    char   pad2a[6];
    int16  numGlyphs;            // 0x30
    char   pad32[6];
    int16* adobeCodes;           // 0x38
    char   pad3c[4];
    int16  numSubrs;             // 0x40
    char   pad42[2];
    uint8** subrs;               // 0x44
    int16  sp;                   // 0x48
    char   pad4a[2];
    int    stack[0x20];          // 0x4c
    char   padcc_[0xcc - 0xcc];
};
static inline int  T1_numMasters(T1Class* t)  { return *(int*)((char*)t + 0xcc); }
static inline int* T1_weights(T1Class* t)     { return (int*)((char*)t + 0xd8); }
static inline GlyphBuilder*& T1_glyph(T1Class* t) { return *(GlyphBuilder**)((char*)t + 0x1cc); }
static inline int& T1_sbx(T1Class* t) { return *(int*)((char*)t + 0x1d0); }
static inline int& T1_sby(T1Class* t) { return *(int*)((char*)t + 0x1d4); }
static inline int& T1_wx(T1Class* t)  { return *(int*)((char*)t + 0x1d8); }
static inline int& T1_wy(T1Class* t)  { return *(int*)((char*)t + 0x1dc); }
extern "C" int    backwardsATOI(uint8* p);                                     // 0x008b6b50
extern "C" int    T1GetGlyphIndexFromAdobeCode(T1Class* t, int16 code);        // 0x008b71a0 (eax=t, si=code)
extern "C" void*  T1GetGlyphByIndex(T1Class* t, int idx, void* a, void* b, int c, int d); // 0x008b8230
// ---- items of slice s008b71c0 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern "C" void* tsi_AllocMem(tsiMemObject* mem, uint32 size);                 // 0x008d1260
extern "C" void* tsi_ReAllocMem(tsiMemObject* mem, void* p, uint32 size);      // 0x008d1330
extern "C" void glyph_AddPoint(GlyphBuilder* g, int x, int y, int onCurve);    // 0x008b0320
extern "C" void glyph_CloseContour(GlyphBuilder* g);                           // 0x008afde0
extern "C" void glyph_StartLine(GlyphBuilder* g, int x, int y);                // 0x008b0440 (FUN_008b0440)
extern "C" int    backwardsATOI(uint8* p);                                     // 0x008b6b50
extern "C" int    T1GetGlyphIndexFromAdobeCode(T1Class* t, int16 code);        // 0x008b71a0 (eax=t, si=code)
extern "C" void*  T1GetGlyphByIndex(T1Class* t, int idx, void* a, void* b, int c, int d); // 0x008b8230

// ---- items of slice s008b8f30 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void  FUN_008cfac0(void* pairs, int n);                                                  // 0x008cfac0
typedef uint16_t uint16;
struct T1Class_s008b_8f30;
struct T1CharStrings;
extern "C" uint32 tsi_PSNameToAppleCode(uint8* name, uint16* code, uint16* a, uint16* b);           // 0x008b6f90
extern "C" void  T1Error(tsiMemObject* mem, int code);                                              // 0x008d10c0
extern "C" T1CharStrings* T1NewCharStrings(tsiMemObject* mem, int count, void* callback, T1Class_s008b_8f30* owner); // 0x008d1a00
extern "C" void  T1AddCharString(T1CharStrings* table, uint32 name, uint16 code, uint16 length);     // 0x008d1c50
struct T1CharStringEntry {
    uint32 name;                 // 0x00
    uint16 code;                 // 0x04
    uint16 length;               // 0x06
};
struct T1CharStrings {
    char   pad00[0x24];
    T1CharStringEntry* entries;  // 0x24
    uint32 capacity;             // 0x28
    uint32 count;                // 0x2c
};
struct T1Class_s008b_8f30 {
    tsiMemObject* mem;           // 0x00
    char   pad04[4];
    uint8* base;                 // 0x08
    uint32 size;                 // 0x0c
    uint32 field10;              // 0x10
    uint32 field14;              // 0x14
    char   pad18[0x14];
    uint8* encoding;             // 0x2c
    int16  numGlyphs;            // 0x30
    int16* glyphMap;             // 0x34
    int16* adobeCodes;           // 0x38
    uint32* charStringOffsets;   // 0x3c
    char   pad40[0x214 - 0x40];
    uint32 field214;             // 0x214
    uint16 field218;             // 0x218
    uint16 field21a;             // 0x21a
    T1CharStrings* charStrings;  // 0x21c
};
struct KernPair {
    uint32 key;                  // left << 16 | right glyph index
    int16  value;
    int16  pad;
};
struct kernSubTable0Data {
    tsiMemObject* mem;           // 0x00
    uint16 numPairs;             // 0x04
    uint16 pad6;                 // 0x06
    uint16 pad8;                 // 0x08
    uint16 pad10;                // 0x0a
    KernPair* pairs;             // 0x0c
};
static int ATOI(const uint8* p)
{
    uint16 v = 0;
    uint8 sign;
    for (;;) {
        sign = *p;
        if (sign >= '0' && sign <= '9')
            break;
        if (sign == '-')
            break;
        ++p;
    }
    if (sign == '-')
        ++p;
    uint8 c = *p;
    while (c >= '0' && c <= '9') {
        v = (uint16)(v * 10 + c - '0');
        c = *++p;
    }
    int r = (int16)v;
    if (sign == '-')
        r = -r;
    return r;
}
static inline unsigned HexDigitValue(uint8 c, unsigned dflt)
{
    if ((uint8)(c - '0') <= 9)
        return (uint16)((int16)(char)c - 0x30);
    if ((uint8)(c - 'A') <= 5)
        return (uint16)((int16)(char)c - 0x37);
    if ((uint8)(c - 'a') <= 5)
        return (uint16)((int16)(char)c - 0x57);
    return dflt;
}
#define SKIP_CHAR(ch)  for (; *s == (ch) && n < limit; ++n) ++s;
#define COPY_TOKEN(buf, term)                \
    {                                        \
        uint8 c_ = *s;                       \
        int k_ = 0;                          \
        for (; c_ != (term) && k_ < 0x3f; ++k_) { \
            ++s;                             \
            (buf)[k_] = c_;                  \
            c_ = *s;                         \
        }                                    \
        (buf)[k_] = 0;                       \
    }
#define FIND_INDEX(out, tblp, count, val)            \
    {                                                \
        int ix_ = 0;                                 \
        for (; ix_ < (count); ++ix_)                 \
            if ((tblp)[ix_] == (int16)(val)) break;  \
        (out) = ix_;                                 \
    }
#define SKIP_TO_SPACE_COUNTING_PAIR()                                  \
    for (; *s != ' ' && (int)i < limit; ++i) ++s;
#define STORE_PAIR(hi, lo, val)                                       \
    {                                                                 \
        result->pairs[i].key = ((uint32)(uint16)(hi) << 16) | (uint16)(lo); \
        result->pairs[i].value = (val);                               \
    }
struct kernSubTable0 {
    tsiMemObject* mem;           // 0x00
    uint16 flags4;               // 0x04
    uint16 pad6;                 // 0x06
    uint32 length;               // 0x08
    uint16 format;               // 0x0c
    uint16 padE;                 // 0x0e
    kernSubTable0Data* data;     // 0x10
};
struct kernSubTable {
    tsiMemObject* mem;           // 0x00
    uint16 flags4;               // 0x04
    uint16 pad6;                 // 0x06
    uint32 numTables;            // 0x08
    kernSubTable0** tables;      // 0x0c
};
// ---- items of slice s008b8f30 end

// ---- items of slice s008b6400 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" int __cdecl strcmp(const char*, const char*);
#pragma intrinsic(strcmp)
extern "C" void  tsi_DeAllocMem(tsiMemObject*, void*);                         // 0x008d1440
struct GlyphPoints {
    char   pad00[0x38];
    int16  count;                 // 0x38
    char   pad3a[0x48 - 0x3a];
    int16* pts;                   // 0x48
};
struct ContourData {
    char   pad00[0x36];
    int16  numContours;           // 0x36
    char   pad38[0x3c - 0x38];
    int16* starts;                // 0x3c
    int16* ends;                  // 0x40
    int16* xPts;                  // 0x44
    int16* yPts;                  // 0x48
    uint8* flags;                 // 0x4c
};
static inline int ff_ishex(uint8 c)
{
    return (c >= '0' && c <= '9') || (c >= 'A' && c <= 'F') || (uint8)(c - 'a') < 6;
}
static inline uint8 ff_nib(uint8 c)
{
    return c <= '9' ? (uint8)(c - '0') : (c <= 'F' ? (uint8)(c - 0x37) : (uint8)(c - 0x57));
}
struct T1Blob {
    tsiMemObject* mem;            // 0x00
    int   f4;                     // 0x04
    int   base;                   // 0x08
    int   limit;                  // 0x0c
    int   off;                    // 0x10
    char  pad14[0x2c - 0x14];
    char* str;                    // 0x2c
};
// ---- items of slice s008b6400 end

// ---- items of slice s008b81a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" __declspec(dllimport) int __cdecl strncmp(const char*, const char*, unsigned int);
extern "C" char* GetNthNameFromEncodingVector(void*, int);            // 0x008b7130 (object in ebx)
extern "C" int   get_using_uint16_hashClass(void*, int, void*);       // 0x008d1ac0
typedef int32_t int32;
extern "C" int16 backwardsATOI_s008b_81a0(const uint8*);                         // 0x008b6b50
extern "C" int16 ATOI_s008b_81a0(const uint8*);                                  // 0x008b6a20
extern "C" int   ATOFixed(const uint8*, int);                         // 0x008b6a70
extern "C" char* tsi_T1Find_s008b_81a0(void*, const char*, int, int);            // 0x008b6e90
struct GlyphBuilder_s008b_81a0 {
    char   pad00[0x34];
    int16  f34;                  // 0x34
    int16  compFlag;             // 0x36
    int16  contour;              // 0x38
    char   pad3a[0x44 - 0x3a];
    int16* xPts;                 // 0x44
    int16* yPts;                 // 0x48
};
struct T1HashEntry {
    int32  pad;                  // 0x00
    int16  code;                 // 0x04
    int16  value;                // 0x06
};
struct T1Hash {
    char          pad00[0x24];
    T1HashEntry*  table;         // 0x24
    int32         pad28;         // 0x28
    int32         count;         // 0x2c
};
struct T1Class_s008b_81a0 {
    tsiMemObject* mem;           // 0x00
    int32   f04;                 // 0x04
    int32   base;                // 0x08
    int32   len;                 // 0x0c
    int32   off;                 // 0x10
    int32   limit;               // 0x14
    int32   curX;                // 0x18
    int32   curY;                // 0x1c
    int32   inFlex;              // 0x20
    int32   flexCount;           // 0x24
    int16   charBase;            // 0x28
    int16   pad2a;               // 0x2a
    char*   str;                 // 0x2c
    int16   numGlyphs;           // 0x30
    int16   pad32;               // 0x32
    int16*  codes;               // 0x34
    int16*  adobeCodes;          // 0x38
    void**  charStrings;         // 0x3c
    int16   numSubrs;            // 0x40
    int16   pad42;               // 0x42
    void**  subrs;               // 0x44
    int16   sp;                  // 0x48
    int16   pad4a;               // 0x4a
    int32   stack[0x20];         // 0x4c
    int32   numMasters;          // 0xcc
    int32   m_d0;                // 0xd0
    int32   weights[16];         // 0xd4
    int32   blueValues[14];      // 0x114
    int32   m_14c;               // 0x14c
    int32   m_150;               // 0x150
    int32   m_154;               // 0x154
    int32   m_158;               // 0x158
    int32   stemSnapH[12];       // 0x15c
    int32   m_18c;               // 0x18c
    int32   stemSnapV[12];       // 0x190
    int32   m_1c0;               // 0x1c0
    int32   m_1c4;               // 0x1c4
    int32   m_1c8;               // 0x1c8
    GlyphBuilder_s008b_81a0* glyph;         // 0x1cc
    int32   sbx;                 // 0x1d0
    int32   sby;                 // 0x1d4
    int32   wx;                  // 0x1d8
    int32   wy;                  // 0x1dc
    int32   m_1e0;               // 0x1e0
    int32   m_1e4;               // 0x1e4
    int32   m_1e8;               // 0x1e8
    int32   m_1ec;               // 0x1ec
    int32   m_1f0;               // 0x1f0
    int32   m_1f4;               // 0x1f4
    int32   m_1f8;               // 0x1f8
    int32   m_1fc;               // 0x1fc
    int32   m_200;               // 0x200
    int32   m_204;               // 0x204
    int32   m_208;               // 0x208
    int32   m_20c;               // 0x20c
    int32   m_210;               // 0x210
    int32   m_214;               // 0x214
    char    pad218[0x21c - 0x218];
    T1Hash* hashClass;           // 0x21c
    int32   found;               // 0x220
};
struct T1NameEntry {
    const char* name;            // 0x00
    char        pad04[12];
};
extern "C" T1NameEntry g_t1NameTable[];   // 0x014338d4
// ---- items of slice s008b81a0 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
extern "C" void* tsi_T1GetGlyphByIndex(T1Class_s008b_81a0* t, uint16 idx, int16* outX, int16* outW, int p5, int p6);  // 0x008b8230 (stays in the slice: not this object's)

// forward declarations: helpers defined later in VA order (rewrite.py forward_protos)
static uint8* FindString(uint8* hay, const char* needle, int n, int start);   // defined at 0x008b9390, called earlier in the TU

// ---- items of slice s008b9e10 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void  Delete_hashClass(void*);                              // 0x008d1cb0
extern "C" void  PrimeT2KInputStream(void*);                           // 0x008cc0b0
extern "C" void  tsi_Error(void*, int);                                // 0x008d10c0
struct TsiStream {
    uint8*  ptr;                 // 0x000 current window (0 => pull through fn)
    int   (*fn)(int, uint8*, int, int);  // 0x004 refill callback (arg, dst, pos, n)
    int     arg;                 // 0x008 callback argument
    uint8   byte;                // 0x00c one-byte landing pad
    char    pad00d[0x214 - 0x00d];
    uint32  size;                // 0x214 primed window size
    int     primeBase;           // 0x218 window base
    int     curpos;              // 0x21c read cursor
    char    pad220[0x22c - 0x220];
    tsiMemObject* errctx;        // 0x22c error/memory context
    char    pad230[0x238 - 0x230];
    uint8   flag;                // 0x238 raw-mode flag
};
struct T1Class_s008b_9e10 {
    tsiMemObject* mem;           // 0x00
    int32   f04;                 // 0x04
    int32   base;                // 0x08
    int32   len;                 // 0x0c
    int32   off;                 // 0x10
    int32   limit;               // 0x14
    char    pad18[0x28 - 0x18];
    int16   charBase;            // 0x28
    char    pad2a[0x34 - 0x2a];
    int16*  codes;               // 0x34
    int16*  adobeCodes;          // 0x38
    void**  charStrings;         // 0x3c
    char    pad40[0x44 - 0x40];
    void**  subrs;               // 0x44
    char    pad48[0x1cc - 0x48];
    void*   glyph;               // 0x1cc
    char    pad1d0[0x21c - 0x1d0];
    void*   hashClass;           // 0x21c
};
static uint8 ts_readByte(TsiStream* s)
{
    if (s->ptr == 0) {
        int pos = s->curpos;
        s->curpos = pos + 1;
        if (s->fn(s->arg, &s->byte, pos, 1) < 0) {
            tsi_Error(s->errctx, 0x2728);
            return 0;
        }
        return s->byte;
    }
    if (s->fn == 0)
        return s->ptr[s->curpos++];
    if ((uint32)(s->curpos - s->primeBase + 1) > s->size)
        PrimeT2KInputStream(s);
    return s->ptr[s->curpos++ - s->primeBase];
}
// ---- items of slice s008b9e10 end

// ---- items of slice s008bad10 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" int   Tell_InputStream(void*);                              // 0x008cc5b0
extern "C" void  Seek_InputStream(void*, int);                         // 0x008cc580
extern "C" int   PeekInt16(void*, void*, int);                         // 0x008cc220
extern "C" int16 ReadInt16(void*);                                     // 0x008cc190
extern "C" uint8  ReadOfffset1_s008b_ad10(void*);                                 // 0x008b9fa0
extern "C" int16  ReadOfffset2_s008b_ad10(void*);                                 // 0x008ba050
extern "C" uint32 ReadOfffset3_s008b_ad10(void*);                                 // 0x008ba1c0
extern "C" int32  ReadOfffset4_s008b_ad10(void*);                                 // 0x008ba3d0
extern "C" int    READ_REAL_s008b_ad10(void*);                                    // 0x008ba680
extern "C" uint32 READ_INTEGER_s008b_ad10(void*, int);                            // 0x008ba7c0
struct TsiStream_s008b_ad10 {
    uint8*  ptr;                 // 0x000
    int   (*fn)(int, uint8*, int, int);  // 0x004
    int     arg;                 // 0x008
    uint8   byte;                // 0x00c
    char    pad00d[0x214 - 0x00d];
    uint32  size;                // 0x214
    int     primeBase;           // 0x218
    int     curpos;              // 0x21c
    char    pad220[0x22c - 0x220];
    tsiMemObject* errctx;        // 0x22c
};
struct CFFIndex {
    tsiMemObject* mem;           // 0x00
    int     f04;                 // 0x04 absolute data base
    uint8   offSize;             // 0x08 offset width
    char    pad09[0x0c - 0x09];
    int*    offsets;             // 0x0c decoded offsets (count+1 entries)
    int16   count;               // 0x10
};
struct CFFTopDict {
    int16   f00, f02, f04, f06, f08;                    // 0x00
    int32   f0c;                                        // 0x0c
    int32   f10, f14, f18, f1c;                         // 0x10
    int32   f20, f24;                                   // 0x20
    int32   f28, f2c;                                   // 0x28
    uint8   f30;                                        // 0x30
    char    pad31[0x34 - 0x31];
    int32   f34, f38, f3c;                              // 0x34
    int32   f40, f44;                                   // 0x40
    int32   f48, f4c, f50, f54;                         // 0x48
    union {                                             // 0x58
        int32 copy[65];                                 //   operand copy (0x58..0x15c)
        struct { char _p[0x40]; int16 lo, hi; } v;      //   0x98/0x9a view of the copy
    } bbox;
    char    pad9c[0x15c - 0x9c];
    int32   f15c, f160, f164, f168;                     // 0x15c
    uint8   f16c;                                       // 0x16c
};
struct CFFClass {
    char    pad00[4];
    TsiStream_s008b_ad10* stream;           // 0x004
    char    pad08[0x238 - 0x08];
    int     nameIndex;           // 0x238
    char    pad23c[0x374 - 0x23c];
    CFFIndex* nameIdx;           // 0x374
};
static uint8 ts_readByte_s008b_ad10(TsiStream_s008b_ad10* s)
{
    if (s->ptr == 0) {
        int pos = s->curpos;
        s->curpos = pos + 1;
        if (s->fn(s->arg, &s->byte, pos, 1) < 0) {
            tsi_Error(s->errctx, 0x2728);
            return 0;
        }
        return s->byte;
    }
    if (s->fn == 0)
        return s->ptr[s->curpos++];
    if ((uint32)(s->curpos - s->primeBase + 1) > s->size)
        PrimeT2KInputStream(s);
    return s->ptr[s->curpos++ - s->primeBase];
}
// ---- items of slice s008bad10 end

// @ 0x008b68c0
static int16 GetGlyphYMax(GlyphPoints* g)
{
    int16* p = g->pts;
    int n = g->count;
    int16 m = p[0];
    int i = 1;
    if (n > 1) {
        do {
            int16 v = p[i];
            if (m < v)
                m = v;
            ++i;
        } while (i < n);
    }
    return m;
}

// @ 0x008b68f0
static int16 GetGlyphYMin(GlyphPoints* g)
{
    int16* p = g->pts;
    int n = g->count;
    int16 m = p[0];
    int i = 1;
    if (n > 1) {
        do {
            int16 v = p[i];
            if (v < m)
                m = v;
            ++i;
        } while (i < n);
    }
    return m;
}

// @ 0x008b6920
extern "C" void FlipContourDirection(ContourData* d)
{
    uint8* flags = d->flags;
    int16* xPts = d->xPts;
    int16* yPts = d->yPts;
    int c = 0;
    while (c < d->numContours) {
        int16 start = d->starts[c];
        int16 end = d->ends[c];
        int n = (int16)((end - start) / 2);
        int i = 0;
        while (i < n) {
            int16 lo = (int16)(start + 1 + i);
            int16 hi = (int16)(end - i);
            int16 sx = xPts[lo];
            int16 sy = yPts[lo];
            uint8 sf = flags[lo];
            xPts[lo] = xPts[hi];
            yPts[lo] = yPts[hi];
            flags[lo] = flags[hi];
            xPts[hi] = sx;
            yPts[hi] = sy;
            flags[hi] = sf;
            ++i;
        }
        ++c;
    }
}

// @ 0x008b6bb0
static int DecryptData(uint8* data, int len)
{
    uint16 r = 0xd971;
    uint16 r2 = 0;
    int16 count = 0;
    int i;
    uint8 X = 0, Y = 0, Z = 0;

    if (!ff_ishex(data[0]) || !ff_ishex(data[1]) || !ff_ishex(data[2]) || !ff_ishex(data[3])) {
        if (len <= 0)
            return len;
        for (i = 0; i < len; ++i) {
            uint8 Xp = X, Yp = Y, Zp = Z;
            uint8 b = data[i];
            uint8 dec = (uint8)(r >> 8) ^ b;
            uint16 sum = (uint16)(b + r);
            X = Yp;
            Z = Xp;
            r = (uint16)(0x58bf - sum * (uint16)0x3193);
            if (count == 0) {
                Y = dec;
                data[i] = dec;
                if (Zp == ' ' && dec == ' ') {
                    if ((Xp == 'R' && Yp == 'D') || (Xp == '-' && Yp == '|')) {
                        count = (int16)backwardsATOI(data + i - 4);
                        r2 = 0x10ea;
                    }
                }
            } else {
                uint8 dec2 = (uint8)(r2 >> 8) ^ dec;
                --count;
                r2 = (uint16)(0x58bf - (uint16)(dec + r2) * (uint16)0x3193);
                Y = dec2;
                data[i] = dec2;
            }
        }
        return len;
    }

    {
        int out = 0;
        i = 0;
        while (i < len) {
            uint8 c1;
            do { c1 = data[i++]; } while (c1 == ' ' || c1 == '\n' || c1 == '\r' || c1 == '\t');
            uint8 c2;
            do { c2 = data[i++]; } while (c2 == ' ' || c2 == '\n' || c2 == '\r' || c2 == '\t');
            uint8 b = (uint8)((ff_nib(c1) << 4) | ff_nib(c2));
            uint8 Xp = X, Yp = Y, Zp = Z;
            uint8 dec = (uint8)(r >> 8) ^ b;
            uint16 sum = (uint16)(b + r);
            X = Yp;
            Z = Xp;
            r = (uint16)(0x58bf - sum * (uint16)0x3193);
            if (count == 0) {
                Y = dec;
                data[out] = dec;
                if (Zp == ' ' && dec == ' ') {
                    if ((Xp == 'R' && Yp == 'D') || (Xp == '-' && Yp == '|')) {
                        count = (int16)backwardsATOI(data + out - 4);
                        r2 = 0x10ea;
                    }
                }
            } else {
                uint8 dec2 = (uint8)(r2 >> 8) ^ dec;
                --count;
                r2 = (uint16)(0x58bf - (uint16)(dec + r2) * (uint16)0x3193);
                Y = dec2;
                data[out] = dec2;
            }
            ++out;
        }
        return i;
    }
}

// @ 0x008b6e90
extern "C" char* tsi_T1Find(T1Blob* blob, const char* needle, int start, int limit)
{
    char* p = (char*)needle;
    while (*p++)
        ;
    int len = (int)(p - (char*)needle) - 1;
    if (limit <= start)
        return 0;
    char* base = (char*)blob->base;
    do {
        char* hay = base + start;
        if (*needle == *hay) {
            int k = 1;
            if (len <= 1)
                return base + start + k;
            while (hay[k] == needle[k]) {
                ++k;
                if (len <= k)
                    return base + start + k;
            }
        }
        ++start;
        if (limit <= start)
            return 0;
    } while (1);
}

// @ 0x008b6f00
static int TransformData(T1Blob* ctx, uint8* base, int length, int which)
{
    ctx->f4 = (int)base;
    ctx->base = (int)base;
    ctx->limit = length;
    ctx->off = length;
    char* p = tsi_T1Find(ctx, "ntfile eexec", 0, length);
    if (p == 0) {
        if (base != 0) {
            tsi_DeAllocMem(ctx->mem, base);
            ctx->base = 0;
        }
        return 0xffff;
    }
    ctx->off = 0;
    while (*p == '\r' || *p == '\n')
        ++p;
    int skip = (int)p - (int)base;
    ctx->off = skip;
    if (which == 0x14 && skip > 0) {
        int n = DecryptData((uint8*)p, length - skip);
        ctx->limit = n + skip;
    }
    return 0;
}

// @ 0x008b71a0
extern "C" int tsi_T1GetGlyphIndexFromAdobeCode(int* t, int16 code)
{
    int n = *(int16*)((char*)t + 0x30);
    int16* codes = *(int16**)((char*)t + 0x38);
    int i = 0;
    if (n > 0) {
        do {
            if (codes[i] == code)
                return i;
            ++i;
        } while (i < n);
    }
    return i;
}

// @ 0x008b71c0
void Type1BuildChar(T1Class* t, uint8* data, int len, int depth, T1Outline* out, int flexLimit)
{
    int x = t->curX;
    int y = t->curY;
    int pos = 0;

    while (pos < len) {
        int op = data[pos++];
        if (op >= 0x20) {
            int v;
            if (op < 0xf7) {
                v = op - 0x8b;
            } else if (op < 0xfb) {
                v = op * 0x100 - 0xf694 + data[pos];
                pos += 1;
            } else if (op < 0xff) {
                v = (0xfa94 - op * 0x100) - data[pos];
                pos += 1;
            } else {
                v = (data[pos] << 24) | (data[pos + 1] << 16) | (data[pos + 2] << 8) | data[pos + 3];
                pos += 4;
            }
            if (t->sp < 0x20) {
                t->stack[t->sp] = v;
                t->sp++;
            }
            continue;
        }
        switch (op) {
        case 1: // hstem
            if (out) {
                if (out->capYPts <= out->cntYPts + 2) {
                    out->capYPts += 0x14;
                    out->yPts = (int16*)tsi_ReAllocMem(out->mem, out->yPts, out->capYPts * 2);
                    out->capYAll += 0x14;
                    out->yAll = (int16*)tsi_ReAllocMem(out->mem, out->yAll, out->capYAll * 2);
                }
                out->yPts[out->cntYPts] = (int16)t->stack[0];
                out->yPts[out->cntYPts] += (int16)T1_sby(t);
                out->yAll[out->cntYPts] = T1_glyph(t)->contour;
                out->cntYPts++;
                out->yPts[out->cntYPts] = out->yPts[out->cntYPts - 1] + (int16)t->stack[1];
                out->yAll[out->cntYPts] = T1_glyph(t)->contour;
                if (out->yPts[out->cntYPts] < out->yPts[out->cntYPts - 1]) {
                    int16 tmp = out->yPts[out->cntYPts - 1];
                    out->yPts[out->cntYPts - 1] = out->yPts[out->cntYPts];
                    out->yPts[out->cntYPts] = tmp;
                }
                out->cntYPts++;
            }
            t->sp = 0;
            break;
        case 3: // vstem
            if (out) {
                if (out->capXPts <= out->cntXPts + 2) {
                    out->capXPts += 0x14;
                    out->xPts = (int16*)tsi_ReAllocMem(out->mem, out->xPts, out->capXPts * 2);
                    out->capXAll += 0x14;
                    out->xAll = (int16*)tsi_ReAllocMem(out->mem, out->xAll, out->capXAll * 2);
                }
                out->xPts[out->cntXPts] = (int16)t->stack[0];
                out->xPts[out->cntXPts] += (int16)T1_sbx(t);
                out->xAll[out->cntXPts] = T1_glyph(t)->contour;
                out->cntXPts++;
                out->xPts[out->cntXPts] = out->xPts[out->cntXPts - 1] + (int16)t->stack[1];
                out->xAll[out->cntXPts] = T1_glyph(t)->contour;
                if (out->xPts[out->cntXPts] < out->xPts[out->cntXPts - 1]) {
                    int16 tmp = out->xPts[out->cntXPts - 1];
                    out->xPts[out->cntXPts - 1] = out->xPts[out->cntXPts];
                    out->xPts[out->cntXPts] = tmp;
                }
                out->cntXPts++;
            }
            t->sp = 0;
            break;
        case 4: // vmoveto
            y += t->stack[0];
            t->sp = 0;
            if (t->inFlex == 0) glyph_CloseContour(T1_glyph(t));
            glyph_AddPoint(T1_glyph(t), x, y, 1);
            break;
        case 5: // rlineto
            glyph_StartLine(T1_glyph(t), x, y);
            x += t->stack[0];
            y += t->stack[1];
            glyph_AddPoint(T1_glyph(t), x, y, 1);
            t->sp = 0;
            break;
        case 6: // hlineto
            glyph_StartLine(T1_glyph(t), x, y);
            x += t->stack[0];
            glyph_AddPoint(T1_glyph(t), x, y, 1);
            t->sp = 0;
            break;
        case 7: // vlineto
            glyph_StartLine(T1_glyph(t), x, y);
            y += t->stack[0];
            glyph_AddPoint(T1_glyph(t), x, y, 1);
            t->sp = 0;
            break;
        case 8: // rrcurveto
            glyph_StartLine(T1_glyph(t), x, y);
            {
                int dy = t->stack[1];
                int dx = t->stack[0];
                glyph_AddPoint(T1_glyph(t), x + dx, y + dy, 0);
                y = y + dy + t->stack[3];
                x = x + dx + t->stack[2];
                glyph_AddPoint(T1_glyph(t), x, y, 0);
                x += t->stack[4];
                y += t->stack[5];
                glyph_AddPoint(T1_glyph(t), x, y, 1);
            }
            t->sp = 0;
            break;
        case 9: // closepath
            glyph_CloseContour(T1_glyph(t));
            t->sp = 0;
            break;
        case 10: // callsubr
            t->sp--;
            {
                int idx = t->stack[t->sp];
                if (idx >= 0 && idx < t->numSubrs) {
                    uint8** pp = &t->subrs[idx];
                    int n = (int16)backwardsATOI(*pp - 5);
                    if (n - t->charBase > 0 && depth < 10) {
                        t->curX = x;
                        t->curY = y;
                        Type1BuildChar(t, *pp + t->charBase, n - t->charBase, depth + 1, out, flexLimit);
                        x = t->curX;
                        y = t->curY;
                    }
                }
            }
            break;
        case 0xb: // return
            t->curY = y;
            t->curX = x;
            return;
        case 0xc: { // escape
            int sub = data[pos];
            pos += 1;
            switch (sub) {
            case 0: // dotsection
                t->sp = 0;
                break;
            case 1: // vstem3
                if (!out) { t->sp = 0; break; }
                if (out->capXPts <= out->cntXPts + 6) {
                    out->capXPts += 0x14;
                    out->xPts = (int16*)tsi_ReAllocMem(out->mem, out->xPts, out->capXPts * 2);
                    out->capXAll += 0x14;
                    out->xAll = (int16*)tsi_ReAllocMem(out->mem, out->xAll, out->capXAll * 2);
                }
                for (int i = 0; i < 3; i++) {
                    out->xPts[out->cntXPts] = (int16)t->stack[i * 2];
                    out->xPts[out->cntXPts] += (int16)T1_sbx(t);
                    out->xAll[out->cntXPts] = T1_glyph(t)->contour;
                    out->cntXPts++;
                    out->xPts[out->cntXPts] = out->xPts[out->cntXPts - 1] + (int16)t->stack[i * 2 + 1];
                    out->xAll[out->cntXPts] = T1_glyph(t)->contour;
                    if (out->xPts[out->cntXPts] < out->xPts[out->cntXPts - 1]) {
                        int16 tmp = out->xPts[out->cntXPts - 1];
                        out->xPts[out->cntXPts - 1] = out->xPts[out->cntXPts];
                        out->xPts[out->cntXPts] = tmp;
                    }
                    out->cntXPts++;
                }
                t->sp = 0;
                break;
            case 2: // hstem3
                if (!out) { t->sp = 0; break; }
                if (out->capYPts <= out->cntYPts + 6) {
                    out->capYPts += 0x14;
                    out->yPts = (int16*)tsi_ReAllocMem(out->mem, out->yPts, out->capYPts * 2);
                    out->capYAll += 0x14;
                    out->yAll = (int16*)tsi_ReAllocMem(out->mem, out->yAll, out->capYAll * 2);
                }
                for (int i = 0; i < 3; i++) {
                    out->yPts[out->cntYPts] = (int16)t->stack[i * 2];
                    out->yPts[out->cntYPts] += (int16)T1_sby(t);
                    out->yAll[out->cntYPts] = T1_glyph(t)->contour;
                    out->cntYPts++;
                    out->yPts[out->cntYPts] = out->yPts[out->cntYPts - 1] + (int16)t->stack[i * 2 + 1];
                    out->yAll[out->cntYPts] = T1_glyph(t)->contour;
                    if (out->yPts[out->cntYPts] < out->yPts[out->cntYPts - 1]) {
                        int16 tmp = out->yPts[out->cntYPts - 1];
                        out->yPts[out->cntYPts - 1] = out->yPts[out->cntYPts];
                        out->yPts[out->cntYPts] = tmp;
                    }
                    out->cntYPts++;
                }
                t->sp = 0;
                break;
            case 6: { // seac
                int adx = t->stack[1];
                int ady = t->stack[2];
                GlyphBuilder* savedGlyph = T1_glyph(t);
                int accentIdx = T1GetGlyphIndexFromAdobeCode(t, (int16)t->stack[4]) & 0xffff;
                int baseIdx = T1GetGlyphIndexFromAdobeCode(t, (int16)t->stack[3]) & 0xffff;
                int off = 0;
                char dummy[4];
                void* g;
                if (accentIdx < t->numGlyphs &&
                    (g = T1GetGlyphByIndex(t, accentIdx, dummy, &depth, 0, -1)) != 0) {
                    off = T1_sbx(t);
                    Delete_GlyphClass(g);
                }
                if (baseIdx < t->numGlyphs &&
                    (g = T1GetGlyphByIndex(t, baseIdx, dummy, &depth, 0, -1)) != 0) {
                    off = off - x;
                    Delete_GlyphClass(g);
                }
                T1_glyph(t) = savedGlyph;
                savedGlyph->compCap = 0x40;
                int16* buf = (int16*)tsi_AllocMem(t->mem, 0x80);
                savedGlyph->compCount = 0;
                savedGlyph->compData = buf;
                buf[0] = 0x27;
                savedGlyph->compCount++;
                savedGlyph->compData[savedGlyph->compCount] = (int16)baseIdx;
                savedGlyph->compCount++;
                savedGlyph->compData[savedGlyph->compCount] = 0;
                savedGlyph->compCount++;
                savedGlyph->compData[savedGlyph->compCount] = 0;
                savedGlyph->compCount++;
                savedGlyph->compData[savedGlyph->compCount] = 7;
                savedGlyph->compCount++;
                savedGlyph->compData[savedGlyph->compCount] = (int16)accentIdx;
                savedGlyph->compCount++;
                savedGlyph->compData[savedGlyph->compCount] = (int16)adx - (int16)off;
                savedGlyph->compCount++;
                savedGlyph->compData[savedGlyph->compCount] = (int16)ady;
                savedGlyph->compCount++;
                savedGlyph->compFlag = -1;
                t->sp = 0;
                break;
            }
            case 7: // sbw
                x = t->stack[0];
                y = t->stack[1];
                T1_sbx(t) = x;
                T1_sby(t) = y;
                T1_wx(t) = t->stack[2];
                T1_wy(t) = t->stack[3];
                t->sp = 0;
                break;
            case 0xc: { // div
                int s = t->sp;
                t->stack[s - 2] = t->stack[s - 2] / t->stack[s - 1];
                t->sp--;
                break;
            }
            case 0x10: { // callothersubr
                t->sp--;
                int16 s0 = t->sp;
                int othr = t->stack[s0];
                int16 s1 = s0 - 1;
                t->sp = s1;
                int nargs = t->stack[s1];
                switch (othr) {
                case 0: { // end flex
                    t->inFlex = 0;
                    t->sp = s0 - 3;
                    if (out) {
                        GlyphBuilder* g = T1_glyph(t);
                        int n = g->contour;
                        int16* arr;
                        if (g->xPts[n - 1] == g->xPts[n - 7]) {
                            arr = g->xPts;
                        } else {
                            if (g->yPts[n - 1] != g->yPts[n - 7]) break;
                            arr = g->yPts;
                        }
                        flexLimit = (arr[n - 1] - arr[n - 4]) * flexLimit;
                        if (flexLimit < 0) flexLimit = -flexLimit;
                        if (flexLimit < t->stack[0] * 10) {
                            GlyphBuilder* g2 = T1_glyph(t);
                            int nn = g2->contour;
                            int px = g2->xPts[nn - 1];
                            int py = g2->yPts[nn - 1];
                            g2->contour -= 6;
                            glyph_AddPoint(T1_glyph(t), px, py, 1);
                        }
                    }
                    break;
                }
                case 1: // begin flex
                    t->inFlex = 1;
                    t->flexCount = 0;
                    glyph_StartLine(T1_glyph(t), x, y);
                    break;
                case 2: // flex point
                    if (t->inFlex) {
                        switch (t->flexCount) {
                        case 1: case 4:
                            glyph_AddPoint(T1_glyph(t), x, y, 0);
                            t->flexCount++;
                            break;
                        case 2: case 5:
                            glyph_AddPoint(T1_glyph(t), x, y, 0);
                            t->flexCount++;
                            break;
                        case 3: case 6:
                            glyph_AddPoint(T1_glyph(t), x, y, 1);
                            // fallthrough
                        default:
                            t->flexCount++;
                        }
                    }
                    break;
                case 3: { // hint replacement
                    int16 c;
                    if (out &&
                        ((c = T1_glyph(t)->contour, c == out->yAll[out->cntYPts - 1]) ||
                         c == out->xAll[out->cntXPts - 1])) {
                        int i = out->cntXPts - 1;
                        if (out->xAll[i] == c) {
                            for (;;) {
                                if (i < 1) goto zeroX;
                                int j = i;
                                i--;
                                if (out->xAll[j - 1] != T1_glyph(t)->contour) break;
                            }
                        }
                        if (i < 1) {
                        zeroX:
                            out->cntXPts = 0;
                        } else {
                            out->cntXPts = (int16)i + 1;
                        }
                        i = out->cntYPts - 1;
                        if (out->yAll[out->cntYPts - 1] == T1_glyph(t)->contour) {
                            for (;;) {
                                if (i < 1) goto zeroY;
                                int j = i;
                                i--;
                                if (out->yAll[j - 1] != T1_glyph(t)->contour) break;
                            }
                        }
                        if (0 < i) {
                            out->cntYPts = (int16)i + 1;
                            t->sp = t->sp - (int16)nargs;
                            break;
                        }
                    zeroY:
                        out->cntYPts = 0;
                    }
                    t->sp = t->sp - (int16)nargs;
                    break;
                }
                default:
                    t->sp = s1 - (int16)nargs;
                    break;
                case 0xc: case 0xd:
                    t->sp = 0;
                    break;
                case 0xe: case 0xf: case 0x10: case 0x11: case 0x12: {
                    int n = (othr == 0x12) ? 6 : (othr - 0xd);
                    int16 sp2 = s1 - (int16)T1_numMasters(t) * (int16)n;
                    t->sp = sp2;
                    int* src = &t->stack[n + sp2];
                    for (int k = n; k > 0; k--) {
                        int acc = t->stack[t->sp];
                        int* w = T1_weights(t);
                        for (int i = 1; i < T1_numMasters(t); i++) {
                            acc += util_FixMul(*src, *w);
                            src++;
                            w++;
                        }
                        t->stack[t->sp] = acc;
                        t->sp++;
                    }
                    t->sp = t->sp - (int16)n;
                    break;
                }
                }
                if (t->sp < 0) t->sp = 0;
                break;
            }
            case 0x11: // pop
                t->sp++;
                break;
            case 0x21: // setcurrentpoint
                glyph_StartLine(T1_glyph(t), x, y);
                t->sp = 0;
                break;
            }
            break;
        }
        case 0xd: // hsbw
            x = t->stack[0];
            y = 0;
            T1_sbx(t) = x;
            T1_sby(t) = 0;
            T1_wx(t) = t->stack[1];
            T1_wy(t) = 0;
            t->sp = 0;
            break;
        case 0xe: // endchar
            t->sp = 0;
            break;
        case 0x15: // rmoveto
            x += t->stack[0];
            y += t->stack[1];
            t->sp = 0;
            if (t->inFlex == 0) glyph_CloseContour(T1_glyph(t));
            break;
        case 0x16: // hmoveto
            x += t->stack[0];
            t->sp = 0;
            if (t->inFlex == 0) glyph_CloseContour(T1_glyph(t));
            glyph_AddPoint(T1_glyph(t), x, y, 1);
            break;
        case 0x1e: // vhcurveto
            glyph_StartLine(T1_glyph(t), x, y);
            {
                int d = t->stack[0];
                glyph_AddPoint(T1_glyph(t), x, y + d, 0);
                y = y + d + t->stack[2];
                int d2 = t->stack[1];
                glyph_AddPoint(T1_glyph(t), x + d2, y, 0);
                x = x + d2 + t->stack[3];
                glyph_AddPoint(T1_glyph(t), x, y, 1);
            }
            t->sp = 0;
            break;
        case 0x1f: // hvcurveto
            glyph_StartLine(T1_glyph(t), x, y);
            {
                int d = t->stack[0];
                glyph_AddPoint(T1_glyph(t), x + d, y, 0);
                int e = t->stack[2];
                x = x + d + t->stack[1];
                glyph_AddPoint(T1_glyph(t), x, y + e, 0);
                y = y + e + t->stack[3];
                glyph_AddPoint(T1_glyph(t), x, y, 1);
            }
            t->sp = 0;
            break;
        default:
            break;
        }
    }
    t->curY = y;
    t->curX = x;
}

// @ 0x008b81a0
extern "C" int tsi_T1CodeToGlyphIndex(T1Class_s008b_81a0* t, int16 code)
{
    int16* codes = t->codes;
    int n = t->numGlyphs;
    int i = 0;
    if (n > 0) {
        do {
            if (codes[i] == code)
                break;
            ++i;
        } while (i < n);
    }
    t->found = (i < n);
    if (i < n)
        return i;

    T1Hash* h = t->hashClass;
    int cnt = h->count;
    i = 0;
    if (cnt != 0) {
        if (cnt > 0) {
            T1HashEntry* e = h->table;
            do {
                if (e->code == code)
                    break;
                ++i;
                e = (T1HashEntry*)((char*)e + 8);
            } while (i < h->count);
        }
        t->found = (i < cnt);
        if (i < cnt)
            return h->table[i].value;
    }
    return 0;
}

// @ 0x008b83d0
extern "C" int tsi_T1GetArray(T1Class_s008b_81a0* t, const char* name, int maxcount, int* out)
{
    char* s = tsi_T1Find_s008b_81a0(t, name, t->off, t->limit);
    if (s == 0)
        return 0;
    int i = 0;
    while (*s != '[' && i < 0x20) {
        ++s;
        ++i;
    }
    ++s;
    int n = 0;
    if (maxcount < 1)
        return 0;
    char c = *s;
    for (;;) {
        while (c == ' ' && i < 0x200) {
            ++s;
            ++i;
            c = *s;
        }
        if (*s == ']')
            return n;
        char* q = s;
        uint16 v = 0;
        char d = *q;
        while (d < '0' || d > '9') {
            if (d == '-')
                break;
            ++q;
            d = *q;
        }
        if (d == '-')
            ++q;
        char e = *q;
        while (e >= '0' && e <= '9') {
            v = (uint16)(v * 10 + e - '0');
            e = *++q;
        }
        int16 val = (int16)v;
        if (d == '-')
            val = (int16)-val;
        out[n] = val;
        ++n;
        c = *s;
        for (;;) {
            if (c == ' ')
                break;
            if (i >= 0x200)
                break;
            ++i;
            if (c == ']')
                break;
            c = s[1];
            ++s;
        }
        if (n >= maxcount)
            return n;
    }
}

// @ 0x008b84d0
extern "C" int tsi_T1GetArray_2(T1Class_s008b_81a0* t, const char* name, int maxcount, int* out)
{
    char* s = tsi_T1Find_s008b_81a0(t, name, t->off, t->limit);
    if (s == 0)
        return 0;
    int i = 0;
    char c = *s;
    while (c != '{' && c != '[' && i < 0x20) {
        c = s[1];
        ++s;
        ++i;
    }
    ++s;
    int n = 0;
    if (maxcount < 1)
        return 0;
    c = *s;
    for (;;) {
        while (c == ' ' && i < 0x200) {
            ++s;
            ++i;
            c = *s;
        }
        if (*s == '}' || *s == ']')
            return n;
        char* q = s;
        uint16 v = 0;
        char d = *q;
        while (d < '0' || d > '9') {
            if (d == '-')
                break;
            ++q;
            d = *q;
        }
        if (d == '-')
            ++q;
        char e = *q;
        while (e >= '0' && e <= '9') {
            v = (uint16)(v * 10 + e - '0');
            e = *++q;
        }
        int16 val = (int16)v;
        if (d == '-')
            val = (int16)-val;
        out[n] = val;
        ++n;
        c = *s;
        for (;;) {
            if (c == ' ')
                break;
            if (i >= 0x200)
                break;
            ++i;
            if (c == ']' || c == '}')
                break;
            c = s[1];
            ++s;
        }
        if (n >= maxcount)
            return n;
    }
}

// @ 0x008b85e0
extern "C" int tsi_T1GetFixedArray(T1Class_s008b_81a0* t, const char* name, int maxcount, int* out)
{
    char* s = tsi_T1Find_s008b_81a0(t, name, t->off, t->limit);
    if (s == 0)
        return 0;
    int i = 0;
    while (*s != '[' && i < 0x20) {
        ++s;
        ++i;
    }
    ++s;
    int n = 0;
    if (maxcount > 0) {
        char c = *s;
        for (;;) {
            while (c == ' ' && i < 0x200) {
                ++s;
                ++i;
                c = *s;
            }
            if (*s == ']')
                return n;
            out[n] = ATOFixed((const uint8*)s, 0);
            c = *s;
            ++n;
            while (c != ' ' && i < 0x200) {
                c = s[1];
                ++s;
                ++i;
            }
            if (n >= maxcount)
                return n;
        }
    }
    return n;
}

// @ 0x008b8680
extern "C" void GetT1FontMatrix(T1Class_s008b_81a0* t)
{
    t->m_204 = 0x10000;
    t->m_210 = 0x10000;
    t->m_208 = 0;
    t->m_20c = 0;
    int i = 0;
    char* s = tsi_T1Find_s008b_81a0(t, "/FontMatrix ", t->off, t->limit);
    if (s == 0)
        return;
    while (*s != '[' && i < 0x100) {
        ++s;
        ++i;
    }
    ++s;
    while (*s == ' ' && i < 0x100) {
        ++s;
        ++i;
    }
    if (i < 0x100)
        t->m_204 = ATOFixed((const uint8*)s, 3);
    while (*s != ' ' && i < 0x100) {
        ++s;
        ++i;
    }
    while (*s == ' ' && i < 0x100) {
        ++s;
        ++i;
    }
    if (i < 0x100)
        t->m_20c = ATOFixed((const uint8*)s, 3);
    while (*s != ' ' && i < 0x100) {
        ++s;
        ++i;
    }
    while (*s == ' ' && i < 0x100) {
        ++s;
        ++i;
    }
    if (i < 0x100)
        t->m_208 = ATOFixed((const uint8*)s, 3);
    while (*s != ' ' && i < 0x100) {
        ++s;
        ++i;
    }
    while (*s == ' ' && i < 0x100) {
        ++s;
        ++i;
    }
    if (i < 0x100)
        t->m_210 = ATOFixed((const uint8*)s, 3);
}

// @ 0x008b87e0
extern "C" char* GetT1NameProperty(T1Class_s008b_81a0* t, int unused, int16 kind)
{
    const char* name;
    if (kind == 3)
        name = "/FamilyName";
    else if (kind == 4)
        name = "/FullName";
    else
        return 0;
    char* s = tsi_T1Find_s008b_81a0(t, name, 0, t->limit);
    if (s == 0)
        return 0;
    if (*s != '(') {
        ++s;
        if (*s != '(') {
            ++s;
            if (*s != '(') {
                ++s;
                if (*s != '(')
                    return 0;
            }
        }
    }
    ++s;
    int n = 0;
    while (*s != ')' && n < 0x50) {
        ++n;
        if (s[n] == ')')
            break;
    }
    char* out = (char*)tsi_AllocMem(t->mem, n + 1);
    int k = 0;
    if (n > 0) {
        char* dst = out;
        char* src = s;
        k = n;
        do {
            *dst = *src;
            ++dst;
            --n;
        } while (n != 0);
    }
    out[k] = 0;
    return out;
}

// @ 0x008b8c80
extern "C" short FF_GetAW_T1Class(T1Class_s008b_81a0* t, int16 idx)
{
    int16 outX = 0;
    int16 outW;
    void* g = tsi_T1GetGlyphByIndex(t, (uint16)idx, &outX, &outW, 0, -1);
    short result = 0;
    if (g != 0) {
        result = outX;
        Delete_GlyphClass(g);
    }
    return result;
}

// @ 0x008b8cc0
extern "C" void BuildSubrs(T1Class_s008b_81a0* t)
{
    t->numSubrs = 0;
    t->subrs = 0;
    char* p = tsi_T1Find_s008b_81a0(t, "/Subrs ", t->off, t->len);
    if (p == 0)
        return;

    int16 n = ATOI_s008b_81a0((const uint8*)p);
    t->numSubrs = n;
    t->subrs = (void**)tsi_AllocMem(t->mem, (uint32)((int)n * 4));

    int i = 0;
    if (n > 0) {
        do {
            t->subrs[i] = 0;
            ++i;
        } while (i < t->numSubrs);
    }
    if (t->numSubrs <= 0)
        return;

    int count = 0;
    char* cur = p;
    do {
        char* base = (char*)t->base;
        char* q = tsi_T1Find_s008b_81a0(t, "dup ", (int)(cur - base), t->len);
        uint16 v = 0;
        char b = *q;
        while (b < '0' || b > '9') {
            if (b == '-')
                break;
            ++q;
            b = *q;
        }
        if (b == '-')
            ++q;
        char c = *q;
        while (c >= '0' && c <= '9') {
            v = (uint16)(v * 10 + c - '0');
            c = *++q;
        }
        int16 idx = (int16)v;
        if (b == '-')
            idx = (int16)-idx;

        int off = (int)(cur - base);
        char* r = tsi_T1Find_s008b_81a0(t, "RD ", off, off + 0x10);
        if (r == 0)
            r = tsi_T1Find_s008b_81a0(t, "-| ", off, off + 0x10);
        int16 len = backwardsATOI_s008b_81a0((const uint8*)r - 5);
        t->subrs[idx] = r;
        ++count;
        cur = r + len;
    } while (count < t->numSubrs);
}

// @ 0x008b8e20
extern "C" int T1stringsAreEqual(T1Class_s008b_81a0* t, const char* name, int16 code)
{
    uint8 len = 0;
    if ((uint16)code == 0xfffe)
        return 0;

    char* candidate = 0;
    char first = *t->str;
    if (first >= '0' && first <= '9') {
        if ((int)(uint16)code < (int)ATOI_s008b_81a0((const uint8*)t->str)) {
            candidate = GetNthNameFromEncodingVector(t, (uint16)code);
            if (candidate != 0) {
                if (candidate[0] >= 0x21) {
                    len = 0;
                    do {
                        ++len;
                    } while ((uint8)candidate[len] >= 0x21);
                }
                goto compare;
            }
        }
    } else if ((uint16)code < 0x120) {
        candidate = (char*)g_t1NameTable[code].name;
        if (candidate != 0) {
            const char* q = candidate + 1;
            const char* r = candidate;
            do {
                ++r;
            } while (*r != 0);
            len = (uint8)(r - q);
            goto compare;
        }
    }

    if (t->hashClass->table != 0) {
        int out;
        return get_using_uint16_hashClass(t->hashClass, code, &out);
    }

compare:
    {
        int nl = 0;
        while (name[nl] != 0)
            ++nl;
        if (nl == (int)len && strncmp(name, candidate, len) == 0)
            return 1;
    }
    return 0;
}

// @ 0x008b8f30
void ParseT1CharStrings(T1Class_s008b_8f30* t)
{
    uint8* base = t->base;
    uint32 size = t->size;
    uint8* encoding = FindString(base, "/Encoding ", (int)size, 0);
    if (!encoding)
        return;
    t->encoding = encoding;

    uint8 first = *encoding;
    uint8 decimal = (first >= '0' && first <= '9') ? 1 : 0;
    uint8 encodingKind = 0;
    if (!decimal) {
        if (first == 'S')
            encodingKind = 0;
        else if (first == 'I')
            encodingKind = 1;
    }

    uint8* charStrings = FindString(base, "/CharStrings ", (int)size, (int)t->field10);
    if (!charStrings) {
        T1Error(t->mem, 0x2729);
        return;
    }
    t->field14 = (uint32)(charStrings - base);

    int16 count = (int16)ATOI(charStrings);
    t->numGlyphs = count;
    int glyphCount = (uint16)count;
    uint32 encodingCount = decimal ? (uint16)ATOI(t->encoding) : 0x100;

    t->glyphMap = (int16*)tsi_AllocMem(t->mem, (uint32)glyphCount * 2);
    t->adobeCodes = (int16*)tsi_AllocMem(t->mem, (uint32)glyphCount * 2);
    t->charStringOffsets = (uint32*)tsi_AllocMem(t->mem, (uint32)glyphCount * 4);
    t->charStrings = T1NewCharStrings(t->mem, glyphCount, (void*)0x8b8e20, t);

    for (int i = 0; i < glyphCount; ++i) {
        t->glyphMap[i] = -1;
        t->adobeCodes[i] = -1;
        t->charStringOffsets[i] = 0;
    }

    t->field218 = 0;
    t->field21a = 0x00ff;
    t->field214 = 0;
    if (t->charStrings) {
        t->charStrings->capacity = encodingCount;
        t->charStrings->count = 0;
    }

    uint8* limit = base + size;
    uint8* p = charStrings;
    int glyph = 0;
    while (p < limit && glyph < glyphCount) {
        uint8* slash = p;
        while (slash < limit && *slash != '/')
            ++slash;
        if (slash >= limit)
            break;

        uint8* name = slash + 1;
        uint8* q = name;
        int nameLen = 0;
        while (q < limit && *q > ' ' && nameLen < 0x3f) {
            ++q;
            ++nameLen;
        }

        uint8 nameBuf[64];
        for (int i = 0; i < nameLen; ++i)
            nameBuf[i] = name[i];
        nameBuf[nameLen] = 0;

        uint8* num = q;
        while (num < limit && (*num == ' ' || *num == '\t' || *num == '\r' || *num == '\n'))
            ++num;
        int dataLen = ATOI(num);

        uint8* rd = num;
        while (rd + 1 < limit &&
               !(rd[0] == 'R' && rd[1] == 'D') &&
               !(rd[0] == '-' && rd[1] == '|'))
            ++rd;
        if (rd + 1 >= limit)
            break;

        uint8* data = rd + 2;
        while (data < limit && (*data == ' ' || *data == '\r' || *data == '\n'))
            ++data;

        t->charStringOffsets[glyph] = (uint32)(data - base);

        uint16 code = 0xffff;
        uint16 codeA = 0;
        uint16 codeB = 0;
        tsi_PSNameToAppleCode(nameBuf, &code, &codeA, &codeB);
        t->adobeCodes[glyph] = (int16)code;
        t->glyphMap[glyph] = (int16)glyph;

        if (t->charStrings)
            T1AddCharString(t->charStrings, (uint32)(name - base), (uint16)glyph, (uint16)dataLen);

        data += (uint16)dataLen;
        p = data;
        while (p + 1 < limit &&
               !(p[0] == 'N' && p[1] == 'D') &&
               !(p[0] == '|' && p[1] == '-'))
            ++p;
        if (p + 1 >= limit)
            break;
        p += 2;
        ++glyph;
    }

    (void)encodingKind;
}

// @ 0x008b9390
static uint8* FindString(uint8* hay, const char* needle, int n, int start)
{
    int len = 0;
    while (needle[len])
        ++len;
    for (int i = start; i < n; ++i) {
        if (hay[i] != (uint8)needle[0])
            continue;
        int k = 1;
        while (k < len) {
            if (hay[i + k] != (uint8)needle[k])
                break;
            ++k;
        }
        if (k >= len)
            return hay + i + k;
    }
    return 0;
}

// @ 0x008b9400
kernSubTable0Data* New_T1kernSubTable0Data(T1Class_s008b_8f30* t, tsiMemObject* mem, uint8* p, int length)
{
    uint8 buf1[64];
    uint8 buf2[64];
    uint32 a4 = 0;         // current Apple/hex code (low 16 bits written by tsi_PSNameToAppleCode)
    uint32 v9c = 0;        // low hex digit
    uint32 v88 = 0;        // first glyph index (16 bit) of the current record
    uint32 a0 = 0;         // glyph code table, then the second glyph index
    int v8c;               // glyph count / scratch output of tsi_PSNameToAppleCode
    uint8 v98[4];          // scratch output of tsi_PSNameToAppleCode
    int a8;                // first glyph index
    int cnt;
    int n;
    int limit;
    uint8* s;
    uint8* cursor;
    bool found;
    uint16 i;
    int numPairsIn;

    kernSubTable0Data* result = (kernSubTable0Data*)tsi_AllocMem(mem, 0x10);
    uint8* end = p + length;
    result->mem = mem;
    result->numPairs = 0;
    result->pairs = 0;

    cursor = FindString(p, "StartKernPairs", length, 0);
    if (cursor != 0) {
        int count = (int16)ATOI(cursor);
        result->pad6 = 0;
        result->numPairs = (uint16)count;
        result->pad8 = 0;
        result->pad10 = 0;
        numPairsIn = count;
        result->pairs = (KernPair*)tsi_AllocMem(mem, (uint32)(uint16)count * 8);
        i = 0;
        if (0 < count) {
            do {
                if (cursor + 0x50 > end) {
                    limit = (int)(end - cursor);
                    if (limit <= 10)
                        break;
                } else {
                    limit = 0x50;
                }
                found = false;
                n = 0;

                // ---- "KP " name1 name2 x y ----------------------------------------------------
                s = FindString(cursor, "KP ", limit - 2, 0);
                if (s) {
                    found = true;
                    SKIP_CHAR(' ')
                    COPY_TOKEN(buf1, ' ')
                    tsi_PSNameToAppleCode(buf1, (uint16*)&a4, (uint16*)&v8c, (uint16*)v98);
                    cnt = t->numGlyphs;
                    a0 = (uint32)t->adobeCodes;
                    FIND_INDEX(a8, (int16*)a0, cnt, a4)
                    v88 = (uint16)a8;
                    SKIP_CHAR(' ')
                    COPY_TOKEN(buf2, ' ')
                    tsi_PSNameToAppleCode(buf2, (uint16*)&a4, (uint16*)&v8c, (uint16*)v98);
                    {
                        int ix;
                        FIND_INDEX(ix, (int16*)a0, cnt, a4)
                        a0 = (uint16)ix;
                    }
                    SKIP_CHAR(' ')
                    {
                        int16 value = (int16)ATOI(s);
                        SKIP_TO_SPACE_COUNTING_PAIR()
                        STORE_PAIR(a8, a0, value)
                    }
                    cursor = s;
                    if (s + 0x50 > end) {
                        limit = (int)(end - s);
                        if (limit <= 10)
                            break;
                    } else {
                        limit = 0x50;
                    }
                }

                // ---- "KPH" <hex> <hex> x y ----------------------------------------------------
                n = 0;
                s = FindString(cursor, "KPH", limit - 3, 0);
                if (s) {
                    unsigned hi, v1, v2;
                    int16* tbl;
                    found = true;
                    SKIP_CHAR(' ')
                    SKIP_CHAR('<')
                    COPY_TOKEN(buf1, '>')
                    hi = (uint8)(buf1[0] - '0') <= 9 ? (uint16)((int16)(char)buf1[0] - 0x30)
                       : (uint8)(buf1[0] - 'A') <= 5 ? (uint16)((int16)(char)buf2[0] - 0x37)
                       : (uint8)(buf1[0] - 'a') <= 5 ? (uint16)((int16)(char)buf2[0] - 0x57)
                       : a4;
                    v9c = HexDigitValue(buf1[1], v9c);
                    v1 = (uint16)(((v9c & 0xf) | (hi << 4)));
                    tbl = t->adobeCodes;
                    v8c = t->numGlyphs;
                    FIND_INDEX(a8, tbl, v8c, v1)
                    v88 = (uint16)a8;
                    SKIP_CHAR('>')
                    SKIP_CHAR(' ')
                    SKIP_CHAR('<')
                    COPY_TOKEN(buf2, '>')
                    hi = HexDigitValue(buf2[0], v1);
                    v9c = HexDigitValue(buf2[1], v9c);
                    v2 = (uint16)(((v9c & 0xf) | (hi << 4)));
                    a4 = v2;
                    {
                        int ix;
                        FIND_INDEX(ix, tbl, v8c, v2)
                        a0 = (uint16)ix;
                    }
                    SKIP_CHAR('>')
                    for (; *s == ' ' && (int)i < limit; ++i) ++s;
                    {
                        int16 value = (int16)ATOI(s);
                        SKIP_TO_SPACE_COUNTING_PAIR()
                        STORE_PAIR(a8, a0, value)
                    }
                    cursor = s;
                    if (s + 0x50 > end) {
                        limit = (int)(end - s);
                        if (limit <= 10)
                            break;
                    } else {
                        limit = 0x50;
                    }
                }

                // ---- "KPX" name1 name2 x ------------------------------------------------------
                n = 0;
                s = FindString(cursor, "KPX", limit - 3, 0);
                if (s) {
                    found = true;
                    SKIP_CHAR(' ')
                    COPY_TOKEN(buf1, ' ')
                    tsi_PSNameToAppleCode(buf1, (uint16*)&a4, (uint16*)&v8c, (uint16*)v98);
                    cnt = t->numGlyphs;
                    a0 = (uint32)t->adobeCodes;
                    FIND_INDEX(a8, (int16*)a0, cnt, a4)
                    v88 = (uint16)a8;
                    SKIP_CHAR(' ')
                    COPY_TOKEN(buf2, ' ')
                    tsi_PSNameToAppleCode(buf2, (uint16*)&a4, (uint16*)&v8c, (uint16*)v98);
                    {
                        int ix;
                        FIND_INDEX(ix, (int16*)a0, cnt, a4)
                        a0 = (uint16)ix;
                    }
                    SKIP_CHAR(' ')
                    {
                        int16 value = (int16)ATOI(s);
                        STORE_PAIR(a8, a0, value)
                    }
                    cursor = s;
                    if (s + 0x50 > end) {
                        limit = (int)(end - s);
                        if (limit <= 10)
                            break;
                    } else {
                        limit = 0x50;
                    }
                }

                // ---- "KPY" name1 name2 y (y ignored; glyph indices left over from the last KPX) --
                n = 0;
                s = FindString(cursor, "KPY", limit - 3, 0);
                if (s == 0) {
                    if (!found)
                        break;
                } else {
                    SKIP_CHAR(' ')
                    COPY_TOKEN(buf1, ' ')
                    SKIP_CHAR(' ')
                    COPY_TOKEN(buf2, ' ')
                    SKIP_CHAR(' ')
                    STORE_PAIR(v88, a0, 0)
                    cursor = s;
                    if (s + 0x50 > end && (int)(end - s) <= 10)
                        break;
                }
                ++i;
            } while ((int)i < numPairsIn);

            if (i == 0)
                return result;
            result->numPairs = i;
            FUN_008cfac0(result->pairs, i);
            return result;
        }
    }
    return result;
}

// @ 0x008b9d90
kernSubTable* New_T1kernSubTable(T1Class_s008b_8f30* t, tsiMemObject* mem, uint8* p, int length)
{
    kernSubTable0* table;
    kernSubTable* result = (kernSubTable*)tsi_AllocMem(mem, 0x10);
    result->mem = mem;
    result->flags4 = 0;
    result->numTables = 1;
    result->tables = (kernSubTable0**)tsi_AllocMem(mem, 4);

    table = (kernSubTable0*)tsi_AllocMem(mem, 0x14);
    table->mem = mem;
    table->flags4 = 0;
    table->length = 0x14;
    table->format = 1;
    table->data = New_T1kernSubTable0Data(t, mem, p, length);
    result->tables[0] = table;
    return result;
}

// @ 0x008b9f20
extern "C" void tsi_DeleteT1Class(T1Class_s008b_9e10* t)
{
    if (t != 0) {
        Delete_GlyphClass(t->glyph);
        if (t->base != t->f04)
            tsi_DeAllocMem(t->mem, (void*)t->base);
        tsi_DeAllocMem(t->mem, t->codes);
        tsi_DeAllocMem(t->mem, t->adobeCodes);
        tsi_DeAllocMem(t->mem, t->charStrings);
        tsi_DeAllocMem(t->mem, t->subrs);
        Delete_hashClass(t->hashClass);
        tsi_DeAllocMem(t->mem, t);
    }
}

// @ 0x008b9fa0
extern "C" uint8 ReadOfffset1(TsiStream* s)
{
    return ts_readByte(s);
}

// @ 0x008ba050
extern "C" int16 ReadOfffset2(TsiStream* s)
{
    uint8 hi = ts_readByte(s);
    uint8 lo = ts_readByte(s);
    return (int16)((hi << 8) | lo);
}

// @ 0x008ba1c0
extern "C" uint32 ReadOfffset3(TsiStream* s)
{
    uint32 v = ts_readByte(s);
    v = (v << 8) | ts_readByte(s);
    v = (v << 8) | ts_readByte(s);
    return v;
}

// @ 0x008ba3d0
extern "C" int32 ReadOfffset4(TsiStream* s)
{
    uint32 v = ts_readByte(s);
    v = (v << 8) | ts_readByte(s);
    v = (v << 8) | ts_readByte(s);
    v = (v << 8) | ts_readByte(s);
    return (int32)v;
}

// @ 0x008ba680
extern "C" int READ_REAL(TsiStream* s)
{
    uint8 nib[4];
    char  out[68];
    int   n = 0;

    for (;;) {
        uint8 b = ts_readByte(s);
        nib[1] = b & 0xf;
        nib[0] = b >> 4;
        for (int k = 0; k < 2; ++k) {
            switch (nib[k]) {
            case 10: out[n] = '.';  break;               // nibble 0xa: decimal point
            case 11: out[n] = 'E';  break;               // nibble 0xb: exponent
            case 12: out[n] = 'E';  out[++n] = '-'; break; // 0xc: negative exponent
            case 14: out[n] = '-';  break;               // 0xe: minus sign
            case 13: continue;                           // 0xd: no character
            case 15:                                     // 0xf: end of number
                out[n] = 0;
                return ATOFixed((const uint8*)out, 0);
            default:
                out[n] = (char)(nib[k] + 0x30);
                break;
            }
            ++n;
        }
    }
}

// @ 0x008ba7c0
extern "C" uint32 READ_INTEGER(TsiStream* s, int tag)
{
    uint32 v = 0;

    if (tag == 0x1c) {                     // shortint: 2 bytes
        v = ts_readByte(s);
    } else if (tag == 0x1d) {              // longint: 4 bytes
        v = ts_readByte(s);
        v = (v << 8) | ts_readByte(s);
        v = (v << 8) | ts_readByte(s);
    } else if (tag <= 0xf6) {              // single-byte integer, bias 0x8b
        return (uint32)(tag - 0x8b);
    } else if (tag <= 0xfa) {              // positive 2-byte, bias 0xf694
        return (uint32)(tag * 0x100 - 0xf694 + ts_readByte(s));
    } else if (tag <= 0xfe) {              // negative 2-byte
        return (uint32)(0xfa94 - tag * 0x100 - ts_readByte(s));
    } else {                               // 0xff: reserved
        return 0;
    }
    return (v << 8) | ts_readByte(s);
}

// @ 0x008bad10
extern "C" CFFIndex* tsi_NewCFFIndexClass(tsiMemObject* mem, TsiStream_s008b_ad10* s)
{
    CFFIndex* ix = (CFFIndex*)tsi_AllocMem(mem, 0x14);
    ix->mem = mem;
    ix->f04 = 0;

    int16 count = ReadInt16(s);
    ix->count = count;
    if (count != 0) {
        ix->offSize = ts_readByte_s008b_ad10(s);
        ix->offsets = (int*)tsi_AllocMem(mem, (uint32)(uint16)count * 4 + 4);

        uint32 (*read)(TsiStream_s008b_ad10*);
        if (ix->offSize == 1)
            read = (uint32 (*)(TsiStream_s008b_ad10*))ReadOfffset1_s008b_ad10;
        else if (ix->offSize == 2)
            read = (uint32 (*)(TsiStream_s008b_ad10*))ReadOfffset2_s008b_ad10;
        else if (ix->offSize == 3)
            read = (uint32 (*)(TsiStream_s008b_ad10*))ReadOfffset3_s008b_ad10;
        else
            read = (uint32 (*)(TsiStream_s008b_ad10*))ReadOfffset4_s008b_ad10;

        int i = 0;
        do {
            ix->offsets[i] = (int)read(s);
            ++i;
        } while (i <= (int)(uint16)count);

        int t = Tell_InputStream(s);
        ix->f04 = t - 1;
        Seek_InputStream(s, ix->offsets[(uint16)count] + (t - 1));
    }
    return ix;
}

// @ 0x008bae70
extern "C" int tsi_GetCFFData(int index, CFFIndex* ix, TsiStream_s008b_ad10* s)
{
    int buf = 0;
    if (index >= 0 && index < (int)(uint16)ix->count) {
        int pos = Tell_InputStream(s);
        Seek_InputStream(s, ix->offsets[index] + ix->f04);

        int len = ix->offsets[index + 1] - ix->offsets[index];
        int p = (int)tsi_AllocMem(ix->mem, (uint32)(len + 2));
        buf = p;
        PeekInt16(s, (void*)p, len);
        *(uint8*)(p + len) = 0;
        *(uint8*)(p + len + 1) = 0;
        Seek_InputStream(s, pos);
    }
    return buf;
}

// @ 0x008baee0
extern "C" int GetT2NameProperty(CFFClass* t, int unused, int16 kind)
{
    if (kind == 4 && t->nameIdx != 0)
        return tsi_GetCFFData(t->nameIndex, t->nameIdx, t->stream);
    return 0;
}

// @ 0x008baf10
extern "C" void tsi_ParsePrivateDictData(void* p)
{
    char*   base = (char*)p;
    TsiStream_s008b_ad10* s = *(TsiStream_s008b_ad10**)(base + 4);
    int st[64];
    int n = 0;

    int savepos = Tell_InputStream(s);
    *(int*)(base + 0x4fc) = 0;
    *(int*)(base + 0x500) = 0;
    *(int*)(base + 0x504) = 0;
    *(int*)(base + 0x508) = 0;

    Seek_InputStream(s, *(int*)(base + 0x3c0) + *(int*)(base + 8));
    int end = *(int*)(base + 0x3bc) + *(int*)(base + 0x3c0) + *(int*)(base + 8);

    while ((uint32)Tell_InputStream(s) < (uint32)end) {
        uint8 b = ts_readByte_s008b_ad10(s);
        if (b <= 0x1b || b == 0x1f) {
            if (b == 0x13)
                *(int*)(base + 0x4fc) = st[0];
            else if (b == 0x14)
                *(int*)(base + 0x504) = st[0];
            else if (b == 0x15)
                *(int*)(base + 0x508) = st[0];
            n = 0;
        } else if (b == 0x1e) {
            st[n++] = READ_REAL_s008b_ad10(s);
        } else {
            st[n++] = (int)READ_INTEGER_s008b_ad10(s, b);
        }
    }

    if (*(int*)(base + 0x4fc) != 0)
        *(int*)(base + 0x500) = *(int*)(base + 0x3c0) + *(int*)(base + 0x4fc) + *(int*)(base + 8);
    Seek_InputStream(s, savepos);
}

// @ 0x008bb0d0
extern "C" void tsi_ParseCFFTopDict(TsiStream_s008b_ad10* s, CFFIndex* ix, CFFTopDict* d, int index)
{
    int st[64];
    int n = 0;

    int start = Tell_InputStream(s);

    d->f18 = 0; d->f10 = 0; d->f1c = 0; d->f14 = 0;
    d->f24 = 0;
    d->f160 = 0; d->f164 = 0;
    d->f34 = 0; d->f38 = 0; d->f40 = 0; d->f44 = 0;
    d->f48 = 0; d->f50 = 0; d->f54 = 0;
    d->f20 = 0;
    d->f16c = 0;
    d->f28 = -100;
    d->f2c = 50;
    d->f15c = 0x10000;
    d->f168 = 0x10000;
    d->f4c = 1;
    d->f30 = 2;

    Seek_InputStream(s, ix->offsets[index] + ix->f04);
    int end = ix->offsets[index + 1] + ix->f04;

    while ((uint32)Tell_InputStream(s) < (uint32)end) {
        uint8 b = ts_readByte_s008b_ad10(s);
        int   v0 = st[0];

        if (b <= 0x1b || b == 0x1f) {
            if (b == 0x0c) {
                uint8 op2 = ts_readByte_s008b_ad10(s);
                switch (op2) {
                case 1:  d->f20 = v0; break;
                case 2:  d->f24 = v0; break;
                case 3:  d->f28 = v0; break;
                case 4:  d->f2c = v0; break;
                case 6:  d->f30 = (uint8)v0; break;
                case 7:
                    d->f15c = util_FixMul(v0, 0x3e80000);
                    d->f164 = util_FixMul(st[1], 0x3e80000);
                    d->f160 = util_FixMul(st[2], 0x3e80000);
                    d->f168 = util_FixMul(st[3], 0x3e80000);
                    break;
                case 0x1c:
                    d->f48 = n - 4;
                    d->f4c = v0;
                    for (int k = 0; k < n - 4; ++k)
                        d->bbox.copy[k] = st[k + 1];
                    d->f50 = st[d->f48 + 1];
                    d->f54 = (int)tsi_AllocMem(ix->mem, (uint32)d->f50 * 4);
                    d->bbox.v.lo = (int16)st[d->f48 + 2];
                    d->bbox.v.hi = (int16)st[d->f48 + 3];
                    /* falls through into the FontMatrix case */
                    d->f15c = util_FixMul(v0, 0x3e80000);
                    d->f164 = util_FixMul(st[1], 0x3e80000);
                    d->f160 = util_FixMul(st[2], 0x3e80000);
                    d->f168 = util_FixMul(st[3], 0x3e80000);
                    break;
                case 0x1e:
                    d->f16c = 1;
                    break;
                default:
                    break;
                }
            } else {
                switch (b) {
                case 0:  d->f00 = (int16)v0; break;
                case 1:  d->f02 = (int16)v0; break;
                case 2:  d->f04 = (int16)v0; break;
                case 3:  d->f06 = (int16)v0; break;
                case 4:  d->f08 = (int16)v0; break;
                case 5:  d->f10 = v0; d->f14 = st[1]; d->f18 = st[2]; d->f1c = st[3]; break;
                case 13: d->f0c = v0; break;
                case 15: d->f34 = v0; break;
                case 16: d->f38 = v0; break;
                case 17: d->f3c = v0; break;
                case 18: d->f40 = v0; d->f44 = st[1]; break;
                default: break;
                }
            }
            n = 0;
        } else if (b == 0x1e) {
            st[n++] = READ_REAL_s008b_ad10(s);
        } else {
            st[n++] = (int)READ_INTEGER_s008b_ad10(s, b);
        }
    }

    Seek_InputStream(s, start);
}
