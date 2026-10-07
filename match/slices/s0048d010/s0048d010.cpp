// Slice s0048d010: SP::cSPEditorManipulationStacking helper + small Havok ctor/dtor/copy helpers.
// 0x48d010 is the retail MoveBlockLowAngleStacking: a __cdecl free function in retail (the dev PDB has
// it as a cSPEditorManipulationStacking member). Its Havok locals are 16-byte aligned, so the slice
// is compiled with /Oy added (no effect on the ordinary frames of the small helpers).
// Module flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

template<int N> inline void ScratchSlots() { uint32_t s[N]; }

struct Vector3T {
    float x, y, z;
    Vector3T() {}
    float& operator[](int i) { return (&x)[i]; }
    const float& operator[](int i) const { return (&x)[i]; }
};
struct cSPVector3 : Vector3T {
    cSPVector3() {}
    __forceinline cSPVector3(const Vector3T& v) { x = v.x; y = v.y; z = v.z; }
    cSPVector3& operator=(const Vector3T& v) { x = v.x; y = v.y; z = v.z; return *this; }
};

// hkMemory singleton (vtable slot 5 = Free)
struct hkMemory {
    virtual void _v0();
    virtual void _v1();
    virtual void _v2();
    virtual void _v3();
    virtual void _v4();
    virtual void* Free(void* p, int align, int size);
};
extern hkMemory* g_hkMemory;                    // @ 0x16e4178

// ---- small Havok object ctor/dtor/copy helpers ----
struct HkObj {
    char data0[4];
    float mField4;                              // +0x04
    char data1[0x20 - 8];
    float mArray[4];                            // +0x20
    int mField30;                               // +0x30
    char rest[0x40 - 0x34];
    void* F_48db10(unsigned flags);             // @ 0x48db10
    void  F_48db60();                           // @ 0x48db60
    void* F_48dbb0(unsigned flags);             // @ 0x48dbb0
    void* F_48dc50(HkObj* src);                 // @ 0x48dc50
};

// @ 0x48db10
void* HkObj::F_48db10(unsigned flags)
{
    *(void**)this = (void*)0x13ef534;
    if (flags & 1) {
        hkMemory* node = g_hkMemory;
        node->Free(this, 8, 0x1c);
    }
    return this;
}

// @ 0x48db60
void HkObj::F_48db60()
{
    mField30 = 0;
    float k = *(float*)0x13ef4f8;
    mArray[3] = k;
    mField4 = *(float*)0x13ef4f8;
}

// @ 0x48dbb0
void* HkObj::F_48dbb0(unsigned flags)
{
    *(void**)this = (void*)0x13ef52c;
    *(void**)this = (void*)0x13ef534;
    if (flags & 1) {
        hkMemory* node = g_hkMemory;
        node->Free(this, 8, 0x1c);
    }
    return this;
}

// @ 0x48dc50
void* HkObj::F_48dc50(HkObj* src)
{
    *(float*)((char*)this + 0x0) = *(float*)((char*)src + 0x0);
    *(float*)((char*)this + 0x4) = *(float*)((char*)src + 0x4);
    *(float*)((char*)this + 0x8) = *(float*)((char*)src + 0x8);
    *(float*)((char*)this + 0xc) = *(float*)((char*)src + 0xc);
    float* d = (float*)((char*)src + 0x10);
    float* s = (float*)((char*)this + 0x10);
    s[0] = d[0]; s[1] = d[1]; s[2] = d[2]; s[3] = d[3];
    return this;
}

// ---- 0x48d010: MoveBlockLowAngleStacking ----
// Havok 3.1 FPU math types (layouts: match/include/havok31/hkReflectedClasses.h).
typedef float hkReal;
extern "C" double __cdecl fabs(double);
#pragma intrinsic(fabs)

struct hkBool {
    char m_bool;
    hkBool(bool b) { m_bool = (char)b; }
    operator bool() const { return m_bool != 0; }
};

