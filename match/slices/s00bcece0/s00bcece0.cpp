// Slice s00bcece0 -- TakeHit wrapper of a vehicle-like combatant (cCombatant sub-object at +0x120 of its owner).
// Sibling of s00bd0510 (creature variant, sub-object at +0x588). It filters the hit (dead / friendly / stun
// type), reports "fought enemy" to the relationship manager, plays a hit effect, calls cCombatant::TakeHit,
// and on the killing blow notifies the owner, plays a sound and starts the death handling.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-
#include "types.h"

#define VPAD(n) virtual void vpad##n()

struct Vec3 {
    float x, y, z;
    Vec3() {}
    Vec3(float a, float b, float c) : x(a), y(b), z(c) {}
    Vec3(const Vec3& o) : x(o.x), y(o.y), z(o.z) {}
};
struct RawVec3 { float x, y, z; };
struct Mat3 { float m[9]; };
struct BBox { float minx, miny, minz, maxx, maxy, maxz; };

struct XformMsg {
    uint16_t flags;
    uint16_t count;
    RawVec3 pos;
    float scale;                 // +0x10
    uint32_t pad14[3];
    Mat3 rot;                    // +0x20
    XformMsg();                  // 00434040
};

struct cIVisualEffect {
    VPAD(0);
    virtual void Release();                              // +0x04
    virtual void Func8(int a);                           // +0x08
    VPAD(3); VPAD(4); VPAD(5);
    virtual void Apply(XformMsg* m);                     // +0x18
};

template <class T> struct AutoRefCount {
    T* mp;
    AutoRefCount() : mp(0) {}
    ~AutoRefCount() { if (mp) mp->Release(); }
    T** AsPPTypeParam();                                 // 00a16f40
};

struct EffectsMgr {
    VPAD(0); VPAD(1); VPAD(2); VPAD(3); VPAD(4); VPAD(5); VPAD(6); VPAD(7); VPAD(8); VPAD(9); VPAD(10);
    virtual bool CreateEffect(uint32_t id, int a, cIVisualEffect** out);   // +0x2c
};
struct SoundMgr {
    VPAD(0); VPAD(1); VPAD(2); VPAD(3); VPAD(4); VPAD(5); VPAD(6); VPAD(7); VPAD(8); VPAD(9); VPAD(10);
    VPAD(11); VPAD(12); VPAD(13); VPAD(14); VPAD(15); VPAD(16); VPAD(17); VPAD(18); VPAD(19); VPAD(20);
    VPAD(21); VPAD(22); VPAD(23);
    virtual void Play(uint32_t id, const Vec3* pos, const Vec3* dir);      // +0x60
};

// Secondary base at +0x34 of the owner: transform interface.
struct cSpatial {
    VPAD(0); VPAD(1); VPAD(2); VPAD(3); VPAD(4); VPAD(5); VPAD(6); VPAD(7); VPAD(8); VPAD(9); VPAD(10);
    virtual Vec3* GetPosition();                         // +0x2c
    VPAD(12); VPAD(13); VPAD(14); VPAD(15); VPAD(16); VPAD(17);
    virtual bool IsVisible();                            // +0x48
    VPAD(19); VPAD(20); VPAD(21); VPAD(22);
    virtual Vec3* GetFacing(Vec3* out);                  // +0x5c
    VPAD(24); VPAD(25);
    virtual BBox* GetBounds();                           // +0x68
    virtual BBox* GetBoundsCopy(BBox* out);              // +0x6c
    virtual float GetRadius();                           // +0x70
};

struct FlagTarget { uint8_t pad[0x8e]; uint8_t mFlag8e; void SetFlag8e(); };   // 00bef880

struct Owner;
// The object returned by owner->Slot84 (a "parent" with its own vtable).
struct Parent {
    VPAD(0); VPAD(1); VPAD(2); VPAD(3); VPAD(4); VPAD(5); VPAD(6); VPAD(7); VPAD(8); VPAD(9); VPAD(10);
    VPAD(11); VPAD(12); VPAD(13); VPAD(14); VPAD(15); VPAD(16); VPAD(17); VPAD(18);
    virtual int GetOwnerEmpire();                        // +0x4c
    uint8_t pad[0x2f0 - 0x50];
    int mField2f0;
    void Func_bdbf10();                                  // 00bdbf10
    int Func_bd81f0();                                   // 00bd81f0 (returns [this+0x2f0])
};

