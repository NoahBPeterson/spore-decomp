// Slice s00c308b0: SP::cEmpire methods (0x00C308B0) plus small free helpers.
// Layout (retail disassembly; the object is far larger than the 2008 PDB layout):
//   +0x58  dword  archetype / terrain-picker mode
//   +0x84  uint   empire id
//   +0x88  ptr    begin of eastl::vector<cCivData*> (star / city list)
//   +0x8c  ptr    end   of that vector
//   +0xb0  int    UFOKey group / HomePlanet star id (-1 = none)
//   +0xb4  int    empire money / HomePlanet planet id (-1 = none)
//   +0xb8  ...    resource key block
//   +0xc4..+0xcc  three floats (position)
//   +0xd8  int    weaponry level       (lazy, <0 = unset)
//   +0xe0  float  background fighter DPS (lazy, <=0 = unset)
//   +0xe4  float  background bomber  DPS
//   +0xe8  float  background turret  DPS
//   +0xf0  float* UFO health array
//   +0x104 ptr    AutoRefCount<UTFWinControls::IWinText>
//   +0x128 cSPTimer (relationship timer)
// Callees are masked relocations: declarations only need the right calling convention and
// argument sizes (arity taken from each callee's `ret N`).
// Flags: /O2 /MD /Gy /TP /arch:SSE.
#include "types.h"
#include <math.h>

typedef unsigned int uint;

struct Vec3 { float x, y, z; };

// ---- collaborators ---------------------------------------------------------------------------------
struct Obj;

// Managers / helpers returning a manager (cdecl, no args).
struct MsgObj;
Obj* __cdecl SP_NounManager();                       // 0x00b3d300
Obj* __cdecl SP_StarManager();                       // 0x00b3d2a0
Obj* __cdecl SP_RelationshipManager();               // 0x00b3d2c0
Obj* __cdecl SP_CommManager();                       // 0x00b3d4a0
MsgObj* __cdecl SP_MessageServer();                  // 0x0067dcc0
Obj* __cdecl EA_ResourceMan_GetManager();            // 0x0067dcd0
Obj* __cdecl SP_GetSpaceRelationshipTuning();        // 0x010407c0
Obj* __cdecl SP_GetSpaceCombatTuning();              // 0x01029940
int  __cdecl SP_PlayerEmpireID();                    // 0x01021090
int  __cdecl SP_UniverseContext();                   // 0x01021080
Obj* __cdecl SP_GetAvatar();                         // 0x00b1fdb0

// Free functions (cdecl).
void* __cdecl EA_Allocate(uint size, const char* owner, int a, int b, int c, int d);  // 0x00f473a0
bool  __cdecl IO_WriteUint32(void* stream, const uint* p, int n, int mode);            // 0x0093aa70
bool  __cdecl IO_ReadInt32(void* stream, uint* p, int n, int mode);                    // 0x0093a780
void  __cdecl FUN_0102c7f0(void* p, int v);                                            // 0x0102c7f0
char  __cdecl FUN_00c70150(Obj* p, Obj* self, int b);                                  // 0x00c70150
Obj*  __cdecl SP_FUN_01021300();                                                       // 0x01021300
Obj*  __cdecl SP_FUN_01021240();                                                       // 0x01021240
int   __cdecl SP_GetCurrentGameMode();                                                 // 0x00b5b800
Obj*  __cdecl SP_GetAvatar();                                                          // 0x00b1fdb0
void  __cdecl GetPropertyAsIntArray(void* prop, int key, int* a, int* b);              // 0x006a07d0

extern const char DAT_01572b60[];   // 0x01572b60

// Stream interface helpers.
struct OutStream {
    virtual void v0(); virtual void v1(); virtual void v2();
    virtual void v3(); virtual void v4(); virtual void v5();
    virtual void* m18();                    // +0x18
};
struct IStream {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual OutStream* m20();               // +0x20
};

// The two FUN_00b6e2d0 / FUN_00b6e340 thiscall helpers (this = cEmpire+0xc).
struct cTail {
    bool m_b6e2d0(Obj* p);                  // 0x00b6e2d0 (ret 4) write
    bool m_b6e340(Obj* p);                  // 0x00b6e340 (ret 4) read
};

