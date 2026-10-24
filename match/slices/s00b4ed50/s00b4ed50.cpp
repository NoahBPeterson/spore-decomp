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
    hkVector4(hkReal _x, hkReal _y, hkReal _z, hkReal _w) : x(_x), y(_y), z(_z), w(_w) {}
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

// =============================================================================================
// 0x00b4f3e0 .. 0x00b4fc80: registration helpers, an orthonormal-basis factory, Havok object
// copy constructors and the hash-table erase/rehash/find primitives of the same object.
// =============================================================================================
#include <new>

// ---- Havok memory manager: slot +0x10 = allocate, slot +0x14 = deallocate -------------------
class hkMemoryManager {
public:
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
    virtual void* allocate(int nbytes, int align);              // slot 4 (+0x10)
    virtual void  deallocate(void* p, int nbytes, int tag);     // slot 5 (+0x14)
};
extern hkMemoryManager* gMemoryManager;         // 0x016e4178

struct Vector3 { float x, y, z; };
extern Vector3 gPerpBase;                       // 0x0167ecf4

// world a Havok entity/body lives in (0x01083ff0 / 0x01083110 / 0x0108c790 family)
class hkWorld {
public:
    char pad00[0x84];
    void* m_array;                              // +0x84
    char pad88[4];
    void* m_broadphase;                         // +0x8c
    void addAabb(const hkVector4* aabb);        // 0x01083ff0
    void touch(const hkVector4* a, const hkVector4* b);   // 0x01083ff1 (never called)
    void removeEntity(char* flag, void* obj);   // 0x01083110
};

// hkReferencedObject header (size/flags, refcount) plus the world link
class hkRefObject {
public:
    void* mVtable;                              // +0x00
    unsigned short mSizeAndFlags;               // +0x04
    unsigned short mRefCount;                   // +0x06
    hkWorld* mWorld;                            // +0x08

    void removeReference();                     // 0x0109ae60
    void baseDtor();                            // 0x0108c790
    void* scalarDtor(int flags);
};

extern hkRefObject* gRegistered_167ecd4;        // 0x0167ecd4

// ---- listener/sample-ref bookkeeping --------------------------------------------------------
struct ListenerRef {            // arg->mRef
    char pad00[0x10];
    int  mEntityOffset;         // +0x10  self-relative offset of the entity
    char pad14[4];
    char mActive;               // +0x18  must be 1
};

struct ListenerArg {
    hkEntity* mEntity;          // +0x00
    ListenerRef* mRef;          // +0x04
    char mEnabled;              // +0x08
};

struct EntityLink { char pad00[0xc]; hkEntity* mLinked; };   // hkEntity +0x0c

class ListOwner {
public:
    void append(void* p);       // 0x00aef2c0
    void remove(void* p);       // 0x00aef2d0
};

// ---- 0x00b4f470 factory object (0x30 bytes; built by 0x010c2730) ----------------------------
class hkPerpVectors {
public:
    void* mVtable;                              // +0x00
    unsigned short mSizeAndFlags;               // +0x04
    unsigned short mRefCount;                   // +0x06
    unsigned int mFlags;                        // +0x08
    float mScale;                               // +0x0c
    hkVector4 mA;                               // +0x10
    hkVector4 mB;                               // +0x20
    hkPerpVectors(const hkVector4& a, const hkVector4& b, float scale);   // 0x010c2730
};

// ---- 0x00b4f5?0 transform-like matrix copied by 0x00b4d3f0 --------------------------------
struct Mat50 {
    float m0;                                   // +0x00
    float m4;                                   // +0x04
    char pad08[8];
    float m16[16];                              // +0x10
    void CopyFrom(const Mat50& src);            // 0x00b4d3f0
};

// 0x74-byte "shape instance" with the matrix at +0x20
struct Inner {
    int m0;                                     // +0x00
    int m4;                                     // +0x04
    int m8;                                     // +0x08
    int mC;                                     // +0x0c
    float m10;                                  // +0x10
    int m14;                                    // +0x14
    int m18;                                    // +0x18
    char pad1c[4];
    Mat50 mH;                                   // +0x20
    int m70;                                    // +0x70

    Inner() {}
    Inner(const Inner& src);
};

struct Key3 { int m0, m4, m8; };
// 0x84-byte wrapper: three key dwords followed by the 0x74-byte instance
class Outer {
public:
    int m0;                                     // +0x00
    int m4;                                     // +0x04
    int m8;                                     // +0x08
    char pad0c[4];
    Inner mInner;                               // +0x10
    Outer(const Key3& key, const Inner& inner);
};

