// Slice s00c19b60: 0x00C1A3C0, the cCombatant::TakeDamage override of Simulator::cCreatureBase
// (the cCombatant sub-object sits at cCreatureBase+0x5a8; ModAPI cCombatant vslot 0x18
//  TakeDamage(float damage, uint32 attackerPoliticalID, int damageType, const Vector3& dir,
//  cCombatant* attacker), ret 0x14; the method name is the ModAPI one).
//
// What it does:
//   1. ignores the hit when the creature reports "invulnerable"(vslot 0x2c of the game-data
//      sub-object), when the combatant flag bit 9 is set in the civ-stage, or when the creature
//      is a locomotive that a game-state object (mode 1 or 2) protects;
//   2. in the civ stage (mode 0x1654c05) a player attacker one-shots (damage = 10000) unless the
//      creature's pointer at +0x8dc has its byte +0x388 set;
//   3. in the creature stage (mode 0x1654c10, damage type != 7) runs the four creature-ability
//      damage modifiers (each: profile count at +0x578 nonzero, modifier returns a reduced damage;
//      if it reduced it and the cooldown at +0x9d8 passed the global threshold, queue an effect
//      reference on the list at +0x9dc) and resets the cooldown if any fired;
//   4. calls cCombatant::TakeHit; when the creature is then dead (damage state 2) it clears flag
//      0x1000, posts the death effects (damage types 0/1 send effect 0x1b55d9a/b with the negated
//      hit direction) and, outside some modes, calls vslot 0xc8 of the game-data sub-object;
//   5. for damage type 0 (not in the creature stage, no +0x8dc override) it applies a knock-back
//      impulse to the locomotive sub-object and switches the creature state (-0x2f8) to 3.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-
#include "types.h"

typedef unsigned int size_t;
inline void* operator new(size_t, void* p) { return p; }
void* operator new(size_t size, const char* name, int flags, unsigned debugFlags,
                   const char* file, int line);                          // 0x00f473a0

struct Vector3 { float x, y, z; };

struct RefObj {
    virtual int AddRef();       // 0x00
    virtual int Release();      // 0x04
};

