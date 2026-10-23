/* Slice s008caba0 -- T2K / Font Fusion (module "EA-UTF"): glyph stroking + hint application.
 *
 * COMPILE AS C: "/O2 /MD /Gy /TC /GS-"   (T2K is C, like s008bb550 / s008bdb70 / s008be260).
 * The retail binary was built with LTCG, so several of these routines take arguments in
 * caller-saved registers rather than on the stack; they are written here with those values as
 * ordinary leading/extra parameters and cannot be byte-exact from a single /O2 TU (see
 * nonmatching.txt).
 *
 * 008caba0 glyph_StrokeCtr            stroke one contour of a glyph (source glyph arrives in EDI)
 * 008cae30 ApplyHintsToStrokeGlyph    snap the x then y coordinates to the pixel grid (5th arg in EAX)
 * 008cb070 ff_glyph_StrokeGlyph       stroke a whole glyph into a freshly allocated GlyphClass
 * 008cb1b0 ff_Read2Numbers            bit-packed 2-number stream decoder
 * 008cb2e0 ff_Read4Numbers            bit-packed 4-number stream decoder
 * 008cb450 ReadLowUnsignedNumber      0xf0-prefixed 4-bits-per-byte variable-length number
 * 008cb520 AllocatePointSpaceIfNeeded grow the point arrays and copy the old points (glyph in ECX, count in EAX)
 * 008cb5e0 GetGlyphStream             open a sub-stream over one glyph's data (font in ESI)
 * 008cb6b0 Read_PreferredMappingTable decode the "preferred mapping" cmap sub-table
 * 008cb790 MapCodeToGlyph             binary search of a decoded mapping table
 */

typedef unsigned char uint8;
typedef signed char int8;
typedef unsigned short uint16;
typedef short int16;
typedef unsigned int uint32;
typedef int int32;

typedef struct tsiMemObject {
    uint8 pad00[0x54];
    void* base54;           // +0x54
    uint8 pad58[0x8c - 0x58];
    int32 flag8c;           // +0x8c
} tsiMemObject;

typedef int (*PF_READ_TO_RAM)(void* id, uint8* dest, int32 offset, int32 numBytes);

typedef struct InputStream {
    uint8* privateBase;            // +0x000
    PF_READ_TO_RAM ReadToRamFunc;  // +0x004
    void* nonRamID;                // +0x008
    uint8 tmp_ch[0x208];           // +0x00c
    uint32 cacheCount;             // +0x214
    uint32 posZero;                // +0x218
    uint32 pos;                    // +0x21c
    uint32 pad220[3];              // +0x220
    tsiMemObject* mem;             // +0x22c
} InputStream;

typedef struct GlyphClass {
    tsiMemObject* mem;      // +0x00
    int16 contourCount;     // +0x04
    int16 pad06;
    int32 pointCount32;     // +0x08
    int32 x0c;              // +0x0c
    int32 x10;              // +0x10
    int16 spBuffer[16];     // +0x14
    int16 x34;              // +0x34
    int16 contourCountMax;  // +0x36
    int16 pointCount;       // +0x38
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
} GlyphClass;

typedef struct T2KSFont {
    uint8 pad00[0x2c];
    void* sloc;                        // +0x2c
    uint8 pad30[0xdc - 0x30];
    InputStream* in;                   // +0xdc
    uint8 pade0[0xe8 - 0xe0];
    tsiMemObject* mem;                 // +0xe8
    uint8 padec[0xf0 - 0xec];
    int32 numGlyphs;                   // +0xf0
} T2KSFont;

// Decoded "preferred mapping" table (see Read_PreferredMappingTable below).
typedef struct MappingTable {
    tsiMemObject* mem;   // +0x00
    uint32 version;      // +0x04
    int32 count;         // +0x08
    uint16 field0c;      // +0x0c
    uint16 field0e;      // +0x0e
    uint16* keys;        // +0x10
    uint16* values;      // +0x14
} MappingTable;