struct __declspec(align(16)) hkVector4 {
    hkReal x, y, z, w;
    __forceinline hkVector4() {}
    __forceinline hkVector4(hkReal a, hkReal b, hkReal c, hkReal d) { x = a; y = b; z = c; w = d; }
    __forceinline hkVector4(const hkVector4& v) { x = v.x; y = v.y; z = v.z; w = v.w; }
    __forceinline void operator=(const hkVector4& v) { x = v.x; y = v.y; z = v.z; w = v.w; }
    __forceinline hkReal& operator()(int i) { return (&x)[i]; }
    __forceinline const hkReal& operator()(int i) const { return (&x)[i]; }
    __forceinline void setInterpolate4(const hkVector4& v0, const hkVector4& v1, hkReal t)
    {
        const hkReal s = 1.0f - t;
        (*this)(0) = s * v0(0) + t * v1(0);
        (*this)(1) = s * v0(1) + t * v1(1);
        (*this)(2) = s * v0(2) + t * v1(2);
        (*this)(3) = s * v0(3) + t * v1(3);
    }
};

struct hkMatrix3 {
    hkVector4 m_col0, m_col1, m_col2;
    __forceinline hkMatrix3() {}
    hkMatrix3(const hkMatrix3& m);              // @ 0x48daf0
    void operator=(const hkMatrix3& m);         // @ 0x44a8c0
};
struct hkRotation : hkMatrix3 {
    __forceinline hkRotation() {}
    __forceinline hkRotation(const hkRotation& r) : hkMatrix3(r) {}
};

struct hkTransform {
    hkRotation m_rotation;
    hkVector4 m_translation;
    __forceinline hkTransform() {}
    __forceinline hkTransform(const hkTransform& t) : m_rotation(t.m_rotation), m_translation(t.m_translation) {}
    __forceinline void operator=(const hkTransform& t) { m_rotation = t.m_rotation; m_translation = t.m_translation; }
    void setRotation(const hkRotation& r) { m_rotation = r; }
    static hkTransform s_identity;              // @ 0x15b9b20
    static const hkTransform& getIdentity() { return s_identity; }
};

struct hkAabb {
    hkVector4 m_min;
    hkVector4 m_max;
};

struct hkShape {
    virtual void _v0();
    virtual void _v1();
    virtual void _v2();
    virtual void getAabb(const hkTransform& localToWorld, hkReal tolerance, hkAabb& out) const;   // +0xc
};

struct hkCdBody {
    const hkShape* m_shape;                     // +0x00
    unsigned int m_shapeKey;
    const void* m_motion;
    const hkCdBody* m_parent;
    const hkShape* getShape() const { return m_shape; }
};
struct hkCollidable : hkCdBody {
    int m_ownerOffset;                          // +0x10
    unsigned int m_bpId;
    char m_bpType, m_bpOwnerOffset;
    unsigned short m_objectQualityType;
    unsigned int m_collisionFilterInfo;         // +0x1c
    hkReal m_allowedPenetrationDepth;
    void* getOwner() const { return (char*)this + m_ownerOffset; }
};

struct hkMotion {
    char pad[0x10];
    hkTransform m_transform;                    // +0x10 (motion state)
    const hkTransform& getTransform() const { return m_transform; }
    const hkVector4& getPosition() const { return m_transform.m_translation; }
};

struct hkRigidBody {
    char pad00[0x1c];
    hkCollidable m_collidable;                  // +0x1c
    char pad40[0x58 - 0x1c - sizeof(hkCollidable)];
    hkMotion* m_motion;                         // +0x58
    const hkCollidable* getCollidable() const { return &m_collidable; }
    hkMotion* getRigidMotion() const { return m_motion; }
    void setPosition(const hkVector4& p);       // @ 0x1087820
    void setTransform(const hkTransform& t);    // @ 0x1087890
};
inline hkRigidBody* hkGetRigidBody(const hkCollidable* c)
{
    hkRigidBody* body = (hkRigidBody*)c->getOwner();
    return body;
}

