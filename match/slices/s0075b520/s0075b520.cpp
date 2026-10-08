// Slice s0075b520: SP::cMultiBlender methods (oldanimation blend controller).
// Optimized /O2 region (no frame pointer, ECX = this). Callees and globals are
// masked relocations, so only the call shapes / offsets matter.
#include "types.h"
#include <xmmintrin.h>
extern "C" double __cdecl cos(double);
extern "C" double __cdecl sin(double);
extern "C" double __cdecl acos(double);
#pragma intrinsic(cos, sin, acos)

// ------------------------------------------------------------------ oldanimation
namespace rw { namespace oldanimation {

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

struct Controller {                     // size 0x1c
    void* m_remapDataPtr;               // +0x00
    ControllerVTable* m_vTable;         // +0x04
    char* m_outputPtr;                  // +0x08
    unsigned int m_outputFormat;        // +0x0c
    unsigned int m_maxNodeSize;         // +0x10
    unsigned int m_numNodes;            // +0x14
    unsigned int m_bufferValid;         // +0x18
};

struct KeyframeAnimation {              // size 0x30 (PDB); only +0x28 is used here
    char pad00[0x28];
    void* m_interpInfoPtr;              // +0x28
    unsigned int m_firstSequenceHeaderPtr; // +0x2c
};

struct Interpolator : Controller {      // size 0x38
    KeyframeAnimation* m_currentAnimPtr; // +0x1c
    float m_currentTime;                 // +0x20
    float m_timeModifier;                // +0x24
    void* m_interpFramesPtr;             // +0x28
    void* m_InterpolateCallBack;         // +0x2c
    void* m_KeyframeSizeCallBack;        // +0x30
    unsigned int m_keyframeTypeID;       // +0x34
    void SetKeyframeType(void* info);    // @ 0x011fdff0
    int SetAnimation(KeyframeAnimation* anim); // @ 0x011fe100
    int SetTime(float t);                // @ 0x011fe600
};

}} // namespace rw::oldanimation

namespace SP {

using namespace rw::oldanimation;

class cMultiBlender : public Controller {   // size 0x54
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
    void StartAnim(Interpolator* interp, KeyframeAnimation* anim); // @ 0x0075b540
    void SetAnimTime(KeyframeAnimation* anim, float time);   // @ 0x0075b5d0
    void SetWeight(KeyframeAnimation* anim, float weight);   // @ 0x0075b630
    void SetAnimating(KeyframeAnimation* anim, bool value);  // @ 0x0075b6e0
    void SetBlending(KeyframeAnimation* anim, bool value);   // @ 0x0075b790
};

// @ 0x0075b520
int cMultiBlender::GetBlendState()
{
    int v = 0;
    if (mNumAnims > v) {
        Interpolator* p = (Interpolator*)mInterpolators;
        int* r = (int*)p->m_remapDataPtr;
        if (r == 0 || *r == 0)
            return ((int (__thiscall*)(void*))p->m_vTable->m_GetOutputNames)(p);
        v = *r;
    }
    return v;
}

// @ 0x0075b540
void cMultiBlender::StartAnim(Interpolator* interp, KeyframeAnimation* anim)
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

// @ 0x0075b5d0
void cMultiBlender::SetAnimTime(KeyframeAnimation* anim, float time)
{
    unsigned int n = mNumAnims;
    int idx = 0;
    if (n > 0) {
        char* p = mInterpolators + 0x1c;
        unsigned int stride = mInterpolatorStride;
        do {
            if (*(KeyframeAnimation**)p == anim) {
                if (idx >= 0) {
                    ((Interpolator*)(mInterpolators + stride * idx))->SetTime(time);
                    m_bufferValid = 0;
                }
                return;
            }
            idx++;
            p += stride;
        } while ((unsigned int)idx < n);
    }
}

// @ 0x0075b630
void cMultiBlender::SetWeight(KeyframeAnimation* anim, float weight)
{
    unsigned int n = mNumAnims;
    int idx = 0;
    if (n > 0) {
        char* p = mInterpolators + 0x1c;
        unsigned int stride = mInterpolatorStride;
        do {
            if (*(KeyframeAnimation**)p == anim) {
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
        StartAnim((Interpolator*)(mInterpolators + mInterpolatorStride * j), anim);
        m_bufferValid = 0;
        mWeights[j] = weight;
        RecalcWeights();
    }
}

// @ 0x0075b6e0
void cMultiBlender::SetAnimating(KeyframeAnimation* anim, bool value)
{
    unsigned int n = mNumAnims;
    int idx = 0;
    if (n > 0) {
        char* p = mInterpolators + 0x1c;
        unsigned int stride = mInterpolatorStride;
        do {
            if (*(KeyframeAnimation**)p == anim) {
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
        StartAnim((Interpolator*)(mInterpolators + mInterpolatorStride * j), anim);
        m_bufferValid = 0;
        mAnimating[j] = value;
        RecalcWeights();
    }
}

// @ 0x0075b790
void cMultiBlender::SetBlending(KeyframeAnimation* anim, bool value)
{
    unsigned int n = mNumAnims;
    int idx = 0;
    if (n > 0) {
        char* p = mInterpolators + 0x1c;
        unsigned int stride = mInterpolatorStride;
        do {
            if (*(KeyframeAnimation**)p == anim) {
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
            StartAnim((Interpolator*)(mInterpolators + mInterpolatorStride * j), anim);
            m_bufferValid = 0;
            mBlending[j] = value;
        } else {
            return;
        }
    }
update:
    RecalcWeights();
}

} // namespace SP

// Keyframe-pair (function at 0x0075b830) interpolation for rw::oldanimation: blends the rotation quaternion (nlerp for
// nearly parallel keys, slerp otherwise) and/or the translation of two keyframes at fraction
// (t - tA) / (tB - tA), appending the results to `out` (16-byte slots). `info` says whether the key
// data is raw floats (info->compressed == 0) or must go through the per-component decoders.
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

extern const float kSlerpAngle;                       // 0x01538360 (5 degrees in radians)

#define SPLAT(v, i) _mm_shuffle_ps((v), (v), _MM_SHUFFLE(i, i, i, i))

static __forceinline __m128 Dot4(__m128 a, __m128 b)
{
    __m128 d = _mm_add_ps(_mm_mul_ps(SPLAT(a, 0), SPLAT(b, 0)), _mm_mul_ps(SPLAT(a, 1), SPLAT(b, 1)));
    d = _mm_add_ps(d, _mm_mul_ps(SPLAT(a, 2), SPLAT(b, 2)));
    d = _mm_add_ps(d, _mm_mul_ps(SPLAT(a, 3), SPLAT(b, 3)));
    return d;
}

// lane-0 transcendental helpers: spill the vector, run the x87 op on its first float, splat the result
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
