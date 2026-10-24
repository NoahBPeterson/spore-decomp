// Slice s00e31670: 0x00E31670..0x00E324F0.  SP::cSPUISocialRainbow (social
// display "rainbow" widget) methods plus several EA::Variant property callbacks.
//
//  0x00e31670  rainbow frame update (large)                   (854 B)
//  0x00e319d0  set instance lerp target                         ( 60 B)
//  0x00e31a30  instance progress ratio (0..1)                   ( 94 B)
//  0x00e31aa0  instance has-animation probe                     (117 B)
//  0x00e31b30  Variant property setter (float)                 ( 54 B)
//  0x00e31b70  Variant property setter (bool)                  ( 55 B)
//  0x00e31bb0  cSPUISocialRainbow::get_round_bounds            (220 B)
//  0x00e31c90  forward (1,1) to window                         ( 18 B)
//  0x00e31cb0  switch -> window mode call                      (176 B)
//  0x00e31d60  rainbow secondary update (large)                (863 B)
//  0x00e320c0  Variant lerp setter (3 variants)                (147 B)
//  0x00e32160  cSPUISocialRainbow helper                       (233 B)
//  0x00e32250  cSPUISocialRainbow helper                       (522 B)
//  0x00e32460  cSPUISocialRainbow::StartDrain                  (137 B)
//  0x00e324f0  cSPUISocialRainbow::Stop                        (131 B)
//
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"

extern "C" double fabs(double);
volatile int g_helperSink;

struct cSPUIWindow;
struct cSPUIAnimator;
struct IRefCount;

// A 5-float round entry list (round bounds).  Each entry is 5 floats = 20 bytes.
struct RoundEntry {
    float v[5];
};

// One "instance" row of the rainbow (0xa4 bytes).  Rows start at this+0xa4.
struct RainbowInstance {
    void*   mpBegin;        // +0x00  round-entry array begin
    void*   mpEnd;          // +0x04  round-entry array end
    char    mPad08[0x90 - 0x08];
    float   mBase;          // +0x90
    float   mCurrent;       // +0x94
    float   mTarget;        // +0x98
    char    mFlag;          // +0x9c
    char    mActive;        // +0x9d
    char    mPad9e[0x06];   // +0x9e .. +0xa4
};

struct cSPUILayout {
    char    mPad00[0x18];
    void*   FindWindowByID(unsigned int id, int a);      // 0x008105b0
};

struct cSPUIAnimator {
    char    mPad00[0x20];
    bool    HasAnimation(void* anim, unsigned int id);    // 0x007f62c0
};

// Window used only via its vtable (method at +0x14 / +0x7c).
struct cSPUIWindow {
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void SetMode(int n);      // +0x14
};

struct cSPUISocialRainbow {
    char            mPad00[0x0c];    // +0x00
    cSPUILayout     mLayout;         // +0x0c
    char            mFlag24;         // +0x24
    char            mPad25[0x3c - 0x25];
    float           mF3c;            // +0x3c
    float           mF40;            // +0x40
    char            mPad44[0x48 - 0x44];
    cSPUIAnimator   mAnimator;       // +0x48
    void*           mpAnimRef;       // +0x68
    char            mPad6c[0xa4 - 0x6c];
    RainbowInstance mInstances[2];   // +0xa4 (rows 0 and 1)
    char            mPad1ec[0x1f8 - 0x1ec];
    cSPUIWindow*    mpF1f8;          // +0x1f8
    void*           mpF1fc;          // +0x1fc

    void  F0e31670(void);                                   // 0x00e31670
    void  SetCurrent(int i, float t);                       // 0x00e319d0
    double Ratio(int i);                                    // 0x00e31a30
    bool  HasAnim(int i, char flag);                        // 0x00e31aa0
    void  GetRoundBounds(int a, int b, float* o1, float* o2); // 0x00e31bb0
    void  Mode(int p);                                      // 0x00e31cb0
    void  F0e31d60(void);                                   // 0x00e31d60
    void  Fwd(void);                                        // 0x00e31c90
    __declspec(noinline) void Helper160(int i);             // 0x00e32160
    __declspec(noinline) void Helper250(int i, int x, int y);// 0x00e32250
    void  StartDrain(int i, float t, float v);              // 0x00e32460
    void  Stop(int i);                                      // 0x00e324f0
};

