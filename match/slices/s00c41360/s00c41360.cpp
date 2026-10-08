// Slice s00c41360 — SP::cInterCityRoad: builds the road's path (mPathData, Vector3 list) from a curve
// that is routed between the two cities, trimmed to the city-wall radii and extended back to them.
// Retail layout (ModAPI): mpCity1 +0x11c, mpCity2 +0x120, mPathData +0x128 (retail sp_vector, 0x14 bytes).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc), same module family as s00b8c330.
#include <math.h>
#include "types.h"

void __cdecl operator_delete__(void* p);   // 0xf47380 (operator delete[])

inline void* operator new(unsigned int, void* p) throw() { return p; }

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    Vector3(const Vector3& o) : x(o.x), y(o.y), z(o.z) {}
};
inline Vector3 operator-(const Vector3& a, const Vector3& b) { return Vector3(a.x - b.x, a.y - b.y, a.z - b.z); }
inline Vector3 operator+(const Vector3& a, const Vector3& b) { return Vector3(a.x + b.x, a.y + b.y, a.z + b.z); }
inline Vector3 operator*(const Vector3& a, float s) { return Vector3(a.x * s, a.y * s, a.z * s); }
struct PodVec3 {    // trivially copyable (integer-register copies)
    float x, y, z;
};
bool __cdecl Vector3Equal(const PodVec3* a, const PodVec3* b);   // 0x004232c0
extern PodVec3 g_DefaultPosition;                                 // 0x0168e690 (also the "no position" marker)

struct sp_vector_allocator {
    const char* mpName;
    uint32_t mFlags;
    sp_vector_allocator() {}
    void deallocate(void* p) {
        if (((uint32_t*)p)[-1])
            operator_delete__(p);
    }
};

template <class T> struct SpVector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    sp_vector_allocator mAllocator;

    SpVector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~SpVector() { if (mpBegin) mAllocator.deallocate(mpBegin); }
    int size() const { return (int)(mpEnd - mpBegin); }
    bool empty() const { return mpBegin == mpEnd; }
    T& operator[](int i) { return mpBegin[i]; }
    T* begin() { return mpBegin; }
    T* end() { return mpEnd; }
    T* erase(T* first, T* last);
    T* insert(T* pos, const T& v);
    void DoInsertValue(T* pos, const T& v);
    void push_back_default();
    void push_back(const T& v)
    {
        if (mpEnd < mpCapacity)
            ::new (mpEnd++) T(v);
        else
            DoInsertValue(mpEnd, v);
    }
};

struct cCurvePoint {          // 0x3c bytes
    Vector3 mPos;             // +0x00
    float mF0c;               // +0x0c
    int mF10;                 // +0x10
    uint32_t pad14[(0x38 - 0x14) / 4];
    bool mF38;                // +0x38
    cCurvePoint(const Vector3& p) : mPos(p), mF0c(1.0f), mF10(0), mF38(false) {}
};

typedef SpVector<Vector3> Vec3Vector;
typedef SpVector<cCurvePoint> CurveVector;

template <> cCurvePoint* CurveVector::erase(cCurvePoint* first, cCurvePoint* last);          // 0xac4570
template <> cCurvePoint* CurveVector::insert(cCurvePoint* pos, const cCurvePoint& v);        // 0xc41190
template <> void CurveVector::push_back_default();                                           // 0xc410e0
template <> Vector3* Vec3Vector::erase(Vector3* first, Vector3* last);                       // 0x50f740
template <> void Vec3Vector::DoInsertValue(Vector3* pos, const Vector3& v);                  // 0x4b5ad0

struct cCurveParams {         // 20 bytes
    const char* mpName;
    void* mpA;
    void* mpFunc;
    void* mpB;
    void* mpC;
};
extern cCurveParams g_LandAvoidCitiesParams;          // 0x1565b54 ("landAvoidCities")

struct cCurveBuilder {
    void Build(const cCurveParams& params, const PodVec3& a, const PodVec3& b,
               CurveVector& out, float t0, float t1);  // 0xac6960
};
cCurveBuilder* __cdecl GetCurveBuilder();             // 0xb3d290

struct cCityWalls {
    char pad[0x25c];
    float mOuterRadius;                               // +0x25c
    const PodVec3& GetWallPosition(Vector3& out, const Vector3& towards, int flag);   // 0xbec660 (sret)
    const PodVec3& RequestPosition(Vector3& out, int mode);                           // 0xbec2d0 (sret)
};

struct cSpatialObject {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual const Vector3& GetPosition();             // +0x2c
};

struct cCity {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64(); virtual void v68();
    virtual cCityWalls* GetCityWalls();               // +0x6c
    char pad04[0x120 - 4 - 4 * 0];
    cSpatialObject mSpatial;                          // +0x120 (secondary base)
};

