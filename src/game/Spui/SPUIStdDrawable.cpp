// src/game/Spui/SPUIStdDrawable.cpp -- migrated from slice(s) s012f64e0, s00830c00, s0082f9a0 by tools/migrate/rewrite.py
// Object file: Spui/SPUIStdDrawable.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <intrin.h>

// unnamed retail callees and globals (address in the comment)
extern char g_vtblImgInfo;      // 0x141a760 (primary)
extern char g_vtblImgInfoSec;   // 0x141a750
extern char g_vtblDrawable;     // 0x141a7d8
extern char g_vtblDrawableSec;  // 0x141a7c0
extern char g_vtblDrawableThr;  // 0x141a780
extern char g_vtblEditorResource; // 0x13eb938
extern char g_vtblContentValidation;   // 0x13ec458
extern "C" void __cdecl FUN_008304a0(void *, void *);                      // 0x8304a0
extern "C" double __cdecl TypesetterValidate(double);                      // 0x11e0906

// ---- items of slice s0082f9a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct ShadowDesc {
    uint32_t mode1;   // +0x00
    uint32_t mode2;   // +0x04
    uint32_t f8;      // +0x08
    uint32_t fc;      // +0x0c
    uint32_t f10;     // +0x10
    float    s14;     // +0x14
    float    s18;     // +0x18
    float    s1c;     // +0x1c
    float    s20;     // +0x20
    uint32_t f24;     // +0x24

    void SetMode1(int mode);                 // 0x00830280
    void SetMode2(int mode);                 // 0x00830150
};
extern ShadowDesc g_shadowDefaults;   // 0x1547690
struct DrawableTail {
    char   pad0[0x38];
    float  f38;   // +0x38
    float  f3c;   // +0x3c
    void SetPoint(const float *p);   // 0x00830af0
};
struct StdBase { void ctor(); void dtor(); };
// External view of ShadowDesc::SetMode2 (the original caller's TU only saw a
// declaration, so the call must stay opaque to the optimizer).
struct ShadowDescExt {
    uint32_t mode1, mode2, f8, fc, f10;
    float    s14, s18, s1c, s20;
    uint32_t f24;
    void SetMode2(int mode);   // 0x00830150
};
struct FactoryRegistry {
    void *vptr;   // +0
    int *CreateInstance(int **out, int a1, int a2, int a3);   // 0x008304c0
};
struct ImageInfo {
    void    *vptr0;   // +0x00
    void    *vptr4;   // +0x04
    uint32_t r8;      // +0x08
    uint32_t fc;      // +0x0c
    void    *img10;   // +0x10
    uint32_t c14, c18, c1c, c20, c24;   // +0x14..+0x24
    float    s28, s2c, s30, s34, s38, s3c, s40, s44;   // +0x28..+0x44
    ShadowDesc stroke;   // +0x48
    ShadowDesc halo;     // +0x70
    ImageInfo *Construct();   // 0x00830810
};
struct SmallSet {
    char  pad0[4];
    void  Do(int param_2);   // 0x00830910
};
struct Drawable {
    char data[0x7c];
    ImageInfo mImageInfo;          // +0x7c
    void *mImageInfos[8];          // +0x114
    uint8_t mbHasUserDefaults;     // +0x134
    char  pad135[3];
    uint32_t mDrawParams[4];       // +0x138
    float  mDrawArea[4];           // +0x148
    float  mOODrawAreaSize[2];     // +0x158
    Drawable *Construct();         // 0x00830950
    void Destroy();                // 0x00830b30
};
// ---- items of slice s0082f9a0 end

// unnamed retail callees and globals that name local stubs (address in the comment)

// ---- items of slice s00830c00 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void *__cdecl FUN_00920090(void);                  // 0x920090 (returns registry singleton)
extern "C" void __cdecl MultiHeap_delete(void *);              // 0x951330
struct ShadowDesc_s0083_0c00 { char pad[0x28]; };
void FillDefaults(ShadowDesc_s0083_0c00 *dst, const ShadowDesc_s0083_0c00 *src);   // 0x00830380
struct Drawable_s0083_0c00 {
    void    *vptr0;      // +0x00
    void    *vptr4;      // +0x04
    void    *f8;         // +0x08
    void    *vptrC;      // +0x0c
    void    *f10;        // +0x10
    char     pad14[0x7c - 0x14];
    char     mInfo[0x98];    // +0x7c mDefaultImageInfo
    void    *mImageInfos[8]; // +0x114
    uint8_t  mbHasUserDefaults;  // +0x134

