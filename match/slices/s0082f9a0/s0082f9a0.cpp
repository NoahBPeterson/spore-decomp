// Slice s0082f9a0 -- UTFWin SPUI standard drawable + drop-shadow descriptor helpers.
// Region flags /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast.
#include "types.h"

// ---------------------------------------------------------------- masked externs/globals
extern char g_vtblImgInfo;      // 0x141a760 (primary)
extern char g_vtblImgInfoSec;   // 0x141a750
extern char g_vtblDrawable;     // 0x141a7d8
extern char g_vtblDrawableSec;  // 0x141a7c0
extern char g_vtblDrawableThr;  // 0x141a780
extern char g_vtblEditorResource; // 0x13eb938
extern char g_vtblContentValidation;   // 0x13ec458

// ---------------------------------------------------------------- class stubs
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

// ---------------------------------------------------------------- 0x00830380
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

// ---------------------------------------------------------------- 0x00830280
void ShadowDesc::SetMode1(int mode)
{
    mode1 = mode;
    switch (mode) {
    case 1: s18 = 1.0f; s14 = 1.0f; return;
    case 2: s18 = 2.0f; s14 = 2.0f; return;
    case 3: s18 = 3.0f; s14 = 3.0f; return;
    case 4: s18 = 4.0f; s14 = 4.0f; return;
    case 5: s18 = 5.0f; s14 = 5.0f; return;
    case 6: s18 = 6.0f; s14 = 6.0f; return;
    case 7: s18 = 7.0f; s14 = 7.0f; return;
    case 8: s18 = 8.0f; s14 = 8.0f; return;
    case 9: s18 = 9.0f; s14 = 9.0f; return;
    }
}

// ---------------------------------------------------------------- 0x00830150
void ShadowDesc::SetMode2(int mode)
{
    mode2 = mode;
    switch (mode) {
    case 1: s1c = 0.0004f; s20 = 0.25f;  return;
    case 2: s1c = 0.0003f; s20 = 0.5f;   return;
    case 3: s1c = 0.0002f; s20 = 0.75f;  return;
    case 4: s1c = 0.0001f; s20 = 1.0f;   return;
    case 5: s1c = 0.0f;    s20 = 1.25f;  return;
    case 6: s1c = 0.0f;    s20 = 1.5f;   return;
    case 7: s1c = 0.0f;    s20 = 1.85f;  return;
    case 8: s1c = 0.0f;    s20 = 2.35f;  return;
    case 9: s1c = 0.0f;    s20 = 3.15f;  return;
    }
}

// ---------------------------------------------------------------- 0x00830430
struct cSPUIStdDrawableImageInfo {
    void *vptr;        // +0x00
    char  pad[0x94];
    void *QueryInterface(unsigned id);   // 0x00830430
};

void *cSPUIStdDrawableImageInfo::QueryInterface(unsigned id)
{
    switch (id) {
    case 0x5400186:
    case 0xae9cb0fa:
    case 0xee3f516e:
    case 0xeec58382:
        return this;
    }
    return 0;
}

// ---------------------------------------------------------------- 0x008306a0
struct ImageInfoFull {
    char pad0[0x48];
    ShadowDesc mShadowStroke;   // +0x48
    ShadowDesc mShadowHalo;     // +0x70
};

void FUN_008306a0(ImageInfoFull *p)
{
    p->mShadowHalo.SetMode1(p->mShadowHalo.mode1);
    p->mShadowHalo.SetMode2(p->mShadowHalo.mode2);
    p->mShadowStroke.SetMode1(p->mShadowStroke.mode1);
    p->mShadowStroke.SetMode2(p->mShadowStroke.mode2);
}

// ---------------------------------------------------------------- 0x00830af0
struct DrawableTail {
    char   pad0[0x38];
    float  f38;   // +0x38
    float  f3c;   // +0x3c
    void SetPoint(const float *p);   // 0x00830af0
};

void DrawableTail::SetPoint(const float *p)
{
    f38 = p[0];
    f3c = p[1];
}

// ================================================================ remaining funcs
extern "C" void __cdecl VisitWindowTreeDepthFirst(void *, void *, void *); // 0x807d30
extern "C" void __cdecl VisitCallback_30020();                             // 0x830020
extern "C" void __cdecl FUN_008304a0(void *, void *);                      // 0x8304a0
extern "C" double __cdecl TypesetterValidate(double);                      // 0x11e0906
struct StdBase { void ctor(); void dtor(); };

