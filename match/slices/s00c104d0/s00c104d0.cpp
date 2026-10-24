// Slice s00c104d0 -- FUN_00c104d0 (0x00c104d0, 2734 bytes).
//
// Free __cdecl planet-surface helper (writes through `out`, returns nothing):
//   n   = normalize(up)                      (up is a planet-centred position)
//   dp  = (target - up) rejected from n      (tangent-plane direction to the target)
//   fp  = fwd rejected from n                (tangent-plane forward)
//   angle1 = wrapped signed angle (dp -> target-up) about normalize(dp x n)   (elevation)
//   s   = cPlanetModel::Get()->Func(up)      (0x00b7e3b0, a Vector3 by value)
//   angle2 = wrapped signed angle (fp -> fp rejected from s) about normalize(fp x n)
//   If the target lies more than 60 degrees off the forward direction (cos < 0.5), dp is
//   pulled toward fp rotated 60 degrees about n, and angle1 is blended toward angle2.
//   If |dp| < 1, dp/angle1 are blended by smoothstep(|dp|).
//   r   = dp rotated by angle1 about normalize(dp x n)
//   *out = lerp(up + r, p5, exp(t * -3.0103))
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (siblings s00c09fa0, s00c12640).
#include "types.h"
#include <math.h>
#include <string.h>

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
    Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
    Vector3& operator=(const Vector3& v) { x = v.x; y = v.y; z = v.z; return *this; }
    Vector3 Cross(const Vector3& b) const
    {
        return Vector3(y * b.z - z * b.y, z * b.x - x * b.z, x * b.y - y * b.x);
    }
    float Dot(const Vector3& b) const { return x * b.x + y * b.y + z * b.z; }
    float LengthSq() const { return x * x + y * y + z * z; }
    Vector3 operator+(const Vector3& b) const { return Vector3(x + b.x, y + b.y, z + b.z); }
    Vector3 operator-(const Vector3& b) const { return Vector3(x - b.x, y - b.y, z - b.z); }
    Vector3 operator*(float s) const { return Vector3(x * s, y * s, z * s); }
};

