// Slice s009873a0 -- EA::UTFWinControls WinSpinner / StdDrawable.
// Module flags: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE /fp:fast
#include "types.h"
#include <math.h>
#pragma intrinsic(sqrt)

// ---------------------------------------------------------------- externs
extern "C" void* FUN_009512c0(void);                        // 0x9512c0
extern "C" void* FUN_009512d0(int size, int align, const char* name, void* alloc); // 0x9512d0
extern "C" void  FUN_00951330(void* p);                      // 0x951330 operator delete
extern "C" void* FUN_011e073e(void* dst, int zero, unsigned size); // 0x11e073e operator_new[]
extern "C" void  FUN_00f47380(void* p);                      // 0xf47380 operator delete
extern "C" void  FUN_0095c5f0(void*, void*, void*, void*, float, float, int, int); // 0x95c5f0
extern "C" void  FUN_0095ca40(void*, void*, void*, void*, float*, float, float);   // 0x95ca40
extern "C" void  FUN_0095d000(void*, void*, void*, void*, float*, float, float);   // 0x95d000 BltEdgeStretch
extern "C" void  FUN_0095d780(void*, void*, int, int, float);                      // 0x95d780 DrawStdButton
extern "C" void  FUN_0095da40(void*, void*, int, float);                           // 0x95da40
extern "C" double FUN_011e0906(double);                       // floor
extern "C" int   FUN_0095bc10(void* ctx, int);               // Begin2D
struct ShadowDesc32;
extern "C" int*  FUN_00c2e4e0(void* self);                   // ILayoutElement::SetSerializer-ish
void __cdecl CopyWithQualityAdjustment(ShadowDesc32* dst, ShadowDesc32* src, int quality); // 0x96e3a0

struct WinBase { void ctor962a10(); void dtor962740(); };
struct Sw      { void ctor(unsigned a, unsigned b); void SetUnits(int u); };
struct IWinSub { void SetFlag(unsigned flag, unsigned char on); };

// ---------------------------------------------------------------- shadow descriptor
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

// the descriptor's default constructor, inlined into StdDrawable's ctor
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

// ---------------------------------------------------------------- UI::StdDrawable
// stand-ins for the inlined base-class constructors (vtable pointer stores)
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