// ---------------------------------------------------------------- 0x00830080
struct VisitCtx { uint8_t b; char pad[3]; uint32_t v; };

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

// ---------------------------------------------------------------- 0x008300e0
struct W20 {
    void *vptr;         // +0
    char  pad[0x1c];    // +4
    void *f20;          // +0x20
    bool  SetThing(void *p);   // 0x008300e0
};

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

// ---------------------------------------------------------------- 0x008304c0
struct FactoryRegistry {
    void *vptr;   // +0
    int *CreateInstance(int **out, int a1, int a2, int a3);   // 0x008304c0
};

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

// ---------------------------------------------------------------- 0x008306e0
float *FUN_008306e0(float *dst, float *a, float *b, float *c)
{
    float f1 = a[0], f2 = a[1], f3 = a[2], f4 = a[3];
    dst[0] = f1;
    dst[1] = f2;
    dst[2] = f3;
    dst[3] = f4;
    double d6 = TypesetterValidate((double)(((b[0] - 1.0f) * (f3 - f1)) * 0.5f));
    double d7 = TypesetterValidate((double)(((b[1] - 1.0f) * (f4 - f2)) * 0.5f));
    double d8 = TypesetterValidate((double)c[1]);
    double d9 = TypesetterValidate((double)c[0]);
    dst[0] = (dst[0] - (float)d6) + (float)d9;
    dst[1] = (dst[1] - (float)d7) + (float)d8;
    dst[2] = (dst[2] + (float)d9) + (float)d6;
    dst[3] = ((float)d8 + dst[3]) + (float)d7;
    return dst;
}

// ---------------------------------------------------------------- 0x00830810
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

extern char g_vtblContentValidation;   // 0x13ec458

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
    stroke.SetMode2(2);

    halo.mode1 = 0; halo.mode2 = 2; halo.f8 = 3; halo.fc = 0; halo.f10 = 0;
    halo.s14 = 0; halo.s18 = 0; halo.s1c = 0; halo.s20 = 0; halo.f24 = 0;
    halo.SetMode2(2);
    return this;
}

// ---------------------------------------------------------------- 0x00830910
struct SmallSet {
    char  pad0[4];
    void  Do(int param_2);   // 0x00830910
};

void SmallSet::Do(int param_2)
{
    FUN_008304a0((void *)param_2, (char *)this - 4);
    int v = ((int (__thiscall *)(void *))(*(void ***)this)[0x14 / 4])(this);
    *(int *)(param_2 + 0xc) = v;
}

// ---------------------------------------------------------------- 0x00830950
struct Drawable {
    char data[0x7c];
    ImageInfo mImageInfo;          // +0x7c
    void *mImageInfos[8];          // +0x114
    uint8_t mbHasUserDefaults;     // +0x134
    char  pad135[3];
    uint32_t mDrawParams[8];       // +0x138
    float  mDrawArea[4];           // +0x148
    float  mOODrawAreaSize[2];     // +0x158
    Drawable *Construct();         // 0x00830950
    void Destroy();                // 0x00830b30
};

Drawable *Drawable::Construct()
{
    ((StdBase *)this)->ctor();
    *(void **)this = &g_vtblDrawable;
    *(void **)((char *)this + 4) = &g_vtblDrawableSec;
    *(void **)((char *)this + 0xc) = &g_vtblDrawableThr;
    mImageInfo.Construct();

    for (int i = 0; i < 8; ++i)
        mImageInfos[i] = 0;
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

    void *src = (char *)this + 0x7c;
    ((void (__thiscall *)(void *))(*(void ***)src)[0])(src);
    for (int i = 0; i < 8; ++i) {
        void *old = mImageInfos[i];
        if (src != old) {
            if (src)
                ((void (__thiscall *)(void *))(*(void ***)src)[0])(src);
            mImageInfos[i] = src;
            if (old)
                ((void (__thiscall *)(void *))(*(void ***)old)[1])(old);
        }
    }
    return this;
}

// ---------------------------------------------------------------- 0x00830b30
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

// ---------------------------------------------------------------- 0x0082f9a0
// ArgScript parser ("SetFromArgScript"): large state machine, translation incomplete.
int FUN_0082f9a0(void * /*this*/, void * /*arg*/)
{
    return 1;
}

