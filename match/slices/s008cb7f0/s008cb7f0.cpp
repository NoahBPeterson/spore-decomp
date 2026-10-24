// Slice s008cb7f0: T2K (Type 2000 font scaler, "T2KS" compact glyph format) recursive glyph builder.
// Flags: /O2 /MD /Gy /TP  (no /EHsc: the original has no EH frame)
//
// Builds one glyph (0x008cb7f0, 1821 bytes). It opens the glyph's stream, reads four counts
// (components, "shifted" components, "scaled" components, contours). Components recurse
// (depth+1) into the same function and append their points; the first group is merged as-is,
// the second group is translated by a decoded (dx, dy), the third is scaled by two 8.8 fixed
// factors and translated. Then the glyph's own contour end-points and delta coded points are
// appended, the four phantom points are written after the last point (left side 0, advance
// width, top and bottom from the units-per-em), and, at depth 0, the points are scaled by 8,
// hinted / stroked, and the max point / contour counters are updated.
//
// The original uses TU-local register conventions for three static helpers; their real bodies
// are given below so that cl emits the same calls: GetGlyphStream (font in ESI),
// ReadLowUnsignedNumber (stream in ESI), AllocatePointSpaceIfNeeded (glyph in ECX, count in
// EAX). ApplyHintsToStrokeGlyph (0x008cae30) additionally takes its fifth argument in EAX; it is
// declared here as a plain cdecl function with that value as the fifth stack argument.
#include "types.h"

typedef uint8_t uint8;
typedef int8_t int8;
typedef int16_t int16;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef int32_t int32;

struct tsiMemObject {
    uint8 pad00[0x54];
    void* base54;           // +0x54
    void* stream58;         // +0x58 (stream that owns +0x90)
    uint8 pad5c[0x8c - 0x5c];
    int32 flag8c;           // +0x8c
    int32 flag90;           // +0x90
};

typedef int (*PF_READ_TO_RAM)(void* id, uint8* dest, int32 offset, int32 numBytes);

struct InputStream {
    uint8* privateBase;            // +0x000
    PF_READ_TO_RAM ReadToRamFunc;  // +0x004
    void* nonRamID;                // +0x008
    uint8 tmp_ch[0x204];           // +0x00c (byte cache lives at +0x00d)
    uint32 pendingCount;           // +0x210 (bytes left after the primed block)
    uint32 cacheCount;             // +0x214
    uint32 posZero;                // +0x218
    uint32 pos;                    // +0x21c
    uint32 streamEnd;              // +0x220
    uint32 baseOffset;             // +0x224
    uint8 kind;                    // +0x228
    uint8 pad229[3];               // +0x229
    tsiMemObject* mem;             // +0x22c
    uint32 field230;               // +0x230
    uint32 field234;               // +0x234
    uint8 field238;                // +0x238
    uint8 pad239[3];               // +0x239
};

struct GlyphClass {
    tsiMemObject* mem;      // +0x00
    int16 contourCount;     // +0x04
    int16 pad06;
    int32 pointCount32;     // +0x08
    int32 x0c;              // +0x0c
    int32 x10;              // +0x10
    int16 spBuffer[16];     // +0x14
    int16 x34;              // +0x34
    int16 contourCountMax;  // +0x36 (current number of contours)
    int16 pointCount;       // +0x38 (current number of points)
    int16 pad3a;
    int16* sp;              // +0x3c
    int16* ep;              // +0x40
    int16* oox;             // +0x44
    int16* ooy;             // +0x48
    uint8* onCurve;         // +0x4c
    void* x50;              // +0x50
    void* x54;              // +0x54
    int16* componentData;   // +0x58
    int32 componentSize;    // +0x5c
    int32 componentSizeMax; // +0x60
    uint8* hintFragment;    // +0x64
    int32 hintLength;       // +0x68
    int16 xmin;             // +0x6c
    int16 ymin;             // +0x6e
    int16 xmax;             // +0x70
    int16 ymax;             // +0x72
    int32 x74;              // +0x74
};

struct MaxLimits {                     // font->limits (+0x54)
    uint8 pad00[0x0a];
    uint16 maxPoints;                  // +0x0a
    uint16 maxContours;                // +0x0c
};

struct HeadLike {                      // font->head (+0x30)
    uint8 pad00[0x0a];
    int16 yMinLike;                    // +0x0a
    int16 yMaxLike;                    // +0x0c
};

