// match/slices/s00c18b40/s00c18b40.cpp
// Object file: SPGonzago/SPCreatureBase.obj
// flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /Isrc/game/include
#include <math.h>

typedef unsigned int   uint32;
typedef unsigned char  uint8;
typedef unsigned short uint16;
typedef unsigned long long uint64;
typedef int            int32;

// ---------------------------------------------------------------------------
// globals (unnamed retail data; address in the comment)
// ---------------------------------------------------------------------------
extern const float kRealZero;      // 0x01485378  _HK_REAL_ZERO
extern const float kRealOne;       // 0x01485720  _HK_REAL_ONE
extern const float kSqrtEpsilon;   // 0x013ec4b8
extern const float kThree;         // 0x013eb95c
extern float  gZeroVecX;           // 0x0168d910
extern float  gZeroVecY;           // 0x0168d914
extern float  gZeroVecZ;           // 0x0168d918
extern bool   gB_1572050;          // 0x01572050
extern bool   gB_1572051;          // 0x01572051
extern bool   gB_169e381;          // 0x0169e381
extern float  gF_169e384;          // 0x0169e384
extern float  gF_169e388;          // 0x0169e388
extern float  gF_169e38c;          // 0x0169e38c
extern float  gF_169e390;          // 0x0169e390
extern float  gF_169e3b4;          // 0x0169e3b4
extern float  gF_169e3b8;          // 0x0169e3b8
extern float  gF_169e3bc;          // 0x0169e3bc
extern const char* gBodyPartsString; // 0x015716e8
extern int gAbilityStatesAllocator;  // 0x013ebb38 (eastl allocator)
extern const float kLeapRadiusScale; // 0x01582fd8
extern const float kDefaultSpeedCap; // 0x01582fc0
extern const float kCe80Boost;       // 0x0150c900
extern const float kHalf;            // 0x01471064
extern const float kClampLow;        // 0x013eb8c8
extern const float kPlenEpsilon;     // 0x01488874

// ---------------------------------------------------------------------------
// helpers
// ---------------------------------------------------------------------------
struct Vector3 { float x, y, z; };
struct InventoryItem;

bool   Vector3Equal(const Vector3* a, const Vector3* b);                  // 0x004232c0 (cdecl)
Vector3* normalized_safe(Vector3* out, const Vector3* in);                // 0x00449c20 (cdecl)
void   operator_delete__(void* p);                                       // 0x00f47380 (cdecl)
void*  operator_new(uint32 size, const char* name, int a, int b,
                    const char* file, int line);                          // 0x00f473a0 (cdecl)
void*  FUN_00ac2130(void* begin, void* end, void* dst);                   // 0x00ac2130 (cdecl, copy range)
int    EvaluateContextTargetQuery(void* out, int max, void* abilities,
                                  void* ctx, int a, int b);               // 0x009b2340 (cdecl)

// Planet model used by the jump code.
class cPlanetModel {
public:
    float FUN_00b7e490();                                             // 0x00b7e490
    float GetRadiusAt(const Vector3* p);                              // 0x00b7ef70
    float FUN_00b82310(const Vector3* p);                             // 0x00b82310
};
cPlanetModel* PlanetModel();                                          // 0x00b3d350 (cdecl)

// Locomotion (cLocomotiveObject) sub-object at +0xc0 of the creature.
class cLoco {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual const Vector3* GetPos();                                  // 0x2c
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c0();
    virtual const Vector3* GetForward(Vector3* out);                  // 0x5c
    virtual void v60(); virtual void v64(); virtual void v68();
    virtual const float* GetBounds(float* out);                       // 0x6c
    virtual void v70();
    virtual float GetRadius();                                        // 0x74
    virtual void v78(); virtual void v7c(); virtual void v80(); virtual void v84();
    virtual void v88(); virtual void v8c(); virtual void v90(); virtual void v94();
    virtual void v98(); virtual void v9c(); virtual void va0(); virtual void va4();
    virtual void va8(); virtual void vac(); virtual void vb0(); virtual void vb4();
    virtual void vb8(); virtual void vbc(); virtual void vc0(); virtual void vc4();
    virtual float GetF_0xc8();                                        // 0xc8
    virtual void vcc(); virtual void vd0(); virtual void vd4(); virtual void vd8();
    virtual void Submit(const void* req);                             // 0xdc

