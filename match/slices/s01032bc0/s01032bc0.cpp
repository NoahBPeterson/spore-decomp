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

void   __fastcall FUN_00abf010(Range* out, int, P agentList, Abducted** pthis);  // build [begin,end) over agents
void   __fastcall FUN_00abeb20(Range* it, int);                                  // advance iterator
P      GetActivePlanet();                   // SP::cSPLivingUniverse::GetActivePlanet
P      __fastcall FUN_008414c0(P planet, int);
P      PlanetModel();   // 0x00b3d350 SP::PlanetModel
void   __fastcall FUN_00b81630(P model, int, Vec3* out, const Vec3* pos);
void   __fastcall GetEndPoints(P beam, int, Vec3* a, Vec3* b);   // 0x00cb8ba0 SP::cDefaultBeamProjectile::GetEndPoints
P      GetUFOSimulator();   // 0x00ffbe50 SP::GetUFOSimulator
P      __fastcall GetPlayerInventory(P sim, int);   // 0x00a1ad60 SP::cSPSimulatorSpaceGame::GetPlayerInventory
P      SpaceGameGet();                      // SP::SpaceGameGet
P      GetRecorderState();   // 0x00435e90
void   KillSetiEffects(uint id, P rec);   // 0x00435ed0 SP::cSPUISpace::KillSetiEffects
P      EA_Messaging_GetServer();   // 0x00883860 EA::Messaging::GetServer
P      MessageServer();   // 0x0067dcc0 SP::MessageServer
P      NounManager(P noun);                 // SP::NounManager
void   __fastcall RemoveNoun(P mgr, int);        // 0xb225d0 (stack arg = noun passed to NounManager)
P      StarManager();   // 0x00b3d2a0 SP::StarManager
int    __fastcall FUN_00885c90(P mgr, int);
P      EventLog(uint a, uint b, int c, int d, int e, int f);   // 0x00b3d3e0 SP::EventLog
void   __fastcall PostFeedbackEvent(P log, int);   // 0x00dd8640 SP::cSPUIEventLog::PostFeedbackEvent
P      __fastcall FUN_00c0bc00(P creature, int, int a, int b);
P      __fastcall FUN_00c463d0(P slot, int, P arg);
P      FUN_00b3d450(P x);
P      __fastcall MakeInventoryItemFromSpecies(P mgr, int);
bool   __fastcall SetSpeciesAsScanned(P planet, int, P species);  // SP::cPlanet::SetSpeciesAsScanned
void   FUN_01058660(P creature, int flag);
void   __fastcall FUN_00c74690(P planet, int, P x);
P      __fastcall FUN_00c3e1e0(P noun, int, P out);
P      FUN_00b3d420(P x);
P      __fastcall GetSpeciesFromID(P mgr, int);  // SP::cPlantSpeciesManager::GetSpeciesFromID
P      __fastcall FUN_01015df0(P a, int, int b);
void   __fastcall RemoveHighLODPlant(P walkAround, int);
void   FUN_010527f0(P a, uint b, int c);
void   __fastcall InterruptAnimation(P creature, int, uint id, int a, int b);  // SP::cSPCreatureBase::InterruptAnimation
void   __fastcall FUN_00c421b0(P mover, int, P locomotion);
void   __fastcall FUN_00c14750(P creature, int, int a);
P      FUN_00b3d240();
P      FUN_00b3d480(P x);
void   __fastcall FUN_00aca360(P x, int);
P      FUN_00b3d3b0(P x);
void   __fastcall FUN_00b2d910(P x, int);
void   __fastcall SetSimAnimalAt(P cube, int, P a, P pos, int flag);
void   __fastcall SetSimPlantAt(P low, int, P a, P pos, int flag);
void   SetZooMarker(P low, P a);
P      __fastcall FUN_00ce6950(P tree, int, uint key);
P      __fastcall GetCurrentTerrainSphere(P terrainEditor, int);
char   __fastcall FUN_00c830b0(P x, int);
void   __fastcall FUN_00c830d0(P x, int, char v);
P      __fastcall FUN_00bfc5f0(P game, int);  // Simulator::cGameData::SetGameDataOwner2
void   __fastcall FUN_00fe5430(P x, int, int a, int b);
P      __fastcall FUN_00ad2620(P artifact, int, P out);
P      __fastcall FUN_00b8dad0(P low, int, P a);
bool   FUN_004eb930(P a, P b);
P      __fastcall FUN_00ace2c0(P mgr, int);
P      FUN_00ac9dd0(P a, P b);
P      __fastcall FUN_00bd81f0(P x, int, float f);
void   __fastcall FUN_00ff0350(P x, int);
P      __fastcall FUN_00c31a00(P x, int);
P      GetPlayerEmpire(uint id);   // 0x01021300 SP::cSPLivingUniverse::GetPlayerEmpire
void   __fastcall FUN_00fffdd0(P ufo, int, int a, uint b);
P      FUN_00b3d3d0(int a, P b);
void   __fastcall CollectSpicePile(P x, int);   // 0x0103fe90 SP::cSPSpaceTrading::CollectSpicePile
bool   __fastcall IsRare(P artifact, int);   // 0x00c74ca0 SP::cSPPlanetaryArtifact::IsRare
int    __fastcall FUN_0103ac40(P x, int);
void   __fastcall FUN_00c389c0(P inv, int, int a, int b);
bool   FUN_005f78f0(P a, P b);              // EA::ResourceMan::operator!=
P      FUN_00b3d390(P a, P out);
bool   __fastcall CreateToolFromToolID(P mgr, int);   // 0x0104e340
P      FUN_01005180(P x, int a);
void   __fastcall FUN_007eb820(P x, int, int a);
void   FUN_00c878d0(Vec3 key, P out);
void   RemoveArtifact(P low, P a, uint count);   // 0x00c71160 SP::RemoveArtifact
P      InterfaceCastArtifact(P noun);   // 0x01030e40 EA::COM::interface_cast<cSPPlanetaryArtifact*, ...>
extern uint  g_Msg_vtbl;                    // vtbl_UI::BehaviorMessage / message vtable
extern P     g_spaceTokenTranslator;   // 0x016e0d08 _gpSpaceTokenTranslator_SP__3PAVcSpaceTokenTranslator_1_A
extern char  DAT_016ded38[], DAT_016ded44[];
void   __fastcall MsgConstruct(P msg, int, int a);   // 0x00421c80 SlotMessage::Construct
void   __fastcall MsgDestruct(P msg, int);           // SlotMessage::Destruct
void*  operator_new(uint size, const char* name, int a, int b, int c, int d);   // 0x00f473a0

