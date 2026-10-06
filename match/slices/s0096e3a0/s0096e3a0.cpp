// Slice s0096e3a0 -- EA::UTFWin cDropShadowDescriptor, FadeEffect and
// EASTL vector helpers. Module flags: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE /fp:fast
#include "types.h"
#include <math.h>
#pragma intrinsic(sqrt)

// ---------------------------------------------------------------- globals / externs
extern "C" int  g_sQuality[];                  // 0x154f514
extern "C" void* g_vec1c0[];                   // 0x166b1c0 (eastl vector<bool>)
extern "C" void* g_vec1d4[];                   // 0x166b1d4 (eastl vector<GlyphLayoutInfo>)

extern "C" int  FUN_00951240(int id);                       // 0x951240
extern "C" void* FUN_009512c0(void);                        // 0x9512c0
extern "C" void* FUN_009512d0(int size, int align, const char* name, void* alloc); // 0x9512d0

struct ExtBase {
    void ctor963db0();      // 0x963db0
    void dtor980420();      // 0x980420 Navigator::~Navigator
    void ctor980430();      // 0x980430 ExplicitNavigator ctor
};
extern "C" void FUN_00951330(void* p);   // 0x951330 operator delete (cdecl)
extern "C" void FUN_0096eca0(void);
extern "C" void FUN_00963e50(void);
extern "C" void FUN_00988670(void);
extern "C" void FUN_00983ac0(void);
extern "C" void FUN_00980f30(void);
extern "C" void FUN_00985c30(void);
extern "C" void FUN_0096b310(void);
extern "C" void FUN_00970170(void);
extern "C" void FUN_0097ec60(void);
extern "C" void FUN_009891e0(void);
extern "C" void FUN_00967820(void);
extern "C" void FUN_00992590(void);
extern "C" void FUN_00991f20(void);
extern "C" void FUN_00969aa0(void);
extern "C" void FUN_0098f330(void);
extern "C" void FUN_009878e0(void);
extern "C" void FUN_00963ea0(void);
extern "C" void FUN_00963ef0(void);
extern "C" void FUN_00983b10(void);
extern "C" void FUN_00980f80(void);
extern "C" void FUN_00985c80(void);
extern "C" void FUN_0096b360(void);
extern "C" void FUN_0097d090(void);
extern "C" void FUN_00967870(void);
extern "C" void FUN_0096f220(void);
extern "C" void FUN_0097e780(void);
extern "C" void FUN_0097e7d0(void);
extern "C" void FUN_0096ff00(void);
extern "C" void FUN_0096f040(void);
extern "C" void FUN_0097e480(void);
extern "C" void FUN_009800c0(void);
extern "C" void FUN_009672b0(void);
extern "C" void FUN_00980be0(void);
extern "C" void FUN_009804c0(void);
extern "C" void FUN_009806f0(void);
extern "C" void FUN_0097d9e0(void);

// EASTL helper entry points (relocations masked; signatures are void* based here).
extern "C" void* FUN_00c033a0(void* a, void* b, void* c);        // 0xc033a0 uninitialized_copy-ish
extern "C" void  FUN_00898550(void* a, unsigned n, void* v);     // uninitialized_fill_n
extern "C" void  FUN_00c04920(void* sret, void* a, void* b, void* c, void* d); // uninitialized_copy
extern "C" void  FUN_00898520(void* a, void* b, void* v);        // fill
extern "C" void  FUN_00898f90(void* a, void* b, void* c);        // copy_backward
extern "C" void  FUN_00899420(void* a, void* b);                 // erase
extern "C" void  FUN_006eea80(unsigned n);                       // resize
extern "C" void* FUN_00f473a0(unsigned size, const char* cat, int a, int b, const char* file, int line);
extern "C" void  FUN_00f47380(void* p);                          // operator delete
extern "C" void  FUN_011e0744(void*, void*, unsigned);          // vector<bool>::DoInsertValue

// ---------------------------------------------------------------- cDropShadowDescriptor
struct ShadowDesc {
    unsigned f00;   // +0x00 mode/quality
    unsigned f04;   // +0x04 detail level
    unsigned f08;
    float    f0c;   // +0x0c
    float    f10;   // +0x10
    float    f14;   // +0x14 width
    float    f18;   // +0x18 height
    unsigned f1c;
    unsigned f20;
    unsigned f24;
    void SetMode(int m);   // 0x830150
};

