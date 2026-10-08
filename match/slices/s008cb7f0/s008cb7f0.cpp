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
typedef int16_t int16;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef int32_t int32;

struct tsiMemObject {
    uint8 pad00[0x54];
    void* base54;           // +0x54
    uint8 pad58[0x8c - 0x58];
    int32 flag8c;           // +0x8c
};

typedef int (*PF_READ_TO_RAM)(void* id, uint8* dest, int32 offset, int32 numBytes);

struct InputStream {
    uint8* privateBase;            // +0x000
    PF_READ_TO_RAM ReadToRamFunc;  // +0x004
    void* nonRamID;                // +0x008
    uint8 tmp_ch[0x208];           // +0x00c
    uint32 cacheCount;             // +0x214
    uint32 posZero;                // +0x218
    uint32 pos;                    // +0x21c
    uint32 pad220[3];              // +0x220
    tsiMemObject* mem;             // +0x22c
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
void PrimeT2KInputStream(InputStream* in);                                           // 0x008cc0b0
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
