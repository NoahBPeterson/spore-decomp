// Slice s00cd6980 -- tribe-mode event dispatch (cTribeModeStrategy::RaiseEvent).
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

// Retail image references, use relocatable symbols rather than numeric addresses.
extern "C" unsigned char g_0157f174[];
extern "C" unsigned char g_0157f184[];

namespace Simulator {

// Hint keys and the shared offset value live in the game's data section; naming
// them as globals reproduces the retail build's absolute operands.
struct ResourceKey {
    uint32_t instanceID;
    uint32_t typeID;
    uint32_t groupID;
};

extern ResourceKey g_hintKeys[3];                            // 0x0157f138 (12 bytes each)
extern const float g_hintOffset;                             // 0x013eb1bc

// Terrain-sphere event-flag table reached through cGameNounManager.
struct cTerrainSphere_s00cd6980 {
    bool __thiscall Contains(uint32_t key);                  // 0x00c772c0
    void __thiscall Remove(uint32_t key);                    // 0x00c77300
    bool __thiscall HasFlagOrInsert(uint32_t key);           // 0x00c77bf0
};

struct cNounManager_s00cd6980 {
    cTerrainSphere_s00cd6980* __thiscall GetCurrentTerrainSphere(); // 0x00f67d90
};

struct cGameTimeManager_s00cd6980 {
    void __thiscall IncPauseGate(uint32_t timer);            // 0x00b32220
    void __thiscall DecPauseGate(uint32_t timer);            // 0x00b32250
    bool __thiscall IsPaused();                              // 0x00cce590 (ecx = manager)
};

struct cGameInputManager_s00cd6980 {
    uint8_t pad000[0x110];                                   // +0x000
    int32_t m110;                                            // +0x110
};

struct cRelationsStrip_s00cd6980 {
    void __thiscall Reset();                                 // 0x00e2f270
};

struct cCameraCtl_s00cd6980 {
    uint8_t pad000[0x390];                                   // +0x000
    uint8_t m390;                                            // +0x390
};

// cTribeModeStrategy +0x394 points at the mission/objective bookkeeping object.
struct cMissionMgr_s00cd6980 {
    uint32_t __thiscall HintClear(uint32_t hint);            // 0x00b707a0
};

// Hint-layer singleton: its insert method takes 0x28 bytes (ret 0x28).
struct cHintManager_s00cd6980 {
    void __thiscall ShowHint(ResourceKey key, void* handler, int a,
                             float x, float y, float z, int b, int c); // 0x0067aaf0
};

// Global object whose virtual slot +0x30 looks a resource up by hashed id.
struct cResourceFinder_s00cd6980 {
    virtual void v00();                                      // +0x00
    virtual void v01();                                      // +0x04
    virtual void v02();                                      // +0x08
    virtual void v03();                                      // +0x0c
    virtual void v04();                                      // +0x10
    virtual void v05();                                      // +0x14
    virtual void v06();                                      // +0x18
    virtual void v07();                                      // +0x1c
    virtual void v08();                                      // +0x20
    virtual void v09();                                      // +0x24
    virtual void v10();                                      // +0x28
    virtual void v11();                                      // +0x2c
    virtual void* Find(uint32_t id);                         // +0x30
};

} // namespace Simulator

Simulator::cNounManager_s00cd6980*      __cdecl NounManager();      // 0x00b3d300
Simulator::cGameTimeManager_s00cd6980*  __cdecl GameTimeManager();  // 0x00b3d380
Simulator::cGameInputManager_s00cd6980* __cdecl GameInputManager(); // 0x00b3d250
Simulator::cCameraCtl_s00cd6980* __cdecl GetCameraCtl();     // 0x00b3d280
Simulator::cResourceFinder_s00cd6980* __cdecl Function_0067dd30(); // 0x0067dd30
// No stack adjustment follows this call in retail, so it pops its argument.
Simulator::cRelationsStrip_s00cd6980* __stdcall Function_00b3d4f0(int); // 0x00b3d4f0

// Hint-layer getter: no arguments, returns the singleton in eax.
Simulator::cHintManager_s00cd6980* __cdecl GetHintManager();  // 0x0067caf0

void __cdecl Function_00cd3fb0(int eventHash);               // 0x00cd3fb0
void __cdecl Function_00cd3fd0(int eventHash);               // 0x00cd3fd0

struct cTribeModeStrategy_s00cd6980 {
    uint8_t pad000[0x1a4];                                   // +0x000
    uint8_t m1a4;                                            // +0x1a4
    uint8_t pad1a5[0x394 - 0x1a5];                           // +0x1a5
    Simulator::cMissionMgr_s00cd6980* mp394;                 // +0x394

    bool __thiscall HasEvent(uint32_t eventHash);            // 0x00cd4460
    void __thiscall RaiseEvent(uint32_t eventHash);          // 0x00cd6980
    void __thiscall Notify(uint32_t eventHash);              // 0x00cd6130
};