// The opaque collaborator object: every thiscall callee is one of its members (name m_<va>).
struct Obj {
    int   m_885c90();                       // 0x00885c90
    int   m_ba6d80(uint starID);            // 0x00ba6d80
    int   m_ba6dc0(uint starID);            // 0x00ba6dc0
    Obj*  m_bba500();                       // 0x00bba500
    Obj*  m_bba790();                       // 0x00bba790
    void  m_bb4af0(int a, int b);           // 0x00bb4af0 (ActivatePlanetRecordsForQuery, ret 8)
    Obj*  m_bb5ae0(int a);                  // 0x00bb5ae0
    Obj*  m_ce6950();                       // 0x00ce6950 cStarRecordRef::GetCommContext
    void  m_baf630(int a, int b);           // 0x00baf630 (ret 8)
    void  m_aeb3e0(int a, int b, int c, int d, int e, int f, int g, int h); // 0x00aeb3e0
    Obj*  m_b8de30();                       // 0x00b8de30
    // cTerrainEditor
    Obj*  m_f67d90();                       // 0x00f67d90 GetCurrentTerrainSphere
    bool  m_c7a710(uint id);                // 0x00c7a710 (ret 4)
    bool  m_c7a770(uint id);                // 0x00c7a770 (ret 4)
    void  m_c7a830(uint id);                // 0x00c7a830 (ret 4)
    void  m_c7bba0(uint id);                // 0x00c7bba0 (ret 4)
    void  m_c7bb80(uint id);                // 0x00c7bb80 (ret 4)
    void  m_c7bbf0(uint id, uint v);        // 0x00c7bbf0 (ret 8)
    int   m_c75420();                       // 0x00c75420
    void  m_c759a0();                       // 0x00c759a0
    // relationship manager
    bool  m_d01f20(int a, int b);           // 0x00d01f20 (ret 8)
    bool  m_d01fb0(int a, int b);           // 0x00d01fb0 (ret 8)
    float m_d01b80(int a, int b, int key);  // 0x00d01b80 (ret 0xc)
    float m_d00a10(int a, int b, int c);    // 0x00d00a10 (ret 0xc)
    // tuning
    float m_1040860();                      // 0x01040860
    float m_0097eeb0();                     // 0x0097eeb0
    float m_00fb8a00();                     // 0x00fb8a00
    int   m_102a360();                      // 0x0102a360 cSPSpaceCombatTuning::GetWeaponLevel
    float m_1029cc0(int lvl);               // 0x01029cc0 GetBackgroundFighterDPS
    float m_1029d50(int lvl);               // 0x01029d50 GetBackgroundBomberDPS
    float m_1029de0(int lvl);               // 0x01029de0 GetBackgroundTurretDPS
    float m_102a630(int idx, int lvl);      // 0x0102a630 GetUFOHealth
    // player-city music / win-text / misc
    Obj*  m_eb0ea0();                       // 0x00eb0ea0 cPlayerCityMusic ctor (returns this)
    Obj*  m_eab410(int v);                  // 0x00eab410 (ret 4)
    int   m_10107b0(int id);                // 0x010107b0 (ret 4)
    // resource manager (0x0067dcd0): vtable slot 3
    virtual void v0();
    virtual void v4();
    virtual void v8();
    virtual bool Query(void* p, int a, int b, int c, int d, int e);
};

// MessageServer (0x0067dcc0) returns an object whose vtable slot 6 is the send/notify call.
struct MsgObj {
    virtual void mv0(); virtual void mv1(); virtual void mv2();
    virtual void mv3(); virtual void mv4(); virtual void mv5();
    virtual int send(int a, int b, int c, int d);   // vtable[0x18]
};

struct cCivData;

// cCivData::GetCities (thiscall, no args)
Vec3* __fastcall cCivData_GetCities(cCivData* self);  // 0x005c65e0

