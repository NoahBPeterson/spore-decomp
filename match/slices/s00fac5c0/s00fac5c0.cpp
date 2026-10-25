// Slice s00fac5c0 -- strand ("ribbon") mesh builder that feeds six cube-face quadtrees.
// FUN_00fac5c0: for every strand of points it builds one quad per segment (tangent frame from
// neighbouring points, miter offset, running texture length) and hands the quad to the
// per-face builder (FUN_00fab2b0), then flushes every face tree.
#include "types.h"
#include <math.h>

extern void FreeArr(void* p);                  // 0x00f47380, operator delete[] (cdecl)

struct Point {                                  // 0x24 bytes
    float x, y, z;                              // +0x0
    float scale;                                // +0xc
    float pad[5];
};

struct Strand {
    uint32_t pad0;
    Point* mpBegin;                             // +0x4
    Point* mpEnd;                               // +0x8
};

// One 0x110-byte element of a face builder's vector (owns a heap block unless it points at its
// inline buffer at +0x10).
struct BuildElem {
    void* mpData;                               // +0x0
    uint32_t pad[3];
    void* mpInline;                             // +0x10
    uint32_t rest[(0x110 - 0x14) / 4];
};

// Per-face accumulator (a 0x14-byte vector of BuildElem); filled by Builder::AddQuad.
struct FaceBuilder {
    BuildElem* mpBegin;
    BuildElem* mpEnd;
    BuildElem* mpCapacity;
    uint32_t mAlloc[2];

    void Init() { mpBegin = 0; mpEnd = 0; mpCapacity = 0; }
    void Destroy()
    {
        BuildElem* last = mpEnd;
        for (BuildElem* p = mpBegin; p < last; ++p) {
            void* d = p->mpData;
            if (d != 0 && d != p->mpInline) FreeArr(d);
        }
        BuildElem* b = mpBegin;
        if (b != 0 && ((int*)b)[-1] != 0) FreeArr(b);
    }
    // 0x00fab2b0: eax = pos[4][3], stack = uv[4][2], alpha[4], info{len, segLen, strand}.
    // (The original passes pos in EAX; here it is the first stack argument.)
    void AddQuad(const float* pos, const float* uv, const float* alpha, const float* info);
};

struct FaceTree {
    char pad[8];
    void Clear();                               // 0x00fb7720
    void Flush(FaceBuilder* b);                 // 0x00fb78f0 (ret 4)
};

// uint32 vector (EASTL sp_vector shape); DoInsertValue inserts before pWhere.
struct SPVectorU32 {
    uint32_t* mpBegin;                          // +0x0
    uint32_t* mpEnd;                            // +0x4
    uint32_t* mpCap;                            // +0x8

    void DoInsertValue(uint32_t* pWhere, const uint32_t& value);   // 0x004558a0
};

struct StrandMesh {
    void** mpVtbl;                              // +0x0
    char pad0[0x118 - 4];                       // +0x4
    FaceTree* mFaces[6];                        // +0x118
    char pad1[0x2b8 - 0x130];
    Strand** mpStrands;                         // +0x2b8
    Strand** mpStrandsEnd;                      // +0x2bc
    Strand** mpStrandsCap;                      // +0x2c0
    char pad2[0x2cc - 0x2c4];                   // +0x2c4
    SPVectorU32 mFree;                          // +0x2cc

    void Build();
    int StrandCount() { return mpStrandsEnd - mpStrands; }
    uint32_t AllocStrandIndex();                // 0x00fa3ba0
    void BuildRibbon(uint32_t index, Strand* p);   // 0x00fabd60
    uint32_t AddStrand(Strand* p);              // 0x00facef0
    void RemoveStrand(uint32_t index);          // 0x00facf20
};

// A vertex vector whose first element owns a count word at [-1] (EASTL allocator).
struct Vertex3DVec {
    void* mpBegin;                              // +0x0
    void* mpEnd;                                // +0x4
    void* mpCap;                                // +0x8

    void CopyUninit(void* pBegin, void* pEnd);  // 0x00b85500
};