struct Quaternion {
    float x, y, z, w;
    Quaternion() {}
    Quaternion(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {}
    Quaternion(const Quaternion& q) : x(q.x), y(q.y), z(q.z), w(q.w) {}
    Quaternion& operator=(const Quaternion& q)
    {
        x = q.x;
        y = q.y;
        z = q.z;
        w = q.w;
        return *this;
    }
};

// Rotation of `angle` radians about the unit vector `axis`.
inline Quaternion AxisAngle(const Vector3& axis, float angle)
{
    float h = angle * 0.5f;
    float s = sinf(h);
    float c = cosf(h);
    return Quaternion(axis.x * s, axis.y * s, axis.z * s, c);
}

// SSE clamp helper from the original math headers (maxss then minss).
__forceinline float Clamp(float value, float minValue, float maxValue)
{
    __asm {
        movss xmm0, value
        maxss xmm0, minValue
        minss xmm0, maxValue
        movss value, xmm0
    }
    return value;
}

inline float SmoothStep(float v)
{
    v = Clamp(v, 0.0f, 1.0f);
    return (3.0f - v * 2.0f) * v * v;
}

inline Vector3 NormalizeSafe(const Vector3& v)
{
    float inv = 1.0f / sqrtf(v.LengthSq() + 1e-8f);
    return v * inv;
}

inline Vector3 Reject(const Vector3& v, const Vector3& n)
{
    float d = v.Dot(n);
    return v - n * d;
}

// ---- callees ----
Vector3 RotateVector(const Vector3& v, const Quaternion& q);                  // 0x0059aed0
float SignedAngle(const Vector3& a, const Vector3& b, const Vector3& axis);   // 0x0069b760

struct cPlanetModel {
    static cPlanetModel* Get();                       // 0x00b3d350
    Vector3 SurfaceNormal(const Vector3& position);   // 0x00b7e3b0
};

extern const float kPi;     // 0x0157174c
extern float gTwoPi;        // 0x0168d960 (dynamic-initialized)

// fmod into (-pi, pi] using the module's 2*pi.
static inline float WrapAngleMod(float a)
{
    float x = (float)fmod((double)a, (double)gTwoPi);
    if (x > kPi)
        return x - gTwoPi;
    if (x < -kPi)
        return x + gTwoPi;
    return x;
}

// @ 0x00c104d0
void FUN_00c104d0(Vector3* out, const Vector3& up, const Vector3& fwd, const Vector3& target,
                  const Vector3& goal, float t)
{
    Vector3 u = up;
    float inv = 1.0f / sqrtf(u.LengthSq());
    Vector3 n = u * inv;
    Vector3 d = target - u;
    Vector3 dp = Reject(d, n);
    Vector3 fp = Reject(fwd, n);
    Vector3 dpN = NormalizeSafe(dp);
    float cosA = NormalizeSafe(fp).Dot(dpN);

    Vector3 side = NormalizeSafe(dp.Cross(n));
    float angle = WrapAngleMod(SignedAngle(dp, d, side));

    Vector3 surfUp = cPlanetModel::Get()->SurfaceNormal(up);
    Vector3 fpSide = NormalizeSafe(fp.Cross(n));
    float baseAngle = WrapAngleMod(SignedAngle(fp, Reject(fp, surfUp), fpSide));

    if (cosA < 0.5f) {
        float turn = WrapAngleMod(SignedAngle(fp, dpN, n));
        if (turn > 0.0f)
            turn = 1.0471976f;
        else
            turn = -1.0471976f;
        Vector3 r = RotateVector(fp, AxisAngle(n, turn));
        float w = SmoothStep((cosA + 1.0f) * 0.6666667f);
        float iw = 1.0f - w;
        dp = Vector3(r.x * w + fp.x * iw, r.y * w + fp.y * iw, r.z * w + fp.z * iw);
        dpN = NormalizeSafe(dp);
        angle = iw * baseAngle + w * angle;
    }

    float len = sqrtf(dp.LengthSq());
    if (len < 1.0f) {
        float w = SmoothStep(len);
        float iw = 1.0f - w;
        float k = iw * 3.0f;
        dp = Vector3(dpN.x * w + fp.x * k, dpN.y * w + fp.y * k, dpN.z * w + fp.z * k);
        angle = iw * baseAngle + w * angle;
    }

    Vector3 axis = NormalizeSafe(dp.Cross(n));
    Vector3 r = RotateVector(dp, AxisAngle(axis, angle));
    float f = (float)exp((double)(t * -3.0103f));
    float g = 1.0f - f;
    Vector3 p = up + r;
    out->x = goal.x * f + p.x * g;
    out->y = goal.y * f + p.y * g;
    out->z = goal.z * f + p.z * g;
}

// ---------------------------------------------------------------------------------------------
// SP speed-boost / damage-over-time helpers (0x00c10f80 .. 0x00c111b0).
//
// Every helper takes the same small "speed boost assignment" record.  The record's +0x3c field is
// the creature container; its virtual slot +0x0c resolves a component id to a cSPCreatureBase.
// The creature is a cSPCreatureBase with the vtable slots used below (0x20, 0x2c, 0x38, 0x3c,
// 0x68, 0x9c, 0xac, 0xb8) and an ILocomotive sub-object embedded at +0xc0.

namespace SP {

struct cSPCreatureBase;
struct DamageEntry;
struct DamageContext;
struct DamageNode;

struct IContainer {
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual cSPCreatureBase* Get(unsigned int id);       // +0x0c
};

// The record passed to the helpers.
struct SPThing {
    uint32_t mId;              // +0x00
    int      mIndex;           // +0x04
    int      mFlag08;          // +0x08
    uint32_t mBoostId;         // +0x0c
    uint8_t  pad10[0x3c - 0x10];
    IContainer* mpContainer;   // +0x3c