struct T2KSFont {
    uint32 pad00;
    uint16 (*GetAdvance)(void* userData, int glyphIndex);   // +0x04
    void* userData;                    // +0x08
    uint8 pad0c[0x2c - 0x0c];
    void* sloc;                        // +0x2c
    HeadLike* head;                    // +0x30
    uint8 pad34[0x54 - 0x34];
    MaxLimits* limits;                 // +0x54
    uint8 pad58[0xc0 - 0x58];
    int32 xScale;                      // +0xc0
    int32 yScale;                      // +0xc4
    int useNativeHints;                // +0xc8
    int strokeGlyph;                   // +0xcc
    int greyScaleLevel;                // +0xd0
    int32 currentCoordinate;           // +0xd4
    uint32 padd8;
    InputStream* in;                   // +0xdc
    uint32 pade0[2];
    tsiMemObject* mem;                 // +0xe8
    uint32 padec;
    int32 numGlyphs;                   // +0xf0
};

extern "C" {
void tsi_Error(tsiMemObject* mem, int32 errCode);                                    // 0x008d10c0
void tsi_DeAllocMem(tsiMemObject* mem, void* p);                                     // 0x008d1440
__declspec(noinline) int32 PrimeT2KInputStream(InputStream* in);                     // 0x008cc0b0
uint32 Tell_InputStream(InputStream* in);                                            // 0x008cc5b0
void Seek_InputStream(InputStream* in, uint32 pos);                                  // 0x008cc580
InputStream* New_InputStream2(tsiMemObject* mem, InputStream* in, uint32 offset, uint32 length,
                              int32 unused, int* errCode);                           // 0x008cc330
void Delete_InputStream(InputStream* t, int* errCode);                               // 0x008cc5d0
int32 FF_SLOC_MapIndexToOffset(void* sloc, InputStream* in, int32 index);            // 0x008cdec0
uint8* GetTableDirEntry_sfntClass(T2KSFont* t, uint32 tag);                          // 0x008cebe0
uint16 GetUPEM(T2KSFont* t);                                                         // 0x008ceb70
void AllocGlyphPointMemory(GlyphClass* t, int32 pointCount);                         // 0x008b0230
GlyphClass* New_EmptyGlyph(tsiMemObject* mem, int a, int b, int c, int d);           // 0x008b0480
void glyph_AllocContours(GlyphClass* t, int32 contours);                             // 0x008afd50
uint32 ReadDeltaXYValue(InputStream* in, int16* a, int16* b);                            // 0x008af670
void ff_Read2Numbers(InputStream* in, uint16* out);                                  // 0x008cb1b0
void ff_Read4Numbers(InputStream* in, uint16* out);                                  // 0x008cb2e0
int32 util_FixMul(int32 a, int32 b);                                                 // 0x008d1590
int32 util_FixDiv(int32 a, int32 b);                                                 // 0x008d16d0
void ApplyHintsToStrokeGlyph(GlyphClass* g, int32 xScale, int32 yScale, int flag, int32 eaxArg);  // 0x008cae30 (5th arg in EAX)
GlyphClass* ff_glyph_StrokeGlyph(GlyphClass* g, int32 a, int b, int c, int d);       // 0x008cb070
}

#define T2K_ERR_TRANS_FAIL 10024

static __inline int ReadUnsignedByteSlow(InputStream* in)
{
    int error = in->ReadToRamFunc(in->nonRamID, in->tmp_ch, in->pos++, 1);
    if (error < 0) {
        tsi_Error(in->mem, T2K_ERR_TRANS_FAIL);
        return 0;
    }
    return in->tmp_ch[0];
}

#define ReadUnsignedByteMacro2(stream) \
    ((int)(((stream)->pos - (stream)->posZero + 1 > (stream)->cacheCount ? PrimeT2KInputStream(stream) : (void)0), \
             (stream)->privateBase[(stream)->pos++ - (stream)->posZero]))

#define ReadUnsignedByteMacro(stream) \
    ((uint8)((stream)->privateBase != 0 \
                 ? ((stream)->ReadToRamFunc != 0 ? ReadUnsignedByteMacro2(stream) \
                                                 : (stream)->privateBase[(stream)->pos++]) \
                 : ReadUnsignedByteSlow(stream)))

