// SP::cSPSpaceGameBehaviorAbducted::Action (0x01032bc0): per-tick update of the UFO abduction
// beam. Iterates every agent in the interaction's agent list, queries its interfaces by id,
// and runs the beam state machine (0 = pull to the ship, 1 = drop, 2 = release).
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE. Callees are masked relocations; declarations only
// need the right calling convention and argument sizes.
#include "types.h"

typedef unsigned int uint;
typedef void* P;

struct Vec3 { float x, y, z; };

// ---- external callees (names from the PDB / Ghidra where known) ----
struct Range { P* blocks; uint idx; int c; int d; int e; int f; };  // 6-dword by-value iterator
struct Abducted;

// The original callees use __thiscall with a callee-cleaned stack (ret N).  MSVC only allows
// __thiscall on members, so they are declared as members of a stub class and reached through
// the FUN_* wrappers below; each wrapper passes its first argument as `this` (ecx) and the
// rest as stack arguments, matching the original call sites exactly.
struct Tc {
    void __thiscall m_00abf010(P agentList, P filter);                         // 0x00abf010 build [begin,end) over agents
    void __thiscall m_00abeb20();                                              // 0x00abeb20 advance iterator
    P    __thiscall m_008414c0();                                              // 0x008414c0
    void __thiscall m_00b81630(Vec3* out, const Vec3* pos);                    // 0x00b81630
    void __thiscall m_00cb8ba0(Vec3* a, Vec3* b);                              // 0x00cb8ba0 GetEndPoints
    P    __thiscall m_00a1ad60();                                              // 0x00a1ad60 GetPlayerInventory
    void __thiscall m_00b225d0(P noun);                                        // 0x00b225d0 RemoveNoun ret 4
    int  __thiscall m_00885c90();                                              // 0x00885c90 getter of [ecx+0x1d8]
    void __thiscall m_00dd8640(uint a, uint b, int c, int d, int e, int f);    // 0x00dd8640 PostFeedbackEvent ret 0x18
    P    __thiscall m_00c0bc00();                                              // 0x00c0bc00 accessor
    P    __thiscall m_00c463d0();                                              // 0x00c463d0 accessor returning its argument
    P    __thiscall m_00ac0cb0(P a, P b, int c, int d);                        // 0x00ac0cb0 MakeInventoryItemFromSpecies ret 0x10
    bool __thiscall m_00c73ea0(P species);                                     // 0x00c73ea0 SetSpeciesAsScanned ret 4
    void __thiscall m_00c74690(P a, int b, int c);                             // 0x00c74690 ret 0xc
    P    __thiscall m_00c3e1e0(P out);                                         // 0x00c3e1e0 ret 4
    P    __thiscall m_00b90410(P species);                                     // 0x00b90410 GetSpeciesFromID ret 4
    void __thiscall m_01016540(P a, int b);                                    // 0x01016540 RemoveHighLODPlant ret 8
    void __thiscall m_00c12310(uint id, int a, int b);                         // 0x00c12310 InterruptAnimation ret 0xc
    void __thiscall m_00c421b0(P locomotion);                                  // 0x00c421b0 ret 4
    void __thiscall m_00c14750(int a);                                         // 0x00c14750 ret 4
    void __thiscall m_00aca360(P arg);                                         // 0x00aca360 ret 4
    void __thiscall m_00b2d910(P arg);                                         // 0x00b2d910 ret 4
    void __thiscall m_00c82400(P a, P pos, int flag);                          // 0x00c82400 SetSimAnimalAt ret 0xc
    void __thiscall m_00c81ab0(P a, P pos, int flag);                          // 0x00c81ab0 SetSimPlantAt ret 0xc
    P    __thiscall m_00ce6950();                                              // 0x00ce6950 getter of [ecx+0x184]
    P    __thiscall m_00f67d90();                                              // 0x00f67d90 GetCurrentTerrainSphere getter of [ecx+0x74]
    char __thiscall m_00c830b0(P arg);                                         // 0x00c830b0 ret 4
    void __thiscall m_00c830d0(P arg, int v);                                  // 0x00c830d0 ret 8
    P    __thiscall m_00bfc5f0();                                              // 0x00bfc5f0 getter of [ecx+0x70]
    void __thiscall m_00fe5430(int a, int b);                                  // 0x00fe5430 ret 8
    P    __thiscall m_00ad2620(P out);                                         // 0x00ad2620 ret 4
    P    __thiscall m_00b8dad0();                                              // 0x00b8dad0 accessor
    P    __thiscall m_00ace2c0();                                              // 0x00ace2c0
    P    __thiscall m_00bd81f0();                                              // 0x00bd81f0 getter of [ecx+0x2f0]
    void __thiscall m_00ff0350(float f);                                       // 0x00ff0350 ret 4
    P    __thiscall m_00c31a00(int a);                                         // 0x00c31a00 ret 4
    void __thiscall m_00fffdd0(int a, uint b);                                 // 0x00fffdd0 ret 8
    void __thiscall m_0103fe90(int a, P b);                                    // 0x0103fe90 CollectSpicePile ret 8
    bool __thiscall m_00c74ca0();                                              // 0x00c74ca0 IsRare
    int  __thiscall m_0103ac40(P a);                                           // 0x0103ac40 ret 4
    void __thiscall m_00c389c0(int a, int b);                                  // 0x00c389c0 ret 8
    bool __thiscall m_0104e340(P a, P b);                                      // 0x0104e340 CreateToolFromToolID ret 8
    P    __thiscall m_01005180(int a);                                         // 0x01005180 ret 4
    void __thiscall m_007eb820(int a);                                         // 0x007eb820 ret 4
    void __thiscall m_00421c80(int a);                                         // 0x00421c80 SlotMessage::Construct ret 4
    void __thiscall m_00421cf0();                                              // 0x00421cf0 SlotMessage::Destruct
};
#define FUN_00abf010(r,a,b)            (((Tc*)(r))->m_00abf010(a,b))
#define FUN_00abeb20(r)                (((Tc*)(r))->m_00abeb20())
#define FUN_008414c0(r)                (((Tc*)(r))->m_008414c0())
#define FUN_00b81630(r,a,b)            (((Tc*)(r))->m_00b81630(a,b))
#define GetEndPoints(r,a,b)            (((Tc*)(r))->m_00cb8ba0(a,b))
#define GetPlayerInventory(r)          (((Tc*)(r))->m_00a1ad60())
#define RemoveNoun(r,a)                (((Tc*)(r))->m_00b225d0(a))
#define FUN_00885c90(r)                (((Tc*)(r))->m_00885c90())
#define PostFeedbackEvent(r,a,b,c,d,e,f) (((Tc*)(r))->m_00dd8640(a,b,c,d,e,f))
#define FUN_00c0bc00(r)                (((Tc*)(r))->m_00c0bc00())
#define FUN_00c463d0(r)                (((Tc*)(r))->m_00c463d0())
#define MakeInventoryItemFromSpecies(r,a,b,c,d) (((Tc*)(r))->m_00ac0cb0(a,b,c,d))
#define SetSpeciesAsScanned(r,a)       (((Tc*)(r))->m_00c73ea0(a))
#define FUN_00c74690(r,a,b,c)          (((Tc*)(r))->m_00c74690(a,b,c))
#define FUN_00c3e1e0(r,a)              (((Tc*)(r))->m_00c3e1e0(a))
#define GetSpeciesFromID(r,a)          (((Tc*)(r))->m_00b90410(a))
#define RemoveHighLODPlant(r,a,b)      (((Tc*)(r))->m_01016540(a,b))
#define InterruptAnimation(r,a,b,c)    (((Tc*)(r))->m_00c12310(a,b,c))
#define FUN_00c421b0(r,a)              (((Tc*)(r))->m_00c421b0(a))
#define FUN_00c14750(r,a)              (((Tc*)(r))->m_00c14750(a))
#define FUN_00aca360(r,a)              (((Tc*)(r))->m_00aca360(a))
#define FUN_00b2d910(r,a)              (((Tc*)(r))->m_00b2d910(a))
#define SetSimAnimalAt(r,a,b,c)        (((Tc*)(r))->m_00c82400(a,b,c))
#define SetSimPlantAt(r,a,b,c)         (((Tc*)(r))->m_00c81ab0(a,b,c))
#define FUN_00ce6950(r)                (((Tc*)(r))->m_00ce6950())
#define GetCurrentTerrainSphere(r)     (((Tc*)(r))->m_00f67d90())
#define FUN_00c830b0(r,a)              (((Tc*)(r))->m_00c830b0(a))
#define FUN_00c830d0(r,a,b)            (((Tc*)(r))->m_00c830d0(a,b))
#define FUN_00bfc5f0(r)                (((Tc*)(r))->m_00bfc5f0())
#define FUN_00fe5430(r,a,b)            (((Tc*)(r))->m_00fe5430(a,b))
#define FUN_00ad2620(r,a)              (((Tc*)(r))->m_00ad2620(a))
#define FUN_00b8dad0(r)                (((Tc*)(r))->m_00b8dad0())
#define FUN_00ace2c0(r)                (((Tc*)(r))->m_00ace2c0())
#define FUN_00bd81f0(r)                (((Tc*)(r))->m_00bd81f0())
#define FUN_00ff0350(r,a)              (((Tc*)(r))->m_00ff0350(a))
#define FUN_00c31a00(r,a)              (((Tc*)(r))->m_00c31a00(a))
#define FUN_00fffdd0(r,a,b)            (((Tc*)(r))->m_00fffdd0(a,b))
#define CollectSpicePile(r,a,b)        (((Tc*)(r))->m_0103fe90(a,b))
#define IsRare(r)                      (((Tc*)(r))->m_00c74ca0())
#define FUN_0103ac40(r,a)              (((Tc*)(r))->m_0103ac40(a))
#define FUN_00c389c0(r,a,b)            (((Tc*)(r))->m_00c389c0(a,b))
#define CreateToolFromToolID(r,a,b)    (((Tc*)(r))->m_0104e340(a,b))
#define FUN_01005180(r,a)              (((Tc*)(r))->m_01005180(a))
#define FUN_007eb820(r,a)              (((Tc*)(r))->m_007eb820(a))
#define MsgConstruct(r,a)              (((Tc*)(r))->m_00421c80(a))
#define MsgDestruct(r)                 (((Tc*)(r))->m_00421cf0())