    void Apply(cSPCreatureBase* creature, char flag);
};

struct BoundBox {
    float mMin[3];             // +0x00
    float mMax[3];             // +0x0c
};

struct Matrix33 {
    float m[9];                // column-major
};

struct DamageNodeHeader {
    uint16_t mFlags;           // +0x00 (node +0x08)
    uint16_t mCount;           // +0x02
    uint32_t mPosX;            // +0x04 (node +0x0c)
    uint32_t mPosY;            // +0x08
    uint32_t mPosZ;            // +0x0c
    uint32_t f10;              // +0x10
    uint32_t mMatrix[9];       // +0x14 (node +0x1c)
};
struct DamageNode {
    uint32_t f00;              // +0x00
    uint32_t f04;              // +0x04
    DamageNodeHeader hdr;      // +0x08
};
union FloatBits {
    float f;
    uint32_t u;
};

struct DamageEntry {          // 0x24 bytes
    uint32_t f00;              // +0x00
    uint32_t f04;              // +0x04
    uint32_t f08;              // +0x08
    uint32_t mRefCount;        // +0x0c
    uint32_t f10;              // +0x10
    uint32_t f14;              // +0x14
    uint32_t f18;              // +0x18
    uint32_t f1c;              // +0x1c
    uint32_t f20;              // +0x20
};

struct DamageContext {
    uint8_t pad00[0x184];
    void*   mpTable;           // +0x184
};

struct DamageResult {
    uint8_t pad00[0xc0];
    int     mState;            // +0xc0
};

#define SP_V(n) virtual void v##n();
struct ILocomotive {
    SP_V(00) SP_V(04) SP_V(08) SP_V(0c) SP_V(10) SP_V(14) SP_V(18) SP_V(1c)
    SP_V(20) SP_V(24) SP_V(28)
    virtual const Vector3* GetPosition();              // +0x2c
    SP_V(30) SP_V(34)
    virtual void SetPosition(const Vector3& position); // +0x38
};

struct cSPCreatureBase {
    SP_V(00) SP_V(04) SP_V(08) SP_V(0c) SP_V(10) SP_V(14) SP_V(18) SP_V(1c)
    virtual void* Slot20();                            // +0x20
    SP_V(24) SP_V(28)
    virtual uint32_t IsDead();                         // +0x2c
    SP_V(30) SP_V(34)
    virtual void SetPosition(const Vector3& position); // +0x38
    virtual void SetOrientation(const Quaternion& orientation); // +0x3c
    SP_V(40) SP_V(44) SP_V(48) SP_V(4c) SP_V(50) SP_V(54) SP_V(58) SP_V(5c)
    SP_V(60) SP_V(64)
    virtual const BoundBox* GetBounds();               // +0x68
    SP_V(6c) SP_V(70) SP_V(74) SP_V(78) SP_V(7c) SP_V(80) SP_V(84) SP_V(88)
    SP_V(8c) SP_V(90) SP_V(94) SP_V(98)
    virtual void Slot9C(int value);                    // +0x9c
    SP_V(a0) SP_V(a4) SP_V(a8)
    virtual DamageNode* GetNode();                     // +0xac
    SP_V(b0) SP_V(b4)
    virtual cSPCreatureBase* GetChild(unsigned int id); // +0xb8

    uint8_t pad04[0xc0 - 4];
    ILocomotive mLocomotive;           // +0xc0
    uint8_t padC4[0x135 - 0xc4];
    uint8_t mField135;                 // +0x135
    uint8_t pad136[0xb54 - 0x136];
    DamageContext* mDamageCtx;         // +0xb54
    uint8_t padB58[0xb5e - 0xb58];
    uint8_t mDeadFlag;                 // +0xb5e
    uint8_t padB5F[0xb70 - 0xb5f];
    int     mFieldB70;                 // +0xb70
    uint8_t padB74[0xe40 - 0xb74];
    DamageEntry* mEffectBegin;         // +0xe40
    DamageEntry* mEffectEnd;           // +0xe44

