// Slice s0073d6b0 (0x0073d6b0-0x0073e080): SP::cModelInstance pose picking.
// Region: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast (SSE scalar floats, EH frames).
// 0x0073d6b0 GetPoseTransforms is complete (see nonmatching.txt); 0x0073e080 is still partial.
#include "types.h"
#include <xmmintrin.h>

// ---------------------------------------------------------------------------
// SIMD matrix helpers (same inlined math library as slice s00770320).
// ---------------------------------------------------------------------------
struct __declspec(align(16)) Mat4 {
    __m128 r[4];        // rows; rows 0-2 are the 3x3 part, row 3 the translation
    Mat4() {}
    Mat4(const Mat4& o) { r[0] = o.r[0]; r[1] = o.r[1]; r[2] = o.r[2]; r[3] = o.r[3]; }
    Mat4& operator=(const Mat4& o) { r[0] = o.r[0]; r[1] = o.r[1]; r[2] = o.r[2]; r[3] = o.r[3]; return *this; }
};

// Cofactor inverse of the affine matrix m (16 floats, column 3 taken as
// (0,0,0,1)).  Returns false and leaves o untouched when the 3x3 determinant is 0.
static __forceinline bool AffineInverse(Mat4& o, const float* m)
{
    const __m128 Z = _mm_set1_ps(0.0f);
    const __m128 O = _mm_set1_ps(1.0f);
#define E(k) _mm_set1_ps(m[k])
#define MUL _mm_mul_ps
#define SUB _mm_sub_ps
#define ADD _mm_add_ps
    __m128 det = ADD(ADD(MUL(SUB(MUL(E(5), E(10)), MUL(E(6), E(9))), E(0)),
                         MUL(SUB(MUL(E(6), E(8)), MUL(E(10), E(4))), E(1))),
                     MUL(SUB(MUL(E(9), E(4)), MUL(E(5), E(8))), E(2)));
    if (_mm_movemask_ps(_mm_cmpeq_ps(det, Z)) == 0xf)
        return false;

    __m128 i32 = _mm_div_ps(ADD(ADD(MUL(SUB(MUL(E(5), E(2)), MUL(E(6), E(1))), E(12)),
                                    MUL(SUB(MUL(E(6), E(0)), MUL(E(4), E(2))), E(13))),
                                MUL(SUB(MUL(E(4), E(1)), MUL(E(5), E(0))), E(14))), det);
    __m128 i31 = _mm_div_ps(ADD(ADD(MUL(SUB(MUL(E(13), E(2)), MUL(E(14), E(1))), E(8)),
                                    MUL(SUB(MUL(E(14), E(0)), MUL(E(12), E(2))), E(9))),
                                MUL(SUB(MUL(E(12), E(1)), MUL(E(13), E(0))), E(10))), det);
    __m128 i30 = _mm_div_ps(ADD(ADD(MUL(SUB(MUL(E(13), E(10)), MUL(E(9), E(14))), E(4)),
                                    MUL(SUB(MUL(E(14), E(8)), MUL(E(10), E(12))), E(5))),
                                MUL(SUB(MUL(E(9), E(12)), MUL(E(13), E(8))), E(6))), det);
    __m128 i22 = _mm_div_ps(ADD(ADD(MUL(SUB(MUL(E(1), Z), MUL(E(5), Z)), E(12)),
                                    MUL(SUB(MUL(E(5), E(0)), MUL(E(4), E(1))), O)),
                                MUL(SUB(MUL(E(4), Z), MUL(E(0), Z)), E(13))), det);
    __m128 i21 = _mm_div_ps(ADD(ADD(MUL(SUB(MUL(E(1), O), MUL(E(13), Z)), E(8)),
                                    MUL(SUB(MUL(E(13), E(0)), MUL(E(12), E(1))), Z)),
                                MUL(SUB(MUL(E(12), Z), MUL(E(0), O)), E(9))), det);
    __m128 i20 = _mm_div_ps(ADD(ADD(MUL(SUB(MUL(E(13), E(8)), MUL(E(9), E(12))), Z),
                                    MUL(SUB(MUL(E(9), O), MUL(E(13), Z)), E(4))),
                                MUL(SUB(MUL(E(12), Z), MUL(E(8), O)), E(5))), det);
    __m128 i12 = _mm_div_ps(ADD(ADD(MUL(SUB(MUL(E(4), E(2)), MUL(E(6), E(0))), O),
                                    MUL(SUB(MUL(E(0), Z), MUL(E(4), Z)), E(14))),
                                MUL(SUB(MUL(E(6), Z), MUL(E(2), Z)), E(12))), det);
    __m128 i11 = _mm_div_ps(ADD(ADD(MUL(SUB(MUL(E(12), E(2)), MUL(E(14), E(0))), Z),
                                    MUL(SUB(MUL(E(0), O), MUL(E(12), Z)), E(10))),
                                MUL(SUB(MUL(E(14), Z), MUL(E(2), O)), E(8))), det);
    __m128 i10 = _mm_div_ps(ADD(ADD(MUL(SUB(MUL(E(10), E(12)), MUL(E(14), E(8))), Z),
                                    MUL(SUB(MUL(E(8), O), MUL(E(12), Z)), E(6))),
                                MUL(SUB(MUL(E(14), Z), MUL(E(10), O)), E(4))), det);
    __m128 i02 = _mm_div_ps(ADD(ADD(MUL(SUB(MUL(E(2), Z), MUL(E(6), Z)), E(13)),
                                    MUL(SUB(MUL(E(5), Z), MUL(E(1), Z)), E(14))),
                                MUL(SUB(MUL(E(6), E(1)), MUL(E(5), E(2))), O)), det);
    __m128 i01 = _mm_div_ps(ADD(ADD(MUL(SUB(MUL(E(2), O), MUL(E(14), Z)), E(9)),
                                    MUL(SUB(MUL(E(13), Z), MUL(E(1), O)), E(10))),
                                MUL(SUB(MUL(E(14), E(1)), MUL(E(13), E(2))), Z)), det);
    __m128 i00 = _mm_div_ps(ADD(ADD(MUL(SUB(MUL(E(10), O), MUL(E(14), Z)), E(5)),
                                    MUL(SUB(MUL(E(13), Z), MUL(E(9), O)), E(6))),
                                MUL(SUB(MUL(E(9), E(14)), MUL(E(13), E(10))), Z)), det);
#undef E
#undef MUL
#undef SUB
#undef ADD
    o.r[0] = _mm_unpacklo_ps(_mm_unpacklo_ps(i00, i02), _mm_unpacklo_ps(i01, i00));
    o.r[1] = _mm_unpacklo_ps(_mm_unpacklo_ps(i10, i12), _mm_unpacklo_ps(i11, i10));
    o.r[2] = _mm_unpacklo_ps(_mm_unpacklo_ps(i20, i22), _mm_unpacklo_ps(i21, i20));
    o.r[3] = _mm_unpacklo_ps(_mm_unpacklo_ps(i30, i32), _mm_unpacklo_ps(i31, i30));
    return true;
}


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