// 0x008cb450: variable length number, 4 bits per 0xf0.. prefix byte.
static uint32 ReadLowUnsignedNumber(InputStream* in)
{
    uint32 acc = 0;
    int shift = 0;
    for (;;) {
        uint8 b = ReadUnsignedByteMacro(in);
        if (b < 0xf0)
            return ((uint32)b << shift) | acc;
        acc |= (uint32)(b - 0xf0) << shift;
        shift += 4;
    }
}

// 0x008cb520: grow the point arrays so that `count` points fit, copying the existing points.
__declspec(noinline) static void AllocatePointSpaceIfNeeded(GlyphClass* g, int32 count)
{
    if (count > g->pointCount32) {
        int16* oldOox = g->oox;
        int16* oldOoy = g->ooy;
        uint8* oldOn = g->onCurve;
        void* oldBase = g->x50;
        AllocGlyphPointMemory(g, count + 0x20);
        int n = g->pointCount + 4;
        int16* newOox = g->oox;
        int16* newOoy = g->ooy;
        uint8* newOn = g->onCurve;
        for (int i = 0; i < n; i++) {
            newOox[i] = oldOox[i];
            newOoy[i] = oldOoy[i];
            newOn[i] = oldOn[i];
        }
        tsiMemObject* mem = g->mem;
        if (oldBase == mem->base54)
            mem->flag8c = 1;
        else
            tsi_DeAllocMem(mem, oldBase);
    }
}

// 0x008cb5e0: opens a sub-stream on the glyph's data, *len receives its length.
static InputStream* GetGlyphStream(T2KSFont* font, int glyphIndex, int* len)
{
    InputStream* stream = 0;
    int length = 0;
    uint8* dir = GetTableDirEntry_sfntClass(font, 0x676c7966);   // 'glyf'
    void* sloc = font->sloc;
    if (dir != 0 && sloc != 0 && glyphIndex >= 0 && glyphIndex < font->numGlyphs) {
        uint32 savedPos = Tell_InputStream(font->in);
        int32 start = FF_SLOC_MapIndexToOffset(sloc, font->in, glyphIndex);
        int32 end = FF_SLOC_MapIndexToOffset(sloc, font->in, glyphIndex + 1);
        length = end - start;
        Seek_InputStream(font->in, savedPos);
        stream = New_InputStream2(font->mem, font->in, *(uint32*)(dir + 8) + start, length, 2, 0);
    }
    *len = length;
    return stream;
}

