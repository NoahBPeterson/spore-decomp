// Slice s00bcf6f0: cBuilding's cCombatant::TakeDamage override (0x00bcf6f0).
// `this` is the cCombatant subobject at cBuilding + 0x120, the cSpatialObject subobject is at +0x34.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

typedef unsigned int uint;
typedef unsigned long long uint64;

struct Vector3 { float x, y, z; };
struct Matrix3 { float m[9]; };
struct BBox { Vector3 lo, hi; };

struct XformMsg {                        // 0x38 bytes; ctor 0x00434040
    uint16_t flags;                      // |4 position, |2 matrix
    int16_t count;
    Vector3 pos;
    float scale;
    Matrix3 rot;
    XformMsg();
    void SetPos(const Vector3& v) { pos = v; flags |= 4; ++count; }
    void SetRot(const Matrix3& m) { rot = m; flags |= 2; ++count; }
    void SetScale(float s)        { scale = s; ++count; }
};

struct IEffect {                         // EA::Swarm::cIVisualEffect (slots used here)
    virtual void v00();
    virtual void Release();              // 0x04
    virtual void Start(int flag);        // 0x08
    virtual void Stop(int flag);         // 0x0c
    virtual bool IsPlaying();            // 0x10
    virtual void v14();
    virtual void SetTransform(XformMsg* xf);   // 0x18
};
struct EffectRef {                       // EA::AutoRefCount<cIVisualEffect>
    IEffect* p;
    IEffect** AsPPTypeParam();           // 0x00a16f40
    ~EffectRef() { if (p) p->Release(); }
};
struct EffectsMgr {
    virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0c();
    virtual void s10(); virtual void s14(); virtual void s18(); virtual void s1c();
    virtual void s20(); virtual void s24(); virtual void s28();
    virtual bool CreateEffect(uint id, int unused, IEffect** out);   // 0x2c
};
EffectsMgr* __cdecl EffectsManager();                                // 0x0067ddd0

struct Timer {                           // SP::cSPTimer
    char d[0x20];
    void Restart();                      // 0x00bc3130
    bool IsRunning();                    // 0x00feba90
    uint64 GetElapsedTime();             // 0x00bc3190
};

struct Civ { char pad[0x4b8]; int mCounter; };

struct City {
    virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0c();
    virtual void s10(); virtual void s14(); virtual void s18(); virtual void s1c();
    virtual void s20(); virtual void s24(); virtual void s28(); virtual void s2c();
    virtual void s30(); virtual void s34(); virtual void s38(); virtual void s3c();
    virtual void s40(); virtual void s44(); virtual void s48();
    virtual unsigned GetPoliticalID();   // 0x4c
    char pad[0x230 - 4];
    Timer mTimer230;                     // +0x230
    char pad2[0x748 - 0x250];
    float mField748;
    int   mField74c;
    Civ* GetCivilization();              // 0x00bd9bf0
    void F00bd8300(int amount);          // 0x00bd8300 (ret 4)
    void F00bdbf10();   // 0x00bdbf10
    bool F00bd9d20();   // 0x00bd9d20
    int  F00bd81f0();   // 0x00bd81f0
    int  F00bd9bb0();   // 0x00bd9bb0
    void F00c00b00(int a, int b);        // 0x00c00b00 (ret 8)
    void F00be2bb0(float damage, int empire);   // 0x00be2bb0 (ret 8)
};

struct Planet { int F00c70e00(); };   // 0x00c70e00
struct PlanetRec;
struct ShipInfo { char pad[0x714]; int mKind; };

struct Combatant {
    virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0c();
    virtual void s10(); virtual void s14(); virtual void s18(); virtual void s1c();
    virtual void s20(); virtual void s24(); virtual void s28(); virtual void s2c();
    virtual void s30(); virtual void s34(); virtual void s38(); virtual void s3c();
    virtual void s40(); virtual void s44(); virtual void s48(); virtual void s4c();
    virtual void s50(); virtual void s54(); virtual void s58();
    virtual void* Cast(uint typeId);     // 0x5c
};

struct Inventory { char pad[0x508]; };
struct UFOSim {
    Inventory* GetPlayerInventory();     // 0x00a1ad60
    void F00ffd830(City* city);          // 0x00ffd830 (ret 4)
};

struct Tuning {
    float F0102a4f0();   // 0x0102a4f0
    float F0102a540();   // 0x0102a540
    float GetCityCaptureFactor();        // 0x01029be0
};

struct RelMgr { float RecordFoughtEnemyEvent(uint pid, uint att, uint ev, float w); };   // 0x00d06270, ret 0x10
struct NounMgr { int F00b1f9d0(); };                                                      // 0x00b1f9d0 player empire or -1

