// Slice s00ffa2c0 -- SP::cSPSimPlanetHighLOD subsystem
//   UpdateCombatState / UpdateLoot / CreateReplacement / BlowUpCity / war-music state machine
//
// All helper callees keep their retail address in a trailing comment; the equivalence checker
// resolves those comments to the original addresses.  Deliberately NO raw-offset pointer
// arithmetic: every touched field is a named member whose ordinal position reproduces the
// retail layout.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-
#include "types.h"
#include <math.h>

#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV  virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4
#define PV16 PV8 PV8

namespace SP {

struct Vec3 { float x, y, z; };

// ---- generic refcounted handle (vtable slots: +4 Release, +8 FX, +0xc SetFlag(int)) -------
struct RefObj {
    PV
    virtual void Release();          // +0x04
    virtual void FX();               // +0x08
    virtual void SetFlag(int);       // +0x0c
    void FUN_00ebd340();             // 0x00ebd340
};

// the m1dc handle has a 2nd slot that takes an argument
struct RefObjI {
    PV
    virtual void Release();          // +0x04
    virtual void Slot2(int);         // +0x08
    virtual void SetFlag(int);       // +0x0c
};

struct SFXObj {
    void FUN_00becd70(int);          // 0x00becd70
};

// ---- creature animation host at creature+8 --------------------------------------------
struct CreatureAnim {
    void* Play(int a, unsigned flags);   // 0x00bc96a0
};
struct Creature { uint32_t m00, m04; CreatureAnim m08; };

// ---- sub-objects embedded at fixed offsets of a noun -----------------------------------
struct Sub120 {                         // noun+0x120 (position provider)
    PV8 PV2 PV
    virtual Vec3* Slot2C();             // +0x2c
};
struct Sub508 {                         // noun+0x508
    int FUN_008e7f80();                 // 0x008e7f80
};
struct PbObj {                          // *(noun+0x518)
    PV4 PV2
    virtual void* Slot18();             // +0x18
};
struct PbHolder {                       // returned by noun vtable slot 1
    uint8_t pad00[0x518];
    PbObj*  m518;                       // +0x518
};

// ---- a noun (creature / city / UFO) ----------------------------------------------------
struct Entity {
    PV                                  // +0x00
    virtual void* Slot04(int);          // +0x04
    PV8                                 // +0x08..0x24
    PV                                  // +0x28
    virtual bool  Slot2C();             // +0x2c
    PV4 PV2 PV                          // +0x30..0x48
    virtual int   Slot4C();             // +0x4c
    PV4 PV                          // +0x50..0x60
    virtual Vec3* Slot64();             // +0x64
    PV                                  // +0x68
    virtual SFXObj* Slot6C();           // +0x6c
    bool  FUN_00c372b0();               // 0x00c372b0
    bool  FUN_00c004c0(int);            // 0x00c004c0
    int   FUN_00bd9b60();               // 0x00bd9b60
    void  FUN_00bdc050();               // 0x00bdc050
    // data (object offset +0x04 onward)
    uint8_t pad04[0x10 - 0x04];
    int8_t  m10;                        // +0x10
    uint8_t pad11[0x12 - 0x11];
    int8_t  m12;                        // +0x12
    uint8_t pad13[0x18 - 0x13];
    int     m18;                        // +0x18
    uint8_t pad1c[0x28 - 0x1c];
    int     m28;                        // +0x28
    uint8_t pad2c[0x120 - 0x2c];
    Sub120  m120;                       // +0x120
    uint8_t pad124[0x220 - 0x124];
    float   m220;                       // +0x220
    uint8_t pad224[0x508 - 0x224];
    Sub508  m508;                       // +0x508
    uint8_t pad50c[0x518 - 0x50c];
    PbObj*  m518;                       // +0x518
    uint8_t pad51c[0x640 - 0x51c];
    int     m640;                       // +0x640
    uint8_t pad644[0x658 - 0x644];
    int     m658;                       // +0x658
    uint8_t pad65c[0x68c - 0x65c];
    int     m68c;                       // +0x68c
    uint8_t pad690[0x6c8 - 0x690];
    Creature* m6c8;                     // +0x6c8
    uint8_t pad6cc[0x714 - 0x6cc];
    int     m714;                       // +0x714
    uint8_t pad718[0x748 - 0x718];
    float   m748;                       // +0x748
    int     m74c;                       // +0x74c
};

// ---- record element inside planetRecord+0x134 (stride 0x2c) -----------------------------
struct RecElem {
    uint8_t pad00[0x12];
    int8_t  m12;                        // +0x12
    uint8_t pad13[0x18 - 0x13];
    int     m18;                        // +0x18
    uint8_t pad1c[0x28 - 0x1c];
    int     m28;                        // +0x28
};
struct ElemList {
    RecElem* m00;                       // +0x134
    RecElem* m04;                       // +0x138
    void FUN_00b8e540(RecElem*);        // 0x00b8e540
};

// ---- global managers -------------------------------------------------------------------
struct GdVector { uint32_t m00; void** m04; void** m08; uint32_t m0c; uint32_t m10; };
struct GameTimeManager { uint64_t FUN_00b316c0(); };   // 0x00b316c0
struct NounIter { void FUN_00acc390(); void FUN_00ad0bd0(); };

struct cGameNounManager {
    void* GetAvatar();                                             // 0x00b1fdb0
    void  RemoveNoun(void*);                                       // 0x00b225d0
    GdVector* GetGameDataVector(void*, void*, void*, void*, void*); // 0x00b21340
    void  FUN_00b25fe0();                                          // 0x00b25fe0
    void  FUN_00b22bc0();                                          // 0x00b22bc0
    void  FUN_00b22960();                                          // 0x00b22960
    void  FUN_00b222a0();                                          // 0x00b222a0
};

struct AudioSystem {
    PV8 PV4 PV2
    virtual void Slot38(int);                                       // +0x38
    virtual void Slot3c(int, float);                                // +0x3c
    virtual void Slot40(int, int);                                  // +0x40
    PV4 PV
    virtual void Slot58();                                          // +0x58
};
struct BehaviorManager {
    PV8 PV4
    virtual void Slot30();                                          // +0x30
    PV4
    virtual void Slot44();                                          // +0x44
};
struct CheatManager {
    PV4 PV2 PV
    virtual void Slot1c(void*);                                     // +0x1c
};
struct MessageServer {
    PV4 PV
    virtual void Slot14(int, int, int);                             // +0x14
};
struct SimTicker {
    PV16 PV4 PV
    virtual void Slot54(void*);                                     // +0x54
};
struct SimSingleton {
    SimSingleton* ctor();               // 0x00dc7d70
    void FUN_00dcc2c0();                // 0x00dcc2c0
};
struct EffectsManager {
    PV8 PV2 PV
    virtual bool Slot2C(int, int, void*);                           // +0x2c
};
struct TerrainSphere {
    PV16 PV16 PV8 PV2 PV
    virtual void SlotAC();                                          // +0xac
};

struct cStarRecord { uint8_t pad[4]; };
struct cEmpire {
    uint8_t pad00[0x84];
    cStarRecord* m84;                   // +0x84
    int  GetUFOKey();                   // 0x00c326b0
    int  GetHomePlanet();               // 0x00c31730
    bool IsHostileToPlayer();           // 0x00c309e0
};
struct cStarManager { cEmpire* GetEmpireByID(int id); };           // 0x00ba9370

struct InvSub {
    PV8 PV2 PV
    virtual Vec3* Slot2C();             // +0x2c
};
struct Inventory {
    uint8_t pad00[0x34];
    InvSub m34;                         // +0x34
    bool FUN_00c38500();                // 0x00c38500
};
struct UFOsim { Inventory* GetPlayerInventory(); };                // 0x00a1ad60

struct PlanetModelObj {
    void GetRandomSurfacePoint(Vec3*); // 0x00b84730
    void FUN_00b87bb0();               // 0x00b87bb0
};
struct cSPGameDataUFO {
    void FUN_00c3be70(Vec3*);          // 0x00c3be70
    void FUN_00c3daa0(float);          // 0x00c3daa0
    void PopToDestination();           // 0x00c37e60
};

struct PlanetObj {                      // GetActivePlanet()
    uint8_t pad00[0x108];
    int m108;                           // +0x108
    int  FUN_00c71e30();                // 0x00c71e30
    int  FUN_00c70e00();                // 0x00c70e00
    void FUN_00c70bc0(int);             // 0x00c70bc0
};
struct PlanetRecord {                   // GetActivePlanetRecord()
    uint8_t pad00[0x134];
    ElemList mElemList;                 // +0x134
    cGameNounManager* FUN_00b8de30();        // 0x00b8de30
    int          FUN_00b8dab0();        // 0x00b8dab0
};

// ---- random / tuning -------------------------------------------------------------------
struct RandomLCG { float FUN_009360d0(); };                         // 0x009360d0
struct cSPSpaceCombatTuning { float GetLootCityMoneyChance(); };    // 0x0102a310
struct RelMgr { bool FUN_00d01f50(); };                             // 0x00d01f50
struct AeObj { void FUN_00ae49d0(int, int, void*, int, int, int, int, int); };  // 0x00ae49d0

// temporary builder used by FUN_00ffaa90
struct TempC {
    void* mPtr;                         // scratch array begin
    void FUN_00b93c60(int, void*);      // 0x00b93c60
};

// ---- data / address operands ------------------------------------------------------------
extern char gFn_00cd7d10[];    // 0x00cd7d10
extern char gFn_00d3d420[];    // 0x00d3d420
extern char gFn_00ad48b0[];    // 0x00ad48b0
extern char gFn_00acdff0[];    // 0x00acdff0
extern char gFn_00ad4930[];    // 0x00ad4930
extern char gFn_00b1e500[];    // 0x00b1e500
extern char gFn_00b1e520[];    // 0x00b1e520
extern char gFn_00ae7060[];    // 0x00ae7060
extern char gFn_00ae7080[];    // 0x00ae7080
extern char gStr_spgspg[];     // 0x01495078 "spg_war_music_level"
extern char gStr_SimSingleton[]; // 0x0145f924 "Simulator/SimSingleton"
extern const float gF_1485378;  // 0x01485378 0.0
extern const float gF_13ec4d0;  // 0x013ec4d0 100.0
extern const float gF_13f7670;  // 0x013f7670 35.0
extern const float gF_13f4fd0;  // 0x013f4fd0 4294967296.0
extern const float gF_15b60d8;  // 0x015b60d8
extern uint32_t gU_15b8690;     // 0x015b8690
extern void* gSim_1699ab8;      // 0x01699ab8
extern uint32_t gKey_016db5c4;  // 0x016db5c4
extern uint32_t gKey_016db5c8;  // 0x016db5c8
extern uint32_t gKey_016db5cc;  // 0x016db5cc
extern RandomLCG gRand_1601760; // 0x01601760

// ---- free helpers ----------------------------------------------------------------------
cGameNounManager* NounManager();          // 0x00b3d300
GameTimeManager* GameTimeManager300();    // 0x00b3d380
cStarManager* StarManager();              // 0x00b3d2a0
PlanetModelObj* PlanetModel();            // 0x00b3d350
SimTicker* SimTicker_();                  // 0x00b3d330
BehaviorManager* BehaviorManager_();      // 0x00b3d260
CheatManager* CheatManager_();            // 0x0067de20
MessageServer* MessageServer_();          // 0x0067dcc0
EffectsManager* EffectsManagerPtr();      // 0x0067ddd0
AudioSystem* GetSystemAT();               // 0x00a206f0
TerrainSphere* GetActiveTerrainSphere();  // 0x00f48aa0
UFOsim* GetUFOSimulator();                // 0x00ffbe50
PlanetObj* GetActivePlanet();             // 0x01021260
PlanetRecord* GetActivePlanetRecord();    // 0x010212a0
cEmpire* GetPlayerEmpire();               // 0x01021300
int GetPlayerEmpireID();                  // 0x01021090
cGameNounManager* FUN_01021240();         // 0x01021240
NounIter* FUN_00b3d480();                 // 0x00b3d480
cSPGameDataUFO* CreateUFO(int, void*, int);   // 0x0102acb0
cSPSpaceCombatTuning* GetSpaceCombatTuning(); // 0x01029940
void DropLoot(Vec3);                      // 0x0102ba30
bool IsMissionActiveAtPlanet(PlanetObj*);// 0x0102adf0
void* operator_new(uint32_t, const void*, int, int, int, int);  // 0x00f473a0
void  operator_delete_array(void*);       // 0x00f47380
void* RBTreeIncrement(void*);             // 0x00921580
void  FUN_00ba5270(void*, int);           // 0x00ba5270
void  FUN_00bd7d10(int, float);           // 0x00bd7d10
void  FUN_00bd7f70(Vec3*, float*);        // 0x00bd7f70
uint32_t FNVHash(const char*, uint32_t, int);  // 0x00932e80
void  FUN_00c9a080();                     // 0x00c9a080
void  FUN_00829110(void**, void*, void*, void*, void*); // 0x00829110
void* FUN_00b26930(int, int, void*, int, int, int, int, int);   // 0x00b26930
int   FUN_0102b690(int, int, int);        // 0x0102b690
RelMgr* FUN_00b3d2c0(int, int);           // 0x00b3d2c0

// ---- the HighLOD simulator object ------------------------------------------------------
struct ListNode { ListNode* mNext; uint32_t m04; RefObj* m08; };
struct ListHead {
    ListNode* mHead;                    // +0x34
    ListNode* mTail;                    // +0x38
    void FUN_00ff80b0();                // 0x00ff80b0
};
struct TreeNode { uint8_t pad[0x14]; RefObj* m14; };
struct RBTree {
    uint32_t m00;                       // +0x1c0
    void*    m04;                       // +0x1c4
    void*    m08;                       // +0x1c8
    void*    m0c;                       // +0x1cc
    uint8_t  m10;                       // +0x1d0
    uint32_t m14;                       // +0x1d4
    void FUN_00d0c930(void*);           // 0x00d0c930
};

class cSPSimPlanetHighLOD {
public:
    void FUN_00ffa2c0();                       // 0x00ffa2c0
    void CreateReplacement();                  // 0x00ffa780
    void BlowUpCity(void* city, int param3);   // 0x00ffa900
    void FUN_00ffaa90(int param);              // 0x00ffaa90
    void FUN_00ffabc0();                       // 0x00ffabc0
    void FUN_00ffb030();                       // 0x00ffb030

