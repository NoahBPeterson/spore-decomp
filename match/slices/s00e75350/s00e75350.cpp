// Slice s00e75350 -- cell stage: scatter clusters of cells inside a bounding box.
// SP::sGenCluster (dev PDB: SP::sGenCluster, SPGonzago/SPCellGame.obj, SPCellGame.cpp:4578-4679,
// dev 0x00a84160).  For every whole unit of `count` that passes a random draw, a new group is
// allocated and `parts` cells are placed: the first at a random point of `extents`, each later one
// next to an already placed cell of the group (the latest one when `linear`, else a random one).
// A position is retried up to ten times while it is not clear (see below).  Parameter and local
// names are the dev PDB's; retail calls out-of-line helpers where the prototype inlined them.
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (cell TU).
#include "types.h"
#include <math.h>

namespace rw { namespace math { namespace fpu {

// RenderWare's FPU vector value type, the base of cSPVector3.  Its copy constructor is user-written and
// its assignment is the implicit one, so copying a cSPVector3 into a cSPVector3 is a plain block copy,
// while assigning an operator result (a Vector3Template) goes through cSPVector3::operator= below.
// The free operators return the base type and take the scalar as const T& (dev mangled names:
// ??$?DM$0A@...@ABM@Z for operator*, ??$?KM...ABM@Z for operator/).  How each body builds its result
// (the 3-argument constructor or a named result) is not visible in the prototype's code; the choice here
// (operator* and operator/ through the constructor, operator+ through a named result) is the one that
// reproduces retail's operand order, and is the same set slice s00e5e850 (same TU) matches with.  The
// compound operators compute all three components before storing, as the prototype's out-of-line copies do.
template <class T, int Aligned> class Vector3Template {
public:
    T x, y, z;
    Vector3Template() {}
    Vector3Template(T ax, T ay, T az) : x(ax), y(ay), z(az) {}
    Vector3Template(const Vector3Template& v) : x(v.x), y(v.y), z(v.z) {}
};

template <class T, int Aligned>
inline Vector3Template<T, Aligned> operator*(const Vector3Template<T, Aligned>& v, const T& s)
{
    return Vector3Template<T, Aligned>(v.x * s, v.y * s, v.z * s);
}

template <class T, int Aligned>
inline Vector3Template<T, Aligned> operator/(const Vector3Template<T, Aligned>& v, const T& s)
{
    T inv = 1.0f / s;
    return Vector3Template<T, Aligned>(v.x * inv, v.y * inv, v.z * inv);
}

template <class T, int Aligned>
inline Vector3Template<T, Aligned> operator+(const Vector3Template<T, Aligned>& a, const Vector3Template<T, Aligned>& b)
{
    Vector3Template<T, Aligned> r;
    r.x = a.x + b.x;
    r.y = a.y + b.y;
    r.z = a.z + b.z;
    return r;
}

template <class T, int Aligned>
inline Vector3Template<T, Aligned>& operator+=(Vector3Template<T, Aligned>& a, const Vector3Template<T, Aligned>& b)
{
    T x = a.x + b.x;
    T y = a.y + b.y;
    T z = a.z + b.z;
    a.x = x;
    a.y = y;
    a.z = z;
    return a;
}

} } }

struct cSPVector3 : public rw::math::fpu::Vector3Template<float, 0> {
    cSPVector3() {}
    cSPVector3(float ax, float ay, float az) : rw::math::fpu::Vector3Template<float, 0>(ax, ay, az) {}
    cSPVector3(const cSPVector3& v) : rw::math::fpu::Vector3Template<float, 0>(v) {}
    cSPVector3(const rw::math::fpu::Vector3Template<float, 0>& v) : rw::math::fpu::Vector3Template<float, 0>(v) {}
    cSPVector3& operator=(const rw::math::fpu::Vector3Template<float, 0>& v) { x = v.x; y = v.y; z = v.z; return *this; }
};

struct cSPBoundingBox {
    cSPVector3 mMin;   // +0x00
    cSPVector3 mMax;   // +0x0c

    // Inclusive on every face.
    bool Contains(const cSPVector3& p) const
    {
        return p.x >= mMin.x && p.x <= mMax.x &&
               p.y >= mMin.y && p.y <= mMax.y &&
               p.z >= mMin.z && p.z <= mMax.z;
    }
};

namespace SP {

struct cSPSphereTree;
struct cResourceHandle;
struct cTextureMask;
enum eLevel { kLevelDummy };

// Cell object: only the placement fields and the group tag are touched here.
struct cCell {
    unsigned char pad00[0x4c];
    cSPVector3    mPosition;   // +0x4c
    float         mRadius;     // +0x58
    unsigned char pad5c[0x38c - 0x5c];
    int           mGroup;      // +0x38c
};

// The group objects handed out by the pool at cCellGame + 0xa8.
struct cCellGroup {
    unsigned char pad00[4];
    int           mCount;      // +0x04
    int           mIds[1];     // +0x08
};

}  // namespace SP

struct cObjectPool {
    unsigned int Alloc();                   // 0x00b72160
    void*        At(unsigned int index);    // 0x00b72210
};

template <class T> struct cSPObjectPoolT : public cObjectPool {
    T* Get(unsigned int index) { return (T*)At(index); }
};

namespace SP {

struct cCellGame {
    unsigned char  pad0000[0x1c];
    cSPObjectPoolT<cCell> mCells;  // +0x001c
    unsigned char  pad001d[0xa8 - 0x1d];
    cSPObjectPoolT<cCellGroup> mGroups; // +0x00a8
    unsigned char  pad00a9[0x40fc - 0xa9];
    cSPSphereTree* mpPlayerTree;   // +0x40fc
    unsigned char  pad4100[0x514c - 0x4100];
    float          mCellSize;      // +0x514c
};

extern cCellGame* gspCellGame;     // 0x016b3c04

}  // namespace SP