// @ 0x008cb7f0
GlyphClass* BuildGlyphT2KS(T2KSFont* font, GlyphClass* g, int glyphIndex, uint16* advanceOut, int16* upemOut,
                           int arg6, int depth)
{
    tsiMemObject* mem = font->mem;
    int16* ooy = 0;
    int16* oox = 0;
    int np = 0;
    int streamLen;
    InputStream* in = GetGlyphStream(font, glyphIndex, &streamLen);

    if (streamLen == 0) {
        if (g == 0) {
            g = New_EmptyGlyph(mem, 0, 0, 0, 0);
            ooy = g->ooy;
            oox = g->oox;
        }
    } else {
        uint16 nums[4];
        ff_Read4Numbers(in, nums);
        uint32 countC = nums[2];
        uint32 countB = nums[1];
        uint32 countA = nums[0];
        if (depth > 0 && (nums[0] != 0 || nums[1] != 0 || nums[2] != 0)) {
            countC = 0;
            countB = 0;
            countA = 0;
        }

        // group A: plain components
        if (countA != 0) {
            int nextDepth = depth + 1;
            do {
                uint16 aw;
                int16 upem;
                uint32 id = ReadLowUnsignedNumber(in);
                g = BuildGlyphT2KS(font, g, id, &aw, &upem, arg6, nextDepth);
                countA--;
            } while (countA != 0);
        }

        // group B: translated components
        if ((countB & 0xffff) != 0) {
            int nextDepth = depth + 1;
            countB &= 0xffff;
            do {
                int16 dy;
                int16 dx;
                int r = ReadDeltaXYValue(in, &dx, &dy);
                dx = (int16)(r + dx * 2);
                int base = (g == 0) ? 0 : (int)g->pointCount;
                uint16 aw;
                int16 upem;
                uint32 id = ReadLowUnsignedNumber(in);
                g = BuildGlyphT2KS(font, g, id, &aw, &upem, arg6, nextDepth);
                int16* ox = g->oox;
                int16* oy = g->ooy;
                if (base < g->pointCount) {
                    int16* py = oy + base;
                    int16* px = ox + base;
                    int n = g->pointCount - base;
                    do {
                        *px = (int16)(*px + (int16)dx);
                        *py = (int16)(*py + (int16)dy);
                        px++;
                        py++;
                        n--;
                    } while (n != 0);
                }
                countB--;
            } while (countB != 0);
        }

        // group C: scaled and translated components
        if ((countC & 0xffff) != 0) {
            int nextDepth = depth + 1;
            countC &= 0xffff;
            do {
                int16 sx;
                int16 tx;
                int r1 = ReadDeltaXYValue(in, &tx, &sx);
                tx = (int16)(r1 + tx * 2);
                int16 sy;
                int16 ty;
                int r2 = ReadDeltaXYValue(in, &ty, &sy);
                ty = (int16)(r2 + ty * 2);
                int32 fx = util_FixDiv((int16)ty + 0x100, 0x100);
                int32 fy = util_FixDiv((int16)sy + 0x100, 0x100);
                int base = (g == 0) ? 0 : (int)g->pointCount;
                uint16 aw;
                int16 upem;
                uint32 id = ReadLowUnsignedNumber(in);
                g = BuildGlyphT2KS(font, g, id, &aw, &upem, arg6, nextDepth);
                if (base < g->pointCount) {
                    int16* px = g->oox + base;
                    int16* py = g->ooy + base;
                    int n = g->pointCount - base;
                    int mulX = (int16)((fx + 8) >> 4);
                    int mulY = (int16)((fy + 8) >> 4);
                    do {
                        *px = (int16)((*px * mulX + 0x800) >> 12) + (int16)tx;
                        *py = (int16)((*py * mulY + 0x800) >> 12) + (int16)sx;
                        px++;
                        py++;
                        n--;
                    } while (n != 0);
                }
                countC--;
            } while (countC != 0);
        }

        // the glyph's own contours
        if (g == 0)
            g = New_EmptyGlyph(mem, 0, 0, 0, 0);
        oox = g->oox;
        ooy = g->ooy;
        glyph_AllocContours(g, (uint16)(g->contourCountMax + nums[3]));
        int contours = nums[3];
        int16 pos = g->pointCount;
        int k = 0;
        if (contours != 0) {
            do {
                uint16 pair[2];
                ff_Read2Numbers(in, pair);
                g->sp[g->contourCountMax] = pos;
                g->ep[g->contourCountMax] = pair[0] + pos;
                pos = g->ep[g->contourCountMax] + 1;
                g->contourCountMax++;
                if (contours <= k + 1)
                    break;
                g->sp[g->contourCountMax] = pos;
                g->ep[g->contourCountMax] = pair[1] + pos;
                pos = g->ep[g->contourCountMax] + 1;
                k += 2;
                g->contourCountMax++;
            } while (k < contours);
        }

        // the glyph's own points
        np = g->pointCount;
        int remaining = pos - np;
        if (remaining > 0) {
            AllocatePointSpaceIfNeeded(g, remaining + np);
            uint8* onCurve = g->onCurve;
            oox = g->oox;
            ooy = g->ooy;
            uint32 xAcc = 0, yAcc = 0;
            g->hintLength = 0;
            uint32 minX = 0x7fff;
            uint32 maxY = 0xffff8001;
            int16* oyp = ooy + np;
            int oxDelta = (int)oox - (int)ooy;
            do {
                int16 a, b;
                uint8 flag = (uint8)ReadDeltaXYValue(in, &a, &b);
                xAcc += b;
                yAcc += a;
                onCurve[np] = flag;
                if ((int16)xAcc < (int16)minX)
                    minX = xAcc & 0xffff;
                if ((int16)maxY < (int16)yAcc)
                    maxY = yAcc & 0xffff;
                *(int16*)((int)oyp + oxDelta) = (int16)xAcc;
                np++;
                *oyp = (int16)yAcc;
                oyp++;
                remaining--;
            } while (remaining != 0);
            g->xmin = (int16)minX;
            g->ymax = (int16)maxY;
        }
    }

    if (depth == 0) {
        g->xmin = g->xmin << 3;
        g->ymax = g->ymax << 3;
    }

    int upem = GetUPEM(font) & 0xffff;
    uint16 aw = font->GetAdvance(font->userData, glyphIndex);
    int16 ymaxSaved = g->ymax;
    int16 xminSaved = g->xmin;
    ooy[np] = 0;
    oox[np] = g->xmin - xminSaved;
    ooy[np + 1] = 0;
    int16 left = oox[np];
    int16 right = (int16)(aw + left);
    oox[np + 1] = right;
    ooy[np + 2] = g->ymax + ((int16)upem - ymaxSaved);
    int16 mid = (int16)((right + left) >> 1);
    oox[np + 2] = mid;
    ooy[np + 3] = ooy[np + 2] - (int16)upem;
    oox[np + 3] = mid;
    *advanceOut = aw;
    *upemOut = (int16)upem;

    if (depth == 0 && np >= 0) {
        int16* py = ooy;
        int16* px = oox;
        int n = np + 1;
        do {
            *px = *px << 3;
            *py = *py << 3;
            py++;
            px++;
            n--;
        } while (n != 0);
    }

    g->pointCount = (int16)np;
    Delete_InputStream(in, 0);

    if (depth == 0) {
        int32 v = util_FixMul(font->currentCoordinate, (int)font->head->yMaxLike - (int)font->head->yMinLike);
        v = v + font->head->yMinLike;
        if (font->greyScaleLevel == 0 && font->yScale > 0) {
            v = util_FixMul(v * 2, font->yScale);
            uint32 target = (v + 0x20) & 0xffffffc0;
            if ((int)target < 0x40)
                target = 0x40;
            v = util_FixDiv((int)target / 2, font->yScale);
            int32 got = util_FixMul(v * 2, font->yScale);
            while (got < (int)target) {
                v++;
                got = util_FixMul(v * 2, font->yScale);
            }
        }
        int16* yy = g->ooy;
        if (g->contourCountMax > 0) {
            int last = g->ep[g->contourCountMax - 1];
            int i = 0;
            if (last >= 0) {
                do {
                    yy[i] = yy[i] + (int16)v;
                    i++;
                } while (i <= last);
            }
        }
        if (font->useNativeHints != 0)
            ApplyHintsToStrokeGlyph(g, font->xScale, font->yScale, font->greyScaleLevel == 0, v);
        if (font->strokeGlyph != 0)
            g = ff_glyph_StrokeGlyph(g, v, 0, 1, 1);
        if ((int)font->limits->maxPoints < (int)g->pointCount)
            font->limits->maxPoints = g->pointCount;
        if ((int)font->limits->maxContours < (int)g->contourCountMax)
            font->limits->maxContours = g->contourCountMax;
    }
    return g;
}

