// Slice s00d06710 -- small vehicle/relationship helpers: ref-counted slot constructors and the
// matching scalar deleting destructor, plus a one-line argument forwarder.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE2 /fp:fast
#include "types.h"

#pragma warning(disable : 4100)

namespace SP {

class cRefCounted {
public:
    virtual void r00();                                  // +0x00 add reference
    virtual void Release();                              // +0x04
    virtual void Destroy();                              // +0x08
};

struct cSlotVTable { int mSlot0; };
extern cSlotVTable gSlotVtbl;                            // 0x01479070
extern cSlotVTable gSlotVtbl2;                           // 0x014790a0
extern cSlotVTable gSlotVtbl3;                           // 0x014790d0

void __cdecl operator_delete_array(void* p);             // 0x00f47380

// Two ref-counted pointers behind a vtable pointer; +8 is the assigned one.
class cCountedSlot {
public:
    void* volatile          mpVtbl;                      // +0x00
    cRefCounted*            mpField4;                    // +0x04
    cRefCounted* volatile   mpField8;                    // +0x08

    cCountedSlot* FUN_00d06eb0(cRefCounted* p);
    void*         FUN_00d070b0(uint32_t flags);

    void FUN_00d06a50(int value);                        // 0x00d06a50
    void FUN_00d06c30(int first, int value);
};

class cCountedSlot2 {
public:
    void* volatile          mpVtbl;                      // +0x00
    cRefCounted*            mpField4;                    // +0x04
    cRefCounted* volatile   mpField8;                    // +0x08

    cCountedSlot2* FUN_00d07420(cRefCounted* p);
};

// Third slot flavour of the same ref-counted assignment (own vtable at 0x014790d0).
class cCountedSlot3 {
public:
    void* volatile          mpVtbl;                      // +0x00
    cRefCounted*            mpField4;                    // +0x04
    cRefCounted* volatile   mpField8;                    // +0x08

    cCountedSlot3* FUN_00d07720(cRefCounted* p);
};

// @ 0xd06920 onwards: relationship-manager entry point reached through the manager object.
class cRelationshipManager {
public:
    void StartAlliance(void* pOther, uint32_t allianceId);  // 0x00d06920
};

} // namespace SP

using namespace SP;

namespace SP {

// @ 0xd06710 FUN_00d06710
void __fastcall FUN_00d06710(void* this_, int unused)
{
    (void)this_;
}

// @ 0xd068c0 FUN_00d068c0
void __fastcall FUN_00d068c0(void* this_, int unused)
{
    (void)this_;
}

// @ 0xd06920 SP::cRelationshipManager::StartAlliance
void __thiscall cRelationshipManager::StartAlliance(void* pOther, uint32_t allianceId)
{
    (void)pOther;
    (void)allianceId;
}

// @ 0xd06a50 SP::cCountedSlot::FUN_00d06a50
void __thiscall cCountedSlot::FUN_00d06a50(int value)
{
    (void)value;
}

// @ 0xd06c30 SP::cCountedSlot::FUN_00d06c30
void __thiscall cCountedSlot::FUN_00d06c30(int first, int value)
{
    (void)first;
    FUN_00d06a50(value);
}

// @ 0xd06d80 FUN_00d06d80
void __fastcall FUN_00d06d80(void* this_, int unused)
{
    (void)this_;
}

// @ 0xd06e70 Simulator::cSoundLoopObject::cSoundLoopObject
void __fastcall cSoundLoopObjectCtor(void* this_, int unused)
{
    (void)this_;
}

// @ 0xd06eb0 SP::cCountedSlot::FUN_00d06eb0
cCountedSlot* __thiscall cCountedSlot::FUN_00d06eb0(cRefCounted* p)
{
    mpVtbl = &gSlotVtbl;
    mpField4 = 0;
    mpField8 = 0;
    cRefCounted* pOld = mpField8;
    if (p != pOld) {
        if (p)
            p->r00();
        mpField8 = p;
        if (pOld)
            pOld->Release();
    }
    return this;
}

// @ 0xd06f00 FUN_00d06f00
void __fastcall FUN_00d06f00(void* this_, int unused)
{
    (void)this_;
}

// @ 0xd070b0 SP::cCountedSlot::FUN_00d070b0
void* __thiscall cCountedSlot::FUN_00d070b0(uint32_t flags)
{
    mpVtbl = &gSlotVtbl;
    if (mpField8)
        mpField8->Release();
    if (mpField4)
        mpField4->Destroy();
    if (flags & 1)
        operator_delete_array(this);
    return this;
}

// @ 0xd070f0 E207
void E207()
{
}

// @ 0xd07420 SP::cCountedSlot2::FUN_00d07420
cCountedSlot2* __thiscall cCountedSlot2::FUN_00d07420(cRefCounted* p)
{
    mpVtbl = &gSlotVtbl2;
    mpField4 = 0;
    mpField8 = 0;
    cRefCounted* pOld = mpField8;
    if (p != pOld) {
        if (p)
            p->r00();
        mpField8 = p;
        if (pOld)
            pOld->Release();
    }
    return this;
}

// @ 0xd07470 FUN_00d07470
void __fastcall FUN_00d07470(void* this_, int unused)
{
    (void)this_;
}

// @ 0xd07590 FUN_00d07590
void __fastcall FUN_00d07590(void* this_, int unused)
{
    (void)this_;
}

// @ 0xd075d0 FUN_00d075d0
void __fastcall FUN_00d075d0(void* this_, int unused)
{
    (void)this_;
}

// @ 0xd07720 SP::cCountedSlot3::FUN_00d07720
cCountedSlot3* __thiscall cCountedSlot3::FUN_00d07720(cRefCounted* p)
{
    mpVtbl = &gSlotVtbl3;
    mpField4 = 0;
    mpField8 = 0;
    cRefCounted* pOld = mpField8;
    if (p != pOld) {
        if (p)
            p->r00();
        mpField8 = p;
        if (pOld)
            pOld->Release();
    }
    return this;
}

} // namespace SP
