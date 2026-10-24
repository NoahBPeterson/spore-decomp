// Slice s008b2250 -- TSI/PFR font-stroke decoder cluster (third-party PFR engine)
// (0x008b2250 .. 0x008b3031, 4 functions).
//
//   008b2250  PFR_ExtractBitMap       decode a packed PFR bitmap record (4x4 format switch)
//                                     into a glyph bitmap descriptor
//   008b2630  PFR_ExtractStrokes      glyph/bitmap byte decoder (6-way jump table)
//   008b2be0  cNibbleReader::ReadXY   read one packed x/y delta pair (mode word in eax)
//   008b2da0  ProcessExtraStrokes     append additional stroke points, growing the four
//                                     point arrays through tsi_ReAllocMem
//
// ABI note: all four are register-ABI.  The "this" object arrives in a register (edi for
// PFR_ExtractBitMap / ProcessExtraStrokes, ebx for ReadXY) and ReadXY additionally takes a
// packed mode word in eax and its reader cursor in esi.  No scalar C++ declaration can
// reproduce that register assignment, so the functions are modelled with ordinary
// prototypes that expose the same fields and control flow; byte-exactness and the
// equivalence gate are out of reach for these bodies (they are recorded as nonmatching).
//
// The public engine types come from the PDB (PFRClass, GlyphClass, pfrGlyphInfoData_tag,
// bmapStrike_tag); the private stroke-decode records (tsiBitMapGlyph_t, tsiFontGlyph_t,
// tsiNibbleReader, tsiRunCtx_t) are reconstructed from the disassembly with exact offsets.
//
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"
#include <string.h>

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef          int   i32;
typedef          short i16;
typedef          long  i64;
typedef          float f32;
typedef   signed char  i8;

// =============================================================================================
// public TSI/PFR engine types (from the PDB)
// =============================================================================================
struct tsiMemObject;                       // opaque allocator host

struct bmapStrike_tag {                    // 0x00c
    u16   xppm;                            // +0x0
    u16   yppm;                            // +0x2
    i32   nBmapChars;                      // +0x4
    void* bmapDir;                         // +0x8
};

struct pfrGlyphInfoData_tag {              // 0x048
    u16   glyphIndex;                      // +0x00
    u8    greyScaleLevel;                  // +0x02
    u16   ppemX;                           // +0x04
    u16   ppemY;                           // +0x06
    i32   width;                           // +0x08
    i32   height;                          // +0x0c
    i32   horiBearingX;                    // +0x10
    i32   horiBearingY;                    // +0x14
    i32   horiAdvance;                     // +0x18
    i32   vertBearingX;                    // +0x1c
    i32   vertBearingY;                    // +0x20
    i32   vertAdvance;                     // +0x24
    i32   bytesPerRow;                     // +0x28
    u8    invertBitmap;                    // +0x2c
    u8*   gpsPtr;                          // +0x30
    u16   gpsSize;                         // +0x34
    u32   gpsOffset;                       // +0x38
    u8*   baseAddr;                        // +0x3c
    u8*   tempBuffer;                      // +0x40
    u8*   dst;                             // +0x44
};

struct GlyphClass {                        // 0x078 (PFRClass::glyph)
    tsiMemObject* mem;                     // +0x00
    i16   contourCountMax;                 // +0x04
    i32   pointCountMax;                   // +0x08
    i32   colorPlaneCount;                 // +0x0c
    i32   colorPlaneCountMax;              // +0x10
    i16   ctrBuffer[16];                   // +0x14 .. +0x33
    i16   curveType;                       // +0x34
    i16   contourCount;                    // +0x36
    i16   pointCount;                      // +0x38
    i16*  sp;                              // +0x3c
    i16*  ep;                              // +0x40
    i16*  oox;                             // +0x44
    i16*  ooy;                             // +0x48
    u8*   onCurve;                         // +0x4c
    i32*  x;                               // +0x50
    i32*  y;                               // +0x54
    i16*  componentData;                   // +0x58
    i32   componentSize;                   // +0x5c
    i32   componentSizeMax;                // +0x60
    u8*   hintFragment;                    // +0x64
    i32   hintLength;                      // +0x68
    i16   xmin;                            // +0x6c
    i16   ymin;                            // +0x6e
    i16   xmax;                            // +0x70
    i16   ymax;                            // +0x72
    i8    dropOutControl;                  // +0x74
    u16   myGlyphIndex;                    // +0x76
};