    __declspec(noinline) void *GetImageInfo(int index);   // 0x00830c00
    void  SetImageColor(int index, int color);        // 0x00831170
    void  SetField18At(int index, int v);             // 0x008311f0
    void  SetField20At(int index, int v);             // 0x00831270
    void  SetPair38At(int index, float *v);           // 0x008312f0
    void  SetPair40At(int index, float *v);           // 0x00831380
    void *PickImageInfo(int flags, void *dst);        // 0x00831410
    bool  GetNaturalSize(float *out, int index);      // 0x00831530
    bool  HitTest(int a, int b);                      // 0x008315c0
    void  EnsureImageInfo0();                         // 0x00831650
    void  SetImageIcon(int index, void *img);         // 0x00831760
};
struct ImageInfo2 {
    void    *vptr0;   // +0x00
    void    *vptr4;   // +0x04
    uint32_t r8;      // +0x08
    void    *mpImage; // +0x0c
    void    *mpIcon;  // +0x10
    char     pad14[0x84];
    void *ScalarDtor(unsigned flags); // 0x00831030
    void  CopyFrom(const ImageInfo2 *src); // 0x008310a0
};
struct DSub {
    char pad[0xc];
    int  GetFieldC(int index);    // 0x00830c60
    int  GetField14(int index);   // 0x00830c80
    void GetPair28(float *out, int index);  // 0x00830c90
    void GetPair30(float *out, int index);  // 0x00830cc0
    int  GetField10(int index);   // 0x00830cf0
    int  GetField18(int index);   // 0x00830d10
    int  GetField20(int index);   // 0x00830d20
    void GetPair38(float *out, int index);  // 0x00830d30
    void GetPair40(float *out, int index);  // 0x00830d60
    void SetImage(int index, void *img);    // 0x008316b0
};
static __forceinline void *MakeInfoAt(Drawable_s0083_0c00 *self, unsigned index, void *slot)
{
    int *p = ((FactoryRegistry *)FUN_00920090())->CreateInstance((int **)slot, 0x540037e, 0, 0);
    ((ImageInfo2 *)p)->CopyFrom((const ImageInfo2 *)((char *)self + 0x7c));
    return p;
}
// ---- items of slice s00830c00 end

// ---- items of slice s012f64e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct TypeRegEntry {
    void* f0;       // +0x00
    int   f1;       // +0x04
    short f2;       // +0x08
    short f3;       // +0x0a
    int   f4;       // +0x0c
    int   f5;       // +0x10
    int   f6;       // +0x14
};
// ---- items of slice s012f64e0 end

// ---- items of slice s0082f9a0_b begin (TODO(rewrite): local stubs, replace by canonical classes)
struct ImageInfoFull {
    char        pad0[0x48];
    ShadowDesc  mShadowStroke;   // +0x48
    ShadowDesc  mShadowHalo;     // +0x70
};
// ---- items of slice s0082f9a0_b end

// @ 0x00830380
void FillDefaults(ShadowDesc *dst, const ShadowDesc *src)
{
    if (dst->f24 == g_shadowDefaults.f24) dst->f24 = src->f24;
    if (dst->mode1 == g_shadowDefaults.mode1) dst->mode1 = src->mode1;
    if (dst->mode2 == g_shadowDefaults.mode2) dst->mode2 = src->mode2;
    if (dst->f8 == g_shadowDefaults.f8) dst->f8 = src->f8;
    if (dst->s14 == g_shadowDefaults.s14) dst->s14 = src->s14;
    if (dst->s18 == g_shadowDefaults.s18) dst->s18 = src->s18;
    if (dst->s1c == g_shadowDefaults.s1c) dst->s1c = src->s1c;
    if (dst->s20 == g_shadowDefaults.s20) dst->s20 = src->s20;
}

