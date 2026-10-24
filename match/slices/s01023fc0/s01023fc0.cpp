// Slice s01023fc0: SP::nSpaceCheats::cCommandMission::Execute(cArguments*) @ 0x01023FC0.
// The "mission" cheat console command:
//   mission create <type> | complete <id> | fulfill <id> | abort <id> | fail <id> | list
//         | debugdraw (dd) | next <type> | ui
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc, same cheat-console region as 0x01025840).
#include "s01023fc0.h"

using namespace EA::ArgScript;

namespace SP {
namespace nSpaceCheats {

// @ 0x01023FC0
void cCommandMission::Execute(cArguments* args)
{
    int numArgs = args->NumArguments();
    if (numArgs <= 1)
        return;

    eastl::sim_string sub(args->operator[](1));

    if (sub == "create") {
        if (numArgs > 2) {
            if (SpaceGameGet()) {
                cPlanet* planet = cSPLivingUniverse::GetActivePlanet();
                if (!planet) {
                    Output(mpFormatParser, "You need to be planet-side to create a mission\n");
                    return;
                }
                eastl::string typeName(args->operator[](2));
                void* target = planet->GetOrbitTarget();
                cSPMission* mission = GetMissionManager()->CreateMissionFromID(
                    SPIDFromName(typeName.c_str()), planet->mpPlanetRecord, target, 0);
                if (mission) {
                    mission->Accept();
                    Output(mpFormatParser, "Mission 0x%X is created.\n", mission);
                } else {
                    Output(mpFormatParser, "Mission creation failed, perhaps it was unable to find a suitable planet.\n");
                }
            } else {
                Output(mpFormatParser, "Can only create a mission while on the planet\n");
            }
        } else {
            Output(mpFormatParser, "Usage: mission create <typename>\n");
        }
    } else if (sub == "complete") {
        if (numArgs > 2) {
            uint32_t id = mpFormatParser->ParseInt(args->operator[](2));
            if (id) {
                if (NounManager()) {
                    cSPMission* mission = VerifyMission(id);
                    if (mission) {
                        mission->Complete();
                        Output(mpFormatParser, "Mission 0x%X is completed. \n", mission);
                    } else {
                        Output(mpFormatParser, "No mission with ID:0x%X\n", id);
                    }
                } else {
                    Output(mpFormatParser, "Noun Manager Error\n");
                }
            } else {
                Output(mpFormatParser, "Invalid ID:0x%X\n", 0);
            }
        } else {
            Output(mpFormatParser, "Usage: mission complete <id>\n");
        }
    } else if (sub == "fulfill") {
        if (numArgs > 2) {
            uint32_t id = mpFormatParser->ParseInt(args->operator[](2));
            if (id) {
                if (NounManager()) {
                    cSPMission* mission = VerifyMission(id);
                    if (mission) {
                        mission->Fulfill();
                        Output(mpFormatParser, "Mission 0x%X is fulfilled. \n", mission);
                    } else {
                        Output(mpFormatParser, "No mission with ID:0x%X\n", id);
                    }
                } else {
                    Output(mpFormatParser, "Noun Manager Error\n");
                }
            } else {
                Output(mpFormatParser, "Invalid ID:0x%X\n", 0);
            }
        }
    } else if (sub == "abort") {
        if (numArgs > 2) {
            uint32_t id = mpFormatParser->ParseInt(args->operator[](2));
            if (id) {
                if (NounManager()) {
                    cSPMission* mission = VerifyMission(id);
                    if (mission) {
                        mission->Abort();
                        Output(mpFormatParser, "Mission 0x%X is aborted.\n", mission);
                    } else {
                        Output(mpFormatParser, "No mission with ID:0x%X\n", id);
                    }
                } else {
                    Output(mpFormatParser, "Noun Manager Error\n");
                }
            } else {
                Output(mpFormatParser, "Invalid ID:0x%X\n", 0);
            }
        } else {
            Output(mpFormatParser, "Usage: mission abort <id>\n");
        }
    } else if (sub == "fail") {
        if (numArgs > 2) {
            uint32_t id = mpFormatParser->ParseInt(args->operator[](2));
            if (id) {
                if (NounManager()) {
                    cSPMission* mission = VerifyMission(id);
                    if (mission)
                        mission->Fail();
                    else
                        Output(mpFormatParser, "No mission with ID:0x%X\n", id);
                } else {
                    Output(mpFormatParser, "Noun Manager Error\n");
                }
            } else {
                Output(mpFormatParser, "Invalid ID:0x%X\n", 0);
            }
        } else {
            Output(mpFormatParser, "Usage: mission fail <id>\n");
        }
    } else if (sub == "list") {
        MissionList list(*GetMissionManager()->GetMissionList());
        for (cSPMission** it = list.mpBegin; it != list.mpEnd; ++it) {
            cSPMission* mission = *it;
            eastl::string16 name;
            const char* suffix = mission->mpParentMission ? "(sub-mission)" : "";
            const wchar_t* text = mission->GetName(&name)->c_str();
            Output(mpFormatParser, "\t- ID:0x%X, %ls %s\n", mission, text, suffix);
        }
        Output(mpFormatParser, "Total %d missions. ", list.size());
        Output(mpFormatParser, "(Regular: %d, Event: %d)\n",
            GetMissionManager()->GetNumNonEventMissions(false), GetMissionManager()->GetNumEventMissions());
    } else if (sub == "debugdraw" || sub == "dd") {
        if (GetMissionManager()->ToggleDebugDraw())
            Output(mpFormatParser, "Enabled debug draw mission lines.\n");
        else
            Output(mpFormatParser, "Disabled debug draw mission lines.\n");
    } else if (sub == "next") {
        eastl::string typeName(args->operator[](2));
        GetMissionManager()->SetNextMissionID(SPIDFromName(typeName.c_str()));
    } else if (sub == "ui") {
        GetUIManager()->ShowMissionUI(0);
    } else {
        Output(mpFormatParser, "Command 'mission' did not understand argument");
    }
}

} // namespace nSpaceCheats
} // namespace SP

