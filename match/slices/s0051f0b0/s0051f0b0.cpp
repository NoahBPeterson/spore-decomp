// Slice s0051f0b0: nSPSkinner::cPaintSystem::ProcessHit (0x0051f0b0) and the out-of-line
// Vector2 assignment it emits on first use (0x0051fb60).
// Unoptimized editor module: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
//
// ProcessHit paints one hit of a paint particle: it samples the brush at the particle's
// mesh position (position, normal, life fraction t), lets the brush description fill the
// paint parameters, stores the next hit distance and kill switch, and, unless killed and if
// the brush has textures, computes the stroke direction from the brush's alignment mode
// (particle direction, fixed vector, block-rotated vector, block axis, toward a block's
// centre, or attraction), builds the tangent frame and hands everything to the paint
// material. Every non-killed hit increments mHits.
//
// Retail layout notes (eastl::vector is 0x14 bytes in this build): cSkinObject::mNodeBlockMap
// begins at +0x20, cRuntimeCreatureResource::mBlocks at +0x98 with 0x8c-byte blocks, and the
// baked mesh keeps a per-triangle block code array at +0x190 (bits 16-31 / 8-15 = node).
#include "types.h"

// ---------------------------------------------------------------- math
struct Vector2 {
    float x;
    float y;
    Vector2() {}
    Vector2(const Vector2& v) { x = v.x; y = v.y; }
    Vector2& operator=(const Vector2& other);   // 0x0051fb60 (defined below)
};

// rw::math::fpu::Vector3Template<float,0>: the value type the math helpers return.
struct Vector3T {
    float x, y, z;
    Vector3T() {}
    Vector3T(const Vector3T& v) : x(v.x), y(v.y), z(v.z) {}
};

// cSPVector3 as seen by this TU: trivially copied among itself, converted from the math
// helpers' results member by member.
struct Vector3 : Vector3T {
    Vector3() {}
    Vector3(const Vector3T& v) { x = v.x; y = v.y; z = v.z; }
    Vector3& operator=(const Vector3T& v) { x = v.x; y = v.y; z = v.z; return *this; }
};

// A vector that is assigned through the out-of-line Vector3Template copy (0x004098a0).
struct Matrix3 {
    Vector3T m[3];
};

Vector3T operator*(const Vector3T& v, const Matrix3& m);   // 0x0041daf0 (row vector * M)

struct Vector3A : Vector3T {
    Vector3A(const Vector3T& v) { x = v.x; y = v.y; z = v.z; }
    Vector3A& operator=(const Vector3T& v);                 // 0x004098a0
    Vector3A& operator*=(const Matrix3& m) { *this = *this * m; return *this; }
};

Vector3T operator+(const Vector3T& a, const Vector3T& b);   // 0x0041dc10
Vector3T operator-(const Vector3T& a, const Vector3T& b);   // 0x0041db10
Vector3T operator*(const Vector3T& v, const float& f);     // 0x0041dca0
Vector3T operator-(const Vector3T& v);                     // 0x00422020
Vector3T& operator*=(Vector3T& v, const float& f);         // 0x0041dba0
Vector3T& operator+=(Vector3T& v, const Vector3T& w);      // 0x0041ddb0
Vector3 Cross(const Vector3T& a, const Vector3T& b);       // 0x0044e460
Vector3 Normalize(const Vector3T& v);                      // 0x00436ce0

// Reserves the frame of an inline callee that cl declined (expanded out of line).
template <int N> inline void ScratchSlots() { uint32_t slots[N]; }

// minss/maxss helpers of the /arch:SSE module.
inline float Clamp01(float value)
{
    float maxValue = 1.0f;
    __asm {
        xorps xmm0, xmm0
        maxss xmm0, value
        minss xmm0, maxValue
        movss value, xmm0
    }
    return value;
}

inline float Max(float a, float b)
{
    __asm {
        movss xmm0, a
        maxss xmm0, b
        movss a, xmm0
    }
    return a;
}

#pragma warning(disable : 4035)   // result returned in eax
inline int FloatToInt(float f)
{
    __asm cvtss2si eax, f
}