struct hkContactPoint {
    hkVector4 m_position;
    hkVector4 m_separatingNormal;
    const hkVector4& getPosition() const { return m_position; }
    hkReal getDistance() const { return m_separatingNormal(3); }
};
// Its implicit copy ctor is 0x48dc00 (byte-exact; emitted because MoveBlockLowAngleStacking copies a hit).
struct hkRootCdPoint {
    hkContactPoint m_contact;
    const hkCollidable* m_rootCollidableA;
    unsigned int m_shapeKeyA;
    const hkCollidable* m_rootCollidableB;
    unsigned int m_shapeKeyB;
};

extern hkReal HK_REAL_MAX;                      // @ 0x13ef4f8
extern hkReal HK_REAL_EPSILON;                  // @ 0x13ef4f4

struct hkCdPointCollector {
    hkReal m_earlyOutDistance;
    hkCdPointCollector() { m_earlyOutDistance = HK_REAL_MAX; }
    virtual ~hkCdPointCollector() {}            // vtable 0x13ef534
    virtual void addCdPoint(const void* event) = 0;
    virtual void reset();
};
struct hkClosestCdPointCollector : hkCdPointCollector {
    hkRootCdPoint m_hitPoint;                   // +0x10
    hkClosestCdPointCollector() { reset(); }
    virtual ~hkClosestCdPointCollector() {}     // vtable 0x13ef52c
    virtual void addCdPoint(const void* event);
    virtual void reset();                       // @ 0x48db60
    hkBool hasHit() const { return m_hitPoint.m_rootCollidableA != 0; }
    const hkRootCdPoint& getHit() const { return m_hitPoint; }
};

struct hkLinearCastInput {
    hkVector4 m_to;
    hkReal m_maxExtraPenetration;
    hkReal m_startPointTolerance;
    hkLinearCastInput() { m_maxExtraPenetration = HK_REAL_EPSILON; m_startPointTolerance = HK_REAL_EPSILON; }
};

struct hkWorld {
    void linearCast(const hkCollidable* collA, const hkLinearCastInput& input,
                    hkCdPointCollector& castCollector, hkCdPointCollector* startCollector);   // @ 0x1082b90
};

inline float fabsf(float x) { return (float)::fabs(x); }      // <math.h> C++ overload
namespace hkMath { inline hkReal fabs(hkReal r) { return ::fabsf(r); } }

// ---- Spore editor side ----
struct Matrix3 { float m[9]; };
struct cSPEditorPhysicsWorld { hkWorld* World(); };                // World @ 0x4b91c0
struct cSPEditorModel {
    cSPEditorPhysicsWorld* GetPhysicsWorld();   // @ 0x4ad450
    void NumberBlocks();                        // @ 0x4ad4e0
};
struct cSPEditorBlock;
template<class T> struct AutoRefCount {
    T* mpObject;
    operator T*() const { return mpObject; }
    T* operator->() const { return mpObject; }
};
struct cSPEditorBlock {
    char pad00[0x28];
    cSPEditorModel* mEditorModel;               // +0x28
    char pad2c[0x18c - 0x2c];
    hkRigidBody* mpRigidBody;                   // +0x18c
    char pad190[0x33c - 0x190];
    AutoRefCount<cSPEditorBlock> mSymmetricBlock;   // +0x33c
    void SetCollisionFilterInfo(int info);      // @ 0x451e50
};
struct BlockList;

Vector3T operator*(const float& s, const Vector3T& v);              // @ 0x41de40
Vector3T operator+(const Vector3T& a, const Vector3T& b);           // @ 0x41dc10
void PrepareBlockForStacking(cSPEditorBlock* block, BlockList& piles, int a, int b, int c);   // @ 0x4a6690
void ToHkRotation(const Matrix3& m, hkRotation& out);               // @ 0x4a8fc0