// Message block as laid out on the stack (0x40 bytes).
struct Msg {
    P vtbl; int rc; P data0; int pad0; uint data1; uint pad[8]; int tail0; int pad1; int tail1;
};

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
    char pad[0x5a8]; int fileIndex;    // +0x5a8 (PFIndexModifiable)
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
    Range it;
    FUN_00abf010(&it, 0, (P)agentList, &self);
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
    P cube = FUN_008414c0(planet, 0);
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
                FUN_00c421b0((P)mover, 0, (P)loco);
                if (creature) {
                    InterruptAnimation(creature, 0, 0x3cc7ebb, -1, 0);
                    ((void(__thiscall*)(P, int))(*(P**)creature)[0x9c / 4])(creature, 0);
                }
            }

            switch (state) {
            case 0: {
                if (!beam) break;
                Vec3 endA, endB;
                GetEndPoints(beam, 0, &endA, &endB);
                Vec3* pos = mover->GetPosition();
                float dx = pos->x - endA.x, dz = pos->z - endA.z, dy = pos->y - endA.y;
                if (!(dx * dx + dz * dz + dy * dy < 6.0f)) break;

                P item = 0;
                P ufo = GetUFOSimulator();
                if (ufo) {
                    P inv = GetPlayerInventory(GetUFOSimulator(), 0);
                    P invp = inv ? (P)((char*)inv + 0x34) : 0;
                    P owner = *(P*)((char*)*(P*)((char*)beam + 0x134) + 0x114);
                    if (owner == invp) {
                        P sg = SpaceGameGet();
                        P playerInv = 0;
                        if (sg && (playerInv = GetPlayerInventory(sg, 0)) != 0) {
                            KillSetiEffects(0x9fbe154b, GetRecorderState());
                            if (creature) {
                                Msg m; MsgConstruct(&m.rc, 0, 0); m.data0 = entry;
                                ((void(__thiscall*)(P, uint, P, int))(*(P**)EA_Messaging_GetServer())[0x14 / 4])
                                    (EA_Messaging_GetServer(), 0x3029f11, &m.rc, 0);
                                bool big = ((ICreature*)creature)->fileIndex != 2;
                                bool done = false;
                                if (flag) {
                                    int id = FUN_00885c90(StarManager(), 0);
                                    if (flag->GetId() == id) {
                                        PostFeedbackEvent(EventLog(0x49256302, 0x131a9f54, 0, 0, 1, 0), 0);
                                        MsgDestruct(&m, 0);
                                        done = true;
                                    }
                                }
                                if (!done) {
                                    if (big) {
                                        P slot = FUN_00c463d0(&entry, 0, FUN_00c0bc00(creature, 0, 1, flag != 0));
                                        item = MakeInventoryItemFromSpecies(FUN_00b3d450(slot), 0);
                                        if (item) {
                                            if (flag) {
                                                // stamp the empire/species id on the item
                                                *(int*)((char*)item + 0x20) = flag->GetId();
                                                MsgDestruct(&m, 0);
                                                done = true;
                                            } else {
                                                P kind = ((IItem*)item)->GetKind(0, 0);
                                                if (!SetSpeciesAsScanned(cube, 0, kind)) {
                                                    FUN_01058660(creature, 1);
                                                    P k2 = ((IItem*)item)->GetKind(1, 1);
                                                    FUN_00c74690(cube, 0, k2);
                                                }
                                            }
                                        }
                                    }
                                    if (!done) MsgDestruct(&m, 0);
                                }
                            } else if (plant) {
                                Msg dummy; (void)dummy;
                                P noun = plant;
                                P species = GetSpeciesFromID(FUN_00b3d420(FUN_00c3e1e0(noun, 0, 0)), 0);
                                if (species) {
                                    P slot = FUN_00c463d0(&item, 0, 0);
                                    ((void(__thiscall*)(P, P))(*(P**)species)[0x24 / 4])(species, slot);
                                    RemoveHighLODPlant(FUN_01015df0(noun, 0, 0), 0);
                                    P k = ((IItem*)item)->GetKind(1, 1);
                                    FUN_00c74690(cube, 0, k);
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
                    Msg m; MsgConstruct(&m.rc, 0, 0); m.data0 = entry;
                    ((void(__thiscall*)(P, uint, P, int))(*(P**)EA_Messaging_GetServer())[0x14 / 4])
                        (EA_Messaging_GetServer(), 0x3029f11, &m.rc, 0);
                    FUN_00b2d910(FUN_00b3d3b0(plant), 0);
                    MsgDestruct(&m, 0);
                }
                if (artifact) {
                    P art = InterfaceCastArtifact(artifact);
                    if (art) {
                        switch (*(int*)((char*)art + 0x658)) {
                        case 7:
                            FUN_00c31a00(GetPlayerEmpire(*(uint*)((char*)art + 0x638)), 0);
                            FUN_00fffdd0(GetUFOSimulator(), 0, 0, *(uint*)((char*)art + 0x638));
                            break;
                        case 4:
                            if (GetUFOSimulator()) {
                                P inv = GetPlayerInventory(GetUFOSimulator(), 0);
                                P invp = inv ? (P)((char*)inv + 0x34) : 0;
                                P owner = *(P*)((char*)*(P*)((char*)beam + 0x134) + 0x114);
                                if (owner == invp) {
                                    char tmp[16];
                                    if (FUN_005f78f0(FUN_00ad2620(art, 0, tmp), DAT_016ded44) &&
                                        *(uint*)((char*)art + 0x638) != 0) {
                                        P tool = 0;
                                        P mgr = FUN_00b3d390(FUN_00ad2620(art, 0, tmp), FUN_00c463d0(&tool, 0, 0));
                                        if (CreateToolFromToolID(mgr, 0)) {
                                            FUN_00c389c0(GetPlayerInventory(GetUFOSimulator(), 0), 0, 5, 1);
                                            *(int*)((char*)tool + 0x7c) = *(int*)((char*)art + 0x638);
                                            IItem* pi = (IItem*)GetPlayerInventory(SpaceGameGet(), 0);
                                            pi->PutBack(tool, 0, 1);
                                            P ui = FUN_01005180(SpaceGameGet(), 0xf);
                                            FUN_007eb820(ui, 0, 9);
                                            P* kind = (P*)((P(__thiscall*)(P))(*(P**)tool)[0x18 / 4])(tool);
                                            *(P*)(*(char**)((char*)ui + 0xc) + 0x1c) = *kind;
                                            *(int*)(*(char**)((char*)ui + 0xc) + 0x20) = 3;
                                            *(P*)((char*)g_spaceTokenTranslator + 0x14) = tool;
                                            PostFeedbackEvent(EventLog(0x15e1a624, 0x131a9f54, 0, 0, 1, 0), 0);
                                        }
                                        if (tool) ((IObject*)tool)->Release();
                                    }
                                }
                            }
                            break;
                        case 5:
                            if (GetUFOSimulator()) {
                                P inv = GetPlayerInventory(GetUFOSimulator(), 0);
                                P invp = inv ? (P)((char*)inv + 0x34) : 0;
                                P owner = *(P*)((char*)*(P*)((char*)beam + 0x134) + 0x114);
                                if (owner == invp) {
                                    char tmp[16];
                                    P tool = 0;
                                    Vec3 key = *(Vec3*)FUN_00ad2620(art, 0, tmp);
                                    FUN_00c878d0(key, FUN_00c463d0(&tool, 0, 0));
                                    if (tool) {
                                        IItem* pi = (IItem*)GetPlayerInventory(SpaceGameGet(), 0);
                                        pi->PutBack(tool, 0, 1);
                                        if (tool) ((IObject*)tool)->Release();
                                    }
                                }
                            }
                            break;
                        case 2:
                            if (GetUFOSimulator()) {
                                P inv = GetPlayerInventory(GetUFOSimulator(), 0);
                                P invp = inv ? (P)((char*)inv + 0x34) : 0;
                                P owner = *(P*)((char*)*(P*)((char*)beam + 0x134) + 0x114);
                                if (owner == invp) {
                                    CollectSpicePile(FUN_00b3d3d0(1, art), 0);
                                    if (IsRare(art, 0)) {
                                        char tmp[16];
                                        if (FUN_0103ac40(FUN_00b3d3d0(0, FUN_00ad2620(art, 0, tmp)), 0) != 1)
                                            FUN_00c389c0(GetPlayerInventory(GetUFOSimulator(), 0), 0, 7, 1);
                                    }
                                }
                            }
                            break;
                        }
                        Msg m; MsgConstruct(&m.rc, 0, 0); m.data0 = entry;
                        ((void(__thiscall*)(P, uint, P, int))(*(P**)EA_Messaging_GetServer())[0x14 / 4])
                            (EA_Messaging_GetServer(), 0x3029f11, &m.rc, 0);
                        char tmp[16];
                        RemoveArtifact(low, FUN_00ad2620(art, 0, tmp), *(uint*)((char*)art + 0x638));
                        MsgDestruct(&m, 0);
                    }
                    RemoveNoun(NounManager(artifact), 0);
                }
                break;
            }
            case 1: {
                Vec3* pos = mover->GetPosition();
                Vec3 up;
                FUN_00b81630(model, 0, &up, pos);
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
                            FUN_00c14750(creature, 0, 1);
                            int before = (int)(((int*)low)[0xd4 / 4] - ((int*)low)[0xd0 / 4]) / 12;
                            Vec3 v; mover->GetFacing(&v);
                            ((void(__thiscall*)(P, uint, P, P))(*(P**)FUN_00b3d240())[0x60 / 4])
                                (FUN_00b3d240(), 0x2818ee0, &v, DAT_016ded38);
                            if (*(uint*)((char*)low + 0x2c) & 0x800)
                                SetZooMarker(low, FUN_00c0bc00(creature, 0, (int)pos, (int)creature));
                            FUN_00aca360(FUN_00b3d480(creature), 0);
                            SetSimAnimalAt(cube, 0, FUN_00c0bc00(creature, 0, (int)pos, 1), pos, 1);
                            if (!SetSpeciesAsScanned(low, 0, FUN_00c0bc00(creature, 0, 0, 0)))
                                FUN_01058660(creature, 0);
                            FUN_00c74690(cube, 0, FUN_00c0bc00(creature, 0, 1, 0));
                            if (!(*(uint*)((char*)low + 0x2c) & 0x800)) {
                                int after = (int)(((int*)low)[0xd4 / 4] - ((int*)low)[0xd0 / 4]) / 12;
                                if (before != after) {
                                    char cnt = (char)(after / 3);
                                    P sphere = GetCurrentTerrainSphere(NounManager(FUN_00ce6950(low, 0, 0)), 0);
                                    if (FUN_00c830b0(sphere, 0) < cnt) {
                                        FUN_00c830d0(GetCurrentTerrainSphere(NounManager(FUN_00ce6950(low, 0, cnt)), 0), 0, cnt);
                                        P owner = FUN_00bfc5f0(SpaceGameGet(), 0);
                                        if (owner) FUN_00fe5430(owner, 0, 10, 1);
                                        ((void(__thiscall*)(P, uint, int, int))(*(P**)MessageServer())[0x14 / 4])
                                            (MessageServer(), 0xf46092d5, 0, 0);
                                    }
                                }
                            }
                        }
                    } else {
                        hit = self->OnAgentHitsGround(entry, isAbducting, false);
                        if (hit) {
                            FUN_00c14750(creature, 0, 1);
                            Vec3 v; mover->GetFacing(&v);
                            ((void(__thiscall*)(P, uint, P, P))(*(P**)FUN_00b3d240())[0x60 / 4])
                                (FUN_00b3d240(), 0x2818ee0, &v, DAT_016ded38);
                            FUN_00aca360(FUN_00b3d480(creature), 0);
                        }
                    }
                }
                if (plant) {
                    char tmp[16];
                    P species = GetSpeciesFromID(FUN_00b3d420(FUN_00c3e1e0(plant, 0, tmp)), 0);
                    Vec3 sp = *(Vec3*)((P(__thiscall*)(P))(*(P**)species)[0x18 / 4])(species);
                    hit = self->OnAgentHitsGround(entry, isAbducting, false);
                    if (!hit) {
                        RemoveNoun(NounManager(plant), 0);
                    } else {
                        Vec3 v; mover->GetFacing(&v);
                        ((void(__thiscall*)(P, uint, P, P))(*(P**)FUN_00b3d240())[0x60 / 4])
                            (FUN_00b3d240(), 0x2818ee0, &v, DAT_016ded38);
                        SetSimPlantAt(cube, 0, &sp, pos, 1);
                        FUN_00c74690(cube, 0, &sp);
                    }
                }
                if (artifact) {
                    Vec3 v; mover->GetFacing(&v);
                    ((void(__thiscall*)(P, uint, P, P))(*(P**)FUN_00b3d240())[0x60 / 4])
                        (FUN_00b3d240(), 0x2818ee0, &v, DAT_016ded38);
                    P art = InterfaceCastArtifact(artifact);
                    if (art && *(int*)((char*)art + 0x658) == 4) {
                        char tmp[16];
                        if (FUN_004eb930(FUN_00b8dad0(*(P*)((char*)planet + 0x13c), 0, FUN_00ad2620(art, 0, tmp)), 0)) {
                            P mgr = ((P(__thiscall*)(P))(*(P**)*(P*)((char*)art + 0x34))[0x2c / 4])((char*)art + 0x34);
                            P x = FUN_00ac9dd0(FUN_00ace2c0(NounManager(mgr), 0), 0);
                            if (x) {
                                uint cnt = *(uint*)((char*)art + 0x638);
                                FUN_00ff0350(FUN_00bd81f0(x, 0, (float)cnt), 0);
                            }
                        }
                    }
                    if (!(art && *(int*)((char*)art + 0x658) == 4))
                        RemoveNoun(NounManager(artifact), 0);
                }
                if (self->IsAgentDone(entry)) self->RemoveAgent(it);
                Msg m; m.rc = 0; m.vtbl = (P)0x013eb844; m.data0 = entry; m.data1 = hit;
                ((void(__thiscall*)(P, uint, P, int))(*(P**)EA_Messaging_GetServer())[0x14 / 4])
                    (EA_Messaging_GetServer(), 0x3029f12, &m.rc, 0);
                MsgDestruct(&m, 0);
                break;
            }
            case 2: {
                Vec3* pos = mover->GetPosition();
                Vec3 up;
                FUN_00b81630(model, 0, &up, pos);
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
                        RemoveNoun(NounManager(plant), 0);
                    } else {
                        mover->GetFacing(&v);
                        ((void(__thiscall*)(P, uint, P, P))(*(P**)FUN_00b3d240())[0x60 / 4])
                            (FUN_00b3d240(), 0x2818ee0, &v, DAT_016ded38);
                        if (!isAbducting) {
                            char tmp[16];
                            P sp0 = GetSpeciesFromID(FUN_00b3d420(FUN_00c3e1e0(plant, 0, tmp)), 0);
                            Vec3 sp = *(Vec3*)((P(__thiscall*)(P))(*(P**)sp0)[0x18 / 4])(sp0);
                            SetSimPlantAt(low, 0, &sp, plant, 1);
                            FUN_00c74690(cube, 0, &sp);
                        }
                    }
                }
                if (artifact) {
                    mover->GetFacing(&v);
                    P art = InterfaceCastArtifact(artifact);
                    if (art && *(int*)((char*)art + 0x658) == 4) {
                        char tmp[16];
                        if (FUN_004eb930(FUN_00b8dad0(low, 0, FUN_00ad2620(art, 0, tmp)), 0)) {
                            P mgr = ((P(__thiscall*)(P))(*(P**)*(P*)((char*)art + 0x34))[0x2c / 4])((char*)art + 0x34);
                            P x = FUN_00ac9dd0(FUN_00ace2c0(NounManager(mgr), 0), 0);
                            if (x) {
                                uint cnt = *(uint*)((char*)art + 0x638);
                                FUN_00ff0350(FUN_00bd81f0(x, 0, (float)cnt), 0);
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
        FUN_00abeb20(&it, 0);
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
