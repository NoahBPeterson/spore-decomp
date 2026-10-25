#include "types.h"
#include <math.h>
#include <string.h>

#pragma intrinsic(sqrt)

// ---------------------------------------------------------------------------
// Named views over the retail objects this slice touches.
// ---------------------------------------------------------------------------

struct cEffectSlot {
    virtual void v00();                // slot +0x00
    virtual void v04();                // slot +0x04
    virtual void v08();                // slot +0x08
    virtual void v0c();                // slot +0x0c
    virtual bool IsActive();           // slot +0x10
};

struct cEffectEntry {
    uint8_t      mPad000[0x8c];        // +0x000
    cEffectSlot* mEffect;              // +0x08c
};

struct cVector3 {
    float x, y, z;
};

struct cMatrix3 {
    float m[9];

    void Assign(const cMatrix3* src);  // 0x0041cb40
};

// cTransform: uint16 flags, uint16 version, offset(+0x04), scale(+0x10), 3x3 rotation(+0x14).
struct cSPTransform {
    uint16_t  mFlags;                  // +0x00
    uint16_t  mVersion;                // +0x02
    cVector3  mOffset;                 // +0x04
    float     mScale;                  // +0x10
    cMatrix3  mRot;                    // +0x14

    void BackTransformPoint(cVector3* point);   // 0x004ff6d0
    void PreRotateY(float angle);               // 0x004099b0
};

// One entry of the animated body-part table (stride 0x2bc).
struct cBodyPart {
    uint8_t mPad000[0x10];             // +0x000
    float   mPosition[3];              // +0x010
    uint8_t mPad01c[0x2bc - 0x1c];     // +0x01c
};

// One entry of the anim-set part table (stride 0x468).
struct cAnimPartInstance {
    uint8_t mPad000[0x36c];            // +0x000
    float   mRadius;                   // +0x36c
    uint8_t mPad370[0x468 - 0x370];    // +0x370
};

struct cAnimPartSet {
    uint8_t            mPad000[0x384]; // +0x000
    cAnimPartInstance* mpParts;        // +0x384
};

// The live animation instance at cCreatureBody::mAnim (+0x17c).
struct cBodyAnim {
    cAnimPartSet*  mpAnimSet;          // +0x000
    uint8_t        mPad004[0x18 - 0x04]; // +0x004
    float          mPosX;              // +0x018
    float          mPosY;              // +0x01c
    float          mPosZ;              // +0x020
    uint8_t        mPad024[0x3c - 0x24]; // +0x024
    float          mOrientation[4];    // +0x03c
    uint8_t        mPad04c[0x70 - 0x4c]; // +0x04c
    float          mScale;             // +0x070
    uint8_t        mPad074[0x2e4 - 0x74]; // +0x074
    cBodyPart*     mpBodyParts;        // +0x2e4

    cEffectEntry* FindEffect(uint32_t key);              // 0x009cab60
    float* GetWorkspaceOrigin(float* out, int part);     // 0x009b61f0
};

struct cCreatureBody {
    uint8_t     mPad000[0x17c];        // +0x000
    cBodyAnim*  mAnim;                 // +0x17c
};

struct cUIntVector {
    uint32_t* mpBegin;                 // +0x00
    uint32_t* mpEnd;                   // +0x04
};

struct cCreaturePartManager {
    cUIntVector* GetPartsA(cCreatureBody* body);   // 0x004d9030
    cUIntVector* GetPartsB(cCreatureBody* body);   // 0x004d9050
};

// eastl fixed-hashtable node and iterator.
struct cHashNode;
struct cListIterator {
    cHashNode* mpNode;                 // +0x00
    void**     mpBucket;               // +0x04
};

struct cHashNode {
    uint8_t mPad00[4];                 // +0x00
    void*   mpValue;                   // +0x04
};

struct cHashTable {
    uint8_t      mPad00[4];            // +0x00
    cHashNode**  mpBuckets;            // +0x04
    int32_t      mBucketIndex;         // +0x08

