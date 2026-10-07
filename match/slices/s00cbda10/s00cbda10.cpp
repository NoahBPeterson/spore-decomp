// Slice s00cbda10: the single function in this slice is
//   0x00CBDA10  Simulator::cCulturalProjectile::LaunchProjectile   (3113 bytes, __thiscall, ret 0x20)
//
// (Ghidra's label "EA::COM::interface_cast<cCulturalTarget,...>" is wrong; ModAPI lists this
// function as cCulturalProjectile::LaunchProjectile.)
//
// Stores the owner's political id, the vehicle / target / tool refs and the two flags, then
// builds the flight path as a vector of points:
//   - spin mode (mbSpin): a 12-point circle (radius 1) around the target, oriented from +Z
//     to the target direction; the point nearest to the projectile picks the start angle,
//     and the approach ends at a circle point of radius 4 (turret) or 8 at a height of
//     1 (turret), 5 (vehicle) or 3;
//   - vehicle/animal targets: a random aim point of the target;
//   - otherwise the target position pushed out 10 units along its own direction;
//   then 32 points from the projectile to that end point, raised along the local "up"
//   (arched for hostile/cultural shots, a hump otherwise), and in spin mode 60 more points
//   spiralling up around the target.
// Finally creates a cPathFollowingLocomotion over the points and sets the desired speed
// (doubled against vehicles).
//
// Build flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc: the original has no EH frame,
// although it has a vector local with a destructor).
#include "types.h"

#pragma warning(disable: 4100)

inline void* operator new(unsigned int, void* p) throw() { return p; }
inline void operator delete(void*, void*) throw() {}
void* __cdecl operator new(unsigned int size, const char* pName, int flags, unsigned debugFlags,
                           const char* file, int line);                     // 0x00f473a0
void __cdecl operator delete[](void* p);                                    // 0x00f47380

extern "C" double __cdecl sqrt(double);
extern "C" double __cdecl sin(double);
extern "C" double __cdecl cos(double);
#pragma intrinsic(sqrt, sin, cos)

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
    Vector3 operator+(const Vector3& b) const { return Vector3(x + b.x, y + b.y, z + b.z); }
    Vector3 operator-(const Vector3& b) const { return Vector3(x - b.x, y - b.y, z - b.z); }
    Vector3 operator*(float s) const { return Vector3(x * s, y * s, z * s); }
    Vector3 operator/(float s) const { float inv = 1.0f / s; return Vector3(x * inv, y * inv, z * inv); }
    Vector3& operator+=(const Vector3& b) { x += b.x; y += b.y; z += b.z; return *this; }
    float Length() const { return (float)sqrt(x * x + y * y + z * z); }
    Vector3 Normalized() const
    {
        float inv = 1.0f / (float)sqrt(x * x + y * y + z * z + 1e-8f);
        return Vector3(x * inv, y * inv, z * inv);
    }
    void Normalize()
    {
        float inv = 1.0f / (float)sqrt(x * x + y * y + z * z + 1e-8f);
        x *= inv; y *= inv; z *= inv;
    }
    inline void Rotate(const struct Matrix3& r);
    static const Vector3 ZERO;     // 0x0169a414
    static const Vector3 Z_AXIS;   // 0x0157d380 (0, 0, 1)
};

struct Matrix3 {
    float m[3][3];
    Matrix3& operator=(const Matrix3& o);    // 0x0041cb40 (out of line)
    static const Matrix3 IDENTITY;           // 0x0169aa44
};

// row vector * matrix, in place
inline void Vector3::Rotate(const Matrix3& r)
{
    float nx = x * r.m[0][0] + y * r.m[1][0] + z * r.m[2][0];
    float ny = x * r.m[0][1] + y * r.m[1][1] + z * r.m[2][1];
    float nz = x * r.m[0][2] + y * r.m[1][2] + z * r.m[2][2];
    x = nx; y = ny; z = nz;
}

Vector3 normalized_safe(const Vector3& v);  // 0x00449c20 SP::normalized_safe

extern float kTwoPi;                         // 0x0169aa28 (runtime-initialized float)

struct Transform {
    enum { kTransformFlagScale = 1, kTransformFlagRotation = 2, kTransformFlagOffset = 4 };
    int16_t mnFlags;
    int16_t mnTransformCount;
    Vector3 mOffset;
    float   mfScale;
    Matrix3 mRotation;

