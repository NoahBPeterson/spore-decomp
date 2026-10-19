// src/game/UTFSpore_Win32/StdDrawable.cpp -- migrated from slice(s) s01300280, s009873a0 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/StdDrawable.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/UTFWin/Window.h"
#include "EA/UTFWin/RenderContext.h"
#include "EA/Stopwatch.h"
#include "EA/UTFWin/cDropShadowDescriptor.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void  FUN_0095c5f0(void*, void*, void*, void*, float, float, int, int); // 0x95c5f0
extern "C" void  FUN_0095ca40(void*, void*, void*, void*, float*, float, float);   // 0x95ca40
extern "C" void  FUN_0095d000(void*, void*, void*, void*, float*, float, float);   // 0x95d000 BltEdgeStretch
extern "C" void  FUN_0095d780(void*, void*, int, int, float);                      // 0x95d780 DrawStdButton
extern "C" void  FUN_0095da40(void*, void*, int, float);                           // 0x95da40
extern "C" double FUN_011e0906(double);                       // floor
#include <math.h>
#pragma intrinsic(sqrt)

// ---- items of slice s009873a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void  FUN_0095c5f0(void*, void*, void*, void*, float, float, int, int); // 0x95c5f0
extern "C" void  FUN_0095ca40(void*, void*, void*, void*, float*, float, float);   // 0x95ca40
extern "C" void  FUN_0095d000(void*, void*, void*, void*, float*, float, float);   // 0x95d000 BltEdgeStretch
extern "C" void  FUN_0095d780(void*, void*, int, int, float);                      // 0x95d780 DrawStdButton
extern "C" void  FUN_0095da40(void*, void*, int, float);                           // 0x95da40
extern "C" double FUN_011e0906(double);                       // floor
struct RenderContext { int* Begin2D(int mode); };            // 0x95bc10 EA::UTFWin::RenderContext::Begin2D (thiscall)
struct ShadowDesc32;
void __cdecl CopyWithQualityAdjustment(ShadowDesc32* dst, ShadowDesc32* src, int quality); // 0x96e3a0
struct ShadowDesc32 {
    int   m00;      // +0x00 mode
    int   m04;      // +0x04
    int   m08;      // +0x08
    float f0c;
    float f10;
    float f14;
    float f18;
    int   m1c;
    int   m20;
    int   m24;
    void SetMode1(int);   // 0x830280
    void SetMode2(int);   // 0x830150
};
struct ShadowDescC : ShadowDesc32 {
    void Init()
    {
        m00 = 0;
        m04 = 2;
        m08 = 3;
        f14 = 0.0f;
        f18 = 0.0f;
        f0c = 0.0f;
        f10 = 0.0f;
        m24 = 0;
        SetMode2(2);
    }
};
struct StdDrawableBase0 {
    void* v[4];                     // +0x00 vtable ptrs (0,4,8,c)
    StdDrawableBase0()
    {
        *(void* volatile*)&v[1] = (void*)0x13fa72c;
        v[2] = 0;
        *(void* volatile*)&v[3] = (void*)0x1445200;
    }
};
struct StdDrawableBase : StdDrawableBase0 {
    StdDrawableBase()
    {
        *(void* volatile*)&v[0] = (void*)0x1445298;
        *(void* volatile*)&v[1] = (void*)0x1445280;
        *(void* volatile*)&v[3] = (void*)0x1445240;
    }
};
struct StdDrawable : StdDrawableBase {
    void* mpImage[8];               // +0x10
    int   mScalingType;             // +0x30
    float mAreaL, mAreaT, mAreaR, mAreaB;  // +0x34
    float mScaleX, mScaleY;         // +0x44
    void* mHitMask;                 // +0x4c
    float mBevelWidth;              // +0x50
    ShadowDescC  mShadow;           // +0x54

    void  SetSerializerX();                        // 0xc2e4e0
    void  FUN_00987900();                          // 0x987900
    void  SetImageAt(unsigned idx, void* img);     // 0x987970
    void* GetImageAt(unsigned idx);                // 0x9879b0
    void* GetImageForState(unsigned st);           // 0x9879f0
    ~StdDrawable();                                // 0x987b10
    void  draw_with_image(int* sink, void* p3, void* p4);   // 0x987bf0
    void  CreateRenderables(void* ctx, float* rect, unsigned* flags);  // 0x987d40
    bool  HitTest(float* rect, int* pt, int unused);                   // 0x9880e0
    bool  QueryAttribute(int id, unsigned* out);                       // 0x9883c0
    bool  GetNaturalSize(float* out, int state, int unused);           // 0x9883f0
    StdDrawable();                                                     // 0x988420
};
// ---- items of slice s009873a0 end