// The thing that hit us.
struct HitSource {
    VPAD(0); VPAD(1); VPAD(2); VPAD(3); VPAD(4); VPAD(5); VPAD(6); VPAD(7); VPAD(8); VPAD(9); VPAD(10);
    VPAD(11); VPAD(12); VPAD(13); VPAD(14); VPAD(15); VPAD(16); VPAD(17); VPAD(18); VPAD(19); VPAD(20);
    VPAD(21); VPAD(22);
    virtual void* Cast(uint32_t id);                     // +0x5c
};
struct Inventory { uint32_t pad[0x508 / 4]; };

struct cSPTimer {
    bool IsRunning();                                    // 00feba90
    uint64_t GetElapsedTime();                           // 00bc3190
    void Restart();                                      // 00bc3130
};

struct GameSim { void* GetPlayerInventory(); void Func_ffd830(void* owner); }; // 00a1ad60 / 00ffd830

struct RelMgr { float RecordFoughtEnemyEvent(int a, int b, uint32_t c, float d); };   // 00d06270 (ret 0x10)
struct NounMgr { int GetPlayerEmpireOrMinus1(); };       // 00b1f9d0
struct Tuning { float Func_102a4a0(); };                 // 0102a4a0

// Object at this+0xd0 (aggro / target helper).
struct Aggro {
    VPAD(0); VPAD(1); VPAD(2); VPAD(3); VPAD(4); VPAD(5); VPAD(6); VPAD(7); VPAD(8); VPAD(9); VPAD(10);
    virtual bool IsDone();                               // +0x2c
    void Func_bdff50(const Vec3* pos, float r, int who); // 00bdff50 (ret 0xc)
    void Func_bd9e50();                                  // 00bd9e50
};

struct RandomLinearCongruential { double RandomDoubleUniform(); };   // 009360d0
extern RandomLinearCongruential g_Random;                           // 01601760

// globals / free functions
int GetCurrentGameMode();                                // 00b5b800
int GetPlayerEmpireID();                                 // 01021090
GameSim* GetUFOSimulator();                              // 00ffbe50
EffectsMgr* GetEffectsManager();                         // 0067ddd0
SoundMgr* GetSoundMgr();                                 // 00b3d240
RelMgr* GetRelationshipManager();                        // 00b3d2c0
NounMgr* GetNounManager();                               // 00b3d300
Vec3* normalized_safe(Vec3* out, const Vec3* v);         // 00449c20
Mat3* Matrix3FromFacingAndUp(Mat3* out, const Vec3* facing, const Vec3* up);   // 0069b440
Tuning* GetSpaceCombatTuning();                          // 01029940
struct Planet { int Func_c70e00(); };                    // 00c70e00
Planet* GetActivePlanet();                               // 01021260
void* GetActivePlanetRecord();                           // 010212a0
struct Empire { uint8_t pad[0x44]; uint8_t mFlag44; };
Empire* Func_1021230();                                  // 01021230
bool Func_1029a10(int empire, void* planetRecord);       // 01029a10
float Func_bd7fb0();                                     // 00bd7fb0 (returns 80.0f)
void Func_be9b20(void* planetRecord, Parent* p, int a, int b, float f, int attacker, int zero);   // 00be9b20
void Func_be2440(Parent* p, int a, int b);               // 00be2440 (cdecl, 3 args)
__forceinline int RoundF(float x) { __asm { cvtss2si eax, x } }