// @ 0x008304c0
int *FactoryRegistry::CreateInstance(int **out, int a1, int a2, int a3)
{
    int *p = (int *)((int (__thiscall *)(void *, int, int, int, int))(*(void ***)this)[0x20 / 4])
                        (this, a1, 0x5400186, a2, a3);
    int *old = *out;
    if (p == old)
        return old;
    if (p)
        ((void (__thiscall *)(void *))(*(void ***)p)[0])(p);
    *out = p;
    if (old) {
        ((void (__thiscall *)(void *))(*(void ***)old)[1])(old);
        return *out;
    }
    return p;
}

// @ 0x008306a0
void FUN_008306a0(ImageInfoFull *p)
{
    p->mShadowHalo.SetMode1(p->mShadowHalo.mode1);
    p->mShadowHalo.SetMode2(p->mShadowHalo.mode2);
    p->mShadowStroke.SetMode1(p->mShadowStroke.mode1);
    p->mShadowStroke.SetMode2(p->mShadowStroke.mode2);
}

// @ 0x008306e0
float *FUN_008306e0(float *dst, float *a, float *b, float *c)
{
    float f1 = a[0]; dst[0] = f1;
    float f2 = a[1]; dst[1] = f2;
    float f3 = a[2]; dst[2] = f3;
    float f4 = a[3]; dst[3] = f4;
    float d6 = (float)TypesetterValidate((double)(((b[0] - 1.0f) * (f3 - f1)) * 0.5f));
    float d7 = (float)TypesetterValidate((double)(((b[1] - 1.0f) * (f4 - f2)) * 0.5f));
    float d8 = (float)TypesetterValidate((double)c[1]);
    float d9 = (float)TypesetterValidate((double)c[0]);
    dst[0] = (dst[0] - d6) + d9;
    dst[1] = (dst[1] - d7) + d8;
    dst[2] = (dst[2] + d9) + d6;
    dst[3] = (d8 + dst[3]) + d7;
    return dst;
}

// @ 0x00830810
ImageInfo *ImageInfo::Construct()
{
    vptr4 = &g_vtblContentValidation;
    r8 = 0;
    vptr0 = &g_vtblImgInfo;
    vptr4 = &g_vtblImgInfoSec;
    fc = 0;
    img10 = 0;
    c14 = 0xffffffff;
    c18 = 0xffffffff;
    c1c = 1;
    c20 = 1;
    c24 = 1;
    s28 = 1.0f; s2c = 1.0f; s30 = 0.0f; s34 = 0.0f;
    s38 = 1.0f; s3c = 1.0f; s40 = 0.0f; s44 = 0.0f;

    stroke.mode1 = 0; stroke.mode2 = 2; stroke.f8 = 3; stroke.fc = 0; stroke.f10 = 0;
    stroke.s14 = 0; stroke.s18 = 0; stroke.s1c = 0; stroke.s20 = 0; stroke.f24 = 0;
    ((ShadowDescExt *)&stroke)->SetMode2(2);

    halo.mode1 = 0; halo.mode2 = 2; halo.f8 = 3; halo.fc = 0; halo.f10 = 0;
    halo.s14 = 0; halo.s18 = 0; halo.s1c = 0; halo.s20 = 0; halo.f24 = 0;
    ((ShadowDescExt *)&halo)->SetMode2(2);
    return this;
}

// @ 0x00830910
void SmallSet::Do(int param_2)
{
    FUN_008304a0((void *)param_2, (char *)this - 4);
    int v = ((int (__thiscall *)(void *))(*(void ***)this)[0x14 / 4])(this);
    *(int *)(param_2 + 0xc) = v;
}

