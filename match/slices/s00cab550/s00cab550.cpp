// Slice s00cab550 -- cVehicle override of cCombatant::TakeDamage (vtable slot 0x18).
// `this` is the cCombatant sub-object, located 0x508 bytes into the cVehicle; the cLocomotiveObject
// sub-object sits at cVehicle+0x34 (this-0x4d4). Field names follow the ModAPI cVehicle layout.
#include "types.h"

struct Vec3 { float x, y, z; };
struct Mat3 { float m[9]; };

struct XformMsg {
    uint16_t mFlags;     // +0x0
    uint16_t mCount;     // +0x2
    Vec3     mPos;       // +0x4
    float    mScale;     // +0x10
    Mat3     mMat;       // +0x14
    XformMsg();          // 0x00434040
};

struct VehV;
struct CivV;
struct CombatantV;

// ---- small helpers -----------------------------------------------------------------------
__forceinline int RoundToInt(float f) { __asm cvtss2si eax, f }   // asm helper in the original

// ---- stub types --------------------------------------------------------------------------
struct GameDataV { char pad[4]; };

struct GameDataRef {                           // EA::AutoRefCount<..>
    GameDataV* mp;
    void Assign(GameDataV* p);                 // 0x00b5f950 (operator=, ret 4)
};

struct IdleAnim {
    char pad0[8];
    float mDuration;                           // +0x8
    float mDamage;                             // +0xc
    char pad1[0x2c - 0x10];
    GameDataRef mSource;                       // +0x2c
};

struct IdleHost {                              // cSPCreatureBase at group-order +8
    IdleAnim* PlayIdleAnimation(uint32_t flags, int z);                        // 0x00bc96a0 (ret 8)
    IdleAnim* StartIdle(uint32_t flags, int z, float dur, GameDataV* src);     // 0x00bc97f0 (ret 0x10)
};
struct IdleOwner {
    char pad[8];
    IdleHost host;                             // +0x8
};

struct IEffect {
    virtual void v0();
    virtual void Release();                    // 0x4
    virtual void Stop(int arg);                // 0x8
    virtual void v3(); virtual void v4(); virtual void v5();
    virtual void Send(XformMsg* msg);          // 0x18
};
struct EffectRef {
    IEffect* mp;
    void** AsPPTypeParam();                    // 0x00a16f40
};
struct EffectsManagerV {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
    virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
    virtual void s8(); virtual void s9(); virtual void s10();
    virtual bool CreateEffect(uint32_t id, int z, void** out);     // 0x2c
};
extern EffectsManagerV* GetEffectsManager();   // 0x0067ddd0

struct SpawnMgrV {                             // FUN_00b3d240 result
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual void s7();
    virtual void s8();
    virtual void s9();
    virtual void s10();
    virtual void s11();
    virtual void s12();
    virtual void s13();
    virtual void s14();
    virtual void s15();
    virtual void s16();
    virtual void s17();
    virtual void s18();
    virtual void s19();
    virtual void s20();
    virtual void s21();
    virtual void s22();
    virtual void s23();
    virtual void SpawnEffect(uint32_t id, Vec3* pos, Vec3* dir);   // 0x60
};
extern SpawnMgrV* GetSpawnMgr();               // 0x00b3d240

struct BehaviorMgrV {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
    virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
    virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11();
    virtual void s12(); virtual void s13(); virtual void s14();
    virtual void Remove(void* agent);          // 0x3c
};
extern BehaviorMgrV* GetBehaviorMgr();         // 0x00b3d260

struct CivV {                                  // civilization (cGameData primary vtable)
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
    virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
    virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11();
    virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
    virtual void s16(); virtual void s17(); virtual void s18();
    virtual uint32_t GetPoliticalID();         // 0x4c
    char pad[0x40 - 4];
    int mField40;                              // +0x40
    void RemoveVehicle(VehV* v);               // 0x00bf3b50 (ret 4)
    int F_bef950();                            // 0x00bef950
};

struct TickerV {                               // singleton from FUN_00c9efc0
    void Notify(uint32_t v);                   // 0x00dcc300 (ret 4)
};
extern TickerV* GetTicker();                   // 0x00c9efc0

struct CityV {
    CivV* GetCivilization();                   // 0x00bd9bf0
};
struct PlanetModelV {
    CityV* FindCity(const Vec3* p);            // 0x00b894a0 (ret 4)
};
extern PlanetModelV* GetPlanetModel();         // 0x00b3d350

struct RelMgrV {
    float RecordFoughtEnemyEvent(uint32_t a, uint32_t b, uint32_t c, float d);   // 0x00d06270 (ret 0x10); x87 result unused
};
extern RelMgrV* GetRelationshipManager();      // 0x00b3d2c0

