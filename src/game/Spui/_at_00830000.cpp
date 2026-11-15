// src/game/Spui/_at_00830000.cpp -- migrated from slice(s) s008356e0, s0082f9a0 by tools/migrate/rewrite.py
// Object file: Spui/_at_00830000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/UTFWin/CustomDrawable.h"
#include "EA/UTFWin/CustomWinProc.h"
#include "EA/UTFWin/IDrawable.h"
#include "EA/UTFWin/ISerializable.h"
#include "EA/UTFWin/IWinProc.h"
#include "EA/UTFWin/RenderContext.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void __cdecl VisitWindowTreeDepthFirst(void *, void *, void *); // 0x807d30
extern "C" void __cdecl VisitCallback_30020();                             // 0x830020

// ---- items of slice s0082f9a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void __cdecl VisitWindowTreeDepthFirst(void *, void *, void *); // 0x807d30
extern "C" void __cdecl VisitCallback_30020();                             // 0x830020
struct VisitCtx { uint8_t b; char pad[3]; uint32_t v; };
struct W20 {
    void *vptr;         // +0
    char  pad[0x1c];    // +4
    void *f20;          // +0x20
    bool  SetThing(void *p);   // 0x008300e0
};
// ---- items of slice s0082f9a0 end

// ---- items of slice s008356e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
static inline void** Vtbl(void* o) { return *(void***)o; }
template <class F> static F VFn(void* o, int byteOff) {
    return (F)(*(void**)((char*)Vtbl(o) + byteOff));
}
struct MultiHeapObject {};
void __cdecl FUN_00835f80(void* obj, void* owner);   // 0x835f80
struct TooltipHelper {
    void Attach(void* param);
};
struct IDrawable { virtual void d0(); };
struct ISerializable2 { virtual void s0(); };
struct CustomDrawable : IDrawable, ISerializable2, MultiHeapObject {
    int mRefCount;
    CustomDrawable() : mRefCount(0) {}
};
struct RenderContext {
    void* Begin2D(int);   // 0x0095bc10
    void  End2D();        // 0x0095bb20
};
struct DrawableImage {
    uint32_t pad0[7];   // +0x00
    int32_t  mWidth;    // +0x1c
};
class cSPUIVariableWidthDrawable : public CustomDrawable { public:
    void* mpImage;       // +0xc
    uint32_t mFillColor; // +0x10
    cSPUIVariableWidthDrawable();
    void Draw(RenderContext* ctx, float* rect, int unused);
};
// ---- items of slice s008356e0 end

// @ 0x00830080
void FUN_00830080(int *param_1)
{
    int *obj;
    if (param_1 == 0)
        obj = 0;
    else
        obj = (int *)((int (__thiscall *)(int *, int))(*(void ***)param_1)[0xc / 4])(param_1, 0x2f009dd0);

    VisitCtx ctx;
    ctx.v = *(uint32_t *)((char *)obj + 0x10);
    ctx.b = *(uint8_t *)((char *)obj + 0xc);
    VisitWindowTreeDepthFirst(*(void **)((char *)obj + 0x20), (void *)&VisitCallback_30020, &ctx);

    int *p = *(int **)((char *)obj + 0x20);
    if (p) {
        *(void **)((char *)obj + 0x20) = 0;
        ((void (__thiscall *)(void *))(*(void ***)p)[1])(p);
    }
}

// @ 0x008300e0
bool W20::SetThing(void *p)
{
    void *old = f20;
    if (p != old) {
        if (p)
            ((void (__thiscall *)(void *))(*(void ***)p)[0])(p);
        f20 = p;
        if (old)
            ((void (__thiscall *)(void *))(*(void ***)old)[1])(old);
    }
    void *q = (void *)((int (__thiscall *)(void *))(*(void ***)p)[0x14 / 4])(p);
    int a;
    if (this == 0)
        a = 0;
    else
        a = ((int (__thiscall *)(void *, int))(*(void ***)this)[0xc / 4])(this, 0xee3f516e);
    ((uint32_t (__thiscall *)(void *, void *, int))(*(void ***)q)[0x1c / 4])(q, (void *)&FUN_00830080, a);
    return false;
}

