// Slice s0075a550 (batch w2g3, slice 18).
// SP::cMultiBlender (blend controller) plus a neighbouring class (vtable 0x140dab0).
// cMultiBlender layout is taken from the 2008 dev-build PDB (base
// rw::oldanimation::Controller at +0).  Built /O2 /arch:SSE with /EHsc.
#include "../../include/types.h"
#include <intrin.h>

extern "C" void* __cdecl operator_new_graph(unsigned size);
extern "C" void  __cdecl eastl_dealloc(void* p);
extern "C" void  __stdcall FUN_011fda40(int arg);
extern "C" void  __cdecl FUN_011fb220(void* self);
extern "C" void  __cdecl FUN_011fe600(void* self, float v);
extern "C" void  __cdecl FUN_00759880(void* p);
extern "C" void  __cdecl FUN_00759c80(void* p);
extern "C" void  __cdecl RefVector_dtor(void* p);
extern "C" void  __cdecl FUN_0041eb80(void* p);
extern "C" void  __cdecl VecVecInt_dtor(void* b, void* e);
extern "C" void  __cdecl FUN_0071dcc0(void* p);

// ---------------------------------------------------------------------------
// rw::oldanimation::Controller base (layout opaque here)
// ---------------------------------------------------------------------------
struct Controller { char pad[0x1c]; };

// an interpolator element (stride mInterpolatorStride).  A 4-byte non-polymorphic
// base puts the vfptr at +4, matching the original's `mov edx,[ecx+4]` virtual calls.
struct InterpBase { int dummy; };
struct Interp : InterpBase {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual float Virt16();
    virtual void  Virt14(float);
    char pad0[0x1c - 8];
    void* mp1c;      // +0x1c
    float mf20;      // +0x20
    void Fb220();
    void Fb600(float);
};

struct B4 { unsigned char b[4]; };

struct cMultiBlender : Controller {
    unsigned m_maxNumQuats;         // +0x1c
    void*    m_BlendCallBack;       // +0x20
    float*   mWeights;              // +0x24
    bool*    mAnimating;            // +0x28
    bool*    mBlending;             // +0x2c
    char*    mInterpolators;        // +0x30
    char*    mPoseKeys;             // +0x34
    int      mMaxAnims;             // +0x38
    unsigned mInterpolatorStride;   // +0x3c
    int      mNumAnims;             // +0x40
    float    mTotalWeight;          // +0x44
    int      mFirstBlend;           // +0x48
    int      mFirstAdd;             // +0x4c
    bool     mLooping;              // +0x50

    Interp* At(int i) { return (Interp*)(mInterpolators + i * (int)mInterpolatorStride); }

    bool  AnyAnimating();           // 0075a6e0
    int   AddWeight();              // 0075a710
    void  F690(float arg);          // 0075a690
    int   F780(float arg);          // 0075a780
    int   F7d0(float arg);          // 0075a7d0
    float SumWeight();              // 0075a820
    void  F880(float arg);          // 0075a880
    void  F8c0(B4 arg);             // 0075a8c0
    int   F900(void* arg);          // 0075a900
    void  F980(void* a, unsigned char* b, int c, int d);  // 0075a980
    void  Fb410();                  // 0075b410
    int   Fb440(float arg);         // 0075b440
};

// ---------------------------------------------------------------------------
// @ 0x0075a6e0   any animating flag set?
// ---------------------------------------------------------------------------
bool cMultiBlender::AnyAnimating() {
    int n = mNumAnims;
    for (int i = 0; i < n; ++i) {
        if (mAnimating[i] != 0) return true;
    }
    return false;
}

// ---------------------------------------------------------------------------
// @ 0x0075a710   find a free weight slot (or steal one)
// ---------------------------------------------------------------------------
int cMultiBlender::AddWeight() {
    int n = mNumAnims;
    int i = 0;
    if (n > 0) {
        float* w = mWeights;
        do {
            if (*w == 0.0f) return i;
            ++i;
            ++w;
        } while (i < n);
    }
    if (n < mMaxAnims) {
        mNumAnims = n + 1;
        mWeights[n] = 1.0f;
        mAnimating[n] = false;
        mBlending[n] = true;
        return n;
    }
    return -1;
}