// @ 0x00987970
void StdDrawable::SetImageAt(unsigned idx, void* img)
{
    if (idx >= 8)
        return;
    if (img)
        (*(void(__thiscall**)(void*))*(void**)img)(img);
    void* old = *(void**)((char*)this + 4 + idx * 4);
    if (old)
        (*(void(__thiscall**)(void*))((char*)*(void**)old + 4))(old);
    *(void**)((char*)this + 4 + idx * 4) = img;
}

// @ 0x009879b0
void* StdDrawable::GetImageAt(unsigned idx)
{
    if (idx >= 8)
        return 0;
    return *(void**)((char*)this + 4 + idx * 4);
}

// @ 0x009879f0
void* StdDrawable::GetImageForState(unsigned st)
{
    switch (st & 7) {
    case 0:
        if ((st & 8) != 0 && mpImage[4] != 0)
            return mpImage[4];
        break;
    case 1:
        if ((st & 8) != 0 && mpImage[5] != 0)
            return mpImage[5];
        if (mpImage[1] != 0)
            return mpImage[1];
        break;
    case 2:
        if ((st & 8) != 0) {
            if (mpImage[6] != 0)
                return mpImage[6];
            if (mpImage[4] != 0)
                return mpImage[4];
        }
        if (mpImage[2] != 0)
            return mpImage[2];
        break;
    case 3:
        if ((st & 8) != 0) {
            if (mpImage[7] != 0)
                return mpImage[7];
            if (mpImage[4] != 0)
                return mpImage[4];
        }
        if (mpImage[3] != 0)
            return mpImage[3];
        break;
    }
    return mpImage[0];
}

// @ 0x00987b10
StdDrawable::~StdDrawable()
{
    v[0] = (void*)0x1445298;
    v[1] = (void*)0x1445280;
    v[3] = (void*)0x1445240;
    for (int i = 0; i < 8; i++) {
        if (mpImage[i])
            (*(void(__thiscall**)(void*))((char*)*(void**)mpImage[i] + 4))(mpImage[i]);
        mpImage[i] = 0;
    }
    if (mHitMask)
        (*(void(__thiscall**)(void*))((char*)*(void**)mHitMask + 4))(mHitMask);
    v[3] = (void*)0x13eb938;
    v[1] = (void*)0x13eb938;
    v[0] = (void*)0x13eb938;
}

// @ 0x00987bf0
void StdDrawable::draw_with_image(int* sink, void* p3, void* p4)
{
    float edge[8];
    edge[4] = mAreaL;
    edge[5] = mAreaT;
    edge[2] = 1.0f;
    edge[3] = 1.0f;
    edge[6] = 1.0f - mAreaR;
    edge[7] = 1.0f - mAreaB;
    edge[0] = 0.0f;
    edge[1] = 0.0f;
    switch (mScalingType) {
    case 1:
        (*(void(__thiscall**)(int*, void*, void*, float*))((char*)*sink + 0x58))(sink, p3, p4, edge);
        return;
    case 2:
        FUN_0095d000(sink, p3, edge, p4, &edge[4], mScaleX, mScaleY);
        return;
    case 3:
        FUN_0095c5f0(sink, p3, edge, p4, mScaleX, mScaleY, 0, 0);
        return;
    case 4:
        FUN_0095ca40(sink, p3, edge, p4, &edge[4], mScaleX, mScaleY);
        return;
    }
}