// @ 0x00830950
Drawable *Drawable::Construct()
{
    void *src = (char *)this + 0x7c;
    ((StdBase *)this)->ctor();
    *(void **)this = &g_vtblDrawable;
    *(void **)((char *)this + 4) = &g_vtblDrawableSec;
    *(void **)((char *)this + 0xc) = &g_vtblDrawableThr;
    ((ImageInfo *)src)->Construct();

    void **q = mImageInfos;
    for (int i = 0; i < 8; ++i)
        q[i] = 0;
    mbHasUserDefaults = 0;
    mDrawParams[0] = 0;
    mDrawParams[1] = 0;
    mDrawParams[2] = 0;
    mDrawParams[3] = 0xffffffff;
    mDrawArea[0] = 0.0f;
    mDrawArea[1] = 0.0f;
    mDrawArea[2] = 0.0f;
    mDrawArea[3] = 0.0f;
    mOODrawAreaSize[0] = 1.0f;
    mOODrawAreaSize[1] = 1.0f;

    ((void (__thiscall *)(void *))(*(void ***)src)[0])(src);
    for (int i = 0; i < 8; ++i) {
        void *old = q[i];
        if (src != old) {
            if (src)
                ((void (__thiscall *)(void *))(*(void ***)src)[0])(src);
            q[i] = src;
            if (old)
                ((void (__thiscall *)(void *))(*(void ***)old)[1])(old);
        }
    }
    return this;
}

// @ 0x00830af0
void DrawableTail::SetPoint(const float *p)
{
    f38 = p[0];
    f3c = p[1];
}

// @ 0x00830b30
void Drawable::Destroy()
{
    *(void **)this = &g_vtblDrawable;
    *(void **)((char *)this + 4) = &g_vtblDrawableSec;
    *(void **)((char *)this + 0xc) = &g_vtblDrawableThr;

    for (int i = 0; i < 8; ++i) {
        void *p = mImageInfos[i];
        if (!p)
            continue;
        void *a = *(void **)((char *)p + 0xc);
        if (a) {
            *(void **)((char *)p + 0xc) = 0;
            ((void (__thiscall *)(void *))(*(void ***)a)[1])(a);
        }
        void *b = *(void **)((char *)p + 0x10);
        if (b) {
            *(void **)((char *)p + 0x10) = 0;
            ((void (__thiscall *)(void *))(*(void ***)b)[1])(b);
        }
    }
    for (int i = 7; i >= 0; --i) {
        void *p = mImageInfos[i];
        if (p)
            ((void (__thiscall *)(void *))(*(void ***)p)[1])(p);
    }
    void *a = *(void **)((char *)this + 0x8c);
    if (a)
        ((void (__thiscall *)(void *))(*(void ***)a)[1])(a);
    void *b = *(void **)((char *)this + 0x88);
    if (b)
        ((void (__thiscall *)(void *))(*(void ***)b)[1])(b);
    *(void **)((char *)this + 0x80) = &g_vtblContentValidation;
    *(void **)((char *)this + 0x7c) = &g_vtblEditorResource;
    ((StdBase *)this)->dtor();
}

// @ 0x00830c00
void *Drawable_s0083_0c00::GetImageInfo(int index)
{
    void *def = mInfo;
    if ((unsigned)index >= 8)
        return def;
    if (mImageInfos[index] == 0) {
        void *old = mImageInfos[index];
        if (def != old) {
            if (def)
                ((void (__thiscall *)(void *))(*(void ***)def)[0])(def);
            mImageInfos[index] = def;
            if (old)
                ((void (__thiscall *)(void *))(*(void ***)old)[1])(old);
        }
    }
    return mImageInfos[index];
}

// @ 0x00830c60
int DSub::GetFieldC(int index)
{
    return *(int *)((char *)((Drawable_s0083_0c00 *)((char *)this - 0xc))->GetImageInfo(index) + 0xc);
}

// @ 0x00830c80
int DSub::GetField14(int index)
{
    return *(int *)((char *)((Drawable_s0083_0c00 *)((char *)this - 0xc))->GetImageInfo(index) + 0x14);
}

// @ 0x00830c90
void DSub::GetPair28(float *out, int index)
{
    char *p = (char *)((Drawable_s0083_0c00 *)((char *)this - 0xc))->GetImageInfo(index);
    out[0] = *(float *)(p + 0x28);
    out[1] = *(float *)(p + 0x2c);
}

// @ 0x00830cc0
void DSub::GetPair30(float *out, int index)
{
    char *p = (char *)((Drawable_s0083_0c00 *)((char *)this - 0xc))->GetImageInfo(index);
    out[0] = *(float *)(p + 0x30);
    out[1] = *(float *)(p + 0x34);
}

// @ 0x00830cf0
int DSub::GetField10(int index)
{
    return *(int *)((char *)((Drawable_s0083_0c00 *)((char *)this - 0xc))->GetImageInfo(index) + 0x10);
}

