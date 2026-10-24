// Slice s00df0280 -- galaxy game entry state machine: reset to no state.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE2 /fp:fast
#include "types.h"

#pragma warning(disable : 4100)

namespace SP {

class cGalaxyStateMachine {
public:
    __declspec(noinline) void SetCurrentState(int32_t state);  // 0x00df0670
    void FUN_00dee2a0();                                       // 0x00dee2a0
};

class cGalaxyGameEntryUIStateMachine {
public:
    void ShowPanel();
    __declspec(noinline) void SetCurrentState(int32_t state);
    void FUN_00df0980();

    uint8_t              pad000[8];                          // +0x00 .. +0x07
    cGalaxyStateMachine* mpStateMachine;                     // +0x08
};

} // namespace SP

using namespace SP;

// @ 0xdf0280 SP::cGalaxyGameEntryUIStateMachine::ShowPanel
void __thiscall cGalaxyGameEntryUIStateMachine::ShowPanel()
{
}

// @ 0xdf0670 SP::cGalaxyGameEntryUIStateMachine::SetCurrentState
void __thiscall cGalaxyGameEntryUIStateMachine::SetCurrentState(int32_t state)
{
}

// @ 0xdf0830 FUN_00df0830
void __cdecl FUN_00df0830()
{
}

// @ 0xdf0980 SP::cGalaxyGameEntryUIStateMachine::FUN_00df0980
void __thiscall cGalaxyGameEntryUIStateMachine::FUN_00df0980()
{
    cGalaxyStateMachine* pMachine = mpStateMachine;
    pMachine->SetCurrentState(0);
    mpStateMachine->FUN_00dee2a0();
}

// @ 0xdf09a0 FUN_00df09a0
void __cdecl FUN_00df09a0()
{
}

// @ 0xdf0a40 FUN_00df0a40
void __cdecl FUN_00df0a40()
{
}

// @ 0xdf0ad0 FUN_00df0ad0
void __cdecl FUN_00df0ad0()
{
}

// @ 0xdf0c00 FUN_00df0c00
void __cdecl FUN_00df0c00()
{
}

// @ 0xdf0f20 FUN_00df0f20
void __cdecl FUN_00df0f20()
{
}
