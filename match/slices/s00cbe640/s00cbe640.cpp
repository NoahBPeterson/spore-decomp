// Slice s00cbe640: 0x00cbea20, a periodic "culture attack" tick (named SP::cDefaultAoEArea::Update
// by the caller-scored PDB candidate; the body launches cCulturalProjectile objects).
//
// `this` is a secondary-base subobject that sits 0xd4 bytes into the real object (the first thing
// the function does is call virtual slots 14/15 on `this - 0xd4`). Every tick (unless the game
// clock is paused) it accumulates elapsed time; once 3000 ms have passed and the "context"
// (+0x14) carries the expected comm-context id, it
//   * mirrors the context's spatial object (position / rotation) onto the real object,
//   * finds the tribe/city the attack targets and the city hall that belongs to it,
//   * works out a start/end point between the hall and the target,
//   * launches one projectile for every tribe member of type 0x1a55e4d that has its flag set
//     and passes a 1-in-4 random roll (only when the target is the city's own tribe), plus one
//     more projectile at the end, or a single projectile when there was no usable city.
// Returns true when the guard flag (+0x28) was clear (the work was attempted).
//
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc)
#include "types.h"

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
};

// Generic COM-like game object. Only the slots this function uses carry a real name.
class Obj {
public:
    virtual void v00(); virtual void v04();
    virtual Obj* GetObject();                        // 0x08
    virtual void v0c(); virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual const Vector3* GetPosition();            // 0x2c
    virtual const Vector3* GetRotation();            // 0x30
    virtual void v34();
    virtual void SetPosition(const Vector3* p);      // 0x38 (on the projectile's embedded interface)
    virtual void v3c(); virtual void v40(); virtual void v44(); virtual void v48();
    virtual void v4c(); virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64(); virtual void v68();
    virtual const float* GetBounds(float* tmp);      // 0x6c
    virtual void v70(); virtual void v74(); virtual void v78(); virtual void v7c();
    virtual void v80(); virtual void v84(); virtual void v88(); virtual void v8c();
    virtual void v90(); virtual void v94(); virtual void v98(); virtual void v9c();
    virtual void va0(); virtual void va4(); virtual void va8(); virtual void vac();
    virtual void vb0(); virtual void vb4();
    virtual Obj* Cast(const void* typeId);           // 0xb8
};

// The real object `this` sits inside (slots 14 and 15 mirror the context's spatial state).
class Owner {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c(); virtual void v10();
    virtual void v14(); virtual void v18(); virtual void v1c(); virtual void v20(); virtual void v24();
    virtual void v28(); virtual void v2c(); virtual void v30(); virtual void v34();
    virtual void SetPosition(const Vector3* p);      // 0x38
    virtual void SetRotation(const Vector3* r);      // 0x3c
};

struct Ref { Obj* p; };   // intrusive smart pointer (just the raw pointer)

// Embedded interface at +0x508 of a tribe object.
class TribeIface {
public:
    virtual void v00(); virtual void v04();
    virtual Obj* v08();                              // 0x08
    virtual void v0c();
    virtual void* v10();                             // 0x10
    virtual void v14(); virtual void v18(); virtual void v1c(); virtual void v20(); virtual void v24();
    virtual void v28(); virtual void v2c(); virtual void v30(); virtual void v34(); virtual void v38();
    virtual void v3c(); virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50();
    virtual void* GetTarget();                       // 0x54
};

class Tribe {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c(); virtual void v10();
    virtual void v14(); virtual void v18(); virtual void v1c(); virtual void v20(); virtual void v24();
    virtual void v28(); virtual void v2c(); virtual void v30(); virtual void v34(); virtual void v38();
    virtual void v3c(); virtual void v40(); virtual void v44(); virtual void v48();
    virtual void* GetOwnerId();                      // 0x4c
    uint32_t pad04[(0x508 - 0x50) / 4];
    TribeIface iface508;                             // 0x508 (vptr)
};

class Ctx {
public:
    uint32_t pad[0x114 / 4];
    Ref r114;
    Ref r118;
    int GetCommContext();                            // 0x00ce6950 ([this+0x184])
    float GetSpeed();                                // 0x0104be50 ([this+0x1d8])
};

class RandomLC { public: unsigned RandomUint32Uniform(unsigned n); };   // 0x00a68fb0 (thiscall)
extern RandomLC sMathRandom;                                          // 0x01601760

struct Member {                                       // tribe member (type 0x1a55e4d)
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c(); virtual void v10();
    virtual void v14(); virtual void v18(); virtual void v1c(); virtual void v20(); virtual void v24();
    virtual void v28(); virtual void v2c(); virtual void v30(); virtual void v34();
    virtual int GetTypeId();                          // 0x38
    uint32_t pad04[(0x34 - 4) / 4];
    Obj sub34;                                        // 0x34
    uint32_t pad38[(0x288 - 0x38) / 4];
    uint8_t b288;
    uint8_t flag289;                                  // 0x289
};

