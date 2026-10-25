// Slice s0075a550 (batch w2g3, slice 18).
// SP::cMultiBlender (blend controller) plus a neighbouring class (vtable 0x140dab0).
// cMultiBlender layout is taken from the 2008 dev-build PDB (base
// rw::oldanimation::Controller at +0).  Built /O2 /arch:SSE with /EHsc.
#include "../../include/types.h"
#include <intrin.h>
#include <string.h>
#include <xmmintrin.h>

extern "C" void* __cdecl operator_new_graph(unsigned size);
extern "C" void  __cdecl eastl_dealloc(void* p);
extern "C" void  __stdcall FUN_011fda40(int arg);
extern "C" void  __cdecl FUN_011fb220(void* self);
extern "C" void  __cdecl FUN_011fe600(void* self, float v);
extern "C" void  __cdecl FUN_00759880(void* p);
extern "C" void  __cdecl FUN_00759c80(void* p);
extern "C" void  __cdecl RefVector_dtor(void* p);
extern "C" void  __cdecl FUN_0041eb80(void* p);
extern "C" void  __stdcall VecVecInt_dtor(void* b, void* e);
extern "C" void  __cdecl FUN_0071dcc0(void* p);

// ---------------------------------------------------------------------------
// rw::oldanimation::Controller base: field prefix shared by the blender and by
// each interpolator element it owns (+0x00 frame list, +0x04 vfptr, +0x08 data,
// +0x0c per-pose layout word, +0x10 bytes per frame, +0x14 frame count).
// ---------------------------------------------------------------------------
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

// rw::BaseResourceDescriptor: {size, alignment}; its ctor/dtor are out of line so that arrays of
// it go through __ehvec_ctor / __ehvec_dtor as in the original.
struct BaseResourceDescriptor {
    unsigned mSize;
    unsigned mAlign;
    BaseResourceDescriptor();            // 0x006c0fa0
    ~BaseResourceDescriptor();           // 0x00c2e4e0
};
struct ResourceDescriptor { BaseResourceDescriptor d[4]; };

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
            typedef float (__thiscall *VFn)(void*);
            VFn f = *(VFn*)(*(int*)((char*)p + 4) + 0x10);
            sum += f(p) * mWeights[i];
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

// ---------------------------------------------------------------------------
// neighbouring class (vtable 0x140dab0): dtor @ 0x0075a550, New70 @ 0x0075a620
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
// @ 0x0075a550
void ClassX::Dtor() {
    vt0 = (void*)g_vt140dab0;
    vt1 = (void*)g_vt140daac;
    if (p5c && ((int*)p5c)[-1] != 0) eastl_dealloc(p5c);
    ((void(__thiscall*)(void*))FUN_00759880)(sub48);
    VecVecInt_dtor(vec34.mBegin, vec34.mEnd);
    if (vec34.mBegin && ((int*)vec34.mBegin)[-1] != 0) eastl_dealloc(vec34.mBegin);
    ((void(__thiscall*)(void*))FUN_0041eb80)(&vec20);
    ((void(__thiscall*)(void*))FUN_0041eb80)(&vec0);
    vt1 = (void*)g_vt13ef094;
}
// @ 0x0075a620
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

// cMultiBlender::GetResourceDescriptor (static, returns the descriptor by value)
// @ 0x0075b190
ResourceDescriptor cMultiBlender::GetResourceDescriptor(int n, B4 flags, int count, int addA, int addB) {
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

// ---------------------------------------------------------------------------
// @ 0x0075a980   zero/identity fill of a pose row (free function: dest, layout,
//                count, stride), then lay the blending channel of the row out
//                according to layout[1].
// ---------------------------------------------------------------------------
void __cdecl FUN_0075a980(void* dest, unsigned char* layout, int count, int stride) {
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

// ---------------------------------------------------------------------------
// @ 0x0075aa30   build one blend pose into mpData for every frame
// ---------------------------------------------------------------------------
void __fastcall FUN_0075aa30(cMultiBlender* self) {
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

// ---------------------------------------------------------------------------
// @ 0x0075ac40   locate the first blending animation and total its weight, then
//                locate the first additive (non-blending) animation
// ---------------------------------------------------------------------------
void __fastcall FUN_0075ac40(cMultiBlender* self) {
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

// ---------------------------------------------------------------------------
// @ 0x0075ad80   quaternion from a column-major 4x4 rotation matrix, using the
//                usual four-branch trace algorithm and a Newton-refined SSE
//                reciprocal square root for the scale.
// ---------------------------------------------------------------------------
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

void __cdecl FUN_0075ad80(float* out, const float* m, const float* threshold) {
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

// ---------------------------------------------------------------------------
// @ 0x0075b2c0   initialise the blender: lay the weight/flag/interpolator/pose
//                arrays out inside the object and allocate the frame storage
// ---------------------------------------------------------------------------
extern int g_vt153813c[];
cMultiBlender* __fastcall FUN_0075b2c0(cMultiBlender* self, int, int numFrames, B4 flags,
                                      int maxAnims, int usePoseKeys, int allocArg) {
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

// ---------------------------------------------------------------------------
// @ 0x0075b4d0   size of the storage this blender needs
// ---------------------------------------------------------------------------
void* __fastcall FUN_0075b4d0(cMultiBlender* self) {
    return (void*)cMultiBlender::GetResourceDescriptor(
        (int)self->mNumFrames, self->mFlags, (int)self->mMaxAnims,
        self->mPoseKeys != 0, self->mpFrameList != 0).d[0].mSize;
}