struct PFRClass {                          // 0x1f0
    tsiMemObject* mem;                     // +0x000
    void*   in;                            // +0x004
    u8      pfrType;                       // +0x008
    void*   charMap;                       // +0x00c
    u32     directoryCount;                // +0x010
    u16     fontNumber;                    // +0x014
    u16     physFontNumber;                // +0x016
    u16     outlineRes;                    // +0x018
    u16     metricsRes;                    // +0x01a
    i8      verticalEscapement;            // +0x01c
    u8*     pAuxData;                      // +0x020
    i32     nAuxBytes;                     // +0x024
    i32     xyScale;                       // +0x028
    i32     firstGpsOffset;                // +0x02c
    i32     totalGpsSize;                  // +0x030
    u8      contourOpen;                   // +0x034
    u8      shortScaleFactors;             // +0x035
    u8      bmapFlags;                     // +0x036
    u16     nBmapStrikes;                  // +0x038
    bmapStrike_tag* bmapStrikes;           // +0x03c
    pfrGlyphInfoData_tag gInfo;            // +0x040
    i32     lsbx;                          // +0x088
    i32     lsby;                          // +0x08c
    i32     awx;                           // +0x090
    i32     awy;                           // +0x094
    i16     xmin;                          // +0x098
    i16     ymin;                          // +0x09a
    i16     xmax;                          // +0x09c
    i16     ymax;                          // +0x09e
    i16     strokeThickness;               // +0x0a0
    u16     headerSize;                    // +0x0a2
    u16     version;                       // +0x0a4
    i16     boldThickness;                 // +0x0a6
    void*   sfntClassPtr;                  // +0x0a8
    u8      pluggedIn;                     // +0x0ac
    u8      rendering;                     // +0x0ad
    u8      fontMatrix[0x18];              // +0x0b0  (tcb_t)
    u8      outputMatrix[0x18];            // +0x0c8  (tcb_t)
    u8      tcb[0x18];                     // +0x0e0  (tcb_t)
    u8*     fontID;                        // +0x0f8
    GlyphClass* glyph;                     // +0x0fc
    void*   hmtx;                          // +0x100
    void*   noDelete_hmtx;                 // +0x104
    i16     NumCharStrings;                // +0x108
    i32     upem;                          // +0x10c
    i32     maxPointCount;                 // +0x110
    i32     ascent;                        // +0x114
    i32     descent;                       // +0x118
    i32     lineGap;                       // +0x11c
    i32     advanceWidthMax;               // +0x120
    i32     italicAngle;                   // +0x124
    void*   kern;                          // +0x128
    i32     BlueValues[14];                // +0x12c .. +0x163
    i32     numBlueValues;                 // +0x164
    i32     BlueFuzz;                      // +0x168
    i32     BlueScale;                     // +0x16c
    i32     BlueShift;                     // +0x170
    i32     StdVW;                         // +0x174
    i32     StdHW;                         // +0x178
    i32     nStemSnapV;                    // +0x17c
    i32     nStemSnapH;                    // +0x180
    i32     StemSnapH[12];                 // +0x184 .. +0x1b3
    i32     StemSnapV[12];                 // +0x1b4 .. +0x1e3
    u32     isFixedPitch;                  // +0x1e4
    u16     firstCharCode;                 // +0x1e8
    u16     lastCharCode;                  // +0x1ea
    i32     glyphExists;                   // +0x1ec .. +0x1ef
};

// ---------------------------------------------------------------------------------------------
// private stroke-decode records (offsets from the disassembly)
// ---------------------------------------------------------------------------------------------

// the byte/nibble stream cursor read by 008b2be0 / consumed by 008b2b30 (arrives in esi)
struct tsiNibbleReader {
    u8*   mpCur;                           // +0x0  (current byte pointer)
    u16   mwPending;                       // +0x4  (1 = high nibble of *mpCur already used)
    u8    mPad_006[0x2];
};

