// src/game/SPEngine/SPGraphicsMultiBlender.cpp -- migrated from slice(s) s0075c070, s0075cf20, s0075b520, s0075a550 by tools/migrate/rewrite.py
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
#include "rw/oldanimation/ControllerFormat.h"
#include <string.h>

// ---- items of slice s0075a550 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern int g_vt153813c[];
struct B4 { unsigned char b[4]; };
struct Controller {
    void*    mpFrameList;       // +0x00
    void*    mpVtbl;            // +0x04
    char*    mpData;            // +0x08
    B4       mFlags;            // +0x0c
    int      mFrameStride;      // +0x10  bytes per frame
    int      mNumFrames;        // +0x14
    int      mDirty;            // +0x18
    void* Alloc(unsigned size, int nAdd, int numFrames, B4 flags, int hasFrames);  // 0x011fda60
};
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
    char* mpFrameData;   // +0x08
    B4    mFlags;        // +0x0c
    int   mFrameStride;  // +0x10
    int   mNumFrames;    // +0x14
    int   mDirty;        // +0x18
    void* mp1c;      // +0x1c
    float mf20;      // +0x20
    void Fb220();
    void Fb600(float);
    void* FrameAt(int frame);   // 0x011fda50
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
    void  Fb410();                  // 0075b410
    int   Fb440(float arg);         // 0075b440
    static ResourceDescriptor GetResourceDescriptor(int n, B4 flags, int count, int addA, int addB);  // 0075b190
};
typedef void (__thiscall *InterpFn)(void*, float);
static inline float HkSqrt(float v) {
    const __m128 vv   = _mm_set1_ps(v);
    const __m128 one  = _mm_set1_ps(1.0f);
    const __m128 half = _mm_set1_ps(0.5f);
    __m128 e = _mm_rsqrt_ps(vv);
    e = _mm_add_ps(_mm_mul_ps(_mm_sub_ps(one, _mm_mul_ps(_mm_mul_ps(e, e), vv)), _mm_mul_ps(e, half)), e);
    e = _mm_add_ps(_mm_mul_ps(_mm_sub_ps(one, _mm_mul_ps(_mm_mul_ps(e, e), vv)), _mm_mul_ps(e, half)), e);
    __m128 r = _mm_andnot_ps(_mm_cmpeq_ps(vv, _mm_setzero_ps()), _mm_mul_ps(e, vv));
    return _mm_cvtss_f32(r);
}
// ---- items of slice s0075a550 end

// ---- items of slice s0075b520 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" double __cdecl cos(double);
extern "C" double __cdecl sin(double);
extern "C" double __cdecl acos(double);
extern const float kSlerpAngle;                       // 0x01538360 (5 degrees in radians)
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
class Controller_s0075_b520 { public:                     // size 0x1c
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
class KeyframeAnimation_s0075_b520 { public:              // size 0x30 (PDB); only +0x28 is used here
    char pad00[0x28];
    void* m_interpInfoPtr;              // +0x28
    unsigned int m_firstSequenceHeaderPtr; // +0x2c
};
}
}
namespace rw {
namespace oldanimation {
class Interpolator_s0075_b520 : public Controller_s0075_b520 { public:      // size 0x38
    KeyframeAnimation_s0075_b520* m_currentAnimPtr; // +0x1c
    float m_currentTime;                 // +0x20
    float m_timeModifier;                // +0x24
    void* m_interpFramesPtr;             // +0x28
    void* m_InterpolateCallBack;         // +0x2c
    void* m_KeyframeSizeCallBack;        // +0x30
    unsigned int m_keyframeTypeID;       // +0x34
    void SetKeyframeType(void* info);    // 0x011fdff0
    int SetAnimation(KeyframeAnimation_s0075_b520* anim); // 0x011fe100
    int SetTime(float t);                // 0x011fe600
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

    int AllocSlot();                 // 0x0075a710
    void RecalcWeights();            // 0x0075ac40