// @ 0x00987900
void StdDrawable::FUN_00987900()
{
    SetSerializerX();
    ((ShadowDesc32*)((char*)this + 0x54))->SetMode1(*(int*)((char*)this + 0x54));
    ((ShadowDesc32*)((char*)this + 0x54))->SetMode2(*(int*)((char*)this + 0x58));
}

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
    int* piVar8 = (int*)FUN_0095bc10(ctx, 0);
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
            for (float v = -sd.f18; v <= sd.f18; v += 1.0f) {
                float a = (float)FUN_011e0906((double)(u + sd.f0c));
                float b = (float)FUN_011e0906((double)(v + sd.f10));
                if (a != 0.0f || b != 0.0f) {
                    float r[4];
                    r[0] = rect[0] + a;
                    r[1] = rect[1] + b;
                    r[2] = rect[2] + a;
                    r[3] = rect[3] + b;
                    float eu = u - b, ev = v - a;
                    float t = (amp / rad1) * (1.0f - (eu * eu + ev * ev) / rad2) + bias;
                    if (t < 0.0f) t = 0.0f;
                    else if (t > 1.0f) t = 1.0f;
                    int alpha = (int)(t * 255.0f);
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

// ---------------------------------------------------------------- BasicFactory_SpinnerDrawable
// @ 0x00987530
void* __stdcall BasicFactory_SpinnerDrawable_CreateInstance(int unused, int alloc)
{
    (void)unused;
    if (alloc == 0)
        alloc = (int)FUN_009512c0();
    void* p = FUN_009512d0(0x1c, 4, "UTFWin/EA::UTFWinControls::SpinnerDrawable", (void*)alloc);
    if (p) {
        *(void* volatile*)((char*)p + 4) = (void*)0x13fa72c;
        *(void**)((char*)p + 8) = 0;
        *(void* volatile*)((char*)p + 0xc) = (void*)0x13fa72c;
        *(void**)((char*)p + 0x00) = (void*)0x1445128;
        *(void**)((char*)p + 0x04) = (void*)0x1445110;
        *(void**)((char*)p + 0x0c) = (void*)0x14450f8;
        *(void**)((char*)p + 0x10) = 0;
        *(void**)((char*)p + 0x14) = 0;
        *(void**)((char*)p + 0x18) = 0;
        return p;
    }
    return 0;
}

// ---------------------------------------------------------------- WinSpinner
struct WinSpinner {
    char   pad_00[0x20c];
    void*  vtbl20c;    // +0x20c
    char   pad_210[0x248 - 0x210];
    void*  mText;      // +0x248
    char   pad_24c[0x4c0];

    void* Ctor();
    void* ScalarDtor(unsigned flags);
    void  Refresh();
};

// @ 0x009873a0
void* WinSpinner::Ctor()
{
    WinSpinner* self = this;
    ((WinBase*)self)->ctor962a10();
    *(void**)((char*)self + 0x20c) = (void*)0x1444e90;
    unsigned char ff = 0xff;
    Sw*     sw  = (Sw*)((char*)self + 0x230);
    IWinSub* sub = (IWinSub*)((char*)self + 4);
    *(void**)((char*)self) = (void*)0x1445060;
    *(void**)((char*)self + 4) = (void*)0x1444f40;
    *(void**)((char*)self + 0x20c) = (void*)0x1444ee8;
    *(void**)((char*)self + 0x210) = 0;
    *(void**)((char*)self + 0x214) = 0;
    *(void**)((char*)self + 0x218) = (void*)0x100;
    *(void**)((char*)self + 0x21c) = (void*)1;
    *(void**)((char*)self + 0x220) = (void*)0x64;
    *((unsigned char*)self + 0x224) = ff;
    *((unsigned char*)self + 0x225) = ff;
    *(void**)((char*)self + 0x228) = (void*)2;
    *((unsigned char*)self + 0x22c) = 1;
    sw->ctor(0, 0);
    *(void**)((char*)self + 0x248) = 0;
    FUN_011e073e((char*)self + 0x24c, 0, 0x30);
    sw->SetUnits(4);
    sub->SetFlag(8, 1);
    return self;
}

// @ 0x00987470
void* WinSpinner::ScalarDtor(unsigned flags)
{
    WinSpinner* self = this;
    *(void**)self = (void*)0x1445060;
    *(void**)((char*)self + 4) = (void*)0x1444f40;
    *(void**)((char*)self + 0x20c) = (void*)0x1444ee8;
    void* p = self->mText;
    if (p)
        (*(void(__thiscall**)(void*))((char*)*(void**)p + 4))(p);
    *(void**)((char*)self + 0x20c) = (void*)0x13eb938;
    ((WinBase*)self)->dtor962740();
    if (flags & 1)
        FUN_00951330(self);
    return self;
}

extern "C" wchar_t g_emptyW[2];                                  // 0x1667bac (eastl empty string rep)
extern "C" void __cdecl WStr_Format(void* str, const wchar_t* fmt, ...) throw();   // 0x41e050 eastl::basic_string<wchar_t>::sprintf
extern const wchar_t g_spinnerFmt[];                             // 0x13f01bc

struct WStrTmp {
    wchar_t* b;
    wchar_t* e;
    wchar_t* cap;
    WStrTmp() : b(g_emptyW), e(g_emptyW), cap(g_emptyW + 1) {}
    void Free() {
        if ((((unsigned)cap - (unsigned)b) & 0xfffffffe) > 2 && b)
            FUN_00f47380(b);
    }
};

// @ 0x00987590
void WinSpinner::Refresh()
{
    char* self = (char*)this;
    if (self[0x22c] == 0)
        return;
    if (*(int*)(self + 0x1e0) == 0)
        return;
    self[0x22c] = 0;
    float* pc = (float*)(self + 0x250);        // three component rects (l,t,r,b) at 0x24c, step 0x10
    for (unsigned i = 0; i < 3; i++) {
        float out[2];                           // [0] width, [1] height
        char* mgr = *(char**)(self + 0x1e0);
        bool ok = (*(bool(__thiscall**)(char*, float*, int, unsigned))((char*)*(void**)mgr + 0x18))(
            mgr, out, (*(int*)(self + 0x228) == 2) ? 0x80 : 0, i);
        if (!ok) {
            void* sub = self + 4;
            float* r = (*(float*(__thiscall**)(void*))((char*)*(void**)sub + 0x38))(sub);
            if (*(int*)(self + 0x228) == 1) {
                float a = (r[2] - r[0]) * 0.5f;
                float b = r[3] - r[1];
                const float* m = (b > a) ? &a : &b;
                out[0] = *m;
                out[1] = r[3] - r[1];
            } else {
                out[0] = r[2] - r[0];
                float a = (r[3] - r[1]) * 0.5f;
                float b = r[2] - r[0];
                const float* m = (b > a) ? &a : &b;
                out[1] = *m;
            }
        }
        pc[-1] = 0.0f;
        pc[0] = 0.0f;
        pc[1] = out[0];
        pc[2] = out[1];
        pc += 4;
    }
    float* c1 = (float*)(self + 0x25c);
    float* c2 = (float*)(self + 0x26c);
    float w1 = c1[2] - c1[0];
    float h1 = c1[3] - c1[1];
    float w2 = c2[2] - c2[0];
    float h2 = c2[3] - c2[1];
    float* win = (float*)(self + 0x88);
    if (*(int*)(self + 0x228) == 1) {
        c2[0] = 0.0f;
        c2[2] = w2;
        c2[1] = (win[3] - win[1] - h2) * 0.5f;
        c2[3] = c2[1] + h2;
        c1[0] = (win[2] - win[0]) - w1;
        c1[2] = c1[0] + w1;
        c1[1] = (win[3] - win[1] - h1) * 0.5f;
        c1[3] = c1[1] + h1;
    } else {
        c1[0] = ((win[2] - win[0]) - w1) * 0.5f;
        c1[2] = c1[0] + w1;
        c1[1] = 0.0f;
        c1[3] = h1;
        c2[0] = ((win[2] - win[0]) - w2) * 0.5f;
        c2[2] = c2[0] + w2;
        c2[1] = (win[3] - win[1]) - h2;
        c2[3] = c2[1] + h2;
    }
    if (*(void**)(self + 0x248)) {
        WStrTmp str;
        WStr_Format(&str, g_spinnerFmt, *(int*)(self + 0x210));
        void* t1 = *(void**)(self + 0x248);
        (*(void(__thiscall**)(void*, wchar_t*))((char*)*(void**)t1 + 0x80))(t1, str.b);
        void* t2 = *(void**)(self + 0x248);
        (*(void(__thiscall**)(void*))((char*)*(void**)t2 + 0x90))(t2);
        str.Free();
    }
    void* sub = self + 4;
    (*(void(__thiscall**)(void*))((char*)*(void**)sub + 0x90))(sub);
}