struct NounMgrV {
    CivV* GetCivByPoliticalID(uint32_t id);    // 0x00b25f40 (ret 4)
    CivV* GetPlayerCivilization();             // 0x00b25fb0
    int   GetPlayerEmpireOrMinus1();           // 0x00b1f9d0
};
extern NounMgrV* GetNounMgr();                 // 0x00b3d300

struct TimerV {                                // cGonzagoTimer / cSPTimer (0x20 bytes)
    char pad[0x20];
    bool     IsRunning();                      // 0x00feba90
    uint64_t GetElapsedTime();                 // 0x00bc3190
    void     Restart();                        // 0x00bc3130
};

struct LocoV {                                 // cLocomotiveObject (cSpatialObject vtable) at vehicle+0x34
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
    virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
    virtual void s8(); virtual void s9(); virtual void s10();
    virtual const Vec3* GetPosition();         // 0x2c
    virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
    virtual void s16(); virtual void s17();
    virtual bool IsOnView();                   // 0x48
    virtual void s19(); virtual void s20(); virtual void s21(); virtual void s22();
    virtual Vec3* GetDirection(Vec3* out);     // 0x5c (sret, ret 4)
    virtual void s24(); virtual void s25();
    virtual const float* GetLocalExtents();    // 0x68
    virtual float* GetWorldExtents(float* out);// 0x6c (sret, ret 4)
    virtual void s28(); virtual void s29(); virtual void s30(); virtual void s31();
    virtual void s32(); virtual void s33(); virtual void s34(); virtual void s35();
    virtual void s36(); virtual void s37();
    virtual const void* GetModelKey();         // 0x98
};

struct VehV {                                  // cVehicle: primary (cGameData) vtable
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
    virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
    virtual void s8(); virtual void s9(); virtual void s10();
    virtual bool IsDestroyed();                // 0x2c
    virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
    virtual void s16(); virtual void s17(); virtual void s18();
    virtual uint32_t GetPoliticalID();         // 0x4c
    void DestroyVehicle(bool flag, uint32_t id);    // 0x00caa360 (ret 8)
    void F_ca04a0();                           // 0x00ca04a0
    void F_ca80e0(int v);                      // 0x00ca80e0 (ret 4)
    bool F_c9ef20();                           // 0x00c9ef20
    void F_c9ef60(int v);                      // 0x00c9ef60 (ret 4)
};

extern uint32_t kTblPurposeA[];                // 0x01474ed8, indexed by mPurpose
extern uint32_t kTblPurposeB[];                // 0x01474ee4
extern uint32_t kTblPurposeC[];                // 0x01474ef0
extern uint32_t kTblPurposeD[];                // 0x01474efc
extern char     kGameModeA;                    // 0x01654c10
extern char     kGameModeB;                    // 0x01654c04
extern void*    GetCurrentGameMode();          // 0x00b5b800
extern GameDataV* CastToCombatant(GameDataRef* r);   // 0x00c0c320, cdecl
extern void*    Matrix3FromFacingAndUp(Mat3* dst, const Vec3* facing, const Vec3* up);   // 0x0069b440
extern Vec3*    normalized_safe(Vec3* dst, const Vec3* src);   // 0x00449c20
extern void     E3c7c0(uint32_t id, int ptr, const void* key, Vec3* pos, uint32_t civ, int a, int b);   // 0x00e3c7c0, cdecl

struct CombatantV {                            // cCombatant sub-object
    virtual void s0(); virtual void s1(); virtual void s2();
    virtual GameDataV* ToGameData();           // 0xc
    virtual uint32_t GetPoliticalID();         // 0x10
    virtual void s5();
    virtual void TakeDamage(float damage, uint32_t id, int type, const Vec3& dir, CombatantV* attacker);   // 0x18
    char pad1[0x2c - 4];
    float mMaxHealth;                          // +0x2c
    int   pad30;
    int   mDamageState;                        // +0x34
    float mHealth;                             // +0x38
    char pad2[0x5e8 - 0x3c];
    IdleOwner* mpIdleOwner;                    // +0x5e8
    char pad3[0x614 - 0x5ec];
    int mLocomotion;                           // +0x614
    int mPurpose;                              // +0x618
    char pad4[0x6c7 - 0x61c];
    bool mFlag6c7;                             // +0x6c7
    char pad5;
    bool mFlag6c9;                             // +0x6c9
    char pad6[0x6d0 - 0x6ca];
    TimerV mTimer6d0;                          // +0x6d0
    char pad7[0x710 - 0x6f0];
    TimerV mTimer710;                          // +0x710
    char pad8[0x800 - 0x730];
    struct TrailObj* mpTrail;                  // +0x800
    int mTrailArg;                             // +0x804

