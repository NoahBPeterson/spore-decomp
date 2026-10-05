// Slice s0075b520: SP::cMultiBlender methods (oldanimation blend controller).
// Optimized /O2 region (no frame pointer, ECX = this). Callees and globals are
// masked relocations, so only the call shapes / offsets matter.
#include "types.h"

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

// @ 0x0075b830
// Partial: large x87+SSE rotational/translational spring blend helper. The aligned
// prologue (and esp,-16; sub esp,0x144) and [ebp+8..0x1c] argument loads give a
// __cdecl signature of 6 args returning float*. Reconstructing the 2099 bytes of SSE
// math (rsqrtps Newton refinement, fcos/fsin slerp) is out of scope here; skeleton only.
float* __cdecl cMultiBlender_Blend(float* out, float* src, int index, float t, int* ctx, int info)
{
    return out;
}
