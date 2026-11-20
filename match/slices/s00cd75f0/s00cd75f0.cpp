// Slice s00cd75f0 -- tribe-mode strategy input handling + game-data factory.
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

namespace Simulator {

struct tGameDataVectorT {
    void*    mpVtable;                                       // +0x00
    uint32_t mValue04;                                       // +0x04
    uint32_t mValue08;                                       // +0x08
    uint32_t mValue0c;                                       // +0x0c
};

} // namespace Simulator

extern "C" void* __cdecl operator_new(uint32_t size, const char* name, int a, int b, int c, int d); // 0x00f473a0
extern "C" void GameDataVectorBaseCtor();                    // 0x00b1e540

// @ 0x00cd7d10
Simulator::tGameDataVectorT* __cdecl CreateGameDataVector()
{
    Simulator::tGameDataVectorT* p = (Simulator::tGameDataVectorT*)operator_new(
        0x18, "Simulator/tGameDataVectorT", 0, 0, 0, 0);
    if (p) {
        ((void (__thiscall*)(void*))GameDataVectorBaseCtor)(p);
        p->mValue04 = 0;
        p->mValue08 = 0;
        p->mValue0c = 0;
        return p;
    }
    return 0;
}

// ---------------------------------------------------------------------------
// Tribe-mode strategy input dispatch (0x00cd75f0).
//
// Retail signature: thiscall, (int key, int modifiers), ret 8, returns bool.
// The strategy first offers the input to the global input manager (slot +0x44),
// then bails out while a game-time timer is running, then records the slot +0x4c
// result. While the current terrain sphere does not already carry the "sphere
// selected" key, and once the blocking key (+0x064be5ff) is no longer queued,
// it maps raw scancodes onto three strategy events.
// ---------------------------------------------------------------------------

struct cGameInputManager_s00cd75f0;

struct cTerrainSphere_s00cd75f0 {
    bool __thiscall Contains(uint32_t key);                  // 0x00c772c0
};

struct cNounManager_s00cd75f0 {
    cTerrainSphere_s00cd75f0* __thiscall GetCurrentTerrainSphere(); // 0x00f67d90
};

struct cGameTimeManager_s00cd75f0 {
    int __thiscall GetTimerState(uint32_t timer);            // 0x00b320d0
};

cGameInputManager_s00cd75f0* __cdecl GameInputManager();      // 0x00b3d250
cGameTimeManager_s00cd75f0*  __cdecl GameTimeManager();       // 0x00b3d380
cNounManager_s00cd75f0*      __cdecl NounManager();           // 0x00b3d300
bool __cdecl IsInputConsumed(int key);                        // 0x00d4a4a0

struct cGameInputManager_s00cd75f0 {
    virtual void v00();                                     // +0x00
    virtual void v01();                                     // +0x04
    virtual void v02();                                     // +0x08
    virtual void v03();                                     // +0x0c
    virtual void v04();                                     // +0x10
    virtual void v05();                                     // +0x14
    virtual bool v06(uint32_t key);                         // +0x18
    virtual void v07();                                     // +0x1c
    virtual void v08();                                     // +0x20
    virtual void v09();                                     // +0x24
    virtual void v10();                                     // +0x28
    virtual void v11();                                     // +0x2c
    virtual void v12();                                     // +0x30
    virtual void v13();                                     // +0x34
    virtual void v14();                                     // +0x38
    virtual void v15();                                     // +0x3c
    virtual void v16();                                     // +0x40
    virtual bool v17(int key, int modifiers);               // +0x44
    virtual void v18();                                     // +0x48
    virtual bool v19(int key, int modifiers);               // +0x4c
};

struct cTribeModeStrategy_s00cd75f0 {
    bool __thiscall HasEvent(uint32_t eventHash);            // 0x00cd4460
    void __thiscall RaiseEvent(uint32_t eventHash);          // 0x00cd6980
    bool __thiscall OnInput(int key, int modifiers);          // 0x00cd75f0
};

// @ 0x00cd75f0
bool cTribeModeStrategy_s00cd75f0::OnInput(int key, int modifiers)
{
    if (GameInputManager()->v17(key, modifiers))
        return true;

    cGameTimeManager_s00cd75f0* timeManager = GameTimeManager();
    if (timeManager->GetTimerState(0x04bf38a9) > 0)
        return true;

    if (modifiers == 0 && IsInputConsumed(key))
        return true;

    bool result = GameInputManager()->v19(key, modifiers);

    cTerrainSphere_s00cd75f0* sphere = NounManager()->GetCurrentTerrainSphere();
    if (sphere != 0 && sphere->Contains(0x056d1871))
        return result;

    if (!HasEvent(0x064be5ff))
        return result;

    cGameInputManager_s00cd75f0* input = GameInputManager();
    if (!HasEvent(0x53203528) && (input->v06(0x12) || input->v06(0x11)))
        RaiseEvent(0x53203528);

    if (!HasEvent(0x83861976) && (input->v06(1) || input->v06(2) ||
                                  input->v06(3) || input->v06(4)))
        RaiseEvent(0x83861976);

    if (!HasEvent(0x064c010f) && (input->v06(9) || input->v06(0x10)))
        RaiseEvent(0x064c010f);

    return result;
}