// ---------------------------------------------------------------------------
// @ 0x0075a690
// ---------------------------------------------------------------------------
void cMultiBlender::F690(float arg) {
    int n = mNumAnims;
    if (n > 0) {
        for (int i = 0; i < n; ++i) At(i)->Fb600(arg);
    }
    *(int*)((char*)this + 0x18) = 0;
}

// ---------------------------------------------------------------------------
// @ 0x0075a780 / 0x0075a7d0
// ---------------------------------------------------------------------------
typedef void (__thiscall *InterpFn)(void*, float);
int cMultiBlender::F780(float arg) {
    int n = mNumAnims;
    for (int i = 0; i < n; ++i) {
        if (mAnimating[i]) {
            char* p = mInterpolators + i * (int)mInterpolatorStride;
            InterpFn f = *(InterpFn*)(*(int*)(p + 4) + 4);
            f(p, arg);
            *(int*)((char*)this + 0x18) = 0;
        }
    }
    return 1;
}
int cMultiBlender::F7d0(float arg) {
    int n = mNumAnims;
    for (int i = 0; i < n; ++i) {
        if (mAnimating[i]) {
            char* p = mInterpolators + i * (int)mInterpolatorStride;
            InterpFn f = *(InterpFn*)(*(int*)(p + 4) + 8);
            f(p, arg);
            *(int*)((char*)this + 0x18) = 0;
        }
    }
    return 1;
}

// ---------------------------------------------------------------------------
// @ 0x0075a820
// ---------------------------------------------------------------------------
float cMultiBlender::SumWeight() {
    int n = mNumAnims;
    float sum = 0.0f;
    for (int i = 0; i < n; ++i) {
        if (mBlending[i]) {
            Interp* p = (Interp*)(mInterpolators + i * (int)mInterpolatorStride);
            sum += p->Virt16() * mWeights[i];
        }
    }
    return sum;
}

// ---------------------------------------------------------------------------
// @ 0x0075a880
// ---------------------------------------------------------------------------
void cMultiBlender::F880(float arg) {
    int n = mNumAnims;
    for (int i = 0; i < n; ++i) {
        char* p = mInterpolators + i * (int)mInterpolatorStride;
        InterpFn f = *(InterpFn*)(*(int*)(p + 4) + 0x14);
        f(p, arg);
    }
}

// ---------------------------------------------------------------------------
// @ 0x0075a8c0
// ---------------------------------------------------------------------------
extern "C" void FUN_011ff090();
extern "C" void FUN_011fe730();
void cMultiBlender::F8c0(B4 arg) {
    FUN_011fda40(*(int*)&arg);
    if (arg.b[0] == 1 && arg.b[1] == 3 && arg.b[2] == 0)
        m_BlendCallBack = (void*)FUN_011ff090;
    else
        m_BlendCallBack = (void*)FUN_011fe730;
}

// ---------------------------------------------------------------------------
// @ 0x0075a900
// ---------------------------------------------------------------------------
int cMultiBlender::F900(void* arg) {
    int n = mMaxAnims;
    int ok = 1;
    for (int i = 0; i < n; ++i) {
        char* p = mInterpolators + i * (int)mInterpolatorStride;
        int* slot = *(int**)p;
        if (slot == 0) {
            // (*(p+4))->virt24(arg)
            typedef int (__thiscall *Fn)(void*, void*);
            Fn f = *(Fn*)(*(int*)(p + 4) + 0x24);
            if (f(*(void**)(p + 4), arg) != 0) { /* keep ok */ }
            else ok = 0;
        } else {
            if (*slot == 0 || *(int*)(*slot + 8) != *(int*)((char*)arg + 8)) {
                *slot = (int)arg;
                typedef int (__thiscall *Fn2)(void*);
                Fn2 f = *(Fn2*)(*(int*)(p + 4) + 0x28);
                if (f(*(void**)(p + 4)) == 0) ok = 0;
            } else {
                *slot = (int)arg;
            }
        }
    }
    return ok;
}

