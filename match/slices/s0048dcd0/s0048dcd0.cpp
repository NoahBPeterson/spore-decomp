// Slice s0048dcd0: SP::EditorUtils::GetMissStackingPosition + a Vec4 helper.
// Module flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

template<int N> inline void ScratchSlots() { uint32_t s[N]; }

struct Vec4T {
    float x, y, z, w;
    float& operator[](int i) { return (&x)[i]; }
    const float& operator[](int i) const { return (&x)[i]; }
};

// @ 0x48e510
float* F_48e510(float* out, Vec4T& src)
{
    float z = src[0];
    float x = src[1];
    float y = src[2];
    out[0] = z;
    out[1] = x;
    out[2] = y;
    out[3] = 0.0f;
    return out;
}

// ---- stub types (layouts as in s0048d010, the sibling MoveBlockLowAngleStacking) ----
struct Vector3T {
    float x, y, z;
    Vector3T() {}
    float& operator[](int i) { return (&x)[i]; }
    const float& operator[](int i) const { return (&x)[i]; }
};
// rw::math::fpu::Vector3Template<float,0>: its copy ctor is out of line (0x4098a0), so passing one
// by value is a real call.
struct Vector3Val : Vector3T {
    Vector3Val() {}
    Vector3Val(const Vector3Val& v);                                    // @ 0x4098a0
};
struct cSPVector3 : Vector3T {
    cSPVector3() {}
    __forceinline cSPVector3(const Vector3T& v) { x = v.x; y = v.y; z = v.z; }
    cSPVector3& operator=(const Vector3T& v) { x = v.x; y = v.y; z = v.z; return *this; }
};
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
    hkRotation& operator=(const hkRotation& r);     // @ 0x48daf0
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

struct hkQuaternion {
    hkReal x, y, z, w;
    __forceinline hkQuaternion() {}
    __forceinline hkQuaternion(const hkQuaternion& q) { x = q.x; y = q.y; z = q.z; w = q.w; }
};
struct hkMotion {
    char pad[0x10];
    hkTransform m_transform;                    // +0x10 (motion state)
    const hkTransform& getTransform() const { return m_transform; }
    const hkVector4& getPosition() const { return m_transform.m_translation; }
    char pad50[0x80 - 0x50];
    hkQuaternion m_rotation;                    // +0x80
    const hkQuaternion& getRotation() const { return m_rotation; }
};