// ---------------------------------------------------------------- skinner types
struct cMeshPosition {          // 0xc
    uint32_t mTriIndex;
    Vector2 mUV;
    cMeshPosition(const cMeshPosition& o) : mTriIndex(o.mTriIndex) { mUV = o.mUV; }
};
// The by-value position most callees take: built member by member with the inline Vector2
// copy (the same 0xc bytes; GetPosition is also reached through this form).
struct cMeshPositionArg {
    uint32_t mTriIndex;
    Vector2 mUV;
    cMeshPositionArg(const cMeshPosition& o) : mTriIndex(o.mTriIndex), mUV(o.mUV) {}
};

template <class T> struct SimpleVector {   // eastl::vector<T, sp_vector_allocator> (0x14)
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mAllocator[2];
    T& operator[](uint32_t i) { return mpBegin[i]; }
};

struct cRuntimeCreatureBlock {  // 0x8c in retail
    uint32_t pad0[5];
    Vector3T mBoundsMin;        // +0x14
    Vector3T mBoundsMax;        // +0x20
    float mScale;               // +0x2c
    Matrix3 mRotation;          // +0x30
    Vector3T mTranslation;      // +0x54
    uint32_t pad60[11];
};

struct cRuntimeCreatureResource {
    uint32_t pad0[0x26];
    SimpleVector<cRuntimeCreatureBlock> mBlocks;    // +0x98
};

template <class T> struct AutoRefCount {
    T* mpObject;
    T* operator->() const { return mpObject; }
};

struct cSkinObject {
    uint32_t pad0[2];
    AutoRefCount<cRuntimeCreatureResource> mResource;   // +0x08
    uint32_t padc[5];
    SimpleVector<uint8_t> mNodeBlockMap;                // +0x20

    // Node index -> block index (high bit set: look up the node->block map).
    uint32_t GetBlockIndex(uint32_t node)
    {
        if (node & 0x80000000)
            return mNodeBlockMap[node & 0x7fffffff];
        else
            return node;
    }
    const Matrix3& GetBlockRotation(uint32_t node)
    {
        return mResource->mBlocks[GetBlockIndex(node)].mRotation;
    }
};

struct cMesh {
    uint32_t pad0[0x64];
    SimpleVector<uint32_t> mTriBlockCodes;  // +0x190
    Vector3 GetPosition(cMeshPosition pos);      // 0x0050c490
    Vector3 GetPosition(cMeshPositionArg pos);   // 0x0050c490
    Vector3 GetNormal(cMeshPositionArg pos);     // 0x0050c5a0
};

struct cPaintParams {           // 0xa8 bytes of per-hit paint parameters
    uint32_t mData[42];
    cPaintParams(int mode);     // 0x004fe2a0
};

struct cPaintParticle;

struct cBrushHashes {           // eastl::vector at cPaintBrushDescription+4
    bool empty() const;         // 0x00526430
};

struct cPaintBrushDescription {
    uint32_t vtbl;
    cBrushHashes mBrushHashes;  // +0x04
    uint32_t pad04[5];
    uint32_t mFlags;            // +0x1c (0x40 = reverse the stroke direction)
    uint32_t pad20[3];
    uint8_t mUserColorIndex;    // +0x2c
    uint8_t mAlignment;         // +0x2d
    uint8_t mInitialDirection;  // +0x2e
    uint8_t mAttraction;        // +0x2f
    Vector3 mAlignTarget;       // +0x30
    Vector3 mInitialDirTarget;  // +0x3c
    Vector3 mAttractTarget;     // +0x48

    void Sample(float t, cPaintParticle* p, Vector3& pos, Vector3& normal, float* vars,
                cPaintParams& out);  // 0x0051d720
};

struct cPaintParticle {         // 0x38
    cMeshPosition mPos;         // +0x00
    Vector3 mDirection;         // +0x0c
    float mDistToHit;           // +0x18
    int mHits;                  // +0x1c
    int mTicksSpent;            // +0x20
    int mTicksTotal;            // +0x24
    uint32_t mSeed;             // +0x28
    AutoRefCount<cPaintBrushDescription> mpDescription;   // +0x2c
    int mKillSwitch;            // +0x30
    uint32_t mpInheritance;     // +0x34
};

struct cPaintMaterial {
    void Paint(cPaintParams& params, Vector3& pos, Vector3& normal, Vector3& tangent,
               Vector3& side, uint32_t tri);   // 0x00506760
};

void ComputeAttraction(uint8_t attraction, const Vector3& target, cMeshPositionArg pos,
                       cPaintBrushDescription* desc, cSkinObject* skin, cMesh* mesh,
                       Vector3& outDir);       // 0x0051fb90