// ---- render settings referenced by 0x00b4f660 ----------------------------------------------
struct RenderCfg {
    int mModeA;                                 // +0x00 (0x01569af8) = 4
    int mModeB;                                 // +0x04 (0x01569afc) = 2
    float mScale;                               // +0x08 (0.3)
    float mBias;                                // +0x0c (0.05)
    float mLimit;                               // +0x10 (10)
};
extern RenderCfg gRenderCfg;                    // 0x01569af8
extern const float kAabbMargin;                 // 0x01485720

struct FlagWord { char pad00[4]; unsigned int mFlags; };    // +0x04

int __cdecl FUN_00b65250(void* obj, int mode, float value, int index);   // 0x00b65250
int __cdecl FUN_00b653d0(void* obj, int mode, float value, int index);   // 0x00b653d0

// ---- hash table with 0x90-byte nodes (next at +0x90) ---------------------------------------
struct Node90 {
    unsigned int mKey0;                         // +0x00
    unsigned int mKey4;                         // +0x04
    char pad08[0x88];
    Node90* mNext;                              // +0x90
};
struct LinkNode {
    unsigned int mKey0;                         // +0x00
    unsigned int mKey4;                         // +0x04
    unsigned int mKey8;                         // +0x08
    char pad0c[0x84];
    LinkNode* mNext;                            // +0x90
};
struct Bucket90 { Node90* mHead; };
struct It90 { Node90* mNode; Bucket90* mBucket; };
class Table90 {
public:
    char pad00[0xc];
    int mCount;                                 // +0x0c
    It90 erase(Node90* node, Bucket90* bucket);
};

// ---- hash table with 0x10-byte links (next at +0x10) ---------------------------------------
struct Node10 {
    unsigned int mKey0;                         // +0x00    unsigned int mKey4;                         // +0x04
    unsigned int mKey8;                         // +0x08
    unsigned int mKeyC;                         // +0x0c
    Node10* mNext;                              // +0x10
};
struct Bucket10 { Node10* mHead; };
struct It10 { Node10* mNode; Bucket10* mBucket; };
class Table10 {
public:
    char pad00[0xc];
    int mCount;                                 // +0x0c
    It10 erase(Node10* node, Bucket10* bucket);
};

// ---- open-addressed bucket table rehashed by 0x00b4fbd0 ------------------------------------
struct NodeB {
    unsigned int mHash0;                        // +0x00
    unsigned int mHash4;                        // +0x04
    char pad08[4];
    NodeB* mNext;                               // +0x0c
};
class TableB {
public:
    char pad00[4];
    NodeB** mBuckets;                           // +0x04
    unsigned int mNumBuckets;                   // +0x08
    int mCount;                                 // +0x0c
    char pad10[0xc];
    NodeB* mFreeList;                           // +0x1c
    char pad20[4];
    char* mHeapLo;                              // +0x24
    char* mHeapHi;                              // +0x28
    char pad2c[4];
    void* mStatic;                              // +0x30

    NodeB** reserveBuckets(unsigned int n);     // 0x00c763d0
    void rehash(unsigned int n);
};

// ---- 0x00b4fc80 property loader target ------------------------------------------------------
struct PropHolder {
    char pad00[0x80];
    float mVecX;                                // +0x80
    float mVecY;                                // +0x84
    float mVecZ;                                // +0x88
    float mVecW;                                // +0x8c
    char pad90[4];
    float mPropA;                               // +0x94
    float mPropB;                               // +0x98
    float mPropC;                               // +0x9c
    float mPropD;                               // +0xa0
    char padA4[0xc];
    signed char mFlag;                          // +0xb0
};

float __cdecl SP_GetPropertyFloat(void* set, unsigned int key, float def);      // 0x004e1c70
int   __cdecl SP_GetPropertyChar(void* set, unsigned int key, int def);         // 0x004e1c30
bool  __cdecl SP_GetPropertyAsVector3(void* set, unsigned int key, Vector3* out);  // 0x006a1110

// @ 0x00b4f3e0
void __stdcall FUN_00b4f3e0(ListenerArg* arg)
{
    ListenerRef* ref = arg->mRef;
    if (ref->mActive != 1)
        return;
    hkEntity* e = (hkEntity*)((char*)ref + ref->mEntityOffset);
    if (!e)
        return;
    hkEntity* ent = arg->mEntity;
    if (e == ((EntityLink*)ent)->mLinked)
        return;
    void* p = e->getProperty(4).p;
    if (p)
        ((ListOwner*)p)->append(ent);
}

