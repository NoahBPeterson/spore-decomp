// s008e9a10 -- EA::XHTML::Layout block-edge tessellation helpers.
//
// Reconstructed from the disassembly in work/match/scratch_s008e9a10_cards.txt.
// MSVC 2008 SP1, /O2 /MD /Gy /TP /GS- /arch:SSE /fp:fast (same module as the
// neighbouring slices s008e8af0 / s008e7230; no /EHsc).
//
// 008e9a10 / 008e9b10 / 008e9fe0 are free __stdcall helpers: arg1 is the
// RenderingContext* that also becomes ecx for the inner calls (ReleaseScroll /
// ScrollViewport / DrawQuad).  008e9e30 is a __thiscall member of the output
// block-metrics struct (ecx = destination, arg1 = source StyleState, arg2 = the
// reference length used by Length::ToPixelsNonNeg).
//
// 008e9a10, 008e9b10 and 008e9e30 are byte-exact (manifest.txt).  008e9fe0 is
// reconstructed in full and behaviourally equivalent but not byte-exact: its
// frame-pointer prologue, callee-saved allocation and integer (non-x87) moves of
// the float bit patterns match the original exactly, only the frame-slot ORDER of
// the aligned gradient vs the corner array differs (nonmatching.txt).
#include "types.h"
#include <math.h>
#include <stddef.h>

typedef unsigned int  uint;
typedef unsigned char uchar;

namespace EA { namespace XHTML {

namespace Style {

class FontMetrics { public:
    float mfFontSize, mfEmSize, mfExSize, mfAscent, mfDescent;
};

struct Length {
    float mValue;   // +0
    int mUnits;     // +4
    float ToPixelsNonNeg(float reference, const FontMetrics& fm) const;   // 0x008f9660
};

}  // namespace Style

namespace Layout {

// RenderingContext (subset): vtable at +0, scroll object at +0, base offsets
// +0x534/+0x538.  ReleaseScroll tail-jumps through the scroll object's vtable.
class RenderingContext {
public:
    void ReleaseScroll(int arg);                                  // 0x008ee7a0 (thiscall)
    void ScrollViewport(float x0, float y0, float x1, float y1);  // 0x008ee7b0 (thiscall)
    void DrawQuad(const float* p0, uint32_t v0, const float* p1, uint32_t v1,
                  const float* p2, uint32_t v2, const float* p3, uint32_t v3);  // 0x008eebb0
};

// Output of FUN_008e9e30: four edge ints, four edge ints, four resolved
// lengths and a "has any visible edge" flag.
struct BlockMetrics {
    int   m0, m1, m2, m3;          // +0x00
    int   m4, m5, m6, m7;          // +0x10
    float f8, f9, f10, f11;        // +0x20
    uchar mFlag;                   // +0x30

    void FUN_008e9e30(const char* src, float reference);   // 0x008e9e30 (thiscall)
};

}  // namespace Layout

}}  // namespace EA::XHTML

void __cdecl FUN_008e9900(int color, int x, float* out, int count);   // 0x008e9900

using namespace EA::XHTML;
using namespace EA::XHTML::Layout;
using EA::XHTML::Style::Length;
using EA::XHTML::Style::FontMetrics;

// ============================ function bodies ============================

// @ 0x008e9a10
void __stdcall FUN_008e9a10(RenderingContext* ctx, float* a, float* b, int* c, uchar flags)
{
    if (flags & 8) {
        ctx->ReleaseScroll(c[0]);
        ctx->ScrollViewport(a[0], b[1], b[0], b[3]);
    }
    if (flags & 1) {
        ctx->ReleaseScroll(c[1]);
        ctx->ScrollViewport(a[0], a[1], a[2], b[1]);
    }
    if (flags & 2) {
        ctx->ReleaseScroll(c[2]);
        ctx->ScrollViewport(b[2], b[1], a[2], b[3]);
    }
    if (flags & 4) {
        ctx->ReleaseScroll(c[3]);
        ctx->ScrollViewport(a[0], b[3], a[2], a[3]);
    }
}

// @ 0x008e9b10
void __stdcall FUN_008e9b10(RenderingContext* ctx, float* a, float* b, int* c,
                            uchar flags, float step)
{
    if (flags & 8) {
        ctx->ReleaseScroll(c[0]);
        float delta = (b[0] - a[0]) * step;
        float cur = b[1] + delta;
        if (b[3] >= cur) {
            float delta2 = delta * 2.0f;
            do {
                float next = cur + delta;
                if (next + delta >= b[3])
                    next = b[3];
                ctx->ScrollViewport(a[0], cur, b[0], next);
                cur = cur + delta2;
            } while (b[3] >= cur);
        }
    }
    if (flags & 1) {
        ctx->ReleaseScroll(c[1]);
        float delta = (b[1] - a[1]) * step;
        float cur = a[0];
        if (a[2] >= cur) {
            float delta2 = delta * 2.0f;
            do {
                float next = cur + delta;
                if (next + delta >= a[2])
                    next = a[2];
                ctx->ScrollViewport(cur, a[1], next, b[1]);
                cur = cur + delta2;
            } while (a[2] >= cur);
        }
    }
    if (flags & 2) {
        ctx->ReleaseScroll(c[2]);
        float delta = (a[2] - b[2]) * step;
        float cur = b[1] + delta;
        if (b[3] >= cur) {
            float delta2 = delta * 2.0f;
            do {
                float next = cur + delta;
                if (next + delta >= b[3])
                    next = b[3];
                ctx->ScrollViewport(b[2], cur, a[2], next);
                cur = cur + delta2;
            } while (b[3] >= cur);
        }
    }
    if (flags & 4) {
        ctx->ReleaseScroll(c[3]);
        float delta = (a[3] - b[3]) * step;
        float cur = a[0];
        if (a[2] >= cur) {
            float delta2 = delta * 2.0f;
            do {
                float next = cur + delta;
                if (next + delta >= a[2])
                    next = a[2];
                ctx->ScrollViewport(cur, b[3], next, a[3]);
                cur = cur + delta2;
            } while (a[2] >= cur);
        }
    }
}

