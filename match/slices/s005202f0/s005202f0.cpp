// Slice s005202f0: nSPSkinner::cPaintSystem::Tick (0x005202f0).
// Unoptimized editor module: /Od /Oy /Ob1 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc); the
// original frame is 16-byte aligned (esp-relative locals).
//
// Moves every live paint particle across the baked skin mesh until the tick budget runs
// out. Each tick a particle walks kMovePerTick along its direction in barycentric space:
// when it leaves its triangle through an edge it is carried into the neighbour triangle
// (mNeighborIndices_TE) and its direction is rotated from the old to the new face normal;
// every mDistToHit units it calls ProcessHit (paints). When it finishes (life over, killed,
// stuck or flipped against an attractor) it spawns its chained brush description (with the
// inherited variable block) or is removed by swapping the last particle into its place.
//
// Retail layout notes: eastl::vector is 0x14 bytes in this build (the dev PDB says 0x10),
// so cPaintSystem::mTickPosition is +0x50, cMesh::mVertexIndices_TV +0x58,
// cMesh::mNeighborIndices_TE +0x94, and cPaintBrushDescription fields after mBrushHashes
// sit 4 bytes later than in the PDB (mFlags +0x1c, mAttractTarget +0x48, ...).
#include "types.h"

#define FLT_MAX 3.402823466e+38F

// ---------------------------------------------------------------- math
struct Vector2 {
    float x, y;
    Vector2& operator=(const Vector2& v) { x = v.x; y = v.y; return *this; }   // 0x0051fb60 when not inlined
    float& operator[](int i) { return (&x)[i]; }
};

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float a, float b, float c) : x(a), y(b), z(c) {}
    float& operator[](int i) { return (&x)[i]; }
    float Dot(const Vector3& v) const { return x * v.x + y * v.y + z * v.z; }
};
struct Matrix3 {
    Vector3 m[3];
};

Vector3 operator+(const Vector3& a, const Vector3& b);          // 0x0041dc10
Vector3 operator-(const Vector3& a, const Vector3& b);          // 0x0041db10
Vector3 operator*(const Vector3& v, const float& f);            // 0x0041dca0
Vector3 operator*(const float& f, const Vector3& v);            // 0x0041de40
Vector3 operator*(const Vector3& v, const Matrix3& m);          // 0x0041daf0 (row vector * M)
Vector3 Normalize(const Vector3& v);                            // 0x00436ce0
Matrix3 RotationBetween(const Vector3& from, const Vector3& to); // 0x0069b1c0

inline float Dot(const Vector3& a, const Vector3& b) { return a.x * b.x + a.y * b.y + a.z * b.z; }

// minss/maxss clamp to [0,1] (the /arch:SSE module's asm helper).
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

// ---------------------------------------------------------------- Windows
union LARGE_INTEGER_ {
    struct { uint32_t LowPart; int32_t HighPart; };
    int64_t QuadPart;
};
extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(LARGE_INTEGER_* t);

// The argument of Tick: a deadline in QueryPerformanceCounter ticks at +0x18.
struct cTickBudget {
    uint32_t pad0[6];
    int64_t mEndTime;           // +0x18
    bool Expired() const
    {
        LARGE_INTEGER_ now;
        QueryPerformanceCounter(&now);
        int64_t left = mEndTime - now.QuadPart;
        return left < 0 ? true : false;
    }
};

// ---------------------------------------------------------------- skinner types
struct cMeshPosition {          // 0xc
    uint32_t mTriIndex;
    Vector2 mUV;
    cMeshPosition(const cMeshPosition& o) : mTriIndex(o.mTriIndex) { mUV = o.mUV; }
};

struct cMesh {
    uint32_t pad0[2];
    Vector3* mpVertices;            // +0x08 mVertices.mpBegin
    uint32_t pad0c[19];
    uint32_t* mpVertexIndices;      // +0x58 mVertexIndices_TV.mpBegin (3 per triangle)
    uint32_t pad5c[14];
    uint32_t* mpNeighborIndices;    // +0x94 mNeighborIndices_TE.mpBegin (tri*3+edge per edge)
    Vector3 GetTriNormal(uint32_t tri);   // 0x005121c0
};

struct cSkinObject;