    const Vector3* GetVelocity();                                     // 0x00d20610
    void FUN_00c446d0(const Vector3* v, int flag);                    // 0x00c446d0 (ret 8)
};

struct AnimatingCreature {
    char  pad000[0x170];
    uint32 mField170;         // +0x170
    char  pad174[0x17c - 0x174];
    void** mpAbilityList;     // +0x17c
};

struct BodyPartQuery {
    int         flag;         // +0x0
    const char* mpName;       // +0x4
    int         a;            // +0x8
    int         b;            // +0xc
};

// Per-ability state, 16 bytes.
struct AbilityState {
    bool  applied;         // +0x0
    bool  inRange;         // +0x1
    char  pad02[2];
    float chargeLevel;     // +0x4
    double refresh;        // +0x8
};

struct Ability {
    char  pad00[0x104];
    float mCost;           // +0x104
};

struct SpeciesProfile {
    char  pad00[0x548];
    float jumpingAbility;      // +0x548
    char  pad54c[4];
    float flappingAbility;     // +0x550
    char  pad554[0x610 - 0x554];
    uint32 sprintLevel;        // +0x610
    char  pad614[8];
    uint32 preferredSocialType; // +0x61c
    char  pad620[0x698 - 0x620];
    uint32 mCount698;          // +0x698
    char  pad69c[4];
    uint32 mCount6a0;          // +0x6a0
};

// A locomotion request object (constructed on the stack).
struct LocomotionRequest {
    char* mpBegin;
    char  pad[0x6c];
    LocomotionRequest();                                              // 0x00ac9850
};

class cSPCreatureBase {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
    virtual void v70(); virtual void v74(); virtual void v78(); virtual void v7c();
    virtual void v80(); virtual void v84(); virtual void v88(); virtual void v8c();
    virtual void v90(); virtual void v94(); virtual void v98(); virtual void v9c();
    virtual void va0(); virtual void va4(); virtual void va8(); virtual void vac();
    virtual uint32 GetAbilityCount();                                 // 0xb0
    virtual Ability* GetAbility(uint32 index);                        // 0xb4

    char  pad04[0xc0 - 4];
    cLoco mBody;                                                      // 0xc0
    char  padc0[0x110 - 0xc4];
    uint32 mFlags;                                                    // 0x110
    char  pad114[0x137 - 0x114];
    bool  mbLeaping;                                                  // 0x137
    char  pad138[0x2b0 - 0x138];
    int   mState;                                                     // 0x2b0
    char  pad2b4[0xb20 - 0x2b4];
    SpeciesProfile* mpProfile;                                        // 0xb20
    char  padb24[0xb54 - 0xb24];
    AnimatingCreature* mpAnimCreature;                                // 0xb54
    uint32 mGeneralFlags;                                             // 0xb58
    char  padb5c[0xbb0 - 0xb5c];
    bool  mbFieldBB0;                                                 // 0xbb0
    char  padbb1[0xbec - 0xbb1];
    uint32 mInUseAbilityBits[3];                                      // 0xbec
    uint32 mRechargingAbilityBits[3];                                 // 0xbf8
    char  padc04[0xc28 - 0xc04];
    AbilityState* mpAbilityStates;                                    // 0xc28
    char  padc2c[0xe40 - 0xc2c];
    InventoryItem* mpItemBegin;                                       // 0xe40
    InventoryItem* mpItemEnd;                                         // 0xe44
    char  pade48[0xe8c - 0xe48];
    uint32 mCurrentAttackIdx;                                         // 0xe8c

