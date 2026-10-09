// @ 0x00f4d9c0  SP::cTerrainBrushEffect::BuildRibbonBrush   (real name, PDB anchor)
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-
//
// Rebuilds the ribbon-brush polygon list from the effect's mRibbonBrushList:
//   1. samples every mRibbonNumSkip-th brush vertex into a position curve and a
//      (size, intensity) curve, and builds an arc-length path from each
//      (FUN_00a7ab40);
//   2. re-parameterises both paths uniformly over their total length;
//   3. walks a particle along both paths in mRibbonNumSteps steps and emits one
//      4-vertex cRibbonBrushPoly per step (U texture coordinate split into a
//      start cap, tiled middle and end cap; V picks a random strip);
//   4. subdivides each quad 1..3 times depending on the average ribbon width;
//   5. projects every vertex onto the unit sphere and hands the polys to the
//      imprint routine (FUN_00f4baa0) with the description's fall-off params.
//
// The class layouts are the 2008 dev-PDB layouts, re-based to the retail offsets
// seen in the disassembly (the description's ribbon fields moved by +0xc).

#include "types.h"
#include <math.h>

inline void* operator new(unsigned int, void* p) { return p; }

extern "C" void __cdecl SP_vector_free(void* p);          // 0x00f47380 (operator delete[])

// ---------------------------------------------------------------------------
// rw::math / EA::Swarm value types
// ---------------------------------------------------------------------------
struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
};

struct Vector2 {
    float x, y;
    Vector2() {}
};

struct Matrix33 {
    float m[9];
    Matrix33() {}
    Matrix33(const Matrix33& src);                        // 0x0041cb40 (out of line)
};

extern const Vector3  kZeroVector3;                       // 0x016c8ff0
extern const Matrix33 kIdentityMatrix33;                  // 0x016c9020

namespace EA { namespace Swarm {
struct cTransform {                                       // size 0x38
    unsigned short mFlags;                                // +0x0
    unsigned short mModificationCount;                    // +0x2
    Vector3        mTranslation;                          // +0x4
    float          mScale;                                // +0x10
    Matrix33       mRotation;                             // +0x14

    cTransform()
        : mFlags(0), mModificationCount(0), mTranslation(kZeroVector3),
          mScale(1.0f), mRotation(kIdentityMatrix33) {}
    void SetIdentity() {
        mRotation = kIdentityMatrix33;
        mTranslation = kZeroVector3;
        mFlags = 0;
        mModificationCount = 0;
        mScale = 1.0f;
    }
};

// One sample of an arc-length parameterised path (0x1c bytes).
struct cPathPoint {
    Vector3 mPosition;                                    // +0x0
    Vector3 mTangent;                                     // +0xc
    float   mDistance;                                    // +0x18
};

// A particle travelling along a cPathPoint path (0x20 bytes).
struct cPathParticle {
    float   mDistance;                                    // +0x0
    float   mLength;                                      // +0x4
    Vector3 mPosition;                                    // +0x8
    Vector3 mDirection;                                   // +0x14
};
}} // namespace EA::Swarm

// ---------------------------------------------------------------------------
// eastl::vector<T, eastl::sp_vector_allocator> (0x10 bytes)
// ---------------------------------------------------------------------------
namespace eastl {
template <class T> class sp_vector {
public:
    typedef unsigned int size_type;
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    int mAllocator;

    sp_vector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~sp_vector() {
        if (mpBegin && ((int*)mpBegin)[-1] != 0)
            SP_vector_free(mpBegin);
    }
    size_type size() const { return (size_type)(mpEnd - mpBegin); }
    T* begin() { return mpBegin; }
    T& operator[](int i) { return mpBegin[i]; }
    T& back() { return *(mpEnd - 1); }

    void push_back(const T& value) {
        if (mpEnd < mpCapacity) {
            T* p = mpEnd++;
            if (p) ::new(p) T(value);
        } else
            DoInsertValue(mpEnd, value);
    }
    T& push_back() {
        if (mpEnd < mpCapacity)
            ++mpEnd;
        else
            DoInsertValue(mpEnd, T());
        return *(mpEnd - 1);
    }
    void reserve(size_type n);                            // 0x00f4c0a0 (cRibbonBrushPoly)
    void DoInsertValue(T* position, const T& value);      // 0x007ed1b0 (Vector3), 0x00f4c180 (poly)
};
} // namespace eastl