// `anonymous namespace'::cVarBlock: 19 inheritable brush variables plus a refcount,
// allocated from a FixedAllocator.
struct cVarValues {
    float mVars[19];
};
struct cVarAllocator {
    void* Allocate();               // 0x004fde40 (FixedAllocator pop)
};
extern cVarAllocator gVarBlockAllocator;   // 0x015de2a0
struct cVarBlock : cVarValues {
    int mRefCount;                  // +0x4c
    cVarBlock() { mRefCount = 0; }
    void* operator new(unsigned int) { return gVarBlockAllocator.Allocate(); }
};
struct cVarBlockPtr {               // AutoRefCount<cVarBlock>
    cVarBlock* mpObject;
    cVarBlockPtr& operator=(cVarBlock* p);   // 0x00525d90
    cVarBlock* operator->() const { return mpObject; }
};

struct cPaintBrushDescription {
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual cPaintBrushDescription* GetChained();   // +0x0c: next brush of the chain (or 0)
    uint32_t pad04[6];
    uint32_t mFlags;                // +0x1c (8 = keep direction tangent to the surface)
    uint32_t pad20[3];
    uint8_t mUserColorIndex;        // +0x2c
    uint8_t mAlignment;             // +0x2d
    uint8_t mInitialDirection;      // +0x2e
    uint8_t mAttraction;            // +0x2f
    Vector3 mAlignTarget;           // +0x30
    Vector3 mInitialDirTarget;      // +0x3c
    Vector3 mAttractTarget;         // +0x48
    float mAttractStrength;         // +0x54
    uint32_t pad58[4];
    uint32_t mInheritMask;          // +0x68
};
struct cPaintBrushDescriptionPtr {  // AutoRefCount<cPaintBrushDescription>
    cPaintBrushDescription* mpObject;
    cPaintBrushDescription* get() const { return mpObject; }
};

struct cPaintParticle {             // 0x38
    cMeshPosition mPos;             // +0x00
    Vector3 mDirection;             // +0x0c
    float mDistToHit;               // +0x18
    int mHits;                      // +0x1c
    int mTicksSpent;                // +0x20
    int mTicksTotal;                // +0x24
    uint32_t mSeed;                 // +0x28
    cPaintBrushDescriptionPtr mpDescription;   // +0x2c
    int mKillSwitch;                // +0x30
    cVarBlockPtr mpInheritance;     // +0x34
    cPaintParticle& operator=(const cPaintParticle& o);   // 0x005218e0
};

struct cParticleVector {            // eastl::vector<cPaintParticle, sp_vector_allocator>
    cPaintParticle* mpBegin;
    cPaintParticle* mpEnd;
    cPaintParticle* mpCapacity;
    uint32_t mAllocator[2];
    cPaintParticle* begin() { return mpBegin; }
    int size() { return (int)(mpEnd - mpBegin); }
    void resize(int n);             // 0x00525e70
};

struct cMeshPtr {                   // AutoRefCount<cMesh>
    cMesh* mpObject;
    cMesh* operator->() const { return mpObject; }
    cMesh* get() const { return mpObject; }
};

extern float kMovePerTick;          // 0x015de718
extern const signed char kNextVertex[3];   // 0x013f1ca4 {1,2,0}
extern const signed char kPrevVertex[3];   // 0x013f1ca0 {2,0,1}

// Steers the particle toward/along the brush's attractor; writes the travel direction.
void ComputeAttraction(uint8_t attraction, const Vector3& target, cMeshPosition pos,
                       cPaintBrushDescription* desc, cSkinObject* skin, cMesh* mesh,
                       Vector3& outDir);   // 0x0051fb90
// Builds the tangent frame around a face normal (outDir is projected into the plane).
void ProjectToTangentPlane(const Vector3& normal, const Vector3& dir, Vector3& outDir,
                           Vector3& outSide);   // 0x00520140

namespace nSPSkinner {

struct cPaintSystem {
    uint32_t pad0[3];
    uint32_t mpMaterial;            // +0x0c
    cMeshPtr mpBakedMesh;           // +0x10
    uint32_t pad14[3];
    cSkinObject* mpEditorSkinPart;  // +0x20
    uint32_t mBounds[6];            // +0x24
    cParticleVector mParticles;     // +0x3c
    uint32_t mTickPosition;         // +0x50 (resume index into mParticles)