    int  FindIndex(int key);                                          // 0x00c0c080 (ret 4)
    void FUN_00c15dc0(float f);                                       // 0x00c15dc0 (ret 4, ApplyWave)
    void FUN_00c15bd0(int index, int a, int b);                       // 0x00c15bd0 (ret 0xc)
    float FUN_00c0ce80(int a, int b);                                 // 0x00c0ce80 (ret 8)

    int  FUN_00c18b40(int arg);                                       // 0x00c18b40 (ret 4)
    bool TryJumpToTarget(const Vector3* a1, const Vector3* a2,
                         int a3, float a4, bool a5);                  // 0x00c190e0 (ret 0x14)
    uint32 FUN_00c196a0(uint32 index, bool a2, bool a3);              // 0x00c196a0 (ret 0xc)
    void FUN_00c197a0(uint32 index);                                  // 0x00c197a0 (ret 4)
    void FUN_00c19940(bool a);                                        // 0x00c19940 (ret 4)
    void InterruptAnimation(uint32 id, int a, int b);                 // 0x00c12310 (ret 0xc)
    bool GetBodyPartPositionAndOrientation(Vector3& out, void* quat,
                                           uint32 part, bool flag) const; // 0x00c11b50 (ret 0x10)
};

// A view whose `this` is 0x5a8 bytes past the cSPCreatureBase.
struct CreatureSubView {
    char pad[0x5a8];
    Vector3* FUN_00c19870(Vector3* out, int part);                    // 0x00c19870 (ret 8)
};

// Item element of mItemInventory (stride 0x24).
struct InventoryItem {
    char pad[0x20];
    void* mpObject;                                                   // +0x20
};

// Object stored per inventory item (has a Query virtual and a kind at +0x110).
class InventoryObject {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
    virtual void v70(); virtual void v74(); virtual void v78(); virtual void v7c();
    virtual void v80(); virtual void v84(); virtual void v88(); virtual void v8c();
    virtual void v90(); virtual void v94(); virtual void v98(); virtual void v9c();
    virtual void va0(); virtual void va4(); virtual void va8(); virtual void vac();
    virtual void vb0(); virtual void vb4();
    virtual void* Query(uint32 id);                                   // 0xb8
    char padbc[0x110 - 0xbc];
    int mKind;                                                        // 0x110
};

// A growable vector with 0x3c-byte elements (the object at this+0 is the vector).
struct Vector003c {
    void* mpBegin;                                                    // +0x0
    void* mpEnd;                                                      // +0x4
    void* mpCapacity;                                                 // +0x8
    void reserve(uint32 count);                                       // 0x00c199e0 (ret 4)
};

// @ 0x00c196a0
uint32 cSPCreatureBase::FUN_00c196a0(uint32 index, bool a2, bool a3)
{
    uint32 result = 0xffffffffu;
    uint32* mask = a2 ? mRechargingAbilityBits : mInUseAbilityBits;
    if (index < 0x58) {
        bool inUse = (mask[index >> 5] & (1u << (index & 0x1f))) != 0;
        if (inUse)
            goto done;
    }
    if (mCurrentAttackIdx != 0xffffffffu)
        goto done;
    if (index >= GetAbilityCount())
        goto done;
    {
        AbilityState* st = &mpAbilityStates[index];
        Ability* ab = GetAbility(index);
        if (st->chargeLevel < 1.0f)
            goto done;
        if (index < 0x58)
            mask[index >> 5] |= 1u << (index & 0x1f);
        if (a2 || a3) {
            st->chargeLevel = 0.0f;
            FUN_00c15dc0(ab->mCost);
        }
        st->applied = false;
        mpAnimCreature->mField170 = 0;
        result = index;
    }
done:
    return result;
}

