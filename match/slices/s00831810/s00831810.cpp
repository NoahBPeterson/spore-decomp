// Slice s00831810 -- SP::cSPUIDebugConsole (derives the SPUI standard drawable).
// Region flags /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast.
#include "types.h"

// ---------------------------------------------------------------- masked externs
extern char g_vtblEditorResource;      // 0x13eb938
extern char g_vtblContentValidation;   // 0x13ec458
extern char g_vtblCreatureAbility;     // 0x13ef094
extern char g_vtblConsole;             // 0x141a894
extern char g_vtblConsoleSec;          // 0x141a884
extern char g_vtblPaintSystem;         // 0x13eb394

extern "C" void __cdecl EA_Free(void *);          // 0xf47380
extern "C" int  __cdecl FUN_00987900();           // 0x987900
extern "C" void __cdecl _ReadWriteBarrier(void);

struct ShadowDesc {
    uint32_t mode1, mode2, f8, fc, f10;
    float    s14, s18, s1c, s20;
    uint32_t f24;
    void SetMode1(int mode);   // 0x00830280 (other TU)
    void SetMode2(int mode);   // 0x00830150 (other TU)
};

struct ImageInfo2 {
    void    *vptr0, *vptr4;
    uint32_t r8;
    void    *mpImage, *mpIcon;
    char     pad[0x84];
    void CopyFrom(const ImageInfo2 *src);   // 0x008310a0 (other TU)
};

struct Stopwatch { double GetElapsed(); };  // 0x93a3a0
struct Animator  { void Dtor(); };          // 0x7f8c20

struct DebugConsole {
    void    *vptr0;        // +0x000
    void    *vptr4;        // +0x004
    uint32_t r8;           // +0x008
    void    *mpAlloc;      // +0x00c
    char     pad10[0x24];  // +0x010..+0x034 (stopwatch at +0x10)
    float    f34;          // +0x034
    uint8_t  b38;          // +0x038
    char     pad39[7];
    char     mAnimator[0x24]; // +0x040
    void    *f64;          // +0x064
    char     pad68[0x14];
    char     mInfo[0x98];  // +0x07c
    void    *mImageInfos[8]; // +0x114
    uint8_t  mbHasUserDefaults; // +0x134
    char     pad135[0xdb];  // +0x135..+0x210
    void    *mpText;        // +0x210

    void  ResetImages();      // 0x00831ef0
    void  Dtor();             // 0x00832160
    bool  CheckTimeout();     // 0x008321d0
    bool  StateCheck();       // 0x00832370
    void  Update();           // 0x008326c0
    void  Dtor2();            // 0x00832710
    void *GetImageInfo(int index);   // 0x00830c00 (other TU)
};

// ---------------------------------------------------------------- 0x00831ef0
void DebugConsole::ResetImages()
{
    FUN_00987900();
    for (int i = 0; i < 8; ++i) {
        void *p = mImageInfos[i];
        if (p == 0) {
            void *def = (char *)this + 0x7c;
            void *old = mImageInfos[i];
            if (def != old) {
                if (def)
                    ((void (__thiscall *)(void *))(*(void ***)def)[0])(def);
                mImageInfos[i] = def;
                if (old)
                    ((void (__thiscall *)(void *))(*(void ***)old)[1])(old);
            }
        } else {
            ((ShadowDesc *)((char *)p + 0x70))->SetMode1(*(int *)((char *)p + 0x70));
            ((ShadowDesc *)((char *)p + 0x70))->SetMode2(*(int *)((char *)p + 0x74));
            ((ShadowDesc *)((char *)p + 0x48))->SetMode1(*(int *)((char *)p + 0x48));
            ((ShadowDesc *)((char *)p + 0x48))->SetMode2(*(int *)((char *)p + 0x4c));
        }
    }
    mbHasUserDefaults = 0;
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
    ((ImageInfo2 *)mImageInfos[0])->CopyFrom((const ImageInfo2 *)def);
}