// Owner object (primary base; the combatant lives at +0x120).
struct Owner {
    VPAD(0); VPAD(1); VPAD(2); VPAD(3); VPAD(4); VPAD(5); VPAD(6);
    VPAD(7);
    virtual int GetClassID();                            // +0x20
    VPAD(9); VPAD(10);
    virtual bool IsDead();                               // +0x2c
    VPAD(12); VPAD(13); VPAD(14); VPAD(15); VPAD(16); VPAD(17); VPAD(18);
    virtual int GetOwnerEmpire();                        // +0x4c
    VPAD(20); VPAD(21); VPAD(22); VPAD(23); VPAD(24); VPAD(25); VPAD(26); VPAD(27); VPAD(28); VPAD(29);
    VPAD(30); VPAD(31); VPAD(32);
    virtual Parent* GetParent();                         // +0x84
    FlagTarget* GetFlagTarget();                         // 00bcd630
    void Func_bcd690(bool killed, int type);             // 00bcd690 (ret 8)
    void Func_bcd550(int a);                             // 00bcd550 (ret 4)
    void Func_bcda90();                                  // 00bcda90
};

struct Combatant {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6();
    virtual void OnHitSource(HitSource* s);              // +0x1c
    uint8_t pad04[0x2c - 4];
    float mF2c;                                          // +0x2c
    uint8_t pad30[0x38 - 0x30];
    float mF38;                                          // +0x38
    uint8_t pad3c[0xd0 - 0x3c];
    Aggro* mpAggro;                                      // +0xd0
    uint8_t padd4[0x118 - 0xd4];
    cSPTimer mTimer118;                                  // +0x118
    uint8_t pad119[0x138 - 0x119];
    cSPTimer mTimer138;                                  // +0x138
    uint8_t pad139[0x200 - 0x139];
    cSPTimer mStunTimer;                                 // +0x200

    Owner* GetOwner() { return (Owner*)((char*)this - 0x120); }
    cSpatial* GetSpatial() { return (cSpatial*)((char*)this - 0xec); }
    int GetDamageState();                                // 008e7f80
    void TakeHit(float dmg, int attacker, int type, uint32_t extra, HitSource* src);   // 00bfcdd0
    void AddStun(int ms);                                // 00bfc640
    void Hit(float dmg, int attacker, int type, uint32_t extra, HitSource* src);       // 00bcece0
};