// @ 0x00c197a0
void cSPCreatureBase::FUN_00c197a0(uint32 index)
{
    if (index >= 0x58)
        return;
    uint32 bit = 1u << (index & 0x1f);
    uint32 word = index >> 5;
    bool inUse = (mInUseAbilityBits[word] & bit) != 0;
    if (!inUse)
        return;
    if (index >= GetAbilityCount())
        return;
    mInUseAbilityBits[word] &= ~bit;
    mRechargingAbilityBits[word] |= bit;
    AbilityState* st = &mpAbilityStates[index];
    Ability* ab = GetAbility(index);
    st->chargeLevel = 0.0f;
    int i = FindIndex(0x27);
    if (i == -1)
        i = FindIndex(0x50);
    if ((int)index == i)
        return;
    int j = FindIndex(0xd);
    if (j == -1)
        j = FindIndex(0x52);
    if ((int)index == j)
        return;
    FUN_00c15dc0(ab->mCost);
}

// @ 0x00c19870
Vector3* CreatureSubView::FUN_00c19870(Vector3* out, int part)
{
    int buf[0xff];
    BodyPartQuery query;
    int p = part;
    if (part == -1) {
        p = -1;
        cSPCreatureBase* base = (cSPCreatureBase*)((char*)this - 0x5a8);
        if (base != 0) {
            AnimatingCreature* anim = base->mpAnimCreature;
            if (anim != 0 && anim->mpAbilityList != 0) {
                query.flag = 1;
                query.mpName = gBodyPartsString;
                query.a = 0;
                query.b = 0;
                uint32 n = (uint32)EvaluateContextTargetQuery(buf, 0xff,
                                            *anim->mpAbilityList, &query, 0, 0);
                if (n > 0)
                    p = buf[0];
            }
        }
    }
    out->x = gZeroVecX;
    out->y = gZeroVecY;
    out->z = gZeroVecZ;
    ((cSPCreatureBase*)((char*)this - 0x5a8))->GetBodyPartPositionAndOrientation(
        *out, &query, (uint32)p, true);
    return out;
}

// @ 0x00c19940
void cSPCreatureBase::FUN_00c19940(bool a)
{
    int count = (int)(mpItemEnd - mpItemBegin);
    if (count == 0)
        return;
    InventoryItem* it = mpItemBegin;
    int i = 0;
    do {
        if (a != 0) {
            if (i >= (int)(mpItemEnd - mpItemBegin))
                goto docall;
            if (it->mpObject == 0)
                goto docall;
            InventoryObject* o = (InventoryObject*)it->mpObject;
            if (o->Query(0x398420d) == 0)
                goto docall;
            if (o->mKind != 3)
                goto docall;
            goto next;
        }
    docall:
        FUN_00c15bd0(i, 0, 0);
    next:
        ++i;
        ++it;
    } while (i < count);
}

// @ 0x00c199e0
void Vector003c::reserve(uint32 count)
{
    uint32 cur = (uint32)(((char*)mpCapacity - (char*)mpBegin) / 0x3c);
    if (count <= cur)
        return;
    char* p;
    if (count != 0) {
        p = (char*)operator_new(count * 0x3c, "Simulator", 0, 0,
               (const char*)&gAbilityStatesAllocator, 0xd1);
    } else {
        p = 0;
    }
    FUN_00ac2130(mpBegin, mpEnd, p);
    if (mpBegin && ((int*)mpBegin)[-1])
        operator_delete__(mpBegin);
    uint32 n = (uint32)(((char*)mpEnd - (char*)mpBegin) / 0x3c);
    mpBegin = p;
    mpEnd = p + n * 0x3c;
    mpCapacity = p + count * 0x3c;
}