// Stroker working state (see slice s008c9e00, lineJoin).
typedef struct StrokeState {
    tsiMemObject* mem;   // +0x00
    int nA;              // +0x04
    int capA;            // +0x08
    int16* ptsA;         // +0x0c
    int nB;              // +0x10
    int capB;            // +0x14
    int16* ptsB;         // +0x18
    int offX;            // +0x1c
    int offY;            // +0x20
    int lastIndex;       // +0x24
} StrokeState;

extern void* tsi_AllocMem(tsiMemObject* mem, int32 size);                     // 0x008d1260
extern void tsi_DeAllocMem(tsiMemObject* mem, void* p);                       // 0x008d1440
extern void tsi_Error(tsiMemObject* mem, int32 errCode);                      // 0x008d10c0
extern void PrimeT2KInputStream(InputStream* in);                            // 0x008cc0b0
extern int32 ReadInt32(InputStream* in);                                     // 0x008cc0f0
extern int16 ReadInt16(InputStream* in);                                     // 0x008cc190
extern InputStream* New_InputStream2(tsiMemObject* mem, InputStream* in, uint32 offset,
                                     uint32 length, int32 unused, int* errCode); // 0x008cc330
extern void Seek_InputStream(InputStream* in, uint32 pos);                   // 0x008cc580
extern uint32 Tell_InputStream(InputStream* in);                             // 0x008cc5b0
extern int32 FF_SLOC_MapIndexToOffset(void* sloc, InputStream* in, int32 index); // 0x008cdec0
extern uint8* GetTableDirEntry_sfntClass(T2KSFont* font, uint32 tag);        // 0x008cebe0
extern int32 util_FixMul(int32 a, int32 b);                                  // 0x008d1590
extern int32 util_FixDiv(int32 a, int32 b);                                  // 0x008d16d0
extern void AllocGlyphPointMemory(GlyphClass* g, int32 pointCount);          // 0x008b0230
extern GlyphClass* New_EmptyGlyph(tsiMemObject* mem, int a, int b, int c, int d); // 0x008b0480
extern void Delete_GlyphClass(GlyphClass* g);                                // 0x008b0280
// 0x008c9e00: join the offset lines of two segments (st, joinType, x0, y0, x1, y1, outer, index, x2, y2, w).
extern void lineJoin(StrokeState* st, int joinType, int x0, int y0, int x1, int y1,
                     int outer, int index, int x2, int y2, int w);
// 0x008ca5b0: round-ish join; 0x008ca980: flush the stroker's points into the destination glyph.
extern void FUN_008ca5b0(StrokeState* st, int c, int x, int y, int w);
extern void FUN_008ca980(StrokeState* st, GlyphClass* dst, int closed);

#define T2K_ERR_TRANS_FAIL 10024

static __inline uint8 ReadUnsignedByteSlow(InputStream* in)
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