// ---------------------------------------------------------------------------
// 0x00cd6980 -- raise one tribe-mode event.
//
// The event is first offered to the current terrain sphere (if the sphere
// already carries it, nothing happens).  Raising an event also inserts its
// flag, then clears the flags of the stages that it supersedes; the
// superseded events fall through the switch in order, so that raising the
// last stage of a chain performs the whole teardown.  Finally, when both
// world markers exist, the event is announced to the strategy.
//
// The hint keys and the offset value the three ShowHint calls pass are global
// data (0x157f138/144/150 and 0x13eb1bc), not literals; naming them keeps the
// retail build's absolute operands.
// ---------------------------------------------------------------------------

// @ 0x00cd6980
void cTribeModeStrategy_s00cd6980::RaiseEvent(uint32_t eventHash)
{
    Simulator::cTerrainSphere_s00cd6980* sphere = NounManager()->GetCurrentTerrainSphere();

    if (sphere != 0 && sphere->Contains(eventHash))
        return;

    sphere = NounManager()->GetCurrentTerrainSphere();
    if (sphere != 0)
        sphere->HasFlagOrInsert(eventHash);

    switch (eventHash)
    {
    case 0x064c010f:
        Function_00cd3fd0(0x53203528);
        // fall through
    case 0x53203528:
        sphere = NounManager()->GetCurrentTerrainSphere();
        if (sphere != 0)
            sphere->Remove(0x83861976);
        // fall through
    case 0x83861976:
        sphere = NounManager()->GetCurrentTerrainSphere();
        if (sphere != 0)
            sphere->Remove(0x064d44f9);
        // fall through
    case 0x064d44f9:
        sphere = NounManager()->GetCurrentTerrainSphere();
        if (sphere != 0)
            sphere->Remove(0x064e70b3);
        // fall through
    case 0x064e70b3:
        sphere = NounManager()->GetCurrentTerrainSphere();
        if (sphere != 0)
            sphere->Remove(0x5ac72d7c);
        // fall through
    case 0x5ac72d7c:
        sphere = NounManager()->GetCurrentTerrainSphere();
        if (sphere != 0)
            sphere->Remove(0x14363974);

        sphere = NounManager()->GetCurrentTerrainSphere();
        if (sphere != 0 && sphere->Contains(0x056d1871))
            break;
        if (!HasEvent(0x064c010f))
            break;
        if (!HasEvent(0x83861976))
            break;
        if (!HasEvent(0x53203528))
            break;
        if (!HasEvent(0x064d44f9))
            break;
        if (!HasEvent(0x064e70b3))
            break;
        if (!HasEvent(0x5ac72d7c))
            break;

        Function_00cd3fb0(0x056d1871);
        m1a4 = 0;

        if (GameTimeManager()->IsPaused())
        {
            Simulator::cGameTimeManager_s00cd6980* time = GameTimeManager();
            time->DecPauseGate(0x064beb65);
            Simulator::cGameInputManager_s00cd6980* input = GameInputManager();
            input->m110--;
        }

        Function_00b3d4f0(0)->Reset();

        if (GetCameraCtl() != 0)
            GetCameraCtl()->m390 = 0;

        if (Function_0067dd30()->Find(0x04ea96cb) != 0 &&
            Function_0067dd30()->Find(0x05b5bb5e) != 0)
        {
            Simulator::cGameTimeManager_s00cd6980* time = GameTimeManager();
            time->IncPauseGate(0x04bf38a7);

            GetHintManager()->ShowHint(Simulator::g_hintKeys[1], (void*)g_0157f174, 0,
                                       Simulator::g_hintOffset, Simulator::g_hintOffset,
                                       0.0f, 0, 0);
        }
        break;

    case 0x064be5ff:
    {
        if (HasEvent(0x056d1871))
            break;
        if (Function_0067dd30()->Find(0x04ea96cb) == 0)
            break;
        if (Function_0067dd30()->Find(0x05b5bb5e) == 0)
            break;

        if (GetCameraCtl() != 0)
            GetCameraCtl()->m390 = 0;

        Simulator::cGameTimeManager_s00cd6980* pauseTime = GameTimeManager();
        pauseTime->IncPauseGate(0x04bf38a7);

        GetHintManager()->ShowHint(Simulator::g_hintKeys[0], 0, 0,
                                   Simulator::g_hintOffset, Simulator::g_hintOffset,
                                   0.0f, 0, 0);

        GetHintManager()->ShowHint(Simulator::g_hintKeys[2], (void*)g_0157f184, 0,
                                   Simulator::g_hintOffset, Simulator::g_hintOffset,
                                   0.0f, 0, 0);

        if (GameTimeManager()->IsPaused())
            break;
        Simulator::cGameTimeManager_s00cd6980* resumeTime = GameTimeManager();
        resumeTime->IncPauseGate(0x064beb65);
        break;
    }

    case 0x14363974:
        mp394->HintClear(0x0391c432);
        mp394->HintClear(0x69ba7f0d);
        mp394->HintClear(0x02d99d0b);
        break;

    case 0x11ade9ce:
    case 0x5312da01:
    case 0x84f037b0:
    case 0x7d7315c8:
    case 0x9a44d4ab:
    case 0xdcdf2f2f:
        mp394->HintClear(eventHash);
        break;
    }

    if (Function_0067dd30()->Find(0x04ea96cb) != 0 &&
        Function_0067dd30()->Find(0x05b5bb5e) != 0)
        Notify(eventHash);
}