// ---- cdecl callees ----
P      GetActivePlanet();                   // 0x01021260 cSPLivingUniverse::GetActivePlanet (getter)
P      PlanetModel();   // 0x00b3d350 SP::PlanetModel (getter)
P      GetUFOSimulator();   // 0x00ffbe50 SP::GetUFOSimulator (getter)
P      SpaceGameGet();                      // 0x01002bd0 SP::SpaceGameGet (getter)
P      GetRecorderState();   // 0x00435e90 (getter)
void   KillSetiEffects(uint id, P rec);   // 0x00435ed0 SP::cSPUISpace::KillSetiEffects
P      EA_Messaging_GetServer();   // 0x00883860 EA::Messaging::GetServer (getter)
P      MessageServer();   // 0x0067dcc0 SP::MessageServer (getter)
P      NounManager();                 // 0x00b3d300 SP::NounManager (getter)
P      StarManager();   // 0x00b3d2a0 SP::StarManager (getter)
P      EventLog();   // 0x00b3d3e0 SP::EventLog (getter)
P      FUN_00b3d450();                        // 0x00b3d450 getter
P      FUN_00b3d420();                           // 0x00b3d420 getter
P      FUN_01015df0();                           // 0x01015df0 getter
void   FUN_01058660(P creature, int flag);    // 0x01058660
void   FUN_010527f0(P a, uint b, int c);   // 0x010527f0 cdecl 3
P      FUN_00b3d240();                            // 0x00b3d240 getter
P      FUN_00b3d480();                            // 0x00b3d480 getter
P      FUN_00b3d3b0();                            // 0x00b3d3b0 getter
void   SetZooMarker(P low, P a, P pos, P noun);   // 0x01043fd0 cdecl 4
bool   FUN_004eb930(P a, P b);                       // 0x004eb930 cdecl 2
P      FUN_00ac9dd0(P a, P b);                       // 0x00ac9dd0 cdecl 2
P      GetPlayerEmpire();   // 0x01021300 cSPLivingUniverse::GetPlayerEmpire (getter)
P      FUN_00b3d3d0();                                 // 0x00b3d3d0 getter
bool   FUN_005f78f0(P a, P b);              // 0x005f78f0 EA::ResourceMan::operator!=
P      FUN_00b3d390();                      // 0x00b3d390 getter
void   FUN_00c878d0(Vec3 key, P out);       // 0x00c878d0 ret 0 (Vec3 by value + out = 4 dwords)
void   RemoveArtifact(P low, P a, uint count);   // 0x00c71160 SP::RemoveArtifact
P      InterfaceCastArtifact(P noun);   // 0x01030e40
extern uint  g_Msg_vtbl;                    // vtbl_UI::BehaviorMessage / message vtable
extern P     g_spaceTokenTranslator;   // 0x016e0d08 _gpSpaceTokenTranslator_SP__3PAVcSpaceTokenTranslator_1_A
extern char  DAT_016ded38[], DAT_016ded44[];
void*  operator_new(uint size, const char* name, int a, int b, int c, int d);   // 0x00f473a0
// Message block as laid out on the stack (0x40 bytes).
struct Msg {
    P vtbl; int rc; P data0; int pad0; uint data1; uint pad[8]; int tail0; int pad1; int tail1;
};
// 16-byte scratch buffer (a struct, not an array, so /GS does not add a cookie).
struct Buf16 { int a, b, c, d; };