// @ 0x008caba0
// Stroke one contour of the source glyph into a fresh StrokerState; `g` is the source glyph
// (in EDI in the retail build).  `dst` is the glyph the flushed points go to.
void FUN_008caba0(int contourIndex, GlyphClass* dst, int a, int b, int c, int d, GlyphClass* g)
{
    tsiMemObject* mem = g->mem;
    int flag = d;
    int closed = 0;
    StrokeState* st;
    int start, end, count, x0, y0, x1, y1, i;
    st = (StrokeState*)tsi_AllocMem(mem, 0x28);
    st->mem = mem;
    st->nA = 0;
    st->capA = 0x100;
    st->nB = 0;
    st->capB = 0x100;
    st->ptsA = (int16*)tsi_AllocMem(mem, 0x200);
    st->ptsB = (int16*)tsi_AllocMem(mem, st->capB * 2);
    st->lastIndex = -1;
    start = g->sp[contourIndex];
    end = g->ep[contourIndex];
    count = end - start + 1;
    if (count > 1) {
        x0 = g->oox[start];
        y0 = g->ooy[start];
        if (flag != 0) {
            int last = start + count - 1;
            if (x0 == g->oox[last] && y0 == g->ooy[last]) {
                flag = 0;
                closed = 1;
            }
        }
        x1 = g->oox[start + 1];
        y1 = g->ooy[start + 1];
        i = start + 2;
        if (flag == 0) {
            end -= closed;
            lineJoin(st, b, g->oox[end], g->ooy[end], x0, y0, g->onCurve[start], start, x1, y1, a);
        } else {
            FUN_008ca5b0(st, c, x0, y0, a);
        }
        while (i <= g->ep[contourIndex]) {
            int prevX = x1;
            int px = g->oox[i];
            int py = g->ooy[i];
            lineJoin(st, b, x0, y0, prevX, y1, g->onCurve[i - 1], i - 1, px, py, a);
            y0 = y1;
            i++;
            x0 = prevX;
            y1 = py;
            x1 = px;
        }
        if (flag == 0) {
            int e = g->ep[contourIndex];
            int first = g->sp[contourIndex] + closed;
            lineJoin(st, b, x0, y0, x1, y1, g->onCurve[e], e, g->oox[first], g->ooy[first], a);
        } else {
            FUN_008ca5b0(st, c, x1, y1, a);
        }
        FUN_008ca980(st, dst, flag);
    }
    tsi_DeAllocMem(mem, st->ptsA);
    tsi_DeAllocMem(mem, st->ptsB);
    tsi_DeAllocMem(mem, st);
}

// @ 0x008cae30
// Snap the glyph's y coordinates, then its x coordinates, to the pixel grid.  `v` is the
// fifth argument, passed in EAX by the retail caller (declared here as a normal parameter).
void ApplyHintsToStrokeGlyph(GlyphClass* g, int32 xScale, int32 yScale, int flag, int32 v)
{
    uint8 used[128];
    int pass;
    for (pass = 0; pass < 2; pass++) {
        int32 scale;
        int32 m;
        int16 s;
        int16* coords;
        uint32 t;
        uint32 phase;
        int contour;
        if (pass == 0) {
            scale = yScale;
            m = util_FixMul(v * 2, yScale);
            s = (int16)util_FixDiv(0x40, yScale);
            coords = g->ooy;
        } else {
            scale = xScale;
            m = util_FixMul(v * 2, xScale);
            s = (int16)util_FixDiv(0x40, xScale);
            coords = g->oox;
        }
        t = (uint32)(m + 0x20);
        if ((int)t < 0x40)
            t = 0x40;
        phase = (t >> 1) & 0x20;
        if (flag == 0) {
            int k;
            for (k = 0; k < 0x20; k += 4) {
                *(uint32*)(used + k * 4) = 0;
                *(uint32*)(used + (k + 1) * 4) = 0;
                *(uint32*)(used + (k + 2) * 4) = 0;
                *(uint32*)(used + (k + 3) * 4) = 0;
            }
        }
        for (contour = 0; contour < g->contourCountMax; contour++) {
            int start = g->sp[contour];
            int end = g->ep[contour];
            int16 prev = coords[start];
            int i = start + 1;
            while (i <= end) {
                int16 cur = coords[i];
                if ((uint16)((prev - cur) + 1) < 3) {
                    uint32 a = util_FixMul(prev, scale);
                    uint32 b;
                    uint32 idx;
                    if (phase == 0)
                        b = (a + 0x20) & 0xffffffc0;
                    else
                        b = (a & 0xffffffc0) + 0x20;
                    idx = (int)b >> 6;
                    if (flag != 0 || (used[idx & 0x7f] == 0 && used[(idx - 1) & 0x7f] == 0 &&
                                      used[(idx + 1) & 0x7f] == 0)) {
                        int16 d = (int16)b - (int16)a;
                        if (d < 0)
                            prev = (int16)(prev - (int16)((0x20 - (int)d * (int)s) >> 6));
                        else
                            prev = (int16)(prev + (int16)(((int)d * (int)s + 0x20) >> 6));
                        coords[i - 1] = prev;
                        coords[i] = prev;
                    }
                    used[idx & 0x7f] = 1;
                }
                prev = cur;
                i++;
            }
        }
    }
}

