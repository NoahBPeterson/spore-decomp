// Slice s0075c070: SP::cMultiBlender serialization/rebuild helpers.
// Optimized /O2, SSE (/arch:SSE2) with 16-byte aligned frames.
// 0075c070 and 0075ca60 are very large (0x11d4 / 0xa4 frames, quaternion + blend
// bookkeeping); only signature skeletons are emitted for those (see partial.txt).
#include "types.h"

namespace rw { namespace oldanimation {
struct Node { float m[16]; };
}}

namespace SP {

using namespace rw::oldanimation;

class cMultiBlender {
public:
    char pad00[0x08];
    void* m_owner;                  // +0x08
    char pad0c[0x04];
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

    // @ 0x0075c070  (thiscall, 2 args, ret 8) -- partial skeleton
    void RebuildBlend(int param2, int* param3);

    // @ 0x0075c9d0  (__cdecl, 7 args, EH frame) -- complete but not byte-exact
    // @ 0x0075ca60  (thiscall, 0 args) -- partial skeleton
    void UpdateBlend();

    // callees (out of line, masked relocations)
    int  SetupBlend(void* a, void* b, void* c, int d, void* e); // 0x0075b2c0
    int  AllocSlot2();                                           // 0x0075a980
};

// @ 0x0075c070
void cMultiBlender::RebuildBlend(int param2, int* param3)
{
    // Skeleton: 2099 bytes of identity-matrix build + per-node SSE transform
    // (FUN_0075ad80) and a 4-way switch on *(param3) & 3 (store/load/restore of a
    // 16-float band). Not reconstructed.
    (void)param2; (void)param3;
}

// @ 0x0075c9d0
// __cdecl wrapper: p is a handle-to-pointer; if non-null it sets up the blend
// source, then always runs the big RebuildBlend(flag5, arg6). SEH state spans the
// first call (local object), hence the EH prolog. Behaviorally complete.
extern "C" int __cdecl cMultiBlender_RebuildWrapper(void** p, void* a, void* b, void* c,
                                                    int flag, void* d, void* e)
{
    cMultiBlender* obj = (cMultiBlender*)*p;
    if (obj != 0)
        obj->SetupBlend(a, b, c, flag != 0, e);
    obj->RebuildBlend(flag, (int*)d);
    return (int)obj;
}

// @ 0x0075ca60
void cMultiBlender::UpdateBlend()
{
    // Skeleton: blend-weight normalization + quaternion conjugate/multiply over the
    // node array. Not reconstructed.
}

} // namespace SP