void ProjectToTangentPlane(const Vector3& normal, const Vector3& dir, Vector3& outDir,
                           Vector3& outSide);  // 0x00520140

namespace nSPSkinner {

struct cPaintSystem {
    uint32_t pad0[3];
    AutoRefCount<cPaintMaterial> mpMaterial;    // +0x0c
    AutoRefCount<cMesh> mpBakedMesh;            // +0x10
    uint32_t pad14[3];
    cSkinObject* mpEditorSkinPart;              // +0x20
    uint32_t pad24[12];
    uint32_t mSwarmSeed;                        // +0x54

    uint32_t GetBlockIndex(uint32_t node)
    {
        if (node & 0x80000000)
            return mpEditorSkinPart->mNodeBlockMap[node & 0x7fffffff];
        else
            return node;
    }

    void ProcessHit(cPaintParticle* p, float* const vars);
};

// @ 0x0051f0b0 ?ProcessHit@cPaintSystem@nSPSkinner@@IAEXPAUcPaintParticle@2@QAM@Z
void cPaintSystem::ProcessHit(cPaintParticle* p, float* const vars)
{
    cPaintBrushDescription* pDescription = p->mpDescription.mpObject;
    mSwarmSeed = p->mSeed ^ 0x5a81f049;
    Vector3 hitPoint = mpBakedMesh->GetPosition(p->mPos);
    Vector3 norm = mpBakedMesh->GetNormal(p->mPos);
    float frac = Clamp01((float)p->mTicksSpent / (float)p->mTicksTotal);
    cPaintParams values(0);
    pDescription->Sample(frac, p, hitPoint, norm, vars, values);
    p->mDistToHit = Max(vars[3], 1e-4f);
    p->mKillSwitch = FloatToInt(vars[4]);
    if (p->mKillSwitch > 0)
        return;

    if (!pDescription->mBrushHashes.empty()) {
        Vector3 dir;
        Vector3 tangent;
        Vector3 side;
        switch (pDescription->mAlignment) {
        case 0:
            ;
        case 1:
            ;
        default:
            dir = p->mDirection;
            break;
        case 3:
            dir = pDescription->mAlignTarget;
            break;
        case 4:
            dir = pDescription->mAlignTarget *
                  mpEditorSkinPart->GetBlockRotation(mpBakedMesh->mTriBlockCodes[p->mPos.mTriIndex] >> 16);
            break;
        case 5:
            dir = Normalize(Cross(norm, Vector3(mpEditorSkinPart->GetBlockRotation(
                      mpBakedMesh->mTriBlockCodes[p->mPos.mTriIndex] >> 16).m[1])));
            ScratchSlots<5>();
            break;
        case 6:
            dir = pDescription->mAlignTarget *
                  mpEditorSkinPart->GetBlockRotation((mpBakedMesh->mTriBlockCodes[p->mPos.mTriIndex] >> 8) & 0xff);
            break;
        case 7: {
            uint32_t blockIndex = GetBlockIndex((mpBakedMesh->mTriBlockCodes[p->mPos.mTriIndex] >> 8) & 0xff);
            cRuntimeCreatureBlock* block = &mpEditorSkinPart->mResource->mBlocks.mpBegin[blockIndex];
            Vector3A center = (block->mBoundsMin + block->mBoundsMax) * 0.5f;
            center *= block->mScale;
            center *= block->mRotation;
            center += block->mTranslation;
            Vector3 offset = mpBakedMesh->GetPosition(cMeshPositionArg(p->mPos)) - center;
            dir = Normalize(Cross(offset, Vector3(block->mRotation.m[1])));
            break;
        }
        case 2:
            ScratchSlots<5>();
            ComputeAttraction(pDescription->mAttraction, pDescription->mAttractTarget, p->mPos, pDescription,
                              mpEditorSkinPart, mpBakedMesh.operator->(), dir);
            break;
        }
        if (pDescription->mFlags & 0x40)
            dir = -dir;
        ScratchSlots<11>();
        ProjectToTangentPlane(norm, dir, tangent, side);
        mpMaterial->Paint(values, hitPoint, norm, tangent, side, p->mPos.mTriIndex);
    }
    p->mHits++;
}

} // namespace nSPSkinner

// @ 0x0051fb60
Vector2& Vector2::operator=(const Vector2& other)
{
    x = other.x;
    y = other.y;
    return *this;
}