namespace EA { namespace Random {
class RandomLinearCongruential {
public:
    unsigned RandomUint32Uniform(unsigned limit);         // 0x00a68fb0
};
}}
extern EA::Random::RandomLinearCongruential sRandom_Swarm; // 0x016778dc

namespace EA { namespace Swarm {
// 0x00a7ab40: build an arc-length path through `count` control points.
void BuildPath(int count, const Vector3* points, float tension, const cTransform* transform,
               eastl::sp_vector<cPathPoint>* out);
// 0x00a79f60: advance a particle by `delta` along a path; false once past the end.
bool SnapParticleToPath(cPathParticle* particle, float delta, const eastl::sp_vector<cPathPoint>* path,
                        const Vector3* startPosition, const Vector3* startTangent,
                        const cTransform* transform);
}}

// ---------------------------------------------------------------------------
// SP types
// ---------------------------------------------------------------------------
namespace SP {
struct cBrushVertex {                                     // size 0x1c
    Vector3 mPosition;                                    // +0x0
    Vector2 mUV;                                          // +0xc
    float   mIntensity;                                   // +0x14
    float   mSize;                                        // +0x18
    cBrushVertex() {}
};

struct cRibbonBrushPoly {                                 // size 0x1c4
    int          mNumVertices;                            // +0x0
    cBrushVertex mVertices[16];                           // +0x4
    cRibbonBrushPoly() {}
};

// Fall-off block handed to the imprint routine (0x44 bytes, first 0x2c unused here).
struct cRibbonFalloffParams {
    char  pad0[0x2c];
    int   mFallOffOp;                                     // +0x2c
    float mFallOffN1;                                     // +0x30
    float mFallOffN2;                                     // +0x34
    int   mGradientCondOp;                                // +0x38
    float mGradientCondN1;                                // +0x3c
    float mGradientCondN2;                                // +0x40
};

struct cTerrainBrushDescription {                         // retail layout
    char          pad0[0x54];
    bool          mbVaryFallOff;                          // +0x54 (retail; name unknown)
    char          pad55[0xa0 - 0x55];
    unsigned char mFallOffOp;                             // +0xa0
    float         mFallOffN1;                             // +0xa4
    float         mFallOffN2;                             // +0xa8
    unsigned char mGradientCondOp;                        // +0xac
    float         mGradientCondN1;                        // +0xb0
    float         mGradientCondN2;                        // +0xb4
    char          padb8[0xf0 - 0xb8];
    int           mRibbonNumTiles;                        // +0xf0
    int           mRibbonNumSteps;                        // +0xf4
    int           mRibbonNumStrips;                       // +0xf8
    int           mRibbonNumSkip;                         // +0xfc
};

class cTerrainEditor {
public:
    float GetRandom01();                                  // 0x00f678d0
};
cTerrainEditor* TerrainEditor();                          // 0x00f48a70

class cTerrainBrushEffect {
public:
    void* vftable;                                        // +0x0
    char  pad4[0x8];
    cTerrainBrushDescription* mDesc;                      // +0xc
    char  pad10[0xc4 - 0x10];
    eastl::sp_vector<cBrushVertex> mRibbonBrushList;      // +0xc4

    void ImprintRibbonPolys(float intensity, int count, cRibbonBrushPoly* polys,
                            const cRibbonFalloffParams* params);   // 0x00f4baa0
    void BuildRibbonBrush();
};
} // namespace SP

using EA::Swarm::cTransform;
using EA::Swarm::cPathPoint;
using EA::Swarm::cPathParticle;

static __forceinline Vector3 Normalized(const Vector3& v)
{
    float inv = 1.0f / sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
    return Vector3(v.x * inv, v.y * inv, v.z * inv);
}

static __forceinline Vector3 Cross(const Vector3& a, const Vector3& b)
{
    return Vector3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}