struct hkRigidBody {
    char pad00[0x1c];
    hkCollidable m_collidable;                  // +0x1c
    char pad40[0x58 - 0x1c - sizeof(hkCollidable)];
    hkMotion* m_motion;                         // +0x58
    const hkCollidable* getCollidable() const { return &m_collidable; }
    hkMotion* getRigidMotion() const { return m_motion; }
    void setPosition(const hkVector4& p);       // @ 0x1087820
    void setRotation(const hkQuaternion& q);    // @ 0x1087840
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
    void setDistance(hkReal d) { m_separatingNormal(3) = d; }
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
    __forceinline void resetInline() {
        m_hitPoint.m_rootCollidableA = 0;
        m_hitPoint.m_contact.setDistance(HK_REAL_MAX);
        m_earlyOutDistance = HK_REAL_MAX;
    }
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
struct cSPEditorPhysicsWorld {
    hkWorld* World();                           // @ 0x4b91c0
    void SetFloorFilter(int info);              // @ 0x4b9440
    void SetDefaultFloorFilter();               // @ 0x4b9470
    void UpdateCollisionFilters();              // @ 0x4b9420
    char pad0[0xc];
    hkRigidBody* mGroundBody;                   // +0x0c
    hkRigidBody* GetGroundBody() { return mGroundBody; }
};
struct cSPEditorModel {
    char pad0[0x30];
    cSPEditorPhysicsWorld* GetPhysicsWorld();   // @ 0x4ad450
    void NumberBlocks();                        // @ 0x4ad4e0
    float GetMaxHeight();                       // @ 0x4adb40 (+0x44)
    float GetMinHeight();                       // @ 0x4adb00 (+0x40)
    float GetGridSize();                        // @ 0x4adaa0 (+0x38)
};
struct BlockList;
struct cSPEditorBlock {
    char pad00[0x28];
    cSPEditorModel* mEditorModel;               // +0x28
    char pad2c[0x18c - 0x2c];
    hkRigidBody* mpRigidBody;                   // +0x18c
    Matrix3 GetNeutralOrientation(Vector3Val direction);    // @ 0x4494b0 (ret 0x10)
};

Vector3T operator*(const float& s, const Vector3T& v);              // @ 0x41de40
Vector3T operator+(const Vector3T& a, const Vector3T& b);           // @ 0x41dc10
float VectorLength(const Vector3T& v);                              // @ 0x40ae50
void PrepareBlockForStacking(cSPEditorBlock* block, BlockList& piles, int a, int b, int c);   // @ 0x4a6690
void ToHkRotation(const Matrix3& m, hkRotation& out);               // @ 0x4a8fc0

__forceinline cSPVector3 ToSPVector3(const hkVector4& v)
{
    float x = v(0);
    float y = v(1);
    float z = v(2);
    cSPVector3 r;
    r.x = x; r.y = y; r.z = z;
    return r;
}

template<class T> inline const T& Max(const T& a, const T& b) { return (a < b) ? b : a; }

namespace SP {
namespace EditorUtils {

// @ 0x48dcd0
// Lowers `block` from `position` along `direction` (distance |position| + max(grid, height span))
// with a Havok linear cast, using the block's neutral orientation for `direction`. If it hits a body
// other than the editor ground, the block's current position is blended toward the cast target by
// the hit fraction and written to `outPosition`; returns true then. The collision filters are reset
// and the block's original rotation restored.
bool GetMissStackingPosition(cSPEditorBlock* block, BlockList& piles, Vector3Val position,
                             Vector3Val direction, Matrix3 orientation, cSPVector3* outPosition)
{
    (void)orientation;
    cSPEditorModel* model = block->mEditorModel;
    int noParent = 0;
    int filterInfo = 1;
    model->NumberBlocks();
    PrepareBlockForStacking(block, piles, noParent, filterInfo, 1);
    model->GetPhysicsWorld()->SetFloorFilter(filterInfo);

    hkClosestCdPointCollector collector;
    collector.resetInline();
    hkLinearCastInput input;

    float top = model->GetMaxHeight();
    float span = top - model->GetMinHeight();
    float grid = model->GetGridSize();
    const float& extra = Max(grid, span);
    float distance = VectorLength(position) + extra;
    cSPVector3 target = position + distance * direction;
    float tmp[4];
    input.m_to = *(hkVector4*)F_48e510(tmp, (Vec4T&)target);

    bool found = false;
    if (block != 0) {
        hkRigidBody* rb = block->mpRigidBody;
        if (rb != 0) {
            hkRigidBody* rb2 = block->mpRigidBody;
            hkMotion* motion = rb2->getRigidMotion();
            hkQuaternion savedRotation(motion->getRotation());

            Matrix3 neutral = block->GetNeutralOrientation(direction);
            hkRotation rotation;
            ToHkRotation(neutral, rotation);
            hkTransform castTransform;
            castTransform = rb->getRigidMotion()->getTransform();
            castTransform.setRotation(rotation);
            rb->setTransform(castTransform);

            hkVector4 start(position[0], position[1], position[2], 0.0f);
            rb->setPosition(start);

            hkRigidBody* body = block->mpRigidBody;
            model->GetPhysicsWorld()->World()->linearCast(body->getCollidable(), input, collector, 0);

            bool hit = collector.hasHit();
            if (hit) {
                hkRigidBody* hitBody = hkGetRigidBody(collector.getHit().m_rootCollidableB);
                if (hitBody != model->GetPhysicsWorld()->GetGroundBody()) {
                    float fraction = collector.getHit().m_contact.getDistance();
                    hkMotion* m = block->mpRigidBody->getRigidMotion();
                    const hkVector4& cur = m->getPosition();
                    hkVector4 blended;
                    blended.setInterpolate4(cur, input.m_to, fraction);
                    *outPosition = ToSPVector3(blended);
                    found = true;
                }
            }
            rb->setRotation(savedRotation);
        }
    }
    model->NumberBlocks();
    model->GetPhysicsWorld()->SetDefaultFloorFilter();
    model->GetPhysicsWorld()->UpdateCollisionFilters();
    return found;
}

}  // namespace EditorUtils
}  // namespace SP