// cVarListSerializer (this in ecx).
class cVarListSerializer {
public:
    cVarListSerializer(void* pOwner, const void* pKey, uint id);  // 0x00692f90 (ret 0xc)
    bool Serialize(IStream* s);                                   // 0x00692900 (ret 4)
    bool SerializeStream(IStream* s);                             // 0x00693e10 (ret 4)
};

// cSPTimer (this in ecx).
struct cSPTimer {
    uint8_t m18;                  // +0x18 running flag
    int64_t GetElapsedTime();     // 0x00bc3190
    void    Stop();               // 0x00bc3110
    void    FUN_00bc3170();       // 0x00bc3170
};

// EA::AutoRefCount<EA::UTFWinControls::IWinText>::operator= (ret 4)
struct WinTextRef {
    void** m_assign(void* value);       // 0x00b5f950 (ret 4)
};

// cSPSpaceCombatTuning (this in ecx)
struct cSpaceCombatTuning {
    uint8_t pad[8];
    Obj* mProperty;      // +0x8
};

// ---------------------------------------------------------------------------------------------------
struct cEmpire {
    uint8_t  pad00[0x58];
    uint32_t mArchetype;                 // +0x58
    uint8_t  pad5c[0x84 - 0x5c];
    uint32_t mEmpireID;                  // +0x84
    cCivData** mCitiesBegin;             // +0x88
    cCivData** mCitiesEnd;               // +0x8c
    uint8_t  pad90[0xb0 - 0x90];
    int32_t  mUFOKey;                    // +0xb0
    int32_t  mEmpireMoney;               // +0xb4
    uint8_t  padb8[0xc4 - 0xb8];
    float    mPosX;                      // +0xc4
    float    mPosY;                      // +0xc8
    float    mPosZ;                      // +0xcc
    uint8_t  padd0[0xd8 - 0xd0];
    int32_t  mWeaponryLevel;             // +0xd8
    uint8_t  paddc[0xe0 - 0xdc];
    float    mBgFighterDPS;              // +0xe0
    float    mBgBomberDPS;               // +0xe4
    float    mBgTurretDPS;               // +0xe8
    uint8_t  padec[0xf0 - 0xec];
    float*   mUFOHealth;                 // +0xf0
    uint8_t  padf4[0x104 - 0xf4];
    void*    mMusic;                     // +0x104
    uint8_t  pad108[0x128 - 0x108];
    cSPTimer mRelationshipTimer;         // +0x128
    // __thiscall members (ret N): declared here so the first stack argument lands on the stack.
    int   FUN_00c308e0(Obj* p);          // 0x00c308e0 (ret 4)
    void  FUN_00c309b0(uint arg);        // 0x00c309b0 (ret 4)
    float GetUFOHealth(int idx);         // 0x00c31920 (ret 4)
    void  FUN_00c30c10(Obj* p);          // 0x00c30c10 (ret 4)
    void  FUN_00c30fa0(const Vec3* p);   // 0x00c30fa0 (ret 4)
    bool  FUN_00c31470(cCivData* c);     // 0x00c31470 (ret 4)
    void  SetHomePlanet(Obj* p);         // 0x00c316c0 (ret 4)
};

// forward declarations for mutually-referenced helpers
cCivData* __fastcall cEmpireFindNearestCity(cEmpire* self, Vec3 pos);
void      __fastcall cEmpireSetHomePlanet(cEmpire* self, Obj* p);

// ===================================================================================================
// @ 0x00c308b0
bool __fastcall cEmpireIsPlayerCurrentStar(cEmpire* self)
{
    return SP_StarManager()->m_885c90() == (int)self->mEmpireID;
}

// ===================================================================================================
// @ 0x00c308e0
int cEmpire::FUN_00c308e0(Obj* p)
{
    if (p != 0)
        if (FUN_00c70150(p, (Obj*)this, 0))
            return 1;
    return 0;
}

// ===================================================================================================
// @ 0x00c30910
void __fastcall cEmpireFUN_00c30910(cEmpire* self)
{
    uint id = self->mEmpireID;
    SP_NounManager()->m_f67d90()->m_c7a710(id);
}