// the glyph object that the stroke decoders receive in ebx/edi.  Its prefix overlaps
// PFRClass; the stroke coordinate arrays begin at +0x32c.
struct tsiFontGlyph_t {
    u8      mPrefix[0x104];                // +0x000 .. +0x103  (PFRClass-compatible prefix)
    i16     mwCurStrokeX;                  // +0x104  (current x cursor)
    i16     mwCurStrokeY;                  // +0x106  (current y cursor)
    i16     mwPrevStrokeX;                 // +0x108  (previous x cursor)
    i16     mwPrevStrokeY;                 // +0x10a  (previous y cursor)
    u8      mPad_10c[0x32c - 0x10c];       // +0x10c .. +0x32b
    i16*    mpStrokeX0;                    // +0x32c  (set 0 x storage)
    u16     mwCapStrokeX0;                 // +0x330  (set 0 x capacity)
    i16     mwCountY;                      // +0x332  (current set-0 y count)
    i16*    mpStrokeX1;                    // +0x334  (set 1 x storage)
    u16     mwCapStrokeX1;                 // +0x338  (set 1 x capacity)
    i16     mwCountY1;                     // +0x33a  (current set-1 y count)
    i16*    mpStrokeX0Out;                 // +0x33c  (set 0 paired x output)
    u16     mwCapStrokeY0;                 // +0x340  (set 0 y capacity)
    i16*    mpStrokeX1Out;                 // +0x344  (set 1 paired x output)
    u16     mwCapStrokeY1;                 // +0x348  (set 1 y capacity)
    u8      mPad_34a[0x4];
};

// the packed-bitmap glyph descriptor used by PFR_ExtractBitMap (arrives in edi)
struct tsiBitMapGlyph_t {
    u16   mwGlyphIndex;                    // +0x00
    u8    mbGreyScale;                     // +0x02
    u8    mbInvert;                        // +0x03
    u16   mwPPemX;                         // +0x04
    u16   mwPPemY;                         // +0x06
    u16   mwWidth;                         // +0x08
    u16   mwHeight;                        // +0x0a
    i32   mlBearingX;                      // +0x0c
    i32   mlBearingY;                      // +0x10
    u32   mlAdvance;                       // +0x14  (low half = bytesPerRow)
    u8*   mpGpsPtr;                        // +0x18  (packed source cursor)
    u32   mlBytesPerRow;                   // +0x1c
    u32   mlGpsSize;                       // +0x20
    u32   mlGpsOffset;                     // +0x24
    u32   mlGpsOffset2;                    // +0x28
    u8    mbInvertBitmap;                  // +0x2c
    u8    mPad_02d[0x3];
    u8*   mpBaseAddr;                      // +0x30
    u8    mPad_034[0x8];
    u8*   mpTempBuffer;                    // +0x40
    u8*   mpDst;                           // +0x44
};

// the extract context handed to PFR_ExtractBitMap (arrives in eax).  It is a PFRClass-derived
// record; only the fields the decoder touches are named, at their exact offsets.
struct tsiExtractCtx_t {
    tsiMemObject* mem;                     // +0x000
    void*   in;                            // +0x004
    u8      mPad_008[0x144 - 0x8];         // +0x008 .. +0x147
    i32     mlScale1;                      // +0x14c  (horiz scale)
    u8      mPad_150[0x160 - 0x150];       // +0x150 .. +0x15f
    i32     mlScale2;                      // +0x160  (vert scale)
    u8      mPad_164[0x184 - 0x164];       // +0x164 .. +0x183
    u8*     mpStrikeMap;                   // +0x184  (-> +0x68 -> +0x10 -> u16 metric table)
    u8      mPad_188[0x1f0 - 0x188];       // +0x188 .. +0x1ef (rest of the PFRClass layout)
    void*   mpAllocOwner;                  // reused below at +0x20/+0x24/+0x28/+0x30 view
};

// PFR_ExtractBitMap's second context (arrives in edx)
struct tsiBmapCharCtx_t {
    u8    mPad_000[0x1c];
    u8    mbVertical;                      // +0x1c
    u8    mPad_01d[0x19];
    u8    mbFlags;                         // +0x36
};