// ---------------------------------------------------------------- 0x008320d0
void DebugConsole_Ctor(DebugConsole *self)
{
    self->vptr4 = (void *)0x13ef094;
    self->r8 = 0;
    void *p = (char *)self + 0x10;
    self->vptr0 = (void *)0x141a830;
    self->vptr4 = (void *)0x141a82c;
    self->mpAlloc = p;
    if (p) {
        *(uint32_t *)p = 0x86421357;
        void *q = self->mpAlloc;
        *(uint32_t *)((char *)q + 4) = 0x1f0;
        q = self->mpAlloc;
        *(uint32_t *)((char *)q + 0x14) = 0;
        *(uint32_t *)((char *)q + 0x10) = 8;
        void *e = (char *)q + 0x10;
        void *r = self->mpAlloc;
        *(int *)((char *)e + 8) = *(int *)((char *)r + 4) - 8;
        *(void **)((char *)e + 0xc) = e;
        r = self->mpAlloc;
        *(int *)((char *)r + 8) = *(int *)((char *)r + 4) - 8;
        r = self->mpAlloc;
        *(void **)((char *)r + 0xc) = e;
    } else {
        self->mpAlloc = 0;
    }
    self->mpText = 0;
}

// ---------------------------------------------------------------- 0x00832160
void DebugConsole::Dtor()
{
    vptr0 = (void *)0x141a830;
    vptr4 = (void *)0x141a82c;
    EA_Free(mpText);
    mpAlloc = 0;
    vptr4 = (void *)&g_vtblCreatureAbility;
    vptr0 = (void *)&g_vtblEditorResource;
}

// ---------------------------------------------------------------- 0x008321d0
bool DebugConsole::CheckTimeout()
{
    void *pi = (void *)((int (__thiscall *)(void *))(*(void ***)f64)[0x10 / 4])(f64);
    char *r = (char *)((int (__thiscall *)(void *))(*(void ***)pi)[0x38 / 4])(pi);
    if (*(float *)(r + 0xc) >= 0.0f) {
        double t = ((Stopwatch *)((char *)this + 0x10))->GetElapsed();
        if ((float)t * *(float *)((char *)this + 0x24) <= *(float *)((char *)this + 0x30))
            return false;
    }
    return true;
}

// ---------------------------------------------------------------- 0x00832370
bool DebugConsole::StateCheck()
{
    void *p = (char *)this + 0x10;
    if (*(uint32_t *)p != 0 || *(uint32_t *)((char *)p + 4) != 0)
        return true;
    return false;
}

// ---------------------------------------------------------------- 0x008326c0
void DebugConsole::Update()
{
}

// ---------------------------------------------------------------- 0x00832710
void DebugConsole::Dtor2()
{
    *(void **)this = &g_vtblConsole;
    *(void **)((char *)this + 8) = &g_vtblConsoleSec;
    _ReadWriteBarrier();
    void *a = *(void **)((char *)this + 0x88);
    void *cap = *(void **)((char *)this + 0x90);
    if ((((int)((char *)cap - (char *)a) & ~1) > 2) && a && a != *(void **)((char *)this + 0x98))
        EA_Free(a);
    void *c = *(void **)((char *)this + 0x64);
    if (c)
        ((void (__thiscall *)(void *))(*(void ***)c)[1])(c);
    void *d = *(void **)((char *)this + 0x60);
    if (d)
        ((void (__thiscall *)(void *))(*(void ***)d)[1])(d);
    ((Animator *)((char *)this + 0x40))->Dtor();
    *(void **)((char *)this + 8) = &g_vtblPaintSystem;
    *(void **)this = &g_vtblContentValidation;
}

// ---------------------------------------------------------------- 0x00832010
int FUN_00832010(void * /*self*/, int /*a*/, int /*kind*/, void * /*val*/)
{
    return 0;
}

// ---------------------------------------------------------------- unfinished big functions
void FUN_00831810(void *) {}
void FUN_00832230(void *) {}
void FUN_008323d0(void *) {}
void FUN_008324d0(void *) {}
void FUN_00832580(void *) {}