// ---------------------------------------------------------------------------
// T2K input stream set (0x008cbf10 .. 0x008cc670).
//
// InputStream is a 0x23c byte big-endian byte stream: either read straight out of a memory
// block (kind 4), or through the owner's ReadToRamFunc callback, which is primed with up to
// 0x200 bytes at a time into tmp_ch (kind 1 = whole stream pulled into memory, 2 = window on a
// parent stream, 4 = callback driven).
// ---------------------------------------------------------------------------

struct T2KMemHeader {                   // 0x14 bytes
    tsiMemObject* mem;                  // +0x00
    int16 flags04;                      // +0x04
    int16 flags06;                      // +0x06
    int16 value08;                      // +0x08
    int16 value0a;                      // +0x0a
    int16 value0c;                      // +0x0c
    int16 value0e;                      // +0x0e
    int16 value10;                      // +0x10
    int16 pad12;                        // +0x12
};

extern "C" {
void* tsi_AllocMem(tsiMemObject* mem, int32 size);                                    // 0x008d1260
void* tsi_FastAllocN(tsiMemObject* mem, int32 size, int32 align);                     // 0x008d14d0
void tsi_EmergencyShutDown(tsiMemObject* mem);                                        // 0x008d1210
int setjmp3(void* buf, int unused);                                                   // 0x011e0cac
void* memcpy(void* dst, const void* src, unsigned int count);                         // 0x011e0744
void PreLoadT2KInputStream(InputStream* in, int32 length);                            // 0x008cc040
uint32 ReadInt32(InputStream* in);                                                    // 0x008cc0f0
uint16 ReadInt16(InputStream* in);                                                    // 0x008cc190
void PeekInt16(InputStream* in, void* dest, int32 count);                             // 0x008cc220
int32 GetStreamLength(InputStream* in);                                               // 0x008cc2a0
int32 GetEntireStreamIntoMemory(InputStream* in);                                     // 0x008cc2c0
InputStream* New_InputStream4(tsiMemObject* mem, void* base, uint32 end, int* errCode);  // 0x008cc410
InputStream* New_NonRamInputStream(tsiMemObject* mem, PF_READ_TO_RAM readToRam, void* id,
                                   uint32 end, int* errCode);                         // 0x008cc4b0
void Rewind_InputStream(InputStream* in);                                             // 0x008cc550
T2KMemHeader* New_T2KMemHeader(tsiMemObject* mem, InputStream* in, int32 count);      // 0x008cbf10
void Delete_T2KMemHeader(T2KMemHeader* h);                                            // 0x008cc020
uint32 ReadUnsignedNumber(InputStream* in);                                           // 0x008cc670
}