// @ 0x00c18b40
int cSPCreatureBase::FUN_00c18b40(int arg)
{
    SpeciesProfile* prof = mpProfile;
    if (prof->sprintLevel == 0)
        return 0;

    bool bLeap = mbLeaping;
    float range;
    if (bLeap) {
        range = prof->jumpingAbility;
    } else {
        if (mFlags & 0x1000)
            return 0;
        range = prof->flappingAbility;
    }
    if (range <= kRealZero)
        return 0;

    bool isAvatar = ((mGeneralFlags >> 9) & 1) != 0;

    const Vector3* pos = mBody.GetPos();
    Vector3 res = { gZeroVecX, gZeroVecY, gZeroVecZ };

    float inv = 1.0f / sqrtf(pos->x*pos->x + pos->y*pos->y + pos->z*pos->z
                             + kSqrtEpsilon);
    Vector3 fwd = { pos->x*inv, pos->y*inv, pos->z*inv };

    Vector3 face;
    mBody.GetForward(&face);

    const Vector3* vel = mBody.GetVelocity();
    float speed = sqrtf(vel->x*vel->x + vel->y*vel->y + vel->z*vel->z);

    float dot = (fwd.x*vel->y + fwd.y*vel->z) + range*vel->x;
    float q  = range * dot;
    float projX = vel->x - q;
    float t  = fwd.y * dot;
    float projZ = vel->z - t;
    float u  = fwd.x * dot;
    float projY = vel->y - u;
    float projLen = sqrtf(projY*projY + (projZ*projZ + projX*projX));

    float radius = mBody.GetF_0xc8();

    if (gB_1572051 && isAvatar && gB_169e381 &&
        Vector3Equal(vel, (const Vector3*)&gZeroVecX)) {
        res.x = gF_169e388 * gF_169e384;
        res.y = gF_169e38c * gF_169e384;
        res.z = gF_169e390 * gF_169e384;
    }

    if (bLeap) {
        Vector3 r;
        r.z = fwd.z*range + vel->z;
        r.y = fwd.y*range + vel->y;
        r.x = fwd.x*range + vel->x;
        float len = sqrtf(r.z*r.z + r.y*r.y + r.x*r.x);
        float lim = (speed > range) ? speed : range;
        if (len > lim) {
            float s = lim / len;
            r.x *= s;
            r.y *= s;
            r.z *= s;
        }
        r.x -= vel->x;
        r.y -= vel->y;
        r.z -= vel->z;
        res = r;
    } else {
        Vector3 dir = fwd;
        if (radius > projLen) {
            Vector3 a = { face.x + fwd.x*kThree,
                          face.y + fwd.y*kThree,
                          face.z + fwd.z*kThree };
            normalized_safe(&dir, &a);
        }
        res.x = dir.x * range;
        res.y = dir.y * range;
        res.z = dir.z * range;
        if (gB_1572050 && speed > kRealZero &&
            (projX*fwd.x + projY*fwd.y + projZ*fwd.z) < kRealZero) {
            res.x -= projX;
            res.y -= projY;
            res.z -= projZ;
        }
    }

    mBody.FUN_00c446d0(&res, 0);

    if (isAvatar) {
        LocomotionRequest req;
        mBody.Submit(&req);
        if (req.mpBegin && ((int*)req.mpBegin)[-1] != 0)
            operator_delete__(req.mpBegin);
    }

    FUN_00c15dc0((float)arg);

    if (!bLeap) {
        if (prof->mCount698 == 0)
            InterruptAnimation(0x5485a4cu, -1, 0);
        else
            InterruptAnimation(0x77300ffu, -1, 0);
        return 1;
    }

    uint32 id;
    if (prof->preferredSocialType == 0) {
        id = (prof->mCount6a0 == 0) ? 0x25b3bc0u : 0x7995fdcu;
    } else if (prof->mCount6a0 != 0) {
        id = 0x7995fdcu;
    } else {
        id = (prof->mCount698 != 0) ? 0x77300f2u : 0x5261d56u;
    }
    InterruptAnimation(id, -1, 0);

    mState = 3;
    mbLeaping = false;
    if (isAvatar) {
        gF_169e3b4 = pos->x;
        gF_169e3b8 = pos->y;
        gF_169e3bc = pos->z;
    }
    return 1;
}