class cInterCityRoad {
public:
    char pad[0x11c];
    cCity* mpCity1;               // +0x11c
    cCity* mpCity2;               // +0x120
    int mRoadType;                // +0x124
    Vec3Vector mPathData;         // +0x128
    char pad13c[4];
    float mWidth;                 // +0x13c (unused here)
    void BuildPath();             // 0x00c41360
};

// @ 0x00c41360
void cInterCityRoad::BuildPath()
{
    mPathData.erase(mPathData.begin(), mPathData.end());

    if (mpCity1 && mpCity1->GetCityWalls() && mpCity2 && mpCity2->GetCityWalls()) {
        CurveVector curve;

        Vector3 tmp;
        PodVec3 posA = mpCity1->GetCityWalls()->GetWallPosition(tmp, mpCity2->mSpatial.GetPosition(), 0);
        PodVec3 posB = mpCity2->GetCityWalls()->GetWallPosition(tmp, mpCity1->mSpatial.GetPosition(), 0);
        if (Vector3Equal(&posA, &g_DefaultPosition))
            posA = mpCity1->GetCityWalls()->RequestPosition(tmp, 5);
        if (Vector3Equal(&posB, &g_DefaultPosition))
            posB = mpCity2->GetCityWalls()->RequestPosition(tmp, 5);

        GetCurveBuilder()->Build(g_LandAvoidCitiesParams, posA, posB, curve, 0.0f, 1.0f);

        // drop the tail of the curve starting at the first point inside city 2's wall radius
        for (unsigned i = 0; i < (unsigned)curve.size(); ++i) {
            Vector3 d = curve[i].mPos - mpCity2->mSpatial.GetPosition();
            cCityWalls* w = mpCity2->GetCityWalls();
            float len = sqrtf(d.x * d.x + d.z * d.z + d.y * d.y);
            if (len < w->mOuterRadius + 1.0f) {
                curve.erase(&curve[i], curve.end());
                break;
            }
        }
        // drop the head of the curve up to the last point inside city 1's wall radius
        for (int i = curve.size(); i != 0; --i) {
            Vector3 d = curve[i - 1].mPos - mpCity1->mSpatial.GetPosition();
            cCityWalls* w = mpCity1->GetCityWalls();
            float len = sqrtf(d.x * d.x + d.z * d.z + d.y * d.y);
            if (len < w->mOuterRadius + 1.0f) {
                curve.erase(curve.begin(), &curve[i]);
                break;
            }
        }

        if (curve.begin() != curve.end()) {
            // first point too far from city 1: add a start point on the wall circle
            {
                const Vector3* p = &curve.begin()->mPos;
                Vector3 d = *p - mpCity1->mSpatial.GetPosition();
                cCityWalls* w = mpCity1->GetCityWalls();
                float len = sqrtf(d.x * d.x + d.z * d.z + d.y * d.y);
                if (len > w->mOuterRadius + 3.0f) {
                    float r = mpCity1->GetCityWalls()->mOuterRadius + 1.0f;
                    cCurvePoint* first = curve.begin();
                    Vector3 d2 = first->mPos - mpCity1->mSpatial.GetPosition();
                    float inv = 1.0f / sqrtf(d2.x * d2.x + d2.z * d2.z + d2.y * d2.y);
                    Vector3 off = d2 * inv * r;
                    Vector3 np = mpCity1->mSpatial.GetPosition() + off;
                    curve.insert(curve.begin(), cCurvePoint(Vector3(g_DefaultPosition.x, g_DefaultPosition.y, g_DefaultPosition.z)));
                    curve.begin()->mPos = np;
                }
            }
            // last point too far from city 2: add an end point on the wall circle
            {
                cCurvePoint* last = curve.end() - 1;
                Vector3 d = last->mPos - mpCity2->mSpatial.GetPosition();
                cCityWalls* w = mpCity2->GetCityWalls();
                float len = sqrtf(d.x * d.x + d.z * d.z + d.y * d.y);
                if (len > w->mOuterRadius + 3.0f) {
                    float r = mpCity2->GetCityWalls()->mOuterRadius + 1.0f;
                    cCurvePoint* last2 = curve.end() - 1;
                    Vector3 d2 = last2->mPos - mpCity2->mSpatial.GetPosition();
                    float inv = 1.0f / sqrtf(d2.x * d2.x + d2.z * d2.z + d2.y * d2.y);
                    Vector3 off = d2 * inv * r;
                    Vector3 np = off + mpCity2->mSpatial.GetPosition();
                    curve.push_back_default();
                    (curve.end() - 1)->mPos = np;
                }
            }
        }

        int n = curve.size();
        for (int i = 0; i < n; ++i)
            mPathData.push_back(curve[i].mPos);
    }
}