// @ 0x008cbf10  New_T2KMemHeader
T2KMemHeader* New_T2KMemHeader(tsiMemObject* mem, InputStream* in, int32 count)
{
    T2KMemHeader* h = (T2KMemHeader*)tsi_AllocMem(mem, 0x14);
    h->flags04 = 0;
    h->flags06 = 0;
    h->value08 = 1;
    h->value0a = 2;
    h->mem = mem;
    h->value0c = 10;
    h->value0e = 0;
    h->value10 = 0;
    if (in != 0) {
        h->flags04 = (int16)ReadInt16(in);
        h->flags06 = (int16)ReadInt16(in);
        if (h->flags04 == 1 && count > 4) {
            int32 n = (int32)(((uint32)(count - 5) >> 2) + 1);
            do {
                int16 tag = (int16)ReadInt16(in);
                int16 value = (int16)ReadInt16(in);
                switch (tag) {
                case 0:
                    h->value08 = value;
                    break;
                case 1:
                    h->value0a = value;
                    break;
                case 2:
                    h->value0c = value;
                    break;
                case 3:
                    h->value0e = value;
                    break;
                case 4:
                    h->value10 = value;
                    break;
                }
                n--;
            } while (n != 0);
        }
    }
    h->value0a = (int16)(h->value0a * 8);
    h->value0c = (int16)(h->value0c * 8);
    return h;
}

// @ 0x008cc020  Delete_T2KMemHeader
void Delete_T2KMemHeader(T2KMemHeader* h)
{
    if (h != 0)
        tsi_DeAllocMem(h->mem, h);
}

// @ 0x008cc040  PreLoadT2KInputStream
void PreLoadT2KInputStream(InputStream* in, int32 length)
{
    PF_READ_TO_RAM func = in->ReadToRamFunc;
    if (func != 0) {
        uint32 pos = in->pos;
        int32 got = 0x200;
        if (length < got)
            got = length;
        in->pendingCount = (uint32)(length - got);
        in->privateBase = in->tmp_ch + 1;
        int r = func(in->nonRamID, in->privateBase, (int32)pos, got);
        if (r < 0)
            tsi_Error(in->mem, T2K_ERR_TRANS_FAIL);
        in->cacheCount = (uint32)got;
        in->posZero = in->pos;
    }
}

// @ 0x008cc0b0  PrimeT2KInputStream
int32 PrimeT2KInputStream(InputStream* in)
{
    int32 remaining = (int32)(in->streamEnd - in->pos);
    int32 n = remaining;
    if (n > 8)
        n = 8;
    if ((int32)in->pendingCount > n)
        n = (int32)in->pendingCount;
    if (n > remaining)
        n = remaining;
    PreLoadT2KInputStream(in, n);
    return 0;
}

// @ 0x008cc0f0  ReadInt32
uint32 ReadInt32(InputStream* in)
{
    uint32 pos = in->pos;
    uint8* p = in->privateBase;
    if (p != 0) {
        uint32 off = pos;
        if (in->ReadToRamFunc != 0) {
            if (pos - in->posZero + 4 > in->cacheCount)
                PrimeT2KInputStream(in);
            off = pos - in->posZero;
        }
        p += off;
    } else {
        uint32 buf;
        p = (uint8*)&buf;
        int r = in->ReadToRamFunc(in->nonRamID, p, (int32)pos, 4);
        if (r < 0)
            tsi_Error(in->mem, T2K_ERR_TRANS_FAIL);
    }
    in->pos = pos + 4;
    uint32 v = p[0];
    v = (v << 8) | p[1];
    v = (v << 8) | p[2];
    v = (v << 8) | p[3];
    return v;
}