// @ 0x00c30930
void __fastcall cEmpireFUN_00c30930(cEmpire* self)
{
    uint id = self->mEmpireID;
    SP_NounManager()->m_f67d90()->m_c7bb80(id);
    id = self->mEmpireID;
    SP_NounManager()->m_f67d90()->m_c7bba0(id);
}

// @ 0x00c30970
void __fastcall cEmpireFUN_00c30970(cEmpire* self)
{
    uint id = self->mEmpireID;
    SP_NounManager()->m_f67d90()->m_c7a770(id);
}

// @ 0x00c30990
void __fastcall cEmpireFUN_00c30990(cEmpire* self)
{
    uint id = self->mEmpireID;
    SP_NounManager()->m_f67d90()->m_c7a830(id);
}

// @ 0x00c309b0
void cEmpire::FUN_00c309b0(uint arg)
{
    uint id = this->mEmpireID;
    SP_NounManager()->m_f67d90()->m_c7bbf0(id, arg);
}

// ===================================================================================================
// @ 0x00c309e0
bool __fastcall cEmpireIsHostileToPlayer(cEmpire* self)
{
    Obj* rels = SP_RelationshipManager();
    uint player = (uint)SP_PlayerEmpireID();
    if (self->mEmpireID == player)
        return false;
    uint myId = self->mEmpireID;
    if (myId == (uint)SP_StarManager()->m_885c90()) {
        if (rels->m_d01f20(myId, player))
            return true;
        if (((Obj*)0x16dc798)->m_10107b0(myId) >= 3)
            if (!rels->m_d01fb0(myId, player))
                return true;
        return false;
    }
    if (rels->m_d01b80(myId, player, 0x5b6ce81) > 0.0f) {
        float f = rels->m_d00a10(myId, player, 0);
        if (f >= SP_GetSpaceRelationshipTuning()->m_1040860())
            return false;
    }
    if (rels->m_d01f20(myId, player))
        return true;
    if (((Obj*)0x16dc798)->m_10107b0(myId) >= 3) {
        float f = rels->m_d00a10(myId, player, 0);
        if (f <= SP_GetSpaceRelationshipTuning()->m_0097eeb0())
            return true;
    }
    return false;
}

// ===================================================================================================
// 0x00c30b40  HasDemandForTributeExpired: true when the relationship timer has run longer than
// 0.001 * the tuning's tribute timeout (tuning+0x98).
// @ 0x00c30b40
bool __fastcall cEmpireHasDemandForTributeExpired(cEmpire* self)
{
    int64_t elapsed = self->mRelationshipTimer.GetElapsedTime();
    float t = (float)elapsed * 0.001f;
    return t > *(float*)((char*)SP_GetSpaceRelationshipTuning() + 0x98);
}

// @ 0x00c30bb0
void __fastcall cEmpireFUN_00c30bb0(cEmpire* self)
{
    cSPTimer* t = &self->mRelationshipTimer;
    t->Stop();
    t->FUN_00bc3170();
}

// @ 0x00c30bd0
void* __fastcall cEmpireFUN_00c30bd0(cEmpire* self)
{
    Obj* m = EA_ResourceMan_GetManager();
    void* p = (char*)self + 0xb8;
    if (!m->Query(p, 0, 0, 0, 0, 0))
        FUN_0102c7f0(p, 1);
    return p;
}

// @ 0x00c30c10
void cEmpire::FUN_00c30c10(Obj* p)
{
    int v;
    if (p != 0)
        v = *(int*)((char*)p + 0x70);
    else
        v = -1;
    this->mUFOKey = v;
    SP_StarManager()->m_baf630(*(int*)&this->mEmpireID, (int)p);
    MsgObj* msg = SP_MessageServer();
    msg->send(0x43f2586, 0, 0, 0);
}

// @ 0x00c30c60
int __fastcall cEmpireFUN_00c30c60(cEmpire* self)
{
    int id = self->mUFOKey;
    if (id == -1)
        return 0;
    return SP_StarManager()->m_ba6d80((uint)id);
}