// Heap record returned by the mesh's virtual 0xc4 lookup in RemoveStrand.
struct DecalRecord {
    void* mpOwner;                              // +0x0
    Vertex3DVec mVertices;                      // +0x4
};

// One of the six cube-face decal quads reached through the mesh at +0x78 (faces at +0x118).
struct FaceQuad {
    void AddDecal(void* pOwner);                // 0x00fb4a50
    void RemoveDecal(void* pOwner);             // 0x00fb3660
};

struct QuadMesh {
    char pad[0x118];
    FaceQuad* mFaces[6];                        // +0x118
};

// Owner object that pushes its decal onto / off its six face quads.
struct DecalHost {
    char pad0[0x78];                            // +0x0
    QuadMesh* mpMesh;                           // +0x78
    char pad1[0xb8 - 0x7c];                     // +0x7c
    uint32_t mFlags;                            // +0xb8

    void AttachDecal();                         // 0x00facfc0
    void DetachDecal();                         // 0x00fad000
};

// A 0x14-byte face record: face id plus its 2D bounding box.
struct FaceElem {
    uint32_t mFace;                             // +0x0
    float mBox[4];                              // +0x4
};

// 0x14-byte vector element used by the three copy helpers below.
struct BoxElem {
    uint32_t mKey;                              // +0x0
    float mVal[4];                              // +0x4
};

// Deleters take an inline-owned block (count word at [-1]).
void CopyBoxElemsChecked(const BoxElem* pFirst, const BoxElem* pLast, BoxElem* pDst);
void CopyBoxElems(const BoxElem* pFirst, const BoxElem* pLast, BoxElem* pDst);
void CopyBoxElemsBackward(const BoxElem* pFirst, const BoxElem* pLast, BoxElem* pDstEnd);

extern "C" long __cdecl _InterlockedExchangeAdd(volatile long*, long);
#pragma intrinsic(_InterlockedExchangeAdd)

// A three-component vector; rows of the matrix are stored as one of these.
struct Vec3 { float x, y, z; };

// 3x3 float matrix (rw::math::fpu::Matrix33Template<float,0> layout: row major, 9 floats).
// The rows are exposed as vectors because the original assigns whole rows.
struct Matrix33 {
    union {
        float m[9];                             // +0x0
        struct { Vec3 xAxis, yAxis, zAxis; } row;
    };

    void Assign(const Matrix33* pSrc);          // 0x0041cb40
};

// 0x38-byte decal node: flags/stamp, a normal, and a basis that is rebuilt from it.
struct DecalNode {
    uint16_t mFlags;                            // +0x0
    uint16_t mStamp;                            // +0x2
    float mNormal[3];                           // +0x4
    uint32_t mPad;                              // +0x10
    Matrix33 mBasis;                            // +0x14
};

// Owner of a refcounted record and of a counted heap block.
struct DecalOwner {
    void* mpVtbl;                               // +0x0
    char pad0[0x80 - 0x4];                      // +0x4
    void* mpBlock_80;                           // +0x80
    char pad1[0x128 - 0x84];                    // +0x84
    void* mpRef_128;                            // +0x128

    void Destroy();                             // 0x00fad4f0
};

static const float kEps = 1e-8f;

