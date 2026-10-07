// Slice s00b78880: FUN_00b78880 (0x00b78880), builds a 2D footprint hull for a model.
// /O2 /arch:SSE /fp:fast module.
//
// The model's transform is saved, reset to identity with the owner's scale, and the
// footprint points are gathered into a stack sp_fixed_vector<Vector3,256>:
//   * from the model's property 0x637d439 (Vector2 array, scaled by the owner scale and
//     optionally by property 0xfba611) when it has more than two points, else
//   * from the model-world's transformed hull: when bClipToPlanet is set, the hull
//     triangles' edges that cross the planet surface are clipped (FUN_00b76b80); if that
//     yields nothing (or bClipToPlanet is false) every hull vertex is projected onto the
//     plane orthogonal to the global axis at 0x16880e0.
// FUN_00b780d0 then reduces the points into owner->mHull; with at least three hull
// points the owner's centre (mean) and radius (max distance) are recomputed.  The
// model transform is restored and the result (hull has >= 3 points) returned.
#include "types.h"
#include <math.h>

struct Vector2 { float x, y; };
struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    Vector3& operator+=(const Vector3& b) { x = b.x + x; y = b.y + y; z = b.z + z; return *this; }
    Vector3& operator*=(float s) { x *= s; y *= s; z *= s; return *this; }
    Vector3& operator*=(const struct Matrix3& r);
};
inline Vector3 operator-(const Vector3& a, const Vector3& b)
{
    Vector3 r;
    r.x = a.x - b.x; r.y = a.y - b.y; r.z = a.z - b.z;
    return r;
}
inline Vector3 operator*(float s, const Vector3& v)
{
    Vector3 r;
    r.x = s * v.x; r.y = s * v.y; r.z = s * v.z;
    return r;
}
inline float Dot(const Vector3& a, const Vector3& b) { return a.x * b.x + a.y * b.y + a.z * b.z; }

struct Matrix3 { float m[3][3]; };
// row vector * matrix
inline Vector3& Vector3::operator*=(const Matrix3& r)
{
    float rx = r.m[0][0] * x + r.m[1][0] * y + r.m[2][0] * z;
    float ry = r.m[0][1] * x + r.m[1][1] * y + r.m[2][1] * z;
    float rz = r.m[0][2] * x + r.m[1][2] * y + r.m[2][2] * z;
    x = rx;
    y = ry;
    z = rz;
    return *this;
}

struct cSPTransform {                         // 0x38
    uint16_t mFlags;                          // +0x00 (2 = has rotation)
    uint16_t mModificationCount;              // +0x02
    Vector3  mTranslation;                    // +0x04
    float    mScale;                          // +0x10
    Matrix3  mRotation;                       // +0x14

    cSPTransform(const cSPTransform& t);                  // 0x0040ce80
    cSPTransform& operator=(const cSPTransform& t);       // 0x00537dc0
    void SetIdentity();                                   // 0x005aa530
    void SetScale(float s) { mScale = s; mModificationCount++; }
};

// ---- properties -------------------------------------------------------------
struct Property { float* GetValueFloat(); };              // 0x0041ea70
class cPropertyList {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20();
    virtual bool GetProperty(uint32_t id, Property*& result);           // 0x24
};
bool GetPropertyAsVector2Array(cPropertyList* list, uint32_t id, int* count, Vector2** out);  // 0x006a0920

// ---- containers ----------------------------------------------------------------
namespace eastl {
struct sp_vector_allocator { uint32_t mData[2]; };

template <typename T>
struct vector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    sp_vector_allocator mAllocator;

    unsigned size() const { return (unsigned)(mpEnd - mpBegin); }
    T& operator[](unsigned n) { return mpBegin[n]; }
    void resize(unsigned n);              // 0x00473810 (Vector3), 0x00b77850 (HullVertex)
};
}

// spstl::sp_fixed_vector<T,N>: the word before the inline buffer is 0; a heap block
// carries a non-zero header there.
template <typename T, int N>
struct sp_fixed_vector : eastl::vector<T> {
    uint32_t mPadding;
    T mBuffer[N];

    sp_fixed_vector()
    {
        this->mpBegin = this->mpEnd = mBuffer;
        this->mpCapacity = mBuffer + N;
        mPadding = 0;
    }
    ~sp_fixed_vector()
    {
        if (this->mpBegin && ((int*)this->mpBegin)[-1] != 0)
            operator delete[](this->mpBegin);
    }
};

struct HullVertex {          // 0x10
    Vector3 pos;
    bool    bOutside;        // beyond the planet surface
};

// ---- model world ---------------------------------------------------------------
struct cMWTransformedHull {
    int mVertStride;         // +0x00
    int mTriStride;          // +0x04
    int mVertCount;          // +0x08
    int mTriCount;           // +0x0c
    Vector3*  mVertArray;    // +0x10
    uint32_t* mTriArray;     // +0x14 (4 words per triangle)
};

struct cModel {
    uint32_t pad00[2];
    cSPTransform mTransform;              // +0x08
    uint32_t pad40[20];
    cPropertyList* mpPropList;            // +0x90
};

class cModelWorld {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
    virtual void v70(); virtual void v74(); virtual void v78(); virtual void v7c();
    virtual void v80(); virtual void v84(); virtual void v88(); virtual void v8c();
    virtual void v90(); virtual void v94(); virtual void v98(); virtual void v9c();
    virtual void va0(); virtual void va4(); virtual void va8(); virtual void vac();
    virtual void vb0(); virtual void vb4(); virtual void vb8(); virtual void vbc();
    virtual void vc0(); virtual void vc4(); virtual void vc8(); virtual void vcc();
    virtual void vd0(); virtual void vd4(); virtual void vd8();
    virtual void GetTransformedHull(cModel* model, cMWTransformedHull*& hull);    // 0xdc
    virtual void ReleaseTransformedHull(cMWTransformedHull*& hull);               // 0xe0
};