    void Find(cListIterator* out, const uint32_t* key);                    // 0x00645ed0
    cListIterator* Erase(cListIterator* out, cListIterator node);          // 0x00d2c9f0
};

struct cStyleValue {
    virtual void v00();                // slot +0x00
    virtual void v04();                // slot +0x04
    virtual void v08();                // slot +0x08
    virtual void v0c(void* arg);       // slot +0x0c
};

// Text-style manager: two fixed hashtables of style entries.
struct cTextStyleManager {
    uint8_t    mPad000[0xcc8];         // +0x000
    cHashTable mLookup;                // +0xcc8
    uint8_t    mPad0cd4[0xd68 - 0xcd4]; // +0x0cd4
    cHashTable mSecondary;             // +0x0d68
};

// 16-byte animation context query record handed to EvaluateContextTargetQuery.
struct cBodyPartQuery {
    int32_t  mRootOnly;                // +0x00
    uint32_t mName;                    // +0x04
    uint32_t mPad08;                   // +0x08
    uint32_t mPad0c;                   // +0x0c
};

extern const uint32_t gBodyPartNames[16];  // 0x015716e8  four-character part names
extern const float kPi;                    // 0x0157174c
extern const float kOne;                   // 0x01485720
extern const float kEps;                   // 0x013ec4b8  (1e-8f)
extern const cVector3 gZeroVector;         // 0x0168d910
extern const cMatrix3 gIdentityMatrix;     // 0x0168db30

extern "C" uint32_t FUN_009b2340(uint32_t* out, uint32_t max, uint32_t model,
                                 void* query, int zero1, int zero2);   // 0x009b2340
extern "C" float* QuaternionVectorTransform(float* out, const float* orientation,
                                            const float* point);       // 0x0099c1a0

// SP::cSPCreatureBase
struct cSPCreatureBase {
    uint8_t        mPad0000[0xb20];    // +0x0000
    cCreaturePartManager* mCreature;   // +0x0b20
    uint8_t        mPad0b24[0xb54 - 0xb24]; // +0x0b24
    cCreatureBody* mBody;              // +0x0b54

    uint32_t MakeBodyEffect(uint32_t part, uint32_t a, uint32_t b);  // 0x00c14f70
    void     BodyEffectNotify(uint32_t a, uint32_t b);               // 0x00c15150

    // 0x00c17580
    uint32_t GetBodyPartIndex(uint32_t kind, uint32_t index);
    // 0x00c17c80
    uint32_t CreateBodyEffect(uint32_t kind, uint32_t a, uint32_t b);
    // 0x00c17cc0
    uint32_t CreateBodyEffectChecked(bool flag, uint32_t kind, uint32_t a, uint32_t e,
                                     uint32_t b);
    // 0x00c17d60
    uint32_t CreateBodyEffectChecked2(bool flag, uint32_t kind, uint32_t a, uint32_t e,
                                      uint32_t b);

    // 0x00c175d0
    bool CanReachPointWithBodyPart(cSPTransform* transform, const float* point, uint32_t kind,
                                   int32_t part, float* outPos, uint8_t* outHit,
                                   float radiusAdd);
    // 0x00c17a30
    bool GetBodyPartPosition(float* outPos, uint32_t kind, bool world, int32_t part);
};

// 0x00c17420  enumerate the body parts of `kind` into `out` (up to `max`)
uint32_t QueryCreatureBodyParts(cSPCreatureBase* self, int32_t kind, uint32_t* out,
                                uint32_t max);

// ---------------------------------------------------------------------------
// 0x00c17580  index into the enumerated body-part list
// ---------------------------------------------------------------------------
// @ 0x00c17580
uint32_t cSPCreatureBase::GetBodyPartIndex(uint32_t kind, uint32_t index)
{
    uint32_t result = 0xffffffff;
    uint32_t parts[255];
    uint32_t count = QueryCreatureBodyParts(this, kind, parts, 255);
    if (index < count) {
        result = parts[index];
    }
    return result;
}

