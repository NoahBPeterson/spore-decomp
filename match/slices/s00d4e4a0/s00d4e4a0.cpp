// Slice s00d4e4a0 -- drama manager event slot assignment.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE2 /fp:fast
#include "types.h"

#pragma warning(disable : 4100)

namespace SP {

class cDramaEvent;

// Ref-counted drama object hung off the manager.
class cDramaRefObj {
public:
    virtual void AddRef();                               // +0x00
    virtual void Release();                              // +0x04
};

// Slot holder living inside the event handle (locked access to one slot).
class cDramaSlotHolder {
public:
    cDramaRefObj** FUN_00d4eb30(cDramaRefObj*** ppOutSlot); // 0x00d4eb30
    void           FUN_00d4e8e0(cDramaRefObj*** ppOutSlot); // 0x00d4e8e0
};

// The handle whose +0x5c member holds the drama event slot.
class cDramaEventHandle {
public:
    void Assign(cDramaRefObj** ppOut, cDramaRefObj* p);

    uint8_t           pad000[0x5c];                      // +0x000 .. +0x05b
    cDramaSlotHolder  mSlotHolder;                       // +0x05c
};

class cMeteorStrikeEvent {
public:
    void Clear();
};

class cTribeFoodRaidEvent {
public:
    void TriggerEvent();
    void ShouldActivate();
    void TickInactiveEvent();
};

} // namespace SP

using namespace SP;

// @ 0xd4e4a0 FUN_00d4e4a0
void __cdecl FUN_00d4e4a0()
{
}

// @ 0xd4e8e0 SP::cDramaSlotHolder::FUN_00d4e8e0
__declspec(noinline) void __thiscall cDramaSlotHolder::FUN_00d4e8e0(cDramaRefObj*** ppOutSlot)
{
    *ppOutSlot = 0;
}

// @ 0xd4e950 SP::cMeteorStrikeEvent::Clear
void __thiscall cMeteorStrikeEvent::Clear()
{
}

// @ 0xd4ea90 Simulator::cDramaManager::cDramaManager
void __fastcall cDramaManagerCtor(void* this_, int unused)
{
    (void)this_;
}

// @ 0xd4eb30 SP::cDramaSlotHolder::FUN_00d4eb30
__declspec(noinline) cDramaRefObj** __thiscall cDramaSlotHolder::FUN_00d4eb30(cDramaRefObj*** ppOutSlot)
{
    return (cDramaRefObj**)ppOutSlot;
}

// @ 0xd4ebe0 allocator_template_helper
void __cdecl allocator_template_helper()
{
}

// @ 0xd4edd0 SP::cDramaEventHandle::Assign
void __thiscall cDramaEventHandle::Assign(cDramaRefObj** ppOut, cDramaRefObj* p)
{
    cDramaSlotHolder& holder = mSlotHolder;
    if (p) {
        cDramaRefObj** ppSlot = holder.FUN_00d4eb30(&ppOut);
        cDramaRefObj* pOld = *ppSlot;
        if (p != pOld) {
            p->AddRef();
            *ppSlot = p;
            if (pOld)
                pOld->Release();
        }
    } else {
        holder.FUN_00d4e8e0(&ppOut);
    }
}

// @ 0xd4ee20 SP::cTribeFoodRaidEvent::TriggerEvent
void __thiscall cTribeFoodRaidEvent::TriggerEvent()
{
}

// @ 0xd4f0a0 SP::cTribeFoodRaidEvent::ShouldActivate
void __thiscall cTribeFoodRaidEvent::ShouldActivate()
{
}

// @ 0xd4f260 SP::cTribeFoodRaidEvent::TickInactiveEvent
void __thiscall cTribeFoodRaidEvent::TickInactiveEvent()
{
}