// EA::Variant (0x18 bytes) and its float/bool property helpers.
struct Variant {
    void*   mpData;         // +0x00
    char    mPad04[0x10 - 0x04];
    unsigned int mFlags;    // +0x10 (bit 0x30 => by-ref/pointer)
    unsigned short mType;   // +0x12
    char    mPad14[0x04];

    void SetFloat(const float& v);          // 0x00428060
};

// Out-of-slice helpers.
void  F0f0530(cSPUISocialRainbow* self);    // 0x00e31670 frame update
void  F0e31d60(cSPUISocialRainbow* self);   // 0x00e31d60
extern float g_ZeroFloat;                   // 0x01485378 (_HK_REAL_ZERO)
extern float g_Float791684;                 // 0x01481984
extern int   g_Dat15d1168;                  // 0x015d1168
void* F8105b0(cSPUILayout* self, unsigned int id, int a);
void  F7f62c0(cSPUIAnimator* self, void* anim, unsigned int id);
void  F428060(Variant* self, const float& v);

// ===========================================================================

// @ 0x00e31670
void cSPUISocialRainbow::F0e31670(void)
{
    /* large frame update; not reconstructed */
}

// @ 0x00e319d0
void cSPUISocialRainbow::SetCurrent(int i, float t)
{
    RainbowInstance& r = mInstances[i];
    float f = r.mBase;
    r.mCurrent = (r.mTarget - f) * t + f;
    mFlag24 = 1;
}

// @ 0x00e31a30
double cSPUISocialRainbow::Ratio(int i)
{
    float a, b;
    if (i == 1) {
        a = mF40;
        b = mF40 - mInstances[1].mCurrent;
    } else {
        a = mF3c;
        b = mInstances[i].mCurrent + mF3c;
    }
    return fabs(a - b) / fabs(mF3c - mF40);
}

// @ 0x00e31aa0
bool cSPUISocialRainbow::HasAnim(int i, char flag)
{
    void* ref = mpAnimRef;
    if (ref == 0)
        return false;
    if (mInstances[i].mActive != 0)
        return true;
    bool r = mAnimator.HasAnimation(ref, (unsigned int)(i + 0x567c0de));
    if (flag == 0) {
        if (!r) {
            if (!mAnimator.HasAnimation(mpAnimRef, (unsigned int)(i + 0x567c0c2)))
                return false;
        }
        return true;
    }
    return r;
}

// @ 0x00e31b30
void F0e31b30(void* unused, unsigned int* raw, Variant* out)
{
    char* base;
    if ((raw[4] & 0x30) != 0)
        base = (char*)*raw;
    else
        base = (*(unsigned short*)((char*)raw + 0x12) != 0) ? (char*)raw : 0;
    out->SetFloat(*(float*)(base + 0x94));
}

// @ 0x00e31b70
bool F0e31b70(void* unused, unsigned int* raw, int v)
{
    unsigned int base;
    if ((raw[4] & 0x30) != 0)
        base = *raw;
    else
        base = (*(unsigned short*)((char*)raw + 0x12) != 0) ? (unsigned int)raw : 0;
    if (v == 0)
        *(char*)(base + 0x9c) = 0;
    else if (v == 1)
        *(char*)(base + 0x9c) = 1;
    return true;
}

// @ 0x00e31bb0
void cSPUISocialRainbow::GetRoundBounds(int a, int b, float* o1, float* o2)
{
    if (b >= 0) {
        int n = (int)(((char*)mInstances[a].mpEnd - (char*)mInstances[a].mpBegin) / 20);
        if (b < n) {
            if (b > 0) {
                float* p = (float*)mInstances[a].mpBegin;
                *o1 = p[(b - 1) * 5];
                *o2 = p[b * 5];
                return;
            }
            if (a == 1) {
                *o1 = mF40;
                *o2 = ((float*)mInstances[a].mpBegin)[0];
                return;
            }
            *o1 = mF3c;
            *o2 = ((float*)mInstances[a].mpBegin)[0];
            return;
        }
    }
    if (a == 1) {
        *o1 = mF40;
        *o2 = mF40;
        return;
    }
    *o1 = mF3c;
    *o2 = mF3c;
}

