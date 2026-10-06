// Slice s00531510: cSPSkinPaintDistributeEffect::ApplyEffect.
// Distributes particle effects over the creature skin mesh: triangles are visited in a
// (seeded) shuffled order, filtered by region flags (bone regions, back/belly normal
// cutoffs, limb weighting, spine range), get the selected particle effects attached at
// their centroid, and then flood-fill a spacing-sized patch of neighbouring triangles as
// "covered". Unoptimized module: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
// Layout notes (retail): cSPSkinPaintDistributeEffect fields as in slice s00530db0;
// cSPSkinPaintDistributeDescription::mParticleSelectIndependent is at +0x50 (vectors are
// 0x14 bytes in this build, the dev PDB says +0x4c).
#include "types.h"

typedef unsigned int size_t;

// ---------------------------------------------------------------- math
struct Vector2 {
    float x, y;
    Vector2() {}
    Vector2(float a, float b) : x(a), y(b) {}
    Vector2(const Vector2& v) : x(v.x), y(v.y) {}
    Vector2& operator=(const Vector2& v);   // 0x0051fb60
};

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float a, float b, float c) : x(a), y(b), z(c) {}
    Vector3(const Vector3& v);              // 0x004098a0
    static const Vector3 ZERO;              // 0x015e12d8
};
struct Matrix3 {
    Vector3 m[3];
};

Vector3 operator+(const Vector3& a, const Vector3& b);          // 0x0041dc10
Vector3 operator-(const Vector3& a, const Vector3& b);          // 0x0041db10
Vector3 operator*(const Vector3& v, const float& f);            // 0x0041dca0
Vector3 operator*(const float& f, const Vector3& v);            // 0x0041de40
Vector3 operator/(const Vector3& v, const float& f);            // 0x00453880
Vector3 operator*(const Vector3& v, const Matrix3& m);          // 0x0041daf0 (row vector * M)
Vector3& operator+=(Vector3& a, const Vector3& b);              // 0x0041ddb0
Vector3& operator*=(Vector3& a, const float& f);                // 0x0041dba0
float LengthSquared(const Vector3& v);                          // 0x00532f80
Vector3 Normalize(const Vector3& v);                            // 0x00436ce0
Vector3 normalized_safe(const Vector3& v);                      // 0x00449c20
void OrthonormalBasis(const Vector3& n, Vector3& right, Vector3& up);   // 0x00520220
Vector2 Barycentric(Vector3 a, Vector3 b, Vector3 c, Vector3 n, Vector3 p);   // 0x00532fe0