    int GetBlendState();                                     // 0x0075b520
    void StartAnim(Interpolator_s0075_b520* interp, KeyframeAnimation_s0075_b520* anim); // 0x0075b540
    void SetAnimTime(KeyframeAnimation_s0075_b520* anim, float time);   // 0x0075b5d0
    void SetWeight(KeyframeAnimation_s0075_b520* anim, float weight);   // 0x0075b630
    void SetAnimating(KeyframeAnimation_s0075_b520* anim, bool value);  // 0x0075b6e0
    void SetBlending(KeyframeAnimation_s0075_b520* anim, bool value);   // 0x0075b790
};
}
struct KeyInfo {
    int compressed;                                   // +0x00
    int vecStride;                                    // +0x04
    int quatStride;                                   // +0x08
    int pad0c[3];
    void (__cdecl* decodeVec)(float* out, const void* in);    // +0x18
    int pad1c;
    void (__cdecl* decodeQuat)(float* out, const void* in);   // +0x20
};
struct KeyFlags {
    int pad00[2];
    unsigned int mask;                                // +0x08: bit 0-7 rotation, bit 8-15 translation
    float offX, scaleX;                               // +0x0c, +0x10
    float offY, scaleY;                               // +0x14, +0x18
    float offZ, scaleZ;                               // +0x1c, +0x20
};
#define SPLAT(v, i) _mm_shuffle_ps((v), (v), _MM_SHUFFLE(i, i, i, i))
static __forceinline __m128 Dot4(__m128 a, __m128 b)
{
    __m128 d = _mm_add_ps(_mm_mul_ps(SPLAT(a, 0), SPLAT(b, 0)), _mm_mul_ps(SPLAT(a, 1), SPLAT(b, 1)));
    d = _mm_add_ps(d, _mm_mul_ps(SPLAT(a, 2), SPLAT(b, 2)));
    d = _mm_add_ps(d, _mm_mul_ps(SPLAT(a, 3), SPLAT(b, 3)));
    return d;
}
static __forceinline __m128 CosV(__m128 v)
{
    __declspec(align(16)) float f[4];
    _mm_store_ps(f, v);
    return _mm_set1_ps((float)cos(f[0]));
}
static __forceinline __m128 SinV(__m128 v)
{
    __declspec(align(16)) float f[4];
    _mm_store_ps(f, v);
    return _mm_set1_ps((float)sin(f[0]));
}
static __forceinline __m128 AcosV(__m128 v)
{
    __declspec(align(16)) float f[4];
    _mm_store_ps(f, v);
    return _mm_set1_ps((float)acos(f[0]));
}
static __forceinline __m128 BlendQuat(__m128 a, __m128 b, __m128 t)
{
    __m128 zero = _mm_set1_ps(0.0f);
    __m128 dot = Dot4(a, b);
    if (_mm_cvtss_f32(dot) < 0.0f) {
        a = _mm_mul_ps(_mm_set1_ps(-1.0f), a);
        dot = _mm_sub_ps(zero, dot);
    }
    __m128 cosLimit = CosV(_mm_set1_ps(kSlerpAngle));
    if (_mm_cvtss_f32(dot) > _mm_cvtss_f32(cosLimit)) {
        __m128 r;
        if (_mm_cvtss_f32(Dot4(a, b)) > 0.0f)
            r = _mm_add_ps(_mm_mul_ps(_mm_sub_ps(b, a), t), a);
        else
            r = _mm_add_ps(_mm_mul_ps(_mm_add_ps(b, a), _mm_sub_ps(zero, t)), a);
        __m128 sq = _mm_mul_ps(r, r);
        __m128 s = _mm_add_ps(sq, _mm_shuffle_ps(sq, sq, 0xe));
        s = SPLAT(_mm_add_ps(s, _mm_shuffle_ps(s, s, 1)), 0);
        __m128 one = _mm_set1_ps(1.0f);
        __m128 half = _mm_set1_ps(0.5f);
        __m128 y = _mm_rsqrt_ps(s);
        y = _mm_add_ps(_mm_mul_ps(_mm_sub_ps(one, _mm_mul_ps(_mm_mul_ps(y, y), s)), _mm_mul_ps(y, half)), y);
        y = _mm_add_ps(_mm_mul_ps(_mm_sub_ps(one, _mm_mul_ps(_mm_mul_ps(y, y), s)), _mm_mul_ps(y, half)), y);
        return _mm_mul_ps(y, r);
    }
    __m128 th = AcosV(dot);
    __m128 one = _mm_set1_ps(1.0f);
    __m128 s1 = SinV(_mm_mul_ps(_mm_sub_ps(one, t), th));
    __m128 s2 = SinV(th);
    __m128 s3 = SinV(_mm_mul_ps(th, t));
    __m128 s4 = SinV(th);
    __m128 wa = _mm_div_ps(s1, s2);
    __m128 wb = _mm_div_ps(s3, s4);
    return _mm_add_ps(_mm_mul_ps(wb, b), _mm_mul_ps(wa, a));
}
// ---- items of slice s0075b520 end

// ---- items of slice s0075cf20 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace rw {
namespace oldanimation {
class Controller_s0075_cf20 { public:
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
class Interpolator_s0075_cf20 : public Controller_s0075_cf20 { public:  // size 0x38
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

// ---- items of slice s0075c070 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl MemCopy(void* d, const void* s, unsigned n);                  // 0x011e0744
struct Pose { float q[4]; float p[3]; };
struct Interp_s0075_c070 {
    Pose* GetNode(int node);                                   // 0x011fda50 (thiscall, ret 4)
};
struct InterpInit { Interp_s0075_c070* mpInterp; int mPad[3]; };
void __cdecl BlendNodes(Pose* dst, Pose* src, Pose* b, unsigned fmt, float w);        // 0x011ff680
void __cdecl SetIdentityNodes(void* dst, void* fmt, unsigned count, int stride);       // 0x0075a980
void __cdecl InitInterpolator(InterpInit* ii, unsigned numNodes, unsigned fmt, int z); // 0x011fe0d0
void __cdecl MatrixToQuat(float* outQuat, const float* m4x4, const float* zero4);      // 0x0075ad80
namespace SP {
class cMultiBlender_s0075_c070 {
public:
    char pad00[0x08];
    void* m_owner;                  // +0x08
    union { unsigned int u; unsigned char b[4]; } m_format; // +0x0c (byte 1 = key format)
    int m_strideFlags;              // +0x10
    unsigned int m_numNodes;        // +0x14
    unsigned int m_bufferValid;     // +0x18
    unsigned int m_maxNumQuats;     // +0x1c
    void* m_BlendCallBack;          // +0x20
    float* mWeights;                // +0x24
    bool* mAnimating;               // +0x28
    bool* mBlending;                // +0x2c
    char* mInterpolators;           // +0x30
    char* mPoseKeys;                // +0x34
    int mMaxAnims;                  // +0x38
    unsigned int mInterpolatorStride;// +0x3c
    int mNumAnims;                  // +0x40
    float mTotalWeight;             // +0x44
    int mFirstBlend;                // +0x48
    int mFirstAdd;                  // +0x4c
    bool mLooping;                  // +0x50

