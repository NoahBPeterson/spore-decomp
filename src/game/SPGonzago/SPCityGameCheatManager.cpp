// Object file: SPGonzago/SPCityGameCheatManager.obj
// The commands a city game registers with the cheat manager, and the manager
// destructor that unregisters them again.

#include "game/types.h"
#include "EA/ArgScript/cArguments.h"
#include "EA/ArgScript/cIParser.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void  FUN_00e94a00();  // 0x00e94a00  cVehicleView::ToggleShowPaths
extern "C" void  FUN_00cac1a0();  // 0x00cac1a0  cVehicle::DebugChangeWeapons (cdecl 1)
extern "C" void *FUN_0067de20();  // 0x0067de20  SP::CheatManager
extern "C" void *FUN_00f473a0();  // 0x00f473a0  operator_new(size,file,0,0,0,0)
extern "C" void *FUN_0083c800();  // 0x0083c800  cCommandBase::cCommandBase (ecx)
extern "C" void *FUN_00b3d300();  // 0x00b3d300  SP::NounManager
extern "C" void *FUN_00b21340();  // 0x00b21340  cGameNounManager::GetGameDataVector (ecx, 5)
extern "C" void *FUN_00b25c30();  // 0x00b25c30  (ecx = noun manager)
extern "C" void  FUN_00be1340();  // 0x00be1340  (ecx = manager)
extern "C" void FUN_00cd7d10();  // 0x00cd7d10
extern "C" void FUN_00d3d420();  // 0x00d3d420
extern "C" void FUN_00acdff0();  // 0x00acdff0
extern "C" void FUN_00b1e500();  // 0x00b1e500
extern "C" void *g_cmdMakeTradeRoutes;      // 0x0158167c
extern "C" void *g_cmdToggleShowPaths;      // 0x01581680
extern "C" void *g_cmdSetVehicleWeapons;    // 0x01581684
extern "C" char  g_dat018c43e8;             // 0x018c43e8

typedef unsigned int   u32;
typedef unsigned char  u8;

// The three command objects the city game's Simulator::cCivModeStrategy registers.
enum {
    kCommandSize      = 0x10,        // sizeof(EA::ArgScript::cCommandBase)
    kRegisterFile     = 0x13f09b4,   // allocator tag ("Simulator")
};

// vtable addresses of the command classes (read from the retail image)
#define kVTblToggleShowPaths     0x14781d4
#define kVTblSetVehicleWeapons   0x14781bc
#define kVTblMakeTradeRoutes     0x14781ec

// The city game's three cheat commands.  Only the vtable pointer layout
// matters here: cCommandSetVehicleWeapons keeps the parser it registered with.
struct cCommandToggleShowPaths {
    void Execute(void *args);
};

struct cCommandSetVehicleWeapons {
    void **m_vtbl00;                          // +0x00
    EA::ArgScript::cIParser *m_parser;        // +0x04
    void Execute(void *args);
};

struct cCommandMakeTradeRoutes {
    void Execute(void *args);
};

// SP::CheatManager, viewed only through its "unregister a command" slot.
struct CheatManagerObj { void **m_vtbl00; };

struct cCityGameCheatManager {
    ~cCityGameCheatManager();
};

// A cCommandBase-derived command object, plus the members the constructor sets.
struct CommandObj {
    void **m_vtbl00;
    void *m_field04;
    int   m_refCount;
};

// eastl::vector<void*> as the noun manager returns it.
struct GameDataVec {
    u32    m_field00;
    void **mpBegin;   // +0x04
    void **mpEnd;     // +0x08
};

namespace Simulator {
struct cCivModeStrategy {
    cCivModeStrategy();
};
}

// @ 0x00cedff0
void cCommandToggleShowPaths::Execute(void *args)
{
    FUN_00e94a00();
}

// @ 0x00cee010
void cCommandSetVehicleWeapons::Execute(void *args)
{
    EA::ArgScript::cArguments *pArgs = (EA::ArgScript::cArguments *)args;
    if (pArgs->NumArguments() > 1) {
        void **vt = *(void ***)m_parser;
        char const *pName = (*pArgs)[1];
        void *pResult = ((void *(__thiscall *)(void *, void *))vt[0x9c / 4])(m_parser, (void *)pName);
        ((void(__cdecl *)(void *))FUN_00cac1a0)(pResult);
    }
}

// @ 0x00cee060
cCityGameCheatManager::~cCityGameCheatManager()
{
    CheatManagerObj *cm = (CheatManagerObj *)FUN_0067de20();
    ((void(__thiscall *)(void *, void *))cm->m_vtbl00[0x1c / 4])(cm, g_cmdMakeTradeRoutes);
    ((void(__thiscall *)(void *, void *))cm->m_vtbl00[0x1c / 4])(cm, g_cmdToggleShowPaths);
    ((void(__thiscall *)(void *, void *))cm->m_vtbl00[0x1c / 4])(cm, g_cmdSetVehicleWeapons);
}

// @ 0x00cee130
Simulator::cCivModeStrategy::cCivModeStrategy()
{
    CommandObj *c;

    FUN_0067de20();

    c = (CommandObj *)((void *(__cdecl *)(u32, void *, u32, u32, u32, u32))FUN_00f473a0)
            (kCommandSize, (void *)kRegisterFile, 0, 0, 0, 0);
    if (c) {
        ((void *(__thiscall *)(void *))FUN_0083c800)(c);
        c->m_vtbl00 = (void **)kVTblToggleShowPaths;
    }

    c = (CommandObj *)((void *(__cdecl *)(u32, void *, u32, u32, u32, u32))FUN_00f473a0)
            (kCommandSize, (void *)kRegisterFile, 0, 0, 0, 0);
    if (c) {
        ((void *(__thiscall *)(void *))FUN_0083c800)(c);
        c->m_vtbl00 = (void **)kVTblSetVehicleWeapons;
    }

    c = (CommandObj *)((void *(__cdecl *)(u32, void *, u32, u32, u32, u32))FUN_00f473a0)
            (kCommandSize, (void *)kRegisterFile, 0, 0, 0, 0);
    if (c) {
        ((void *(__thiscall *)(void *))FUN_0083c800)(c);
        c->m_vtbl00 = (void **)kVTblMakeTradeRoutes;
    }
}

// @ 0x00cee1c0
void cCommandMakeTradeRoutes::Execute(void *args)
{
    GameDataVec *v;
    void *mgr;
    int count;
    int i;

    v = (GameDataVec *)((void *(__thiscall *)(void *, void *, void *, void *, void *, void *))FUN_00b21340)
            ((void *)FUN_00b3d300(),
             (void *)FUN_00cd7d10, (void *)FUN_00d3d420,
             (void *)FUN_00acdff0, (void *)FUN_00b1e500,
             &g_dat018c43e8);

    mgr = ((void *(__thiscall *)(void *))FUN_00b25c30)((void *)FUN_00b3d300());
    if (mgr) {
        count = (int)(v->mpEnd - v->mpBegin);
        for (i = 0; i < count; ++i) {
            void *obj = v->mpBegin[i];
            u8 *pSpatial = (u8 *)obj + 0x120;   // the object's cSpatialObject sub-object
            char c = ((char(__thiscall *)(void *))(*(void ***)pSpatial)[0x58 / 4])(pSpatial);
            if (!c)
                ((void(__thiscall *)(void *, void *, u32))FUN_00be1340)(mgr, obj, 0);
        }
    }
}