// @ 0x008cb070
// Stroke a whole glyph: allocate an empty destination glyph, stroke each contour into it, then
// copy the four phantom points across and free the source glyph.
GlyphClass* ff_glyph_StrokeGlyph(GlyphClass* g, int32 a, int b, int c, int d)
{
    GlyphClass* ng = New_EmptyGlyph(g->mem, 0, 0, 0, 0);
    int16 n = g->contourCountMax * 2;
    int i, gp, np;
    ng->contourCount = n;
    if (n <= 8) {
        ng->sp = ng->spBuffer;
        ng->ep = ng->spBuffer + 8;
    } else {
        int16* arr = (int16*)tsi_AllocMem(ng->mem, n * 4);
        ng->sp = arr;
        ng->ep = arr + n;
    }
    ng->ep[0] = 0;
    ng->sp[0] = 0;
    ng->contourCountMax = 0;
    for (i = 0; i < g->contourCountMax; i++)
        FUN_008caba0(i, ng, a, b, c, d, g);
    gp = g->pointCount;
    np = ng->pointCount;
    ng->ooy[np] = g->ooy[gp];
    ng->oox[np] = g->oox[gp];
    ng->ooy[np + 1] = g->ooy[gp + 1];
    ng->oox[np + 1] = g->oox[gp + 1];
    ng->ooy[np + 2] = g->ooy[gp + 2];
    ng->oox[np + 2] = g->oox[gp + 2];
    ng->ooy[np + 3] = g->ooy[gp + 3];
    ng->oox[np + 3] = g->oox[gp + 3];
    Delete_GlyphClass(g);
    return ng;
}

// @ 0x008cb1b0
// Decode two numbers packed into a run of bytes; each byte contributes one bit that says
// "another byte follows" and seven payload bits (high bits of the two outputs).
void ff_Read2Numbers(InputStream* in, uint16* out)
{
    uint8 buf[8];
    int count = 0;
    int idx = 0;
    uint8 b;
    out[0] = 0;
    out[1] = 0;
    do {
        b = ReadUnsignedByteMacro(in);
        buf[idx] = b >> 1;
        count++;
        if ((b & 1) == 0)
            break;
        idx++;
    } while (idx < 8);
    if (count - 1 >= 0) {
        uint16 u0 = out[0];
        uint16 u1 = out[1];
        int i = count - 1;
        do {
            uint8 c = buf[i];
            u1 = (uint16)(u1 * 8 | (c & 7));
            u0 = (uint16)((c >> 3 & 0xf) | (u0 << 4));
            buf[i] = c >> 7;
            i--;
        } while (i >= 0);
        out[0] = u0;
        out[1] = u1;
    }
}

// @ 0x008cb2e0
// Decode four numbers packed into a run of bytes (7 payload bits per byte: 3/2/1/1).
void ff_Read4Numbers(InputStream* in, uint16* out)
{
    uint8 buf[8];
    int count = 0;
    int idx = 0;
    uint8 b;
    out[0] = 0;
    out[1] = 0;
    out[2] = 0;
    out[3] = 0;
    do {
        b = ReadUnsignedByteMacro(in);
        buf[idx] = b >> 1;
        count++;
        if ((b & 1) == 0)
            break;
        idx++;
    } while (idx < 8);
    if (count - 1 >= 0) {
        uint16 u0 = out[0];
        uint16 u1 = out[1];
        uint16 u2 = out[2];
        uint16 u3 = out[3];
        int i = count - 1;
        do {
            uint8 c = buf[i];
            u3 = (uint16)(u3 * 8 | (c & 7));
            u2 = (uint16)(u2 * 4 | (c >> 3 & 3));
            u1 = (uint16)(u1 * 2 | (c >> 5 & 1));
            u0 = (uint16)((c >> 6 & 1) | (u0 * 2));
            buf[i] = c >> 7;
            i--;
        } while (i >= 0);
        out[0] = u0;
        out[1] = u1;
        out[2] = u2;
        out[3] = u3;
    }
}