// @ 0x0096e500
void __cdecl cDropShadowDescriptor_SetQuality(int quality, int index)
{
    if (quality <= 0) {
        g_sQuality[index] = 0;
        return;
    }
    if (quality >= 3) {
        g_sQuality[index] = 3;
        return;
    }
    g_sQuality[index] = quality;
}

// @ 0x0096e3a0
void __cdecl CopyWithQualityAdjustment(ShadowDesc* dst, ShadowDesc* src, int quality)
{
    for (int i = 0; i < 10; i++)
        ((unsigned*)dst)[i] = ((unsigned*)src)[i];
    int q = g_sQuality[quality];
    if (q >= 2) {
        if (q != 2)
            return;
        goto two;
    }
    if (q == 1) {
        dst->f04 += 1;
        if (dst->f04 > 9) dst->f04 = 9;
        dst->SetMode((int)dst->f04);
        dst->f00 = 0;
        dst->f14 = 0.0f;
        dst->f18 = 0.0f;
        if (0.0f < src->f14)
            dst->f0c = 1.0f;
        if (src->f18 <= 0.0f)
            return;
        dst->f10 = 1.0f;
        return;
    }
    if (q == (int)0xcfffffff)
        goto two;
    if (q != 0)
        return;
    dst->f00 = 0;
    dst->f14 = 0.0f;
    dst->f0c = 0.0f;
    dst->f10 = 0.0f;
    dst->f18 = 0.0f;
    return;
two:
    dst->f04 += 2;
    if (dst->f04 > 9) dst->f04 = 9;
    dst->SetMode((int)dst->f04);
    dst->f00 = 0;
    dst->f14 = (float)(int)((double)(src->f14 * 0.5f));   // floor
    dst->f18 = (float)(int)((double)(src->f18 * 0.5f));
    if (0.0f < src->f14 && dst->f14 <= 1.0f && dst->f14 != 1.0f)
        dst->f14 = 1.0f;
    if (0.0f < src->f18 && dst->f18 <= 1.0f && dst->f18 != 1.0f)
        dst->f18 = 1.0f;
}

// ---------------------------------------------------------------- 0096e540 / 0096e6d0
struct GlyphLayoutInfo { unsigned char b[0x20]; };

struct GlyphVec {
    unsigned v[3];
    void insert(GlyphLayoutInfo* pos, unsigned n, GlyphLayoutInfo* val);   // 0x96e540
    void resize(unsigned n);                                                // 0x96e6d0
};