// ---------------------------------------------------------------------------
// 0x00c17c80  create a body effect for the first body part of `kind`
// ---------------------------------------------------------------------------
// @ 0x00c17c80
uint32_t cSPCreatureBase::CreateBodyEffect(uint32_t kind, uint32_t a, uint32_t b)
{
    uint32_t part;
    if (QueryCreatureBodyParts(this, kind, &part, 1) != 0) {
        return MakeBodyEffect(part, a, b);
    }
    return 0;
}

// ---------------------------------------------------------------------------
// 0x00c17cc0  checked body-effect creation (guards on a live effect)
// ---------------------------------------------------------------------------
// @ 0x00c17cc0
uint32_t cSPCreatureBase::CreateBodyEffectChecked(bool flag, uint32_t kind, uint32_t a,
                                                  uint32_t e, uint32_t b)
{
    if (flag != 0) {
        if (mBody != 0) {
            cEffectEntry* found = mBody->mAnim->FindEffect(e);
            if (found != 0) {
                cEffectSlot* eff = found->mEffect;
                if (eff != 0 && eff->IsActive()) {
                    return 0;
                }
            }
        }
        BodyEffectNotify(e, 1);
        uint32_t part;
        if (QueryCreatureBodyParts(this, kind, &part, 1) != 0) {
            return MakeBodyEffect(part, a, e);
        }
        return 0;
    }
    BodyEffectNotify(e, b);
    return 0;
}

// ---------------------------------------------------------------------------
// 0x00c17d60  checked body-effect creation (no part query)
// ---------------------------------------------------------------------------
// @ 0x00c17d60
uint32_t cSPCreatureBase::CreateBodyEffectChecked2(bool flag, uint32_t kind, uint32_t a,
                                                   uint32_t e, uint32_t b)
{
    if (flag != 0) {
        if (mBody != 0) {
            cEffectEntry* found = mBody->mAnim->FindEffect(e);
            if (found != 0) {
                cEffectSlot* eff = found->mEffect;
                if (eff != 0 && eff->IsActive()) {
                    return 0;
                }
            }
        }
        BodyEffectNotify(e, 1);
        return MakeBodyEffect(kind, a, e);
    }
    BodyEffectNotify(e, b);
    return 0;
}

// ---------------------------------------------------------------------------
// 0x00c17350  drop the style entry for `key` from whichever table holds it
// ---------------------------------------------------------------------------
// @ 0x00c17350
bool __fastcall TextStyleRemove(cTextStyleManager* self, int, uint32_t key, void* arg)
{
    cListIterator it;
    self->mLookup.Find(&it, &key);
    if (it.mpNode != self->mLookup.mpBuckets[self->mLookup.mBucketIndex]) {
        ((cStyleValue*)it.mpNode->mpValue)->v0c(arg);
        self->mLookup.Erase(&it, it);
        return true;
    }

    self->mSecondary.Find(&it, &key);
    if (it.mpNode != self->mSecondary.mpBuckets[self->mSecondary.mBucketIndex]) {
        ((cStyleValue*)it.mpNode->mpValue)->v0c(arg);
        self->mSecondary.Erase(&it, it);
        return true;
    }
    return false;
}