// @ 0x00fac5c0
void StrandMesh::Build()
{
    for (int f = 0; f < 6; ++f) {
        if (mFaces[f] != 0) mFaces[f]->Clear();
    }
    FaceBuilder builders[6];
    { FaceBuilder* q = builders; int c = 5; do { q->Init(); ++q; } while (--c >= 0); }

    for (unsigned s = 0; s < (unsigned)StrandCount(); ++s) {
        if (mpStrands[s] == 0) continue;
        int n = (mpStrands[s]->mpEnd - mpStrands[s]->mpBegin);
        float len = 0.0f;
        float prevPos[3], prevOff[3];
        for (int i = 0; i < n; ++i) {
            float scale = mpStrands[s]->mpBegin[i].scale;
            const Point* cur = &mpStrands[s]->mpBegin[i];
            const Point* prv = cur;
            if (i != 0) prv = &mpStrands[s]->mpBegin[i - 1];
            const Point* nxt = cur;
            if (i != n - 1) nxt = &mpStrands[s]->mpBegin[i + 1];

            // normal before the point: prv x cur
            float a0 = prv->y * cur->z - prv->z * cur->y;
            float a2 = prv->x * cur->y - prv->y * cur->x;
            float a1 = prv->z * cur->x - prv->x * cur->z;
            float ia = 1.0f / sqrtf((a1 * a1 + (a2 * a2 + a0 * a0)) + kEps);
            float na0 = a0 * ia, na1 = a1 * ia, na2 = a2 * ia;
            // normal after the point: cur x nxt
            float b0 = nxt->z * cur->y - nxt->y * cur->z;
            float b1 = nxt->x * cur->z - nxt->z * cur->x;
            float b2 = nxt->y * cur->x - nxt->x * cur->y;
            float ib = 1.0f / sqrtf((b2 * b2 + (b1 * b1 + b0 * b0)) + kEps);

            float dot;
            if (i == 0 || i == n - 1) {
                dot = -1.0f;
            } else {
                float p0 = prv->x - cur->x, p1 = prv->y - cur->y, p2 = prv->z - cur->z;
                float q0 = nxt->x - cur->x, q1 = nxt->y - cur->y, q2 = nxt->z - cur->z;
                dot = (p0 * q0 + (p1 * q1 + p2 * q2)) /
                      (sqrtf(p0 * p0 + (p1 * p1 + p2 * p2)) * sqrtf((q2 * q2 + q1 * q1) + q0 * q0));
                if (dot <= -1.0f) dot = -1.0f;
                if (0.999f <= dot) dot = 0.999f;
            }

            // miter direction
            float m0 = ib * b0 + na0;
            float m1 = b2 * ib + na2;
            float m2 = b1 * ib + na1;
            float ip = 1.0f / sqrtf(cur->x * cur->x + (cur->y * cur->y + cur->z * cur->z));
            float px = (ip * cur->x) * 500.0f;
            float py = (ip * cur->y) * 500.0f;
            float pz = (ip * cur->z) * 500.0f;
            float k = sqrtf(2.0f / (1.0f - dot));
            float im = 1.0f / sqrtf(m2 * m2 + (m1 * m1 + m0 * m0));
            float ox = (((im * m0) * k) * 6.0f) * scale;
            float oy = (((m2 * im) * k) * 6.0f) * scale;
            float oz = (((m1 * im) * k) * 6.0f) * scale;

            if (i > 0) {
                float pos[12], uv[8], alpha[4], info[3];
                pos[0] = prevPos[0] - prevOff[0];
                pos[1] = prevPos[1] - prevOff[1];
                pos[2] = prevPos[2] - prevOff[2];
                pos[3] = prevOff[0] + prevPos[0];
                pos[4] = prevPos[1] + prevOff[1];
                pos[5] = prevPos[2] + prevOff[2];
                pos[6] = ox + px;
                pos[7] = oy + py;
                pos[8] = oz + pz;
                pos[9] = px - ox;
                pos[10] = py - oy;
                pos[11] = pz - oz;
                float dx = px - prevPos[0], dy = py - prevPos[1], dz = pz - prevPos[2];
                float newLen = sqrtf(dz * dz + dy * dy + dx * dx) + len;
                uv[0] = -1.0f; uv[1] = len;
                uv[2] = 1.0f;  uv[3] = len;
                uv[4] = 1.0f;  uv[5] = newLen;
                uv[6] = -1.0f; uv[7] = newLen;
                alpha[0] = alpha[1] = (i == 1) ? 0.0f : 1.0f;
                alpha[2] = alpha[3] = (i == n - 1) ? 0.0f : 1.0f;
                len = newLen;
                info[0] = len;
                info[1] = sqrtf((dz * dz + dy * dy) + dx * dx);
                ((uint32_t*)info)[2] = s;
                builders[0].AddQuad(pos, uv, alpha, info);
            }
            prevPos[0] = px; prevPos[1] = py; prevPos[2] = pz;
            prevOff[0] = ox; prevOff[1] = oy; prevOff[2] = oz;
        }
    }

    for (int f = 0; f < 6; ++f) {
        if (mFaces[f] != 0) mFaces[f]->Flush(&builders[f]);
    }
    for (int k = 5; k >= 0; --k) builders[k].Destroy();
}

