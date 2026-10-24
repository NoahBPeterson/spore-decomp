// Slice s00c11410 -- SP::cSPCreatureBase body-effect / body-part / animation helpers, 0x00c11410..0x00c12307.
// Object file SPGonzago/SPCreatureBase.obj (see src/game/SPGonzago/SPCreatureBase.cpp, match/slices/s00c12640).
//
// Retail layout (from the disassembly): the cLocomotiveObject (cSpatialObject) sub-object is at creature+0xc0,
// the animating-creature pointer at +0xb54, the attribute flonum mirrors +0xe84..+0xf98.  All the offsets here
// are the retail ones (declared as named members, no raw-offset casts).
//
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast, no EH frame.
#include "types.h"
#include <math.h>

#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
    Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
    float Length() const { return sqrtf(x * x + y * y + z * z); }
    float SquaredLength() const { return x * x + y * y + z * z; }
};
inline Vector3 operator+(const Vector3& a, const Vector3& b) { return Vector3(a.x + b.x, a.y + b.y, a.z + b.z); }
inline Vector3 operator-(const Vector3& a, const Vector3& b) { return Vector3(a.x - b.x, a.y - b.y, a.z - b.z); }
inline Vector3 operator*(const Vector3& a, float s) { return Vector3(a.x * s, a.y * s, a.z * s); }
inline Vector3 operator*(float s, const Vector3& a) { return Vector3(s * a.x, s * a.y, s * a.z); }

