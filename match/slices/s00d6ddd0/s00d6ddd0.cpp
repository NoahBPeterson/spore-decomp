// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
// Play-fight callback. Retail clears the creature target through vtable slot 0x84,
// then tail-calls ClearSelection (0x00bcb430) on the behaviour object at +0xb4c.
#include "types.h"

#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4

// Behaviour object at creature +0xb4c. 0x00bcb430 is cVarListEditor::ClearSelection.
struct cBehaviorStimuliOwner {
    void ClearSelection();
};

// Slot layout copied from the local ICombatant in SPCreatureBase.cpp.
class ICombatant {
public:
    PV2                                       // 0x00
    virtual void* ToSpatialObject();          // 0x08
    virtual void* ToGameData();               // 0x0c
    PV8 PV8 PV8 PV4 PV                         // 0x10..0x80
    virtual void SetCreatureTarget(void* a, void* b, void* c); // 0x84

    char mPad04[0xb4c - 0x04];
    cBehaviorStimuliOwner* mpBehavior;        // +0xb4c
};

// @ 0x00d6ddd0
void __cdecl FUN_00d6ddd0(ICombatant* creature)
{
    creature->SetCreatureTarget(0, 0, 0);
    creature->mpBehavior->ClearSelection();
}