struct MemberVec { Member** mpBegin; Member** mpEnd; };

class Slot { public: uint32_t pad[0x70 / 4]; Ref r70; };

class Projectile;
class City;

// The cast target of ctx->r118 (type 0x3d5c477): knows its city and a slot index.
class Caster {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c(); virtual void v10();
    virtual void v14(); virtual void v18(); virtual void v1c(); virtual void v20(); virtual void v24();
    virtual void v28(); virtual void v2c(); virtual void v30(); virtual void v34(); virtual void v38();
    uint32_t pad04[(0x1d4 - 0x3c) / 4];
    uint8_t slotIndex;                                // 0x1d4
    City* GetCity();                                  // 0x00bd84e0 (thiscall, via slot 0x30)
};

class CityHall { public: uint32_t pad04[0x34 / 4]; Obj sub34; };

class City {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c(); virtual void v10();
    virtual void v14(); virtual void v18(); virtual void v1c(); virtual void v20(); virtual void v24();
    virtual void v28(); virtual void v2c(); virtual void v30(); virtual void v34(); virtual void v38();
    virtual void v3c(); virtual void v40(); virtual void v44(); virtual void v48();
    virtual void* GetOwnerId();                       // 0x4c
    CityHall* GetCityHall();                          // 0x00bd9b40 ([this+0x320])
    MemberVec* GetMembers();                          // 0x00c8e810 (&this[+0x340])
    void* GetCivilization();                          // 0x00bd9bf0 ([this+0x590])
    Slot* GetSlot(int index);                         // 0x00bd9e80
    uint32_t pad04[(0x750 - 0x50) / 4];
    float scale;                                      // 0x750
};

class Projectile {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c(); virtual void v10();
    virtual void v14(); virtual void v18(); virtual void v1c(); virtual void v20(); virtual void v24();
    virtual void v28(); virtual void v2c(); virtual void v30(); virtual void v34(); virtual void v38();
    virtual void v3c(); virtual void v40(); virtual void v44();
    virtual void SetOwnerId(void* id);                // 0x48
    uint32_t pad04[(0x34 - 4) / 4];
    Obj sub34;                                        // 0x34
    void Launch(void* owner, void* vehicle, void* tool, void* target, const Vector3* targetPos,
                float speed, bool arg538, bool spin);  // 0x00cbda10 (thiscall, ret 0x20)
};

class NounManager {
public:
    Projectile* GetProjectile();                      // 0x00cb6ea0
    void* GetOwner(void* tribeOwner);                 // 0x00b25f40 (thiscall, ret 4)
};
NounManager* GetNounManager();                        // 0x00b3d300 (cdecl, returns a global)

struct GameTime { uint32_t pad[0x48 / 4]; uint32_t flags; };
GameTime* GetGameTimeManager();                       // 0x00b3d380

// cdecl "interface cast" helpers: take the address of a smart pointer.
Tribe* CastTribe(const Ref* ref);                     // 0x00bd8440
void* CastCommodityNode(const Ref* ref);              // 0x00c9f020
void* CastSpatial(const Ref* ref);                    // 0x00ad2690
Caster* CastCaster(const Ref* ref);                   // 0x00cb45f0

extern const int kTypeA;                              // 0x013f94d4

class cSPTimer { public: int64_t GetElapsedTime(); }; // 0x00bc3190 (thiscall, edx:eax)

class cAttackTick {
public:
    uint32_t pad00[0x14 / 4];
    Ctx* mpCtx;                 // 0x14
    uint32_t pad18[(0x28 - 0x18) / 4];
    bool mbGuard;               // 0x28
    uint8_t pad29[7];
    cSPTimer mTimer;            // 0x30
    uint32_t pad34[(0x50 - 0x34) / 4];
    int64_t mTotal;             // 0x50
    uint64_t mSinceLaunch;      // 0x58
    int64_t mLast;              // 0x60

    bool Update();              // 0x00cbea20
};