// ---------------------------------------------------------------------------
// @ 0x0075a980
// ---------------------------------------------------------------------------
void cMultiBlender::F980(void* a, unsigned char* b, int c, int d) {
    (void)a; (void)b; (void)c; (void)d;
}

// ---------------------------------------------------------------------------
// @ 0x0075a550 / 0x0075a620   neighbouring class (vtable 0x140dab0)
// ---------------------------------------------------------------------------
struct RawVec { void* mBegin; void* mEnd; void* mCap; };
struct ClassX {
    void* vt0; void* vt1;
    char pad08[0xc - 8];
    RawVec vec0;        // +0xc
    char pad1[0x20 - 0x18];
    RawVec vec20;       // +0x20
    char pad2[0x34 - 0x2c];
    RawVec vec34;       // +0x34
    char pad3[0x48 - 0x40];
    char sub48[0x14];   // +0x48
    void* p5c;          // +0x5c
    void Dtor();
    void* New70();
};
extern int g_vt140dab0[], g_vt140daac[], g_vt13ef094[];
void ClassX::Dtor() {
    vt0 = (void*)g_vt140dab0;
    vt1 = (void*)g_vt140daac;
    if (p5c) eastl_dealloc(p5c);
    FUN_00759880(sub48);
    VecVecInt_dtor(vec34.mBegin, vec34.mEnd);
    if (vec34.mBegin) eastl_dealloc(vec34.mBegin);
    FUN_0041eb80(&vec20);
    FUN_0041eb80(&vec0);
    vt1 = (void*)g_vt13ef094;
}
void* ClassX::New70() {
    void* p = operator_new_graph(0x70);
    if (p) FUN_00759c80(p);
    return p;
}

// ---------------------------------------------------------------------------
// @ 0x0075b410
// ---------------------------------------------------------------------------
void cMultiBlender::Fb410() {
    unsigned n = (unsigned)mMaxAnims;
    for (unsigned i = 0; i < n; ++i) At(i)->Fb220();
}

// ---------------------------------------------------------------------------
// @ 0x0075b440
// ---------------------------------------------------------------------------
int cMultiBlender::Fb440(float arg) {
    int n = mNumAnims;
    if (n > 0) {
        for (int i = 0; i < n; ++i) {
            if (mAnimating[i]) {
                Interp* p = At(i);
                float f1 = p->mf20;
                float f2 = *(float*)((char*)p->mp1c + 0x20);
                if (!mLooping && f2 <= f1 + arg) {
                    arg = f2 - f1;
                    mAnimating[i] = false;
                }
                InterpFn f = *(InterpFn*)(*(int*)((char*)p + 4));
                f(p, arg);
                *(int*)((char*)this + 0x18) = 0;
            }
        }
    }
    return 1;
}

// ---------------------------------------------------------------------------
// @ 0x0075aa30 / 0x0075ac40 / 0x0075ad80 / 0x0075b190 / 0x0075b2c0 / 0x0075b4d0
// ---------------------------------------------------------------------------
struct Big700;   // 0x70-byte cMultiBlender-related object
void __fastcall FUN_0075aa30(cMultiBlender* self, void* a, void* b, void* c) {
    (void)self; (void)a; (void)b; (void)c;
}
void __fastcall FUN_0075ac40(cMultiBlender* self, void* a, void* b) {
    (void)self; (void)a; (void)b;
}
void* __fastcall FUN_0075ad80(cMultiBlender* self) { (void)self; return 0; }
void __cdecl cMultiBlender_GetResourceDescriptor(void* out, int a, int b, int c, int d, int e) {
    (void)out; (void)a; (void)b; (void)c; (void)d; (void)e;
}
void __fastcall FUN_0075b2c0(cMultiBlender* self, void* a) { (void)self; (void)a; }
void* __fastcall FUN_0075b4d0(int* self) { (void)self; return 0; }