// @ 0x00830d10
int DSub::GetField18(int index)
{
    return *(int *)((char *)((Drawable_s0083_0c00 *)((char *)this - 0xc))->GetImageInfo(index) + 0x18);
}

// @ 0x00830d20
int DSub::GetField20(int index)
{
    return *(int *)((char *)((Drawable_s0083_0c00 *)((char *)this - 0xc))->GetImageInfo(index) + 0x20);
}

// @ 0x00830d30
void DSub::GetPair38(float *out, int index)
{
    char *p = (char *)((Drawable_s0083_0c00 *)((char *)this - 0xc))->GetImageInfo(index);
    out[0] = *(float *)(p + 0x38);
    out[1] = *(float *)(p + 0x3c);
}

// @ 0x00830d60
void DSub::GetPair40(float *out, int index)
{
    char *p = (char *)((Drawable_s0083_0c00 *)((char *)this - 0xc))->GetImageInfo(index);
    out[0] = *(float *)(p + 0x40);
    out[1] = *(float *)(p + 0x44);
}

// @ 0x00830d90
void FUN_00830d90(void * /*this*/, void * /*a*/, void * /*b*/, void * /*c*/, int /*mode*/)
{
}

// @ 0x00831030
void *ImageInfo2::ScalarDtor(unsigned flags)
{
    if (mpIcon) {
        ((void (__thiscall *)(void *))(*(void ***)mpIcon)[1])(mpIcon);
    }
    if (mpImage) {
        ((void (__thiscall *)(void *))(*(void ***)mpImage)[1])(mpImage);
    }
    vptr4 = &g_vtblContentValidation;
    vptr0 = &g_vtblEditorResource;
    if (flags & 1)
        MultiHeap_delete(this);
    return this;
}

// @ 0x008310a0
void ImageInfo2::CopyFrom(const ImageInfo2 *src)
{
    if (src->mpImage != mpImage) {
        if (src->mpImage)
            ((void (__thiscall *)(void *))(*(void ***)src->mpImage)[0])(src->mpImage);
        void *old = mpImage;
        mpImage = src->mpImage;
        if (old)
            ((void (__thiscall *)(void *))(*(void ***)old)[1])(old);
    }
    if (src->mpIcon != mpIcon) {
        if (src->mpIcon)
            ((void (__thiscall *)(void *))(*(void ***)src->mpIcon)[0])(src->mpIcon);
        void *old = mpIcon;
        mpIcon = src->mpIcon;
        if (old)
            ((void (__thiscall *)(void *))(*(void ***)old)[1])(old);
    }
    for (int i = 0; i < 13; ++i)
        ((uint32_t *)((char *)this + 0x14))[i] = ((const uint32_t *)((const char *)src + 0x14))[i];
    for (int b = 0; b < 2; ++b)
        for (int i = 0; i < 10; ++i)
            ((uint32_t *)((char *)this + 0x48 + b * 0x28))[i] =
                ((const uint32_t *)((const char *)src + 0x48 + b * 0x28))[i];
}

// @ 0x00831170
void Drawable_s0083_0c00::SetImageColor(int index, int color)
{
    char *info = (char *)GetImageInfo(index);
    if ((unsigned)index < 8 && info == (char *)this + 0x7c) {
        void *slot = (char *)this + 0x114 + index * 4;
        info = (char *)MakeInfoAt(this, index, slot);
    }
    *(uint32_t *)(info + 0x14) = (uint32_t)color;
    if (mbHasUserDefaults == 0 && index != 8) {
        mbHasUserDefaults = 0;
        return;
    }
    mbHasUserDefaults = 1;
}

// @ 0x008311f0
void Drawable_s0083_0c00::SetField18At(int index, int v)
{
    char *info = (char *)GetImageInfo(index);
    if ((unsigned)index < 8 && info == (char *)this + 0x7c) {
        void *slot = (char *)this + 0x114 + index * 4;
        info = (char *)MakeInfoAt(this, index, slot);
    }
    *(uint32_t *)(info + 0x18) = (uint32_t)v;
    if (mbHasUserDefaults == 0 && index != 8) {
        mbHasUserDefaults = 0;
        return;
    }
    mbHasUserDefaults = 1;
}