// @ 0x0096e540
void GlyphVec::insert(GlyphLayoutInfo* pos, unsigned n, GlyphLayoutInfo* val)
{
    int begin = (int)v[0];
    int end   = (int)v[1];
    unsigned cur = (unsigned)(end - begin) >> 5;
    if (cur < n) {
        unsigned cnt = (unsigned)(end - begin) >> 5;
        unsigned cap = cnt * 2;
        if (cnt == 0) cap = 1;
        unsigned want = cnt + n;
        if (want > cap) cap = want;
        unsigned char* nb;
        if (cap == 0)
            nb = 0;
        else
            nb = (unsigned char*)FUN_00f473a0(cap << 5, "EASTL", 0, 0,
                "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
        unsigned char* mid = (unsigned char*)FUN_00c033a0((void*)v[0], pos, nb);
        FUN_00898550(mid, n, val);
        unsigned char* tail = (unsigned char*)FUN_00c033a0(pos, (void*)v[1], mid + n * 0x20);
        if (v[0] != 0 && *(int*)((char*)v[0] - 4) != 0)
            FUN_00f47380((void*)v[0]);
        v[0] = (unsigned)nb;
        v[1] = (unsigned)tail;
        v[2] = (unsigned)(nb + cap * 0x20);
        return;
    }
    if (n == 0)
        return;
    unsigned before = (unsigned)(end - (int)pos) >> 5;
    GlyphLayoutInfo tmp;
    for (int i = 0; i < 8; i++)
        ((unsigned*)&tmp)[i] = ((unsigned*)val)[i];
    if (before <= n) {
        unsigned extra = n - before;
        FUN_00898550((void*)end, extra, &tmp);
        v[1] = (unsigned)(end + extra * 0x20);
        FUN_00c04920(0, pos, (void*)end, (void*)v[1], pos);
        v[1] = (unsigned)(v[1] + before * 0x20);
        FUN_00898520(pos, (void*)end, &tmp);
        return;
    } else {
        unsigned char* mid = (unsigned char*)(end - n * 0x20);
        FUN_00c04920(0, mid, (void*)end, (void*)end, pos);
        v[1] = (unsigned)(v[1] + n * 0x20);
        FUN_00898f90(pos, mid, (void*)end);
        FUN_00898520(pos, (void*)(n * 0x20 + (unsigned)pos), &tmp);
        return;
    }
}

// @ 0x0096e6d0
void GlyphVec::resize(unsigned n)
{
    unsigned cnt = (unsigned)((int)v[1] - (int)v[0]) >> 5;
    if (cnt < n) {
        GlyphLayoutInfo tmp;
        for (int i = 0; i < 8; i++) ((unsigned*)&tmp)[i] = 0;
        insert((GlyphLayoutInfo*)v[1], n - cnt, &tmp);
        return;
    }
    FUN_00899420((void*)((unsigned)v[0] + n * 0x20), (void*)v[1]);
}

// ---------------------------------------------------------------- 0096e740 DrawTextGlyphs
struct DropShadowText {
    void draw(int* sink, void* a, void* glyphs, unsigned count,
              unsigned color, short flag, unsigned char mode);   // 0x96e740
};

// @ 0x0096e740
void DropShadowText::draw(int* sink, void* a, void* glyphs, unsigned count,
                          unsigned color, short flag, unsigned char mode)
{
    FUN_006eea80(count);
    ((GlyphVec*)g_vec1d4)->resize(count);
    FUN_011e0744(g_vec1c0, a, count * 2);
    {
        struct G32 { unsigned d[8]; };
        G32* dst = (G32*)g_vec1d4[0];
        G32* sp = (G32*)glyphs;
        G32* send = sp + count;
        for (; sp != send; ++sp, ++dst)
            *dst = *sp;
    }
    ShadowDesc local;
    local.f00 = 0; local.f04 = 2; local.f08 = 3;
    local.f0c = 0.0f; local.f10 = 0.0f; local.f14 = 0.0f; local.f18 = 0.0f;
    local.f24 = 0;
    local.SetMode(2);
    CopyWithQualityAdjustment(&local, (ShadowDesc*)this, 0);
    float amp   = *(float*)&local.f20;
    float bias  = *(float*)&local.f1c;
    float rad1  = (float)sqrt((double)(local.f14 * local.f14 + local.f18 * local.f18)) + 1.0f;
    float cu    = (-local.f14 + local.f14) * 0.5f;     // v-range centre
    float cv    = (-local.f18 + local.f18) * 0.5f;     // u-range centre
    float du    = local.f18 - cv, dv = local.f14 - cu;
    float rad2  = dv * dv + du * du + 1.0f;
    unsigned baseColor = local.f24 & 0xffffff;
    float lastP = 0.0f, lastQ = 0.0f;
    for (float u = -local.f14; u <= local.f14; u += 1.0f) {
        float p = u + local.f0c;
        for (float v = -local.f18; v <= local.f18; v += 1.0f) {
            float q = v + local.f10;
            if (p != 0.0f || q != 0.0f) {
                float dp = p - lastP;
                float dq = q - lastQ;
                lastP = p;
                lastQ = q;
                for (unsigned j = 0; j < count; j++) {
                    unsigned char* g = (unsigned char*)g_vec1d4[0] + j * 0x20;
                    *(float*)(g + 4) += dp;
                    *(float*)(g + 8) += dq;
                    *(float*)(g + 0x10) += dp;
                    *(float*)(g + 0x14) += dq;
                    *(float*)(g + 0x18) += dp;
                    *(float*)(g + 0x1c) += dq;
                }
                float ev = v - cv, eu = u - cu;
                float t = (amp / rad1) * (1.0f - (eu * eu + ev * ev) / rad2) + bias;
                if (t < 0.0f) t = 0.0f;
                else if (t > 1.0f) t = 1.0f;
                int alpha = (int)(t * 255.0f);
                (*(void(__thiscall**)(int*, int))((char*)*(void**)sink + 4))(sink, (alpha << 24) + baseColor);
                (*(void(__thiscall**)(int*, void*, void*, unsigned))((char*)*(void**)sink + 0x30))(sink, g_vec1c0, g_vec1d4[0], count);
            }
        }
    }
    (*(void(__thiscall**)(int*, unsigned))((char*)*(void**)sink + 4))(sink, color);
    if (mode != 0) {
        unsigned c = (flag == -1) ? 0xff00ff00 : 0xffff0000;
        (*(void(__thiscall**)(int*, unsigned))((char*)*(void**)sink + 4))(sink, c);
    }
    (*(void(__thiscall**)(int*, void*, void*, unsigned))((char*)*(void**)sink + 0x30))(sink, a, glyphs, count);
}

// ---------------------------------------------------------------- 0096ecf0
struct Obj96 {
    char pad[0x1c];
    int  f1c;
    bool m(void* sink, void* arg2);   // 0x96ecf0
};

// @ 0x0096ecf0
bool Obj96::m(void* sink, void* arg2)
{
    if (f1c != 0) {
        (*(void(__thiscall**)(void*, void*, int))((char*)*(void**)sink + 0x4c))(sink, arg2, f1c);
        return true;
    }
    return false;
}

// ---------------------------------------------------------------- 0096ed70
// @ 0x0096ed70
bool __cdecl FUN_0096ed70(void* p1, char* p2, char* p3)
{
    unsigned* src = *(unsigned**)(p2 + 4);
    unsigned* dst = (unsigned*)(*(int*)((char*)p1 + 4) + *(int*)(p3 + 0x10));
    for (unsigned n = 0; n < *(unsigned*)(p3 + 0x14); n++) {
        unsigned val = 0;
        void* o = (void*)*src;
        if (o) val = (*(unsigned(__thiscall**)(void*, int))((char*)*(void**)o + 0xc))(o, 0xeeee8218);
        *dst = val;
        dst++;
        src++;
    }
    return true;
}

// ---------------------------------------------------------------- 0096eee0 scalar deleting dtor
struct ExplicitNavigator {
    char pad[0x1c];
    void* f1c;
    void* ScalarDtor(unsigned flags);   // 0x96eee0
};

// @ 0x0096eee0
void* ExplicitNavigator::ScalarDtor(unsigned flags)
{
    *(void**)((char*)this + 0x18) = (void*)0x13eb938;
    ((ExtBase*)this)->dtor980420();
    if (flags & 1)
        FUN_00951330(this);
    return this;
}

// ---------------------------------------------------------------- 0096ef10
// @ 0x0096ef10
void* __stdcall BasicFactory_ExplicitNavigator_CreateInstance(int unused, int alloc)
{
    (void)unused;
    if (alloc == 0)
        alloc = (int)FUN_009512c0();
    void* p = FUN_009512d0(0x20, 4, "UTFWin/EA::UTFWinControls::ExplicitNavigator", (void*)alloc);
    if (p) {
        ((ExtBase*)p)->ctor980430();
        *(void* volatile*)((char*)p + 0x18) = (void*)0x13fa72c;
        *(void**)((char*)p + 0x00) = (void*)0x14421c8;
        *(void**)((char*)p + 0x04) = (void*)0x14421ac;
        *(void**)((char*)p + 0x0c) = (void*)0x1442188;
        *(void**)((char*)p + 0x18) = (void*)0x1442170;
        *(void**)((char*)p + 0x1c) = 0;
        return p;
    }
    return 0;
}

// ---------------------------------------------------------------- 0096ef80
// @ 0x0096ef80
void FUN_0096ef80(void)
{
    FUN_00963e50();
    FUN_00988670();
    FUN_00983ac0();
    FUN_00980f30();
    FUN_00985c30();
    FUN_0096b310();
    FUN_00970170();
    FUN_0097ec60();
    FUN_009891e0();
    FUN_00967820();
    FUN_00992590();
    FUN_00991f20();
    FUN_00969aa0();
    FUN_0098f330();
    FUN_009878e0();
    FUN_00963ea0();
    FUN_00963ef0();
    FUN_00983b10();
    FUN_00980f80();
    FUN_00985c80();
    FUN_0096b360();
    FUN_0097d090();
    FUN_00967870();
    FUN_0096f220();
    FUN_0097e780();
    FUN_0097e7d0();
    FUN_0096ff00();
    FUN_0096f040();
    FUN_0097e480();
    FUN_009800c0();
    FUN_009672b0();
    FUN_00980be0();
    FUN_009804c0();
    FUN_009806f0();
    FUN_0096eca0();
    FUN_0097d9e0();
}

// ---------------------------------------------------------------- 0096f060
struct FadeEffect {
    void* v0; void* v1; void* v2[2];
    FadeEffect();   // 0x96f060
};

// @ 0x0096f060
FadeEffect::FadeEffect()
{
    ((ExtBase*)this)->ctor963db0();
    *(void**)((char*)this + 0x00) = (void*)0x14422f8;
    *(void**)((char*)this + 0x04) = (void*)0x14422e0;
    *(void**)((char*)this + 0x0c) = (void*)0x14422a4;
}

// ---------------------------------------------------------------- 0096f080
// @ 0x0096f080
void __cdecl BiStateEffect_func84h(int* self, float f)
{
    f = (1.0f - f) * 255.0f;
    int a = (int)f;
    a <<= 24;
    a += 0xffffff;
    (*(void(__thiscall**)(int*, int))((char*)*self + 0x5c))(self, a);
}

// ---------------------------------------------------------------- 0096f120
// @ 0x0096f120
void* __stdcall BasicFactory_FadeEffect_CreateInstance(int unused, int alloc)
{
    (void)unused;
    if (alloc == 0)
        alloc = (int)FUN_009512c0();
    void* p = FUN_009512d0(0x60, 8, "UTFWin/EA::UTFWinControls::FadeEffect", (void*)alloc);
    if (p) {
        ((ExtBase*)p)->ctor963db0();
        *(void**)((char*)p + 0x00) = (void*)0x14422f8;
        *(void**)((char*)p + 0x04) = (void*)0x14422e0;
        *(void**)((char*)p + 0x0c) = (void*)0x14422a4;
        return p;
    }
    return 0;
}

// ---------------------------------------------------------------- 0096f1b0 / 0096f1f0 / 0096f240 / 0096f280
struct Ctx96 {
    char pad[0x50];
    void a(float* p, float f);       // 0x96f1b0
    void b(float* p);                // 0x96f1f0
    int  q(int iid);                 // 0x96f240
    int  s(unsigned flags);          // 0x96f280
};

// @ 0x0096f1b0
void Ctx96::a(float* p, float f)
{
    (*(void(__thiscall**)(void*, float, float, float, float, float))((char*)*(void**)this + 0x1c))(
        this, p[0], p[1], p[2], p[3], f);
}

// @ 0x0096f1f0
void Ctx96::b(float* p)
{
    (*(void(__thiscall**)(void*, float, float, float, float))((char*)*(void**)this + 0x38))(
        this, p[0], p[1], p[2], p[3]);
}

// @ 0x0096f240
int Ctx96::q(int iid)
{
    if (iid == 0x30d54ac)
        return (int)this;
    if (iid != (int)0xeec58382)
        return FUN_00951240(iid);
    if (this)
        return (int)this + 4;
    return 0;
}

// @ 0x0096f280
int Ctx96::s(unsigned flags)
{
    char* self = (char*)this;
    switch (flags & 7) {
    case 0:
        if ((flags & 8) != 0 && *(int*)(self + 0x2c) != 0)
            return (int)(self + 0x2c);
        break;
    case 1:
        if ((flags & 8) != 0 && *(int*)(self + 0x34) != 0)
            return (int)(self + 0x34);
        if (*(int*)(self + 0x14) != 0)
            return (int)(self + 0x14);
        break;
    case 2:
        if ((flags & 8) != 0) {
            if (*(int*)(self + 0x3c) != 0)
                return (int)(self + 0x3c);
            if (*(int*)(self + 0x2c) != 0)
                return (int)(self + 0x2c);
        }
        if (*(int*)(self + 0x1c) != 0)
            return (int)(self + 0x1c);
        break;
    case 3:
        if ((flags & 8) != 0) {
            if (*(int*)(self + 0x44) != 0)
                return (int)(self + 0x44);
            if (*(int*)(self + 0x2c) != 0)
                return (int)(self + 0x2c);
        }
        if (*(int*)(self + 0x24) != 0)
            return (int)(self + 0x24);
        break;
    }
    return (int)(self + 0x0c);
}

// ---------------------------------------------------------------- 0096f320
// @ 0x0096f320
bool __cdecl FUN_0096f320(void* p1, char* p2, char* p3)
{
    unsigned* src = *(unsigned**)(p2 + 4);
    unsigned* dst = (unsigned*)(*(int*)((char*)p1 + 4) + *(int*)(p3 + 0x10));
    for (unsigned n = 0; n < *(unsigned*)(p3 + 0x14); n++) {
        unsigned val = *src;
        *dst = val;
        dst++;
        src++;
    }
    return true;
}