// @ 0x00987d40
void StdDrawable::CreateRenderables(void* ctx, float* rect, unsigned* flags)
{
    int* piVar8 = ((RenderContext*)ctx)->Begin2D(0);
    (*(void(__thiscall**)(int*, int))((char*)*piVar8 + 4))(piVar8, -1);
    int image = (int)GetImageForState(*flags);
    if (image != 0) {
        ShadowDesc32 sd;
        sd.m00 = 0;
        sd.m04 = 2;
        sd.m08 = 3;
        sd.f0c = 0.0f;
        sd.f10 = 0.0f;
        sd.f14 = 0.0f;
        sd.f18 = 0.0f;
        sd.m24 = 0;
        sd.SetMode2(2);
        CopyWithQualityAdjustment(&sd, &mShadow, 0);
        float amp  = *(float*)&sd.m20;
        float bias = *(float*)&sd.m1c;
        float rad1 = (float)sqrt((double)(sd.f14 * sd.f14 + sd.f18 * sd.f18)) + 1.0f;
        float cu   = (-sd.f14 + sd.f14) * 0.5f;
        float cv   = (-sd.f18 + sd.f18) * 0.5f;
        float du   = sd.f18 - cv, dv = sd.f14 - cu;
        float rad2 = dv * dv + du * du + 1.0f;
        unsigned baseColor = (unsigned)sd.m24 & 0xffffff;
        for (float u = -sd.f14; u <= sd.f14; u += 1.0f) {
            float v = -sd.f18;
            if (!(v <= sd.f18))
                continue;
            float a = (float)FUN_011e0906((double)(u + sd.f0c));   // hoisted floor: only once the inner loop runs
            for (; v <= sd.f18; v += 1.0f) {
                float b = (float)FUN_011e0906((double)(v + sd.f10));
                if (a != 0.0f || b != 0.0f) {
                    float r[4];
                    r[0] = rect[0] + a;
                    r[1] = rect[1] + b;
                    r[2] = rect[2] + a;
                    r[3] = rect[3] + b;
                    float eu = u - cu, ev = v - cv;
                    float t = (amp / rad1) * (1.0f - (eu * eu + ev * ev) / rad2) + bias;
                    if (t < 0.0f) t = 0.0f;
                    else if (t > 1.0f) t = 1.0f;
                    unsigned alpha = (unsigned)(t * 255.0f);
                    (*(void(__thiscall**)(int*, int))((char*)*piVar8 + 4))(piVar8, (alpha << 24) + baseColor);
                    draw_with_image(piVar8, r, (void*)image);
                }
            }
        }
        (*(void(__thiscall**)(int*, int))((char*)*piVar8 + 4))(piVar8, -1);
        draw_with_image(piVar8, rect, (void*)image);
        return;
    }
    FUN_0095d780(piVar8, rect, (int)flags[2], *flags & 0xf, 3.0f);
    if ((*flags & 0x10) != 0)
        FUN_0095da40(piVar8, rect, -1, mBevelWidth);
}

// @ 0x009880e0
bool StdDrawable::HitTest(float* rect, int* pt, int unused)
{
    (void)unused;
    int local_18 = pt[0];
    int local_14 = pt[1];
    if (!(local_18 > -1 && (float)local_18 < rect[2] - rect[0]))
        return false;
    if (!(local_14 > -1 && (float)local_14 < rect[3] - rect[1]))
        return false;
    if (mHitMask == 0)
        return true;
    int* pi = (int*)(*(int(__thiscall**)(void*))((char*)*(void**)mHitMask + 0x10))(mHitMask);
    unsigned st = (unsigned)mScalingType;
    int iVar2 = pi[0];
    int iVar3 = pi[1];
    switch (st) {
    case 1:
        local_18 = (int)((float)(pt[0] * iVar2) / (rect[2] - rect[0]));
        local_14 = (int)((float)(pt[1] * iVar3) / (rect[3] - rect[1]));
        break;
    case 2:
    case 4: {
        float fStack_4 = (1.0f - mAreaB) * (float)iVar3;
        float fVar13 = mAreaL * (float)iVar2;
        float fVar8  = (1.0f - mAreaR) * (float)iVar2;
        float fVar14 = mAreaT * (float)iVar3;
        float fVar6  = (rect[2] - rect[0]) - ((float)iVar2 - fVar8);
        float fVar12 = (rect[3] - rect[1]) - ((float)iVar3 - fStack_4);
        float fVar9 = fVar13;
        if (fVar6 - fVar13 < 0.0f) {
            fVar6 = (fVar6 + fVar13) * 0.5f;
            fVar9 = fVar6;
        }
        float fVar10 = fVar12 - fVar14;
        if (fVar10 < 0.0f) {
            fVar6 = (fVar6 + fVar9) * 0.5f;
            fVar9 = fVar6;
        }
        local_18 = pt[0];
        float fVar11 = (float)local_18;
        if (fVar9 <= fVar11) {
            if (fVar11 <= fVar6) {
                float fVar7 = fVar8 - fVar13;
                if (fVar6 - fVar9 <= 0.0f || fVar7 <= 0.0f) {
                    local_18 = (int)(fVar8 + fVar13) / 2;
                } else if (st == 2) {
                    local_18 = (int)(((fVar11 - fVar9) * fVar7) / (fVar6 - fVar9) + fVar13);
                } else {
                    local_18 = (int)(fVar11 - fVar9) % (int)fVar7 + (int)fVar13;
                }
            } else {
                local_18 = (int)((fVar11 - fVar6) + fVar8);
            }
        }
        local_14 = pt[1];
        float fVar9b = (float)local_14;
        if (fVar14 <= fVar9b) {
            if (fVar12 < fVar9b) {
                local_14 = (int)((fVar9b - fVar12) + fStack_4);
            } else {
                float fVar6b = fStack_4 - fVar14;
                if (fVar10 <= 0.0f || fVar6b <= 0.0f) {
                    local_14 = (int)(fStack_4 + fVar14) / 2;
                } else if (st == 2) {
                    local_14 = (int)(((fVar9b - fVar14) * fVar6b) / fVar10 + fVar14);
                } else {
                    local_14 = (int)(fVar9b - fVar14) % (int)fVar6b + (int)fVar14;
                }
            }
        }
        break;
    }
    case 3:
        local_18 = pt[0] % iVar2;
        local_14 = pt[1] % iVar3;
        break;
    }
    return (*(unsigned(__thiscall**)(void*, int*))((char*)*(void**)mHitMask + 0x14))(mHitMask, &local_18);
}

