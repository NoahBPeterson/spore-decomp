// Slice s00b4ed50 -- 0x00b4ed50, 1671 bytes (__cdecl, 6 stack args).
//
// Per-frame "keep a floating body at its radial rest depth" step for a locomotive object standing
// on a planet.  For the Havok entity `ent` (its hkRigidMotion lives at ent+0x58) it
//   * returns false at once when there is no entity, the entity is flagged (+0x99) or the object's
//     flag +0x75 is clear; also returns false when the entity is not active, or neither the sim flag
//     (+0x26) nor the object's FUN_00c887c0() value (< threshold) allows it;
//   * normalizes the motion position (+0x40) into the radial "up" direction n, derives the radial
//     depth from the object's bounds (and its AABB when entity property 8 is set, else from the
//     motion's velocity-sized vector at +0x60) and asks FUN_00b4ec70 for a correction vector;
//   * scales it by dt into an impulse, clears obj->grounded (+0x77) and, when the entity has an
//     owner proxy (property 4), accumulates the impulse into it (splitting the owner's pending
//     vector into radial and tangential parts unless the goal override applies); without an owner
//     it applies a linear impulse and a torque impulse to the rigid motion directly.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (SSE scalar math; x87 for sqrt).

#include "types.h"

#pragma warning(disable: 4100)

extern "C" double __cdecl sqrt(double);
#pragma intrinsic(sqrt)

typedef float hkReal;

class __declspec(align(16)) hkVector4 {
public:
    hkReal x, y, z, w;
    hkVector4() {}
    hkVector4(const hkVector4& v) : x(v.x), y(v.y), z(v.z), w(v.w) {}
    void operator=(const hkVector4& v) { x = v.x; y = v.y; z = v.z; w = v.w; }
};

class hkBool {
public:
    hkBool() {}
    hkBool(bool b) : m_bool(b ? 1 : 0) {}
    operator bool() const { return m_bool != 0; }
private:
    char m_bool;
};

static __forceinline hkReal hkSqrtInverse(hkReal r) { return (hkReal)(1.0f / sqrt(r)); }

static __forceinline double LengthXYZ(const hkVector4& v)
{
    return sqrt((double)v.x * v.x + (double)v.y * v.y + (double)v.z * v.z);
}
static __forceinline double LengthXZY(const hkVector4& v)
{
    return sqrt((double)v.x * v.x + (double)v.z * v.z + (double)v.y * v.y);
}

struct hkPropertyValue {
    union { int i; float f; void* p; };
    int hi;
    hkPropertyValue() {}
};

// ---- Havok rigid motion (retail 3.1 layout; slots counted from the vtable) -----------------
class hkRigidMotion {
public:
    virtual void s0();  virtual void s1();  virtual void s2();  virtual void s3();
    virtual void s4();  virtual void s5();  virtual void s6();  virtual void s7();
    virtual void s8();  virtual void s9();  virtual void s10(); virtual void s11();
    virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
    virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
    virtual void applyLinearImpulse(const hkVector4& imp);       // slot 24 (+0x60)
    virtual void s25();
    virtual void applyAngularImpulse(const hkVector4& imp);      // slot 26 (+0x68)

    // (hkVector4 members would pad the vptr out to 16 bytes, so address them by offset)
    const hkVector4* position() const { return (const hkVector4*)((const char*)this + 0x40); }
    const hkVector4* velocity() const { return (const hkVector4*)((const char*)this + 0x60); }   // xyz used

    float getMass() const;          // 0x01088270
};

// ---- owner proxy of an entity (entity property 4) ------------------------------------------
struct Owner {
    char pad00[0xa0];
    hkVector4 m_pending;            // +0xa0  accumulated change (impulse / mass)
    float m_invScale;               // +0xb0
    char padb4[0xc8 - 0xb4];
    bool m_flagC8;                  // +0xc8
    char padc9[3];
    int m_intCC;                    // +0xcc

    const hkVector4* GetPending();                  // 0x00aef400 (returns this + 0xa0)
    void AddImpulse(const hkVector4* v);            // 0x00aef570
};

class hkEntity {
public:
    char pad00[0x4c];
    int m_propBase;                 // +0x4c
    int m_propCount;                // +0x50
    char pad54[4];
    hkRigidMotion* m_motion;        // +0x58
    char pad5c[0x99 - 0x5c];
    bool m_flag99;                  // +0x99

    hkPropertyValue getProperty(uint32_t key) const;    // 0x00496140
    hkBool isActive() const;                            // 0x01088ac0
    void activate();                                    // 0x01088ae0
};

struct Bounds { float pad0[2]; float lo; float pad1[2]; float hi; };
struct Aabb { float v[6]; };       // min xyz, max xyz

class Loco {
public:
    virtual void s0();  virtual void s1();  virtual void s2();  virtual void s3();
    virtual void s4();  virtual void s5();  virtual void s6();  virtual void s7();
    virtual void s8();  virtual void s9();  virtual void s10(); virtual void s11();
    virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
    virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
    virtual void s24(); virtual void s25();
    virtual Bounds* GetBounds();                    // slot 26 (+0x68)
    virtual const Aabb* GetAabb(Aabb* out);         // slot 27 (+0x6c)

    char pad04[0x75 - 4];
    bool m_flag75;                  // +0x75
    char pad76;
    bool m_grounded;                // +0x77

    float FUN_00c887c0();           // 0x00c887c0
};

struct GoalState { char pad[0x5c]; int m_value; };
struct GoalHolder { GoalState* FUN_00c41ec0(); };       // 0x00c41ec0

struct Sim { char pad[0x26]; bool b26; };
Sim* __cdecl GetSim();                                  // 0x00b3d310

