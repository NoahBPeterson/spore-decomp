// src/game/UTFSpore_Win32/t1.cpp -- migrated from slice(s) s008b8f30, s008b71c0 by tools/migrate/rewrite.py
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
extern "C" uint32 tsi_PSNameToAppleCode(uint8* name, uint16* code, uint16* a, uint16* b);           // 0x008b6f90
struct T1Class_s008b_8f30 {
    tsiMemObject* mem;           // 0x00
    char   pad04[0x30 - 4];
    int16  numGlyphs;            // 0x30
    char   pad32[6];
    int16* adobeCodes;           // 0x38
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
// ---- items of slice s008b8f30 end

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