// @ 0x00c30c80
void* __fastcall cEmpireFUN_00c30c80(cEmpire* self)
{
    int id = self->mUFOKey;
    if (id != -1) {
        int v = SP_StarManager()->m_ba6d80((uint)id);
        if (v != 0)
            return ((Obj*)v)->m_bba500();
    }
    return 0;
}

// ===================================================================================================
// 0x00c30cc0  (a: 0..0x12 selects a 3-vector of which the b-th (0..2) element is returned).
// A switch over `a` with groups {0,9,0x12},{1,10},{2,0xb},{3,0xc},{4,0xd},{5,0xe},{6,0xf,0x11},
// {7,0x10},{8}; each returns a 3-way switch over `b`.  Default 0x4e5855b9.
// @ 0x00c30cc0
uint __cdecl FUN_00c30cc0(uint a, int b)
{
    uint r = 0x4e5855b9;
    switch (a) {
    case 0: case 9: case 0x12:
        if (b == 0) return 0xacb9635d;
        if (b == 1) return 0x4fede4a6;
        if (b == 2) return 0xed2bbcc8;
        break;
    case 1: case 10:
        if (b == 0) return 0x04a83b77;
        if (b == 1) return 0x250f78b4;
        if (b == 2) return 0x12486202;
        break;
    case 2: case 0xb:
        if (b == 0) return 0x5d054a25;
        if (b == 1) return 0x076b1a6e;
        if (b == 2) return 0x8aa5a470;
        break;
    case 3: case 0xc:
        if (b == 0) return 0xdf83b46d;
        if (b == 1) return 0xb308c5d6;
        if (b == 2) return 0x21d2a5b8;
        break;
    case 4: case 0xd:
        if (b == 0) return 0x59878688;
        if (b == 1) return 0xacd3a4cf;
        if (b == 2) return 0xf9b2cbad;
        break;
    case 5: case 0xe:
        if (b == 0) return 0xb8196164;
        if (b == 1) return 0x62166b9b;
        if (b == 2) return 0x01100719;
        break;
    case 6: case 0xf: case 0x11:
        if (b == 0) return 0xe80abf05;
        if (b == 1) return 0x901a654e;
        if (b == 2) return 0x18271550;
        break;
    case 7: case 0x10:
        if (b == 0) return 0x401c6160;
        if (b == 1) return 0x86a04027;
        if (b == 2) return 0x3001d0a5;
        break;
    case 8:
        if (b == 0) r = 0x25885eaf;
        else if (b == 1) return 0x7e56d6cc;
        else if (b == 2) return 0x87d7829a;
        break;
    }
    return r;
}

// ===================================================================================================
// 0x00c30e80  dispatches on the terrain editor's current sphere selection into FUN_00c30cc0.
// @ 0x00c30e80
uint __fastcall cEmpireFUN_00c30e80(cEmpire* self)
{
    Obj* sphere = SP_NounManager()->m_f67d90();
    int sel = 1;
    if (sphere != 0)
        sel = sphere->m_c75420();
    return FUN_00c30cc0(self->mArchetype, sel);
}

// ===================================================================================================
// 0x00c30eb0  archetype (this+0x58) -> display name; 0x13-entry jump table + default.
// @ 0x00c30eb0
const char* __fastcall cEmpireDebugArchetype(cEmpire* self)
{
    switch (self->mArchetype) {
    case 0:  return "Warrior";
    case 1:  return "Trader";
    case 2:  return "Scientist";
    case 3:  return "Shaman";
    case 4:  return "Bard";
    case 5:  return "Zealot";
    case 6:  return "Diplomat";
    case 7:  return "Ecologist";
    case 8:  return "gRob";
    case 9:  return "PlayerWarrior";
    case 10: return "PlayerTrader";
    case 11: return "PlayerScientist";
    case 12: return "PlayerShaman";
    case 13: return "PlayerBard";
    case 14: return "PlayerZealot";
    case 15: return "PlayerDiplomat";
    case 16: return "PlayerEcologist";
    case 17: return "PlayerWanderer";
    case 18: return "PlayerKnight";
    default: return "unknown_archetype";
    }
}