// @ 0x008cb450
// Read a variable-length unsigned number: bytes 0xf0..0xff each carry four low bits, and the
// first byte below 0xf0 supplies the remaining high bits.  The stream arrives in ESI.
uint32 ReadLowUnsignedNumber(InputStream* in)
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

// @ 0x008cb520
// Grow the point arrays so that `count` points fit, copying the existing points.  The glyph
// arrives in ECX and the count in EAX.
void AllocatePointSpaceIfNeeded(GlyphClass* g, int32 count)
{
    if (count > g->pointCount32) {
        int16* oldOox = g->oox;
        int16* oldOoy = g->ooy;
        uint8* oldOn = g->onCurve;
        void* oldBase = g->x50;
        int n;
        int16* newOox;
        int16* newOoy;
        uint8* newOn;
        tsiMemObject* mem;
        int i;
        AllocGlyphPointMemory(g, count + 0x20);
        n = g->pointCount + 4;
        newOox = g->oox;
        newOoy = g->ooy;
        newOn = g->onCurve;
        for (i = 0; i < n; i++) {
            newOox[i] = oldOox[i];
            newOoy[i] = oldOoy[i];
            newOn[i] = oldOn[i];
        }
        mem = g->mem;
        if (oldBase == mem->base54)
            mem->flag8c = 1;
        else
            tsi_DeAllocMem(mem, oldBase);
    }
}

// @ 0x008cb5e0
// Open a sub-stream on one glyph's 'glyf' data, storing its length in *len.  The font arrives
// in ESI.
InputStream* GetGlyphStream(T2KSFont* font, int glyphIndex, int* len)
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

// @ 0x008cb6b0
// Decode the "preferred mapping" table: a version gate, a count, two 16-bit fields, then the
// key and value arrays.  The final field and every value are scaled by 8.
MappingTable* FUN_008cb6b0(tsiMemObject* mem, InputStream* in)
{
    int n = 0;
    MappingTable* t = 0;
    uint32 version = ReadInt32(in);
    int i;
    if (version - 0x10000 <= 0xffff) {
        t = (MappingTable*)tsi_AllocMem(mem, 0x18);
        t->mem = mem;
        t->version = version;
        n = ReadInt32(in);
        t->count = n;
        t->keys = (uint16*)tsi_AllocMem(mem, n * 4);
        t->values = t->keys + n;
        t->field0c = ReadInt16(in);
        t->field0e = ReadInt16(in);
        for (i = 0; i < n; i++)
            t->keys[i] = ReadInt16(in);
        for (i = 0; i < n; i++)
            t->values[i] = ReadInt16(in);
    }
    t->field0c = (uint16)(t->field0c << 3);
    for (i = 0; i < n; i++)
        t->values[i] = (uint16)(t->values[i] << 3);
    return t;
}

// @ 0x008cb790
// 16-bit binary search of a decoded mapping table; returns the mapped value or the table's
// default when the code is absent.
uint16 FUN_008cb790(MappingTable* t, uint16 code)
{
    uint16 def = t->field0c;
    int lo = 0;
    int hi = t->count - 1;
    do {
        int mid = (hi + lo) >> 1;
        uint16 v = t->keys[mid];
        if (code > v) {
            lo = mid + 1;
        } else if (code >= v) {
            def = t->values[mid];
            break;
        } else {
            hi = mid - 1;
        }
    } while (hi >= lo);
    return def;
}