template <class T> struct AutoRefCount {
    T* mpObject;
    AutoRefCount(T* p);                                                  // 0x00572660 (ret 4)
    __forceinline AutoRefCount(const AutoRefCount& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
    __forceinline ~AutoRefCount() { if (mpObject) mpObject->Release(); }
};
typedef AutoRefCount<RefObj> ObjRef;

struct ListNode {
    ListNode* mpNext;
    ListNode* mpPrev;
    ObjRef    mValue;
};
struct ListAnchor {
    ListNode* mpNext;
    ListNode* mpPrev;
};

// sub-object at this-0x5a8 (cGameData side)
struct CBase {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual bool IsProtected();                 // 0x2c
    uint8_t pad[0x4];
    void FUN_00c19940(int a);                   // 0x00c19940 (ret 4)
    uint8_t pad8[0xe84 - 8];
    uint8_t* mpOverride;                        // +0xe84
};
struct CBaseV : CBase {
};

// sub-object at this-0x4e8 (cLocomotiveObject side)
struct CLoco {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual const Vector3* GetVector();         // 0x2c
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54();
    virtual bool IsLocomotive();                // 0x58
    void FUN_00c41d60(const Vector3* v);        // 0x00c41d60 (ret 4)
    void FUN_00c446d0(const Vector3* v, int a); // 0x00c446d0 (ret 8)
};

struct CTypeObj { virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
                  virtual void v10(); virtual void v14(); virtual void v18();
                  virtual int GetType(); };     // 0x1c
// sub-object at this-0x550 (cBehaviorAgent side)
struct CAgent {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual CTypeObj* GetTypeObj();             // 0x20
};

struct CManager {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void Post(uint32_t id, void* data, const Vector3* v);   // 0x60
};
CManager* FUN_00b3d240();                                    // 0x00b3d240 (cdecl)
struct StateObj { uint8_t pad[0x2c]; int mState; };
StateObj* FUN_00b3d4d0();                                    // 0x00b3d4d0 (cdecl)
void* StarManager();                                         // 0x00b3d2a0 (cdecl)
bool FUN_00ba6650(uint32_t id);                              // 0x00ba6650 (cdecl)
uint32_t GetCurrentGameMode();                               // 0x00b5b800 (cdecl)
int FUN_00ac80d0(CBase* b, uint32_t id);                     // 0x00ac80d0 (cdecl)
void Vector3_Normalize(Vector3* out, const Vector3* in);     // 0x00436ce0 (cdecl)
RefObj* FUN_00c11690(uint32_t id, CBase* b, void* attacker); // 0x00c11690 (cdecl)
float FUN_00c0db80(float damage, CBase* b);                  // 0x00c0db80 (cdecl)
float FUN_00c161f0(float damage, CBase* b);                  // 0x00c161f0 (cdecl)
float FUN_00c16340(float damage, CBase* b);                  // 0x00c16340 (cdecl)
float FUN_00c0dcb0(float damage, CBase* b);                  // 0x00c0dcb0 (cdecl)
extern uint32_t g_CooldownThreshold;                         // 0x015716d4

struct Profile {
    uint8_t  pad[0x648];
    int      mCount648;
    uint8_t  pad64c[0x660 - 0x64c];
    uint32_t mCount660;
    uint32_t mCount664;
    uint32_t mCount668;
};

class cCreatureCombatant {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64();

    uint32_t pad04;             // (the vptr is 8 bytes wide: cGonzagoTimer alignment)
    uint32_t mFlags8;           // +0x08 (bit 9 tested)
    uint8_t  pad0c[0x578 - 0xc];
    Profile* mpProfile;         // +0x578
    uint8_t  pad57c[0x8dc - 0x57c];
    uint8_t* mpOverride;        // +0x8dc (byte +0x388)
    uint8_t  pad8e0[0x9d8 - 0x8e0];
    uint32_t mCooldown;         // +0x9d8
    ListAnchor mEffects;        // +0x9dc

    int  GetDamageState();                                                        // 0x008e7f80
    void TakeHit(float damage, uint32_t pid, int type, const Vector3& dir, void* attacker);  // 0x00bfcdd0

    CBase*  Base()  { return (CBase*)((char*)this - 0x5a8); }
    CLoco*  Loco()  { return (CLoco*)((char*)this - 0x4e8); }
    CAgent* Agent() { return (CAgent*)((char*)this - 0x550); }

    void TakeDamage(float damage, uint32_t attackerPID, int damageType, const Vector3& dir, void* attacker);   // 0x00c1a3c0
};

static __forceinline bool GetBit(uint32_t v, int n) { return ((v >> n) & 1) != 0; }

static __forceinline void PushEffect(ListAnchor* list, RefObj* obj)
{
    ObjRef tmp(obj);
    ListNode* n = (ListNode*)operator new(sizeof(ListNode), "Simulator", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
        0xd1);
    ::new ((void*)&n->mValue) ObjRef(tmp);
    n->mpNext = (ListNode*)list;
    n->mpPrev = list->mpPrev;
    list->mpPrev->mpNext = n;
    list->mpPrev = n;
}

// @ 0x00c1a3c0
void cCreatureCombatant::TakeDamage(float damage, uint32_t attackerPID, int damageType, const Vector3& dir, void* attacker)
{
    Vector3 tmp;
    CBase* base = Base();
    if (base->IsProtected())
        return;
    if (GetBit(mFlags8, 9) && GetCurrentGameMode() == 0x1654c05)
        return;

    CLoco* loco = Loco();
    if (loco->IsLocomotive()) {
        int s = FUN_00b3d4d0()->mState;
        if (s == 1 || s == 2)
            return;
    }

    if (GetCurrentGameMode() == 0x1654c05) {
        StarManager();
        if (FUN_00ba6650(attackerPID) && (base->mpOverride == 0 || base->mpOverride[0x388] == 0))
            damage = 10000.0f;
    }

    if (GetCurrentGameMode() == 0x1654c10 && damageType != 7) {
        bool fired = false;
        if (mpProfile->mCount668 > 0) {
            float r = FUN_00c0db80(damage, base);
            if (r < damage && mCooldown > g_CooldownThreshold) {
                RefObj* o = FUN_00c11690(0xf7a8a2b1, base, attacker);
                if (o)
                    PushEffect(&mEffects, o);
                fired = true;
            }
            damage = r;
        }
        if (mpProfile->mCount648 > 0) {
            float r = FUN_00c161f0(damage, base);
            if (r < damage && mCooldown > g_CooldownThreshold) {
                RefObj* o = FUN_00c11690(0x924bae45, base, attacker);
                if (o)
                    PushEffect(&mEffects, o);
                fired = true;
            }
            damage = r;
        }
        if (mpProfile->mCount664 > 0) {
            float r = FUN_00c16340(damage, base);
            if (r < damage && mCooldown > g_CooldownThreshold) {
                RefObj* o = FUN_00c11690(0xb9716d18, base, attacker);
                if (o)
                    PushEffect(&mEffects, o);
                fired = true;
            }
            damage = r;
        }
        if (mpProfile->mCount660 > 0) {
            float r = FUN_00c0dcb0(damage, base);
            if (r < damage && mCooldown > g_CooldownThreshold) {
                RefObj* o = FUN_00c11690(0x4c1b2351, base, attacker);
                if (o)
                    PushEffect(&mEffects, o);
                fired = true;
            }
            damage = r;
        }
        if (fired)
            mCooldown = 0;
    }

    TakeHit(damage, attackerPID, damageType, dir, attacker);

    if (GetDamageState() == 2) {
        mFlags8 &= 0xffffefff;
        if (GetCurrentGameMode() == 0x1654c10)
            base->FUN_00c19940(0);
        CAgent* agent = Agent();
        bool skip = false;
        if (agent->GetTypeObj() != 0 && agent->GetTypeObj()->GetType() == 0x3cdbbe9)
            skip = true;
        if (skip || (damageType != 0 && damageType != 1)) {
            if (GetCurrentGameMode() != 0x1654c01 && GetCurrentGameMode() != 0x1654c02 &&
                FUN_00ac80d0(base, 0x18eb45e) == 0 && GetCurrentGameMode() != 0x1654c04)
                ((void (__thiscall*)(CBase*, int))(*(void***)base)[0xc8 / 4])(base, 0);
        } else if (damageType == 0) {
            tmp.x = -dir.x; tmp.y = -dir.y; tmp.z = -dir.z;
            FUN_00b3d240()->Post(0x1b55d9a, (void*)loco->GetVector(), &tmp);
        } else {
            tmp.x = -dir.x; tmp.y = -dir.y; tmp.z = -dir.z;
            FUN_00b3d240()->Post(0x1b55d9b, (void*)loco->GetVector(), &tmp);
            return;
        }
    }
    if (damageType != 0)
        return;
    if ((mpOverride == 0 || mpOverride[0x388] == 0) && GetCurrentGameMode() != 0x1654c10) {
        Vector3_Normalize(&tmp, loco->GetVector());
        const float k2 = 2.0f;
        const float tx = tmp.x * k2, ty = tmp.y * k2, tz = tmp.z * k2;
        tmp.x = (tx + dir.x) * 4.0f; tmp.y = (ty + dir.y) * 4.0f; tmp.z = (tz + dir.z) * 4.0f;
        loco->FUN_00c41d60(&tmp);
        tmp.x = tx + dir.x; tmp.y = ty + dir.y; tmp.z = tz + dir.z;
        loco->FUN_00c446d0(&tmp, 0);
        *(int*)((char*)this - 0x2f8) = 3;
    }
}