// @ 0x00831270
void Drawable_s0083_0c00::SetField20At(int index, int v)
{
    char *info = (char *)GetImageInfo(index);
    if ((unsigned)index < 8 && info == (char *)this + 0x7c) {
        void *slot = (char *)this + 0x114 + index * 4;
        info = (char *)MakeInfoAt(this, index, slot);
    }
    *(uint32_t *)(info + 0x20) = (uint32_t)v;
    if (mbHasUserDefaults == 0 && index != 8) {
        mbHasUserDefaults = 0;
        return;
    }
    mbHasUserDefaults = 1;
}

// @ 0x008312f0
void Drawable_s0083_0c00::SetPair38At(int index, float *v)
{
    char *info = (char *)GetImageInfo(index);
    if ((unsigned)index < 8 && info == (char *)this + 0x7c) {
        void *slot = (char *)this + 0x114 + index * 4;
        info = (char *)MakeInfoAt(this, index, slot);
    }
    *(float *)(info + 0x38) = v[0];
    *(float *)(info + 0x3c) = v[1];
    if (mbHasUserDefaults == 0 && index != 8) {
        mbHasUserDefaults = 0;
        return;
    }
    mbHasUserDefaults = 1;
}

// @ 0x00831380
void Drawable_s0083_0c00::SetPair40At(int index, float *v)
{
    char *info = (char *)GetImageInfo(index);
    if ((unsigned)index < 8 && info == (char *)this + 0x7c) {
        void *slot = (char *)this + 0x114 + index * 4;
        info = (char *)MakeInfoAt(this, index, slot);
    }
    *(float *)(info + 0x40) = v[0];
    *(float *)(info + 0x44) = v[1];
    if (mbHasUserDefaults == 0 && index != 8) {
        mbHasUserDefaults = 0;
        return;
    }
    mbHasUserDefaults = 1;
}

// @ 0x00831410
void *Drawable_s0083_0c00::PickImageInfo(int flags, void *dst)
{
    void *info = (char *)this + 0x7c;
    unsigned sel = (unsigned)flags & 7;
    if (sel <= 3) {
        static const int tbl[4] = { 0, 1, 2, 3 };
        int idx = tbl[sel];
        if (flags & 8)
            idx += 4;
        info = GetImageInfo(idx);
    }
    if (dst) {
        ((ImageInfo2 *)dst)->CopyFrom((ImageInfo2 *)info);
        void *a = *(void **)((char *)this + 0x88);
        if (*(void **)((char *)dst + 0xc) == 0) {
            void *old = *(void **)((char *)dst + 0xc);
            if (a != old) {
                if (a)
                    ((void (__thiscall *)(void *))(*(void ***)a)[0])(a);
                *(void **)((char *)dst + 0xc) = a;
                if (old)
                    ((void (__thiscall *)(void *))(*(void ***)old)[1])(old);
            }
        }
        void *b = *(void **)((char *)this + 0x8c);
        if (*(void **)((char *)dst + 0x10) == 0) {
            void *old = *(void **)((char *)dst + 0x10);
            if (b != old) {
                if (b)
                    ((void (__thiscall *)(void *))(*(void ***)b)[0])(b);
                *(void **)((char *)dst + 0x10) = b;
                if (old)
                    ((void (__thiscall *)(void *))(*(void ***)old)[1])(old);
            }
        }
        FillDefaults((ShadowDesc_s0083_0c00 *)((char *)dst + 0x48), (const ShadowDesc_s0083_0c00 *)((char *)this + 0xc4));
        FillDefaults((ShadowDesc_s0083_0c00 *)((char *)dst + 0x70), (const ShadowDesc_s0083_0c00 *)((char *)this + 0xec));
    }
    return info;
}

// @ 0x00831530
float *FUN_00831530(void * /*this*/, float *out, int /*index*/)
{
    out[0] = 0.0f;
    out[1] = 0.0f;
    return out;
}

// @ 0x008315c0
bool FUN_008315c0(void * /*this*/, int /*a*/, int /*b*/)
{
    return false;
}