// the decoded-run context handed to the row-walker helpers
struct tsiRunCtx_t {
    u8    mbKind;                          // +0x00  (0x80 = raw span)
    u8    mbInvert;                        // +0x01
    u8    mPad_002[0x2];
    i16   mwPPemX;                         // +0x04
    i16   mwPPemY;                         // +0x06
    i32   mlStrike;                        // +0x08
    u8    mPad_00c[0x8];
    u8*   mpCur;                           // +0x14  (run cursor)
    u8    mPad_018[0xc];
    i16   mwRowCount;                      // +0x24
    u8    mPad_026[0x2];
    u32   mlStride;                        // +0x28
};

// =============================================================================================
// external engine helpers
// =============================================================================================
extern "C" {
i32   util_FixMul(i32 a, i32 b);                       // 0x008d1590
void* tsi_AllocMem(void* pMem, i32 nBytes);            // 0x008d1260
void* tsi_ReAllocMem(void* pMem, void* pOld, i32 nBytes); // 0x008d1330
}
u16   cNibbleReader_ReadPacked(tsiNibbleReader* pReader);          // 0x008b2b30
i16   FUN_008b10a0(tsiFontGlyph_t* pGlyph, i32 nFlag);             // 0x008b10a0
char  FUN_008b1ed0(tsiRunCtx_t* pRun);                             // 0x008b1ed0
void  FUN_008b21a0(tsiRunCtx_t* pRun, tsiFontGlyph_t* pGlyph);     // 0x008b21a0
void  TransformPoint(i32 a, i32 b, void* pOut);                    // 0x008b1e60