inline float Dot(const Vector3& a, const Vector3& b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
extern "C" double fabs(double x);
#pragma intrinsic(fabs)

extern "C" void* memset(void* dst, int c, size_t n);
#pragma intrinsic(memset)

// Swarm transform (only built here, never consumed).
struct Transform {
    uint16_t mFlags;        // +0x00
    uint16_t mChangeCount;  // +0x02
    Vector3 mOffset;        // +0x04
    float mScale;           // +0x10
    Matrix3 mRotation;      // +0x14
    Transform();            // 0x00434040
    void SetRotation(const Matrix3& m)
    {
        mRotation = m;
        mFlags |= 2;
        mChangeCount++;
    }
    void SetOffset(const Vector3& v)
    {
        mOffset = v;
        mFlags |= 4;
        mChangeCount++;
    }
};

// ---------------------------------------------------------------- random
struct RandomLinearCongruential {
    uint32_t mnSeed;
    RandomLinearCongruential(uint32_t seed = 0xffffffff) { SetSeed(seed); }
    void SetSeed(uint32_t seed);              // 0x00936090
    uint32_t RandomUint32Uniform();           // 0x009360b0
    uint32_t RandomUint32Uniform(uint32_t n); // 0x00a68fb0
    double RandomDoubleUniform();             // 0x009360d0
};
extern RandomLinearCongruential sRandom;      // 0x016778dc (Swarm random)

// ---------------------------------------------------------------- eastl-like containers
struct allocator {};

template <class T> void uninitialized_fill_n_ptr(T* p, uint32_t n, const T& value);  // 0x004fc960 / 0x005334d0

struct UIntVectorBase {
    uint32_t* mpBegin;
    uint32_t* mpEnd;
    uint32_t* mpCapacity;
    uint32_t mAlloc[2];
    UIntVectorBase(uint32_t n, const allocator& a);   // 0x004aa350
    UIntVectorBase(const allocator& a);
    ~UIntVectorBase();                                // 0x00425990
};
struct UIntVector : UIntVectorBase {
    UIntVector(const allocator& a = allocator());     // 0x00540470
    explicit UIntVector(uint32_t n, const allocator& a = allocator()) : UIntVectorBase(n, a)
    {
        uninitialized_fill_n_ptr<uint32_t>(mpBegin, n, uint32_t());
        mpEnd = mpBegin + n;
    }
    ~UIntVector()
    {
        for (uint32_t* p = mpBegin; p < mpEnd; ++p) {
        }
    }
    bool empty() const;                     // 0x00526430
    void push_back(const uint32_t& value);  // 0x00454860
    uint32_t& back() { return *(mpEnd - 1); }
    void pop_back() { --mpEnd; }
    uint32_t& operator[](uint32_t i) { return mpBegin[i]; }
};

// Particle id list (other allocator type, own ctor/dtor/push_back instances).
struct IdVectorBase {
    uint32_t* mpBegin;
    uint32_t* mpEnd;
    uint32_t* mpCapacity;
    uint32_t mAlloc[2];
    IdVectorBase();
    ~IdVectorBase();                        // 0x004c0b80
};
struct IdVector : IdVectorBase {
    IdVector();                             // 0x00533360
    ~IdVector()
    {
        for (uint32_t* p = mpBegin; p < mpEnd; ++p) {
        }
    }
    void push_back(const int& value);       // 0x00422380
    int size() const { return (int)(mpEnd - mpBegin); }
};

struct ByteVectorBase {
    uint8_t* mpBegin;
    uint8_t* mpEnd;
    uint8_t* mpCapacity;
    uint32_t mAlloc[2];
    ByteVectorBase(uint32_t n, const allocator& a);   // 0x00423be0
    ByteVectorBase(const allocator& a);
};
struct ByteVector : ByteVectorBase {
    ByteVector(const allocator& a = allocator());     // 0x00540470
    ByteVector(uint32_t n, const uint8_t& value, const allocator& a = allocator()) : ByteVectorBase(n, a)
    {
        uninitialized_fill_n_ptr<uint8_t>(mpBegin, n, value);
        mpEnd = mpBegin + n;
    }
    ~ByteVector();                                    // 0x0041e5d0
    void resize(uint32_t n);                          // 0x004c0410
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    uint8_t& operator[](uint32_t i) { return mpBegin[i]; }
};

struct PairIF {
    int first;
    float second;
};
struct PairVectorBase {
    PairIF* mpBegin;
    PairIF* mpEnd;
    PairIF* mpCapacity;
    uint32_t mAlloc[2];
    PairVectorBase(const allocator& a);
    ~PairVectorBase();                                // 0x0045daf0
};
struct PairVector : PairVectorBase {
    PairVector(const allocator& a = allocator());     // 0x00540470
    ~PairVector()
    {
        for (PairIF* p = mpBegin; p < mpEnd; ++p) {
        }
    }
    bool empty() const;                               // 0x00526430
    PairIF* erase(PairIF* first, PairIF* last);       // 0x00530c80
    void clear() { erase(mpBegin, mpEnd); }
    int size() const { return (int)(mpEnd - mpBegin); }
    PairIF& operator[](int i) { return mpBegin[i]; }
};

// eastl::vector_map<uint32_t, float> (key: bone pointer), sorted by weight below.
struct PairUF {
    uint32_t first;
    float second;
};
struct greater_second {
    bool operator()(const PairUF& a, const PairUF& b) const { return a.second > b.second; }
};
void sort(PairUF* first, PairUF* last, greater_second compare);   // 0x00533680
struct WeightMap {
    PairUF* mpBegin;
    PairUF* mpEnd;
    PairUF* mpCapacity;
    uint32_t mAlloc[2];
    WeightMap();                                      // 0x00533410
    ~WeightMap();                                     // 0x005333d0
    float& operator[](const uint32_t& key);           // 0x00533430
};

struct EAString {
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    uint32_t mAlloc;
    bool empty() const { return mpBegin == mpEnd; }
};

// ---------------------------------------------------------------- skin mesh / rig
struct cTriCoord {
    int mTri;
    Vector2 mBary;
    cTriCoord(int tri) : mTri(tri), mBary(0.33333334f, 0.33333334f) {}
    cTriCoord(const cTriCoord& c) : mTri(c.mTri) { mBary = c.mBary; }
};
struct cTriCoordArg {   // by-value copy with the inline Vector2 copy
    int mTri;
    Vector2 mBary;
    cTriCoordArg(const cTriCoord& c) : mTri(c.mTri), mBary(c.mBary) {}
};

struct cSkinMesh {
    uint32_t pad0[2];
    Vector3* mpPositions;       // +0x08
    uint32_t pad0c[4];
    Vector3* mpNormals;         // +0x1c
    uint32_t pad20[14];
    uint32_t* mpIndices;        // +0x58 (3 position indices per triangle)
    uint32_t* mpIndicesEnd;     // +0x5c
    uint32_t pad60[3];
    uint32_t* mpNormalIndices;  // +0x6c (3 normal indices per triangle)
    uint32_t pad70[9];
    uint32_t* mpAdjacency;      // +0x94 (3 edge ids per triangle, edge/3 = neighbour)
    uint32_t pad98[62];
    uint32_t* mpTriFlags;       // +0x190 (region bits, spine position <<8, bone id <<16)
    Vector3 GetPosition(cTriCoord tc);                  // 0x0050c490
    Vector3 GetPosition(cTriCoordArg tc);               // 0x0050c490
    Vector3 GetTriNormal(uint32_t tri);                 // 0x005121c0
};

struct cBone {   // 0x8c bytes
    uint8_t pad0[0xb];
    uint8_t mType;              // +0x0b (3 = limb, 5 = spine)
    uint32_t pad0c[2];
    Vector3 mStart;             // +0x14
    Vector3 mEnd;               // +0x20
    float mScale;               // +0x2c
    Matrix3 mRotation;          // +0x30
    Vector3 mTranslation;       // +0x54
    uint8_t pad60[0x2c];
};
struct BoneVector {
    cBone* mpBegin;
    cBone* mpEnd;
    int size() const { return (int)(mpEnd - mpBegin); }
};
struct cSkeleton {
    uint32_t pad0[38];
    BoneVector mBones;          // +0x98
};
struct cBoneQuery {
    void FindNearest(const Vector3& pos, PairVector& out);   // 0x004f9570
};
struct cRig {
    uint32_t pad0[2];
    cSkeleton* mpSkeleton;      // +0x08
    uint32_t pad0c[11];
    cBoneQuery* mpQuery;        // +0x38
};
cBone* GetBone(cRig* rig, uint32_t id);   // 0x005332f0

struct cEffectBase0 {
    virtual void b0();
    int mRef;
};
struct cEffectBase1 {
    virtual void c0();
};
struct cParticleEffect : cEffectBase0, cEffectBase1 {
    uint8_t pad[0xb4 - 0xc];
    int mComponentId;           // +0xb4
};
struct cEffectsManager {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
    virtual cParticleEffect* CreateEffect(int kind, int id, int componentId);   // +0x70
};
cEffectsManager* EffectsManager();   // 0x0067ddd0

struct cPaintSystem {
    uint32_t pad0[4];
    cSkinMesh* mpMesh;          // +0x10
    uint32_t pad14[3];
    cRig* mpRig;                // +0x20
    cSkinMesh* GetMesh() { return mpMesh; }
    cRig* GetRig() { return mpRig; }
    void AddParticle(cEffectBase1* effect, cTriCoordArg tc, uint32_t seed);   // 0x005240e0
};
cPaintSystem* GetPaintSystem();      // 0x00401080

// ---------------------------------------------------------------- component
struct cSPSkinPaintDistributeDescription {
    void* vftable;
    int mRefCount;
    EAString mEffect;                   // +0x08
    int mParticleDescId;                // +0x18
    float mSpacing;                     // +0x1c
    uint32_t mLimit;                    // +0x20
    uint32_t mRegionFlags;              // +0x24
    float mBackCutoff;                  // +0x28
    float mBellyCutoff;                 // +0x2c
    Vector2 mSpineRange;                // +0x30
    bool mInvertRegions;                // +0x38
    bool mCenterOnly;                   // +0x39
    bool mExtraCover;                   // +0x3a
    bool mNonRandom;                    // +0x3b
    PairVector mParticleSelect;         // +0x3c
    bool mParticleSelectIndependent;    // +0x50
};

struct VectorAutoRef {
    void** mpBegin;
    void** mpEnd;
    void** mpCapacity;
    uint32_t mAlloc[2];
    bool empty() const;                 // 0x00526430
};

struct cComponentStats;

struct cSPSkinPaintDistributeEffect {
    void* vftable0;
    void* vftable1;
    int mRefCount;
    cSPSkinPaintDistributeDescription* mpDesc;   // +0x0c
    void* mpWorld;                               // +0x10
    int mComponentId;                            // +0x14
    VectorAutoRef mEffectsList;                  // +0x18
    bool mNeedsFirstTick;                        // +0x2c
    void ApplyEffect(float a, float b, cComponentStats* stats);
};

// ---------------------------------------------------------------- @ 0x00531510
void cSPSkinPaintDistributeEffect::ApplyEffect(float a, float b, cComponentStats* stats)
{
    if (!mNeedsFirstTick)
        return;
    mNeedsFirstTick = false;
    if (!mEffectsList.empty())
        return;

    uint32_t limit = mpDesc->mLimit;
    cSkinMesh* mesh = GetPaintSystem()->GetMesh();
    if (mesh == 0)
        return;

    uint32_t numTris = (uint32_t)(mesh->mpIndicesEnd - mesh->mpIndices) / 3;

    // Seeded shuffle of the triangle visiting order.
    RandomLinearCongruential rng;
    rng.SetSeed(sRandom.RandomUint32Uniform() ^ 0x3098a4a3);
    UIntVector order(numTris);
    for (uint32_t i = 0; i < numTris; i++)
        order[i] = i;
    if (!mpDesc->mNonRandom) {
        for (uint32_t i = 0; i < numTris >> 1; i++) {
            uint32_t k = rng.RandomUint32Uniform(numTris - i) + i;
            uint32_t* pk = &order[k];
            uint32_t* pi = &order[i];
            uint32_t tmp = *pi;
            *pi = *pk;
            *pk = tmp;
        }
    }

    bool bUnused = true;
    (void)bUnused;
    ByteVector covered(numTris, (uint8_t)0);   // bit 0: already covered
    cRig* rig = GetPaintSystem()->GetRig();
    cBoneQuery* query = rig->mpQuery;
    int numSpine = -1;
    float spacingSq = mpDesc->mSpacing * mpDesc->mSpacing;
    UIntVector stack;
    ByteVector visited;
    visited.resize(numTris);
    PairVector nearby;

    for (uint32_t i = 0; limit != 0 && i < numTris; i++) {
        uint32_t tri = order[i];
        if (covered[tri] & 1)
            continue;
        if (mesh->mpTriFlags[tri] & 0x40)
            continue;

        cTriCoord tc(tri);
        Vector3 pos = mesh->GetPosition(tc);

        if (mpDesc->mCenterOnly) {
            // Only triangles crossing the symmetry plane (x == 0).
            if ((float)fabs(pos.x) > 0.1f)
                continue;
            Vector3 triNormal = mesh->GetTriNormal(tri);
            Vector3 onPlane(0.0f, pos.y, pos.z);
            Vector3 d = pos - onPlane;
            float t = d.x * triNormal.x + d.y * triNormal.y + d.z * triNormal.z;
            onPlane += triNormal * t;
            const uint32_t* idx = &mesh->mpIndices[tri * 3];
            tc.mBary = Barycentric(mesh->mpPositions[idx[0]], mesh->mpPositions[idx[1]],
                                   mesh->mpPositions[idx[2]], triNormal, onPlane);
            if (0.0f > tc.mBary.x || 0.0f > tc.mBary.y || tc.mBary.x + tc.mBary.y > 1.0f)
                continue;
            if ((float)fabs(mesh->GetPosition(cTriCoordArg(tc)).x) > 0.01f)
                continue;
        }

        if (mpDesc->mRegionFlags != 0xffffffff) {
            bool inRegion = false;
            uint32_t flags = mesh->mpTriFlags[tri] & mpDesc->mRegionFlags;
            if (flags != 0) {
                uint32_t boneId = mesh->mpTriFlags[tri] >> 16;
                cBone* bone = GetBone(rig, boneId);
                if (bone != 0) {
                    if (numSpine == -1) {
                        numSpine = 0;
                        cBone* bones = rig->mpSkeleton->mBones.mpBegin;
                        for (int j = 0, n = rig->mpSkeleton->mBones.size(); j < n; j++) {
                            if (bones[j].mType == 5)
                                numSpine++;
                        }
                    }
                    if (flags & 0x18)
                        flags &= ~1u;
                    if (flags & 7)
                        inRegion = true;

                    if (!inRegion && (flags & 0x18)) {
                        // Back (8) / belly (0x10): compare the bone-weighted outward direction
                        // with the weighted bone up axis.
                        nearby.clear();
                        query->FindNearest(pos, nearby);
                        Vector3 outward(Vector3::ZERO);
                        Vector3 up(Vector3::ZERO);
                        for (int j = 0, n = nearby.size(); j < n; j++) {
                            cBone* nb = GetBone(rig, nearby[j].first);
                            if (nb != 0 && nb->mType == 5) {
                                Vector3 mid = (nb->mStart + nb->mEnd) * 0.5f;
                                mid *= nb->mScale;
                                mid = mid * nb->mRotation;
                                mid += nb->mTranslation;
                                outward += (nearby[j].second * (pos - mid)) / nb->mScale;
                                up += nearby[j].second * nb->mRotation.m[2];
                            }
                        }
                        outward = normalized_safe(outward);
                        up = normalized_safe(up);
                        if (flags & 8)
                            inRegion = Dot(outward, up) >= mpDesc->mBackCutoff;
                        if (!inRegion && (flags & 0x10))
                            inRegion = mpDesc->mBellyCutoff >= Dot(outward, up);
                    }

                    if (!inRegion && (flags & 0x20)) {
                        // Limb (0x20): the second-heaviest bone must be a limb bone.
                        nearby.clear();
                        query->FindNearest(pos, nearby);
                        WeightMap weights;
                        for (int j = 0, n = nearby.size(); j < n; j++) {
                            uint32_t key = (uint32_t)GetBone(rig, nearby[j].first);
                            weights[key] += nearby[j].second;
                        }
                        WeightMap& sorted = weights;
                        sort(sorted.mpBegin, sorted.mpEnd, greater_second());
                        if ((uint32_t)(sorted.mpEnd - sorted.mpBegin) > 1) {
                            cBone* second = (cBone*)sorted.mpBegin[1].first;
                            if (second->mType == 3)
                                inRegion = true;
                        }
                    }

                    if (inRegion &&
                        (mpDesc->mSpineRange.x > 0.0f || mpDesc->mSpineRange.y < 1.0f)) {
                        uint32_t spinePos = (mesh->mpTriFlags[tri] >> 8) & 0xff;
                        if ((float)numSpine * mpDesc->mSpineRange.x > (float)spinePos ||
                            (float)spinePos > (float)numSpine * mpDesc->mSpineRange.y)
                            inRegion = false;
                    }
                }
            }
            if (inRegion == mpDesc->mInvertRegions)
                continue;
        }

        // Pick the particle effects for this spot.
        IdVector particles;
        if (mpDesc->mParticleSelect.empty()) {
            if (mpDesc->mParticleDescId != -1)
                particles.push_back(mpDesc->mParticleDescId);
        } else if (mpDesc->mParticleSelectIndependent) {
            for (int j = 0, n = mpDesc->mParticleSelect.size(); j < n; j++) {
                float r = (float)sRandom.RandomDoubleUniform();
                if (mpDesc->mParticleSelect.mpBegin[j].second >= r)
                    particles.push_back(mpDesc->mParticleSelect.mpBegin[j].first);
            }
        } else {
            int chosen = -1;
            float r = (float)sRandom.RandomDoubleUniform();
            for (int j = 0, n = mpDesc->mParticleSelect.size(); chosen == -1 && j < n; j++) {
                if (mpDesc->mParticleSelect.mpBegin[j].second >= r)
                    chosen = j;
            }
            if (chosen != -1)
                particles.push_back(mpDesc->mParticleSelect.mpBegin[chosen].first);
        }

        for (int j = 0, n = particles.size(); j < n; j++) {
            cParticleEffect* effect =
                EffectsManager()->CreateEffect(0x26, particles.mpBegin[j], mComponentId);
            effect->mComponentId = mComponentId;
            uint32_t seed = sRandom.RandomUint32Uniform();
            GetPaintSystem()->AddParticle(effect, cTriCoordArg(tc), seed);
        }

        const uint32_t* nidx = &mesh->mpNormalIndices[tri * 3];
        Vector3 normalSum = (mesh->mpNormals[nidx[0]] + mesh->mpNormals[nidx[1]]) +
                            mesh->mpNormals[nidx[2]];
        Vector3 normal = Normalize(normalSum);

        if (!mpDesc->mEffect.empty()) {
            // Builds the effect transform; the result is not used in this build.
            Vector3 right, up;
            OrthonormalBasis(normal, right, up);
            Matrix3 rot;
            rot.m[0] = right;
            rot.m[1] = up;
            rot.m[2] = normal;
            Transform xf;
            xf.SetRotation(rot);
            xf.SetOffset(pos);
        }

        limit--;

        // Flood-fill the neighbourhood within mSpacing as covered.
        stack.push_back(tri);
        memset(visited.mpBegin, 0, visited.size());
        while (!stack.empty()) {
            uint32_t t = stack.back();
            stack.pop_back();
            if (visited[t])
                continue;
            float third = 0.33333334f;
            const uint32_t* vidx = &mesh->mpIndices[t * 3];
            Vector3 centroid = ((mesh->mpPositions[vidx[0]] + mesh->mpPositions[vidx[1]]) +
                                mesh->mpPositions[vidx[2]]) * third;
            if (LengthSquared(centroid - pos) < spacingSq) {
                const uint32_t* tn = &mesh->mpNormalIndices[t * 3];
                if (!mpDesc->mExtraCover ||
                    (Dot(mesh->mpNormals[tn[0]], normal) > 0.31f &&
                     Dot(mesh->mpNormals[tn[1]], normal) > 0.31f &&
                     Dot(mesh->mpNormals[tn[2]], normal) > 0.31f)) {
                    covered[t] |= 1;
                    visited[t] = 1;
                    const uint32_t* adj = &mesh->mpAdjacency[t * 3];
                    uint32_t n0 = adj[0] / 3;
                    stack.push_back(n0);
                    uint32_t n1 = adj[1] / 3;
                    stack.push_back(n1);
                    uint32_t n2 = adj[2] / 3;
                    stack.push_back(n2);
                }
            }
        }
    }
}