// ---------------------------------------------------------------------------
// 0x00c17420  enumerate the body parts of `kind` into `out` (up to `max`)
// ---------------------------------------------------------------------------
// @ 0x00c17420
uint32_t QueryCreatureBodyParts(cSPCreatureBase* self, int32_t kind, uint32_t* out,
                                uint32_t max)
{
    if (self == 0) {
        return 0;
    }
    cCreatureBody* body = self->mBody;
    if (body == 0) {
        return 0;
    }
    cBodyAnim* anim = body->mAnim;
    if (anim == 0) {
        return 0;
    }

    int32_t k = kind;
    if (k >= 0x10) {
        k = 0;
    }

    if (k == 2) {
        cUIntVector* v = self->mCreature->GetPartsA(body);
        uint32_t count = (uint32_t)(v->mpEnd - v->mpBegin);
        uint32_t n = (count < max) ? count : max;
        uint32_t* src = self->mCreature->GetPartsA(body)->mpBegin;
        uint32_t* src2 = self->mCreature->GetPartsA(body)->mpBegin;
        memcpy(out, src2, (size_t)((char*)src2 + n * 4 - (char*)src));
        return n;
    }

    if (k == 0xb) {
        cUIntVector* v = self->mCreature->GetPartsB(body);
        uint32_t count = (uint32_t)(v->mpEnd - v->mpBegin);
        uint32_t n = (count < max) ? count : max;
        uint32_t* src = self->mCreature->GetPartsB(body)->mpBegin;
        uint32_t* src2 = self->mCreature->GetPartsB(body)->mpBegin;
        memcpy(out, src2, (size_t)((char*)src2 + n * 4 - (char*)src));
        return n;
    }

    cBodyPartQuery query;
    query.mRootOnly = (k == 0);
    query.mName = gBodyPartNames[k];
    query.mPad08 = 0;
    query.mPad0c = 0;
    return FUN_009b2340(out, max, (uint32_t)(uintptr_t)anim->mpAnimSet, &query, 0, 0);
}

// ---------------------------------------------------------------------------
// 0x00c175d0  is `point` within reach of the animated body part?
// ---------------------------------------------------------------------------
// @ 0x00c175d0
bool cSPCreatureBase::CanReachPointWithBodyPart(cSPTransform* transform, const float* point,
                                                uint32_t kind, int32_t part, float* outPos,
                                                uint8_t* outHit, float radiusAdd)
{
    uint32_t parts[255];
    int32_t count = (int32_t)QueryCreatureBodyParts(this, (int32_t)kind, parts, 255);
    if (count <= 0 || part > count) {
        if (outHit != 0) {
            *outHit = 0;
        }
        return false;
    }

    cVector3 local;
    local.x = point[0];
    local.y = point[1];
    local.z = point[2];
    transform->BackTransformPoint(&local);

    int32_t start = 0;
    int32_t end = count;
    if (part >= 0) {
        start = part;
        end = part + 1;
    }

    for (int32_t i = start; i < end; ++i) {
        uint32_t partId = parts[i];
        cBodyAnim* anim = mBody->mAnim;
        cAnimPartSet* set = anim->mpAnimSet;
        cAnimPartInstance* partData = &set->mpParts[partId];
        cVector3 origin;
        anim->GetWorkspaceOrigin(&origin.x, (int)partId);
        float radius = anim->mScale * partData->mRadius;
        float dx = origin.x - local.x;
        float dy = origin.y - local.y;
        float dz = origin.z - local.z;
        if (radius * radius + radiusAdd > dz * dz + dy * dy + dx * dx) {
            float vx = origin.x;
            float vy = origin.y;
            float vz = origin.z;
            if (transform->mFlags & 2) {
                float nx = transform->mRot.m[6] * vz + transform->mRot.m[3] * vy
                         + transform->mRot.m[0] * vx;
                float ny = transform->mRot.m[7] * vz + transform->mRot.m[4] * vy
                         + transform->mRot.m[1] * vx;
                float nz = transform->mRot.m[8] * vz + transform->mRot.m[5] * vy
                         + transform->mRot.m[2] * vx;
                vx = nx;
                vy = ny;
                vz = nz;
            }
            if (outPos != 0 && outHit != 0) {
                outPos[0] = transform->mOffset.x + vx * transform->mScale;
                outPos[1] = transform->mOffset.y + vy * transform->mScale;
                outPos[2] = transform->mOffset.z + vz * transform->mScale;
                *outHit = 1;
            }
            return true;
        }
    }

    if (outPos != 0 && outHit != 0) {
        uint32_t partId = parts[(part < 0) ? 0 : part];
        cBodyAnim* anim = mBody->mAnim;
        cAnimPartSet* set = anim->mpAnimSet;
        cAnimPartInstance* partData = &set->mpParts[partId];
        cVector3 origin;
        anim->GetWorkspaceOrigin(&origin.x, (int)partId);
        float radius = anim->mScale * partData->mRadius;
        float dx = origin.x - local.x;
        float dy = origin.y - local.y;
        float dz = origin.z - local.z;
        float len = (float)(1.0 / sqrt((double)dz * dz + (double)dy * dy
                                       + (double)dx * dx + (double)kEps));
        float vx = local.x + (len * dx) * radius;
        float vy = local.y + (len * dy) * radius;
        float vz = local.z + (len * dz) * radius;
        if (transform->mFlags & 2) {
            float nx = transform->mRot.m[6] * vz + transform->mRot.m[3] * vy
                     + transform->mRot.m[0] * vx;
            float ny = transform->mRot.m[1] * vx + transform->mRot.m[7] * vz
                     + transform->mRot.m[4] * vy;
            float nz = transform->mRot.m[2] * vx + transform->mRot.m[8] * vz
                     + transform->mRot.m[5] * vy;
            vx = nx;
            vy = ny;
            vz = nz;
        }
        outPos[0] = transform->mOffset.x + vx * transform->mScale;
        outPos[1] = transform->mOffset.y + vy * transform->mScale;
        outPos[2] = transform->mOffset.z + vz * transform->mScale;
        *outHit = 1;
    }
    return false;
}