// ===========================================================================
// Ribbon-mesh strand slots, decal attachment, SPVector copy helpers and the
// terrain decal basis / teardown helpers.
// ===========================================================================

// rw::graphics-style strand mesh: hand out a strand slot, then build it.
// @ 0x00facef0
uint32_t StrandMesh::AddStrand(Strand* p)
{
    uint32_t index = AllocStrandIndex();
    mpStrands[index] = p;
    BuildRibbon(index, p);
    return index;
}

// Recycle a strand slot: ask the virtual 0xc4 lookup for the record, release its
// vertex vector and the record itself, zero the slot, push the index on the free
// list and rebuild the faces.
// @ 0x00facf20
void StrandMesh::RemoveStrand(uint32_t index)
{
    DecalRecord* p = (*(DecalRecord* (__thiscall*)(StrandMesh*, uint32_t))((char*)mpVtbl + 0xc4))(this, index);
    if (p != 0) {
        p->mVertices.CopyUninit(p->mVertices.mpBegin, p->mVertices.mpEnd);
        void* pBegin = p->mVertices.mpBegin;
        if (pBegin != 0 && ((int*)pBegin)[-1] != 0)
            FreeArr(pBegin);
        FreeArr(p);
    }
    mpStrands[index] = 0;
    if (mFree.mpEnd < mFree.mpCap)
        *mFree.mpEnd++ = index;
    else
        mFree.DoInsertValue(mFree.mpEnd, index);
    Build();
}

// Push this decal onto every face quad, then mark the decal request flag.
// @ 0x00facfc0
void DecalHost::AttachDecal()
{
    FaceQuad** pFace = mpMesh->mFaces;
    FaceQuad** pFaceEnd = pFace + 6;
    do {
        (*pFace)->AddDecal(this);
        ++pFace;
    } while (pFace < pFaceEnd);
    mFlags |= 0x10;
}

// @ 0x00fad000
void DecalHost::DetachDecal()
{
    FaceQuad** pFace = mpMesh->mFaces;
    FaceQuad** pFaceEnd = pFace + 6;
    do {
        if (*pFace != 0)
            (*pFace)->RemoveDecal(this);
        ++pFace;
    } while (pFace < pFaceEnd);
    mFlags &= ~0x10u;
}

// @ 0x00fad040
void CopyBoxElemsChecked(const BoxElem* pFirst, const BoxElem* pLast, BoxElem* pDst)
{
    while (pFirst != pLast) {
        if (pDst != 0) {
            pDst->mKey = pFirst->mKey;
            pDst->mVal[0] = pFirst->mVal[0];
            pDst->mVal[1] = pFirst->mVal[1];
            pDst->mVal[2] = pFirst->mVal[2];
            pDst->mVal[3] = pFirst->mVal[3];
        }
        ++pFirst;
        ++pDst;
    }
}

// @ 0x00fad0a0
void CopyBoxElems(const BoxElem* pFirst, const BoxElem* pLast, BoxElem* pDst)
{
    while (pFirst != pLast) {
        pDst->mKey = pFirst->mKey;
        pDst->mVal[0] = pFirst->mVal[0];
        pDst->mVal[1] = pFirst->mVal[1];
        pDst->mVal[2] = pFirst->mVal[2];
        pDst->mVal[3] = pFirst->mVal[3];
        ++pFirst;
        ++pDst;
    }
}

// @ 0x00fad0f0
void CopyBoxElemsBackward(const BoxElem* pFirst, const BoxElem* pLast, BoxElem* pDstEnd)
{
    while (pFirst != pLast) {
        --pFirst;
        --pDstEnd;
        pDstEnd->mKey = pFirst->mKey;
        pDstEnd->mVal[0] = pFirst->mVal[0];
        pDstEnd->mVal[1] = pFirst->mVal[1];
        pDstEnd->mVal[2] = pFirst->mVal[2];
        pDstEnd->mVal[3] = pFirst->mVal[3];
    }
}