namespace SP {
unsigned __cdecl GetCurrentGameMode();                         // 0x00b5b800
int __cdecl GetPlayerEmpireID();                               // 0x01021090 (cSPLivingUniverse)
Planet* __cdecl GetActivePlanet();                             // 0x01021260
PlanetRec* __cdecl GetActivePlanetRecord();                    // 0x010212a0
Tuning* __cdecl GetSpaceCombatTuning();                        // 0x01029940
UFOSim* __cdecl GetUFOSimulator();                             // 0x00ffbe50
RelMgr* __cdecl RelationshipManager();                         // 0x00b3d2c0
NounMgr* __cdecl NounManager();                                // 0x00b3d300
Vector3 __cdecl normalized_safe(const Vector3& v);             // 0x00449c20
const Matrix3* __cdecl Matrix3FromFacingAndUp(Matrix3* out, const Vector3* facing, const Vector3* up);   // 0x0069b440
}
ShipInfo* __cdecl F00ae3370(Combatant* c);                     // 0x00ae3370
bool __cdecl F01029a10(int empire, PlanetRec* rec);            // 0x01029a10
struct Flag44 { char pad[0x44]; bool mFlag; };
Flag44* __cdecl F01021230();                                   // 0x01021230
void __cdecl F00be9b20(PlanetRec* rec, City* city, int a, uint ownerID, float damage, int attacker, bool b);   // 0x00be9b20

struct Building {
    void F00bcd690(int a, int type);   // 0x00bcd690 (ret 8)
    virtual void s00();
    virtual void s04();
    virtual void s08();
    virtual void s0c();
    virtual void s10();
    virtual void s14();
    virtual void s18();
    virtual void s1c();
    virtual void s20();
    virtual void s24();
    virtual void s28();
    virtual bool IsDestroyed();                 // 0x2c
    virtual void s30();
    virtual void s34();
    virtual void s38();
    virtual void s3c();
    virtual void s40();
    virtual void s44();
    virtual void s48();
    virtual unsigned GetPoliticalID();            // 0x4c
    virtual void s50();
    virtual void s54();
    virtual void s58();
    virtual void s5c();
    virtual void s60();
    virtual void s64();
    virtual void s68();
    virtual void s6c();
    virtual void s70();
    virtual void s74();
    virtual void s78();
    virtual void s7c();
    virtual void s80();
    virtual City* GetOwnerCity();                  // 0x84
};

struct Spatial {
    virtual void s00();
    virtual void s04();
    virtual void s08();
    virtual void s0c();
    virtual void s10();
    virtual void s14();
    virtual void s18();
    virtual void s1c();
    virtual void s20();
    virtual void s24();
    virtual void s28();
    virtual const Vector3& GetPosition();         // 0x2c
    virtual void s30();
    virtual void s34();
    virtual void s38();
    virtual void s3c();
    virtual void s40();
    virtual void s44();
    virtual bool IsOnView();                       // 0x48
    virtual void s4c();
    virtual void s50();
    virtual void s54();
    virtual void s58();
    virtual Vector3 GetDirection();               // 0x5c
    virtual void s60();
    virtual void s64();
    virtual const BBox& GetLocalExtents();        // 0x68
};

struct BldCombatant {
    // BldCombatant is a Combatant subobject (vptr at +0); only the offsets the function needs are modelled.
    virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0c();
    virtual void s10(); virtual void s14();
    virtual void TakeDamage(float damage, uint attackerID, int damageType, const Vector3& pos, Combatant* src);   // 0x18
    char pad[0x238 - 0x20];
    Timer mAttackTimer;                  // +0x238
    void TakeDamageBase(float damage, uint attackerID, int damageType, const Vector3& pos, Combatant* src);   // 0x00bcece0 (ret 0x14)
    void SpawnTurretHitEffect();
};