// ---------------------------------------------------------------------------
// 0x00c17a30  position of body part `part` of `kind`
// ---------------------------------------------------------------------------
// @ 0x00c17a30
bool cSPCreatureBase::GetBodyPartPosition(float* outPos, uint32_t kind, bool world, int32_t part)
{
    uint32_t parts[255];
    cVector3 local;
    cSPTransform xf;

    if (part < 0) {
        part = 0;
    }

    uint32_t count = QueryCreatureBodyParts(this, (int32_t)kind, parts, 255);
    if ((uint32_t)part >= count) {
        return false;
    }

    int32_t partIndex = (int32_t)parts[part];
    if (partIndex == -1) {
        return false;
    }

    cBodyAnim* anim = mBody->mAnim;
    if (world) {
        cBodyPart* bp = anim->mpBodyParts + partIndex;
        QuaternionVectorTransform(&local.x, anim->mOrientation, bp->mPosition);
        outPos[0] = local.x + anim->mPosX;
        outPos[1] = local.y + anim->mPosY;
        outPos[2] = local.z + anim->mPosZ;
        return true;
    }

    cBodyPart* bp = anim->mpBodyParts + partIndex;
    outPos[0] = bp->mPosition[0];
    outPos[1] = bp->mPosition[1];
    outPos[2] = bp->mPosition[2];

    xf.mFlags = 0;
    xf.mVersion = 0;
    xf.mOffset = gZeroVector;
    xf.mScale = kOne;
    xf.mRot.Assign(&gIdentityMatrix);
    xf.PreRotateY(-kPi);

    if (xf.mFlags & 2) {
        float x = outPos[0];
        float y = outPos[1];
        float z = outPos[2];
        outPos[0] = xf.mRot.m[0] * x + xf.mRot.m[3] * y + xf.mRot.m[6] * z;
        outPos[1] = xf.mRot.m[1] * x + xf.mRot.m[4] * y + xf.mRot.m[7] * z;
        outPos[2] = xf.mRot.m[2] * x + xf.mRot.m[5] * y + xf.mRot.m[8] * z;
    }
    outPos[0] *= xf.mScale;
    outPos[1] *= xf.mScale;
    outPos[2] *= xf.mScale;
    return true;
}
