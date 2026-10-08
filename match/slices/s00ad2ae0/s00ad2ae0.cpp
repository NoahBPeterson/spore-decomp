// Slice s00ad2ae0: FUN_00ad2ae0 (cdecl), the cinematic/scripted-action position resolver
// ("ComputeTargetPosition" in slice s00ad4b60's callers and s00ad3190).
//
// Returns the world position for a placement `mode` (switch 0..10) relative to something:
//   0 the raw offset                         1 the action target's own transform
//   2 a named cinematic object's transform   3 the herd of the target object (surface-aligned)
//   4 the target creature's tribe (via its aux transform)   5 the tribe's transform
//   6 the creature's city transform          7/8 a named cinematic target's transform
//   9/10 a named target, found by a search for ground near it and facing it
// The offset is first scaled by the target's scale (kind 1 or 2). Modes 1,2,3,7,8,9,10 snap
// the result to the planet surface (FUN_00b82b40), modes 4,5,6 clamp it (FUN_00b81630).
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc, same module as s00ad4b60 / s00ad3190).
#include "types.h"

struct Vector3 {
    float x, y, z;
    __forceinline Vector3() {}
    __forceinline Vector3(const Vector3& o) : x(o.x), y(o.y), z(o.z) {}
    __forceinline Vector3(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}
};
struct Quaternion { float x, y, z, w; };
struct Matrix3 { float m[3][3]; };

__forceinline Vector3 operator+(const Vector3& a, const Vector3& b)
{
    return Vector3(a.x + b.x, a.y + b.y, a.z + b.z);
}
__forceinline Vector3 operator-(const Vector3& a, const Vector3& b)
{
    return Vector3(a.x - b.x, a.y - b.y, a.z - b.z);
}

extern Vector3 kInvalidPosition;   // 0x0167A4BC

#define V(n) virtual void v##n()

// Game object interface (Cast at +0xB8, AddRef/Release at +0xBC/+0xC0).
struct cGameObject {
    V(00); V(04); V(08); V(0c); V(10); V(14); V(18); V(1c);
    virtual uint32_t GetTypeID();                                  // +0x20
    V(24); V(28);
    virtual const Vector3* GetPosition();                          // +0x2C
    virtual const Quaternion* GetOrientation();                    // +0x30
    V(34); V(38); V(3c); V(40); V(44); V(48); V(4c); V(50); V(54); V(58); V(5c);
    V(60); V(64); V(68); V(6c);
    virtual float GetScaleB();                                     // +0x70
    virtual float GetScaleA();                                     // +0x74
    V(78); V(7c); V(80); V(84); V(88); V(8c); V(90); V(94); V(98); V(9c); V(a0); V(a4);
    V(a8); V(ac); V(b0); V(b4);
    virtual cGameObject* Cast(uint32_t typeID);                    // +0xB8
    V(bc);
    virtual int Release();                                         // +0xC0
    virtual void* GetTransformObject();                            // +0xC4 (unused)
};

// Target of the action (0x30 bytes): placement data plus the object.
struct cActionTarget {
    Vector3 mPosition;                 // +0x00
    Quaternion mOrientation;           // +0x0C
    float mScaleA;                     // +0x1C
    float mScaleB;                     // +0x20
    float mUnused24, mUnused28;
    cGameObject* mpObject;             // +0x2C
    cActionTarget();                   // 0x00AD7940
    ~cActionTarget();                  // 0x00AD7AD0
    const Vector3* GetPosition();      // 0x00AD7B50
    const Quaternion* GetOrientation();   // 0x00AD7B70
    float GetScaleB();                 // 0x00AD7B10
    float GetScaleA();                 // 0x00AD7B30
};

// Message used to read an object's transform (ctor 0x00434040).
struct XformMsg {
    uint16_t a, b;
    Vector3 mPosition;                 // +0x04
    float mScale;                      // +0x10
    Matrix3 mMatrix;                   // +0x14
    XformMsg();                        // 0x00434040
};
struct cXformObject {
    V(00); V(04); V(08); V(0c); V(10); V(14); V(18); V(1c);
    virtual void GetTransform(XformMsg* msg);                      // +0x20
};