// @ 0x008cc190  ReadInt16
uint16 ReadInt16(InputStream* in)
{
    uint32 pos = in->pos;
    uint8* p = in->privateBase;
    if (p != 0) {
        uint32 off = pos;
        if (in->ReadToRamFunc != 0) {
            if (pos - in->posZero + 2 > in->cacheCount)
                PrimeT2KInputStream(in);
            off = pos - in->posZero;
        }
        p += off;
    } else {
        uint16 buf;
        p = (uint8*)&buf;
        int r = in->ReadToRamFunc(in->nonRamID, p, (int32)pos, 2);
        if (r < 0)
            tsi_Error(in->mem, T2K_ERR_TRANS_FAIL);
    }
    in->pos = pos + 2;
    uint16 v = p[0];
    v <<= 8;
    v |= p[1];
    return v;
}

// @ 0x008cc220  PeekInt16
void PeekInt16(InputStream* in, void* dest, int32 count)
{
    if (count <= 0)
        return;
    uint32 pos = in->pos;
    if (in->ReadToRamFunc != 0) {
        int r = in->ReadToRamFunc(in->nonRamID, (uint8*)dest, (int32)pos, count);
        if (r < 0)
            tsi_Error(in->mem, T2K_ERR_TRANS_FAIL);
    } else {
        memcpy(dest, in->privateBase + pos, (uint32)count);
    }
    pos += (uint32)count;
    if (pos > in->streamEnd)
        tsi_Error(in->mem, 0x2729);
    in->pos = pos;
}

// @ 0x008cc2a0  GetStreamLength
int32 GetStreamLength(InputStream* in)
{
    return (int32)(in->streamEnd - in->baseOffset);
}

// @ 0x008cc2c0  GetEntireStreamIntoMemory
int32 GetEntireStreamIntoMemory(InputStream* in)
{
    if (in->privateBase == 0 && in->ReadToRamFunc != 0) {
        in->kind = 1;
        uint8* base = (uint8*)tsi_AllocMem(in->mem, (int32)in->streamEnd);
        in->privateBase = base;
        int r = in->ReadToRamFunc(in->nonRamID, base, 0, (int32)in->streamEnd);
        if (r < 0)
            tsi_Error(in->mem, T2K_ERR_TRANS_FAIL);
    }
    return (int32)(in->baseOffset + (uint32)in->privateBase);
}

// The original keeps a frame pointer in these four: the body wraps the CRT setjmp3.
#pragma optimize("y", off)
// @ 0x008cc330  New_InputStream2
InputStream* New_InputStream2(tsiMemObject* mem, InputStream* src, uint32 offset, uint32 length,
                              int32 unused, int* errCode)
{
    if (errCode != 0) {
        int r = setjmp3((uint8*)mem + 0x10, 0);
        *errCode = r;
        if (r != 0) {
            tsi_EmergencyShutDown(mem);
            return 0;
        }
    }
    InputStream* in = unused != 0 ? (InputStream*)tsi_FastAllocN(mem, 0x23c, 2)
                                  : (InputStream*)tsi_AllocMem(mem, 0x23c);
    in->mem = mem;
    in->privateBase = src->privateBase;
    in->ReadToRamFunc = src->ReadToRamFunc;
    in->nonRamID = src->nonRamID;
    in->cacheCount = 0;
    in->posZero = 0;
    uint32 base = src->baseOffset + offset;
    in->baseOffset = base;
    in->pos = base;
    in->streamEnd = base + length;
    in->field230 = 0;
    in->field234 = 0;
    in->kind = 2;
    in->field238 = 0;
    PreLoadT2KInputStream(in, (int32)length);
    return in;
}

// @ 0x008cc410  New_InputStream4
InputStream* New_InputStream4(tsiMemObject* mem, void* base, uint32 end, int* errCode)
{
    if (errCode != 0) {
        int r = setjmp3((uint8*)mem + 0x10, 0);
        *errCode = r;
        if (r != 0) {
            tsi_EmergencyShutDown(mem);
            return 0;
        }
    }
    InputStream* in = (InputStream*)tsi_AllocMem(mem, 0x23c);
    in->mem = mem;
    in->ReadToRamFunc = 0;
    in->nonRamID = 0;
    in->cacheCount = 0;
    in->posZero = 0;
    in->pos = 0;
    in->baseOffset = 0;
    in->field230 = 0;
    in->field234 = 0;
    in->field238 = 0;
    in->privateBase = (uint8*)base;
    in->streamEnd = end;
    in->kind = 4;
    return in;
}

