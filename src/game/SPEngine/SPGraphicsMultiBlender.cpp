// src/game/SPEngine/SPGraphicsMultiBlender.cpp -- migrated from slice(s) s0075cf20, s0075b520, s0075a550 by tools/migrate/rewrite.py
// Object file: SPEngine/SPGraphicsMultiBlender.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void  __stdcall FUN_011fda40(int arg);
extern "C" void FUN_011ff090();
extern "C" void FUN_011fe730();
#include <intrin.h>
#include <xmmintrin.h>
#include "SP/cRenderer.h"
#include "rw/oldanimation/Controller.h"
#include "rw/oldanimation/Interpolator.h"

// ---- items of slice s0075a550 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Controller { char pad[0x1c]; };
struct B4 { unsigned char b[4]; };
struct BaseResourceDescriptor {
    unsigned mSize;
    unsigned mAlign;
    BaseResourceDescriptor();            // 0x006c0fa0
    ~BaseResourceDescriptor();           // 0x00c2e4e0
};
struct ResourceDescriptor { BaseResourceDescriptor d[4]; };
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
    static ResourceDescriptor GetResourceDescriptor(int n, B4 flags, int x);   // 0x011fe550
};
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
    static ResourceDescriptor GetResourceDescriptor(int n, B4 flags, int count, int addA, int addB);  // 0075b190
};
typedef void (__thiscall *InterpFn)(void*, float);
// ---- items of slice s0075a550 end

// ---- items of slice s0075b520 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" double __cdecl cos(double);
extern "C" double __cdecl sin(double);
extern "C" double __cdecl acos(double);
#pragma intrinsic(cos, sin, acos)
namespace rw {
namespace oldanimation {
struct ControllerVTable {
    void* m_AddTime;         // +0x00
    void* m_SubTime;         // +0x04
    void* m_SetTime;         // +0x08
    void* m_Update;          // +0x0c
    void* m_GetNaturalMeter; // +0x10
    void* m_SetMeter;        // +0x14
    void* m_SetOutputFormat; // +0x18
    void* m_GetMySize;       // +0x1c
    void* m_GetOutputNames;  // +0x20
    void* m_SetOutputNames;  // +0x24
    void* m_UpdateRemapping; // +0x28
};
}
}
namespace rw {
namespace oldanimation {
struct Controller_s0075_b520 {                     // size 0x1c
    void* m_remapDataPtr;               // +0x00
    ControllerVTable* m_vTable;         // +0x04
    char* m_outputPtr;                  // +0x08
    unsigned int m_outputFormat;        // +0x0c
    unsigned int m_maxNodeSize;         // +0x10
    unsigned int m_numNodes;            // +0x14
    unsigned int m_bufferValid;         // +0x18
};
}
}
namespace rw {
namespace oldanimation {
struct KeyframeAnimation_s0075_b520 {              // size 0x30 (PDB); only +0x28 is used here
    char pad00[0x28];
    void* m_interpInfoPtr;              // +0x28
    unsigned int m_firstSequenceHeaderPtr; // +0x2c
};
}
}
namespace rw {
namespace oldanimation {
struct Interpolator_s0075_b520 : Controller_s0075_b520 {      // size 0x38
    KeyframeAnimation_s0075_b520* m_currentAnimPtr; // +0x1c
    float m_currentTime;                 // +0x20
    float m_timeModifier;                // +0x24
    void* m_interpFramesPtr;             // +0x28
    void* m_InterpolateCallBack;         // +0x2c
    void* m_KeyframeSizeCallBack;        // +0x30
    unsigned int m_keyframeTypeID;       // +0x34
    void SetKeyframeType(void* info);    // @ 0x011fdff0
    int SetAnimation(KeyframeAnimation_s0075_b520* anim); // @ 0x011fe100
    int SetTime(float t);                // @ 0x011fe600
};
}
}
namespace SP {
using namespace rw::oldanimation;
}
namespace SP {
class cMultiBlender_s0075_b520 : public Controller_s0075_b520 {   // size 0x54
public:
    unsigned int m_maxNumQuats;      // +0x1c
    void* m_BlendCallBack;           // +0x20
    float* mWeights;                 // +0x24
    bool* mAnimating;                // +0x28
    bool* mBlending;                 // +0x2c
    char* mInterpolators;            // +0x30
    char* mPoseKeys;                 // +0x34
    int mMaxAnims;                   // +0x38
    unsigned int mInterpolatorStride;// +0x3c
    int mNumAnims;                   // +0x40
    float mTotalWeight;              // +0x44
    int mFirstBlend;                 // +0x48
    int mFirstAdd;                   // +0x4c
    bool mLooping;                   // +0x50