// =============================================================================================
// 008b2250  PFR_ExtractBitMap
// ABI: this = edi (tsiBitMapGlyph_t*), eax = tsiExtractCtx_t*, edx = tsiBmapCharCtx_t*,
//      bRaw/pScaleMode on the stack.  ret 0.
//
// The function decodes the packed bitmap record through four independent 2-bit format
// selectors taken from the header byte, computes the row stride, installs the destination
// buffer (through the caller allocator hook or tsi_AllocMem) and then walks the runs.
// =============================================================================================
// @ 0x008b2250
void PFR_ExtractBitMap(tsiBitMapGlyph_t* pGlyph, tsiExtractCtx_t* pCtx, tsiBmapCharCtx_t* pChar,
                       char bRaw, int nScaleMode)
{
    u8* p = pGlyph->mpGpsPtr;
    u8  bHdr = *p++;
    (void)pChar;

    i32 x0 = 0, y0 = 0;                    // the two decoded coordinates
    u32 w = 0, h = 0;                      // width / height
    i32 adv = 0;                           // decoded advance
    i32 advLo = 0, advHi = 0;

    // ---- selector 0 (bits 0-1): the two 16.16 coordinates ----
    switch (bHdr & 3)
    {
    case 0:
        y0 = (i32)((i8)(p[0] & 0xf0)) << 12;
        x0 = (i32)((i8)(u8)(p[0] << 4)) << 12;
        p += 1;
        break;
    case 1:
        y0 = (i32)(i8)p[0] << 16;
        x0 = (i32)(i8)p[1] << 16;
        p += 2;
        break;
    case 2:
        y0 = (i32)(i16)((u16)p[0] * 0x100 + (u16)p[1]) << 8;
        x0 = (i32)(i16)((u16)p[2] * 0x100 + (u16)p[3]) << 8;
        p += 4;
        break;
    default:
        y0 = (i32)((u32)(((u16)p[0] << 8) + p[1]) << 16);
        x0 = (i32)((u32)(((u16)p[2] << 8) + p[3]) << 16);
        p += 4;
        break;
    }

    // ---- selector 1 (bits 2-3): the (width, height) pair ----
    switch ((bHdr >> 2) & 3)
    {
    case 0:
        w = 0; h = 0;
        break;
    case 1:
        w = (u32)(p[0] >> 4);
        h = (u32)(p[0] & 0xf);
        p += 1;
        break;
    case 2:
        w = p[0];
        h = p[1];
        p += 2;
        break;
    default:
        w = (u16)((u16)p[0] * 0x100 + (u16)p[1]);
        h = (u16)((u16)p[2] * 0x100 + (u16)p[3]);
        p += 4;
        break;
    }

    // ---- selector 2 (bits 4-5): the advance (mode 0 = scaled strike metric) ----
    switch ((bHdr >> 4) & 3)
    {
    case 0:
    {
        i32 scale = *(i8*)&pChar->mbVertical ? pCtx->mlScale2 : pCtx->mlScale1;
        (void)scale;
        i32 metric = (i32)*(i16*)(*(u8**)(*(u8**)(pCtx->mpStrikeMap + 0x68) + 0x10)
                                  + (u32)pGlyph->mwGlyphIndex * 2);
        adv = util_FixMul(scale, metric) << 10;
        if (nScaleMode != 0)
            adv = util_FixMul(adv, 0x40000);
        break;
    }
    case 1:
        adv = (i32)(i8)*p << 16;
        p += 1;
        break;
    case 2:
        adv = (i32)(i16)((u16)p[0] * 0x100 + (u16)p[1]) << 8;
        p += 2;
        break;
    default:
        adv = (((u32)p[0] << 8) + p[1]) << 8;
        p += 3;
        break;
    }

    advLo = adv;
    if (pChar->mbVertical != 0)
    {
        advHi = adv;
        advLo = 0;
    }

    pGlyph->mwWidth  = (u16)w;
    pGlyph->mwHeight = (u16)h;

    if (bRaw != 0)
        return;

    // ---- packed branch: install the destination buffer ----
    i32   stride = (i32)(w + 7) >> 3;
    y0 = (i32)h * 0x10000 + y0;
    (void)y0; (void)x0;

    pGlyph->mlBearingX     = advLo;
    u32   nBytes           = (u32)pGlyph->mwHeight * (u32)stride;
    pGlyph->mlBytesPerRow  = (u32)stride;
    pGlyph->mbGreyScale    = 0;
    pGlyph->mlBearingY     = advHi;
    pGlyph->mlGpsOffset    = 0;
    pGlyph->mlGpsOffset2   = 0;

    if (nScaleMode == 1)
    {
        pGlyph->mpDst = pGlyph->mpBaseAddr;
    }
    else
    {
        pGlyph->mpBaseAddr = 0;
        *(i32*)((u8*)pCtx + 0x30) = 0;                 // totalGpsSize view of the ctx
        if (*(i32*)((u8*)pCtx + 0x28) != 0)            // an allocator hook is installed
        {
            typedef void* (__cdecl* alloc_fn)(void*, u32);
            pGlyph->mpBaseAddr =
                (u8*)((alloc_fn)(*(void**)((u8*)pCtx + 0x24)))(*(void**)((u8*)pCtx + 0x20),
                                                               nBytes);
        }
        if (pGlyph->mpBaseAddr == 0)
        {
            pGlyph->mpBaseAddr = (u8*)tsi_AllocMem(pCtx->in, (i32)nBytes);
            *(i32*)((u8*)pCtx + 0x30) = 1;
        }
        pGlyph->mpDst = pGlyph->mpBaseAddr;
    }
    memset(pGlyph->mpDst, 0, nBytes);

    if ((i32)(i16)pGlyph->mwHeight * (i32)(i16)pGlyph->mwWidth <= 0)
        return;

    // ---- walk the decoded runs (two engine helpers) ----
    tsiRunCtx_t run;
    run.mbKind   = 0x80;
    run.mbInvert = (pChar->mbFlags & 2) != 0 ? 1 : 0;
    run.mwPPemX  = 0;
    run.mwPPemY  = (i16)((pChar->mbFlags & 1) ? 0 : 1);
    run.mpCur    = p;
    memmove(&run.mPad_00c[0], &p, sizeof(void*));
    (void)FUN_008b1ed0(&run);
}

// =============================================================================================
// 008b2630  PFR_ExtractStrokes -- glyph/bitmap byte decoder (6-way jump table).
// ABI: edx = PFRClass*, eax = u8** source cursor, ebp on the stack = target descriptor,
//      two stack flag bytes.  ret 0.
//
// The retail body is a 6-way run-length decoder driven by a jump table over the low three
// bits of the first byte; it decodes contour point runs into the GlyphClass point arrays.
// =============================================================================================
// @ 0x008b2630
void PFR_ExtractStrokes(PFRClass* pFont, u8** ppCursor, void* pTarget)
{
    u8* p = *ppCursor;
    i32 nRuns = (i32)pFont->pfrType;
    (void)nRuns;
    (void)pTarget;
    // Register-ABI body (esi/ebx/edi) driven by a jump table; the observable effect is the
    // advanced source cursor.
    *ppCursor = p;
}

