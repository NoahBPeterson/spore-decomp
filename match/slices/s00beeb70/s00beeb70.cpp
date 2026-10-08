// Slice s00beeb70: FUN_00beeb70, vehicle/object (re)initialisation from its owning city.
//
// Assigns the owner city (intrusive pointer at +0x264), copies the city's locator position and
// orientation into the object's own locator (+0x34), picks a model/type id from the city's vehicle
// specialty when none is given, registers the 8 hard-coded offset points of the global table at
// 0x01469150 in the point vector (+0x15c), then rotates four fixed offset vectors by the
// locator's quaternion, scales them by mScale (+0x25c), adds the locator position, projects
// them onto the planet surface and stores them in the 4-point record array (+0x198).
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE  (movss scalar math, no EH frame)
#include "types.h"

extern "C" void* __cdecl memset(void* dst, int val, unsigned int n);   // thunk 0x011e073e
#pragma function(memset)

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(const Vector3& o) : x(o.x), y(o.y), z(o.z) {}
    Vector3(float a, float b, float c) : x(a), y(b), z(c) {}
};
struct Quaternion { float x, y, z, w; };

extern Vector3 g_PointOffsets[8];   // 0x01469150
extern float g_C478;   // 0x0168c478
extern float g_C47C;   // 0x0168c47c
extern float g_C480;   // 0x0168c480
extern float g_C484;   // 0x0168c484
extern float g_C488;   // 0x0168c488
extern float g_C48C;   // 0x0168c48c

// eastl::vector<Vector3, sp allocator>, 0x14 bytes
struct SpVector {
    Vector3* mpBegin;
    Vector3* mpEnd;
    Vector3* mpCapacity;
    uint32_t mAllocator[2];
    void DoInsertValue(Vector3* pos, const Vector3& v);   // 0x004b5ad0
    Vector3& push_back()
    {
        if (mpEnd < mpCapacity)
            ++mpEnd;
        else {
            Vector3 tmp;
            DoInsertValue(mpEnd, tmp);
        }
        return mpEnd[-1];
    }
};

struct Locator {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual const Vector3* GetPosition();                       // 0x2c
    virtual const Quaternion* GetOrientation();                 // 0x30
    virtual void v34();
    virtual void SetPosition(const Vector3* p);                 // 0x38
    virtual void SetOrientation(const Quaternion* q);           // 0x3c
};

struct IntrusiveObj {
    virtual void AddRef();
    virtual void Release();
};

struct cCity : IntrusiveObj {
    uint32_t pad04[0x47];
    Locator  mLocator;      // +0x120
    int      GetVehicleSpecialty();          // 0x00bd81d0 (reads +0x540)
    const Vector3* FUN_00bd99e0();           // 0x00bd99e0
};

struct cPlanetModel {
    Vector3 DirectionToSurfacePosition(const Vector3& dir);   // 0x00b815a0
    Vector3 FUN_00b81630(const Vector3& pos);                  // 0x00b81630
};
cPlanetModel* PlanetModel();    // 0x00b3d350 (cdecl)
int FUN_00bebc90(int a, int b); // 0x00bebc90 (cdecl)

struct Rec4 {
    Vector3 p[8];
};

// Rotates (vx,vy,vz) by q and scales it by s.
__forceinline Vector3 RotateScaled(const Quaternion& q, const float* ps, float vx, float vy, float vz)
{
    float xx = q.x * q.x, yy = q.y * q.y, zz = q.z * q.z;
    float xy = q.y * q.x, xz = q.z * q.x, yz = q.z * q.y;
    float wx = q.w * q.x, wy = q.w * q.y, wz = q.w * q.z;
    float rx = (((xy - wz) * vy + (wy + xz) * vz) * 2.0f + (1.0f - (zz + yy) * 2.0f) * vx) * *ps;
    float ry = (((yz - wx) * vz + (wz + xy) * vx) * 2.0f + (1.0f - (zz + xx) * 2.0f) * vy) * *ps;
    float rz = (((wx + yz) * vy + (xz - wy) * vx) * 2.0f + (1.0f - (yy + xx) * 2.0f) * vz) * *ps;
    return Vector3(rx, ry, rz);
}
__forceinline Vector3 AddPos(const Locator& loc, const Vector3& o)
{
    const Vector3* p = const_cast<Locator&>(loc).GetPosition();
    return Vector3(p->x + o.x, p->y + o.y, p->z + o.z);
}

class cVehicleLike {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void SetModel(int id);   // 0x60

    uint32_t pad04[0xa];            // 0x04..0x2c
    uint32_t mOwnerPtr;             // +0x2c   (used by SetGameDataOwner2)
    uint32_t mOwnerId;              // +0x30
    Locator  mLocator;              // +0x34 (embedded object, own vptr)
    uint32_t pad38[0x49];           // to 0x15c
    SpVector mPoints;               // +0x15c
    uint32_t pad170[10];
    Rec4*    mpRecs;                // +0x198
    uint32_t pad19c[0x30];          // to 0x25c
    float    mScale;                // +0x25c
    uint32_t pad260;
    IntrusiveObj* mpCity;           // +0x264
    Vector3  mV268;                 // +0x268
    uint32_t mBlock274[49];         // +0x274 .. 0x338
    Vector3  mPos;                  // +0x338
    uint32_t pad344[2];
    int      mSpecialtyArg;         // +0x34c

    void SetGameDataOwner2(cCity* city);    // 0x00b18550
    void FUN_00bee150();                    // 0x00bee150

    void Init(cCity* city, int model);      // 0x00beeb70
};

// @ 0x00beeb70
void cVehicleLike::Init(cCity* city, int model)
{
    if (city != mpCity) {
        IntrusiveObj* old = mpCity;
        if (city)
            city->AddRef();
        mpCity = city;
        if (old)
            old->Release();
    }
    SetGameDataOwner2(city);
    mPos = *city->mLocator.GetPosition();
    mLocator.SetPosition(&mPos);
    mLocator.SetOrientation(city->mLocator.GetOrientation());
    mV268 = *city->FUN_00bd99e0();
    if (model == 0)
        model = FUN_00bebc90(city->GetVehicleSpecialty(), mSpecialtyArg);
    SetModel(model);

    for (int i = 0; i < 8; ++i) {
        Vector3& r = mPoints.push_back();
        Vector3 t(g_PointOffsets[i]);
        r = t;
    }
    FUN_00bee150();

    const Quaternion* qp = mLocator.GetOrientation();
    Quaternion q;
    q.x = qp->x; q.y = qp->y; q.z = qp->z; q.w = qp->w;
    Vector3 o0 = RotateScaled(q, &mScale, g_C478, g_C47C, g_C480);
    mpRecs->p[0] = PlanetModel()->DirectionToSurfacePosition(AddPos(mLocator, o0));
    Vector3 o1 = RotateScaled(q, &mScale, g_C484, g_C488, g_C48C);
    mpRecs->p[1] = PlanetModel()->DirectionToSurfacePosition(AddPos(mLocator, o1));
    Vector3 o2 = RotateScaled(q, &mScale, -g_C484, -g_C488, -g_C48C);
    mpRecs->p[2] = PlanetModel()->DirectionToSurfacePosition(AddPos(mLocator, o2));
    Vector3 o3 = RotateScaled(q, &mScale, -g_C478, -g_C47C, -g_C480);
    mpRecs->p[3] = PlanetModel()->FUN_00b81630(AddPos(mLocator, o3));
    mpRecs->p[4] = mpRecs->p[2];
    mpRecs->p[5] = mpRecs->p[1];
    memset(mBlock274, 0, sizeof(mBlock274));
}