class cPlanetModel { public: float GetRadiusAt(const Vector3& pos); };    // 0x00b7ef70
cPlanetModel* PlanetModel();                                              // 0x00b3d350

struct cFootprint {
    uint32_t pad00[14];
    float   mScale;                       // +0x38
    float   mRadius;                      // +0x3c
    Vector3 mCenter;                      // +0x40
    eastl::vector<Vector3> mHull;         // +0x4c
};

extern const Vector3 kZeroVector;         // 0x01687ad4
extern const Vector3 kFootprintAxis;      // 0x016880e0

// 0x00b76b80: adds the point where edge (outside, inside) meets the planet surface.
void AddPlanetEdgePoint(HullVertex* outside, HullVertex* inside, eastl::vector<Vector3>* points,
                        cSPTransform* transform);
// 0x00b780d0: reduces points to their hull.
void BuildHull(eastl::vector<Vector3>* points, eastl::vector<Vector3>* hull);

inline void ClipEdge(HullVertex* a, HullVertex* b, eastl::vector<Vector3>* points, cSPTransform* transform)
{
    if (a->bOutside != b->bOutside) {
        if (a->bOutside == true && b->bOutside == false)
            AddPlanetEdgePoint(a, b, points, transform);
        else
            AddPlanetEdgePoint(b, a, points, transform);
    }
}

// @ 0xb78880
bool BuildFootprint(cFootprint* footprint, cModel* model, cModelWorld* world, bool bClipToPlanet)
{
    bool result = false;
    if (footprint && model && world) {
        cSPTransform* pTransform = &model->mTransform;
        cSPTransform savedTransform(*pTransform);
        pTransform->SetIdentity();
        pTransform->SetScale(footprint->mScale);

        sp_fixed_vector<Vector3, 256> points;
        int count = 0;
        Vector2* pPoints;
        if (GetPropertyAsVector2Array(model->mpPropList, 0x0637d439, &count, &pPoints) && count > 2) {
            float scale = footprint->mScale;
            Property* prop = 0;
            if (model->mpPropList->GetProperty(0x00fba611, prop))
                scale *= *prop->GetValueFloat();
            points.resize(count);
            for (int i = 0; i < count; i++) {
                const Vector2& src = pPoints[i];
                Vector3& p = points[i];
                p.x = src.x * scale;
                p.y = src.y * scale;
                p.z = 0.0f;
            }
        } else {
            cMWTransformedHull* hull = 0;
            world->GetTransformedHull(model, hull);
            if (hull) {
                if (bClipToPlanet) {
                    cPlanetModel* planet = PlanetModel();
                    cSPTransform transform(savedTransform);
                    sp_fixed_vector<HullVertex, 128> verts;
                    verts.resize(hull->mVertCount);
                    int numVerts = hull->mVertCount;
                    uint16_t hasRotation = transform.mFlags & 2;
                    for (int i = 0; i < numVerts; i++) {
                        HullVertex& v = verts[i];
                        v.pos = hull->mVertArray[i];
                        if (hasRotation)
                            v.pos *= transform.mRotation;
                        v.pos += transform.mTranslation;
                        float radius = planet->GetRadiusAt(v.pos);
                        v.bOutside = radius * radius < Dot(v.pos, v.pos);
                    }
                    int numTris = hull->mTriCount;
                    for (int i = 0; i < numTris; i++) {
                        uint32_t* tri = &hull->mTriArray[i * 4];
                        HullVertex* a = &verts[tri[0]];
                        HullVertex* b = &verts[tri[1]];
                        HullVertex* c = &verts[tri[2]];
                        ClipEdge(a, b, &points, &savedTransform);
                        ClipEdge(b, c, &points, &savedTransform);
                        ClipEdge(a, c, &points, &savedTransform);
                    }
                    if (points.size() == 0)
                        bClipToPlanet = false;
                }
                if (!bClipToPlanet) {
                    points.resize(hull->mVertCount);
                    int numVerts = hull->mVertCount;
                    for (int i = 0; i < numVerts; i++) {
                        const Vector3& v = hull->mVertArray[i];
                        // (x, z, y operand order: matches the original's /fp:fast schedule)
                        float d = v.x * kFootprintAxis.x + v.z * kFootprintAxis.z + v.y * kFootprintAxis.y;
                        points[i] = v - d * kFootprintAxis;
                    }
                }
                if (hull)
                    world->ReleaseTransformedHull(hull);
            }
        }

        BuildHull(&points, &footprint->mHull);
        result = footprint->mHull.size() >= 3;
        if (result) {
            footprint->mCenter = kZeroVector;
            int n = footprint->mHull.size();
            for (int i = 0; i < n; i++)
                footprint->mCenter += footprint->mHull[i];
            footprint->mCenter *= 1.0f / n;
            float maxDistSq = 0.0f;
            for (int i = 0; i < n; i++) {
                Vector3 d = footprint->mHull[i] - footprint->mCenter;
                float distSq = Dot(d, d);
                if (distSq > maxDistSq)
                    maxDistSq = distSq;
            }
            footprint->mRadius = sqrtf(maxDistSq);
        }
        *pTransform = savedTransform;
    }
    return result;
}
