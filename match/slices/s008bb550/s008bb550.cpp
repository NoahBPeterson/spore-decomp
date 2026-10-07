// Slice s008bb550 — 0x008bb550 Type2BuildChar (9560 code bytes + 2 jump tables).
//
// Module "EA-UTF": the T2K / Font Fusion font engine (tsi_* helpers, InputStream,
// CFFClass).  This is the CFF Type-2 charstring interpreter: it reads the
// charstring byte by byte through the inlined ReadUnsignedByteMacro, pushes
// 16.16 operands on t->gStackValues and turns the path operators into
// glyph_StartLine / glyph_AddPoint / glyph_CloseContour calls; callsubr /
// callgsubr recurse (depth limit 10).
//
// COMPILE AS C: flags "/O2 /MD /Gy /TC".  T2K is C, and C's `c ? uint8 : uint8`
// is int-typed (C++ keeps uint8), which is what gives the reader macro its
// movzx-per-branch shape.  The file still compiles as C++ (/TP) but diverges.
//
// Status: complete; 4 differing bytes (two commutative `add edx,[esp+X]` operand
// orders in the hflex1 dy-sum and the flex1 dy-sum), everything else incl. the
// whole frame layout identical.  Codegen notes that got it there: operands are
// popped with `n -= k; ... n++` (not stack[n-1]); path loops use stack[i++];
// the flex temporaries are function-scope variables shared by all flex cases
// (block-scoped copies change the /O2 spill-slot packing); several cases need a
// distinct loop/temp variable (num, r, rv, sv, m, N, k) for the same reason.
//
// Layouts are the 2008 dev-PDB structs (tools/pdb_type.py CFFClass, InputStream_t,
// TopDictInfo, PrivateDictInfo, CFFIndexClass); all offsets used here were checked
// against the retail disassembly.
//
// @ 0x008bb550

typedef unsigned char  uint8;
typedef signed char    int8;
typedef unsigned short uint16;
typedef short          int16;
typedef unsigned long  uint32;
typedef long           int32;
typedef long           F16Dot16;

typedef struct tsiMemObject tsiMemObject;
typedef struct GlyphClass GlyphClass;
typedef struct cmap_t cmap_t;
typedef struct hashClass hashClass;
typedef struct InputStream InputStream;
typedef struct CFFIndexClass CFFIndexClass;
typedef struct TopDictInfo TopDictInfo;
typedef struct PrivateDictInfo PrivateDictInfo;
typedef struct CFFClass CFFClass;

typedef int (*PF_READ_TO_RAM)(void* id, uint8* dest_ram, unsigned long offset, long numBytes);

struct InputStream {                     // InputStream_t, size 0x23c
    uint8*          privateBase;         // +0x000
    PF_READ_TO_RAM  ReadToRamFunc;       // +0x004
    void*           nonRamID;            // +0x008
    uint8           tmp_ch;              // +0x00c
    uint8           cacheBase[512];      // +0x00d
    long            bytesLeftToPreLoad;  // +0x210
    unsigned long   cacheCount;          // +0x214
    unsigned long   cachePosition;       // +0x218
    unsigned long   pos;                 // +0x21c
    unsigned long   maxPos;              // +0x220
    unsigned long   posZero;             // +0x224
    char            constructorType;     // +0x228
    tsiMemObject*   mem;                 // +0x22c
    unsigned long   bitBufferIn;         // +0x230
    unsigned long   bitCountIn;          // +0x234
    uint8           decrypted;           // +0x238
};

struct CFFIndexClass {                   // size 0x14
    tsiMemObject*   mem;                 // +0x00
    unsigned long   baseDataOffset;      // +0x04
    uint8           offSize;             // +0x08
    unsigned long*  offsetArray;         // +0x0c
    uint16          count;               // +0x10
};