void SP::cTerrainBrushEffect::BuildRibbonBrush()
{
    cTransform transform;
    eastl::sp_vector<cPathPoint> centerPath;
    eastl::sp_vector<cPathPoint> sizePath;
    eastl::sp_vector<Vector3> centerPoints;
    eastl::sp_vector<Vector3> sizePoints;

    // ---- 1. sample every n-th brush vertex ----
    int skip = mDesc->mRibbonNumSkip;
    for (int i = 0; i < (int)mRibbonBrushList.size(); i += skip) {
        centerPoints.push_back(mRibbonBrushList[i].mPosition);
        sizePoints.push_back(Vector3(mRibbonBrushList[i].mSize, mRibbonBrushList[i].mIntensity, 0.0f));
    }

    transform.SetIdentity();
    EA::Swarm::BuildPath((int)centerPoints.size(), centerPoints.begin(), 1.0f, &transform, &centerPath);
    EA::Swarm::BuildPath((int)sizePoints.size(), sizePoints.begin(), 1.0f, &transform, &sizePath);

    // ---- 2. uniform arc-length parameterisation ----
    for (int i = 0; i < (int)centerPath.size(); ++i) {
        float f = (float)i;
        centerPath[i].mDistance = (f / (float)(centerPath.size() - 1)) * centerPath.back().mDistance;
        sizePath[i].mDistance = (f / (float)(sizePath.size() - 1)) * sizePath.back().mDistance;
    }

    // ---- 3. step counts ----
    int numSteps = mDesc->mRibbonNumSteps;
    int numTiles = mDesc->mRibbonNumTiles;
    if (numSteps % numTiles != 0)
        numSteps = (numSteps / numTiles + 1) * numTiles;
    int stepsPerTile = numSteps / numTiles;

    cPathParticle center;
    center.mDistance = 0.0f;
    center.mLength = centerPath.back().mDistance;
    center.mPosition = Vector3(0.0f, 0.0f, 0.0f);
    center.mDirection = centerPath[0].mTangent;

    cPathParticle size;
    size.mDistance = 0.0f;
    size.mLength = sizePath.back().mDistance;
    size.mPosition = Vector3(0.0f, 0.0f, 0.0f);
    size.mDirection = sizePath[0].mTangent;

    eastl::sp_vector<cRibbonBrushPoly> polys;
    polys.reserve(numSteps);

    int strip = (int)sRandom_Swarm.RandomUint32Uniform(mDesc->mRibbonNumStrips);

    EA::Swarm::SnapParticleToPath(&center, 0.0f, &centerPath, &centerPath.begin()->mPosition,
                                  &centerPath.begin()->mTangent, &transform);
    EA::Swarm::SnapParticleToPath(&size, 0.0f, &sizePath, &sizePath.begin()->mPosition,
                                  &sizePath.begin()->mTangent, &transform);

    cPathParticle prevCenter = center;
    cPathParticle prevSize = size;
    float widthSum = size.mPosition.x;

    // ---- 4. emit one quad per step ----
    if (numSteps > 0) {
        float fNumSteps = (float)numSteps;
        float fStrip = (float)strip;
        float fStripNext = (float)(strip + 1);
        int capSteps = stepsPerTile / 2;
        int tileStep = -(stepsPerTile / 2);

        for (int i = 0; i < numSteps; ++i) {
            EA::Swarm::SnapParticleToPath(&center, (centerPath.back().mDistance - 0.001f) / fNumSteps,
                                          &centerPath, &centerPath.begin()->mPosition,
                                          &centerPath.begin()->mTangent, &transform);
            EA::Swarm::SnapParticleToPath(&size, (sizePath.back().mDistance - 0.001f) / fNumSteps,
                                          &sizePath, &sizePath.begin()->mPosition,
                                          &sizePath.begin()->mTangent, &transform);

            // side vectors at the previous and the current sample
            Vector3 prevSide = Cross(Normalized(prevCenter.mDirection), Normalized(prevCenter.mPosition));
            Vector3 pos = center.mPosition;
            Vector3 side = Cross(Normalized(center.mDirection), Normalized(center.mPosition));

            float numStrips = (float)mDesc->mRibbonNumStrips;
            float v0 = fStrip / numStrips;
            float v1 = fStripNext / numStrips;

            float u0, u1;
            if (i < capSteps) {
                u0 = ((float)i / (float)capSteps) * 0.25f;
                u1 = ((float)(i + 1) / (float)capSteps) * 0.25f;
            } else if (i < stepsPerTile * numTiles - capSteps) {
                int k = tileStep % stepsPerTile;
                u0 = ((float)k / (float)stepsPerTile) * 0.5f + 0.25f;
                u1 = ((float)(k + 1) / (float)stepsPerTile) * 0.5f + 0.25f;
            } else {
                int k = capSteps - stepsPerTile * numTiles + i;
                u0 = ((float)k / (float)capSteps) * 0.25f + 0.75f;
                u1 = ((float)(k + 1) / (float)capSteps) * 0.25f + 0.75f;
            }

            cRibbonBrushPoly& poly = polys.push_back();
            float prevWidth = prevSize.mPosition.x;
            float width = size.mPosition.x;
            poly.mNumVertices = 4;

            cBrushVertex* v = poly.mVertices;
            v[0].mPosition.x = prevCenter.mPosition.x - prevSide.x * prevWidth;
            v[0].mPosition.y = prevCenter.mPosition.y - prevSide.y * prevWidth;
            v[0].mPosition.z = prevCenter.mPosition.z - prevSide.z * prevWidth;
            v[0].mUV.x = v0;
            v[0].mUV.y = u0;
            v[0].mIntensity = prevSize.mPosition.y;

            v[1].mPosition.x = prevCenter.mPosition.x + prevSide.x * prevWidth;
            v[1].mPosition.y = prevCenter.mPosition.y + prevSide.y * prevWidth;
            v[1].mPosition.z = prevCenter.mPosition.z + prevSide.z * prevWidth;
            v[1].mUV.x = v1;
            v[1].mUV.y = u0;
            v[1].mIntensity = prevSize.mPosition.y;

            v[2].mPosition.x = pos.x + side.x * width;
            v[2].mPosition.y = pos.y + side.y * width;
            v[2].mPosition.z = pos.z + side.z * width;
            v[2].mUV.x = v1;
            v[2].mUV.y = u1;
            v[2].mIntensity = size.mPosition.y;

            v[3].mPosition.x = pos.x - side.x * width;
            v[3].mPosition.y = pos.y - side.y * width;
            v[3].mPosition.z = pos.z - side.z * width;
            v[3].mUV.x = v0;
            v[3].mUV.y = u1;
            v[3].mIntensity = size.mPosition.y;

            ++tileStep;
            widthSum += width;
            prevCenter = center;
            prevSize = size;
        }
    }

    // ---- 5. subdivide wide ribbons ----
    float avgWidth = widthSum / (float)(numSteps - 1);
    int level;
    if (avgWidth > 384.0f)
        level = 3;
    else if (avgWidth > 179.2f)
        level = 2;
    else if (avgWidth > 51.2f)
        level = 1;
    else
        level = 0;
    int subdiv = level < 0 ? 0 : level;
    if (subdiv > 3)
        subdiv = 3;

    if (subdiv > 1) {
        int count = (int)polys.size();
        if (count > 0) {
            float inv = 1.0f / (float)subdiv;
            for (int i = 0; i < count; ++i) {
                cBrushVertex* v = polys[i].mVertices;
                float d01px = (v[1].mPosition.x - v[0].mPosition.x) * inv;
                float d01py = (v[1].mPosition.y - v[0].mPosition.y) * inv;
                float d01pz = (v[1].mPosition.z - v[0].mPosition.z) * inv;
                float d01u  = (v[1].mUV.x - v[0].mUV.x) * inv;
                float d01v  = (v[1].mUV.y - v[0].mUV.y) * inv;
                float d01i  = (v[1].mIntensity - v[0].mIntensity) * inv;
                float d32px = (v[2].mPosition.x - v[3].mPosition.x) * inv;
                float d32py = (v[2].mPosition.y - v[3].mPosition.y) * inv;
                float d32pz = (v[2].mPosition.z - v[3].mPosition.z) * inv;
                float d32u  = (v[2].mUV.x - v[3].mUV.x) * inv;
                float d32v  = (v[2].mUV.y - v[3].mUV.y) * inv;
                float d32i  = (v[2].mIntensity - v[3].mIntensity) * inv;

                // shrink this quad to the first sub-quad
                v[1].mPosition.z = v[0].mPosition.z + d01pz;
                v[1].mPosition.y = v[0].mPosition.y + d01py;
                v[1].mPosition.x = v[0].mPosition.x + d01px;
                v[1].mUV.x = v[0].mUV.x + d01u;
                v[1].mUV.y = v[0].mUV.y + d01v;
                v[1].mIntensity = d01i + v[0].mIntensity;
                v[2].mPosition.x = d32px + v[3].mPosition.x;
                v[2].mPosition.y = d32py + v[3].mPosition.y;
                v[2].mPosition.z = d32pz + v[3].mPosition.z;
                v[2].mUV.x = d32u + v[3].mUV.x;
                v[2].mUV.y = d32v + v[3].mUV.y;
                v[2].mIntensity = d32i + v[3].mIntensity;

                // and append the remaining sub-quads
                for (int k = 1; k < subdiv; ++k) {
                    cRibbonBrushPoly& q = polys.push_back();
                    q.mNumVertices = 4;
                    const cBrushVertex* s = polys[i].mVertices;   // may have moved
                    float f0 = (float)k;
                    float f1 = (float)(k + 1);

                    q.mVertices[0].mPosition.x = s[0].mPosition.x + f0 * d01px;
                    q.mVertices[0].mPosition.y = s[0].mPosition.y + d01py * f0;
                    q.mVertices[0].mPosition.z = s[0].mPosition.z + d01pz * f0;
                    q.mVertices[0].mUV.x = d01u * f0 + s[0].mUV.x;
                    q.mVertices[0].mUV.y = s[0].mUV.y + d01v * f0;
                    q.mVertices[0].mIntensity = f0 * d01i + s[0].mIntensity;

                    q.mVertices[1].mPosition.x = f1 * d01px + s[0].mPosition.x;
                    q.mVertices[1].mPosition.y = s[0].mPosition.y + d01py * f1;
                    q.mVertices[1].mPosition.z = s[0].mPosition.z + d01pz * f1;
                    q.mVertices[1].mUV.x = d01u * f1 + s[0].mUV.x;
                    q.mVertices[1].mUV.y = s[0].mUV.y + d01v * f1;
                    q.mVertices[1].mIntensity = f1 * d01i + s[0].mIntensity;

                    q.mVertices[2].mPosition.x = d32px * f1 + s[3].mPosition.x;
                    q.mVertices[2].mPosition.y = s[3].mPosition.y + d32py * f1;
                    q.mVertices[2].mPosition.z = s[3].mPosition.z + d32pz * f1;
                    q.mVertices[2].mUV.x = d32u * f1 + s[3].mUV.x;
                    q.mVertices[2].mUV.y = s[3].mUV.y + d32v * f1;
                    q.mVertices[2].mIntensity = f1 * d32i + s[3].mIntensity;

                    q.mVertices[3].mPosition.x = d32px * f0 + s[3].mPosition.x;
                    q.mVertices[3].mPosition.y = s[3].mPosition.y + d32py * f0;
                    q.mVertices[3].mPosition.z = s[3].mPosition.z + d32pz * f0;
                    q.mVertices[3].mUV.x = d32u * f0 + s[3].mUV.x;
                    q.mVertices[3].mUV.y = s[3].mUV.y + d32v * f0;
                    q.mVertices[3].mIntensity = f0 * d32i + s[3].mIntensity;
                }
            }
        }
    }

    // ---- 6. project every vertex onto the unit sphere ----
    int numPolys = (int)polys.size();
    for (int i = 0; i < numPolys; ++i) {
        cRibbonBrushPoly& p = polys[i];
        for (int j = 0; j < p.mNumVertices; ++j)
            p.mVertices[j].mPosition = Normalized(p.mVertices[j].mPosition);
    }

    // ---- 7. imprint with the description's fall-off parameters ----
    float vary = 0.0f;
    if (mDesc->mbVaryFallOff) {
        cTerrainEditor* editor = TerrainEditor();
        editor->GetRandom01();
        vary = editor->GetRandom01() - 0.5f;
    }
    cTerrainBrushDescription* desc = mDesc;
    cRibbonFalloffParams params;
    params.mFallOffOp = desc->mFallOffOp;
    params.mGradientCondOp = desc->mGradientCondOp;
    params.mFallOffN1 = desc->mFallOffN1 + vary;
    params.mFallOffN2 = desc->mFallOffN2 + vary;
    params.mGradientCondN1 = desc->mGradientCondN1 + vary;
    params.mGradientCondN2 = desc->mGradientCondN2 + vary;
    ImprintRibbonPolys(1.0f, numPolys, polys.begin(), &params);
}
// --- equivalence checker address annotations

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}

namespace __equiv_ann1 {   // address annotations for the equivalence checker; never referenced
struct EA {
    void BuildPath();   // 0x00a7ab40 (equiv t3)
};
struct UVector3 {
    void DoInsertValue();   // 0x007ed1b0 (equiv t3)
};
struct UcRibbonBrushPoly {
    void DoInsertValue();   // 0x00f4c180 (equiv t2)
    void reserve();   // 0x00f4c0a0 (equiv t3)
};
}