// @ 0x00cbea20
bool cAttackTick::Update()
{
    bool active = !mbGuard;
    if (active) {
        Owner* owner = (Owner*)((char*)this - 0xd4);
        Obj* q = mpCtx->r118.p;
        Obj* cast = 0;
        if (q)
            cast = q->Cast(&kTypeA);
        if (q && cast) {
            Obj* obj = cast->GetObject();
            owner->SetPosition(obj->GetPosition());
            owner->SetRotation(obj->GetRotation());
        } else {
            owner->SetPosition(mpCtx->r114.p->GetPosition());
            owner->SetRotation(mpCtx->r114.p->GetRotation());
        }
        bool commOk = mpCtx->GetCommContext() == (int)0x94e412ed;
        int64_t now = mTimer.GetElapsedTime();
        if ((GetGameTimeManager()->flags & 1) == 0) {
            mTotal += now - mLast;
            mSinceLaunch += now - mLast;
            if (commOk) {
                if (mSinceLaunch > 3000)
                    mSinceLaunch = 0;
                if (mSinceLaunch == 0) {
                    Tribe* tribe = CastTribe(&mpCtx->r114);
                    if (tribe) {
                        TribeIface* iface = &tribe->iface508;
                        float tmp[6];
                        const float* b = iface->v08()->GetBounds(tmp);
                        Vector3 mid;
                        mid.x = (b[0] + b[3]) * 0.5f;
                        mid.y = (b[4] + b[1]) * 0.5f;
                        mid.z = (b[5] + b[2]) * 0.5f;
                        Vector3 start = *mpCtx->r118.p->GetPosition();
                        Vector3 end = *mpCtx->r118.p->GetPosition();
                        bool arg538 = false;
                        bool spin;
                        if (!CastTribe(&mpCtx->r118) && !CastCommodityNode(&mpCtx->r118))
                            spin = CastSpatial(&mpCtx->r118) == 0;
                        else
                            spin = false;
                        Member* member;
                        Caster* caster = CastCaster(&mpCtx->r118);
                        if (caster) {
                            City* city = caster->GetCity();
                            if (city) {
                                CityHall* hall = city->GetCityHall();
                                if (hall) {
                                    Obj* hallSub = &hall->sub34;
                                    start = *hallSub->GetPosition();
                                    Slot* slot = caster->GetCity()->GetSlot(caster->slotIndex);
                                    Tribe* tribe2 = CastTribe(&slot->r70);
                                    if (!tribe2) {
                                        arg538 = true;
                                    } else {
                                        float k = city->scale + 105.0f;
                                        Obj* sub2 = (Obj*)((char*)tribe2 + 0x34);
                                        const Vector3* a = sub2->GetPosition();
                                        const Vector3* h = hallSub->GetPosition();
                                        Vector3 d((h->x - a->x) * k * 0.004f, (h->y - a->y) * k * 0.004f,
                                                  (h->z - a->z) * k * 0.004f);
                                        const Vector3* a2 = sub2->GetPosition();
                                        start = Vector3(d.x + a2->x, a2->y + d.y, a2->z + d.z);
                                        k = city->scale + 95.0f;
                                        a = sub2->GetPosition();
                                        h = hallSub->GetPosition();
                                        d = Vector3((h->x - a->x) * k * 0.004f, (h->y - a->y) * k * 0.004f,
                                                    (h->z - a->z) * k * 0.004f);
                                        a2 = sub2->GetPosition();
                                        end = Vector3(a2->x + d.x, a2->y + d.y, a2->z + d.z);
                                        if (tribe2 == tribe) {
                                            arg538 = true;
                                            MemberVec* members = city->GetMembers();
                                            int n = (int)(members->mpEnd - members->mpBegin);
                                            for (int i = 0; i < n; ++i) {
                                                member = members->mpBegin[i];
                                                if (member->GetTypeId() == 0x1a55e4d && member->flag289 &&
                                                    sMathRandom.RandomUint32Uniform(4) == 0) {
                                                    Projectile* proj = GetNounManager()->GetProjectile();
                                                    proj->SetOwnerId(city->GetOwnerId());
                                                    proj->sub34.SetPosition(member->sub34.GetPosition());
                                                    proj->Launch(city->GetCivilization(), tribe, member,
                                                                 iface->GetTarget(), &end,
                                                                 mpCtx->GetSpeed(), false, false);
                                                }
                                            }
                                            Projectile* proj = GetNounManager()->GetProjectile();
                                            proj->SetOwnerId(city->GetOwnerId());
                                            proj->sub34.SetPosition(hallSub->GetPosition());
                                            proj->Launch(city->GetCivilization(), tribe, member,
                                                         iface->GetTarget(), &end,
                                                         mpCtx->GetSpeed(), true, false);
                                        }
                                    }
                                }
                            }
                            spin = false;
                        }
                        Projectile* proj = GetNounManager()->GetProjectile();
                        proj->SetOwnerId(tribe->GetOwnerId());
                        proj->sub34.SetPosition(&mid);
                        proj->Launch(GetNounManager()->GetOwner(iface->v10()), tribe, member,
                                     iface->GetTarget(), &start, mpCtx->GetSpeed(), arg538, spin);
                    }
                }
            }
        }
        mLast = now;
    }
    return active;
}