// @ 0x00835fa0
void TooltipHelper::Attach(void* param)
{
    FUN_00835f80(param, (char*)this - 4);
    void* r = VFn<void*(__thiscall*)(void*)>(this, 0x14)(this);
    *(void**)((char*)param + 0xc) = r;
}

// @ 0x00835fe0
void cSPUIVariableWidthDrawable::Draw(RenderContext* ctx, float* rect, int)
{
    void* painter = ctx->Begin2D(0);
    if (mpImage == 0) {
        VFn<void(__thiscall*)(void*, uint32_t)>(painter, 4)(painter, mFillColor);
        VFn<void(__thiscall*)(void*, float, float, float, float)>(painter, 0x38)(
            painter, rect[0], rect[1], rect[2], rect[3]);
    } else {
        if (mFillColor)
            VFn<void(__thiscall*)(void*, uint32_t)>(painter, 4)(painter, mFillColor);
        const float x0 = rect[0];
        const float y0 = rect[1];
        const float x1 = rect[2];
        const float y1 = rect[3];
        const float iw = (float)((DrawableImage*)mpImage)->mWidth;
        const float w = x1 - x0;
        if (iw > w) {
            // narrower than the image: draw the left and right slices, cropping the centre
            const float crop = (iw - w) * 0.5f;
            float uv1[4] = { 0.0f, 0.0f, (iw * 0.5f - crop) / iw, 1.0f };
            float d1[4] = { x0, y0, x1 - w * 0.5f, y1 };
            VFn<void(__thiscall*)(void*, float*, void*, float*)>(painter, 0x58)(
                painter, d1, mpImage, uv1);
            float uv2[4] = { (crop + iw * 0.5f) / iw, 0.0f, 1.0f, 1.0f };
            float d2[4] = { x0 + w * 0.5f, y0, x1, y1 };
            VFn<void(__thiscall*)(void*, float*, void*, float*)>(painter, 0x58)(
                painter, d2, mpImage, uv2);
        } else if (w == iw) {
            float uv[4] = { 0.0f, 0.0f, 1.0f, 1.0f };
            VFn<void(__thiscall*)(void*, float*, void*, float*)>(painter, 0x58)(
                painter, rect, mpImage, uv);
        } else {
            // wider than the image: draw the left/right slices and tile the centre strip
            const float half = iw * 0.5f;
            const float quarter = iw * 0.25f;
            float uvL[4] = { 0.0f, 0.0f, 0.5f, 1.0f };
            float dL[4] = { x0, y0, half, y1 };
            VFn<void(__thiscall*)(void*, float*, void*, float*)>(painter, 0x58)(
                painter, dL, mpImage, uvL);
            float uvR[4] = { 0.5f, 0.0f, 1.0f, 1.0f };
            float dR[4] = { x1 - half, y0, x1, y1 };
            VFn<void(__thiscall*)(void*, float*, void*, float*)>(painter, 0x58)(
                painter, dR, mpImage, uvR);
            float left = x0 + half;
            const float right = x1 - half;
            float uvM[4] = { 0.375f, 0.0f, 0.625f, 1.0f };
            float dM[4] = { left, y0, right, y1 };
            if (left < right) {
                do {
                    const float span = right - left;
                    dM[0] = left;
                    if (span > quarter) {
                        dM[2] = left + quarter;
                        uvM[2] = 0.625f;
                    } else {
                        dM[2] = right;
                        uvM[2] = 0.375f + span / iw;
                    }
                    VFn<void(__thiscall*)(void*, float*, void*, float*)>(painter, 0x58)(
                        painter, dM, mpImage, uvM);
                    left += quarter;
                } while (right > left);
            }
        }
    }
    ctx->End2D();
}

// @ 0x00836420
cSPUIVariableWidthDrawable::cSPUIVariableWidthDrawable()
: mpImage(0), mFillColor(0xffffffff) {}