__forceinline hkVector4 ToHkVector4(const cSPVector3& v)
{
    float x = v[0];
    float y = v[1];
    float z = v[2];
    return hkVector4(x, y, z, 0.0f);
}
__forceinline cSPVector3 ToSPVector3(const hkVector4& v)
{
    float x = v(0);
    float y = v(1);
    float z = v(2);
    cSPVector3 r;
    r.x = x; r.y = y; r.z = z;
    return r;
}

// @ 0x48d010
// Moves `block` from `position` along `direction` (100 units) with a Havok linear cast and,
// if it lands flat on top of another body (heights agree within 0.05), writes the landing
// position to `outPosition` and returns that body. The block's transform is restored.
hkRigidBody* MoveBlockLowAngleStacking(cSPEditorBlock* block, BlockList& piles, cSPVector3 position,
                                       cSPVector3 direction, cSPVector3& outPosition,
                                       Matrix3 orientation, bool unused)
{
    cSPEditorModel* model = block->mEditorModel;
    int noParent = 0;
    int filterInfo = 1;
    model->NumberBlocks();

    hkRigidBody* rb = block->mpRigidBody;
    if (rb == 0)
        return 0;

    hkTransform originalTransform(rb->getRigidMotion()->getTransform());

    const hkShape* unusedShape;
    const hkShape* blockShape = unusedShape;
    blockShape = rb->getCollidable()->getShape();
    hkAabb blockAabb;
    blockShape->getAabb(hkTransform::getIdentity(), 0.0f, blockAabb);
    float originalZ = rb->getRigidMotion()->getPosition()(2);

    PrepareBlockForStacking(block, piles, noParent, filterInfo, 1);
    if (block->mSymmetricBlock)
        block->mSymmetricBlock->SetCollisionFilterInfo(filterInfo);

    hkLinearCastInput input;
    cSPVector3 target = position + 100.0f * direction;
    input.m_to = ToHkVector4(target);
    input.m_startPointTolerance = 0.0f;
    input.m_maxExtraPenetration = 0.0f;
    rb->setPosition(ToHkVector4(position));

    hkRotation rotation;
    ToHkRotation(orientation, rotation);
    hkTransform castTransform;
    castTransform = rb->getRigidMotion()->getTransform();
    castTransform.setRotation(rotation);
    rb->setTransform(castTransform);

    hkClosestCdPointCollector collector;
    hkRigidBody* body = block->mpRigidBody;
    model->GetPhysicsWorld()->World()->linearCast(body->getCollidable(), input, collector, 0);

    bool found = false;
    hkRigidBody* result = 0;
    if (collector.hasHit()) {
        hkRigidBody* stackOn = 0;
        hkTransform blockTransform;
        blockTransform = rb->getRigidMotion()->getTransform();
        hkRootCdPoint hit(collector.getHit());
        hkContactPoint contact(hit.m_contact);
        hkRigidBody* hitBody = hkGetRigidBody(hit.m_rootCollidableB);
        hkVector4 hitPosition(contact.getPosition());
        hkReal fraction = contact.getDistance();
        hkVector4 from = ToHkVector4(position);
        hkVector4 newPosition;
        newPosition.setInterpolate4(from, input.m_to, fraction);

        const hkShape* unusedHitShape;
        const hkShape* hitShape = unusedHitShape;
        hitShape = hitBody->getCollidable()->getShape();
        hkAabb hitAabb;
        hitShape->getAabb(hkTransform::getIdentity(), 0.0f, hitAabb);
        float hitTop = hitAabb.m_max(2) + hitBody->getRigidMotion()->getPosition()(2);
        float newBottom = blockAabb.m_min(2) + newPosition(2);
        float rise = hitTop - originalZ;
        float gap = hkMath::fabs(newBottom - hitTop);
        if (gap < 0.05f && rise < 0.05f) {
            stackOn = hitBody;
            result = stackOn;
            found = true;
            outPosition = ToSPVector3(newPosition);
        }
    }
    if (!found)
        result = 0;

    model->NumberBlocks();
    rb->setTransform(originalTransform);
    return result;
}