// ===================================================================================================
// @ 0x00c30fa0
void cEmpire::FUN_00c30fa0(const Vec3* p)
{
    *(uint*)&this->mPosX = *(const uint*)&p->x;
    *(uint*)&this->mPosY = *(const uint*)&p->y;
    *(uint*)&this->mPosZ = *(const uint*)&p->z;
    SP_NounManager()->m_f67d90()->m_c759a0();
}

// ===================================================================================================
// 0x00c31080  compares squared distance from (this->pos) to city a against city b.
// @ 0x00c31080
bool __fastcall cEmpireFUN_00c31080(cEmpire* self, cCivData* a, cCivData* b)
{
    Vec3* ca = cCivData_GetCities(a);
    float ax = ca->x - self->mPosX;
    float ay = ca->y - self->mPosY;
    float az = ca->z - self->mPosZ;
    Vec3* cb = cCivData_GetCities(b);
    float bx = cb->x - self->mPosX;
    float by = cb->y - self->mPosY;
    float bz = cb->z - self->mPosZ;
    return (ay * ay + ax * ax) + az * az < (bz * bz + by * by) + bx * bx;
}

// ===================================================================================================
// 0x00c31150  SP::cEmpire::Write(IO::IStream*): writes the magic 0x1805e75, sets this+0x4c from
// the current game mode, then serialises the cVarList.
// @ 0x00c31150
bool __fastcall cEmpireWrite(cEmpire* self, IStream* p)
{
    OutStream* out = p->m20();
    uint magic = 0x1805e75;
    IO_WriteUint32(out->m18(), &magic, 1, 0);
    bool ok = ((cTail*)((char*)self + 0xc))->m_b6e2d0((Obj*)p);
    switch (SP_GetCurrentGameMode()) {
    case 0x1654c00: *(int*)((char*)self + 0x4c) = 0; break;
    case 0x1654c01: *(int*)((char*)self + 0x4c) = 1; break;
    case 0x1654c02: *(int*)((char*)self + 0x4c) = 2; break;
    case 0x1654c04: *(int*)((char*)self + 0x4c) = 4; break;
    case 0x1654c05: *(int*)((char*)self + 0x4c) = 5; break;
    }
    cVarListSerializer ser(self, &DAT_01572b60, 0x1a80d26);
    if (ok && ser.Serialize(p))
        return true;
    return false;
}

// ===================================================================================================
// 0x00c31240  SP::cEmpire reading counterpart: reads the magic, +0xc helper, then builds the
// player-city music (if this is the player empire) or a win-text music object.
// @ 0x00c31240
bool __fastcall cEmpireRead(cEmpire* self, IStream* p)
{
    OutStream* out = p->m20();
    uint magic;
    IO_ReadInt32(out->m18(), &magic, 1, 0);
    bool bl = ((cTail*)((char*)self + 0xc))->m_b6e340((Obj*)p);
    cVarListSerializer ser(self, &DAT_01572b60, 0x1a80d26);
    if (bl && ser.SerializeStream(p))
        bl = true;
    else
        bl = false;
    if (*(void**)((char*)self + 0x104) != 0)
        return bl;
    if ((void*)self == (void*)SP_FUN_01021300()) {
        void* pc = EA_Allocate(0x220, "Simulator", 0, 0, 0, 0);
        void* nw;
        if (pc != 0)
            nw = ((Obj*)pc)->m_eb0ea0();
        else
            nw = 0;
        void* old = *(void**)((char*)self + 0x104);
        if (nw == old)
            return bl;
        if (nw != 0)
            (*(void(__thiscall**)(void*))*(void**)nw)(nw);
        *(void**)((char*)self + 0x104) = nw;
        if (old != 0)
            (*(void(__thiscall**)(void*))((*(void***)old)[1]))(old);
        return bl;
    }
    int avatar = SP_StarManager()->m_885c90();
    void* obj;
    if (avatar == (int)self->mEmpireID) {
        void* q = EA_Allocate(0x28, "Simulator", 0, 0, 0, 0);
        obj = (q != 0) ? ((Obj*)q)->m_eab410(4) : 0;
    } else {
        void* q = EA_Allocate(0x28, "Simulator", 0, 0, 0, 0);
        obj = (q != 0) ? ((Obj*)q)->m_eab410(3) : 0;
    }
    ((WinTextRef*)((char*)self + 0x104))->m_assign(obj);
    return bl;
}