// @ 0x00831650
void Drawable_s0083_0c00::EnsureImageInfo0()
{
    if (mbHasUserDefaults != 0)
        return;
    void *def = (char *)this + 0x7c;
    if (mImageInfos[0] == 0) {
        void *old = mImageInfos[0];
        if (def != old) {
            if (def)
                ((void (__thiscall *)(void *))(*(void ***)def)[0])(def);
            mImageInfos[0] = def;
            if (old)
                ((void (__thiscall *)(void *))(*(void ***)old)[1])(old);
        }
    }
    ((ImageInfo2 *)mImageInfos[0])->CopyFrom((ImageInfo2 *)def);
}

// @ 0x008316b0
void DSub::SetImage(int index, void *img)
{
    Drawable_s0083_0c00 *self = (Drawable_s0083_0c00 *)((char *)this - 0xc);
    char *info = (char *)self->GetImageInfo(index);
    if ((unsigned)index < 8 && info == (char *)self + 0x7c) {
        void *slot = (char *)self + 0x114 + index * 4;
        info = (char *)MakeInfoAt(self, index, slot);
    }
    void *old = *(void **)(info + 0xc);
    if (img != old) {
        if (img)
            ((void (__thiscall *)(void *))(*(void ***)img)[0])(img);
        *(void **)(info + 0xc) = img;
        if (old)
            ((void (__thiscall *)(void *))(*(void ***)old)[1])(old);
    }
    uint8_t v;
    if (self->mbHasUserDefaults == 0 && index != 8)
        v = 0;
    else
        v = 1;
    self->mbHasUserDefaults = v;
    self->EnsureImageInfo0();
}

// @ 0x00831760
void Drawable_s0083_0c00::SetImageIcon(int index, void *img)
{
    char *info = (char *)GetImageInfo(index);
    if ((unsigned)index < 8 && info == (char *)this + 0x7c) {
        void *slot = (char *)this + 0x114 + index * 4;
        info = (char *)MakeInfoAt(this, index, slot);
    }
    void *old = *(void **)(info + 0x10);
    if (img != old) {
        if (img)
            ((void (__thiscall *)(void *))(*(void ***)img)[0])(img);
        *(void **)(info + 0x10) = img;
        if (old)
            ((void (__thiscall *)(void *))(*(void ***)old)[1])(old);
    }
    int v;
    if (mbHasUserDefaults == 0 && index != 8)
        v = 0;
    else
        v = 1;
    mbHasUserDefaults = v;
    EnsureImageInfo0();
}

// @ 0x012fe300
void init_15476e4()
{
    *(int*)0x15476e4 = 1;
    *(int*)0x15476e8 = 0;
    TypeRegEntry* e = (TypeRegEntry*)0x15476ec;
    e[0].f0 = (void*)0x141a690; e[0].f1 = 0x54010a1; e[0].f2 = 0x13; e[0].f4 = 0x114 + 4; e[0].f5 = 1; e[0].f6 = 0;
    e[1].f0 = (void*)0x141a690; e[1].f1 = 0x54010a2; e[1].f2 = 0x13; e[1].f4 = 0x114 + 8; e[1].f5 = 1; e[1].f6 = 0;
    e[2].f0 = (void*)0x141a690; e[2].f1 = 0x54010a3; e[2].f2 = 0x13; e[2].f4 = 0x114 + 0xc; e[2].f5 = 1; e[2].f6 = 0;
    e[3].f0 = (void*)0x141a690; e[3].f1 = 0x54010a4; e[3].f2 = 0x13; e[3].f4 = 0x114 + 0x10; e[3].f5 = 1; e[3].f6 = 0;
    e[4].f0 = (void*)0x141a690; e[4].f1 = 0x54010a5; e[4].f2 = 0x13; e[4].f4 = 0x114 + 0x14; e[4].f5 = 1; e[4].f6 = 0;
    e[5].f0 = (void*)0x141a690; e[5].f1 = 0x54010a6; e[5].f2 = 0x13; e[5].f4 = 0x114 + 0x18; e[5].f5 = 1; e[5].f6 = 0;
    e[6].f0 = (void*)0x141a690; e[6].f1 = 0x54010a7; e[6].f2 = 0x13; e[6].f4 = 0x114 + 0x1c; e[6].f5 = 1;
}