struct Quaternion {
    float x, y, z, w;
    Quaternion() {}
    Quaternion(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {}
};

struct Matrix3 {
    float m[9];
};

// cTransform: uint16 flags, uint16 version, offset(+4), scale(+0x10), 3x3 rotation(+0x14).
struct Transform {
    uint16_t mFlags;
    uint16_t mVersion;
    Vector3 mOffset;       // +0x04
    float mScale;          // +0x10
    Matrix3 mRot;          // +0x14
    void SetOffset(const Vector3& v) { mFlags |= 4; mVersion++; mOffset = v; }
    void SetScale(float s) { mScale = s; mVersion++; }
    void SetRotation(const Matrix3& m) { mRot = m; mFlags |= 2; mVersion++; }
};

// ---- callees (cdecl unless noted; address in the comment) ----
Matrix3* Matrix3FromQuaternion(Matrix3* out, const Quaternion* q);             // 0x0059c190
Matrix3* Matrix3FromFacingAndUp(Matrix3* out, const Vector3* facing, const Vector3* up);  // 0x0069b440
Vector3* QuaternionVectorTransform(Vector3* out, const Quaternion* q, const Vector3* v);  // 0x0099c1a0
void Matrix3Assign(Matrix3* out, const Matrix3* src);                          // 0x0041cb40
void PreRotateY(Transform* t, float angle);                                    // 0x004099b0
float RandomFloatRange(float a, float b);                                      // 0x00572a10
int CCB_d050(void* creature, float f);                                         // 0x00c0d050
float CCM_e4f0(void* creature);                                                // 0x00c0e4f0
bool C_C5b0(void* self, int id, int* out);                                     // 0x00c0c5b0
void C_QuatHalf(void* self, float f);                                          // 0x00c0c4b0
void FUN_00c10250(void* self, int handle, int arg3, void* layer);              // 0x00c10250
void FUN_00c111b0();                                                           // 0x00c111b0
void* FUN_009cb300(void* instanceData, int id, int a, int b);                  // 0x009cb300  AddEffect
void FUN_009caa40(void* effect, int partIdx, int a, int b);                    // 0x009caa40  effect::Init
bool FUN_00a04990(void* self, int a);                                          // 0x00a04990
void FUN_00a02bc0(void* self);                                                 // 0x00a02bc0
void* FUN_00b3d310(void* self);                                                // 0x00b3d310
void FUN_00b45410(void* self);                                                 // 0x00b45410
void FUN_00b453a0(void* self);                                                 // 0x00b453a0
void FUN_00b54200(void* self);                                                 // 0x00b54200

extern float gF_150c8b8;        // 0x150c8b8  default sight cos threshold
extern float gF_157174c;        // 0x157174c  half-turn angle (radians)
extern float gF_146a330;        // 0x146a330  max sight range
extern float gF_13ec480;        // 0x13ec480  overhead-effect offset
extern float gF_13ef74c;        // 0x13ef74c  body-effect part scale
extern const Matrix3 gM_168d964;   // 0x168d964  identity matrix (3x3)
extern const Matrix3 gM_168db30;   // 0x168db30  identity matrix (3x3)
extern const Vector3 gV_168d910;   // 0x168d910  default body-effect offset
extern const Vector3 gV_168d988;   // 0x168d988  default transform offset

struct cEffectsManager {
    PV8 PV2 PV
    virtual bool CreateVisualEffect(uint32_t id, int flags, void** ppEffect);  // +0x2c
};
cEffectsManager* EffectsManager();                   // 0x0067ddd0

struct cLayerManager {
    PV8 PV4 PV4
    virtual void* GetLayer(uint32_t id);             // +0x40
};
cLayerManager* LayerManager();                       // 0x0067cb20

// ---- ref-counted objects (vtable +0x00 AddRef, +0x04 Release) ----
struct cRefObj {
    virtual void AddRef();                           // +0x00
    virtual void Release();                          // +0x04
    virtual void* Cast(uint32_t type);               // +0x08
    virtual void* V0C(void* arg);                    // +0x0c
};

// EA::Swarm::cIVisualEffect (CreateVisualEffect's product)
struct cIVisualEffect : public cRefObj {
    PV2
    virtual void Start(int flags);                   // +0x18
    virtual void Stop(int flags);                    // +0x1c
    virtual bool IsRunning();                        // +0x20
    PV
    virtual void SetTransform(const Transform& t);   // +0x28
};

// body-part transform table entry (stride 0x2bc), retail
struct BodyPart {
    uint32_t pad00[4];
    Vector3 mPosition;          // +0x10
    Quaternion mOrientation;    // +0x1c
    uint32_t pad2C[0x38];
    float mRestDim0;            // +0x10c
    uint32_t pad110[0x0a];
    float mUnk138;              // +0x138
    float mUnk13C;              // +0x13c
    float mUnk140;              // +0x140
};
struct cCreatureInstanceData {
    uint32_t pad00[6];
    Vector3 mPosition;          // +0x18 (creature root position)
    Quaternion mOrientation;    // +0x1c
    Vector3 mUnk3C;             // +0x3c
    Vector3 mUnk48;             // +0x48
    Vector3 mUnk54;             // +0x54
    uint32_t pad60[0xa1];
    BodyPart* mBodyParts;       // +0x2e4
};

// The animation-side object at creature+0xb54.
struct cAnimatedCreature {
    uint32_t pad00[0x5f];
    cCreatureInstanceData* mpInstanceData;           // +0x17c