    void d0c0(unsigned int id, char flag);  // 0x00c0d0c0
    bool e0c0(int index);                   // 0x00c0e0c0
    void d240();                            // 0x00c0d240
    void fb40(DamageEntry* entry);          // 0x00c0fb40
};
#undef SP_V

inline void SPThing::Apply(cSPCreatureBase* creature, char flag)
{
    creature->d0c0(mId, flag);
}

void* __cdecl FUN_009ff6f0(void* table, int index);                 // 0x009ff6f0
Quaternion __cdecl QuaternionFromMatrix33(const void* matrix, float w); // 0x00472b80
struct F_a047d0 { void __thiscall f(int flag); };                   // 0x00a047d0

extern char gSpeedBoostNode;                                        // 0x018eb4b7

// @ 0x00c10f80
bool FUN_00c10f80(SPThing* p)
{
    bool result = false;
    IContainer** slot = &p->mpContainer;
    if (*slot != 0) {
        cSPCreatureBase* creature = (*slot)->Get(0xce9f6639);
        if (creature != 0 && p != 0) {
            creature->d0c0(p->mId, 1);
            result = true;
        }
    }
    return result;
}

// @ 0x00c10fc0
bool AddSpeedBoost(SPThing* p)
{
    bool result = false;
    IContainer** slot = &p->mpContainer;
    if (*slot != 0) {
        cSPCreatureBase* creature = (*slot)->Get(0xce9f6639);
        if (creature != 0 && p != 0) {
            uint32_t id = p->mId;
            creature->d0c0(id, 0);
            if (id == 0) {
                if (creature->Slot20() == (void*)&gSpeedBoostNode)
                    creature->Slot9C(0);
            }
            result = true;
        }
    }
    return result;
}

// @ 0x00c11030
bool RemoveSpeedBoost(SPThing* p)
{
    IContainer** slot = &p->mpContainer;
    cSPCreatureBase* creature;
    if (*slot != 0)
        creature = (*slot)->Get(0xce9f6639);
    else
        creature = 0;
    if ((creature->IsDead() & 0xff) != 0 || creature->mDeadFlag != 0 || creature->mField135 == 0)
        return false;
    if (p->mIndex != -1)
        return creature->e0c0(p->mIndex);
    return true;
}

// @ 0x00c11090
bool ManageSpeedBoost(SPThing* p)
{
    bool result = false;
    IContainer** slot = &p->mpContainer;
    if (*slot != 0) {
        cSPCreatureBase* creature = (*slot)->Get(0xce9f6639);
        if (creature != 0 && p != 0) {
            if (p->mIndex == 1 && creature->mFieldB70 == (int)p->mBoostId)
                creature->d240();
            result = true;
        }
    }
    return result;
}

// @ 0x00c110e0
uint32_t ApplyDamageOverTime(SPThing* p)
{
    cSPCreatureBase* creature;
    if (p->mpContainer != 0)
        creature = p->mpContainer->Get(0xce9f6639);
    else
        creature = 0;

    uint32_t dead = creature->IsDead();
    if ((dead & 0xff) != 0 || creature->mField135 == 0)
        return dead & 0xffffff00;

    int count = (int)(creature->mEffectEnd - creature->mEffectBegin);
    uint32_t index = p->mId;
    if (index >= (uint32_t)count)
        return (uint32_t)count & 0xffffff00;

    if (p->mFlag08 == 0) {
        DamageEntry** beginSlot = &creature->mEffectBegin;
        DamageEntry* entry = *beginSlot + index;
        entry->mRefCount++;
        creature->fb40(entry);
        p->mFlag08 = 1;
    }

    DamageContext* ctx = creature->mDamageCtx;
    DamageResult* found = (DamageResult*)FUN_009ff6f0(ctx->mpTable, p->mIndex);
    if (found == 0)
        return 0;
    if (found->mState == 1 || found->mState == 2)
        return 1;
    return 0;
}

// @ 0x00c111b0
bool SetSpatialObjectPosRotCallback(IContainer* ic, const Vector3* pos, const Matrix33* rot)
{
    cSPCreatureBase* child;
    if (ic == 0)
        return false;
    cSPCreatureBase* creature = ic->Get(0x1186577);
    if (creature == 0)
        return false;

    Vector3 p = *pos;
    creature->SetPosition(p);

    {
        Quaternion q;
        q = QuaternionFromMatrix33(rot, 0.0f);
        creature->SetOrientation(q);
    }

    child = creature->GetChild(0xce9f6639);
    if (child != 0 && child->mDamageCtx != 0) {
        const BoundBox* bounds = creature->GetBounds();
        float cx = (bounds->mMax[0] + bounds->mMin[0]) * 0.5f;
        float cy = (bounds->mMax[1] + bounds->mMin[1]) * 0.5f;
        float cz = (bounds->mMax[2] + bounds->mMin[2]) * 0.5f;
        Vector3 world;
        world.x = (rot->m[6] * cz + rot->m[3] * cy) + cx * rot->m[0];
        world.y = (rot->m[7] * cz + rot->m[4] * cy) + rot->m[1] * cx;
        world.z = (rot->m[8] * cz + rot->m[5] * cy) + rot->m[2] * cx;
        const Vector3* cur = child->mLocomotive.GetPosition();
        float dx = cur->x - world.x;
        float dy = cur->y - world.y;
        float dz = cur->z - world.z;
        Vector3 delta;
        delta.x = dx;
        delta.y = dy;
        delta.z = dz;
        child->mLocomotive.SetPosition(delta);
        ((F_a047d0*)child->mDamageCtx)->f(1);
        return true;
    }

    DamageNode* node = creature->GetNode();
    if (node != 0) {
        node = creature->GetNode();
        DamageNodeHeader* h = &node->hdr;
        h->mPosX = *(uint32_t*)&p.x;
        h->mPosY = *(uint32_t*)&p.y;
        h->mFlags |= 4;
        h->mCount = (uint16_t)(h->mCount + 1);
        h->mPosZ = *(uint32_t*)&p.z;
        node = creature->GetNode();
        h = &node->hdr;
        memcpy(h->mMatrix, rot, sizeof(h->mMatrix));
        h->mFlags |= 2;
        h->mCount = (uint16_t)(h->mCount + 1);
    }
    return true;
}

}  // namespace SP