    Transform() : mOffset(Vector3::ZERO), mnFlags(0), mnTransformCount(0), mfScale(1.0f)
    {
        mRotation = Matrix3::IDENTITY;
    }
    const Vector3& GetOffset() const { return mOffset; }
    Transform& SetOffset(const Vector3& v)
    {
        mOffset = v;   // NB: implicit Vector3 operator= (field copy)
        mnFlags |= kTransformFlagOffset;
        mnTransformCount++;
        return *this;
    }
    Transform& PreTranslate(const Vector3& v)
    {
        mOffset += v;
        mnFlags |= kTransformFlagOffset;
        mnTransformCount++;
        return *this;
    }
    Transform& PreRotate(const Vector3& from, const Vector3& to);   // 0x006ba840
    Vector3 Apply(Vector3 v) const
    {
        if (mnFlags & kTransformFlagRotation)
            v.Rotate(mRotation);
        return mOffset + v * mfScale;
    }
};

// eastl::vector<Vector3, sp_vector_allocator>
struct Vector3Vector {
    Vector3* mpBegin;
    Vector3* mpEnd;
    Vector3* mpCapacity;
    uint32_t mAllocator;

    Vector3Vector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~Vector3Vector()
    {
        if (mpBegin) {
            if (((uint32_t*)mpBegin)[-1])
                operator delete[](mpBegin);
        }
    }
    Vector3* erase(Vector3* first, Vector3* last);               // 0x0050f740
    void DoInsertValue(Vector3* position, const Vector3& value);  // 0x004b5ad0
    void clear() { erase(mpBegin, mpEnd); }
    void push_back(const Vector3& value)
    {
        if (mpEnd < mpCapacity)
            ::new(mpEnd++) Vector3(value);
        else
            DoInsertValue(mpEnd, value);
    }
};

template <class T> struct intrusive_ptr {
    T* mpObject;
    T* get() const { return mpObject; }
    intrusive_ptr& operator=(T* pObject)
    {
        if (pObject != mpObject) {
            T* const pTemp = mpObject;
            if (pObject)
                pObject->AddRef();
            mpObject = pObject;
            if (pTemp)
                pTemp->Release();
        }
        return *this;
    }
};

// --- interfaces (only the vtable slots this function uses) ---
struct cGameData {
    virtual int AddRef();                       // 0x00
    virtual int Release();                      // 0x04
    virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48();
    virtual uint32_t GetPoliticalID();          // 0x4c
    uint32_t gameDataFields[0x30 / 4];
};

struct cCombatant {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20();
    virtual int GetRandomAimIndex();            // 0x24
    virtual Vector3 GetAimPoint(int index);     // 0x28
    virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58();
    virtual void* Cast(uint32_t type);          // 0x5c
    virtual int AddRef();                       // 0x60
    virtual int Release();                      // 0x64
};

struct cSpaceToolData {
    virtual void v00();
    virtual int AddRef();                       // 0x04
    virtual int Release();                      // 0x08
};

struct cPathFollowingLocomotion {
    virtual int AddRef();                       // 0x00
    virtual int Release();                      // 0x04
    cPathFollowingLocomotion(const Vector3Vector& points, uint32_t motionID);   // 0x00cbaf00
    uint32_t data[0x4c / 4];
};

// cCulturalTarget / cBuilding / cTurret / cVehicle / cCreatureAnimal ::TYPE
enum {
    kCulturalTargetType = 0x3D5C477,
    kBuildingType       = 0xE9CB8BA,
    kTurretType         = 0x436F315,
    kVehicleType        = 0x137E8E0,
    kCreatureAnimalType = 0xD0036E08,
    kProjectileMotion   = 0x82CE6992,
};

template <uint32_t TYPE> inline void* object_cast(cCombatant* p)
{
    return p ? p->Cast(TYPE) : 0;
}

class cLocomotiveObject {   // secondary base at +0x34
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual const Vector3& GetPosition();       // 0x2c
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
    virtual void v70(); virtual void v74(); virtual void v78(); virtual void v7c();
    virtual void v80(); virtual void v84(); virtual void v88(); virtual void v8c();
    virtual void v90(); virtual void v94(); virtual void v98(); virtual void v9c();
    virtual void va0(); virtual void va4(); virtual void va8(); virtual void vac();
    virtual void vb0(); virtual void vb4(); virtual void vb8(); virtual void vbc();
    virtual void vc0();
    virtual void SetDesiredSpeed(float speed, int arg);   // 0xc4

    void SetLocomotion(cPathFollowingLocomotion* p);      // 0x00c421b0

    uint32_t pad04[(0x1f0 - 4) / 4];
    int field_1f0;                              // this+0x224
    uint32_t pad1f4[(0x4d0 - 0x1f4) / 4];
};

class cCulturalProjectile : public cGameData, public cLocomotiveObject {
public:
    void LaunchProjectile(cGameData* owner, cGameData* vehicle, cSpaceToolData* tool,
                          cCombatant* target, const Vector3& targetPos, float speed,
                          bool arg_538, bool spin);