// @ 0x008cc4b0  New_NonRamInputStream
InputStream* New_NonRamInputStream(tsiMemObject* mem, PF_READ_TO_RAM readToRam, void* id,
                                   uint32 end, int* errCode)
{
    if (errCode != 0) {
        int r = setjmp3((uint8*)mem + 0x10, 0);
        *errCode = r;
        if (r != 0) {
            tsi_EmergencyShutDown(mem);
            return 0;
        }
    }
    InputStream* in = (InputStream*)tsi_AllocMem(mem, 0x23c);
    in->mem = mem;
    in->ReadToRamFunc = readToRam;
    in->privateBase = 0;
    in->cacheCount = 0;
    in->posZero = 0;
    in->pos = 0;
    in->baseOffset = 0;
    in->field230 = 0;
    in->field234 = 0;
    in->field238 = 0;
    in->nonRamID = id;
    in->streamEnd = end;
    in->kind = 4;
    return in;
}
#pragma optimize("y", on)

// @ 0x008cc550  Rewind_InputStream
void Rewind_InputStream(InputStream* in)
{
    in->pos = in->baseOffset;
    if (in->baseOffset < in->posZero) {
        in->cacheCount = 0;
        in->posZero = 0;
    }
}

// @ 0x008cc580  Seek_InputStream
void Seek_InputStream(InputStream* in, uint32 offset)
{
    uint32 p = offset;
    p += in->baseOffset;
    in->pos = p;
    if (p < in->posZero) {
        in->cacheCount = 0;
        in->posZero = 0;
    }
}

// @ 0x008cc5b0  Tell_InputStream
uint32 Tell_InputStream(InputStream* in)
{
    return in->pos - in->baseOffset;
}

#pragma optimize("y", off)
// @ 0x008cc5d0  Delete_InputStream
void Delete_InputStream(InputStream* in, int* errCode)
{
    if (in == 0)
        return;
    if (errCode != 0) {
        int r = setjmp3((uint8*)in->mem + 0x10, 0);
        *errCode = r;
        if (r != 0) {
            tsi_EmergencyShutDown(in->mem);
            return;
        }
    }
    if (in->kind == 1) {
        tsi_DeAllocMem(in->mem, in->privateBase);
        tsi_DeAllocMem(in->mem, in);
        return;
    }
    tsiMemObject* mem = in->mem;
    if (in == (InputStream*)mem->stream58) {
        mem->flag90 = 1;
        return;
    }
    tsi_DeAllocMem(mem, in);
}
#pragma optimize("y", on)

// Inline copy of PrimeT2KInputStream's body: cl inlined it at the read site in the original.
static __inline void PrimeStreamInline(InputStream* in)
{
    int32 remaining = (int32)(in->streamEnd - in->pos);
    int32 n = remaining;
    if (n > 8)
        n = 8;
    if ((int32)in->pendingCount > n)
        n = (int32)in->pendingCount;
    if (n > remaining)
        n = remaining;
    PreLoadT2KInputStream(in, n);
}

// @ 0x008cc670  ReadUnsignedNumber
uint32 ReadUnsignedNumber(InputStream* in)
{
    uint32 acc = 0;
    int32 shift = 0;
    for (;;) {
        uint8 b;
        if (in->privateBase == 0) {
            uint32 pos = in->pos;
            in->pos = pos + 1;
            int r = in->ReadToRamFunc(in->nonRamID, in->tmp_ch, (int32)pos, 1);
            if (r < 0) {
                tsi_Error(in->mem, T2K_ERR_TRANS_FAIL);
                b = 0;
            } else {
                b = in->tmp_ch[0];
            }
        } else if (in->ReadToRamFunc == 0) {
            b = in->privateBase[in->pos++];
        } else {
            if (in->pos - in->posZero + 1 > in->cacheCount)
                PrimeStreamInline(in);
            b = in->privateBase[in->pos - in->posZero];
            in->pos++;
        }
        acc |= (uint32)(b & 0x7f) << shift;
        shift += 7;
        if ((int8)b >= 0)
            return acc;
    }
}