    uint8_t pad00[0x10];
    int     m10;                        // +0x10
    int8_t  m14;                        // +0x14
    uint8_t pad15[0x18 - 0x15];
    RefObj* m18;                        // +0x18
    RefObj* m1c;                        // +0x1c
    uint8_t pad20[0x28 - 0x20];
    RefObj* m28;                        // +0x28
    RefObj* m2c;                        // +0x2c
    RefObj* m30;                        // +0x30
    ListHead m34;                       // +0x34
    uint8_t pad3c[0x1b0 - 0x3c];
    RefObj* m1b0;                       // +0x1b0
    int8_t  m1b4;                       // +0x1b4
    uint8_t pad1b5[0x1b8 - 0x1b5];
    int     m1b8;                       // +0x1b8
    RefObj* m1bc;                       // +0x1bc
    RBTree  m1c0;                       // +0x1c0
    RefObjI* m1dc;                      // +0x1dc
    int8_t  m1e0;                       // +0x1e0
};

// @ 0xffa2c0
void cSPSimPlanetHighLOD::FUN_00ffa2c0()
{
    this->m1b8 = 0;
    PlanetObj* planet = GetActivePlanet();
    if (this->m1b4) {
        this->m1b4 = 0;
        FUN_00ba5270(planet, 0);
    }
    this->m1e0 = 0;
    if (this->m1dc) {
        this->m1dc->SetFlag(0);
        if (this->m1dc) { RefObjI* q = this->m1dc; this->m1dc = 0; q->Release(); }
    }
    for (TreeNode* n = (TreeNode*)this->m1c0.m08; n != (TreeNode*)&this->m1c0.m04; n = (TreeNode*)RBTreeIncrement(n))
        n->m14->SetFlag(1);
    this->m1c0.FUN_00d0c930(this->m1c0.m0c);
    this->m1c0.m04 = &this->m1c0.m04;
    this->m1c0.m08 = &this->m1c0.m04;
    this->m1c0.m0c = 0;
    this->m1c0.m10 = 0;
    this->m1c0.m14 = 0;
    if (this->m1bc) {
        this->m1bc->SetFlag(1);
        if (this->m1bc) { RefObj* q = this->m1bc; this->m1bc = 0; q->Release(); }
    }
    if (this->m18) {
        this->m18->SetFlag(1);
        if (this->m18) { RefObj* q = this->m18; this->m18 = 0; q->Release(); }
    }
    if (this->m1c) {
        this->m1c->SetFlag(1);
        if (this->m1c) { RefObj* q = this->m1c; this->m1c = 0; q->Release(); }
    }
    cGameNounManager* nm = NounManager();
    if (nm) {
        FUN_00b3d480()->FUN_00acc390();
        FUN_00b3d480()->FUN_00ad0bd0();
        BehaviorManager_()->Slot30();
        GdVector* gv = nm->GetGameDataVector(gFn_00cd7d10, gFn_00d3d420, gFn_00ad48b0, gFn_00b1e500, (void*)0x18ebadc);
        int cnt10 = 0, cnt14 = 0;
        for (void** pp = (void**)gv->m04; pp != (void**)gv->m08; pp++) {
            Entity* e = (Entity*)*pp;
            if (e->FUN_00c372b0()) continue;
            Creature* c = e->m6c8;
            if (c && c->m08.Play(0x10, 0)) continue;
            if (e->m714 == 6) cnt10++;
            else if (e->m714 == 7) cnt14++;
        }
        planet->FUN_00c70bc0(cnt10);
        planet->m108 = cnt14;
        FUN_00c9a080();
        nm->FUN_00b25fe0();
        nm->FUN_00b22bc0();
        nm->FUN_00b22960();
        nm->FUN_00b222a0();
        BehaviorManager_()->Slot44();
        CheatManager_()->Slot1c(&gU_15b8690);
        if (gSim_1699ab8 == 0) {
            SimSingleton* s = (SimSingleton*)operator_new(0x58, gStr_SimSingleton, 0, 0, 0, 0);
            gSim_1699ab8 = s ? (void*)s->ctor() : 0;
        }
        SimSingleton* sim = (SimSingleton*)gSim_1699ab8;
        sim->FUN_00dcc2c0();
        SimTicker* st = SimTicker_();
        if (gSim_1699ab8 == 0) {
            SimSingleton* s2 = (SimSingleton*)operator_new(0x58, gStr_SimSingleton, 0, 0, 0, 0);
            gSim_1699ab8 = s2 ? (void*)s2->ctor() : 0;
        }
        st->Slot54(gSim_1699ab8);
        if (this->m10 != 1) {
            this->m10 = 1;
            uint32_t u = FNVHash(gStr_spgspg, 0x811c9dc5, 1);
            AudioSystem* as = GetSystemAT();
            if (as) {
                as->Slot38(0x3cdd1a9);
                as->Slot40(0x34753a7, u);
                as->Slot3c(0x34753aa, (float)this->m10);
                as->Slot58();
            }
            MessageServer_()->Slot14(0x4c703a5, 0, 0);
        }
        if (this->m28) { RefObj* q = this->m28; this->m28 = 0; q->FX(); }
        if (this->m30) { RefObj* q = this->m30; this->m30 = 0; q->Release(); }
        for (ListNode* n = this->m34.mHead; n != (ListNode*)&this->m34; n = n->mNext)
            if (n->m08) n->m08->SetFlag(0);
        this->m34.FUN_00ff80b0();
        this->m34.mHead = (ListNode*)&this->m34;
        this->m34.mTail = (ListNode*)&this->m34;
        if (this->m1b0) {
            this->m1b0->FUN_00ebd340();
            if (this->m1b0) { RefObj* q = this->m1b0; this->m1b0 = 0; q->FX(); }
        }
    }
}

// @ 0xffa690
void FUN_00ffa690()
{
    GameTimeManager* gt = GameTimeManager300();
    uint64_t v = gt->FUN_00b316c0();
    uint32_t u = (uint32_t)(v / 1000);

    PlanetRecord* pr = GetActivePlanetRecord();
    ElemList* list = &pr->mElemList;
    for (RecElem* e = list->m00; ; e = (RecElem*)((char*)e + 0x2c)) {
        if (e == list->m04) break;
        if ((e->m28 & 8) && e->m12 == 7 && (uint32_t)e->m18 < u && (u - (uint32_t)e->m18) > 300) {
            list->FUN_00b8e540(e);
            break;
        }
    }
    cGameNounManager* nm = NounManager();
    GdVector* gv = nm->GetGameDataVector(gFn_00cd7d10, gFn_00d3d420, gFn_00ad4930, gFn_00b1e500, (void*)0x2dd8c42);
    int cnt = (int)(((char*)gv->m08 - (char*)gv->m04) >> 2);
    for (int i = 0; i < cnt; i++) {
        Entity* e = ((Entity**)gv->m04)[i];
        if (e->m658 == 7 && (uint32_t)e->m640 < u && (u - (uint32_t)e->m640) > 0x12c) {
            NounManager()->RemoveNoun(e);
            return;
        }
    }
}

// @ 0xffa780
void cSPSimPlanetHighLOD::CreateReplacement()
{
    void* avatar = FUN_01021240()->GetAvatar();
    cEmpire* empire = StarManager()->GetEmpireByID((int)avatar);
    if (!empire) return;

    int key = empire->GetUFOKey();
    cStarRecord* rec = empire->m84;
    cSPGameDataUFO* ufo = CreateUFO(6, &rec, key);

    Inventory* inv = GetUFOSimulator()->GetPlayerInventory();
    Vec3* base = inv->m34.Slot2C();

    Entity* best = 0;
    float bestD = 0.0f;
    GdVector* gv = NounManager()->GetGameDataVector(gFn_00cd7d10, gFn_00d3d420, gFn_00acdff0, gFn_00b1e500, (void*)0x18c43e8);
    if (gv->m04 != gv->m08) {
        for (void** pp = (void**)gv->m04; pp != (void**)gv->m08; pp++) {
            Entity* e = (Entity*)*pp;
            Vec3* p2 = e->m120.Slot2C();
            float dy = p2->y - base->y;
            float dz = p2->z - base->z;
            float dx = p2->x - base->x;
            float d = (float)sqrt(dy * dy + (dz * dz + dx * dx));
            if (d > bestD) { bestD = d; best = e; }
        }
        if (best) {
            Vec3 v;
            FUN_00bd7f70(&v, &bestD);
            float len = (float)sqrt(v.x * v.x + (v.z * v.z + v.y * v.y));
            ufo->FUN_00c3be70(&v);
            ufo->FUN_00c3daa0(len);
            ufo->PopToDestination();
            ufo->FUN_00c3daa0(len + 35.0f);
        }
    }
}

// @ 0xffa900
void cSPSimPlanetHighLOD::BlowUpCity(void* city, int param3)
{
    RefObj* c = this->m2c;
    if (city == c && c != 0) {
        this->m2c = 0;
        c->Release();
    }
    int empId = GetPlayerEmpireID();
    PlanetRecord* pr = GetActivePlanetRecord();
    int avatar = -1;
    if (pr != 0 && pr->FUN_00b8de30() != 0)
        avatar = (int)pr->FUN_00b8de30()->GetAvatar();

    ((Entity*)city)->FUN_00bdc050();
    if (((Entity*)city)->m74c == empId) {
        float r = gRand_1601760.FUN_009360d0();
        float chance = GetSpaceCombatTuning()->GetLootCityMoneyChance();
        if (r <= chance) {
            Vec3* p = ((Entity*)city)->Slot64();
            DropLoot(*p);
        }
    }
    cGameNounManager* nm = NounManager();
    GdVector* gv = nm->GetGameDataVector(gFn_00cd7d10, gFn_00d3d420, gFn_00acdff0, gFn_00b1e500, (void*)0x18c43e8);
    bool four = (((char*)gv->m08 - (char*)gv->m04) & 0xfffffffc) == 4;
    int home = GetPlayerEmpire()->GetHomePlanet();
    if (pr == (PlanetRecord*)home && four) {
        Vec3 v;
        PlanetModel()->GetRandomSurfacePoint(&v);
        void* rr = FUN_00b26930((int)0x1058c90, empId, &v, 0, 0xfd701f6f, 0, 0, 0);
        ((AeObj*)rr)->FUN_00ae49d0((int)0x1058c90, empId, &v, 0, 0xfd701f6f, 0, 0, 0);
    }
    nm->RemoveNoun(city);
    if (param3 == empId && avatar != empId && four)
        FUN_0102b690(avatar, param3, 1);
}

// @ 0xffaa90
void cSPSimPlanetHighLOD::FUN_00ffaa90(int param)
{
    cGameNounManager* nm = NounManager();
    GdVector* gv = nm->GetGameDataVector(gFn_00cd7d10, gFn_00d3d420, gFn_00acdff0, gFn_00b1e500, (void*)0x18c43e8);
    int cnt = (int)(((char*)gv->m08 - (char*)gv->m04) >> 2);
    TempC tmp;
    tmp.FUN_00b93c60(cnt, &gv->m10);
    void* end = 0;
    FUN_00829110(&end, gv->m04, gv->m08, tmp.mPtr, (void*)param);
    int n = (int)(((char*)end - (char*)tmp.mPtr) >> 2);
    for (int i = 0; i < n; i++)
        BlowUpCity(((void**)tmp.mPtr)[i], param);
    for (void** p = (void**)tmp.mPtr; (char*)p < (char*)end; p++)
        if (*p) ((RefObj*)*p)->Release();
    if (tmp.mPtr && ((int*)tmp.mPtr)[-1] != 0)
        operator_delete_array(tmp.mPtr);
}

// @ 0xffab60
void FUN_00ffab60()
{
    cGameNounManager* nm = NounManager();
    GdVector* gv = nm->GetGameDataVector(gFn_00cd7d10, gFn_00d3d420, gFn_00acdff0, gFn_00b1e500, (void*)0x18c43e8);
    int cnt = (int)(((char*)gv->m08 - (char*)gv->m04) >> 2);
    for (int i = 0; i < cnt; i++) {
        Entity* e = ((Entity**)gv->m04)[i];
        SFXObj* s = e->Slot6C();
        s->FUN_00becd70(0);
    }
}

// @ 0xffabc0
void cSPSimPlanetHighLOD::FUN_00ffabc0()
{
    int local_24 = 1;
    PlanetObj* planet = GetActivePlanet();
    int iVar7 = planet->FUN_00c71e30();
    int iVar8 = (int)GetPlayerEmpire();

    bool bVar1;
    if (iVar7 == 0 || iVar7 == iVar8) {
        bVar1 = false;
    } else {
        RelMgr* rel = FUN_00b3d2c0(iVar7, iVar8);
        bVar1 = true;
        if (!rel->FUN_00d01f50()) bVar1 = false;
    }
    bool bVar2 = false, bVar3 = false, bVar4 = false, bVar5 = false;

    Inventory* inv = GetUFOSimulator()->GetPlayerInventory();
    GdVector* gv = NounManager()->GetGameDataVector(gFn_00cd7d10, gFn_00d3d420, gFn_00ad48b0, gFn_00b1e500, (void*)0x18ebadc);
    int cnt = (int)(((char*)gv->m08 - (char*)gv->m04) >> 2);
    for (int i = 0; i < cnt; i++) {
        Entity* e = ((Entity**)gv->m04)[i];
        int iVar16 = e->m714;
        int iVar13 = e->Slot4C();
        cEmpire* empire = StarManager()->GetEmpireByID(iVar13);
        if (e->Slot2C()) continue;
        if (e->FUN_00c372b0()) continue;
        if (e->m508.FUN_008e7f80() == 2) continue;
        if (!bVar2 && (iVar16 == 4 || iVar16 == 2)) {
            if (iVar13 == -1) bVar2 = true;
            else if (empire && empire->IsHostileToPlayer()) bVar2 = true;
        } else if (!bVar3 && iVar16 == 8) {
            if (empire && empire->IsHostileToPlayer()) bVar3 = true;
        } else if (!bVar4 && iVar16 == 6) {
            if (e->m68c == (int)inv) bVar4 = true;
        } else if (!bVar5 && iVar16 == 0xb) {
            bVar5 = true;
        }
    }

    int iVar12 = 0;
    GdVector* gv2 = NounManager()->GetGameDataVector(gFn_00cd7d10, gFn_00d3d420, gFn_00acdff0, gFn_00b1e500, (void*)0x18c43e8);
    int cnt2 = (int)(((char*)gv2->m08 - (char*)gv2->m04) >> 2);
    if (planet->FUN_00c70e00() == 5 && iVar7 != iVar8) {
        for (int i = 0; i < cnt2; i++) {
            Entity* e = ((Entity**)gv2->m04)[i];
            if (e->m748 <= gF_13ec4d0 &&
                (bVar1 || e->m220 > gF_1485378 || e->FUN_00c004c0(0)) &&
                e->FUN_00bd9b60() > 0)
                iVar12++;
        }
    }
    if (bVar1 && iVar12 == 0) {
        local_24 = 2;
    } else if (iVar12 == 1 || bVar2 || bVar5 || bVar4 || bVar3) {
        local_24 = 3;
    }
    if (iVar12 > 1) local_24 = 4;
    if (inv && inv->FUN_00c38500()) local_24 = 1;
    if (this->m10 != local_24) {
        uint32_t u = FNVHash(gStr_spgspg, 0x811c9dc5, 1);
        AudioSystem* as = GetSystemAT();
        if (as) {
            as->Slot38(0x3cdd1a9);
            as->Slot40(0x34753a7, u);
            as->Slot3c(0x34753aa, (float)local_24);
            as->Slot58();
        }
        this->m10 = local_24;
    }
    this->m14 = (this->m10 != 1) ? 1 : 0;
}

// @ 0xffaf20
void __stdcall FUN_00ffaf20(int param_1)
{
    PlanetRecord* pr = GetActivePlanetRecord();
    if (pr->FUN_00b8dab0() != 5) return;

    bool bVar2 = false;
    void* avatar = FUN_01021240()->GetAvatar();
    int pid = GetPlayerEmpireID();
    if ((int)avatar == pid) {
        if (!IsMissionActiveAtPlanet(GetActivePlanet())) bVar2 = true;
    }
    cGameNounManager* nm = NounManager();
    GdVector* gv = nm->GetGameDataVector(gFn_00cd7d10, gFn_00d3d420, gFn_00acdff0, gFn_00b1e500, (void*)0x18c43e8);
    int cnt = (int)(((char*)gv->m08 - (char*)gv->m04) >> 2);
    for (int i = 0; i < cnt; i++) {
        Entity* e = ((Entity**)gv->m04)[i];
        int id = e->m74c;
        if (!bVar2 || id == -1) continue;
        float f = (float)(uint32_t)param_1;
        float a = e->m748 - f * gF_15b60d8;
        float r;
        if (0.0f <= a) r = a; else r = 0.0f;
        if (r == 0.0f) id = -1;
        FUN_00bd7d10(id, r);
    }
}

// @ 0xffb030
void cSPSimPlanetHighLOD::FUN_00ffb030()
{
    this->m1e0 = 1;
    this->FUN_00ffaa90(GetPlayerEmpireID());
    if (this->m1dc) {
        this->m1dc->SetFlag(0);
        if (this->m1dc) { RefObjI* q = this->m1dc; this->m1dc = 0; q->Release(); }
    }
    cGameNounManager* nm = NounManager();
    GdVector* gv = nm->GetGameDataVector(gFn_00cd7d10, gFn_00ae7060, gFn_00ae7080, gFn_00b1e520, (void*)0x142db2a);
    for (Entity** pp = (Entity**)gv->m04; pp != (Entity**)gv->m08; pp++) {
        Entity* e = *pp;
        if (!e) continue;
        PbHolder* h = (PbHolder*)e->Slot04(0x24270c4);
        if (!h || !h->m518) continue;
        void* k = h->m518->Slot18();
        if (((int*)k)[0] == (int)gKey_016db5c4 && ((int*)k)[1] == (int)gKey_016db5c8 && ((int*)k)[2] == (int)gKey_016db5cc)
            e->m10 = 1;
    }
    NounManager()->FUN_00b25fe0();
    PlanetModel()->FUN_00b87bb0();
    GetActiveTerrainSphere()->SlotAC();
    EffectsManager* em = EffectsManagerPtr();
    if (this->m1dc) { RefObjI* q = this->m1dc; this->m1dc = 0; q->Release(); }
    if (em->Slot2C(0x556ed9bc, 0, &this->m1dc))
        this->m1dc->Slot2(0);
}

} // namespace SP