// ===========================================================================
// SP::cTerrainSphereDecal -- per-face bounding boxes.
// ===========================================================================
namespace SP {

struct cTerrainSphereDecal {
    char pad0[0x80];
    FaceElem* mpFaces;                          // +0x80
    FaceElem* mpFacesEnd;                       // +0x84

    bool GetBBoxForFace(uint32_t face, float* pOut);   // 0x00fad140
};

// @ 0x00fad140
bool cTerrainSphereDecal::GetBBoxForFace(uint32_t face, float* pOut)
{
    uint32_t n = (uint32_t)(mpFacesEnd - mpFaces);
    if (n == 0)
        return false;
    uint32_t i = 0;
    do {
        if (mpFaces[i].mFace == face) {
            pOut[0] = mpFaces[i].mBox[0];
            pOut[1] = mpFaces[i].mBox[1];
            pOut[2] = mpFaces[i].mBox[2];
            pOut[3] = mpFaces[i].mBox[3];
            return true;
        }
        ++i;
    } while (i < (uint32_t)(mpFacesEnd - mpFaces));
    return false;
}

} // namespace SP

// Rebuild a decal node's basis from its normal: replace the third row with the
// unit normal and re-derive the two remaining rows from whichever of the first
// two rows is more perpendicular to it.
static Vec3 CrossVec(Vec3 a, Vec3 b)
{
    Vec3 r;
    r.x = a.y * b.z - a.z * b.y;
    r.y = a.z * b.x - a.x * b.z;
    r.z = a.x * b.y - a.y * b.x;
    return r;
}

static Vec3 NormVec(Vec3 v)
{
    float inv = 1.0f / sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
    Vec3 r;
    r.x = v.x * inv;
    r.y = v.y * inv;
    r.z = v.z * inv;
    return r;
}

// @ 0x00fad1d0
void DecalNode_UpdateBasis(DecalNode* pNode)
{
    Matrix33 m;
    m.Assign(&pNode->mBasis);

    Vec3 zAxis;
    zAxis.x = pNode->mNormal[0];
    float invZ = 1.0f / sqrtf(zAxis.x * zAxis.x +
                              pNode->mNormal[2] * pNode->mNormal[2] +
                              pNode->mNormal[1] * pNode->mNormal[1] + 1e-8f);
    zAxis.x = zAxis.x * invZ;
    zAxis.y = pNode->mNormal[1] * invZ;
    zAxis.z = pNode->mNormal[2] * invZ;
    m.row.zAxis = zAxis;

    Vec3 xAxis = m.row.xAxis;
    Vec3 yAxis = m.row.yAxis;

    float dotA = fabsf(xAxis.x * zAxis.x + xAxis.y * zAxis.y + xAxis.z * zAxis.z);
    float dotB = fabsf(yAxis.x * zAxis.x + yAxis.y * zAxis.y + yAxis.z * zAxis.z);

    if (dotB <= dotA) {
        // Rebuild the x row from y x z, then y from z x x.
        xAxis = NormVec(CrossVec(yAxis, zAxis));
        m.row.xAxis = xAxis;
        yAxis = CrossVec(zAxis, xAxis);
        m.row.yAxis = yAxis;
    } else {
        // Rebuild the y row from z x x, then x from y x z.
        yAxis = NormVec(CrossVec(zAxis, xAxis));
        m.row.yAxis = yAxis;
        xAxis = CrossVec(yAxis, zAxis);
        m.row.xAxis = xAxis;
    }

    pNode->mFlags |= 2;
    ++pNode->mStamp;
    pNode->mBasis = m;
}

// @ 0x00fad4f0
void DecalOwner::Destroy()
{
    mpVtbl = (void*)0x1491090;
    if (mpRef_128 != 0) {
        volatile long* pCount = (volatile long*)((char*)mpRef_128 + 8);
        _InterlockedExchangeAdd(pCount, -1);
        long n = _InterlockedExchangeAdd(pCount, 0);
        if (n < 1)
            _InterlockedExchangeAdd(pCount, 1);
        else
            _InterlockedExchangeAdd(pCount, 0);
    }
    if (mpBlock_80 != 0 && ((int*)mpBlock_80)[-1] != 0)
        FreeArr(mpBlock_80);
    mpVtbl = (void*)0x13ef094;
}