    void ProcessHit(cPaintParticle& p, cVarValues& vars);   // 0x0051f0b0
    void SpawnParticle(cPaintParticle& parent, cPaintBrushDescription* desc,
                       cMeshPosition pos, uint32_t seed);   // 0x00523900
    void Tick(const cTickBudget& budget);
};

// @ 0x005202f0 ?Tick@cPaintSystem@nSPSkinner@@
void cPaintSystem::Tick(const cTickBudget& budget)
{
    cPaintParticle* p = mParticles.begin() + mTickPosition;
    cPaintParticle* pEnd = mParticles.begin() + mParticles.size();
    Vector3* verts = mpBakedMesh->mpVertices;
    uint32_t* indices = mpBakedMesh->mpVertexIndices;
    cVarValues vars;

    while (p < pEnd) {
        cPaintBrushDescription* desc = p->mpDescription.get();
        p->mTicksSpent = p->mTicksSpent + 1;
        bool done = p->mTicksSpent >= p->mTicksTotal;

        if (p->mTicksSpent > 0) {
            if (done && p->mDistToHit < 1e-6f) {
                ProcessHit(*p, vars);
            } else {
                float move = kMovePerTick;
                int stuck = 0;
                while (1) {
                    uint32_t tri = p->mPos.mTriIndex;
                    uint32_t triBase = tri * 3;
                    float u = p->mPos.mUV[0];
                    float v = p->mPos.mUV[1];
                    float w = 1.0f - u - v;
                    Vector3 delta = p->mDirection * move;
                    Vector3* v0 = &verts[indices[triBase]];
                    Vector3* v1 = &verts[indices[triBase + 1]];
                    Vector3* v2 = &verts[indices[triBase + 2]];
                    Vector3 e1 = *v1 - *v0;
                    Vector3 e2 = *v2 - *v0;

                    // Barycentric velocity of delta in the triangle plane.
                    float d00 = Dot(e1, e1);
                    float d01 = Dot(e1, e2);
                    float d11 = Dot(e2, e2);
                    float d20 = Dot(e1, delta);
                    float d21 = Dot(e2, delta);
                    float denom = d00 * d11 - d01 * d01;
                    float inv = 1.0f / denom;
                    float du = (d11 * d20 - d01 * d21) * inv;
                    float dv = (-d01 * d20 + d00 * d21) * inv;
                    float dw = -du - dv;

                    // Fraction of the step after which each coordinate reaches 0.
                    float tU = (du < 0.0f) ? -u / du : FLT_MAX;
                    float tV = (dv < 0.0f) ? -v / dv : FLT_MAX;
                    float tW = (dw < 0.0f) ? -w / dw : FLT_MAX;

                    // Never leave exactly through a vertex: nudge one of two equal exits.
                    if (tU != FLT_MAX && tV != FLT_MAX && tU == tV &&
                        tU < tW && tV < tW) {
                        if (du > dv)
                            tU += 1e-6f;
                        else
                            tV += 1e-6f;
                    }

                    float t;
                    int edge;
                    if (tU < tV) {
                        if (tU == tW) {
                            if (du > dw)
                                tU += 1e-6f;
                            else
                                tW += 1e-6f;
                        }
                        if (tU < tW) {
                            t = tU;
                            edge = 2;
                        } else {
                            t = tW;
                            edge = 1;
                        }
                    } else {
                        if (tV == tW) {
                            if (dv > dw)
                                tV += 1e-6f;
                            else
                                tW += 1e-6f;
                        }
                        if (tV < tW) {
                            t = tV;
                            edge = 0;
                        } else {
                            t = tW;
                            edge = 1;
                        }
                    }

                    if (t < 0.000244140625f) {
                        if (stuck > 10) {
                            done = true;
                            break;
                        }
                        stuck = stuck + 1;
                    } else {
                        stuck = 0;
                    }

                    float tc = Clamp01(t);
                    Vector3 bary(w, u, v);
                    Vector3 baryDir(dw, du, dv);
                    Vector3 newBary = bary + tc * baryDir;
                    float travel = move * tc;

                    // Paint every mDistToHit along the way.
                    while (p->mKillSwitch == 0 && p->mDistToHit <= travel) {
                        float frac = p->mDistToHit / travel;
                        Vector2& uv = p->mPos.mUV;
                        float hu = frac * baryDir[1] + bary[1];
                        float hv = frac * baryDir[2] + bary[2];
                        uv.x = hu;
                        uv.y = hv;
                        travel = travel - p->mDistToHit;
                        ProcessHit(*p, vars);
                    }
                    if (p->mKillSwitch != 0) {
                        done = true;
                        break;
                    }
                    p->mDistToHit = p->mDistToHit - travel;

                    if (t < 1.0f) {
                        // Cross the exit edge into the neighbouring triangle.
                        uint32_t edgeIndex = triBase + edge;
                        cMesh* mesh = mpBakedMesh.get();
                        uint32_t neighbor = mesh->mpNeighborIndices[edgeIndex];
                        if (neighbor == edgeIndex) {
                            done = true;   // open (boundary) edge
                            break;
                        }
                        uint32_t newTri = neighbor / 3;
                        uint32_t newEdge = neighbor % 3;
                        uint32_t a = (edge + 2) % 3;
                        uint32_t b = (newEdge + 2) % 3;
                        Vector3 nb;
                        nb[b] = newBary[a];
                        nb[kPrevVertex[b]] = newBary[kNextVertex[a]];
                        nb[kNextVertex[b]] = newBary[kPrevVertex[a]];

                        Vector3 n0 = mpBakedMesh->GetTriNormal(tri);
                        Vector3 n1 = mpBakedMesh->GetTriNormal(newTri);
                        p->mDirection = p->mDirection * RotationBetween(n0, n1);
                        p->mDirection = Normalize(p->mDirection);

                        float nu = nb[1];
                        float nv = nb[2];
                        p->mPos.mTriIndex = newTri;
                        Vector2& uv = p->mPos.mUV;
                        uv.x = nu;
                        uv.y = nv;
                        move = (1.0f - tc) * move;
                    } else {
                        Vector2& uv = p->mPos.mUV;
                        float nu = newBary[1];
                        float nv = newBary[2];
                        uv.x = nu;
                        uv.y = nv;
                        break;
                    }
                }

                if (!done) {
                    // Re-aim along the surface: attraction, tangent projection, attract blend.
                    cMesh* mesh = mpBakedMesh.get();
                    Vector3 dir;
                    ComputeAttraction(desc->mAttraction, desc->mAttractTarget, p->mPos, desc,
                                      mpEditorSkinPart, mesh, dir);
                    if (desc->mFlags & 8) {
                        float d = p->mDirection.Dot(dir);
                        Vector3 tangent = p->mDirection - dir * d;
                        dir = Normalize(tangent);
                    }
                    Vector3 side;
                    ProjectToTangentPlane(mpBakedMesh->GetTriNormal(p->mPos.mTriIndex), dir, dir,
                                          side);
                    if (desc->mAttractStrength > 0.0f && desc->mInitialDirection < 3 &&
                        p->mDirection.Dot(dir) < -0.7f) {
                        done = true;
                    } else {
                        Vector3 blended = p->mDirection +
                                          (dir - p->mDirection) * desc->mAttractStrength;
                        p->mDirection = Normalize(blended);
                    }
                }
            }
        }

        if (done) {
            cPaintBrushDescription* next = desc->GetChained();
            if (next == 0 || p->mKillSwitch >= 2) {
                // Remove: move the last live particle into this slot.
                pEnd = pEnd - 1;
                *p = *pEnd;
            } else {
                SpawnParticle(*p, next, p->mPos, p->mSeed + 12345);
                if (next->mInheritMask != 0) {
                    p->mpInheritance = new cVarBlock;
                    *static_cast<cVarValues*>(p->mpInheritance.mpObject) = vars;
                }
                p++;
            }
        } else {
            p++;
        }

        if (budget.Expired())
            break;
    }

    if (p < pEnd)
        mTickPosition = p - mParticles.begin();
    else
        mTickPosition = 0;
    mParticles.resize(pEnd - mParticles.begin());
}

}  // namespace nSPSkinner