    uint32_t projectile[0x14 / 4];              // 0x504 cProjectile base (unused here)
    intrusive_ptr<cPathFollowingLocomotion> mpLocomotion;   // 0x518
    intrusive_ptr<cGameData> mpVehicle;         // 0x51c
    intrusive_ptr<cCombatant> mpTarget;         // 0x520
    intrusive_ptr<cSpaceToolData> mpTool;       // 0x524
    int field_528;                              // 0x528 (aim index)
    Vector3 mTargetPos;                         // 0x52c
    bool field_538;                             // 0x538
    bool mbSpin;                                // 0x539
    uint32_t pad53c[(0x560 - 0x53c) / 4];
    uint32_t mOwner;                            // 0x560 (owner's political id)
};

static inline float RingAngle(int i) { return (float)i * kTwoPi / -12.0f; }

// @ 0x00cbda10
void cCulturalProjectile::LaunchProjectile(cGameData* owner, cGameData* vehicle, cSpaceToolData* tool,
                                           cCombatant* target, const Vector3& targetPos, float speed,
                                           bool arg_538, bool spin)
{
    mOwner = owner->GetPoliticalID();
    mpVehicle = vehicle;
    mpTarget = target;
    mpTool = tool;
    field_538 = arg_538;
    mbSpin = spin;

    bool bArched = object_cast<kCulturalTargetType>(target) || GetPoliticalID() != vehicle->GetPoliticalID();
    bool isBuilding = object_cast<kBuildingType>(target) != 0;
    bool isTurret = object_cast<kTurretType>(target) != 0;
    bool isVehicle = object_cast<kVehicleType>(target) != 0;
    bool isAnimal = object_cast<kCreatureAnimalType>(target) != 0;

    field_1f0 = 5;

    Vector3Vector points;
    points.clear();

    Transform ring;
    float minDistance = 3.402823466e+38f;
    int startIndex = 0;
    float height = isTurret ? 1.0f : (isVehicle ? 5.0f : 3.0f);

    Vector3 endPoint;
    if (mbSpin) {
        Vector3 dir(targetPos);
        dir.Normalize();
        ring.PreRotate(Vector3::Z_AXIS, dir);
        ring.PreTranslate(targetPos);

        int nearest = 0;
        for (int i = 0; i < 12; i++) {
            float angle = RingAngle(i);
            Vector3 p = ring.Apply(Vector3((float)sin(angle), (float)cos(angle), 0.0f));
            float distance = (p - GetPosition()).Length();
            if (distance < minDistance) {
                minDistance = distance;
                nearest = i;
            }
        }
        startIndex = nearest + 3;
        float angle = RingAngle(startIndex);
        endPoint = ring.Apply(Vector3((float)sin(angle) * (isTurret ? 4.0f : 8.0f),
                                      (float)cos(angle) * (isTurret ? 4.0f : 8.0f), height));
    }
    else if (!isVehicle && !isAnimal) {
        endPoint = targetPos;
        endPoint += normalized_safe(endPoint) * 10.0f;
    }
    else {
        field_528 = target->GetRandomAimIndex();
        endPoint = target->GetAimPoint(field_528);
    }

    Vector3 position = GetPosition();
    Vector3 delta = endPoint - GetPosition();
    float length = delta.Length();
    Vector3 step = delta / length * (length / 33.0f);

    float lift = 0.0f;
    for (int i = 0; i < 32; i++) {
        if (bArched)
            lift += (32 - i) * 0.033f;
        else if (i < 16)
            lift += (16 - i) * (isBuilding ? 0.1f : 0.05f);
        else
            lift -= (i - 16) * (isBuilding ? 0.1f : 0.05f);

        Vector3 p = position + position.Normalized() * lift;
        points.push_back(p);
        mTargetPos = p;
        position += step;
    }

    if (mbSpin) {
        for (int i = startIndex; i < startIndex + 60; i++) {
            float angle = RingAngle(i);
            float x = (float)sin(angle) * (isTurret ? 4.0f : 8.0f);
            float y = (float)cos(angle) * (isTurret ? 4.0f : 8.0f);
            height += (isTurret || isVehicle) ? 0.1f : 0.2f;
            Vector3 p = ring.Apply(Vector3(x, y, height));
            points.push_back(p);
            mTargetPos = p;
        }
    }

    mpLocomotion = new("Simulator/cPathFollowingLocomotion", 0, 0, 0, 0)
        cPathFollowingLocomotion(points, kProjectileMotion);
    SetLocomotion(mpLocomotion.get());

    if (isVehicle)
        speed *= 2.0f;
    SetDesiredSpeed(speed, 0);
}