struct cCinematicManager {
    uint32_t pad[0x148 / 4];
    bool LookupTarget(uint32_t id, cActionTarget* out);       // 0x00ADB2A0
    bool LookupObject(uint32_t id, cXformObject** out);       // 0x00ADB1B0
};
cCinematicManager* CinematicManager();                          // 0x00B3D4D0

struct cPlanetModel {
    Quaternion BuildSurfaceOrientation(const Vector3& pos);                 // 0x00B7F190
    Vector3 ClampToSurface(const Vector3& src);                             // 0x00B81630
    Vector3 ProjectToSurface(const Vector3& src, int flag);                 // 0x00B82B40
    bool FindGround(const Vector3* from, float radius, Vector3* out, float scale, bool flag, int arg);   // 0x00B88770
};
cPlanetModel* PlanetModel();                                    // 0x00B3D350

Vector3 RotateByQuaternion(const Vector3& v, const Quaternion& q);      // 0x0059AED0
Quaternion QuaternionFromMatrix(const Matrix3& m);                      // 0x0046D660
Vector3 NormalizedSafe(const Vector3& v);                               // 0x00449C20
Matrix3* Matrix3FromFacingAndUp(Matrix3* dst, const Vector3& facing, const Vector3& up);   // 0x0069B440

// Citizen / tribe / city / herd objects reached through the target's object
struct cTransformable {
    V(00); V(04); V(08); V(0c); V(10); V(14); V(18); V(1c); V(20); V(24); V(28);
    virtual const Vector3* GetPosition();                          // +0x2C
    virtual const Quaternion* GetOrientation();                    // +0x30
};
struct cTribeAux {
    uint32_t pad[0x34 / 4];
    cTransformable mTransform;         // +0x34
};
struct cTribeBase {
    V(00); V(04); V(08); V(0c); V(10); V(14); V(18); V(1c); V(20); V(24); V(28); V(2c);
    V(30); V(34); V(38); V(3c); V(40); V(44); V(48); V(4c); V(50); V(54); V(58); V(5c);
    V(60); V(64); V(68); V(6c); V(70); V(74); V(78); V(7c); V(80); V(84); V(88); V(8c);
    V(90); V(94); V(98); V(9c); V(a0); V(a4); V(a8);
    virtual cTribeAux* GetAux();                                   // +0xAC
};
struct cTribeWithTransform {
    uint32_t pad[0x120 / 4];
    cTransformable mTransform;         // +0x120
};
struct cCitizen {
    cTribeBase* GetTribe();            // 0x00C22F50 (returned as base: used for slot 0xAC)
};
struct cCitizenB {
    cTribeWithTransform* GetTribe();   // 0x00C22F50
    cTribeWithTransform* GetCity();    // 0x00C23E40
};
struct cHerd {
    const Vector3* GetPosition();      // 0x00C6ACC0
};
struct cCreatureLike {
    cHerd* GetHerd();                  // 0x00C04590
};
cGameObject* CastToType(cGameObject* obj, uint32_t typeID);     // 0x00AC80D0

__forceinline void ScaleBy(Vector3& v, float s)
{
    v.x = v.x * s;
    v.y = v.y * s;
    v.z = s * v.z;
}