// EA::Random::RandomLinearCongruential, SP::sMathRandom at 0x01601760.
struct RandomLCG {
    double       RandomDoubleUniform();                   // 0x009360d0
    unsigned int RandomUint32Uniform(unsigned int range); // 0x00a68fb0
};

namespace SP {

extern RandomLCG sMathRandom;   // 0x01601760

cSPVector3   RandomDirection3();                                         // 0x00b7e560
cSPVector3   RandomPointInBox(const cSPBoundingBox& box);              // 0x00df5f50
double       sGetClusterRadius(cResourceHandle* key, eLevel level);                     // 0x00e5d2b0
bool         sIsSphereVisible(cSPSphereTree* pTree, const cSPVector3* pos, float radius); // 0x00e5d410
int          SphereTreeIntersectSphere(cSPSphereTree* pTree, const cSPVector3* pos, float radius,
                                       int* results, int maxResults, int flags);         // 0x00e87260
int          sCreateCell(cSPSphereTree* pTree, const cSPVector3* pos, float zOffset,
                         cResourceHandle* key, eLevel level, float scale, float radius,
                         int a, int b, int c);                                          // 0x00e74a20
void         SphereTreeUpdate(cSPSphereTree* pTree);                                    // 0x00e86f70

// Linear clusters: the position just outside `parent` along `dir`, for a new cell of `radius`.  The
// random draw is consumed and its value unused (as in the prototype, where the whole branch is the one
// line SPCellGame.cpp:4616 and the parent's radius and position live in unnamed slots: an inlined helper).
inline void sPlaceLinear(cSPVector3& out, cCell* parent, const cSPVector3& dir, const float& radius)
{
    float parentRadius = parent->mRadius;
    sMathRandom.RandomDoubleUniform();
    cSPVector3 parentPos = parent->mPosition;
    out = parentPos + dir * parentRadius;
    out += dir * radius * 1.0001f;
}

// A random unit direction in the xy plane.
inline cSPVector3 RandomDirection2D()
{
    cSPVector3 dir = RandomDirection3();
    dir.z = 0.0f;
    dir = cSPVector3(dir / sqrtf(dir.x * dir.x + dir.y * dir.y + 1e-8f));
    return dir;
}

// Uniform in [lo, hi], clamped against rounding at both ends.
inline double RandomRange(double lo, double hi)
{
    double r = lo + (hi - lo) * sMathRandom.RandomDoubleUniform();
    return (r >= hi) ? hi : ((lo > r) ? lo : r);
}

// @ 0x00e75350
void sGenCluster(cSPSphereTree* pTree, const cSPBoundingBox& extents, float zOffsetBase,
                 float zOffsetMax, int parts, float count, cResourceHandle* key, bool linear,
                 eLevel sourceLevel, const cTextureMask& mask, bool firstTime)
{
    int listResults[512];
    int listObjects[512];

    for (float i = count; i > 0.0f; i -= 1.0f) {
        if (sMathRandom.RandomDoubleUniform() > i)
            continue;

        int groupId = gspCellGame->mGroups.Alloc();
        int numObjects = 0;

        // Height of the cluster, uniform in [zOffsetBase, zOffsetMax] (zOffsetMax == 0: no range).
        float zOffset = (float)RandomRange(zOffsetBase, (zOffsetMax == 0.0f) ? zOffsetBase : zOffsetMax);

        for (int j = 0; j < parts; ++j) {
            float radius = (float)(sGetClusterRadius(key, sourceLevel) / gspCellGame->mCellSize);

            int attempts = 0;
            int numResults = 1;
            cSPVector3 dir = RandomDirection3();
            dir.z = 0.0f;
            dir = cSPVector3(dir / sqrtf(dir.y * dir.y + dir.x * dir.x + 1e-8f));
            cSPVector3 linearDir = dir;
            sMathRandom.RandomUint32Uniform(2);

            cSPVector3 pos;
            while (numResults > 0 && attempts < 10) {
                attempts++;
                if (numObjects > 0) {
                    if (linear) {
                        sPlaceLinear(pos, gspCellGame->mCells.Get(listObjects[numObjects - 1]), linearDir, radius);
                    } else {
                        cCell* parent = gspCellGame->mCells.Get(
                            listObjects[sMathRandom.RandomUint32Uniform(numObjects)]);
                        float parentRadius = parent->mRadius;
                        cSPVector3 parentPos = parent->mPosition;
                        cSPVector3 dir2 = RandomDirection2D();
                        pos = parentPos + dir2 * parentRadius;
                        pos += dir2 * radius * 1.0001f;
                    }
                } else {
                    cSPVector3 point;
                    point = RandomPointInBox(extents);
                    point.z = 0.0f;
                    pos = point;
                }

                if (!sIsSphereVisible(pTree, &pos, radius) || firstTime) {
                    if (extents.Contains(pos)) {
                        if (pTree != gspCellGame->mpPlayerTree)
                            break;
                        numResults = SphereTreeIntersectSphere(pTree, &pos, radius, listResults, 512, 0);
                    }
                }
            }

            if (attempts < 10) {
                int id = sCreateCell(pTree, &pos, zOffset, key, sourceLevel, 1.0f, radius, 1, 0, 0);
                listObjects[numObjects++] = id;
                cCellGroup* group = gspCellGame->mGroups.Get(groupId);
                cCell* cell = gspCellGame->mCells.Get(id);
                cell->mGroup = groupId;
                group->mIds[group->mCount++] = id;
                SphereTreeUpdate(pTree);
            }
        }
    }
}

}  // namespace SP