    virtual void* V08(uint32_t layerID, int b);      // +0x08
    virtual void V0C(void* handle, bool b);          // +0x0c
    PV2                                              // 0x10..0x18
    virtual void V18(void* handle);                  // +0x18
    PV8 PV8 PV8 PV8 PV8 PV8 PV8                      // 0x1c..0x3c
    virtual void V3C(void* handle, int a);           // +0x3c
    virtual void V40(void* handle, uint32_t id);     // +0x40
    virtual void V44(void* handle, float f);         // +0x44
    PV4                                              // 0x48..0x58
    virtual void* V58(uint32_t id, int a, int b, int c, void* out);  // +0x58
};

// Creature animation-effect record / handle (retail offsets).  AddEffect returns one of these; its vtable
// slots +0x00 AddRef and +0x04 Release are used by CreateBodyEffect, and DetachBodyEffect reads +0x40 refcount,
// +0x50 state flags, +0x64 inner-effect pointer, +0x70/0x71/0x75 bytes, +0x8c/+0x90 handles, +0xa4 effect and
// +0xa8 callback, and calls vtable slot +0x170.
struct cCreatureEffect {
    virtual void AddRef();                           // +0x00
    virtual void Release();                          // +0x04
    PV8 PV8 PV8 PV8                                  // 0x08..0x18
    Quaternion mQuat;                                // +0x18
    PV8 PV8 PV8 PV8 PV8 PV8                          // 0x28..0x40
    uint32_t mRefCount;                              // +0x40
    uint32_t pad44[0x03];                            // 0x44..0x50
    uint32_t mStateFlags;                            // +0x50
    uint32_t pad54[0x04];                            // 0x54..0x64
    cRefObj* mpField64;                              // +0x64
    uint32_t pad68[0x02];                            // 0x68..0x70
    uint8_t mFlag70;                                 // +0x70
    uint8_t mFlag71;                                 // +0x71
    uint16_t pad72;
    uint8_t mFlag75;                                 // +0x75
    uint32_t pad76[0x05];                            // 0x76..0x8c
    cRefObj* mpField8C;                              // +0x8c
    cCreatureEffect* mpField90;                      // +0x90
    uint32_t pad94[0x04];                            // 0x94..0xa4
    void* mpEffect;                                  // +0xa4
    void (*mpCallback)();                            // +0xa8
    uint32_t padAC[0x31];                            // 0xac..0x170
    virtual void V170(int release);                  // +0x170
};

// The object passed as `obj` (a cCombatant-like ref object): Cast at vtable slot +0xb8.
struct cEffectSource {
    PV8 PV8 PV8 PV8 PV8 PV8 PV8 PV8 PV8 PV8 PV8 PV8 PV8 PV8 PV8 PV8
    PV8 PV8 PV8 PV8 PV8 PV8 PV8 PV8 PV8 PV8 PV8 PV8 PV8 PV8 PV8 PV8
    PV8 PV8 PV8 PV8 PV8 PV8 PV8 PV8 PV8 PV8 PV8 PV8 PV8
    virtual void* Cast(uint32_t type);               // +0xb8
};

// attrib / bonus object at creature+0xe84
struct cCreatureBonus {
    uint32_t pad00[0xd4];
    float mRadius;                  // +0x350
};

// spatial sub-object (cLocomotiveObject base), at creature+0xc0
struct CreatureBase;
struct cSpatialObject {
    PV8 PV2 PV
    virtual const Vector3& GetPosition();            // +0x2c
    virtual const Quaternion& GetOrientation();      // +0x30
    virtual float GetScale();                        // +0x34
    PV8 PV
    virtual Vector3* GetSampleDir(Vector3* out);     // +0x5c
    PV2
    virtual const Vector3* GetLocalExtents();        // +0x68
    PV
    virtual float GetFootprintRadius();              // +0x74

    // 00c11410 (retail ecx = creature+0xc0)
    void SetSpeedState(float a, float b);
};

// The creature, retail offsets.
struct CreatureBase {
    uint32_t pad00[0x30];                    // 0x00..0xc0
    cSpatialObject mSpatial;                 // +0xc0
    uint32_t padC4[0x77];                    // 0xc4..0x2a0
    float mValue2A0;                         // +0x2a0 (spatial this+0x1e0)
    uint32_t pad2A4[0x22c];                  // 0x2a4..0xb54
    cAnimatedCreature* mpAnimatedCreature;   // +0xb54
    uint32_t mFlagsB58;                      // +0xb58 (spatial this+0xa98)
    uint32_t padB5C[0x15];                   // 0xb5c..0xbb0
    uint8_t mByteBB0;                        // +0xbb0
    uint8_t mbStealthed;                     // +0xbb1
    uint32_t padBB2[0xb4];                   // 0xbb2..0xe84
    cCreatureBonus* mpBonus;                 // +0xe84
    void* mpMostRecentAnimHandle;            // +0xe88
    uint32_t padE8C[0x43];                   // 0xe8c..0xf98
    int32_t mStateF98;                       // +0xf98 (spatial this+0xed8)