// ===================================================================================================
// 0x00c313d0  nearest city (linear scan) to the given position.
// @ 0x00c313d0
cCivData* __fastcall cEmpireFindNearestCity(cEmpire* self, Vec3 pos)
{
    cCivData* best = 0;
    int n = (int)(self->mCitiesEnd - self->mCitiesBegin);
    float bestD = -1.0f;
    for (int i = 0; i < n; i++) {
        Vec3* c = cCivData_GetCities(self->mCitiesBegin[i]);
        float dx = pos.x - c->x;
        float dy = pos.y - c->y;
        float dz = pos.z - c->z;
        float d = sqrtf(dz * dz + dy * dy + dx * dx);
        if (best == 0 || d < bestD) {
            best = self->mCitiesBegin[i];
            bestD = d;
        }
    }
    return best;
}

// @ 0x00c31470
bool cEmpire::FUN_00c31470(cCivData* c)
{
    cCivData** end = this->mCitiesEnd;
    cCivData** p = this->mCitiesBegin;
    while (p != end && *p != c)
        p++;
    return p != end;
}

// ===================================================================================================
// 0x00c314a0  SP::cEmpire::WarnPlayer
// @ 0x00c314a0
void __fastcall cEmpireWarnPlayer(cEmpire* self)
{
    if (!SP_NounManager()->m_f67d90()->m_c7a770(self->mEmpireID)) {
        SP_NounManager()->m_f67d90()->m_c7bba0(self->mEmpireID);
        Vec3* c = cCivData_GetCities((cCivData*)SP_FUN_01021240());
        cCivData* city = cEmpireFindNearestCity(self, *c);
        Obj* sr = (Obj*)SP_StarManager()->m_bb5ae0((int)city);
        Obj* ctx = sr->m_ce6950();
        SP_CommManager()->m_aeb3e0((int)self->mEmpireID, (int)city, (int)ctx,
                                    0x95bbbbfc, 0xde4b97ed, 1, 0, 0);
    }
}

// ===================================================================================================
// 0x00c31550  SP::cEmpire::WelcomePlayer
// @ 0x00c31550
void __fastcall cEmpireWelcomePlayer(cEmpire* self)
{
    if (SP_NounManager()->m_f67d90()->m_c7a770(self->mEmpireID))
        return;
    SP_FUN_01021240();
    if (SP_UniverseContext() != 2) {
        if ((void*)SP_GetAvatar() == (void*)&self->mEmpireID)
            return;
    }
    SP_NounManager()->m_f67d90()->m_c7bba0(self->mEmpireID);
    if (SP_NounManager()->m_f67d90()->m_c7a710(self->mEmpireID))
        return;
    Vec3* c = cCivData_GetCities((cCivData*)SP_FUN_01021240());
    cCivData* city = cEmpireFindNearestCity(self, *c);
    void* sr = SP_StarManager()->m_bb5ae0((int)city);
    void* ctx = ((Obj*)sr)->m_ce6950();
    SP_CommManager()->m_aeb3e0((int)self->mEmpireID, (int)city, (int)ctx,
                                0x95bbbbfc, 0xaf301a2c, 1, 0, 0);
}

// @ 0x00c31640
bool __fastcall cEmpireFUN_00c31640(cEmpire* self)
{
    if (cEmpireIsHostileToPlayer(self))
        return true;
    uint player = (uint)SP_PlayerEmpireID();
    if (self->mEmpireID == player)
        return false;
    if (((Obj*)0x16dc798)->m_10107b0(self->mEmpireID) >= 2) {
        Obj* rels = SP_RelationshipManager();
        float f = rels->m_d00a10(self->mEmpireID, player, 0);
        if (f <= SP_GetSpaceRelationshipTuning()->m_00fb8a00())
            return true;
    }
    return false;
}