    VehV* Veh() { return (VehV*)((char*)this - 0x508); }
    int  GetDamageState();                     // 0x008e7f80 (returns [this+0x34])
    void TakeHit(float damage, uint32_t id, int type, const Vec3& dir, CombatantV* attacker);   // 0x00bfcdd0
    void F_bfc640(int ms);                     // 0x00bfc640 (ret 4)
    float F_bfc490();                          // 0x00bfc490
};
struct TrailObj { void Release(int v); };      // 0x00ff1ff0 (ret 4)
struct AbandonVisualizer { void MakeCitizensAbandonVehicle(VehV* v); };   // 0x00d5d360 (ret 4)
struct AbandonOwner { char pad[0xbc]; AbandonVisualizer* mpVis; };
extern AbandonOwner* GetAbandonOwner();        // 0x00b3d480

// @ 0x00cab550
void CombatantV::TakeDamage(float damage, uint32_t id, int type, const Vec3& dir, CombatantV* attacker)
{
    int prev;
    CivV* civB;
    VehV* veh = (VehV*)((char*)this - 0x508);
    if (veh->IsDestroyed()) return;
    if (GetDamageState() == 2) return;

    if (GetCurrentGameMode() == &kGameModeA) {
        prev = GetDamageState();
        TakeHit(damage, id, type, dir, attacker);
        if (attacker != 0) {
            IdleAnim* anim = mpIdleOwner->host.PlayIdleAnimation(0x10000, 0);
            if (anim != 0) {
                CombatantV* cur = (CombatantV*)CastToCombatant(&anim->mSource);
                if (cur != 0 && cur != attacker && cur->GetDamageState() != 2 &&
                    !((VehV*)cur->ToGameData())->IsDestroyed()) {
                    // current source is still alive: keep it
                } else {
                    anim->mSource.Assign(attacker->ToGameData());
                    anim->mDuration = 10.0f;
                }
            } else {
                IdleAnim* a = mpIdleOwner->host.StartIdle(0x10000, 0, 10.0f, attacker->ToGameData());
                if (a != 0) a->mDamage = damage;
            }
        }
        if (GetDamageState() == 2 && prev != 2) {
            if (GetCurrentGameMode() == &kGameModeA) veh->F_ca04a0();
            veh->DestroyVehicle(true, id);
        }
        return;
    }

    CivV* civA = GetNounMgr()->GetCivByPoliticalID(id);
    civB = GetNounMgr()->GetCivByPoliticalID(veh->GetPoliticalID());

    if (type == 0xf) {
        if (civA != civB) return;
        GetTicker()->Notify(kTblPurposeD[mPurpose]);
        veh->F_c9ef60(RoundToInt(damage * 1000.0f));
        return;
    }
    if (veh->F_c9ef20()) damage = 0.0f;
    if (type == 0xe) {
        GetTicker()->Notify(kTblPurposeC[mPurpose]);
        F_bfc640(RoundToInt(damage * 1000.0f));
        return;
    }
    if (type == 4) {
        if (civA != civB) {
            GetTicker()->Notify(kTblPurposeB[mPurpose]);
            IdleAnim* anim = mpIdleOwner->host.PlayIdleAnimation(0x2000, 0);
            if (anim == 0 || damage > anim->mDuration)
                mpIdleOwner->host.StartIdle(0x2000, 0, damage, 0);
        }
    } else if (type != 0xc && type != 10 && type != 0x10 && civA != 0) {
        LocoV* loco = (LocoV*)((char*)this - 0x4d4);
        CityV* city = GetPlanetModel()->FindCity(loco->GetPosition());
        if ((city == 0 || city->GetCivilization() != civA) && GetCurrentGameMode() == &kGameModeB) {
            if (type == 3)
                GetRelationshipManager()->RecordFoughtEnemyEvent(
                    civB->GetPoliticalID(), civA->GetPoliticalID(), 0x526e504u, 1.0f);
            else
                GetRelationshipManager()->RecordFoughtEnemyEvent(
                    civB->GetPoliticalID(), civA->GetPoliticalID(), 0x526e501u, 1.0f);
            if (civA == GetNounMgr()->GetPlayerCivilization()) {
                bool skip = false;
                if (mTimer710.IsRunning()) {
                    uint64_t t = mTimer710.GetElapsedTime();
                    if (t <= 5000) skip = true;
                }
                if (!skip) {
                    if (loco->IsOnView()) {
                        EffectRef eff;
                        eff.mp = 0;
                        if (GetEffectsManager()->CreateEffect(0xbe84009d, 0, eff.AsPPTypeParam())) {
                            XformMsg msg;
                            Vec3 epos;
                            float scale = loco->GetLocalExtents()[5] + 0.2f;
                            {
                                Vec3 nrm;
                                Vec3* n = normalized_safe(&nrm, loco->GetPosition());
                                Vec3 off;
                                off.x = n->x * scale;
                                off.y = n->y * scale;
                                off.z = n->z * scale;
                                const Vec3* p = loco->GetPosition();
                                epos.x = off.x + p->x;
                                epos.y = p->y + off.y;
                                epos.z = p->z + off.z;
                            }
                            msg.mFlags |= 4;
                            msg.mCount = (uint16_t)(msg.mCount + 1);
                            msg.mPos = epos;
                            {
                                Vec3 dirTmp;
                                Mat3 mtmp;
                                const Mat3* m = (const Mat3*)Matrix3FromFacingAndUp(&mtmp, loco->GetDirection(&dirTmp), loco->GetPosition());
                                msg.mMat = *m;
                            }
                            msg.mFlags |= 2;
                            msg.mCount = (uint16_t)(msg.mCount + 1);
                            msg.mCount = (uint16_t)(msg.mCount + 1);
                            msg.mScale = 4.0f;
                            eff.mp->Send(&msg);
                            eff.mp->Stop(0);
                        }
                        if (eff.mp != 0) eff.mp->Release();
                    }
                    mTimer710.Restart();
                }
            }
        }
        if (type == 3 && veh->GetPoliticalID() != id) {
            if (!mFlag6c9) {
                mFlag6c9 = true;
                veh->F_ca80e0(0x18);
            }
            mTimer6d0.Restart();
        }
    }

    int prevState = GetDamageState();
    bool destroyFlag;
    int hitType;
    if (type == 10) {
        if (veh->GetPoliticalID() != id) return;
        if (damage > 0.0f && mMaxHealth > mHealth) {
            GetTicker()->Notify(kTblPurposeA[mPurpose]);
            SpawnMgrV* sm = GetSpawnMgr();
            LocoV* loco = (LocoV*)((char*)this - 0x4d4);
            float bx[6];
            const float* b = loco->GetWorldExtents(bx);
            Vec3 ctr;
            ctr.x = (b[0] + b[3]) * 0.5f;
            ctr.y = (b[4] + b[1]) * 0.5f;
            ctr.z = (b[5] + b[2]) * 0.5f;
            Vec3 d;
            sm->SpawnEffect(0x498da10, &ctr, loco->GetDirection(&d));
        }
        destroyFlag = true;
        hitType = type;
    } else if (type == 3 || type == 4) {
        destroyFlag = false;
        hitType = 1;
    } else {
        destroyFlag = true;
        hitType = type;
    }
    TakeHit(damage, id, hitType, dir, 0);

    if (!mFlag6c7 && F_bfc490() <= 0.0f) {
        mFlag6c7 = true;
        AbandonOwner* o = GetAbandonOwner();
        if (o != 0) o->mpVis->MakeCitizensAbandonVehicle(Veh());
    }

    if (GetDamageState() != 2) return;
    if (prevState == 2) return;

    if (GetPoliticalID() == (uint32_t)GetNounMgr()->GetPlayerEmpireOrMinus1()) {
        LocoV* loco = (LocoV*)((char*)this - 0x4d4);
        switch (mLocomotion) {
        case 0: {
            uint32_t z[3] = { 0, 0, 0 };
            E3c7c0(0xdc72339b, GetNounMgr()->GetPlayerCivilization()->F_bef950() + 0x504, loco->GetModelKey(), (Vec3*)z, GetNounMgr()->GetPlayerCivilization()->mField40, 0, 0);
            break;
        }
        case 1: {
            uint32_t z[3] = { 0, 0, 0 };
            E3c7c0(0xeae0f265, GetNounMgr()->GetPlayerCivilization()->F_bef950() + 0x504, loco->GetModelKey(), (Vec3*)z, GetNounMgr()->GetPlayerCivilization()->mField40, 0, 0);
            break;
        }
        case 2: {
            uint32_t z[3] = { 0, 0, 0 };
            E3c7c0(0xd5296db2, GetNounMgr()->GetPlayerCivilization()->F_bef950() + 0x504, loco->GetModelKey(), (Vec3*)z, GetNounMgr()->GetPlayerCivilization()->mField40, 0, 0);
            break;
        }
        }
    }

    VehV* dv = Veh();
    dv->DestroyVehicle(destroyFlag, id);
    void* agent = 0;
    if (dv != 0) agent = (char*)this + 0xc8;
    GetBehaviorMgr()->Remove(agent);
    civB->RemoveVehicle(dv);
    if (mpTrail != 0) {
        mpTrail->Release(mTrailArg);
        mTrailArg = 0;
    }
}