    int AllocSlot();                 // @ 0x0075a710
    void RecalcWeights();            // @ 0x0075ac40

    int GetBlendState();                                     // @ 0x0075b520
    void StartAnim(Interpolator_s0075_b520* interp, KeyframeAnimation_s0075_b520* anim); // @ 0x0075b540
    void SetAnimTime(KeyframeAnimation_s0075_b520* anim, float time);   // @ 0x0075b5d0
    void SetWeight(KeyframeAnimation_s0075_b520* anim, float weight);   // @ 0x0075b630
    void SetAnimating(KeyframeAnimation_s0075_b520* anim, bool value);  // @ 0x0075b6e0
    void SetBlending(KeyframeAnimation_s0075_b520* anim, bool value);   // @ 0x0075b790
};
}
// ---- items of slice s0075b520 end

// ---- items of slice s0075cf20 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace rw {
namespace oldanimation {
struct Controller_s0075_cf20 {
    void* m_remapDataPtr;         // +0x00
    ControllerVTable* m_vTable;   // +0x04
    char* m_outputPtr;            // +0x08
    unsigned int m_outputFormat;  // +0x0c
    unsigned int m_maxNodeSize;   // +0x10
    unsigned int m_numNodes;      // +0x14
    unsigned int m_bufferValid;   // +0x18
};
}
}
namespace rw {
namespace oldanimation {
struct Interpolator_s0075_cf20 : Controller_s0075_cf20 {  // size 0x38
    void* m_currentAnimPtr;       // +0x1c
    float m_currentTime;          // +0x20
    float m_timeModifier;         // +0x24
    void* m_interpFramesPtr;      // +0x28
    void* m_InterpolateCallBack;  // +0x2c
    void* m_KeyframeSizeCallBack; // +0x30
    unsigned int m_keyframeTypeID;// +0x34
};
}
}
namespace SP {
class cMultiBlender_s0075_cf20 : public Controller_s0075_cf20 {  // size 0x54
public:
    unsigned int m_maxNumQuats;       // +0x1c
    void* m_BlendCallBack;            // +0x20
    float* mWeights;                  // +0x24
    bool* mAnimating;                 // +0x28
    bool* mBlending;                  // +0x2c
    char* mInterpolators;             // +0x30
    char* mPoseKeys;                  // +0x34
    int mMaxAnims;                    // +0x38
    unsigned int mInterpolatorStride; // +0x3c
    int mNumAnims;                    // +0x40
    float mTotalWeight;               // +0x44
    int mFirstBlend;                  // +0x48
    int mFirstAdd;                    // +0x4c
    bool mLooping;                    // +0x50

    void Update();                    // @ 0x0075d440
    __declspec(noinline) void Rebuild();      // @ 0x0075cf20
    __declspec(noinline) void UpdateBlend();  // @ 0x0075ca60
    void NoOp();                      // @ 0x0075aa30
};
}
// ---- items of slice s0075cf20 end