// @ 0x00c316c0
void cEmpire::SetHomePlanet(Obj* p)
{
    int v;
    if (p != 0)
        v = (int)p->m_ce6950();
    else
        v = -1;
    this->mEmpireMoney = v;
    Obj* q = (p != 0) ? p->m_b8de30() : 0;
    int v2;
    if (p != 0 && q != 0)
        v2 = *(int*)((char*)q + 0x70);
    else
        v2 = -1;
    this->mUFOKey = v2;
    SP_StarManager()->m_baf630(*(int*)&this->mEmpireID, (int)q);
    MsgObj* msg = SP_MessageServer();
    msg->send(0x43f2586, 0, 0, 0);
}

// @ 0x00c31730
Obj* __fastcall cEmpireGetHomePlanet(cEmpire* self)
{
    int star = SP_StarManager()->m_ba6d80((uint)self->mUFOKey);
    if (self->mEmpireMoney == -1 && star != 0) {
        Obj* s = (Obj*)star;
        SP_StarManager()->m_bb4af0(star, 0);
        Obj* rec = s->m_bba790();
        self->SetHomePlanet((Obj*)(*(int*)(*(int*)rec)));
    }
    if (self->mEmpireMoney == -1)
        return 0;
    return (Obj*)SP_StarManager()->m_ba6dc0((uint)self->mEmpireMoney);
}

// @ 0x00c317a0
int __fastcall cEmpireGetWeaponryLevel(cEmpire* self)
{
    if (self->mWeaponryLevel >= 0)
        return self->mWeaponryLevel;
    self->mWeaponryLevel = 0;
    cCivData* cd;
    if (self->mUFOKey == -1)
        cd = 0;
    else
        cd = (cCivData*)SP_StarManager()->m_ba6d80((uint)self->mUFOKey);
    Vec3* c = cCivData_GetCities(cd);
    self->mWeaponryLevel = SP_GetSpaceCombatTuning()->m_102a360();
    int a = 0, b = 0;
    SP_GetSpaceCombatTuning();
    Obj* tun = SP_GetSpaceCombatTuning();
    GetPropertyAsIntArray(*(void**)((char*)tun + 8), 0x5e526ce, &b, &a);
    int n = (int)(self->mCitiesEnd - self->mCitiesBegin);
    if (a > 0) {
        int* arr = (int*)b;
        for (int i = a - 1; i > 0; ) {
            a = i;
            if (n >= arr[i])
                self->mWeaponryLevel++;
            i--;
        }
    }
    if (SP_StarManager()->m_885c90() == (int)self->mEmpireID)
        self->mWeaponryLevel++;
    return self->mWeaponryLevel;
}

// @ 0x00c31890
float __fastcall cEmpireGetBackgroundFighterDPS(cEmpire* self)
{
    if (self->mBgFighterDPS <= 0.0f)
        self->mBgFighterDPS = SP_GetSpaceCombatTuning()->m_1029cc0(cEmpireGetWeaponryLevel(self));
    return self->mBgFighterDPS;
}

// @ 0x00c318c0
float __fastcall cEmpireGetBackgroundBomberDPS(cEmpire* self)
{
    if (self->mBgBomberDPS <= 0.0f)
        self->mBgBomberDPS = SP_GetSpaceCombatTuning()->m_1029d50(cEmpireGetWeaponryLevel(self));
    return self->mBgBomberDPS;
}

// @ 0x00c318f0
float __fastcall cEmpireGetBackgroundTurretDPS(cEmpire* self)
{
    if (self->mBgTurretDPS <= 0.0f)
        self->mBgTurretDPS = SP_GetSpaceCombatTuning()->m_1029de0(cEmpireGetWeaponryLevel(self));
    return self->mBgTurretDPS;
}

// @ 0x00c31920
float __thiscall cEmpire::GetUFOHealth(int idx)
{
    float* p = &this->mUFOHealth[idx];
    if (*p < 0.0f)
        *p = SP_GetSpaceCombatTuning()->m_102a630(idx, cEmpireGetWeaponryLevel(this));
    return *p;
}