struct Planet { float GetRadiusAt(const hkVector4* p); };   // 0x00b7ef70
Planet* __cdecl GetPlanetModel();                       // 0x00b3d350

bool __cdecl FUN_00b4ec70(hkVector4* out, float a, float b, float c, const hkVector4* dir, float d);
const hkVector4* __cdecl FUN_00b658c0(hkVector4* out, hkEntity* e);   // 0x00b658c0
const hkVector4* __cdecl FUN_00b65950(hkVector4* out, hkEntity* e);   // 0x00b65950

extern const float kRestThreshold;      // 0x01569ac4
extern bool gUseTangential;             // 0x01569ab9
extern const float kForceScaleA;        // 0x0167eb7c
extern const float kForceScaleB;        // 0x0167eb80
extern const float kTorqueScale;        // 0x0167eb84

// @ 0x00b4ed50
bool __cdecl FUN_00b4ed50(float dt, Loco* obj, GoalHolder* goal, hkEntity* ent, float depthRef, float limit)
{
    if (!ent || ent->m_flag99 || !obj->m_flag75)
        return false;

    bool result = false;
    Owner* owner = (Owner*)ent->getProperty(4).p;
    if (ent->isActive() && (GetSim()->b26 || obj->FUN_00c887c0() < kRestThreshold)) {
        hkVector4 a;            // property-3 value, correction vector, then the radial/tangent split
        hkVector4 b;            // box centre scratch, then the impulse
        hkVector4 c;            // radial direction, then the tangential part / torque
        *(int*)&a.x = ent->getProperty(3).i;
        const hkVector4* pos = ent->m_motion->position();
        Bounds* bounds = obj->GetBounds();

        // radial direction of the position
        const hkReal lenSq = pos->x * pos->x + pos->y * pos->y + pos->z * pos->z;
        hkReal inv = 0.0f;
        if (lenSq != 0.0f)
            inv = hkSqrtInverse(lenSq);
        c.x = pos->x * inv;
        c.y = pos->y * inv;
        c.z = pos->z * inv;
        c.w = pos->w * inv;

        float centre = (bounds->hi - bounds->lo) * 0.5f + bounds->lo;
        float radial;
        if (ent->getProperty(8).i != 0) {
            Aabb box;
            const Aabb* ab = obj->GetAabb(&box);
            b.x = (ab->v[0] + ab->v[3]) * 0.5f;
            b.z = (ab->v[5] + ab->v[2]) * 0.5f;
            b.y = (ab->v[4] + ab->v[1]) * 0.5f;
            radial = (float)(LengthXZY(b) - centre);
        } else {
            const hkVector4* v = ent->m_motion->velocity();
            radial = (float)LengthXYZ(*v);
        }

        GetPlanetModel()->GetRadiusAt(pos);
        double posLen = LengthXYZ(*pos);
        double depth = ((double)depthRef - posLen) + (bounds->hi - bounds->lo) * 0.5f;
        if (!(depth > 0.0) || !FUN_00b4ec70(&a, radial, a.x, depthRef, &c, limit))
            return false;

        b.x = a.x * dt;
        b.y = a.y * dt;
        b.z = a.z * dt;
        b.w = a.w * dt;
        result = true;
        obj->m_grounded = false;

        if (owner) {
            owner->m_intCC = 0;
            owner->m_flagC8 = true;
            bool noGoal = goal && goal->FUN_00c41ec0()->m_value == 0;
            float wTerm, wScale;
            if (gUseTangential && !noGoal) {
                const hkVector4* u = owner->GetPending();
                float d = (u->x * c.x + u->z * c.z) + u->y * c.y;
                a.x = d * c.x;
                a.y = c.y * d;
                a.z = c.z * d;
                a.w = c.w * d;
                c.x = u->x - a.x;
                c.y = u->y - a.y;
                c.z = u->z - a.z;
                c.w = u->w - a.w;
                float mass = ent->m_motion->getMass();
                float s1 = -((mass * kForceScaleA) * dt);
                b.x = s1 * a.x + b.x;
                b.y = a.y * s1 + b.y;
                b.z = a.z * s1 + b.z;
                b.w = a.w * s1 + b.w;
                mass = ent->m_motion->getMass();
                float s2 = -((mass * kForceScaleB) * dt);
                b.x = s2 * c.x + b.x;
                b.y = c.y * s2 + b.y;
                b.z = c.z * s2 + b.z;
                wTerm = c.w;
                wScale = s2;
            } else {
                float mass = ent->m_motion->getMass();
                const hkVector4* u = owner->GetPending();
                float s = -((mass * kForceScaleA) * dt);
                b.x = u->x * s + b.x;
                b.y = u->y * s + b.y;
                b.z = u->z * s + b.z;
                wTerm = u->w;
                wScale = s;
            }
            b.w = wTerm * wScale + b.w;
            owner->AddImpulse(&b);
            return result;
        }

        // no owner proxy: push the rigid motion directly
        float mass = ent->m_motion->getMass();
        hkVector4 tmp;
        const hkVector4* r = FUN_00b658c0(&tmp, ent);
        float s = -((mass * kForceScaleA) * dt);
        b.x = r->x * s + b.x;
        b.y = r->y * s + b.y;
        b.z = r->z * s + b.z;
        b.w = r->w * s + b.w;
        mass = ent->m_motion->getMass();
        const hkVector4* r2 = FUN_00b65950(&tmp, ent);
        float s3 = -((mass * kTorqueScale) * dt);
        c.x = s3 * r2->x;
        c.y = r2->y * s3;
        c.z = r2->z * s3;
        c.w = r2->w * s3;
        ent->activate();
        ent->m_motion->applyLinearImpulse(b);
        ent->activate();
        ent->m_motion->applyAngularImpulse(c);
    }
    return result;
}
