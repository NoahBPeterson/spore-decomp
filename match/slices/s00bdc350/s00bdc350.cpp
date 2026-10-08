// Slice s00bdc350: cCity::<find a free spot near the city walls> (0x00bdca30, 1772 bytes, __thiscall,
// hidden Vector3 return + one int arg, ret 8).  The method name is Claude-coined; class layout from the ModAPI
// cCity (mpCityWalls +0x324, field_32C Vector3 +0x32c) and the earlier cCity::Initialize slice (s00be7bf0).
//
// What it does: given a mode (0/2 = sample around the walls' requested position, 1 = around the stored
// target position of the walls, other = the default), it builds a target point 2 units beyond the walls'
// RequestPosition (modes 0/2) or takes the walls' stored position (mode 1; if field_32C is still the zero
// vector it returns zero straight away), sets up a cCommunityLayout (cActionCircle) of radius 136 at
// target + 4*dir, asks the collision manager for the objects inside that circle, and walks the layout's
// candidate points (0x18-byte records, position at +0xc): each is projected to the planet surface, rejected
// when too close to the walls (mode 1: nearer than the walls' radius; others: closer than walls radius +
// the circle's radius), randomly pushed outwards in mode 2, rejected when blocked (IsPointFree) or
// within 16 units (squared 255.99998) of any queried object. The first accepted point is returned,
// otherwise the target point. All temporaries (object list with Release of every element) are freed.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS- (no /EHsc).
#include "types.h"

typedef unsigned int size_t;
void operator delete[](void* p);                                         // 0x00f47380
#include <math.h>

struct Vector3 {
    float x, y, z;
    __forceinline Vector3() {}
    __forceinline Vector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    __forceinline Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
    __forceinline Vector3 operator-(const Vector3& v) const { return Vector3(x - v.x, y - v.y, z - v.z); }
    __forceinline Vector3 operator*(float s) const { return Vector3(x * s, y * s, z * s); }
    __forceinline Vector3& operator+=(const Vector3& v) { x += v.x; y += v.y; z += v.z; return *this; }
};
__forceinline Vector3 operator+(const Vector3& a, const Vector3& b) { return Vector3(a.x + b.x, a.y + b.y, a.z + b.z); }

__forceinline Vector3 Normalized(const Vector3& v)
{
    float inv = 1.0f / sqrtf(v.x * v.x + v.y * v.y + v.z * v.z + 1e-8f);
    return Vector3(v.x * inv, v.y * inv, v.z * inv);
}
__forceinline float Length(const Vector3& v) { return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z); }
__forceinline float LengthSquared(const Vector3& v) { return v.x * v.x + v.y * v.y + v.z * v.z; }

extern Vector3 g_ZeroVector;        // 0x0168bd70  (Vector3::ZERO)

// SP's vector allocator keeps a header word in front of each block.
struct sp_vector_allocator {
    uint32_t mData[2];
};
__forceinline void SpFree(void* p)
{
    if (((uint32_t*)p)[-1] != 0)
        operator delete[](p);
}

template <class T> struct intrusive_ptr {
    T* mpObject;
    __forceinline intrusive_ptr() : mpObject(0) {}
    __forceinline ~intrusive_ptr() { if (mpObject) intrusive_ptr_release(mpObject); }
    __forceinline T* get() const { return mpObject; }
    __forceinline T* operator->() const { return mpObject; }
};

template <class T> struct SpVector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    sp_vector_allocator mAllocator;

    __forceinline SpVector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    __forceinline ~SpVector()
    {
        for (T* p = mpBegin; p < mpEnd; ++p)
            p->~T();
        if (mpBegin) SpFree(mpBegin);
    }
};

class cSpatialObject {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual const Vector3& GetPosition();                                // 0x2c
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
    virtual void v70(); virtual void v74(); virtual void v78(); virtual void v7c();
    virtual void v80(); virtual void v84(); virtual void v88(); virtual void v8c();
    virtual void v90(); virtual void v94(); virtual void v98(); virtual void v9c();
    virtual void va0(); virtual void va4(); virtual void va8(); virtual void vac();
    virtual void vb0(); virtual void vb4(); virtual void vb8(); virtual int SpAddRef();   // 0xbc
    virtual int SpRelease();                                             // 0xc0
};
__forceinline void intrusive_ptr_release(cSpatialObject* p) { p->SpRelease(); }

// The walls object (cCityWalls) as used here.
class cCityWalls {
public:
    Vector3* GetPosition(Vector3* out);                                  // 0x00bec190 (thiscall, ret 4)
    Vector3* RequestPosition(Vector3* out, int arg);                     // 0x00bec2d0 (thiscall, ret 8)
    Vector3* GetStoredPosition(Vector3* out);                            // 0x00bec760 (thiscall, ret 4): copies +0x230
    uint32_t pad[0x25c / 4];
    float mRadius;                                                       // +0x25c
};