// @ 0x00AD2AE0
Vector3* ComputeTargetPosition(Vector3* out, cActionTarget* target, int mode, uint32_t id,
                               int kind, const Vector3* offset)
{
    cPlanetModel* planet = PlanetModel();
    out->x = kInvalidPosition.x;
    out->y = kInvalidPosition.y;
    out->z = kInvalidPosition.z;

    cGameObject* obj = target->mpObject ? target->mpObject->Cast(0x17f243b) : 0;
    if (!obj) {
        cActionTarget named;
        if (CinematicManager()->LookupTarget(id, &named))
            obj = named.mpObject ? named.mpObject->Cast(0x17f243b) : 0;
    }

    Vector3 v(*offset);
    if (kind == 1)
        ScaleBy(v, target->GetScaleA());
    else if (kind == 2)
        ScaleBy(v, target->GetScaleB());

    switch (mode) {
    case 0:
        *out = *offset;
        return out;
    case 1: {
        const Vector3* pos = target->GetPosition();
        Vector3 r = RotateByQuaternion(v, *target->GetOrientation());
        out->x = pos->x + r.x;
        out->y = r.y + pos->y;
        out->z = r.z + pos->z;
        *out = planet->ProjectToSurface(*out, 0);
        return out;
    }
    case 2: {
        cXformObject* ref = 0;
        if (!CinematicManager()->LookupObject(id, &ref))
            return out;
        XformMsg msg;
        ref->GetTransform(&msg);
        Quaternion q = QuaternionFromMatrix(msg.mMatrix);
        Vector3 r = RotateByQuaternion(*offset, q);
        out->x = r.x + msg.mPosition.x;
        out->y = r.y + msg.mPosition.y;
        out->z = r.z + msg.mPosition.z;
        *out = planet->ProjectToSurface(*out, 0);
        return out;
    }
    case 3: {
        cGameObject* o = CastToType(obj, 0x18eb45e);
        cHerd* herd = ((cCreatureLike*)o)->GetHerd();
        Quaternion q = planet->BuildSurfaceOrientation(*herd->GetPosition());
        Vector3 r = RotateByQuaternion(v, q);
        const Vector3* pos = herd->GetPosition();
        out->x = pos->x + r.x;
        out->y = r.y + pos->y;
        out->z = r.z + pos->z;
        *out = planet->ProjectToSurface(*out, 0);
        return out;
    }
    case 4: {
        cGameObject* o = CastToType(obj, 0x18eb4b7);
        cTribeAux* aux = ((cCitizen*)o)->GetTribe()->GetAux();
        Vector3 r = RotateByQuaternion(v, *aux->mTransform.GetOrientation());
        const Vector3* pos = aux->mTransform.GetPosition();
        out->x = r.x + pos->x;
        out->y = r.y + pos->y;
        out->z = r.z + pos->z;
        *out = planet->ClampToSurface(*out);
        return out;
    }
    case 5: {
        cGameObject* o = CastToType(obj, 0x18eb4b7);
        cTribeWithTransform* tribe = ((cCitizenB*)o)->GetTribe();
        Vector3 r = RotateByQuaternion(v, *tribe->mTransform.GetOrientation());
        const Vector3* pos = tribe->mTransform.GetPosition();
        out->x = r.x + pos->x;
        out->y = r.y + pos->y;
        out->z = r.z + pos->z;
        *out = planet->ClampToSurface(*out);
        return out;
    }
    case 6: {
        cGameObject* o = CastToType(obj, 0x18eb4b7);
        cTribeWithTransform* city = ((cCitizenB*)o)->GetCity();
        Vector3 r = RotateByQuaternion(v, *city->mTransform.GetOrientation());
        const Vector3* pos = city->mTransform.GetPosition();
        out->x = pos->x + r.x;
        out->y = r.y + pos->y;
        out->z = r.z + pos->z;
        *out = planet->ClampToSurface(*out);
        return out;
    }
    case 7:
    case 8: {
        cActionTarget named;
        if (CinematicManager()->LookupTarget(id, &named)) {
            Vector3 r = RotateByQuaternion(v, *named.GetOrientation());
            const Vector3* pos = named.GetPosition();
            out->x = pos->x + r.x;
            out->y = r.y + pos->y;
            out->z = r.z + pos->z;
            *out = planet->ProjectToSurface(*out, 0);
        }
        return out;
    }
    case 9:
    case 10: {
        cActionTarget named;
        if (CinematicManager()->LookupTarget(id, &named)) {
            *out = *named.GetPosition();
            if (planet->FindGround(named.GetPosition(), 100.0f, out, 1.0f, mode == 9, 0)) {
                const Vector3* tp = named.GetPosition();
                Vector3 d(tp->x - out->x, tp->y - out->y, tp->z - out->z);
                Matrix3 m;
                Matrix3FromFacingAndUp(&m, NormalizedSafe(d), NormalizedSafe(*out));
                Quaternion q = QuaternionFromMatrix(m);
                Vector3 r = RotateByQuaternion(v, q);
                out->x = out->x + r.x;
                out->y = r.y + out->y;
                out->z = r.z + out->z;
                *out = planet->ProjectToSurface(*out, 0);
            }
        }
        return out;
    }
    }
    return out;
}
