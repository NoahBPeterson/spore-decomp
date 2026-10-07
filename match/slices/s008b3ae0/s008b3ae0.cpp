// T2K (Type 2000) PFR font engine: PFRBuildChar (builds one glyph outline, recursing for composites).
// Several callees use custom register conventions in the original (pfr in esi/eax/edi); they are
// declared here as ordinary functions with those registers passed explicitly, so this source is a
// behavior-complete (not byte-exact) reconstruction.
#include "types.h"
typedef uint8_t uint8; typedef int16_t int16; typedef uint16_t uint16;
typedef uint32_t uint32; typedef int32_t int32;

struct tsiMemObject;
struct InputStream;
struct PFRClass;

extern "C" void* tsi_AllocMem(tsiMemObject* mem, uint32 size);                 // 0x008d1260
extern "C" void  tsi_DeAllocMem(tsiMemObject* mem, void* p);                   // 0x008d1440
extern "C" void* tsi_ReAllocMem(tsiMemObject* mem, void* p, uint32 size);      // 0x008d1330
extern "C" void  Seek_InputStream(InputStream* in, int pos);                   // 0x008cc580
extern "C" void  PeekInt16(InputStream* in, void* dst, int n);                 // 0x008cc220
extern "C" int   util_FixMul(int a, int b);                                    // 0x008d1590

// Glyph builder (pfr+0xfc)
struct GlyphBuilder { char pad[0x38]; int16 contour; };
extern "C" void glyph_AddPoint(GlyphBuilder* g, int x, int y, int onCurve);    // 0x008b0320
extern "C" void glyph_CloseContour(GlyphBuilder* g);                           // 0x008afde0

// Outline accumulator (param_9): parallel int16 arrays with counts/capacities
struct PFROutline {
    tsiMemObject* mem;           // 0x000
    char   pad4[0x2c0 - 4];
    int16* xAll;                 // 0x2c0  per-point tags for x set (indexed cntXPts + cntXSet)
    int16  capXAll, pad2c6;      // 0x2c4
    int16* yAll;                 // 0x2c8
    int16  capYAll, pad2ce;      // 0x2cc
    int16* xSetArr;              // 0x2d0
    int16  capXSet, cntXSet;     // 0x2d4, 0x2d6
    int16* ySetArr;              // 0x2d8
    int16  capYSet, cntYSet;     // 0x2dc, 0x2de
    int16* xPts;                 // 0x2e0
    int16  capXPts, cntXPts;     // 0x2e4, 0x2e6
    int16* yPts;                 // 0x2e8
    int16  capYPts, cntYPts;     // 0x2ec, 0x2ee
    char   pad2f0[0x34c - 0x2f0];
    int16  numChars;             // 0x34c
};

struct PFRClass {
    tsiMemObject* mem;           // 0x00
    InputStream*  stream;        // 0x04
    uint8  ver;                  // 0x08
    char   pad09[0x28 - 9];
    int    f28;                  // 0x28
    int    dataBase;             // 0x2c
    char   pad30[4];
    uint8  inContour;            // 0x34
    char   pad35[0xb4 - 0x35];
    int    fb4;                  // 0xb4
    char   padb8[0xe0 - 0xb8];
    int    m[6];                 // 0xe0 transform: m0 m1 m2 m3 tx ty
    char   pade8[0xfc - 0xf8];
    GlyphBuilder* glyph;         // 0xfc
};

// Per-glyph coordinate sets decoded by FUN_008b0920 (stack local)
struct PFRPts {
    int16 nx;  int16 xs[64];     // 0x000
    int16 ny;  int16 ys[64];     // 0x082
    int16 curX, curY;            // 0x104
    int16 w4, w2;                // 0x108
};
struct PFRState { uint8* cur; int16 flag; };   // command stream cursor for FUN_008b3680
struct PFRRec { int v[4]; int offset; uint32 size; };   // component record / saved matrix

// Callees (custom register conventions in the original)
extern "C" void FUN_008b2630(PFRClass* pfr, uint8** cursor, PFRRec* out, int* scratch);          // 0x008b2630
extern "C" void FUN_008b0920(PFRClass* pfr, uint8 flags, uint8** cursor, PFRPts* pts);          // 0x008b0920
extern "C" void FUN_008b0f10(uint8** cursor, uint32 flags, PFRPts* pts, uint32* a, uint32* b);   // 0x008b0f10
extern "C" void FUN_008b3390(PFROutline* o, PFRClass* pfr, uint8** extra);                       // 0x008b3390 (eax = o)
extern "C" void FUN_008b3680(PFRPts* pts, PFRState* st, int16* out, int* type);                  // 0x008b3680 (ecx/eax/edi)
extern "C" void SetupTrans(PFRClass* pfr, int sx, int sy, int tx, int ty);                       // 0x008b1db0 (ecx=tx eax=ty)
// x, y are 16.16 fixed; outputs are 16.16 fixed
extern "C" void TransformPoint(PFRClass* pfr, int x, int y, int* ox, int* oy);                   // 0x008b1e60 (eax = x)