// ---- stub classes for virtual calls ----
struct IMover {  // QI id 0x116dd1b
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10();
    virtual Vec3* GetPosition();      // +0x2c
    virtual void v12(); virtual void v13();
    virtual void GetFacing(Vec3* out); // +0x38
};
struct IFlag {  // QI id 0x4f176642
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
    virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18();
    virtual int GetId();               // +0x4c
};
struct ICreature {  // QI id 0xce9f6639 (cSPCreatureBase)
    char pad[0x5dc]; int damageState;   // +0x5dc (cCombatant::GetDamageState result)
};
struct IObject {  // generic refcounted
    virtual void v0(); virtual void Release0();
    virtual void Release();            // +0x8
};
struct IItem {
    virtual void v0(); virtual void v1(); virtual void v2();
    virtual void v3(); virtual void v4(); virtual void v5();
    virtual P GetKind(int a, int b);   // +0x18
    virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16();
    virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20(); virtual void v21();
    virtual void v22(); virtual void v23(); virtual void v24(); virtual void v25(); virtual void v26();
    virtual void v27(); virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
    virtual void v32(); virtual bool PutBack(P item, int a, int b);  // +0x80
};

struct Abducted {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
    virtual bool IsAgentDone(P agent);      // +0x3c
    virtual void v16();
    virtual void RemoveAgent(Range r);      // +0x44 (iterator by value)
    uint pad0[2];                           // +0x04
    P**  targetBlocks;                      // +0x0c
    uint pad1[5];                           // +0x10
    uint targetFree;                        // +0x24
    uint pad2;                              // +0x28
    uint agentList[6];                      // +0x2c (+0x18 -> +0x44 = agent free chain)
    uint agentFree;                         // +0x44
    uint pad3[11];                          // +0x48
    bool isAbducting;                       // +0x74 (beam style; 0 = tractor)
    char pad4[3];
    int  state;                             // +0x78
    int  nextState;                         // +0x7c