// @ 0x00b4f420
void __stdcall FUN_00b4f420(ListenerArg* arg)
{
    if (!arg->mEnabled)
        return;
    ListenerRef* ref = arg->mRef;
    if (ref->mActive != 1)
        return;
    hkEntity* e = (hkEntity*)((char*)ref + ref->mEntityOffset);
    if (!e)
        return;
    hkEntity* ent = arg->mEntity;
    if (e == ((EntityLink*)ent)->mLinked)
        return;
    void* p = e->getProperty(4).p;
    if (p)
        ((ListOwner*)p)->remove(ent);
}

// @ 0x00b4f470
hkPerpVectors* __cdecl FUN_00b4f470(const Vector3* v)
{
    float w;
    float sx = gPerpBase.x, sy = gPerpBase.y, sz = gPerpBase.z;
    float tx = gPerpBase.x, ty = gPerpBase.y, tz = gPerpBase.z;
    const float y = v->y;
    const float z = v->z;

    if (z > y && z > v->x) {
        w = 0.25f * (v->x + y);
        tz = 0.5f * z - w;
        sz = -tz;
    } else if (y > v->x) {
        w = 0.25f * (v->x + z);
        ty = 0.5f * y - w;
        sy = -ty;
    } else {
        w = 0.25f * (y + z);
        tx = 0.5f * v->x - w;
        sx = -tx;
    }

    hkPerpVectors* obj = (hkPerpVectors*)gMemoryManager->allocate(0x30, 0x24);
    obj->mSizeAndFlags = 0x30;
    hkVector4 a(tx, ty, tz, 0.0f);
    hkVector4 b(sx, sy, sz, 0.0f);
    new (obj) hkPerpVectors(a, b, w);
    return obj;
}

// @ 0x00b4f610
Inner::Inner(const Inner& src)
{
    m0 = src.m0;
    m4 = src.m4;
    m8 = src.m8;
    mC = src.mC;
    m10 = src.m10;
    m14 = src.m14;
    m18 = src.m18;
    mH.CopyFrom(src.mH);
    m70 = src.m70;
}

// @ 0x00b4f660
int __cdecl FUN_00b4f660(void* obj, float value, int index, int kind)
{
    int r = 0;
    if (obj) {
        unsigned int flags = ((FlagWord*)obj)->mFlags;
        bool enabled = (flags & 0x4000) != 0;
        bool skipped = (flags & 0x40000) != 0;
        if (enabled) {
            int i = index;
            float f = value;
            if (!skipped) {
                if (kind == 3)
                    r = FUN_00b653d0(obj, gRenderCfg.mModeA, f, i);
                else if (kind == 6)
                    r = FUN_00b65250(obj, gRenderCfg.mModeB, f, i);
            }
        }
    }
    return r;
}

// @ 0x00b4f6d0
void __cdecl FUN_00b4f6d0(Loco* loco, hkRefObject* ent)
{
    if (!ent)
        return;
    if (loco) {
        Aabb box;
        hkVector4 lo, hi;
        loco->GetAabb(&box);
        const float margin = kAabbMargin;
        box.v[0] = box.v[0] - margin;
        box.v[1] = box.v[1] - margin;
        box.v[2] = box.v[2] - margin;
        box.v[3] = box.v[3] + margin;
        box.v[4] = box.v[4] + margin;
        box.v[5] = box.v[5] + margin;
        lo = hkVector4(box.v[0], box.v[1], box.v[2], 0.0f);
        hi = hkVector4(box.v[3], box.v[4], box.v[5], 0.0f);
        ent->mWorld->addAabb(&lo);
    }
    char flag;
    ent->mWorld->removeEntity(&flag, ent);
}

// @ 0x00b4f7c0
void* hkRefObject::scalarDtor(int flags)
{
    baseDtor();
    if (flags & 1)
        gMemoryManager->deallocate(this, mSizeAndFlags, 0x2e);
    return this;
}

// @ 0x00b4f7f0
void __cdecl FUN_00b4f7f0()
{
    if (!gRegistered_167ecd4)
        return;
    gRegistered_167ecd4->removeReference();
    if (gRegistered_167ecd4) {
        __declspec(align(16)) hkVector4 scratch;
        gRegistered_167ecd4->mWorld->removeEntity(((char*)&scratch) + 15, gRegistered_167ecd4);
    }
    gRegistered_167ecd4 = 0;
}