// @ 0x00bcece0
void Combatant::Hit(float dmg, int attacker, int type, uint32_t extra, HitSource* src)
{
    if (GetOwner()->IsDead())
        return;
    if (type == 0xb) {
        if (GetOwner()->GetClassID() != 0x1a56aba)
            return;
        AddStun(RoundF(dmg * 1000.0f));
        Func_be2440(GetOwner()->GetParent(), 0, 0);
        return;
    }
    if (src && src->Cast(0x436f315))
        return;
    if (GetCurrentGameMode() == 0x1654c05 && src) {
        void* u = src->Cast(0xb033b403);
        if (u && *(int*)((char*)u + 0x714) == 3)
            attacker = GetPlayerEmpireID();
    }
    bool countable;
    if (type == 10) {
        if (attacker != GetOwner()->GetOwnerEmpire())
            return;
        if (dmg > 0.0f && mF2c > mF38) {
            SoundMgr* sm = GetSoundMgr();
            BBox tmp;
            BBox* b = GetSpatial()->GetBoundsCopy(&tmp);
            Vec3 pos((b->minx + b->maxx) * 0.5f, (b->miny + b->maxy) * 0.5f, (b->minz + b->maxz) * 0.5f);
            Vec3 fwd;
            sm->Play(0x3704925, &pos, GetSpatial()->GetFacing(&fwd));
        }
        countable = false;
    } else if (type == 0xc || type == 0x10 || type == 4 || type == 0xf) {
        countable = false;
    } else {
        countable = true;
        if (attacker == GetPlayerEmpireID() && GetCurrentGameMode() != 0x1654c10)
            GetOwner()->GetParent()->Func_bdbf10();
        OnHitSource(src);
        if (GetCurrentGameMode() == 0x1654c05) {
            void* inv = GetUFOSimulator()->GetPlayerInventory();
            Inventory* pi = inv ? (Inventory*)((char*)inv + 0x508) : 0;
            if ((void*)src == (void*)pi) {
                int o = GetOwner()->GetOwnerEmpire();
                if (o != GetPlayerEmpireID())
                    GetUFOSimulator()->Func_ffd830(GetOwner()->GetParent());
            }
        }
        if (attacker != -1 && GetCurrentGameMode() == 0x1654c04 && dmg > 0.0f &&
            GetOwner()->GetOwnerEmpire() != attacker) {
            GetRelationshipManager()->RecordFoughtEnemyEvent(GetOwner()->GetOwnerEmpire(), attacker, 0x526e501, 1.0f);
            if (attacker == GetNounManager()->GetPlayerEmpireOrMinus1()) {
                bool skip = false;
                if (mStunTimer.IsRunning() && mStunTimer.GetElapsedTime() <= 5000)
                    skip = true;
                if (!skip) {
                    if (GetSpatial()->IsVisible()) {
                        AutoRefCount<cIVisualEffect> fx;
                        if (GetEffectsManager()->CreateEffect(0x69a49c25, 0, fx.AsPPTypeParam())) {
                            XformMsg msg;
                            float h = GetSpatial()->GetBounds()->maxz + 2.0f;
                            Vec3 tmp;
                            Vec3* n = normalized_safe(&tmp, GetSpatial()->GetPosition());
                            float ox = n->x * h, oy = n->y * h, oz = n->z * h;
                            Vec3* p = GetSpatial()->GetPosition();
                            Vec3 np(p->x + ox, p->y + oy, p->z + oz);
                            msg.flags |= 4;
                            msg.count += 1;
                            msg.pos = *(RawVec3*)&np;
                            Vec3 fwd;
                            Mat3 mt;
                            msg.rot = *Matrix3FromFacingAndUp(&mt, GetSpatial()->GetFacing(&fwd), GetSpatial()->GetPosition());
                            msg.flags |= 2;
                            msg.count += 2;
                            msg.scale = 4.0f;
                            fx.mp->Apply(&msg);
                            fx.mp->Func8(0);
                        }
                        mStunTimer.Restart();
                    }
                }
            }
        }
    }

    int before = GetDamageState();
    TakeHit(dmg, attacker, type, extra, src);
    if (countable) {
        FlagTarget* ft = GetOwner()->GetFlagTarget();
        if (ft)
            ft->SetFlag8e();
        mTimer118.Restart();
    }
    bool killed = false;
    if (GetDamageState() == 2 && before != 2) {
        if (before == 0) {
            if (type == 0 || type == 2) {
                SoundMgr* sm = GetSoundMgr();
                Vec3 fwd;
                sm->Play(0x1b559d7, GetSpatial()->GetPosition(), GetSpatial()->GetFacing(&fwd));
            }
            killed = true;
        }
        if (mpAggro) {
            bool doIt = true;
            if (GetCurrentGameMode() == 0x1654c05) {
                if (GetActivePlanet()->Func_c70e00() == 4 && attacker == GetPlayerEmpireID())
                    doIt = false;
            }
            if (doIt && (attacker != GetPlayerEmpireID() || Func_1021230()->mFlag44)) {
                float mult = 1.0f;
                if (GetCurrentGameMode() == 0x1654c05)
                    mult = GetSpaceCombatTuning()->Func_102a4a0();
                if (Func_1029a10(attacker, GetActivePlanetRecord())) {
                    Parent* o = GetOwner()->GetParent();
                    Func_be9b20(GetActivePlanetRecord(), GetOwner()->GetParent(), GetOwner()->GetParent()->Func_bd81f0(),
                                o->GetOwnerEmpire(), Func_bd7fb0() * mult, attacker, 0);
                }
            }
        }
        mTimer138.Restart();
        GetOwner()->Func_bcda90();
    }

    if (mpAggro && !mpAggro->IsDone()) {
        GetOwner()->Func_bcd690(killed, type);
        if (type == 0) {
            Vec3* p = GetSpatial()->GetPosition();
            Vec3 pos = *p;
            Aggro* a = mpAggro;
            mpAggro->Func_bdff50(&pos, GetSpatial()->GetRadius() * 2.0f, attacker);
        }
        if (mF38 < 1.5258789e-05f) {
            if (type == 0xd && (float)g_Random.RandomDoubleUniform() < 0.5f)
                GetOwner()->Func_bcd550(1);
            Func_be2440(GetOwner()->GetParent(), 0, 0);
        }
        mpAggro->Func_bd9e50();
    }
}