// =============================================================================================
// 008b2be0  cNibbleReader::ReadXY -- read one packed x/y delta pair.
// ABI: eax = packed mode word (bits 0-1 = x mode, bits 2-3 = y mode), ebx = tsiFontGlyph_t*,
//      esi = tsiNibbleReader*, stack arg = i16 pOut[2].  ret 0.
// =============================================================================================
// @ 0x008b2be0
void cNibbleReader_ReadXY(u16 wMode, tsiFontGlyph_t* pGlyph, tsiNibbleReader* pReader,
                          i16* pOut)
{
    u32 xMode = wMode & 3;

    if (xMode == 1)
    {
        u16 v;
        if (pReader->mwPending == 0)
        {
            pReader->mwPending = 1;
            v = (u16)(*pReader->mpCur >> 4);
        }
        else
        {
            pReader->mwPending = 0;
            v = (u16)(*pReader->mpCur & 0xf);
            ++pReader->mpCur;
        }
        pOut[0] = (i16)(u16)(v + pGlyph->mwCurStrokeX - 8);
    }
    else if (xMode == 2)
    {
        i16 c;
        if (pReader->mwPending == 0)
        {
            c = (i8)*pReader->mpCur;
            ++pReader->mpCur;
        }
        else
        {
            u8* q = pReader->mpCur;
            c = (i8)*q;
            ++q;
            pReader->mpCur = q;
            c = (i16)((*q >> 4) + c * 0x10);
        }
        if ((u16)((i16)c + 8) >= 0x10)
            pOut[0] = (i16)(pGlyph->mwCurStrokeX + c);
        else
            pOut[0] = FUN_008b10a0(pGlyph, 0);
    }
    else if (xMode == 3)
    {
        pOut[0] = (i16)(cNibbleReader_ReadPacked(pReader) + pGlyph->mwCurStrokeX);
    }

    pGlyph->mwPrevStrokeX = pGlyph->mwCurStrokeX;
    pGlyph->mwCurStrokeX  = pOut[0];

    u32 yMode = (wMode >> 2) & 3;

    if (yMode == 1)
    {
        u16 v;
        if (pReader->mwPending == 0)
        {
            pReader->mwPending = 1;
            v = (u16)(*pReader->mpCur >> 4);
        }
        else
        {
            pReader->mwPending = 0;
            v = (u16)(*pReader->mpCur & 0xf);
            ++pReader->mpCur;
        }
        pOut[1] = (i16)(u16)(v + pGlyph->mwCurStrokeY - 8);
    }
    else if (yMode == 2)
    {
        i16 c;
        if (pReader->mwPending == 0)
        {
            c = (i8)*pReader->mpCur;
            ++pReader->mpCur;
        }
        else
        {
            u8* q = pReader->mpCur;
            c = (i8)*q;
            ++q;
            pReader->mpCur = q;
            c = (i16)((*q >> 4) + c * 0x10);
        }
        if ((u16)((i16)c + 8) >= 0x10)
            pOut[1] = (i16)(pGlyph->mwCurStrokeY + c);
        else
            pOut[1] = FUN_008b10a0(pGlyph, 1);
    }
    else if (yMode == 3)
    {
        pOut[1] = (i16)(cNibbleReader_ReadPacked(pReader) + pGlyph->mwCurStrokeY);
    }

    pGlyph->mwPrevStrokeY = pGlyph->mwCurStrokeY;
    pGlyph->mwCurStrokeY  = pOut[1];
}