    bool Action();
    void AdjustRelationship();
    bool OnAgentHitsGround(P agent, bool beam, bool flag);
};

static inline P EntryAt(P* blocksPtr, uint idx)
{
    P* blocks = *(P**)blocksPtr;
    return *(P*)((char*)blocks[idx >> 7] + 4 + (idx & 0x7f) * 8);
}

// @ 0x01032bc0
bool Abducted::Action()
{
    if (agentFree == 0x3fffffff) return false;

    Abducted* self = this;
    struct AgentFilter { Abducted* owner; int flag; };
    AgentFilter filter;
    filter.owner = self;
    filter.flag = 0;
    Range it;
    FUN_00abf010(&it, (P)agentList, (P)&filter);
    if ((uint)it.c + it.d == (uint)it.idx + (uint)it.blocks) return true;

    // beam projectile of the first target
    P beam = 0;
    if (targetFree != 0x3fffffff) {
        P* t = (P*)((char*)targetBlocks[targetFree >> 7] + 4 + (targetFree & 0x7f) * 8);
        P obj = *t;
        if (obj) {
            beam = ((P(__thiscall*)(P, uint))(*(P**)obj)[1])(obj, 0x24630ce);
            if (beam && ((char(__thiscall*)(P))(*(P**)beam)[0x2c / 4])(beam) == 0)
                goto keep;
        }
    }
    nextState = 2;
keep:
    bool changed2 = false;
    if (state != nextState) {
        if (nextState == 2) changed2 = true;
        state = nextState;
    }

    P planet = GetActivePlanet();
    if (!planet) return false;
    P low = *(P*)((char*)planet + 0x13c);
    P cube = FUN_008414c0(planet);
    P model = PlanetModel();

    while ((uint)it.c + it.d != (uint)it.idx + (uint)it.blocks) {
        P entry = EntryAt((P*)it.blocks, it.idx);
        if (!entry) { goto removeAgent; }
        {
            typedef P (__thiscall *QI)(P, uint);
            QI qi = (QI)(*(P**)entry)[2];
            P flagO   = qi(entry, 0x4f176642);
            P creature = qi(entry, 0xce9f6639);
            P plant   = qi(entry, 0xaeb336b4);
            P artifact = qi(entry, 0x283d961);
            IMover* mover = (IMover*)qi(entry, 0x116dd1b);
            IFlag* flag = (IFlag*)flagO;

            if (((!creature && !plant && !artifact) || !mover)) goto removeAgent;

            if (changed2) {
                P* loco = (P*)operator_new(0x14, "Simulator/cDropToGroundLocomotion", 0, 0, 0, 0);
                if (loco) {
                    loco[2] = (P)0x013ec458;
                    loco[3] = 0;
                    loco[0] = (P)0x01499590;
                    loco[2] = (P)0x01499580;
                    loco[4] = 0;
                }
                FUN_00c421b0((P)mover, (P)loco);
                if (creature) {
                    InterruptAnimation(creature, 0x3cc7ebb, -1, 0);
                    ((void(__thiscall*)(P, int))(*(P**)creature)[0x9c / 4])(creature, 0);
                }
            }

            switch (state) {
            case 0: {
                if (!beam) break;
                Vec3 endA, endB;
                GetEndPoints(beam, &endA, &endB);
                Vec3* pos = mover->GetPosition();
                float dx = pos->x - endA.x, dz = pos->z - endA.z, dy = pos->y - endA.y;
                if (!(dx * dx + dz * dz + dy * dy < 6.0f)) break;

                P item = 0;
                P ufo = GetUFOSimulator();
                if (ufo) {
                    P inv = GetPlayerInventory(GetUFOSimulator());
                    P invp = inv ? (P)((char*)inv + 0x34) : 0;
                    P owner = *(P*)((char*)*(P*)((char*)beam + 0x134) + 0x114);
                    if (owner == invp) {
                        P sg = SpaceGameGet();
                        P playerInv = 0;
                        if (sg && (playerInv = GetPlayerInventory(sg)) != 0) {
                            KillSetiEffects(0x9fbe154b, GetRecorderState());
                            if (creature) {
                                Msg m; MsgConstruct(&m.rc, 0); m.data0 = entry;
                                ((void(__thiscall*)(P, uint, P, int))(*(P**)EA_Messaging_GetServer())[0x14 / 4])
                                    (EA_Messaging_GetServer(), 0x3029f11, &m.rc, 0);
                                bool big = ((ICreature*)creature)->damageState != 2;
                                bool done = false;
                                if (flag) {
                                    int id = FUN_00885c90(StarManager());
                                    if (flag->GetId() == id) {
                                        PostFeedbackEvent(EventLog(), 0x49256302, 0x131a9f54, 0, 0, 1, 0);
                                        MsgDestruct(&m);
                                        done = true;
                                    }
                                }
                                if (!done) {
                                    if (big) {
                                        P tool = 0;
                                        P slot = FUN_00c463d0(&tool);
                                        item = MakeInventoryItemFromSpecies(FUN_00b3d450(), slot,
                                                                            FUN_00c0bc00(creature), 1, flag != 0);
                                        if (item) {
                                            if (flag) {
                                                // stamp the empire/species id on the item
                                                *(int*)((char*)item + 0x20) = flag->GetId();
                                                MsgDestruct(&m);
                                                done = true;
                                            } else {
                                                P kind = ((IItem*)item)->GetKind(0, 0);
                                                if (!SetSpeciesAsScanned(planet, kind)) {
                                                    FUN_01058660(creature, 1);
                                                    P k2 = ((IItem*)item)->GetKind(1, 1);
                                                    FUN_00c74690(planet, k2, 1, 0);
                                                }
                                            }
                                        }
                                    }
                                    if (!done) MsgDestruct(&m);
                                }
                            } else if (plant) {
                                Msg dummy; (void)dummy;
                                P noun = plant;
                                Buf16 tmp;
                                P species = GetSpeciesFromID(FUN_00b3d420(), FUN_00c3e1e0(noun, (P)&tmp));
                                if (species) {
                                    P slot = FUN_00c463d0(&item);
                                    ((void(__thiscall*)(P, P))(*(P**)species)[0x24 / 4])(species, slot);
                                    RemoveHighLODPlant(FUN_01015df0(), noun, 0);
                                    P k = ((IItem*)item)->GetKind(1, 1);
                                    FUN_00c74690(planet, k, 1, 1);
                                }
                            }
                        }
                        if (item) {
                            if (!((IItem*)playerInv)->PutBack(item, 0, 1))
                                FUN_010527f0(*(P*)((char*)beam + 0x134), 0xb24b77da, 1);
                        }
                        if (item) ((IObject*)item)->Release();
                        self->AdjustRelationship();
                        item = 0;
                    }
                }
                self->RemoveAgent(it);
                if (creature) ((void(__thiscall*)(P, int))(*(P**)creature)[0xc8 / 4])(creature, 0);
                if (plant) {
                    Msg m; MsgConstruct(&m.rc, 0); m.data0 = entry;
                    ((void(__thiscall*)(P, uint, P, int))(*(P**)EA_Messaging_GetServer())[0x14 / 4])
                        (EA_Messaging_GetServer(), 0x3029f11, &m.rc, 0);
                    FUN_00b2d910(FUN_00b3d3b0(), plant);
                    MsgDestruct(&m);
                }
                if (artifact) {
                    P art = InterfaceCastArtifact(artifact);
                    if (art) {
                        switch (*(int*)((char*)art + 0x658)) {
                        case 7:
                            FUN_00c31a00(GetPlayerEmpire(), *(uint*)((char*)art + 0x638));
                            FUN_00fffdd0(GetUFOSimulator(), 0, *(uint*)((char*)art + 0x638));
                            break;
                        case 2:
                            if (GetUFOSimulator()) {
                                P inv = GetPlayerInventory(GetUFOSimulator());
                                P invp = inv ? (P)((char*)inv + 0x34) : 0;
                                P owner = *(P*)((char*)*(P*)((char*)beam + 0x134) + 0x114);
                                if (owner == invp) {
                                    Buf16 tmp;
                                    if (FUN_005f78f0(FUN_00ad2620(art, &tmp), DAT_016ded44) &&
                                        *(uint*)((char*)art + 0x638) != 0) {
                                        P tool = 0;
                                        P toolSlot = FUN_00c463d0(&tool);
                                        if (CreateToolFromToolID(FUN_00b3d390(), toolSlot, FUN_00ad2620(art, &tmp))) {
                                            FUN_00c389c0(GetPlayerInventory(GetUFOSimulator()), 5, 1);
                                            *(int*)((char*)tool + 0x7c) = *(int*)((char*)art + 0x638);
                                            IItem* pi = (IItem*)GetPlayerInventory(SpaceGameGet());
                                            pi->PutBack(tool, 0, 1);
                                            P ui = FUN_01005180(SpaceGameGet(), 0xf);
                                            FUN_007eb820(ui, 9);
                                            P* kind = (P*)((P(__thiscall*)(P))(*(P**)tool)[0x18 / 4])(tool);
                                            *(P*)(*(char**)((char*)ui + 0xc) + 0x1c) = *kind;
                                            *(int*)(*(char**)((char*)ui + 0xc) + 0x20) = 3;
                                            *(P*)((char*)g_spaceTokenTranslator + 0x14) = tool;
                                            PostFeedbackEvent(EventLog(), 0x15e1a624, 0x131a9f54, 0, 0, 1, 0);
                                        }
                                        if (tool) ((IObject*)tool)->Release();
                                    }
                                }
                            }
                            break;
                        case 5:
                            if (GetUFOSimulator()) {
                                P inv = GetPlayerInventory(GetUFOSimulator());
                                P invp = inv ? (P)((char*)inv + 0x34) : 0;
                                P owner = *(P*)((char*)*(P*)((char*)beam + 0x134) + 0x114);
                                if (owner == invp) {
                                    Buf16 tmp;
                                    P tool = 0;
                                    Vec3 key = *(Vec3*)FUN_00ad2620(art, &tmp);
                                    FUN_00c878d0(key, FUN_00c463d0(&tool));
                                    if (tool) {
                                        IItem* pi = (IItem*)GetPlayerInventory(SpaceGameGet());
                                        pi->PutBack(tool, 0, 1);
                                        if (tool) ((IObject*)tool)->Release();
                                    }
                                }
                            }
                            break;
                        case 4:
                            if (GetUFOSimulator()) {
                                P inv = GetPlayerInventory(GetUFOSimulator());
                                P invp = inv ? (P)((char*)inv + 0x34) : 0;
                                P owner = *(P*)((char*)*(P*)((char*)beam + 0x134) + 0x114);
                                if (owner == invp) {
                                    CollectSpicePile(FUN_00b3d3d0(), 1, art);
                                    if (IsRare(art)) {
                                        Buf16 tmp;
                                        if (FUN_0103ac40(FUN_00b3d3d0(), FUN_00ad2620(art, &tmp)) != 1)
                                            FUN_00c389c0(GetPlayerInventory(GetUFOSimulator()), 7, 1);
                                    }
                                }
                            }
                            break;
                        }
                        Msg m; MsgConstruct(&m.rc, 0); m.data0 = entry;
                        ((void(__thiscall*)(P, uint, P, int))(*(P**)EA_Messaging_GetServer())[0x14 / 4])
                            (EA_Messaging_GetServer(), 0x3029f11, &m.rc, 0);
                        Buf16 tmp;
                        RemoveArtifact(low, FUN_00ad2620(art, &tmp), *(uint*)((char*)art + 0x638));
                        MsgDestruct(&m);
                    }
                    RemoveNoun(NounManager(), artifact);
                }
                break;
            }
            case 1: {
                Vec3* pos = mover->GetPosition();
                Vec3 up;
                FUN_00b81630(model, &up, pos);
                float dx = pos->x - up.x, dy = pos->y - up.y, dz = pos->z - up.z;
                if (!(dx * dx + dz * dz + dy * dy < 1.0f) &&
                    !(pos->y * pos->y + pos->z * pos->z + pos->x * pos->x <=
                      up.y * up.y + up.z * up.z + up.x * up.x))
                    break;
                bool hit = true;
                if (creature) {
                    if (!flag) {
                        hit = self->OnAgentHitsGround(entry, isAbducting, false);
                        if (hit) {
                            FUN_00c14750(creature, 1);
                            int before = (int)(((int*)low)[0xd4 / 4] - ((int*)low)[0xd0 / 4]) / 12;
                            Vec3 v; mover->GetFacing(&v);
                            ((void(__thiscall*)(P, uint, P, P))(*(P**)FUN_00b3d240())[0x60 / 4])
                                (FUN_00b3d240(), 0x2818ee0, &v, DAT_016ded38);
                            if (*(uint*)((char*)low + 0x2c) & 0x800)
                                SetZooMarker(low, FUN_00c0bc00(creature), pos, creature);
                            FUN_00aca360(FUN_00b3d480(), creature);
                            SetSimAnimalAt(cube, FUN_00c0bc00(creature), pos, 1);
                            if (!SetSpeciesAsScanned(planet, FUN_00c0bc00(creature)))
                                FUN_01058660(creature, 0);
                            FUN_00c74690(planet, FUN_00c0bc00(creature), 1, 0);
                            if (!(*(uint*)((char*)low + 0x2c) & 0x800)) {
                                int after = (int)(((int*)low)[0xd4 / 4] - ((int*)low)[0xd0 / 4]) / 12;
                                if (before != after) {
                                    char cnt = (char)(after / 3);
                                    P key = FUN_00ce6950(low);
                                    P sphere = GetCurrentTerrainSphere(NounManager());
                                    if (FUN_00c830b0(sphere, key) < cnt) {
                                        FUN_00c830d0(GetCurrentTerrainSphere(NounManager()), key, cnt);
                                        P owner = FUN_00bfc5f0(SpaceGameGet());
                                        if (owner) FUN_00fe5430(owner, 10, 1);
                                        ((void(__thiscall*)(P, uint, int, int))(*(P**)MessageServer())[0x14 / 4])
                                            (MessageServer(), 0xf46092d5, 0, 0);
                                    }
                                }
                            }
                        }
                    } else {
                        hit = self->OnAgentHitsGround(entry, isAbducting, false);
                        if (hit) {
                            FUN_00c14750(creature, 1);
                            Vec3 v; mover->GetFacing(&v);
                            ((void(__thiscall*)(P, uint, P, P))(*(P**)FUN_00b3d240())[0x60 / 4])
                                (FUN_00b3d240(), 0x2818ee0, &v, DAT_016ded38);
                            FUN_00aca360(FUN_00b3d480(), creature);
                        }
                    }
                }
                if (plant) {
                    Buf16 tmp;
                    P species = GetSpeciesFromID(FUN_00b3d420(), FUN_00c3e1e0(plant, (P)&tmp));
                    Vec3 sp = *(Vec3*)((P(__thiscall*)(P))(*(P**)species)[0x18 / 4])(species);
                    hit = self->OnAgentHitsGround(entry, isAbducting, false);
                    if (!hit) {
                        RemoveNoun(NounManager(), plant);
                    } else {
                        Vec3 v; mover->GetFacing(&v);
                        ((void(__thiscall*)(P, uint, P, P))(*(P**)FUN_00b3d240())[0x60 / 4])
                            (FUN_00b3d240(), 0x2818ee0, &v, DAT_016ded38);
                        SetSimPlantAt(cube, &sp, pos, 1);
                        FUN_00c74690(planet, &sp, 1, 0);
                    }
                }
                if (artifact) {
                    Vec3 v; mover->GetFacing(&v);
                    ((void(__thiscall*)(P, uint, P, P))(*(P**)FUN_00b3d240())[0x60 / 4])
                        (FUN_00b3d240(), 0x2818ee0, &v, DAT_016ded38);
                    P art = InterfaceCastArtifact(artifact);
                    if (art && *(int*)((char*)art + 0x658) == 4) {
                        Buf16 tmp;
                        if (FUN_004eb930(FUN_00b8dad0(low), FUN_00ad2620(art, (P)&tmp))) {
                            P mgr = ((P(__thiscall*)(P))(*(P**)*(P*)((char*)art + 0x34))[0x2c / 4])((char*)art + 0x34);
                            P x = FUN_00ac9dd0(FUN_00ace2c0(NounManager()), mgr);
                            if (x) {
                                uint cnt = *(uint*)((char*)art + 0x638);
                                FUN_00ff0350(FUN_00bd81f0(x), (float)cnt);
                            }
                        }
                    }
                    if (!(art && *(int*)((char*)art + 0x658) == 4))
                        RemoveNoun(NounManager(), artifact);
                }
                if (self->IsAgentDone(entry)) self->RemoveAgent(it);
                Msg m; m.rc = 0; m.vtbl = (P)0x013eb844; m.data0 = entry; m.data1 = hit;
                ((void(__thiscall*)(P, uint, P, int))(*(P**)EA_Messaging_GetServer())[0x14 / 4])
                    (EA_Messaging_GetServer(), 0x3029f12, &m.rc, 0);
                MsgDestruct(&m);
                break;
            }
            case 2: {
                Vec3* pos = mover->GetPosition();
                Vec3 up;
                FUN_00b81630(model, &up, pos);
                float dx = pos->x - up.x, dy = pos->y - up.y, dz = pos->z - up.z;
                if (!(dx * dx + dz * dz + dy * dy < 1.0f) &&
                    !(pos->y * pos->y + pos->z * pos->z + pos->x * pos->x <=
                      up.y * up.y + up.z * up.z + up.x * up.x))
                    break;
                self->AdjustRelationship();
                Vec3 v; mover->GetFacing(&v);
                if (creature) self->OnAgentHitsGround(entry, isAbducting, true);
                if (plant) {
                    if (!self->OnAgentHitsGround(entry, isAbducting, true)) {
                        RemoveNoun(NounManager(), plant);
                    } else {
                        mover->GetFacing(&v);
                        ((void(__thiscall*)(P, uint, P, P))(*(P**)FUN_00b3d240())[0x60 / 4])
                            (FUN_00b3d240(), 0x2818ee0, &v, DAT_016ded38);
                        if (!isAbducting) {
                            Buf16 tmp;
                            P sp0 = GetSpeciesFromID(FUN_00b3d420(), FUN_00c3e1e0(plant, (P)&tmp));
                            Vec3 sp = *(Vec3*)((P(__thiscall*)(P))(*(P**)sp0)[0x18 / 4])(sp0);
                            SetSimPlantAt(cube, &sp, pos, 1);
                            FUN_00c74690(planet, &sp, 1, 0);
                        }
                    }
                }
                if (artifact) {
                    mover->GetFacing(&v);
                    P art = InterfaceCastArtifact(artifact);
                    if (art && *(int*)((char*)art + 0x658) == 4) {
                        Buf16 tmp;
                        if (FUN_004eb930(FUN_00b8dad0(low), FUN_00ad2620(art, (P)&tmp))) {
                            P mgr = ((P(__thiscall*)(P))(*(P**)*(P*)((char*)art + 0x34))[0x2c / 4])((char*)art + 0x34);
                            P x = FUN_00ac9dd0(FUN_00ace2c0(NounManager()), mgr);
                            if (x) {
                                uint cnt = *(uint*)((char*)art + 0x638);
                                FUN_00ff0350(FUN_00bd81f0(x), (float)cnt);
                            }
                        }
                    }
                }
                if (self->IsAgentDone(entry)) self->RemoveAgent(it);
                break;
            }
            }
            goto advance;
        }
    removeAgent:
        self->RemoveAgent(it);
    advance:
        FUN_00abeb20(&it);
    }
    return true;
}
// --- equivalence checker address annotations
    void InterfaceCastArtifact(...); // 0x01030e40
    void MessageServer(...); // 0x0067dcc0
    void PlanetModel(...); // 0x00b3d350
    void operator_new(...); // 0x00f473a0

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}