// @ 0x0075a710
int cMultiBlender::AddWeight()
{
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

// @ 0x0075a780
int cMultiBlender::F780(float arg)
{
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

// @ 0x0075a7d0
int cMultiBlender::F7d0(float arg)
{
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

// @ 0x0075a820
float cMultiBlender::SumWeight()
{
    int n = mNumAnims;
    float sum = 0.0f;
    for (int i = 0; i < n; ++i) {
        if (mBlending[i]) {
            Interp* p = (Interp*)(mInterpolators + i * (int)mInterpolatorStride);
            typedef float (__thiscall *VFn)(void*);
            VFn f = *(VFn*)(*(int*)((char*)p + 4) + 0x10);
            sum += f(p) * mWeights[i];
        }
    }
    return sum;
}

// @ 0x0075a880
void cMultiBlender::F880(float arg)
{
    int n = mNumAnims;
    for (int i = 0; i < n; ++i) {
        char* p = mInterpolators + i * (int)mInterpolatorStride;
        InterpFn f = *(InterpFn*)(*(int*)(p + 4) + 0x14);
        f(p, arg);
    }
}

// @ 0x0075a8c0
void cMultiBlender::F8c0(B4 arg)
{
    FUN_011fda40(*(int*)&arg);
    if (arg.b[0] == 1 && arg.b[1] == 3 && arg.b[2] == 0)
        m_BlendCallBack = (void*)FUN_011ff090;
    else
        m_BlendCallBack = (void*)FUN_011fe730;
}

// @ 0x0075a900
int cMultiBlender::F900(void* arg)
{
    int n = mMaxAnims;
    int ok = 1;
    for (int i = 0; i < n; ++i) {
        char* p = mInterpolators + i * (int)mInterpolatorStride;
        int* slot = *(int**)p;
        if (slot == 0) {
            // (*(p+4))->virt24(arg)
            typedef int (__thiscall *Fn)(void*, void*);
            Fn f = *(Fn*)(*(int*)(p + 4) + 0x24);
            if (f(p, arg) != 0) { /* keep ok */ }
            else ok = 0;
        } else {
            if (*slot == 0 || *(int*)(*slot + 8) != *(int*)((char*)arg + 8)) {
                *slot = (int)arg;
                typedef int (__thiscall *Fn2)(void*);
                Fn2 f = *(Fn2*)(*(int*)(p + 4) + 0x28);
                if (f(p) == 0) ok = 0;
            } else {
                *slot = (int)arg;
            }
        }
    }
    return ok;
}

// @ 0x0075ac40
void __fastcall FUN_0075ac40(cMultiBlender* self, void* a, void* b)
{
    (void)self; (void)a; (void)b;
}

// @ 0x0075b190
ResourceDescriptor cMultiBlender::GetResourceDescriptor(int n, B4 flags, int count, int addA, int addB)
{
    ResourceDescriptor base = Interp::GetResourceDescriptor(n, flags, 0);
    unsigned size = (unsigned)((count * 3 + 0x2a) * 2);
    unsigned align = base.d[0].mAlign;
    if (align > 1)
        size = (size + (align - 1)) & ~(align - 1);
    int rowBytes = ((flags.b[1] + flags.b[0] * 4 + flags.b[2]) * 4) + 4;
    int a1 = 4;
    if (flags.b[0] != 0) a1 = 0x10;
    int total = (int)size;
    total += (int)base.d[0].mSize * count;
    total += ((((unsigned)a1 - 1) + rowBytes) & ~((unsigned)a1 - 1)) * n;
    if (addA != 0) {
        int a2 = 4;
        if (flags.b[0] != 0) a2 = 0x10;
        total = total + ((((unsigned)a2 - 1) + rowBytes) & ~((unsigned)a2 - 1)) * n;
    }
    if (addB != 0)
        total = ((total + 3) & 0xfffffffc) + 0x10 + n * 8;
    ResourceDescriptor result;
    result.d[0].mSize = (unsigned)total;
    result.d[0].mAlign = align;
    return result;
}

// @ 0x0075b2c0
void __fastcall FUN_0075b2c0(cMultiBlender* self, void* a)
{ (void)self; (void)a; }

// @ 0x0075b410
void cMultiBlender::Fb410()
{
    unsigned n = (unsigned)mMaxAnims;
    for (unsigned i = 0; i < n; ++i) At(i)->Fb220();
}

// @ 0x0075b440
int cMultiBlender::Fb440(float arg)
{
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

// @ 0x0075b4d0
void* __fastcall FUN_0075b4d0(int* self)
{ (void)self; return 0; }

// @ 0x0075b520
namespace SP {
int cMultiBlender_s0075_b520::GetBlendState()
{
    int v = 0;
    if (mNumAnims > v) {
        Interpolator_s0075_b520* p = (Interpolator_s0075_b520*)mInterpolators;
        int* r = (int*)p->m_remapDataPtr;
        if (r == 0 || *r == 0)
            return ((int (__thiscall*)(void*))p->m_vTable->m_GetOutputNames)(p);
        v = *r;
    }
    return v;
}
}  // namespace SP

// @ 0x0075b540
namespace SP {
void cMultiBlender_s0075_b520::StartAnim(Interpolator_s0075_b520* interp, KeyframeAnimation_s0075_b520* anim)
{
    interp->SetKeyframeType(*(void**)anim->m_interpInfoPtr);
    interp->SetAnimation(anim);
    if (*(int*)anim->m_interpInfoPtr == 1 && 3 < ((unsigned char*)this)[0xd]) {
        ((void (__thiscall*)(void*))interp->m_vTable->m_Update)(interp);
        struct Val { float x, y, z; Val(float a, float b, float c) { x = a; y = b; z = c; } };
        Val one(1.0f, 1.0f, 1.0f);
        for (unsigned int i = 0; i < m_numNodes; i++) {
            *(Val*)(interp->m_outputPtr + 0x1c + i * 0x30) = one;
        }
    }
}
}  // namespace SP

// @ 0x0075b5d0
namespace SP {
void cMultiBlender_s0075_b520::SetAnimTime(KeyframeAnimation_s0075_b520* anim, float time)
{
    unsigned int n = mNumAnims;
    int idx = 0;
    if (n > 0) {
        char* p = mInterpolators + 0x1c;
        unsigned int stride = mInterpolatorStride;
        do {
            if (*(KeyframeAnimation_s0075_b520**)p == anim) {
                if (idx >= 0) {
                    ((Interpolator_s0075_b520*)(mInterpolators + stride * idx))->SetTime(time);
                    m_bufferValid = 0;
                }
                return;
            }
            idx++;
            p += stride;
        } while ((unsigned int)idx < n);
    }
}
}  // namespace SP

// @ 0x0075b630
namespace SP {
void cMultiBlender_s0075_b520::SetWeight(KeyframeAnimation_s0075_b520* anim, float weight)
{
    unsigned int n = mNumAnims;
    int idx = 0;
    if (n > 0) {
        char* p = mInterpolators + 0x1c;
        unsigned int stride = mInterpolatorStride;
        do {
            if (*(KeyframeAnimation_s0075_b520**)p == anim) {
                if (idx >= 0) {
                    if (mBlending[idx] == false)
                        return;
                    if (mWeights[idx] == weight)
                        return;
                    mWeights[idx] = weight;
                    m_bufferValid = 0;
                    RecalcWeights();
                    return;
                }
                break;
            }
            idx++;
            p += stride;
        } while ((unsigned int)idx < n);
    }
    int j = AllocSlot();
    if (j >= 0) {
        StartAnim((Interpolator_s0075_b520*)(mInterpolators + mInterpolatorStride * j), anim);
        m_bufferValid = 0;
        mWeights[j] = weight;
        RecalcWeights();
    }
}
}  // namespace SP

// @ 0x0075d440
namespace SP {
void cMultiBlender_s0075_cf20::Update()
{
    if (m_bufferValid == 0) {
        int n = mNumAnims;
        for (int i = 0; i < n; i++) {
            Interpolator_s0075_cf20* p = (Interpolator_s0075_cf20*)(mInterpolators + mInterpolatorStride * i);
            ((void (__thiscall*)(void*))p->m_vTable->m_Update)(p);
        }
        if (3 < ((unsigned char*)this)[0xd]) {
            Rebuild();
            m_bufferValid = 1;
            return;
        }
        if (((unsigned char*)this)[0xc] != 0) {
            UpdateBlend();
            m_bufferValid = 1;
            return;
        }
        NoOp();
    }
    m_bufferValid = 1;
}
}  // namespace SP