// @ 0x009883c0
bool StdDrawable::QueryAttribute(int id, unsigned* out)
{
    if (id != 0x19c46fb)
        return false;
    *out = (mHitMask != 0);
    return true;
}

// @ 0x009883f0
bool StdDrawable::GetNaturalSize(float* out, int state, int unused)
{
    (void)unused;
    void* img = GetImageForState((unsigned)state);
    if (img != 0) {
        out[0] = (float)*(int*)((char*)img + 0x1c);
        out[1] = (float)*(int*)((char*)img + 0x20);
        return true;
    }
    return false;
}

// @ 0x00988420
StdDrawable::StdDrawable()
{
    // volatile stores keep the original's order (vtable stores first, then the members)
    *(volatile int*)&mScalingType = 1;
    *(volatile float*)&mAreaL = 0.33333334f;
    *(volatile float*)&mAreaT = 0.33333334f;
    *(volatile float*)&mAreaR = 0.33333334f;
    *(volatile float*)&mAreaB = 0.33333334f;
    *(volatile float*)&mScaleX = 1.0f;
    *(volatile float*)&mScaleY = 1.0f;
    *(void* volatile*)&mHitMask = 0;
    *(volatile float*)&mBevelWidth = 6.0f;
    mShadow.Init();
    for (int i = 0; i < 8; i++)
        mpImage[i] = 0;
}

// @ 0x01300c50
void init_154fbe4()
{
    *(int*)0x154fbe4 = 8;
    *(int*)0x154fbe8 = 0;
    *(int*)0x154fbec = 0;
    *(int*)0x154fbf0 = 0xef3c000a;
    *(short*)0x154fbf4 = 9;
    *(int*)0x154fbf8 = 0x30;
    *(int*)0x154fbfc = 1;
    *(int*)0x154fc00 = 0;
    *(int*)0x154fc04 = 0;
    *(int*)0x154fc08 = 0xef3c000b;
    *(short*)0x154fc0c = 0x11;
    *(int*)0x154fc10 = 0x44;
    *(int*)0x154fc14 = 1;
    *(int*)0x154fc18 = 0;
    *(void**)0x154fc1c = (void*)0x1440e14;
    *(int*)0x154fc20 = 0xef3c000c;
    *(short*)0x154fc24 = 0x14;
    *(int*)0x154fc28 = 0x34;
    *(int*)0x154fc2c = 1;
    *(int*)0x154fc30 = 0;
    *(void**)0x154fc34 = (void*)0x14452e0;
    *(int*)0x154fc38 = 0xf3c000d;
    *(short*)0x154fc3c = 0x13;
    *(int*)0x154fc40 = 0x4c;
    *(int*)0x154fc44 = 1;
    *(int*)0x154fc48 = 0;
    *(int*)0x154fc4c = 0;
    *(int*)0x154fc50 = 0xf3c000e;
    *(short*)0x154fc54 = 0xb;
    *(int*)0x154fc58 = 0x50;
    *(int*)0x154fc5c = 1;
    *(int*)0x154fc60 = 0;
    *(void**)0x154fc64 = (void*)0x141a7fc;
    *(int*)0x154fc68 = 0x39a69e6;
    *(short*)0x154fc6c = 0x14;
    *(int*)0x154fc70 = 0x54;
    *(int*)0x154fc74 = 1;
}