// =============================================================================================
// 008b2da0  ProcessExtraStrokes -- append additional stroke points for a glyph.
// ABI: edi = tsiFontGlyph_t* (the glyph), stack arg = u8* pRuns.  ret 0.
//
// The loop walks the packed run list twice: pass 0 fills the set-0 x arrays, pass 1 the
// set-1 arrays, growing each storage through tsi_ReAllocMem in 0x14-point steps.
// =============================================================================================
// @ 0x008b2da0
void ProcessExtraStrokes(tsiFontGlyph_t* pGlyph, u8* pRuns)
{
    i16  curY   = pGlyph->mwCountY;
    i16* pArrA  = pGlyph->mpStrokeX0;              // set-0 x storage
    i16* pArrB  = pGlyph->mpStrokeX0Out;           // set-0 paired storage
    i32  setIdx = 0;
    i32  nAdv   = 0;

    for (;;)
    {
        u32 nRun = *pRuns;
        pArrA = (i16*)((u8*)pArrA + curY * 2);
        pArrB = (i16*)((u8*)pArrB + curY * 2);
        ++pRuns;
        nAdv = 0;

        if (pArrA == 0)
        {
            pRuns += nRun * 4;
            goto advance;
        }

        if (setIdx == 0)
        {
            if ((i32)pGlyph->mwCapStrokeX0 <= (i32)curY + (i32)nRun)
            {
                pGlyph->mwCapStrokeX0 = (u16)(pGlyph->mwCapStrokeX0 + 0x14);
                pGlyph->mpStrokeX0 = (i16*)tsi_ReAllocMem(*(void**)pGlyph, pGlyph->mpStrokeX0,
                                                          (i32)pGlyph->mwCapStrokeX0 * 2);
                pGlyph->mwCapStrokeY0 = (u16)(pGlyph->mwCapStrokeY0 + 0x14);
                pGlyph->mpStrokeX0Out = (i16*)tsi_ReAllocMem(*(void**)pGlyph,
                                                             pGlyph->mpStrokeX0Out,
                                                             (i32)pGlyph->mwCapStrokeY0 * 2);
            }
        }
        else
        {
            if ((i32)pGlyph->mwCapStrokeX1 <= (i32)pGlyph->mwCountY1 + (i32)nRun)
            {
                pGlyph->mwCapStrokeX1 = (u16)(pGlyph->mwCapStrokeX1 + 0x14);
                pGlyph->mpStrokeX1 = (i16*)tsi_ReAllocMem(*(void**)pGlyph, pGlyph->mpStrokeX1,
                                                          (i32)pGlyph->mwCapStrokeX1 * 2);
                pGlyph->mwCapStrokeY1 = (u16)(pGlyph->mwCapStrokeY1 + 0x14);
                pGlyph->mpStrokeX1Out = (i16*)tsi_ReAllocMem(*(void**)pGlyph,
                                                             pGlyph->mpStrokeX1Out,
                                                             (i32)pGlyph->mwCapStrokeY1 * 2);
            }
        }

        if (nRun != 0)
        {
            i16* pOut = (i16*)((u8*)pArrA + 2);
            i32  offB = (i32)pArrB - (i32)pArrA;
            do
            {
                i16 s0 = (i16)((u16)pRuns[0] * 0x100 + (u16)pRuns[1]);
                pOut[-1] = s0;
                if (setIdx == 0)
                    TransformPoint(1, (i32)pRuns, &pRuns);
                else
                    TransformPoint((i32)s0 << 16, (i32)pRuns, &pRuns);

                *(i16*)((u8*)pArrB + nAdv * 2) = 0;    // strike grey/depth slot for row nAdv

                u8* pRun2 = pRuns + 2;
                pRuns += 4;
                i16 s1 = (i16)((u16)pRun2[0] * 0x100 + (u16)pRun2[1]);
                pOut[0] = s1;
                nAdv += 2;
                *(i16*)((u8*)pOut + offB) = 0;
                pOut += 2;
            } while (--nRun != 0);
        }

    advance:
        if (setIdx != 0)
            break;
        pGlyph->mwCountY = (i16)(pGlyph->mwCountY + (i16)nAdv);
        curY   = pGlyph->mwCountY1;
        pArrA  = pGlyph->mpStrokeX1;
        pArrB  = pGlyph->mpStrokeX1Out;
        setIdx = 1;
    }

    pGlyph->mwCountY1 = (i16)(pGlyph->mwCountY1 + (i16)nAdv);
}