// Effect 0xa14e0379 on the building's spatial object (destruction type 0x10).
// @ 0x00bcf6f0
void BldCombatant::TakeDamage(float damage, uint att, int type, const Vector3& v, Combatant* src)
{
    Building* b = (Building*)((char*)this - 0x120);
    Spatial* sp = (Spatial*)((char*)this - 0xec);
    if (b->IsDestroyed())
        return;

    bool flag;
    if (type == 0xc || type == 0xa || type == 0x10 || type == 4) {
        flag = false;
    } else {
        flag = true;
        if (type == 0xf)
            flag = false;
    }

    if (type == 0xb) {
        b->GetOwnerCity()->mTimer230.Restart();
        return;
    }
    if (type == 0xc) {
        if ((int)att != (int)b->GetPoliticalID()) {
            b->GetOwnerCity()->F00be2bb0(damage, att);
            return;
        }
    } else if (type == 0x10) {
        IEffect* eff = 0;
        EffectsMgr* mgr = EffectsManager();
        if (eff) {
            IEffect* o = eff;
            eff = 0;
            o->Release();
        }
        if (mgr->CreateEffect(0xa14e0379, 0, &eff)) {
            XformMsg msg;
            float h = sp->GetLocalExtents().hi.z + 0.2f;
            Vector3 n = SP::normalized_safe(sp->GetPosition());
            Vector3 off;
            off.x = h * n.x;
            off.y = n.y * h;
            off.z = n.z * h;
            const Vector3& p0 = sp->GetPosition();
            Vector3 p;
            p.x = p0.x + off.x;
            p.y = p0.y + off.y;
            p.z = p0.z + off.z;
            msg.SetPos(p);
            Matrix3 m0;
            Vector3 dir = sp->GetDirection();
            msg.SetRot(*SP::Matrix3FromFacingAndUp(&m0, &dir, &sp->GetPosition()));
            msg.SetScale(4.0f);
            eff->SetTransform(&msg);
            eff->Start(0);
        }
        int dmg = (int)damage;
        b->GetOwnerCity()->F00bd8300(dmg);
        b->GetOwnerCity()->GetCivilization()->mCounter += dmg;
        if (eff)
            eff->Release();
        return;
    }

    if (src && src->Cast(0x436f315))
        return;
    if (SP::GetCurrentGameMode() == 0x1654c05) {
        ShipInfo* si = F00ae3370(src);
        if (si && si->mKind == 3)
            att = SP::GetPlayerEmpireID();
    }
    if (!flag)
        goto base;

    if (att == (uint)SP::GetPlayerEmpireID())
        b->GetOwnerCity()->F00bdbf10();

    if (SP::GetCurrentGameMode() == 0x1654c05) {
        Inventory* inv = SP::GetUFOSimulator()->GetPlayerInventory();
        Combatant* pc = inv ? (Combatant*)((char*)inv + 0x508) : 0;
        if (src == pc) {
            if ((int)b->GetPoliticalID() != SP::GetPlayerEmpireID())
                SP::GetUFOSimulator()->F00ffd830(b->GetOwnerCity());
        }
    }

    if (SP::GetCurrentGameMode() == 0x1654c05) {
        if (SP::GetActivePlanet()->F00c70e00() != 4 || (int)att == SP::GetPlayerEmpireID()) {
            City* city = b->GetOwnerCity();
            int player = SP::GetPlayerEmpireID();
            if (SP::GetCurrentGameMode() == 0x1654c05 && SP::GetActivePlanet()->F00c70e00() == 4 && (int)att == player)
                goto base;
            if (city->mField74c == (int)att && !(city->mField748 < 100.0f))
                goto base;
            if (!F01029a10(att, SP::GetActivePlanetRecord()))
                goto base;
            bool inRange;
            if ((int)b->GetPoliticalID() == player) {
                inRange = ((int)att == player);
            } else {
                if ((int)att != player)
                    goto capture;
                inRange = !F01021230()->mFlag;
            }
            if (inRange)
                goto base;
        capture:
            float n = (float)city->F00bd9bb0() * 0.083333336f;
            float lo = SP::GetSpaceCombatTuning()->F0102a4f0();
            float hi = SP::GetSpaceCombatTuning()->F0102a540();
            float t = (hi - lo) * n + lo;
            city->F00c00b00(0, att);
            F00be9b20(SP::GetActivePlanetRecord(), city, city->F00bd81f0(), city->GetPoliticalID(),
                      SP::GetSpaceCombatTuning()->GetCityCaptureFactor() * t * damage, att, false);
            return;
        }
    }

    if ((int)att != -1 && SP::GetCurrentGameMode() == 0x1654c04 && 0.0f < damage
        && (int)b->GetPoliticalID() != (int)att) {
        SP::RelationshipManager()->RecordFoughtEnemyEvent(b->GetPoliticalID(), att, 0x526e501, 1.0f);
        if ((int)att == SP::NounManager()->F00b1f9d0()) {
            Timer* t = &mAttackTimer;
            bool skip = false;
            if (t->IsRunning()) {
                uint64 el = t->GetElapsedTime();
                if (el <= 0x1388)
                    skip = true;
            }
            if (!skip && sp->IsOnView()) {
                EffectRef ref;
                ref.p = 0;
                if (EffectsManager()->CreateEffect(0x69a49c25, 0, ref.AsPPTypeParam())) {
                    XformMsg msg;
                    float h = sp->GetLocalExtents().hi.z + 2.0f;
                    Vector3 n = SP::normalized_safe(sp->GetPosition());
                    Vector3 off;
                    off.x = n.x * h;
                    off.y = n.y * h;
                    off.z = n.z * h;
                    const Vector3& p0 = sp->GetPosition();
                    Vector3 p;
                    p.x = p0.x + off.x;
                    p.y = p0.y + off.y;
                    p.z = p0.z + off.z;
                    msg.SetPos(p);
                    Matrix3 m0;
                    Vector3 dir = sp->GetDirection();
                    msg.SetRot(*SP::Matrix3FromFacingAndUp(&m0, &dir, &sp->GetPosition()));
                    msg.SetScale(4.0f);
                    ref.p->SetTransform(&msg);
                    ref.p->Start(0);
                }
                t->Restart();
            }
        }
    }

    if (!b->GetOwnerCity()->F00bd9d20() && type != 0xd)
        return;
    b->F00bcd690(0, type);
    F00be9b20(SP::GetActivePlanetRecord(), b->GetOwnerCity(), b->GetOwnerCity()->F00bd81f0(),
              b->GetOwnerCity()->GetPoliticalID(), damage, att, type == 0xd);
    return;
base:
    TakeDamageBase(damage, att, type, v, src);
}