struct TopDictInfo {                     // size 0x170
    uint16  version;                     // +0x00
    uint16  Notice;                      // +0x02
    uint16  FullName;                    // +0x04
    uint16  FamilyName;                  // +0x06
    uint16  Weight;                      // +0x08
    long    UniqueId;                    // +0x0c
    long    bbox_xmin;                   // +0x10
    long    bbox_ymin;                   // +0x14
    long    bbox_xmax;                   // +0x18
    long    bbox_ymax;                   // +0x1c
    unsigned long isFixedPitch;          // +0x20
    long    italicAngle;                 // +0x24
    int     UnderlinePosition;           // +0x28
    int     UnderlineThickness;          // +0x2c
    uint8   CharstringType;              // +0x30
    long    charset;                     // +0x34
    long    Encoding;                    // +0x38
    long    Charstrings;                 // +0x3c
    long    PrivateDictSize;             // +0x40
    long    PrivateDictOffset;           // +0x44
    int     numAxes;                     // +0x48
    int     numMasters;                  // +0x4c
    int     lenBuildCharArray;           // +0x50
    long*   buildCharArray;              // +0x54
    long    defaultWeight[16];           // +0x58
    uint16  NDV;                         // +0x98
    uint16  CDV;                         // +0x9a
    long    reg_WeightVector[16];        // +0x9c
    long    reg_NormalizedDesignVector[16]; // +0xdc
    long    reg_UserDesignVector[16];    // +0x11c
    long    m00, m01, m10, m11;          // +0x15c
    uint8   isCIDKeyed;                  // +0x16c
};

struct PrivateDictInfo {                 // size 0x10
    long Subr;                           // +0x0
    long SubrOffset;                     // +0x4
    long defaultWidthX;                  // +0x8
    long nominalWidthX;                  // +0xc
};

#define T2_MAX_STACK 64

struct CFFClass {                        // size 0x520
    tsiMemObject*   mem;                 // +0x000
    InputStream*    in;                  // +0x004
    unsigned long   cffOffset;           // +0x008
    long            NumCharStrings;      // +0x00c
    uint16          charCodeToSID[256];  // +0x010
    cmap_t*         T2_CMAPTable;        // +0x210
    hashClass*      T2_StringsHash;      // +0x214
    hashClass*      T2_SIDToCharCodeHash;// +0x218
    long            upem;                // +0x21c
    long            maxPointCount;       // +0x220
    long            ascent;              // +0x224
    long            descent;             // +0x228
    long            lineGap;             // +0x22c
    long            advanceWidthMax;     // +0x230
    long            italicAngle;         // +0x234
    long            fontNum;             // +0x238
    F16Dot16        gStackValues[T2_MAX_STACK]; // +0x23c
    long            gNumStackValues;     // +0x33c
    GlyphClass*     glyph;               // +0x340
    long            x;                   // +0x344
    long            y;                   // +0x348
    long            awy;                 // +0x34c
    long            awx;                 // +0x350
    long            lsbx;                // +0x354
    long            lsby;                // +0x358
    int             numStemHints;        // +0x35c
    int             pointAdded;          // +0x360
    int             widthDone;           // +0x364
    int             stkClrOpCalled;      // +0x368
    uint16          seed;                // +0x36c
    uint8           major;               // +0x36e
    uint8           minor;               // +0x36f
    uint8           hdrSize;             // +0x370
    uint8           offSize;             // +0x371
    CFFIndexClass*  name;                // +0x374
    CFFIndexClass*  topDict;             // +0x378
    TopDictInfo     topDictData;         // +0x37c
    CFFIndexClass*  string;              // +0x4ec
    CFFIndexClass*  gSubr;               // +0x4f0
    long            gSubrBias;           // +0x4f4
    CFFIndexClass*  CharStrings;         // +0x4f8
    PrivateDictInfo privateDictData;     // +0x4fc
    CFFIndexClass*  lSubr;               // +0x50c
    long            lSubrBias;           // +0x510
    unsigned long   isFixedPitch;        // +0x514
    uint16          firstCharCode;       // +0x518
    uint16          lastCharCode;        // +0x51a
    int             glyphExists;         // +0x51c
};

#define T2K_ERR_TRANS_FAIL 10024
#define ABS(x) ((x) < 0 ? -(x) : (x))

#ifdef __cplusplus
extern "C" {
#endif
unsigned long Tell_InputStream(InputStream* t);                 // 0x008cc5b0
void Seek_InputStream(InputStream* t, unsigned long offset);    // 0x008cc580 area
void PrimeT2KInputStream(InputStream* t);                       // 0x008cc0b0
void tsi_Error(tsiMemObject* t, int errcode);                   // 0x008d10c0
void glyph_StartLine(GlyphClass* t, long x, long y);            // 0x008b0440
void glyph_AddPoint(GlyphClass* t, long x, long y, uint8 onCurveBit);   // 0x008b0320
void glyph_CloseContour(GlyphClass* t);         // 0x008afde0
F16Dot16 util_FixMul(F16Dot16 a, F16Dot16 b);  // 0x008d1590
F16Dot16 util_FixDiv(F16Dot16 a, F16Dot16 b);  // 0x008d16d0
void Type2BuildChar(CFFClass* t, InputStream* in, long byteCount, long recursionLevel);
#ifdef __cplusplus
}
#endif

