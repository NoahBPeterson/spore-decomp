// src/game/SPGonzago/SPCityGameCheatManager.cpp -- migrated from slice(s) s00cedff0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPCityGameCheatManager.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cGameBundleContainer.h"
#include "SP/cVarListSerializer.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void  FUN_00e94a00();  // 0x00e94a00  cVehicleView::ToggleShowPaths
extern "C" int   FUN_00837f30();  // 0x00837f30  cArguments::NumArguments (ecx)
extern "C" void *FUN_00837f20();  // 0x00837f20  cArguments::operator[] (ecx)
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

// ---- items of slice s00cedff0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int   u32;
typedef unsigned char  u8;
extern "C" void  FUN_00e94a00();  // 0x00e94a00  cVehicleView::ToggleShowPaths
extern "C" int   FUN_00837f30();  // 0x00837f30  cArguments::NumArguments (ecx)
extern "C" void *FUN_00837f20();  // 0x00837f20  cArguments::operator[] (ecx)
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
struct ArgParser { void **m_vtbl00; };
struct cCommandToggleShowPaths {
    void Execute(void *args);
};
struct cCommandSetVehicleWeapons {
    void **m_vtbl00;   // +0x00
    ArgParser *m_parser; // +0x04
    void Execute(void *args);
};
struct cCommandMakeTradeRoutes {
    void Execute(void *args);
};
struct CheatManagerObj { void **m_vtbl00; };
struct cCityGameCheatManager {
    ~cCityGameCheatManager();
};
struct CommandObj {
    void **m_vtbl00;
    void *m_field04;
    int   m_refCount;
};
struct GameDataVec {
    u32    m_field00;
    void **mpBegin;   // +0x04
    void **mpEnd;     // +0x08
};
struct cCommandToggleShowPaths;
namespace Simulator {
struct cCivModeStrategy {
    cCivModeStrategy();
};
}
// ---- items of slice s00cedff0 end

// @ 0x00cedff0
void cCommandToggleShowPaths::Execute(void *args)
{
    FUN_00e94a00();
}

// @ 0x00cee010
void cCommandSetVehicleWeapons::Execute(void *args)
{
    if (((int(__thiscall *)(void *))FUN_00837f30)(args) > 1) {
        void **vt = m_parser->m_vtbl00;
        void *a = ((void *(__thiscall *)(void *, int))FUN_00837f20)(args, 1);
        void *r = ((void *(__thiscall *)(void *, void *))vt[0x9c / 4])(m_parser, a);
        ((void(__cdecl *)(void *))FUN_00cac1a0)(r);
    }
}

// @ 0x00cee060
cCityGameCheatManager::~cCityGameCheatManager()
{
    CheatManagerObj *cm = (CheatManagerObj *)FUN_0067de20();
    ((void(__thiscall *)(void *, void *))(*(void ***)cm)[0x1c / 4])(cm, g_cmdMakeTradeRoutes);
    ((void(__thiscall *)(void *, void *))(*(void ***)cm)[0x1c / 4])(cm, g_cmdToggleShowPaths);
    ((void(__thiscall *)(void *, void *))(*(void ***)cm)[0x1c / 4])(cm, g_cmdSetVehicleWeapons);
}

// @ 0x00cee130
Simulator::cCivModeStrategy::cCivModeStrategy()
{
    CommandObj *c;

    FUN_0067de20();

    c = (CommandObj *)((void *(__cdecl *)(u32, void *, u32, u32, u32, u32))FUN_00f473a0)
            (0x10, (void *)0x13f09b4, 0, 0, 0, 0);
    if (c) {
        ((void *(__thiscall *)(void *))FUN_0083c800)(c);
        c->m_vtbl00 = (void **)0x14781d4;
    }

    c = (CommandObj *)((void *(__cdecl *)(u32, void *, u32, u32, u32, u32))FUN_00f473a0)
            (0x10, (void *)0x13f09b4, 0, 0, 0, 0);
    if (c) {
        ((void *(__thiscall *)(void *))FUN_0083c800)(c);
        c->m_vtbl00 = (void **)0x14781bc;
    }

    c = (CommandObj *)((void *(__cdecl *)(u32, void *, u32, u32, u32, u32))FUN_00f473a0)
            (0x10, (void *)0x13f09b4, 0, 0, 0, 0);
    if (c) {
        ((void *(__thiscall *)(void *))FUN_0083c800)(c);
        c->m_vtbl00 = (void **)0x14781ec;
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
            char c = ((char(__thiscall *)(void *))(*(void ***)((u8 *)obj + 0x120))[0x58 / 4])
                        ((u8 *)obj + 0x120);
            if (!c)
                ((void(__thiscall *)(void *, void *, u32))FUN_00be1340)(mgr, obj, 0);
        }
    }
}
