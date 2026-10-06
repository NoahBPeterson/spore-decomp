// T2K (Type 2000) Type 1 font engine: Type1BuildChar, the Type 1 charstring interpreter
// (hsbw/rlineto/rrcurveto/callsubr/seac/callothersubr flex+hint replacement, multiple master blends).
// Several callees use custom register conventions in the original (T1GetGlyphIndexFromAdobeCode takes
// the class in eax and the code in si); they are declared as ordinary functions here, so this source is a
// behavior-complete (not byte-exact) reconstruction.
#include "types.h"
typedef uint8_t uint8; typedef int16_t int16; typedef uint16_t uint16;
typedef uint32_t uint32; typedef int32_t int32;

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

// Hint outline accumulator: parallel int16 arrays with counts/capacities
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
// 0xcc.. fields accessed through helpers below (kept out of the struct to avoid a giant pad)
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