// t2kstrm.h: the byte reader (inlined at every use).
static __forceinline int ReadUnsignedByteSlow(InputStream* in)
{
    if (in->ReadToRamFunc(in->nonRamID, &in->tmp_ch, in->pos++, 1) < 0) {
        tsi_Error(in->mem, T2K_ERR_TRANS_FAIL);
        return 0;
    }
    return in->tmp_ch;
}

#define ReadUnsignedByteMacro(stream) ((uint8)((stream)->privateBase != 0 ? \
    ((stream)->ReadToRamFunc != 0 ? \
        ((((stream)->pos - (stream)->cachePosition + 1 > (stream)->cacheCount) ? PrimeT2KInputStream(stream) : (void)0), \
         (stream)->privateBase[((stream)->pos)++ - (stream)->cachePosition]) \
      : (stream)->privateBase[((stream)->pos)++]) \
    : ReadUnsignedByteSlow(stream)))

// Leading-operand advance width: the first operand of the first stem/move/endchar
// operator is the width when the operand count says so.
#define T2_CHECK_WIDTH(cond)                                                     \
    if (t->widthDone == 0 && (cond)) {                                           \
        t->widthDone = 1;                                                        \
        if (t->privateDictData.nominalWidthX != 0) {                             \
            t->awx = (int16)(t->gStackValues[0] >> 16) + t->privateDictData.nominalWidthX; \
            i = 1;                                                               \
        }                                                                        \
    }

