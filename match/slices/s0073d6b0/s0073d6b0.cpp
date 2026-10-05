// Slice s0073d6b0 (0x0073d6b0-0x0073e080): SP::cModelInstance pose picking.
// Region: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast (SSE scalar floats, EH frames).
#include "types.h"

// External callees (masked relocations).
extern "C" int   FUN_01201660();                       // 0x1201660
extern "C" int   FUN_012016d0();                       // 0x12016d0
extern "C" void  FUN_0073a6e0();                       // 0x73a6e0
extern "C" void  FUN_006c1c80();                       // 0x6c1c80

struct cSPTransformP {
    uint16_t mFlags;
    uint16_t mModificationCount;
    float    mTranslation[3];
    float    mScale;
    float    mRotation[9];
};

struct cModelInstance_Pose {
    char pad[0x154];

    // @ 0x0073d6b0  SP::cModelInstance::GetPoseTransforms
    int GetPoseTransforms(int param_2, char param_3);

    // @ 0x0073e080  SP::cModelInstance::PickLineWithHit (PDB candidate)
    int PickLineWithHit(uint32_t* pLine, uint32_t* pDir, cSPTransformP* pTransform,
                        float* pOut);
};

// ---------------------------------------------------------------------------
// @ 0x0073d6b0  SP::cModelInstance::GetPoseTransforms  (partial)
// ---------------------------------------------------------------------------
int cModelInstance_Pose::GetPoseTransforms(int param_2, char param_3)
{
    // Partial: the skinned-pose matrix composition (per-bone transform walk) is not
    // yet recovered.  See partial.txt.
    (void)param_2;
    (void)param_3;
    return 0;
}

// ---------------------------------------------------------------------------
// @ 0x0073e080  SP::cModelInstance::PickLineWithHit  (partial)
// ---------------------------------------------------------------------------
int cModelInstance_Pose::PickLineWithHit(uint32_t* pLine, uint32_t* pDir,
                                         cSPTransformP* pTransform, float* pOut)
{
    // Partial: ray/transform setup reproduced; the KD-tree traversal is omitted.
    if (*(int*)((char*)this + 0xcc) == 0)
        return 0;
    (void)pLine; (void)pDir; (void)pTransform; (void)pOut;
    return 0;
}