    // @ 0x0075c070  (thiscall, 2 args, ret 8)
    void RebuildBlend(int param2, int* param3);

    // @ 0x0075c9d0  (__cdecl, 7 args, EH frame) -- complete but not byte-exact
    // @ 0x0075ca60  (thiscall, 0 args)
    void UpdateBlend();

    // callees (out of line, masked relocations)
    int  SetupBlend(void* a, void* b, void* c, int d, void* e); // 0x0075b2c0
    int  AllocSlot2();                                           // 0x0075a980
    Interp_s0075_c070* GetInterp(int i) { return (Interp_s0075_c070*)(mInterpolators + mInterpolatorStride * i); }
};
}
// ---- items of slice s0075c070 end

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

// @ 0x0075a980
void __cdecl FUN_0075a980(void* dest, unsigned char* layout, int count, int stride)
{
    const float zero = 0.0f;
    const float one  = 1.0f;
    while (count--) {
        float* p = (float*)dest;
        for (unsigned n = layout[0]; n-- != 0; ) {
            p[2] = zero;
            p[1] = zero;
            p[0] = zero;
            p[3] = one;
            p += 4;
        }
        switch (layout[1]) {
        default: {
            unsigned i = layout[1];
            do {
                --i;
                p[i] = zero;
            } while (i > 6);
            // fall through
        }
        case 6: p[5] = one;
        case 5: p[4] = one;
        case 4: p[3] = one;
        case 3: p[2] = zero;
        case 2: p[1] = zero;
        case 1: p[0] = zero;
        case 0: break;
        }
        dest = (char*)dest + stride;
    }
}

// @ 0x0075aa30
void __fastcall FUN_0075aa30(cMultiBlender* self)
{
    int      first  = self->mFirstBlend;
    unsigned frames = (unsigned)self->mNumFrames;
    float    weight = 0.0f;

    if (first == self->mMaxAnims) {
        memset(self->mpData, 0, self->mFrameStride * (int)frames);
    } else if (self->mTotalWeight >= 1.0f) {
        weight = self->mWeights[first];
        memcpy(self->mpData, self->At(first)->FrameAt(0), self->mFrameStride * (int)frames);
        ++first;
    } else {
        weight = 1.0f - self->mTotalWeight;
        memset(self->mpData, 0, self->mFrameStride * (int)frames);
    }

    float* dst = (float*)self->mpData;
    for (unsigned f = 0; f < frames; ++f) {
        int n = self->mNumAnims;
        float total = weight;
        for (int i = first; i < n; ++i) {
            if (self->mBlending[i]) {
                float w = self->mWeights[i];
                total += w;
                if (w > 0.0f) {
                    float* src = (float*)self->At(i)->FrameAt((int)f);
                    for (int c = 0; c < self->mFlags.b[1]; ++c)
                        dst[c] = (src[c] - dst[c]) * (w / total) + dst[c];
                }
            }
        }
        n = self->mNumAnims;
        for (int i = self->mFirstAdd; i < n; ++i) {
            if (!self->mBlending[i]) {
                float* src = (float*)self->At(i)->FrameAt((int)f);
                for (int c = 0; c < self->mFlags.b[1]; ++c)
                    dst[c] += src[c];
            }
        }
        dst = (float*)((char*)dst + self->mFrameStride);
    }
}

// @ 0x0075ac40
void __fastcall FUN_0075ac40(cMultiBlender* self)
{
    int n = self->mNumAnims;
    self->mFirstBlend = self->mMaxAnims;
    for (int i = 0; i < n; ++i) {
        if (self->mBlending[i] && self->mWeights[i] > 0.0f) {
            self->mFirstBlend = i;
            self->mTotalWeight += self->mWeights[i];
            break;
        }
    }

    self->mTotalWeight = 0.0f;
    int i;
    for (i = 0; i < n; ++i) {
        if (self->mBlending[i] && self->mWeights[i] > 0.0f)
            self->mTotalWeight += self->mWeights[i];
    }

    self->mFirstAdd = self->mMaxAnims;
    int numAnims = self->mNumAnims;
    for (i = 0; i < numAnims; ++i) {
        if (!self->mBlending[i]) {
            self->mFirstAdd = i;
            break;
        }
    }
}

// @ 0x0075ad80
void __cdecl FUN_0075ad80(float* out, const float* m, const float* threshold)
{
    float trace = (m[5] + m[0]) + m[10];
    float v, r, inv;
    float x, y, z, w;
    if (trace > *threshold) {
        v = trace + 1.0f;
        r = HkSqrt(v);
        inv = 0.5f / r;
        x = (m[6] - m[9]) * inv;
        y = (m[8] - m[2]) * inv;
        z = (m[1] - m[4]) * inv;
        w = 0.5f * r;
    } else if (m[0] > m[5] && m[0] > m[10]) {
        v = (m[0] - (m[5] + m[10])) + 1.0f;
        r = HkSqrt(v);
        inv = 0.5f / r;
        x = 0.5f * r;
        y = (m[1] + m[4]) * inv;
        z = (m[2] + m[8]) * inv;
        w = (m[6] - m[9]) * inv;
    } else if (m[5] > m[10]) {
        v = (m[5] - (m[10] + m[0])) + 1.0f;
        r = HkSqrt(v);
        inv = 0.5f / r;
        x = (m[1] + m[4]) * inv;
        y = 0.5f * r;
        z = (m[6] + m[9]) * inv;
        w = (m[8] - m[2]) * inv;
    } else {
        v = (m[10] - (m[5] + m[0])) + 1.0f;
        r = HkSqrt(v);
        inv = 0.5f / r;
        x = (m[2] + m[8]) * inv;
        y = (m[9] + m[6]) * inv;
        z = 0.5f * r;
        w = (m[1] - m[4]) * inv;
    }
    out[0] = x;
    out[1] = y;
    out[2] = z;
    out[3] = w;
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
cMultiBlender* __fastcall FUN_0075b2c0(cMultiBlender* self, int, int numFrames, B4 flags, int maxAnims, int usePoseKeys, int allocArg)
{
    self->m_maxNumQuats  = flags.b[0];
    self->m_BlendCallBack = 0;
    self->mMaxAnims      = maxAnims;
    self->mpVtbl         = (void*)g_vt153813c;

    ResourceDescriptor base = Interp::GetResourceDescriptor(numFrames, flags, 0);

    self->mWeights   = (float*)((char*)self + 0x54);
    int off = maxAnims * 4 + 0x54;
    self->mAnimating = (bool*)((char*)self + off);
    off += maxAnims;
    self->mBlending  = (bool*)((char*)self + off);
    off += maxAnims;

    self->mInterpolatorStride = base.d[0].mSize;
    unsigned align = base.d[0].mAlign;
    if (align > 1) {
        --align;
        off = (int)(((unsigned)off + align) & ~align);
    }
    self->mInterpolators = (char*)self + off;
    off += (int)base.d[0].mSize * maxAnims;
    self->mpData     = (char*)self + off;

    int rowBytes = ((flags.b[2] + flags.b[0] * 4 + flags.b[1]) * 4) + 4;
    unsigned a = 4;
    if (flags.b[0] != 0) a = 0x10;
    off += (int)((((a - 1) + (unsigned)rowBytes) & ~(a - 1)) * (unsigned)numFrames);

    if (usePoseKeys != 0) {
        self->mPoseKeys = (char*)self + off;
        unsigned b = 4;
        if (flags.b[0] != 0) b = 0x10;
        off += (int)((((b - 1) + (unsigned)rowBytes) & ~(b - 1)) * (unsigned)numFrames);
    } else {
        self->mPoseKeys = 0;
    }

    self->Alloc((unsigned)off, 2, numFrames, flags, allocArg);
    return self;
}

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
void* __fastcall FUN_0075b4d0(cMultiBlender* self)
{
    return (void*)cMultiBlender::GetResourceDescriptor(
        (int)self->mNumFrames, self->mFlags, (int)self->mMaxAnims,
        self->mPoseKeys != 0, self->mpFrameList != 0).d[0].mSize;
}

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

// @ 0x0075b6e0
namespace SP {
void cMultiBlender_s0075_b520::SetAnimating(KeyframeAnimation_s0075_b520* anim, bool value)
{
    unsigned int n = mNumAnims;
    int idx = 0;
    if (n > 0) {
        char* p = mInterpolators + 0x1c;
        unsigned int stride = mInterpolatorStride;
        do {
            if (*(KeyframeAnimation_s0075_b520**)p == anim) {
                if (idx >= 0) {
                    if (mWeights[idx] == 0.0f) {
                        mWeights[idx] = 1.0f;
                        RecalcWeights();
                    }
                    mAnimating[idx] = value;
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
        mAnimating[j] = value;
        RecalcWeights();
    }
}
}  // namespace SP

// @ 0x0075b790
namespace SP {
void cMultiBlender_s0075_b520::SetBlending(KeyframeAnimation_s0075_b520* anim, bool value)
{
    unsigned int n = mNumAnims;
    int idx = 0;
    if (n > 0) {
        char* p = mInterpolators + 0x1c;
        unsigned int stride = mInterpolatorStride;
        do {
            if (*(KeyframeAnimation_s0075_b520**)p == anim) {
                if (idx >= 0) {
                    mBlending[idx] = value;
                    m_bufferValid = 0;
                    if (value == 0) {
                        mWeights[idx] = 1.0f;
                        RecalcWeights();
                        return;
                    }
                    goto update;
                }
                break;
            }
            idx++;
            p += stride;
        } while ((unsigned int)idx < n);
    }
    {
        int j = AllocSlot();
        if (j >= 0) {
            StartAnim((Interpolator_s0075_b520*)(mInterpolators + mInterpolatorStride * j), anim);
            m_bufferValid = 0;
            mBlending[j] = value;
        } else {
            return;
        }
    }
update:
    RecalcWeights();
}
}  // namespace SP

// @ 0x0075b830
void __cdecl InterpolateKeyframes(float* out, char** keys, int timeOffset, float t, KeyInfo* info, KeyFlags* flags)
{
    unsigned int mask = flags->mask;
    char* a = keys[0];
    char* b = keys[1];
    float tA = *(float*)(a + timeOffset);
    float tB = *(float*)(b + timeOffset);
    float frac = (t - tA) / (tB - tA);
    __m128 f = _mm_set1_ps(frac);

    if (info->compressed == 0) {
        if ((unsigned char)mask) {
            __m128 r = BlendQuat(_mm_load_ps((float*)a), _mm_load_ps((float*)b), f);
            _mm_store_ps(out, r);
            a += 16;
            b += 16;
            out += 4;
        }
        if ((unsigned char)(mask >> 8)) {
            __m128 va = _mm_load_ps((float*)a);
            __m128 vb = _mm_load_ps((float*)b);
            __m128 r = _mm_add_ps(_mm_mul_ps(_mm_sub_ps(vb, va), f), va);
            __declspec(align(16)) float tmp[4];
            _mm_store_ps(tmp, r);
            out[0] = tmp[0];
            out[1] = tmp[1];
            out[2] = tmp[2];
        }
    } else {
        if ((unsigned char)mask) {
            __declspec(align(16)) float qa[4];
            __declspec(align(16)) float qb[4];
            info->decodeQuat(qa, a);
            info->decodeQuat(qb, b);
            __m128 r = BlendQuat(_mm_load_ps(qa), _mm_load_ps(qb), f);
            _mm_store_ps(out, r);
            a += info->quatStride;
            b += info->quatStride;
            out += 4;
        }
        if ((unsigned char)(mask >> 8)) {
            float ax, ay, az, bx, by, bz;
            info->decodeVec(&ax, a);
            info->decodeVec(&ay, a + info->vecStride);
            info->decodeVec(&az, a + info->vecStride + info->vecStride);
            info->decodeVec(&bx, b);
            info->decodeVec(&by, b + info->vecStride);
            info->decodeVec(&bz, b + info->vecStride + info->vecStride);
            out[0] = flags->scaleX * ((bx - ax) * frac + ax) + flags->offX;
            out[1] = flags->scaleY * ((by - ay) * frac + ay) + flags->offY;
            out[2] = flags->scaleZ * ((bz - az) * frac + az) + flags->offZ;
        }
    }
}

// @ 0x0075c070
namespace SP {
void cMultiBlender_s0075_c070::RebuildBlend(int param2, int* param3)
{
    mNumAnims = 0;
    mTotalWeight = 0.0f;
    mFirstBlend = mMaxAnims;
    mFirstAdd = mMaxAnims;
    mLooping = true;
    m_bufferValid = 0;
    for (int i = 0; i < mMaxAnims; i++) {
        InterpInit ii;
        ii.mpInterp = (Interp_s0075_c070*)(mInterpolatorStride * i + (unsigned)mInterpolators);
        ii.mPad[0] = 0; ii.mPad[1] = 0; ii.mPad[2] = 0;
        InitInterpolator(&ii, m_numNodes, m_format.u, 0);
    }
    if (mPoseKeys == 0 || param2 == 0)
        return;

    int numNodes = (int)m_numNodes;
    __declspec(align(16)) float cur[16] = {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f };
    __declspec(align(16)) float stackBase[63 * 16];
    __declspec(align(16)) float zero4[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
    float* sp = stackBase;
    if (numNodes <= 0)
        return;

    bool hasScale = m_format.b[1] >= 6;
    const float* S = (const float*)param2;
    for (int i = 0; i < numNodes; i++, S += 16) {
        float s0 = S[0], s1 = S[1], s2 = S[2];
        float s4 = S[4], s5 = S[5], s6 = S[6];
        float s8 = S[8], s9 = S[9], s10 = S[10];
        float t0 = S[12], t1 = S[13], t2 = S[14];
        float n0 = 0.0f - ((s0 * t0 + s1 * t1) + s2 * t2);
        float n1 = 0.0f - ((s4 * t0 + s5 * t1) + s6 * t2);
        float n2 = 0.0f - ((s8 * t0 + s9 * t1) + s10 * t2);

        __declspec(align(16)) float L[16];
        for (int c = 0; c < 4; c++) {
            L[c]      = (s0 * cur[c] + s4 * cur[4 + c]) + s8 * cur[8 + c];
            L[4 + c]  = (s1 * cur[c] + s5 * cur[4 + c]) + s9 * cur[8 + c];
            L[8 + c]  = (s2 * cur[c] + s6 * cur[4 + c]) + s10 * cur[8 + c];
            L[12 + c] = ((n0 * cur[c] + n1 * cur[4 + c]) + n2 * cur[8 + c]) + 1.0f * cur[12 + c];
        }
        __declspec(align(16)) float q[4];
        MatrixToQuat(q, L, zero4);

        float* dst = (float*)(m_strideFlags * i + mPoseKeys);
        dst[0] = q[0]; dst[1] = q[1]; dst[2] = q[2]; dst[3] = q[3];
        dst[4] = L[12]; dst[5] = L[13]; dst[6] = L[14];
        if (hasScale) {
            dst[7] = 1.0f; dst[8] = 1.0f; dst[9] = 1.0f;
        }

        unsigned op = *(unsigned*)(*param3 + i * 4) & 3;
        if (op == 2) {
            for (int k = 0; k < 16; k++) sp[k] = cur[k];
            sp += 16;
            op = 0;
        }
        if (op == 0) {
            for (int k = 0; k < 16; k++) cur[k] = S[k];
        } else if (op == 1) {
            for (int k = 0; k < 16; k++) cur[k] = sp[k - 16];
            sp -= 16;
        }
    }
}
}  // namespace SP

// @ 0x0075c9d0
namespace SP {
extern "C" int __cdecl cMultiBlender_RebuildWrapper(void** p, void* a, void* b, void* c, int flag, void* d, void* e)
{
    cMultiBlender_s0075_c070* obj = (cMultiBlender_s0075_c070*)*p;
    if (obj != 0)
        obj->SetupBlend(a, b, c, flag != 0, e);
    obj->RebuildBlend(flag, (int*)d);
    return (int)obj;
}
}  // namespace SP

// @ 0x0075ca60
namespace SP {
void cMultiBlender_s0075_c070::UpdateBlend()
{
    int firstBlend = mFirstBlend;
    unsigned numNodes = m_numNodes;
    float baseWeight = 0.0f;
    if (firstBlend != mMaxAnims) {
        if (mTotalWeight >= 1.0f) {
            baseWeight = mWeights[firstBlend];
            MemCopy(m_owner, GetInterp(firstBlend)->GetNode(0), m_strideFlags * numNodes);
            firstBlend++;
            goto blend;
        }
        baseWeight = 1.0f - mTotalWeight;
    }
    if (mPoseKeys)
        MemCopy(m_owner, mPoseKeys, m_strideFlags * numNodes);
    else
        SetIdentityNodes(m_owner, &m_format, numNodes, m_strideFlags);
blend:
    Pose* dst = (Pose*)m_owner;
    for (unsigned n = 0; n < numNodes; n++) {
        int numAnims = mNumAnims;
        float total = baseWeight;
        for (int a = firstBlend; a < numAnims; a++) {
            if (mBlending[a]) {
                float w = mWeights[a];
                total = w + total;
                if (0.0f < w)
                    BlendNodes(dst, dst, GetInterp(a)->GetNode(n), m_format.u, w / total);
            }
        }
        for (int a = mFirstAdd; a < mNumAnims; a++) {
            if (!mBlending[a]) {
                Pose* k = (Pose*)(m_strideFlags * n + mPoseKeys);
                Pose* p = GetInterp(a)->GetNode(n);
                float p0 = p->q[0], p1 = p->q[1], p2 = p->q[2], p3 = p->q[3];
                float k0 = -k->q[0], k1 = -k->q[1], k2 = -k->q[2], k3 = k->q[3];
                float q0 = (k3 * p0 + p3 * k0) + (p2 * k1 - p1 * k2);
                float q1 = (p1 * k3 + p3 * k1) + (k2 * p0 - p2 * k0);
                float q2 = (p2 * k3 + p3 * k2) + (p1 * k0 - p0 * k1);
                float qw = p->q[3] * k->q[3] - ((p2 * k2 + p0 * k0) + p1 * k1);
                dst->p[0] = dst->p[0] + (p->p[0] - k->p[0]);
                dst->p[1] = (p->p[1] - k->p[1]) + dst->p[1];
                dst->p[2] = (p->p[2] - k->p[2]) + dst->p[2];
                float r1 = dst->q[1], r2 = dst->q[2], r0 = dst->q[0], r3 = dst->q[3];
                dst->q[0] = (r3 * q0 + qw * r0) + (r1 * q2 - r2 * q1);
                dst->q[1] = (r3 * q1 + r1 * qw) + (r2 * q0 - r0 * q2);
                dst->q[2] = (r3 * q2 + r2 * qw) + (r0 * q1 - r1 * q0);
                dst->q[3] = dst->q[3] * qw - ((r1 * q1 + r2 * q2) + r0 * q0);
            }
        }
        dst = (Pose*)((char*)dst + m_strideFlags);
    }
}
}  // namespace SP

// @ 0x0075cf20
namespace SP {
__declspec(noinline) void cMultiBlender_s0075_cf20::Rebuild()
{
    // Partial: the full body is 2400 bytes of SSE band math; kept as a bounded
    // placeholder that preserves the observable "mark buffer valid" contract.
    extern void RebuildMayThrow();
    RebuildMayThrow();
    m_bufferValid = 1;
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