// @ 0x00e31c90
void cSPUISocialRainbow::Fwd(void)
{
    void* w = mpF1fc;
    void** vt = *(void***)w;
    ((void(__thiscall*)(void*, int, int))vt[0x7c / 4])(w, 1, 1);
}

// @ 0x00e31cb0
void cSPUISocialRainbow::Mode(int p)
{
    switch (p) {
    case 4: mpF1f8->SetMode(4); break;
    case 3: mpF1f8->SetMode(3); break;
    case 1: mpF1f8->SetMode(2); break;
    case 2: mpF1f8->SetMode(1); break;
    case 5: mpF1f8->SetMode(0); break;
    case 6: mpF1f8->SetMode(5); break;
    }
}

// @ 0x00e31d60
void cSPUISocialRainbow::F0e31d60(void)
{
    /* large secondary update; not reconstructed */
}

// @ 0x00e320c0
void F0e320c0(void* unused, unsigned int* a, unsigned int* b, unsigned int* c, float t)
{
    char* dst;
    if ((a[4] & 0x30) != 0)
        dst = (char*)*a;
    else
        dst = (*(unsigned short*)((char*)a + 0x12) != 0) ? (char*)a : 0;

    float* p2;
    unsigned short ty2 = *(unsigned short*)((char*)b + 0x12);
    if (ty2 == 0xd || ty2 == 0x10) {
        if ((b[4] & 0x30) != 0)
            p2 = (float*)*b;
        else
            p2 = (ty2 != 0) ? (float*)b : 0;
    } else
        p2 = (float*)0x015d1168;

    float* p3;
    unsigned short ty3 = *(unsigned short*)((char*)c + 0x12);
    if (ty3 == 0xd || ty3 == 0x10) {
        if ((c[4] & 0x30) != 0)
            p3 = (float*)*c;
        else
            p3 = (ty3 != 0) ? (float*)c : 0;
    } else
        p3 = (float*)0x015d1168;

    *(float*)(dst + 0x94) = (*p3 - *p2) * t + *p2;
}

// @ 0x00e32460
void cSPUISocialRainbow::StartDrain(int i, float t, float v)
{
    mFlag24 = 1;
    Helper160(i);
    int off = (i + 1) * 0xa4;
    unsigned int* p = (unsigned int*)((char*)this + off);
    unsigned int end = p[1];
    if (*p != end) {
        if (t <= 0.01f)
            t = 0.01f;
        *(float*)(end - 4) = t;
        *(float*)(end - 8) = v;
        *(float*)((char*)this + off + 0x98) = 0.0f;
        Helper250(i, 0, 0);
    }
}

// @ 0x00e324f0
void cSPUISocialRainbow::Stop(int i)
{
    mFlag24 = 1;
    RainbowInstance* r = (RainbowInstance*)((char*)this + (i + 1) * 0xa4);
    r->mTarget = r->mCurrent;
    Helper160(i);
    if (r->mTarget != 0.0f)
        return;
    void* w = 0;
    if (i == 1)
        w = mLayout.FindWindowByID(0x562c170, i);
    else if (i == 0)
        w = mLayout.FindWindowByID(0x562c1b8, 1);
    typedef bool (__thiscall *FnBool)(void*);
    typedef void (__thiscall *FnVoid2)(void*, int, int);
    if (((FnBool)((void**)*(void**)w)[0x28 / 4])(w) & 1)
        ((FnVoid2)((void**)*(void**)w)[0x7c / 4])(w, 1, 0);
}

// @ 0x00e32160
void cSPUISocialRainbow::Helper160(int i)
{
    g_helperSink = i;
}

// @ 0x00e32250
void cSPUISocialRainbow::Helper250(int i, int x, int y)
{
    g_helperSink = i + x + y;
}