static inline void Xf(PFRClass* c, int x, int y, int* ox, int* oy)
{
    int a = util_FixMul(y << 16, c->m[2]);
    a += util_FixMul(x << 16, c->m[0]);
    int b = util_FixMul(x << 16, c->m[1]);
    int d = util_FixMul(y << 16, c->m[3]);
    *ox = a + c->m[4];
    *oy = c->m[5] + b + d;
}

static inline uint8* SkipItems(uint8* cur, uint32 n)
{
    for (; n != 0; --n) cur += *cur + 2;
    return cur;
}

// @ 0x008b3ae0
extern "C" void PFRBuildChar(PFRClass* pfr, uint8* data, int param_3, uint16 dataLen,
                             int p5, int p6, int p7, int p8, PFROutline* out)
{
    uint8* cur = data + 1;
    uint8 flags = *data;
    PFRRec rec;
    PFRPts pts;

    if ((int8_t)flags < 0) {
        // composite glyph: a list of component records
        if (flags & 0x40) {
            uint32 n = *cur;
            cur = SkipItems(cur + 1, n);
        }
        int count = (int16)(flags & 0x3f);
        for (; count > 0; --count) {
            FUN_008b2630(pfr, &cur, &rec, &param_3);
            int off = rec.offset;
            Seek_InputStream(pfr->stream, pfr->dataBase + off);
            uint32 sz = rec.size & 0xffff;
            uint8* buf = (uint8*)tsi_AllocMem(pfr->mem, sz);
            PeekInt16(pfr->stream, buf, sz);
            PFRBuildChar(pfr, buf, off, (uint16)rec.size, rec.v[0], rec.v[2], rec.v[1], rec.v[3], out);
            tsi_DeAllocMem(pfr->mem, buf);
        }
        return;
    }

    GlyphBuilder* g = pfr->glyph;
    pts.ny = 0; pts.curX = 0; pts.nx = 0; pts.curY = 0;
    FUN_008b0920(pfr, flags, &cur, &pts);

    uint8* extra = 0;
    if (flags & 8) {
        extra = cur;
        cur = SkipItems(cur + 1, *cur);
    }

    // save the transform, then compose the component's scale/offset into it
    rec.v[0] = pfr->m[0]; rec.v[1] = pfr->m[1]; rec.v[2] = pfr->m[2]; rec.v[3] = pfr->m[3];
    rec.offset = pfr->m[4]; rec.size = pfr->m[5];
    SetupTrans(pfr, p5, p6, p7, p8);

    if (out != 0) {
        if (extra != 0)
            FUN_008b3390(out, pfr, &extra);

        // ---- x coordinate set ----
        int16 n = pts.nx;
        if (n < 1) {
            out->xAll[out->cntXPts + out->cntXSet] = -999;
            if (out->capXSet <= out->cntXSet + 1) {
                out->capXSet += 0x14;
                out->xSetArr = (int16*)tsi_ReAllocMem(out->mem, out->xSetArr, out->capXSet * 2);
            }
            out->xSetArr[out->cntXSet] = pfr->glyph->contour;
            out->cntXSet++;
        } else {
            if (out->capXPts <= out->cntXPts + n) {
                int16 add = (n < 0x14) ? 0x14 : n;
                out->capXPts += add;
                out->xPts = (int16*)tsi_ReAllocMem(out->mem, out->xPts, out->capXPts * 2);
            }
            if (out->capXAll <= out->cntXPts + out->cntXSet + n) {
                int16 add = (n < 0x14) ? 0x14 : n;
                out->capXAll += out->cntXSet + add;
                out->xAll = (int16*)tsi_ReAllocMem(out->mem, out->xAll, out->capXAll * 2);
            }
            for (int i = 0; i < pts.nx; i++) {
                int ox, oy;
                TransformPoint(pfr, pts.xs[i] << 16, 1, &ox, &oy);
                out->xPts[out->cntXPts + i] = (int16)(ox >> 16);
                out->xAll[out->cntXSet + out->cntXPts + i] = pfr->glyph->contour;
            }
        }
        out->cntXPts += pts.nx;

        // ---- y coordinate set ----
        n = pts.ny;
        if (n < 1) {
            out->yAll[out->cntYSet + out->cntYPts] = -999;
            if (out->capYSet <= out->cntYSet + 1) {
                out->capYSet += 0x14;
                out->ySetArr = (int16*)tsi_ReAllocMem(out->mem, out->ySetArr, out->capYSet * 2);
            }
            out->ySetArr[out->cntYSet] = pfr->glyph->contour;
            out->cntYSet++;
        } else {
            if (out->capYPts <= out->cntYPts + n) {
                int16 add = (n < 0x14) ? 0x14 : n;
                out->capYPts += add;
                out->yPts = (int16*)tsi_ReAllocMem(out->mem, out->yPts, out->capYPts * 2);
            }
            if (out->capYAll <= out->cntYPts + out->cntYSet + n) {
                int16 add = (n < 0x14) ? 0x14 : n;
                out->capYAll += out->cntYSet + add;
                out->yAll = (int16*)tsi_ReAllocMem(out->mem, out->yAll, out->capYAll * 2);
            }
            for (int i = 0; i < pts.ny; i++) {
                int ox, oy;
                TransformPoint(pfr, 1, pts.ys[i] << 16, &ox, &oy);
                out->yPts[out->cntYPts + i] = (int16)(oy >> 16);
                out->yAll[out->cntYPts + out->cntYSet + i] = pfr->glyph->contour;
            }
        }
        out->cntYPts += pts.ny;
        out->numChars++;
    }

    if (pfr->ver == 0) {
        // simple command stream
        pfr->inContour = 0;
        for (;;) {
            uint32 b = *cur++;
            switch (b >> 4) {
            case 0:
                if (pfr->inContour) {
                    glyph_CloseContour(g);
                    pfr->inContour = 0;
                }
                pfr->m[0] = rec.v[0]; pfr->m[1] = rec.v[1]; pfr->m[2] = rec.v[2]; pfr->m[3] = rec.v[3];
                pfr->m[4] = rec.offset; pfr->m[5] = rec.size;
                return;
            case 1: {
                uint32 a, c; int ox, oy;
                FUN_008b0f10(&cur, b, &pts, &a, &c);
                TransformPoint(pfr, (int16)a << 16, (int16)c << 16, &ox, &oy);
                glyph_AddPoint(g, (int16)(ox >> 16), (int16)(oy >> 16), 1);
                break;
            }
            case 2: {
                int ox, oy;
                pts.curX = pts.xs[b & 0xf];
                TransformPoint(pfr, pts.curX << 16, pts.curY << 16, &ox, &oy);
                glyph_AddPoint(g, (int16)(ox >> 16), (int16)(oy >> 16), 1);
                break;
            }
            case 3: {
                int ox, oy;
                pts.curY = pts.ys[b & 0xf];
                TransformPoint(pfr, pts.curX << 16, pts.curY << 16, &ox, &oy);
                glyph_AddPoint(g, (int16)(ox >> 16), (int16)(oy >> 16), 1);
                break;
            }
            case 4:
            case 5: {
                uint32 a, c; int ox, oy;
                FUN_008b0f10(&cur, b, &pts, &a, &c);
                if (pfr->inContour)
                    glyph_CloseContour(g);
                TransformPoint(pfr, (int16)a << 16, (int16)c << 16, &ox, &oy);
                glyph_AddPoint(g, (int16)(ox >> 16), (int16)(oy >> 16), 1);
                pfr->inContour = 1;
                break;
            }
            case 6: {
                uint32 a1, b1, a2, b2, a3, b3; int x1, y1, x2, y2, x3, y3;
                FUN_008b0f10(&cur, 0xe, &pts, &a1, &b1);
                FUN_008b0f10(&cur, 8, &pts, &a2, &b2);
                FUN_008b0f10(&cur, 0xb, &pts, &a3, &b3);
                TransformPoint(pfr, (int16)a1 << 16, (int16)b1 << 16, &x1, &y1);
                TransformPoint(pfr, (int16)a2 << 16, (int16)b2 << 16, &x2, &y2);
                TransformPoint(pfr, (int16)a3 << 16, (int16)b3 << 16, &x3, &y3);
                glyph_AddPoint(g, (int16)(x1 >> 16), (int16)(y1 >> 16), 0);
                glyph_AddPoint(g, (int16)(x2 >> 16), (int16)(y2 >> 16), 0);
                glyph_AddPoint(g, (int16)(x3 >> 16), (int16)(y3 >> 16), 1);
                break;
            }
            case 7: {
                uint32 a1, b1, a2, b2, a3, b3; int x1, y1, x2, y2, x3, y3;
                FUN_008b0f10(&cur, 0xb, &pts, &a1, &b1);
                FUN_008b0f10(&cur, 2, &pts, &a2, &b2);
                FUN_008b0f10(&cur, 0xe, &pts, &a3, &b3);
                TransformPoint(pfr, (int16)a1 << 16, (int16)b1 << 16, &x1, &y1);
                TransformPoint(pfr, (int16)a2 << 16, (int16)b2 << 16, &x2, &y2);
                TransformPoint(pfr, (int16)a3 << 16, (int16)b3 << 16, &x3, &y3);
                glyph_AddPoint(g, (int16)(x1 >> 16), (int16)(y1 >> 16), 0);
                glyph_AddPoint(g, (int16)(x2 >> 16), (int16)(y2 >> 16), 0);
                glyph_AddPoint(g, (int16)(x3 >> 16), (int16)(y3 >> 16), 1);
                break;
            }
            default: {
                uint32 a1, b1, a2, b2, a3, b3; int x1, y1, x2, y2, x3, y3;
                FUN_008b0f10(&cur, b, &pts, &a1, &b1);
                uint32 b2byte = *cur++;
                FUN_008b0f10(&cur, b2byte, &pts, &a2, &b2);
                FUN_008b0f10(&cur, b2byte >> 4, &pts, &a3, &b3);
                Xf(pfr, (int16)a1, (int16)b1, &x1, &y1);
                Xf(pfr, (int16)a2, (int16)b2, &x2, &y2);
                Xf(pfr, (int16)a3, (int16)b3, &x3, &y3);
                glyph_AddPoint(g, (int16)(x1 >> 16), (int16)(y1 >> 16), 0);
                glyph_AddPoint(g, (int16)(x2 >> 16), (int16)(y2 >> 16), 0);
                glyph_AddPoint(g, (int16)(x3 >> 16), (int16)(y3 >> 16), 1);
                break;
            }
            }
        }
    }

    // ver != 0: command stream decoded by FUN_008b3680
    uint8* end = data + (dataLen - 1);
    PFRState st;
    int16 pt[6];
    pts.w2 = 0; pts.w4 = 0; pts.curX = 0; pts.curY = 0;
    st.cur = cur;
    st.flag = 0;
    int type = -1;
    pfr->inContour = 0;
    while (st.cur < end || (st.cur == end && st.flag == 0)) {
        FUN_008b3680(&pts, &st, pt, &type);
        if ((int16)type == 0) {
            if (pfr->inContour)
                glyph_CloseContour(g);
            int x, y;
            Xf(pfr, pt[0], pt[1], &x, &y);
            glyph_AddPoint(g, (int16)(x >> 16), (int16)(y >> 16), 1);
            pfr->inContour = 1;
        } else if ((int16)type == 1) {
            int x16 = pt[0] << 16;
            int y16 = pt[1] << 16;
            int tx = util_FixMul(p5, x16) + p7;
            int ty = util_FixMul(p6, y16) + p8;
            int t2 = util_FixMul(ty, pfr->fb4);
            util_FixMul(tx + t2, pfr->f28);
            util_FixMul(ty, pfr->f28);
            int x, y;
            Xf(pfr, pt[0], pt[1], &x, &y);
            glyph_AddPoint(g, (int16)(x >> 16), (int16)(y >> 16), 1);
        } else if ((int16)type == 2) {
            int x1, y1, x2, y2, x3, y3;
            Xf(pfr, pt[0], pt[1], &x1, &y1);
            Xf(pfr, pt[2], pt[3], &x2, &y2);
            Xf(pfr, pt[4], pt[5], &x3, &y3);
            glyph_AddPoint(g, (int16)(x1 >> 16), (int16)(y1 >> 16), 0);
            glyph_AddPoint(g, (int16)(x2 >> 16), (int16)(y2 >> 16), 0);
            glyph_AddPoint(g, (int16)(x3 >> 16), (int16)(y3 >> 16), 1);
        }
    }
    pfr->m[0] = rec.v[0]; pfr->m[1] = rec.v[1]; pfr->m[2] = rec.v[2]; pfr->m[3] = rec.v[3];
    pfr->m[4] = rec.offset; pfr->m[5] = rec.size;
    if (pfr->inContour) {
        glyph_CloseContour(g);
        pfr->inContour = 0;
    }
}