// ===========================================================================
// Gold7 additions to slice s01023fc0.
// ===========================================================================
namespace SP {
namespace nSpaceCheats {

// --- 0x01024E90 : vector<LayoutNode>::reserve (nodes are 0x1c bytes) -------
struct LayoutNode {
    uint32_t mPad0[3];        // +0x00
    void*    mpSubtree;       // +0x0c
    uint32_t mPad1[3];        // +0x10
};

struct SimAllocHeader { int mSize; };

struct LayoutNodeVec {
    LayoutNode* mpBegin;
    LayoutNode* mpEnd;
    LayoutNode* mpCap;
    void reserve(unsigned n);                                   // 0x01024E90
};

LayoutNode* FUN_01023230(LayoutNode* b, LayoutNode* e, LayoutNode* d);  // 0x01023230
LayoutNode* FUN_01023180(LayoutNode* b, LayoutNode* e, LayoutNode* d);  // 0x01023180

// @ 0x01024E90
void LayoutNodeVec::reserve(unsigned n)
{
    unsigned cap = (unsigned)(mpCap - mpBegin);
    if (n <= cap)
        return;
    LayoutNode* p = n ? (LayoutNode*)operator new[](n * sizeof(LayoutNode),
        "Simulator", 0, 0, EASTL_SIM_FILE, 0xd1) : 0;
    LayoutNode* e = mpEnd;
    LayoutNode* b = mpBegin;
    FUN_01023230(b, e, p);
    FUN_01023180(b, e, p);
    if (mpBegin && ((SimAllocHeader*)mpBegin)[-1].mSize != 0)
        operator delete[](mpBegin);
    unsigned count = (unsigned)(mpEnd - mpBegin);
    mpBegin = p;
    mpEnd = p + count;
    mpCap = p + n;
}

// --- 0x01024920 : introsort pass over an array of ref-counted object slots --
struct LayoutRefObj { virtual void vSlot(); };

typedef int (__cdecl* LayoutRefCmp)(int, int);

int** FUN_01021180(int** a, int** b, int** c, LayoutRefCmp cmp);              // 0x01021180
int** FUN_01023270(int** begin, int** end, int* obj, LayoutRefCmp cmp);      // 0x01023270
void  FUN_010232f0(int** begin, int** end, int** end2, LayoutRefCmp cmp);    // 0x010232f0

// @ 0x01024920
void FUN_01024920(int** begin, int** end, int depth, LayoutRefCmp cmp)
{
    while (((int)((char*)end - (char*)begin) & ~3) > 0x70 && depth > 0) {
        int** p = FUN_01021180(begin, begin + (end - begin) / 2, end - 1, cmp);
        int* obj = *p;
        if (obj)
            ((LayoutRefObj*)obj)->vSlot();
        int** pivot = FUN_01023270(begin, end, obj, cmp);
        --depth;
        FUN_01024920(pivot, end, depth, cmp);
        end = pivot;
    }
    if (depth == 0)
        FUN_010232f0(begin, end, end, cmp);
}

// --- 0x01024630 / 0x010249F0 : space cheat commands ------------------------
int   FUN_01021240();                                                       // 0x01021240
void* FUN_010212a0();                                                       // 0x010212a0
eastl::string16* ConvertToString16(eastl::string16* dst, const eastl::sim_string* src); // 0x0093c6d0
extern "C" __declspec(dllimport) int __cdecl tolower(int c);

struct RenameStarRecord {
    void Rename(eastl::string16* name);                                     // 0x00bba4b0
};

struct RenamePlanetRecord {
    uint32_t mPad0[0xb];                                                    // +0x00 .. +0x2b
    unsigned char mFlags;                                                   // +0x2c
    void Rename(eastl::string16* name);                                     // 0x00b8e3f0
};

struct PlanetKeyNode {
    PlanetKeyNode* mpLeft;                                                  // +0x00
    PlanetKeyNode* mpRight;                                                 // +0x04
    PlanetKeyNode* mpParent;                                                // +0x08
    uint32_t       mColor;                                                  // +0x0c
    uint32_t       mKey;                                                    // +0x10
};

struct PlanetKeySet {
    PlanetKeyNode* mpSentinel;                                              // +0x00
    PlanetKeyNode* mpBegin;                                                 // +0x04
    PlanetKeyNode* mpRoot;                                                  // +0x08
    uint32_t       mColor;                                                  // +0x0c
    void Init(uint32_t key);                                                // 0x00d01a40
    void DoNukeSubtree(PlanetKeyNode* node);                                // 0x009a9600
};

struct PlanetKeyIter {
    PlanetKeyNode* mpNode;
    void Increment();                                                       // 0x01022b90
};

struct cPlayerTribe {
    uint32_t GetPlanetKey();                                                // 0x00b7e380
    void     UnlockBadge(uint32_t id);                                      // 0x00fe5a20
    int      CheckBadge(uint32_t id, int n);                                // 0x00fe45f0
    void     GrantBadge(int id, int n);                                     // 0x00fe5430
};

struct cSpaceGameImpl {
    cPlayerTribe* GetPlayerTribe();                                         // 0x00bfc5f0
};

struct cCommandCheat {
    virtual void vf00();
    virtual const char* vf04(int arg);
    EA::ArgScript::FormatParser* mpFormatParser;                            // +0x04
    void Rename(EA::ArgScript::cArguments* args);                           // 0x01024630
    void Badge(EA::ArgScript::cArguments* args);                            // 0x010249F0
};

// @ 0x01024630
void cCommandCheat::Rename(EA::ArgScript::cArguments* args)
{
    int n = args->NumArguments();
    if (n != 3) {
        if (n == 1)
            Output(mpFormatParser, vf04(1));
        else
            Output(mpFormatParser, "Error: must have two arguments\n");
        return;
    }
    eastl::sim_string which(args->operator[](1));
    eastl::sim_string name(args->operator[](2));
    for (char* p = which.mpBegin; p < which.mpEnd; ++p)
        *p = (char)tolower((unsigned char)*p);
    if (which == "star") {
        RenameStarRecord* rec = (RenameStarRecord*)FUN_01021240();
        if (!rec) {
            Output(mpFormatParser, "Error: must be at a star\n");
        } else {
            eastl::string16 name16;
            rec->Rename(ConvertToString16(&name16, &name));
        }
    } else if (which == "planet") {
        RenamePlanetRecord* rec = (RenamePlanetRecord*)FUN_010212a0();
        if (!rec) {
            Output(mpFormatParser, "Error: must be at a planet\n");
        } else if (rec->mFlags & 1) {
            Output(mpFormatParser, "Error: you cannot rename a saved game\n");
        } else {
            eastl::string16 name16;
            rec->Rename(ConvertToString16(&name16, &name));
        }
    } else {
        Output(mpFormatParser, "Error: first argument must be 'star' or 'planet'\n");
    }
}

// @ 0x010249F0
void cCommandCheat::Badge(EA::ArgScript::cArguments* args)
{
    cSpaceGameImpl* game = (cSpaceGameImpl*)SpaceGameGet();
    cPlayerTribe* tribe = game->GetPlayerTribe();
    eastl::sim_string which(args->operator[](1));
    int badge = (int)(unsigned)args;   // unmatched names keep the args pointer (as in the binary)
    if (which == "colonize")
        badge = 0;
    else if (which == "rare")
        badge = 0xb;
    else if (which == "eco")
        badge = 9;
    else if (which == "alliance")
        badge = 1;
    else if (which == "terraform")
        badge = 3;
    else if (which == "explore")
        badge = 2;
    else if (which == "empire")
        badge = 4;
    else if (which == "war")
        badge = 5;
    else if (which == "fetch")
        badge = 7;
    else if (which == "eradicate")
        badge = 8;
    else if (which == "foodweb")
        badge = 0xa;
    else if (which == "mission")
        badge = 0xe;
    else if (which == "trade")
        badge = 0xd;
    else if (which == "defeatgrob")
        badge = 0xf;
    else if (which == "allygrob")
        badge = 0x10;
    else if (which == "flight101")
        badge = 0x11;
    else if (which == "archetype")
        badge = 0x1e;
    else if (which == "defend")
        badge = 0x12;
    else if (which == "level") {
        if (args->operator[](2) != 0) {
            int level = mpFormatParser->ParseInt(args->operator[](2));
            PlanetKeySet set;
            set.Init(tribe->GetPlanetKey());
            PlanetKeyNode* it = set.mpBegin;
            while (it != (PlanetKeyNode*)&set) {
                uint32_t id = it->mKey;
                if (tribe->CheckBadge(id, 1) == level)
                    tribe->UnlockBadge(id);
                PlanetKeyIter iter;
                iter.mpNode = it;
                iter.Increment();
                it = iter.mpNode;
            }
            set.DoNukeSubtree(set.mpRoot);
            badge = (int)(unsigned)args;   // original keeps the args pointer in this slot
        }
    }
    if (args->operator[](2) != 0) {
        for (int k = mpFormatParser->ParseInt(args->operator[](2)); k != 0; --k)
            tribe->GrantBadge(badge, 1);
    }
}

} // namespace nSpaceCheats
} // namespace SP