// Lane k of a vector, read back from a stack copy.
static __forceinline float Lane(__m128 v, int k) { return ((const float*)&v)[k]; }

// SP::cMDBoneTransform: a 3x4 matrix (the transpose of an affine 4x4's first three columns).
struct BoneRow {
    float x, y, z, w;
};
struct cMDBoneTransform {
    BoneRow m[3];
};

// Skinning data reached through the model's material list.
struct cSkinPalette {
    Mat4*        mpMatrices;  // +0x0  per-bone 4x4 (bind) matrices
    unsigned int mnBones;     // +0x4
};

struct cPoseOwner {
    uint32_t      pad0[4];
    cSkinPalette* mpSkin;     // +0x10
};

struct cModelInstance_Pose {
    uint32_t pad0[10];
    cPoseOwner** mpMaterialsBegin;  // +0x28 cModelResourceInfo::mMaterials.mpBegin
    cPoseOwner** mpMaterialsEnd;    // +0x2c
    uint32_t pad30[(0x154 - 0x30) / 4];

    // @ 0x0073d6b0  SP::cModelInstance::GetPoseTransforms
    int GetPoseTransforms(cMDBoneTransform* dst, bool original);

    // @ 0x0073e080  SP::cModelInstance::PickLineWithHit (PDB candidate)
    int PickLineWithHit(uint32_t* pLine, uint32_t* pDir, cSPTransformP* pTransform,
                        float* pOut);
};

// ---------------------------------------------------------------------------
// @ 0x0073d6b0  SP::cModelInstance::GetPoseTransforms  (partial)
// ---------------------------------------------------------------------------
int cModelInstance_Pose::GetPoseTransforms(cMDBoneTransform* dst, bool original)
{
    if (mpMaterialsBegin == mpMaterialsEnd)
        return 0;
    cPoseOwner** materials = mpMaterialsBegin;
    if (!materials[2] || !materials[2]->mpSkin || !materials[2]->mpSkin->mpMatrices)
        return 0;

    for (unsigned int i = 0; i < materials[2]->mpSkin->mnBones; ++i)
    {
        Mat4 m = materials[2]->mpSkin->mpMatrices[i];
        if (!original)
        {
            Mat4 inv;   // left untouched (uninitialized) when the matrix is singular
            AffineInverse(inv, (const float*)&m);
            m = inv;
        }
        // Transposed 3x4 store.
        for (int c = 0; c < 3; ++c)
        {
            BoneRow row;
            row.x = Lane(m.r[0], c);
            row.y = Lane(m.r[1], c);
            row.z = Lane(m.r[2], c);
            row.w = Lane(m.r[3], c);
            dst[i].m[c] = row;
        }
    }
    return materials[2]->mpSkin->mnBones;
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