// @ 0x008bb550
void Type2BuildChar(CFFClass* t, InputStream* in, long byteCount, long recursionLevel)
{
    long v, i, j, n, num, r, rv, sv;
    F16Dot16 dx1, dy1, dx2, dy2, dx3, dy3, dx4, dy4, dx5, dy5, dx6, dy6, dx, dy, adx, ady;
    long k, m, count, regbank, N, J, length, numMasters, numBlends;
    F16Dot16 tmp, a, g, sum, w;
    CFFIndexClass* index;
    unsigned long savePos;
    F16Dot16 x, y;
    F16Dot16* stack;
    unsigned long limit;

    limit = Tell_InputStream(in) + byteCount;
    stack = t->gStackValues;
    x = t->x;
    y = t->y;
    n = t->gNumStackValues;

    while (Tell_InputStream(in) < limit) {
        v = ReadUnsignedByteMacro(in);
        if (v < 32) {
            switch (v) {
            case 1:  /* hstem */
            case 3:  /* vstem */
                i = 0;
                T2_CHECK_WIDTH(n & 1);
                t->numStemHints += (n - i) / 2;
                t->stkClrOpCalled = 1;
                n = 0;
                break;
            case 4: /* vmoveto */
                i = 0;
                T2_CHECK_WIDTH(n > 1);
                y += stack[i];
                t->stkClrOpCalled = 1;
                n = 0;
                if (t->pointAdded) glyph_CloseContour(t->glyph);
                break;
            case 5: /* rlineto */
                glyph_StartLine(t->glyph, x >> 16, y >> 16);
                for (i = 0; i < n;) {
                    x += stack[i++];
                    y += stack[i++];
                    glyph_AddPoint(t->glyph, x >> 16, y >> 16, 1);
                }
                t->pointAdded = 1;
                n = 0;
                break;
            case 6: /* hlineto */
                glyph_StartLine(t->glyph, x >> 16, y >> 16);
                for (i = 0; i < n;) {
                    x += stack[i++];
                    glyph_AddPoint(t->glyph, x >> 16, y >> 16, 1);
                    if (i >= n) break;
                    y += stack[i++];
                    glyph_AddPoint(t->glyph, x >> 16, y >> 16, 1);
                }
                t->pointAdded = 1;
                n = 0;
                break;
            case 7: /* vlineto */
                glyph_StartLine(t->glyph, x >> 16, y >> 16);
                for (i = 0; i < n;) {
                    y += stack[i++];
                    glyph_AddPoint(t->glyph, x >> 16, y >> 16, 1);
                    if (i >= n) break;
                    x += stack[i++];
                    glyph_AddPoint(t->glyph, x >> 16, y >> 16, 1);
                }
                t->pointAdded = 1;
                n = 0;
                break;
            case 8: /* rrcurveto */
                glyph_StartLine(t->glyph, x >> 16, y >> 16);
                for (i = 0; i < n;) {
                    x += stack[i++];
                    y += stack[i++];
                    glyph_AddPoint(t->glyph, x >> 16, y >> 16, 0);
                    x += stack[i++];
                    y += stack[i++];
                    glyph_AddPoint(t->glyph, x >> 16, y >> 16, 0);
                    x += stack[i++];
                    y += stack[i++];
                    glyph_AddPoint(t->glyph, x >> 16, y >> 16, 1);
                }
                t->pointAdded = 1;
                n = 0;
                break;
            case 10: /* callsubr */
            case 29: /* callgsubr */
            {
                CFFIndexClass* index;
                n--;
                m = (int16)(stack[n] >> 16);
                if (v == 10) {
                    m += t->lSubrBias;
                    index = t->lSubr;
                } else {
                    m += t->gSubrBias;
                    index = t->gSubr;
                }
                if (index != 0 && m >= 0 && m < index->count) {
                    unsigned long savePos = Tell_InputStream(in);
                    long length;
                    Seek_InputStream(t->in, index->baseDataOffset + index->offsetArray[m]);
                    length = index->offsetArray[m + 1] - index->offsetArray[m];
                    if (length > 0 && recursionLevel < 10) {
                        t->x = x;
                        t->y = y;
                        t->gNumStackValues = n;
                        Type2BuildChar(t, in, length, recursionLevel + 1);
                        n = t->gNumStackValues;
                        x = t->x;
                        y = t->y;
                    }
                    Seek_InputStream(t->in, savePos);
                }
                break;
            }
            case 11: /* return */
                t->x = x;
                t->y = y;
                t->gNumStackValues = n;
                return;
            case 12: /* escape */
                v = ReadUnsignedByteMacro(in);
                switch (v) {
                case 0: /* dotsection */
                    n = 0;
                    break;
                case 3: /* and */
                    n -= 2;
                    stack[n] = (stack[n] != 0 && stack[n + 1] != 0) ? 0x10000 : 0;
                    n++;
                    break;
                case 4: /* or */
                    n -= 2;
                    stack[n] = (stack[n] != 0 || stack[n + 1] != 0) ? 0x10000 : 0;
                    n++;
                    break;
                case 5: /* not */
                    n -= 1;
                    stack[n] = stack[n] != 0 ? 0 : 0x10000;
                    n++;
                    break;
                case 8: /* store */
                {
                    long regbank, count, k;
                    n -= 4;
                    J = (int16)(stack[n + 1] >> 16);
                    j       = (int16)(stack[n + 2] >> 16);
                    count   = (int16)(stack[n + 3] >> 16);
                    regbank = (int16)(stack[n + 0] >> 16);
                    switch (regbank) {
                    case 0:
                        for (k = 0; k < count; k++) {
                            t->topDictData.reg_WeightVector[J + k] = t->topDictData.buildCharArray[j + k];
                        }
                        break;
                    case 1:
                        for (k = 0; k < count; k++) {
                            t->topDictData.reg_NormalizedDesignVector[J + k] = t->topDictData.buildCharArray[j + k];
                        }
                        break;
                    case 2:
                        for (k = 0; k < count; k++) {
                            t->topDictData.reg_UserDesignVector[J + k] = t->topDictData.buildCharArray[j + k];
                        }
                        break;
                    }
                    break;
                }
                case 9: /* abs */
                    n -= 1;
                    v = stack[n];
                    if (v < 0) stack[n] = -v;
                    n++;
                    break;
                case 10: /* add */
                    n -= 2;
                    stack[n] += stack[n + 1];
                    n++;
                    break;
                case 11: /* sub */
                    n -= 2;
                    stack[n] -= stack[n + 1];
                    n++;
                    break;
                case 12: /* div */
                    n -= 2;
                    stack[n] = util_FixDiv(stack[n], stack[n + 1]);
                    n++;
                    break;
                case 13: /* load */
                {
                    long regbank, count, k;
                    n -= 3;
                    N = (int16)(stack[n + 1] >> 16);
                    count   = (int16)(stack[n + 2] >> 16);
                    regbank = (int16)(stack[n + 0] >> 16);
                    switch (regbank) {
                    case 0:
                        for (k = 0; k < count; k++) {
                            t->topDictData.buildCharArray[N + k] = t->topDictData.reg_WeightVector[k];
                        }
                        break;
                    case 1:
                        for (k = 0; k < count; k++) {
                            t->topDictData.buildCharArray[N + k] = t->topDictData.reg_NormalizedDesignVector[k];
                        }
                        break;
                    case 2:
                        for (k = 0; k < count; k++) {
                            t->topDictData.buildCharArray[N + k] = t->topDictData.reg_UserDesignVector[k];
                        }
                        break;
                    }
                    break;
                }
                case 14: /* neg */
                    n -= 1;
                    stack[n] = -stack[n];
                    n++;
                    break;
                case 15: /* eq */
                    n -= 2;
                    stack[n] = stack[n] == stack[n + 1] ? 0x10000 : 0;
                    n++;
                    break;
                case 18: /* drop */
                    n--;
                    break;
                case 20: /* put */
                    n -= 2;
                    t->topDictData.buildCharArray[(int16)(stack[n + 1] >> 16)] = stack[n];
                    break;
                case 21: /* get */
                    n -= 1;
                    stack[n] = t->topDictData.buildCharArray[(int16)(stack[n] >> 16)];
                    n++;
                    break;
                case 22: /* ifelse */
                    n -= 4;
                    stack[n] = stack[n + 2] <= stack[n + 3] ? stack[n] : stack[n + 1];
                    n++;
                    break;
                case 23: /* random */
                {
                    rv = util_FixMul(stack[2], stack[3]);
                    rv ^= util_FixMul(stack[0], stack[1]);
                    rv ^= ~(n << 10) ^ stack[4];
                    t->seed = (uint16)(t->seed * 58653 + 13849);
                    rv = ((t->seed ^ rv) & 0xffff) + 1;
                    stack[n++] = rv;
                    break;
                }
                case 24: /* mul */
                    n -= 2;
                    stack[n] = util_FixMul(stack[n], stack[n + 1]);
                    n++;
                    break;
                case 26: /* sqrt */
                {
                    F16Dot16 a, g;
                    long k;
                    n -= 1;
                    k = 0;
                    a = stack[n];
                    r = a;
                    do {
                        g = r;
                        r = (util_FixDiv(a, g) + 1 + g) >> 1;
                        if (g == r) break;
                    } while (k++ < 10);
                    stack[n] = r;
                    n++;
                    break;
                }
                case 27: /* dup */
                    n -= 1;
                    stack[n + 1] = stack[n];
                    n += 2;
                    break;
                case 28: /* exch */
                {
                    F16Dot16 tmp;
                    n -= 2;
                    tmp = stack[n];
                    stack[n] = stack[n + 1];
                    stack[n + 1] = tmp;
                    n += 2;
                    break;
                }
                case 29: /* index */
                    i = (int16)(stack[n - 1] >> 16);
                    if (i < 0) {
                        i = 0;
                    } else if (i > n - 2) {
                        i = n - 2;
                    }
                    stack[n - 1] = stack[n - 2 - i];
                    break;
                case 30: /* roll */
                {
                    long N, J, k, m;
                    F16Dot16 tmp;
                    n -= 2;
                    N = (int16)(stack[n] >> 16);
                    if (N < 0) N = 0;
                    J = (int16)(stack[n + 1] >> 16);
                    if (J >= 0) {
                        for (m = 0; m < J; m++) {
                            tmp = stack[n - 1];
                            for (k = 1; k < N; k++) {
                                stack[n - k] = stack[n - k - 1];
                            }
                            stack[n - N] = tmp;
                        }
                    } else {
                        J = -J;
                        for (m = 0; m < J; m++) {
                            tmp = stack[n - N];
                            for (k = N - 1; k > 0; k--) {
                                stack[n - k - 1] = stack[n - k];
                            }
                            stack[n - 1] = tmp;
                        }
                    }
                    break;
                }
                case 34: /* hflex */
                {
                    n -= 7;
                    glyph_StartLine(t->glyph, x >> 16, y >> 16);
                    dx1 = stack[n + 0];
                    dx2 = stack[n + 1];
                    dy2 = stack[n + 2];
                    dx3 = stack[n + 3];
                    dx4 = stack[n + 4];
                    dx5 = stack[n + 5];
                    dx6 = stack[n + 6];
                    x += dx1;
                    glyph_AddPoint(t->glyph, x >> 16, y >> 16, 0);
                    x += dx2; y += dy2;
                    glyph_AddPoint(t->glyph, x >> 16, y >> 16, 0);
                    x += dx3;
                    glyph_AddPoint(t->glyph, x >> 16, y >> 16, 1);
                    x += dx4;
                    glyph_AddPoint(t->glyph, x >> 16, y >> 16, 0);
                    x += dx5; y -= dy2;
                    glyph_AddPoint(t->glyph, x >> 16, y >> 16, 0);
                    x += dx6;
                    glyph_AddPoint(t->glyph, x >> 16, y >> 16, 1);
                    t->pointAdded = 1;
                    break;
                }
                case 35: /* flex */
                {
                    n -= 13;
                    glyph_StartLine(t->glyph, x >> 16, y >> 16);
                    dx1 = stack[n + 0];  dy1 = stack[n + 1];
                    dx2 = stack[n + 2];  dy2 = stack[n + 3];
                    dx3 = stack[n + 4];  dy3 = stack[n + 5];
                    dx4 = stack[n + 6];  dy4 = stack[n + 7];
                    dx5 = stack[n + 8];  dy5 = stack[n + 9];
                    dx6 = stack[n + 10]; dy6 = stack[n + 11];
                    x += dx1; y += dy1;
                    glyph_AddPoint(t->glyph, x >> 16, y >> 16, 0);
                    x += dx2; y += dy2;
                    glyph_AddPoint(t->glyph, x >> 16, y >> 16, 0);
                    x += dx3; y += dy3;
                    glyph_AddPoint(t->glyph, x >> 16, y >> 16, 1);
                    x += dx4; y += dy4;
                    glyph_AddPoint(t->glyph, x >> 16, y >> 16, 0);
                    x += dx5; y += dy5;
                    glyph_AddPoint(t->glyph, x >> 16, y >> 16, 0);
                    x += dx6; y += dy6;
                    glyph_AddPoint(t->glyph, x >> 16, y >> 16, 1);
                    t->pointAdded = 1;
                    break;
                }
                case 36: /* hflex1 */
                {
                    n -= 9;
                    glyph_StartLine(t->glyph, x >> 16, y >> 16);
                    dx1 = stack[n + 0]; dy1 = stack[n + 1];
                    dx2 = stack[n + 2]; dy2 = stack[n + 3];
                    dx3 = stack[n + 4];
                    dx4 = stack[n + 5];
                    dx5 = stack[n + 6]; dy5 = stack[n + 7];
                    dx6 = stack[n + 8];
                    x += dx1; y += dy1;
                    glyph_AddPoint(t->glyph, x >> 16, y >> 16, 0);
                    x += dx2; y += dy2;
                    glyph_AddPoint(t->glyph, x >> 16, y >> 16, 0);
                    x += dx3;
                    glyph_AddPoint(t->glyph, x >> 16, y >> 16, 1);
                    x += dx4;
                    glyph_AddPoint(t->glyph, x >> 16, y >> 16, 0);
                    x += dx5; y += dy5;
                    glyph_AddPoint(t->glyph, x >> 16, y >> 16, 0);
                    x += dx6; y -= dy1 + dy2 + dy5;
                    glyph_AddPoint(t->glyph, x >> 16, y >> 16, 1);
                    t->pointAdded = 1;
                    break;
                }
                case 37: /* flex1 */
                {
                    n -= 11;
                    glyph_StartLine(t->glyph, x >> 16, y >> 16);
                    dx1 = stack[n + 0]; dy1 = stack[n + 1];
                    dx2 = stack[n + 2]; dy2 = stack[n + 3];
                    dx3 = stack[n + 4]; dy3 = stack[n + 5];
                    dx4 = stack[n + 6]; dy4 = stack[n + 7];
                    dx5 = stack[n + 8]; dy5 = stack[n + 9];
                    dx = dx1 + dx2 + dx3 + dx4 + dx5;
                    dy = dy1 + dy2 + dy3 + dy4 + dy5;
                    adx = dx;
                    ady = dy;
                    adx = ABS(adx);
                    ady = ABS(ady);
                    if (adx > ady) {
                        dx6 = stack[n + 10];
                        dy6 = -dy;
                    } else {
                        dx6 = -dx;
                        dy6 = stack[n + 10];
                    }
                    x += dx1; y += dy1;
                    glyph_AddPoint(t->glyph, x >> 16, y >> 16, 0);
                    x += dx2; y += dy2;
                    glyph_AddPoint(t->glyph, x >> 16, y >> 16, 0);
                    x += dx3; y += dy3;
                    glyph_AddPoint(t->glyph, x >> 16, y >> 16, 1);
                    x += dx4; y += dy4;
                    glyph_AddPoint(t->glyph, x >> 16, y >> 16, 0);
                    x += dx5; y += dy5;
                    glyph_AddPoint(t->glyph, x >> 16, y >> 16, 0);
                    x += dx6; y += dy6;
                    glyph_AddPoint(t->glyph, x >> 16, y >> 16, 1);
                    t->pointAdded = 1;
                    break;
                }
                default:
                    break;
                }
                break;
            case 14: /* endchar */
                t->x = x;
                t->y = y;
                t->gNumStackValues = n;
                i = 0;
                T2_CHECK_WIDTH(n > 0);
                t->stkClrOpCalled = 1;
                n = 0;
                break;
            case 16: /* blend */
            {
                long numMasters = t->topDictData.numMasters;
                long numBlends, k;
                n--;
                numBlends = (int16)(stack[n] >> 16);
                n -= numBlends * numMasters;
                for (k = 0; k < numBlends; k++) {
                    F16Dot16 sum = stack[n + k];
                    for (j = 1; j < numMasters; j++) {
                        F16Dot16 w = t->topDictData.defaultWeight[j];
                        sum += util_FixMul(w, stack[n + k + j * numMasters]);
                    }
                    stack[n + k] = sum;
                }
                n += numBlends;
                break;
            }
            case 18: /* hstemhm */
            case 23: /* vstemhm */
                i = 0;
                T2_CHECK_WIDTH(n & 1);
                t->numStemHints += (n - i) / 2;
                t->stkClrOpCalled = 1;
                n = 0;
                break;
            case 19: /* hintmask */
            case 20: /* cntrmask */
                i = 0;
                if (t->stkClrOpCalled == 0 && t->widthDone == 0 && n > 0) {
                    t->widthDone = 1;
                    if (t->privateDictData.nominalWidthX != 0) {
                        t->awx = (int16)(t->gStackValues[0] >> 16) + t->privateDictData.nominalWidthX;
                        i = 1;
                    }
                }
                for (; i < n; i += 2) {
                    t->numStemHints++;
                }
                k = (t->numStemHints + 7) >> 3;
                while (k > 0) {
                    k--;
                    Seek_InputStream(in, in->pos + 1);
                }
                t->stkClrOpCalled = 1;
                n = 0;
                break;
            case 21: /* rmoveto */
                i = 0;
                T2_CHECK_WIDTH(n > 2);
                x += stack[i];
                y += stack[i + 1];
                t->stkClrOpCalled = 1;
                n = 0;
                if (t->pointAdded) glyph_CloseContour(t->glyph);
                break;
            case 22: /* hmoveto */
                i = 0;
                T2_CHECK_WIDTH(n > 1);
                x += stack[i];
                t->stkClrOpCalled = 1;
                n = 0;
                if (t->pointAdded) glyph_CloseContour(t->glyph);
                break;
            case 24: /* rcurveline */
                glyph_StartLine(t->glyph, x >> 16, y >> 16);
                for (i = 0; i + 6 <= n;) {
                    x += stack[i++];
                    y += stack[i++];
                    glyph_AddPoint(t->glyph, x >> 16, y >> 16, 0);
                    x += stack[i++];
                    y += stack[i++];
                    glyph_AddPoint(t->glyph, x >> 16, y >> 16, 0);
                    x += stack[i++];
                    y += stack[i++];
                    glyph_AddPoint(t->glyph, x >> 16, y >> 16, 1);
                }
                x += stack[i++];
                y += stack[i++];
                glyph_AddPoint(t->glyph, x >> 16, y >> 16, 1);
                n = 0;
                t->pointAdded = 1;
                break;
            case 25: /* rlinecurve */
                glyph_StartLine(t->glyph, x >> 16, y >> 16);
                for (i = 0; i + 6 < n;) {
                    x += stack[i++];
                    y += stack[i++];
                    glyph_AddPoint(t->glyph, x >> 16, y >> 16, 1);
                }
                x += stack[i++];
                y += stack[i++];
                glyph_AddPoint(t->glyph, x >> 16, y >> 16, 0);
                x += stack[i++];
                y += stack[i++];
                glyph_AddPoint(t->glyph, x >> 16, y >> 16, 0);
                x += stack[i++];
                y += stack[i++];
                glyph_AddPoint(t->glyph, x >> 16, y >> 16, 1);
                t->pointAdded = 1;
                n = 0;
                break;
            case 26: /* vvcurveto */
                glyph_StartLine(t->glyph, x >> 16, y >> 16);
                i = 0;
                if (n & 1) x += stack[i++];
                for (; i + 4 <= n;) {
                    y += stack[i++];
                    glyph_AddPoint(t->glyph, x >> 16, y >> 16, 0);
                    x += stack[i++];
                    y += stack[i++];
                    glyph_AddPoint(t->glyph, x >> 16, y >> 16, 0);
                    y += stack[i++];
                    glyph_AddPoint(t->glyph, x >> 16, y >> 16, 1);
                }
                t->pointAdded = 1;
                n = 0;
                break;
            case 27: /* hhcurveto */
                glyph_StartLine(t->glyph, x >> 16, y >> 16);
                i = 0;
                if (n & 1) y += stack[i++];
                for (; i + 4 <= n;) {
                    x += stack[i++];
                    glyph_AddPoint(t->glyph, x >> 16, y >> 16, 0);
                    x += stack[i++];
                    y += stack[i++];
                    glyph_AddPoint(t->glyph, x >> 16, y >> 16, 0);
                    x += stack[i++];
                    glyph_AddPoint(t->glyph, x >> 16, y >> 16, 1);
                }
                t->pointAdded = 1;
                n = 0;
                break;
            case 28: /* shortint */
                sv  = ReadUnsignedByteMacro(in);
                sv <<= 8;
                sv |= ReadUnsignedByteMacro(in);
                if (n < T2_MAX_STACK) {
                    stack[n++] = sv << 16;
                }
                break;
            case 30: /* vhcurveto */
                glyph_StartLine(t->glyph, x >> 16, y >> 16);
                for (i = 0; i + 4 <= n;) {
                    y += stack[i++];
                    glyph_AddPoint(t->glyph, x >> 16, y >> 16, 0);
                    x += stack[i++];
                    y += stack[i++];
                    glyph_AddPoint(t->glyph, x >> 16, y >> 16, 0);
                    x += stack[i++];
                    if (i + 1 == n) y += stack[i++];
                    glyph_AddPoint(t->glyph, x >> 16, y >> 16, 1);
                    if (i + 4 > n) break;
                    x += stack[i++];
                    glyph_AddPoint(t->glyph, x >> 16, y >> 16, 0);
                    x += stack[i++];
                    y += stack[i++];
                    glyph_AddPoint(t->glyph, x >> 16, y >> 16, 0);
                    y += stack[i++];
                    if (i + 1 == n) x += stack[i++];
                    glyph_AddPoint(t->glyph, x >> 16, y >> 16, 1);
                }
                t->pointAdded = 1;
                n = 0;
                break;
            case 31: /* hvcurveto */
                glyph_StartLine(t->glyph, x >> 16, y >> 16);
                for (i = 0; i + 4 <= n;) {
                    x += stack[i++];
                    glyph_AddPoint(t->glyph, x >> 16, y >> 16, 0);
                    x += stack[i++];
                    y += stack[i++];
                    glyph_AddPoint(t->glyph, x >> 16, y >> 16, 0);
                    y += stack[i++];
                    if (i + 1 == n) x += stack[i++];
                    glyph_AddPoint(t->glyph, x >> 16, y >> 16, 1);
                    if (i + 4 > n) break;
                    y += stack[i++];
                    glyph_AddPoint(t->glyph, x >> 16, y >> 16, 0);
                    x += stack[i++];
                    y += stack[i++];
                    glyph_AddPoint(t->glyph, x >> 16, y >> 16, 0);
                    x += stack[i++];
                    if (i + 1 == n) y += stack[i++];
                    glyph_AddPoint(t->glyph, x >> 16, y >> 16, 1);
                }
                t->pointAdded = 1;
                n = 0;
                break;
            default: /* 0, 2, 9, 13, 15, 17: reserved */
                break;
            }
        } else {
            /* operand */
            if (v <= 246) {
                num = (v - 139) << 16;
            } else if (v <= 250) {
                num = ((v - 247) * 256 + ReadUnsignedByteMacro(in) + 108) << 16;
            } else if (v <= 254) {
                num = (-(v - 251) * 256 - ReadUnsignedByteMacro(in) - 108) << 16;
            } else {
                num  = ReadUnsignedByteMacro(in);
                num <<= 8;
                num |= ReadUnsignedByteMacro(in);
                num <<= 8;
                num |= ReadUnsignedByteMacro(in);
                num <<= 8;
                num |= ReadUnsignedByteMacro(in);
            }
            if (n < T2_MAX_STACK) {
                stack[n++] = num;
            }
        }
    }
    t->x = x;
    t->y = y;
    t->gNumStackValues = n;
}