// cCommunityLayout / cActionCircle: the result list (0x18-byte records, position at +0xc) is at +0x50.
struct tLayoutPoint {
    uint32_t pad[3];
    Vector3 mPosition;                                                   // +0x0c
};
class cCommunityLayout {
public:
    cCommunityLayout();                                                  // 0x00afba10
    ~cCommunityLayout();                                                 // 0x00afbad0
    void SetCenter(const Vector3& pos, float radius, const Vector3& dir, float arg);   // 0x00af9cf0 (ret 0x10)
    void SetSlots(int arg, float spacing);                               // 0x00afef10 (ret 8)

    uint32_t mHead[0xc / 4];
    float mRadius;                                                       // +0x0c
    float mField10;                                                      // +0x10
    Vector3 mCenter;                                                     // +0x14
    uint32_t mBody[(0x50 - 0x20) / 4];
    tLayoutPoint* mpPointsBegin;                                         // +0x50
    tLayoutPoint* mpPointsEnd;                                           // +0x54
    tLayoutPoint* mpPointsCapacity;                                      // +0x58
};

class cObjectQuery {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44();
    virtual void FindInSphere(const Vector3* center, float radius, SpVector<intrusive_ptr<cSpatialObject> >* out,
                              int a, int b, int c);                      // 0x48 (ret 0x18)
};
cObjectQuery* ObjectQuery();                                             // 0x00b3d240

class cPlanetModel {
public:
    void Flush();                                                        // 0x00b88420
    Vector3 ToSurface(const Vector3& pos);                               // 0x00b81630
};
cPlanetModel* PlanetModel();                                             // 0x00b3d350

bool IsPointFree(int kind, const Vector3* pos);                       // 0x00c9e8e0
float RandomPushFactor();                                                // 0x00c9eb60 (cdecl, float in st0)

class cCity {
public:
    Vector3 FindSpot(int mode);                                          // 0x00bdca30

    uint32_t pad0[0x324 / 4];
    cCityWalls* mpCityWalls;                                             // +0x324
    uint32_t pad328[1];
    Vector3 field_32C;                                                   // +0x32c
};

// @ 0x00BDCA30
Vector3 cCity::FindSpot(int mode)
{
    Vector3 target = g_ZeroVector;
    float radiusSq;

    switch (mode) {
    case 0:
    case 2: {
        Vector3 requested;
        mpCityWalls->RequestPosition(&requested, 0);
        Vector3 center;
        mpCityWalls->GetPosition(&center);
        target = requested + Normalized(requested - center) * 2.0f;
        break;
    }
    case 1: {
        if (field_32C.x == g_ZeroVector.x && field_32C.y == g_ZeroVector.y && field_32C.z == g_ZeroVector.z)
            return g_ZeroVector;
        Vector3 stored;
        target = *mpCityWalls->GetStoredPosition(&stored);
        Vector3 center;
        mpCityWalls->GetPosition(&center);
        radiusSq = LengthSquared(target - center);
        break;
    }
    }

    Vector3 wallsPos;
    mpCityWalls->GetPosition(&wallsPos);
    Vector3 dir = Normalized(target - wallsPos);

    cCommunityLayout layout;
    Vector3 layoutCenter = dir * 4.0f + target;
    layout.SetCenter(layoutCenter, 136.0f, dir, 0.0f);
    layout.SetSlots(0, 4.0f);

    SpVector<intrusive_ptr<cSpatialObject> > objects;
    ObjectQuery()->FindInSphere(&layout.mCenter, layout.mRadius, &objects, 0, 0, 0);
    const int numObjects = objects.mpEnd - objects.mpBegin;
    const int numPoints = layout.mpPointsEnd - layout.mpPointsBegin;
    PlanetModel()->Flush();

    for (int i = 0; i < numPoints; i++) {
        Vector3 p = PlanetModel()->ToSurface(layout.mpPointsBegin[i].mPosition);
        if (mode == 1) {
            Vector3 center;
            mpCityWalls->GetPosition(&center);
            if (radiusSq > LengthSquared(p - center))
                continue;
        } else if (mode == 2) {
            float push = RandomPushFactor();
            p += Normalized(p) * push;
        }

        const float spare = layout.mField10;
        if (mpCityWalls) {
            Vector3 center;
            mpCityWalls->GetPosition(&center);
            if (mpCityWalls->mRadius + spare > Length(p - center))
                continue;
        }
        if (!IsPointFree(mode, &p))
            continue;

        bool tooClose = false;
        for (int j = 0; j < numObjects; j++) {
            if (tooClose)
                break;
            const Vector3& q = objects.mpBegin[j]->GetPosition();
            if (LengthSquared(q - p) < 255.99998f)
                tooClose = true;
        }
        if (tooClose)
            continue;
        return p;
    }
    return target;
}