// @ 0x008e9e30
void BlockMetrics::FUN_008e9e30(const char* src, float reference)
{
    m0 = *(int*)(src + 0x368);
    m2 = *(int*)(src + 0x328);
    m1 = *(int*)(src + 0x308);
    m3 = *(int*)(src + 0x348);
    if (m0 == 0) m0 = *(int*)(src + 0x2c0);
    if (m2 == 0) m2 = *(int*)(src + 0x2c0);
    if (m1 == 0) m1 = *(int*)(src + 0x2c0);
    if (m3 == 0) m3 = *(int*)(src + 0x2c0);
    m4 = *(int*)(src + 0x364);
    m6 = *(int*)(src + 0x324);
    m5 = *(int*)(src + 0x304);
    m7 = *(int*)(src + 0x344);
    const FontMetrics& fm = *(FontMetrics*)(src + 0x430);
    f8  = (float)floor((double)(((const Length*)(src + 0x35c))->ToPixelsNonNeg(reference, fm) + 0.5f));
    f10 = (float)floor((double)(((const Length*)(src + 0x31c))->ToPixelsNonNeg(reference, fm) + 0.5f));
    f9  = (float)floor((double)(((const Length*)(src + 0x2fc))->ToPixelsNonNeg(reference, fm) + 0.5f));
    f11 = (float)floor((double)(((const Length*)(src + 0x33c))->ToPixelsNonNeg(reference, fm) + 0.5f));
    mFlag = 1;
    if ((f8 == 0.0f || m4 == 0) && (f10 == 0.0f || m6 == 0) &&
        (f9 == 0.0f || m5 == 0) && (f11 == 0.0f || m7 == 0))
        mFlag = 0;
}

// @ 0x008e9fe0
void __stdcall FUN_008e9fe0(RenderingContext* ctx, float* a, float* b, int* c,
                            float x, uchar flags)
{
    float pts[8];
    __declspec(align(8)) uint32_t grad[4];
    int last = 0;

    ctx->ReleaseScroll(-1);

    if (flags & 8) {
        FUN_008e9900(c[0], *(int*)&x, (float*)grad, 4);
        pts[6] = a[3];
        pts[7] = a[0];
        pts[4] = b[3];
        last = c[0];
        pts[5] = b[0];
        pts[2] = b[1];
        pts[0] = a[1];
        pts[3] = pts[5];
        pts[1] = pts[7];
        ctx->DrawQuad(&pts[1], grad[0], &pts[3], grad[1],
                      &pts[5], grad[1], &pts[7], grad[0]);
    }
    if (flags & 1) {
        if (last != c[1] || last == 0)
            FUN_008e9900(c[1], *(int*)&x, (float*)grad, 4);
        last = c[1];
        pts[1] = b[0];
        pts[3] = b[2];
        pts[2] = b[1];
        pts[5] = a[2];
        pts[7] = a[0];
        pts[6] = a[1];
        pts[4] = pts[6];
        pts[0] = pts[2];
        ctx->DrawQuad(&pts[7], grad[0], &pts[5], grad[0],
                      &pts[3], grad[1], &pts[1], grad[1]);
    }
    if (flags & 2) {
        if (last != c[2] || last == 0)
            FUN_008e9900(c[2], *(int*)&x, (float*)grad, 4);
        last = c[2];
        pts[0] = b[3];
        pts[7] = b[2];
        pts[2] = a[3];
        pts[5] = a[2];
        pts[4] = a[1];
        pts[6] = b[1];
        pts[3] = pts[5];
        pts[1] = pts[7];
        ctx->DrawQuad(&pts[7], grad[2], &pts[5], grad[3],
                      &pts[3], grad[3], &pts[1], grad[2]);
    }
    if (flags & 4) {
        if (last != c[3] || last == 0)
            FUN_008e9900(c[3], *(int*)&x, (float*)grad, 4);
        last = c[3];
        pts[3] = b[2];
        pts[1] = a[2];
        pts[5] = b[0];
        pts[4] = b[3];
        pts[6] = a[3];
        pts[7] = a[0];
        pts[2] = pts[4];
        pts[0] = pts[6];
        ctx->DrawQuad(&pts[7], grad[3], &pts[5], grad[2],
                      &pts[3], grad[2], &pts[1], grad[3]);
    }
}