    // 00c11480
    bool IsWithinSight(const Vector3& target, float angle, float range);
    // 00c115d0
    bool funcC0h(CreatureBase* other, float angle, float range);
    // 00c11920
    void OneShotOverheadEffect(uint32_t effectID);
    // 00c11b50
    bool GetBodyPartPositionAndOrientation(Vector3* pos, Quaternion* orient, int partIdx, bool local);
    // 00c11f50
    bool CreateBodyEffect(int partIdx, void* effect, void* obj, uint32_t id);
    // 00c12190
    int PlayAnimation(uint32_t id, bool arg2, int arg3);
    // 00c122c0
    void PlayAnimationRange(uint32_t id, float a, float b);

    cSpatialObject& GetSpatial() { return mSpatial; }
};

// @ 0x00c11410
void cSpatialObject::SetSpeedState(float a, float b)
{
    CreatureBase* owner = (CreatureBase*)((char*)this - 0xc0);
    owner->mStateF98 = CCB_d050(owner, a);
    if ((owner->mFlagsB58 & 0x200) || (owner->mFlagsB58 & 0x100))
        owner->mValue2A0 = 1.5f * b;
    else
        owner->mValue2A0 = 1.0f * b;
}

// @ 0x00c11480
bool CreatureBase::IsWithinSight(const Vector3& target, float angle, float range)
{
    if (range == 0.0f)
        return true;
    Vector3 delta = target - mSpatial.GetPosition();
    if (CCM_e4f0(this) * angle < range)
        return false;
    float inv =
        1.0f / sqrtf(delta.x * delta.x + delta.y * delta.y + delta.z * delta.z + 1e-8f);
    Vector3 dir = delta * inv;
    Vector3 sample;
    mSpatial.GetSampleDir(&sample);
    float cone = gF_150c8b8;
    if (mpBonus && mpBonus->mRadius >= 0.0f)
        cone = mpBonus->mRadius;
    float c = cosf(cone * 0.008726646f);
    float dot = sample.z * dir.z + sample.y * dir.y + sample.x * dir.x;
    return dot >= c;
}

// @ 0x00c115d0
bool CreatureBase::funcC0h(CreatureBase* other, float angle, float range)
{
    if (other->mbStealthed)
        return false;
    const Vector3& otherPos = other->mSpatial.GetPosition();
    float rs;
    if (gF_146a330 <= range) {
        rs = range;
    } else {
        Vector3 delta = otherPos - mSpatial.GetPosition();
        float dist = sqrtf(delta.x * delta.x + delta.y * delta.y + delta.z * delta.z);
        rs = dist - (mSpatial.GetFootprintRadius() + other->mSpatial.GetFootprintRadius());
    }
    return IsWithinSight(otherPos, angle, rs);
}

// @ 0x00c11690
void* FUN_00c11690(CreatureBase* self, void* arg1, void* obj, uint32_t id)
{
    void* ref = 0;
    cEffectsManager* mgr = EffectsManager();
    void* effect = 0;
    (void)arg1;
    if (!mgr->CreateVisualEffect(id, 0, &ref))
        return 0;
    effect = ref;

    Transform t;
    t.mFlags = 0;
    t.mVersion = 0;
    t.mOffset = gV_168d988;
    t.mScale = 1.0f;
    Matrix3Assign(&t.mRot, &gM_168d964);
    t.mOffset = self->GetSpatial().GetPosition();
    t.mFlags |= 4;
    t.mVersion++;

    if (obj) {
        CreatureBase* other = (CreatureBase*)obj;
        const Vector3& faceFrom = other->GetSpatial().GetPosition();
        const Vector3& faceTo = self->GetSpatial().GetPosition();
        Vector3 nf = faceTo - faceFrom;
        Vector3 nu = faceTo;
        float fi = 1.0f / sqrtf(nf.x * nf.x + nf.y * nf.y + nf.z * nf.z);
        nf = nf * fi;
        float ui = 1.0f / sqrtf(nu.x * nu.x + nu.y * nu.y + nu.z * nu.z);
        nu = nu * ui;
        Matrix3 rot;
        Matrix3FromFacingAndUp(&rot, &nf, &nu);
        t.mRot = rot;
    } else {
        Matrix3 rot;
        Matrix3FromQuaternion(&rot, &self->GetSpatial().GetOrientation());
        t.mRot = rot;
    }
    t.mFlags |= 2;
    t.mVersion++;
    t.mScale = self->GetSpatial().GetScale();
    t.mVersion++;

    if (effect) {
        ((cIVisualEffect*)effect)->SetTransform(t);
        ((cIVisualEffect*)effect)->Start(0);
    }
    if (ref)
        ((cRefObj*)ref)->Release();

    return (void*)1;
}

// @ 0x00c11920
void CreatureBase::OneShotOverheadEffect(uint32_t effectID)
{
    void* ref = 0;
    cEffectsManager* mgr = EffectsManager();
    if (!mgr->CreateVisualEffect(effectID, 0, &ref))
        return;
    cIVisualEffect* effect = (cIVisualEffect*)ref;

    const Vector3& pos = mSpatial.GetPosition();
    Vector3 dir = pos;
    float inv = 1.0f / sqrtf(dir.x * dir.x + dir.y * dir.y + dir.z * dir.z + 1e-8f);
    dir = dir * inv;
    float dist = mSpatial.GetLocalExtents()[5].x + gF_13ec480;
    Vector3 endPos = pos + dir * dist;

    Transform t;
    t.mFlags = 0;
    t.mVersion = 0;
    t.mOffset = endPos;
    t.mScale = 1.0f;
    Matrix3Assign(&t.mRot, &gM_168d964);
    t.mFlags |= 4;
    t.mVersion++;
    Matrix3 rot;
    Matrix3FromQuaternion(&rot, &mSpatial.GetOrientation());
    t.mRot = rot;
    t.mFlags |= 2;
    t.mVersion++;
    t.mScale = mSpatial.GetScale();
    t.mVersion++;

    effect->SetTransform(t);
    effect->Start(0);

    effect->Release();
}

// @ 0x00c11b50
bool CreatureBase::GetBodyPartPositionAndOrientation(Vector3* pos, Quaternion* orient, int partIdx, bool local)
{
    if (partIdx == -1)
        return false;
    cCreatureInstanceData* inst = mpAnimatedCreature->mpInstanceData;
    BodyPart* parts = inst->mBodyParts;
    const BodyPart& bp = parts[partIdx];
    if (local) {
        Vector3 v = *pos + bp.mPosition;
        Vector3 rotated;
        QuaternionVectorTransform(&rotated, &inst->mOrientation, &v);
        *pos = rotated + inst->mPosition;
        *orient = bp.mOrientation;
        return true;
    }
    *pos = *pos + bp.mPosition;
    Transform t;
    t.mFlags = 0;
    t.mVersion = 0;
    t.mOffset = gV_168d910;
    t.mScale = 1.0f;
    Matrix3Assign(&t.mRot, &gM_168db30);
    PreRotateY(&t, -gF_157174c);
    if (t.mFlags & 2) {
        Vector3 v = *pos;
        *pos = Vector3(t.mRot.m[0] * v.x + t.mRot.m[1] * v.y + t.mRot.m[2] * v.z,
                       t.mRot.m[3] * v.x + t.mRot.m[4] * v.y + t.mRot.m[5] * v.z,
                       t.mRot.m[6] * v.x + t.mRot.m[7] * v.y + t.mRot.m[8] * v.z);
    }
    *pos = *pos * t.mScale;
    *orient = bp.mOrientation;
    return true;
}

// @ 0x00c11f50
bool CreatureBase::CreateBodyEffect(int partIdx, void* effect, void* obj, uint32_t id)
{
    if (effect == 0 && obj == 0)
        return false;
    if (partIdx == -1)
        return false;
    cCreatureInstanceData* inst = mpAnimatedCreature->mpInstanceData;
    cCreatureEffect* rec = (cCreatureEffect*)FUN_009cb300(inst, id, 0, 0);
    if (rec == 0)
        return false;
    FUN_009caa40(rec, partIdx, 0, 0);
    BodyPart* parts = inst->mBodyParts;
    BodyPart* bp = &parts[partIdx];
    if ((bp->mUnk138 + bp->mUnk13C + bp->mUnk140) * gF_13ef74c < bp->mRestDim0)
        C_QuatHalf(&rec->mQuat, gF_157174c);
    void* src = 0;
    cEffectSource* source = (cEffectSource*)obj;
    if (source)
        src = source->Cast(0xee3f516e);
    void* old = rec->mpEffect;
    if (src != old) {
        if (src) ((cRefObj*)src)->AddRef();
        rec->mpEffect = src;
        if (old) ((cRefObj*)old)->Release();
    }
    if (source) {
        rec->mpCallback = FUN_00c111b0;
        if (FUN_00b3d310(obj))
            FUN_00b45410(FUN_00b3d310(obj));
    }
    return true;
}

// @ 0x00c12080
void DetachBodyEffect(cCreatureEffect* rec, bool release)
{
    cCreatureEffect* r = 0;
    if (rec->mpEffect) {
        cRefObj* p = (cRefObj*)rec->mpEffect;
        r = (cCreatureEffect*)p->V0C((void*)0x01186577);
    }
    if (rec->mpField90) {
        cRefObj* inner = rec->mpField90->mpField64;
        if (inner)
            r = (cCreatureEffect*)inner->V0C((void*)0x01186577);
    }
    if (r) {
        rec->mpCallback = 0;
        r->mStateFlags &= ~4u;
        r->mFlag70 = 1;
        r->mFlag71 = 0;
        if (r->mFlag75) {
            if (FUN_00b3d310(r)) {
                FUN_00b453a0(FUN_00b3d310(r));
                FUN_00b54200(r);
            }
        }
        cCreatureEffect* h = rec->mpField90;
        if (h) {
            rec->mpField90 = 0;
            if ((int)h->mRefCount <= 1)
                h->V170((int)(((unsigned)h->mRefCount) >> 31) & 1);
            else
                h->mRefCount--;
        }
        cCreatureEffect* e = (cCreatureEffect*)rec->mpEffect;
        if (e) {
            rec->mpEffect = 0;
            e->Release();
        }
    }
    if (rec->mpField8C)
        rec->mpField8C->V0C((void*)(release ? 1 : 0));
}

// @ 0x00c12190
int CreatureBase::PlayAnimation(uint32_t id, bool arg2, int arg3)
{
    int layerID = id;
    C_C5b0(this, (int)id, &layerID);
    void* layer = LayerManager()->GetLayer((uint32_t)layerID);
    if (!layer)
        return 0;

    int handle = 0;
    cAnimatedCreature* anim = mpAnimatedCreature;
    if (anim) {
        int unk = 0;
        anim->V58(layerID, 0, 0, 0, &unk);
        anim = mpAnimatedCreature;
        if (layerID == (int)id && FUN_00a04990(anim, 0))
            return 0;
        anim = mpAnimatedCreature;
        bool wasPlaying = FUN_00a04990(anim, 0);
        if (arg2)
            FUN_00a02bc0(mpAnimatedCreature);
        anim = mpAnimatedCreature;
        handle = (int)anim->V08(layerID, 0);
        anim->V0C((void*)handle, wasPlaying);
        anim->V18((void*)handle);
        anim->V40((void*)handle, id);
        anim->V3C((void*)handle, 0);
        FUN_00c10250(this, handle, arg3, layer);
        if (((char*)layer)[0x1c] != 1)
            mpMostRecentAnimHandle = (void*)handle;
    }
    return handle;
}

// @ 0x00c122c0
void CreatureBase::PlayAnimationRange(uint32_t id, float a, float b)
{
    int handle = PlayAnimation(id, true, -1);
    if (handle)
        mpAnimatedCreature->V44((void*)handle, RandomFloatRange(b, a));
}