// @ 0x00b4f830
Outer::Outer(const Key3& key, const Inner& inner)
{
    m0 = key.m0;
    m4 = key.m4;
    m8 = key.m8;
    mInner.m0 = inner.m0;
    mInner.m4 = inner.m4;
    mInner.m8 = inner.m8;
    mInner.mC = inner.mC;
    mInner.m10 = inner.m10;
    mInner.m14 = inner.m14;
    mInner.m18 = inner.m18;
    mInner.mH.CopyFrom(inner.mH);
    mInner.m70 = inner.m70;
}

// @ 0x00b4f8a0
It90 Table90::erase(Node90* node, Bucket90* bucket)
{
    It90 it;
    it.mNode = node->mNext;
    it.mBucket = bucket;
    while (!it.mNode) {
        unsigned int step = sizeof(Bucket90);
        it.mBucket = (Bucket90*)((char*)it.mBucket + step);
        it.mNode = it.mBucket->mHead;
    }
    if (bucket->mHead == node) {
        bucket->mHead = node->mNext;
        ::operator delete[](node);
        this->mCount = this->mCount - 1;
        return it;
    }
    Node90* prev = bucket->mHead;
    Node90* p = prev->mNext;
    while (p != node) {
        prev = p;
        p = p->mNext;
    }
    prev->mNext = node->mNext;
    ::operator delete[](node);
    Table90* self2 = this;
    --self2->mCount;
    return it;
}

// @ 0x00b4f930
It10 Table10::erase(Node10* node, Bucket10* bucket)
{
    It10 it;
    it.mNode = node->mNext;
    it.mBucket = bucket;
    while (!it.mNode) {
        unsigned int step = sizeof(Bucket10);
        it.mBucket = (Bucket10*)((char*)it.mBucket + step);
        it.mNode = it.mBucket->mHead;
    }
    if (bucket->mHead == node) {
        Bucket10* self = bucket;
        self->mHead = node->mNext;
        ::operator delete[](node);
        int n = mCount;
        mCount = n - 1;
        return it;
    }
    Node10* prev = bucket->mHead;
    Node10* p = prev->mNext;
    while (p != node) {
        prev = p;
        p = p->mNext;
    }
    prev->mNext = node->mNext;
    ::operator delete[](node);
    this->mCount = this->mCount - 1;
    return it;
}

struct CopyBait {
    void* mThis;
    CopyBait(void* p) : mThis(p) {}
    void* retSelf() { return this; }
};

// @ 0x00b4fae0
LinkNode* __stdcall FUN_00b4fae0(LinkNode* head, const Key3* key, int unused)
{
    if (!head)
        return 0;
    do {
        if (key->m0 == (int)head->mKey0 && key->m4 == (int)head->mKey4 && key->m8 == (int)head->mKey8)
            return head;
        head = head->mNext;
    } while (head);
    return 0;
}

// @ 0x00b4fbd0
void TableB::rehash(unsigned int n)
{
    NodeB** newBuckets = reserveBuckets(n);
    for (unsigned int i = 0; i < mNumBuckets; ++i) {
        NodeB* node = mBuckets[i];
        while (node) {
            unsigned int h = (node->mHash0 + node->mHash4) % n;
            NodeB* next = node->mNext;
            mBuckets[i] = next;
            node->mNext = newBuckets[h];
            newBuckets[h] = node;
            node = next;
            (void)node;
        }
    }
    if (mNumBuckets > 1 && mBuckets != (NodeB**)mStatic) {
        if ((char*)mBuckets < mHeapLo || (char*)mBuckets >= mHeapHi) {
            ::operator delete[](mBuckets);
        } else {
            *(NodeB**)mBuckets = mFreeList;
            mFreeList = (NodeB*)mBuckets;
        }
    }
    mBuckets = newBuckets;
    mNumBuckets = n;
}

// @ 0x00b4fc80
void __cdecl FUN_00b4fc80(PropHolder* self, void* unused, void* props)
{
    if (!props)
        return;
    self->mPropB = SP_GetPropertyFloat(props, 0x635002bd, self->mPropB);
    self->mPropA = SP_GetPropertyFloat(props, 0x959b621c, self->mPropA);
    self->mPropC = SP_GetPropertyFloat(props, 0xfe64124b, self->mPropC);
    self->mPropD = SP_GetPropertyFloat(props, 0xc09b2ebf, self->mPropD);
    self->mFlag = SP_GetPropertyChar(props, 0x57a59e5f, self->mFlag);
    Vector3 v;
    if (SP_GetPropertyAsVector3(props, 0xfc485e65, &v)) {
        self->mVecX = v.x;
        self->mVecY = v.y;
        self->mVecZ = v.z;
        self->mVecW = 0.0f;
    }
}