// @ 0x00c190e0
bool cSPCreatureBase::TryJumpToTarget(const Vector3* a1, const Vector3* a2,
                                      int a3, float a4, bool a5)
{
    SpeciesProfile* prof = mpProfile;
    if (!a5 && prof->sprintLevel == 0)
        return false;

    float r1 = mBody.GetRadius();
    float r2 = mBody.GetRadius();
    float maxSq = a4*a4 + (kLeapRadiusScale*kLeapRadiusScale + r2*r1);

    const Vector3* pos = mBody.GetPos();
    float dx = pos->x - a2->x;
    float dy = pos->y - a2->y;
    float dz = pos->z - a2->z;
    if (dx*dx + dy*dy + dz*dz < maxSq)
        return false;

    bool bLeap = mbLeaping;
    float range;
    if (bLeap) {
        range = prof->jumpingAbility;
    } else {
        range = (mFlags & 0x1000) ? 0.0f : prof->flappingAbility;
    }
    if (a5) {
        if (range <= 0.0f)
            range = 5.0f;
    } else {
        if (range <= 0.0f)
            return false;
    }

    bool flagB = (prof->preferredSocialType != 0) || (prof->flappingAbility > 0.0f);

    cPlanetModel* pm = PlanetModel();
    float f7 = pm->FUN_00b7e490();

    const Vector3* p2 = mBody.GetPos();
    Vector3 face;
    mBody.GetForward(&face);

    float inv = 1.0f / sqrtf(p2->x*p2->x + p2->y*p2->y + p2->z*p2->z
                             + kSqrtEpsilon);
    float fx = p2->x * inv;
    float fy = p2->y * inv;
    float fz = p2->z * inv;

    const Vector3* vel = mBody.GetVelocity();
    float dist = sqrtf(p2->x*p2->x + (p2->y*p2->y + p2->z*p2->z));
    pm->GetRadiusAt(p2);

    float dot = vel->x*fx + fy*vel->y + fz*vel->z;
    float px = vel->x - fx*dot;
    float pz = vel->z - fz*dot;
    float py = vel->y - fy*dot;
    float plen = sqrtf(py*py + (pz*pz + px*px));

    float speedLim = kDefaultSpeedCap;
    if (!flagB) {
        float g;
        if (!mbFieldBB0)
            g = FUN_00c0ce80(2, 0);
        else
            g = FUN_00c0ce80(2, 1) + kCe80Boost;
        speedLim = (g <= plen) ? plen : g;
    }

    float ratio;
    if (plen <= kPlenEpsilon) {
        ratio = 1.0f;
    } else {
        Vector3 proj = { px, py, pz };
        Vector3 dir;
        normalized_safe(&dir, &proj);
        ratio = dir.x*face.x + dir.y*face.y + dir.z*face.z;
    }
    float r = ratio + kHalf;
    if (r <= kClampLow)
        r = kClampLow;
    if (r >= 1.0f)
        r = 1.0f;

    float a = pm->FUN_00b82310(a1);
    float ax = a1->x - p2->x;
    float ay = a1->y - p2->y;
    float az = a1->z - p2->z;
    float d2 = az*az + ay*ay + ax*ax;
    float dd = sqrtf(d2);
    float invd = 1.0f / sqrtf(d2 + kSqrtEpsilon);
    float scale = dd / speedLim;
    float t = (a - dist) / scale - (scale * range) * kHalf;
    if (t > 0.0f)
        t = 0.0f;
    float v = t;

    Vector3 out;
    out.x = fx*v + (invd*ax)*speedLim - vel->x;
    out.y = fy*v + (invd*ay)*speedLim - vel->y;
    out.z = fz*v + (invd*az)*speedLim - vel->z;

    mBody.FUN_00c446d0(&out, 0);
    FUN_00c15dc0((float)a3);

    if (bLeap) {
        uint32 id = (prof->mCount698 == 0) ? 0x5261d56u : 0x77300f2u;
        InterruptAnimation(id, -1, 0);
        mState = 3;
        mbLeaping = false;
        return true;
    }
    uint32 id = (prof->mCount698 == 0) ? 0x5485a4cu : 0x77300ffu;
    InterruptAnimation(id, -1, 0);
    {
        LocomotionRequest req;
        mBody.Submit(&req);
        if (req.mpBegin && ((int*)req.mpBegin)[-1] != 0)
            operator_delete__(req.mpBegin);
    }
    return true;
}
