// Slice s00fd9f70 -- space app mode: tearing down the Gonzago subsystem on mode exit, plus the rest
// of the space-mode entry points.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE2 /fp:fast
#include "types.h"

#pragma warning(disable : 4100)

namespace SP {

class cGonzagoSubsystem {
public:
    virtual void Shutdown(int immediate);                // +0x00
    virtual void v04();                                  // +0x04
    virtual void Release();                              // +0x08
};

class cAppModeSpace {
public:
    void OnMouseUp();
    void Deactivate();
    void ShutdownGonzagoSubsystem();
    void SetPlanetTimeOnFirstEntry();
    void Write();
    void FUN_00fda1f0();
    void FUN_00fda2e0();
    void FUN_00fda480();
    void FUN_00fda5e0();
    void FUN_00fda750();
    void FUN_00fda940();
    void FUN_00fda9f0();
    void FUN_00fdab40();
    void FUN_00fdabf0();

    uint8_t             pad000[0x180];                   // +0x000 .. +0x17f
    cGonzagoSubsystem*  mpGonzagoSubsystem;              // +0x180
};

} // namespace SP

using namespace SP;

namespace SP {

// @ 0xfd9f70 SP::cAppModeSpace::OnMouseUp
void __thiscall cAppModeSpace::OnMouseUp()
{
}

// @ 0xfda1f0 SP::cAppModeSpace::FUN_00fda1f0
void __thiscall cAppModeSpace::FUN_00fda1f0()
{
}

// @ 0xfda2e0 SP::cAppModeSpace::FUN_00fda2e0
void __thiscall cAppModeSpace::FUN_00fda2e0()
{
}

// @ 0xfda390 SP::cAppModeSpace::Deactivate
void __thiscall cAppModeSpace::Deactivate()
{
}

// @ 0xfda480 SP::cAppModeSpace::FUN_00fda480
void __thiscall cAppModeSpace::FUN_00fda480()
{
}

// @ 0xfda4f0 SP::cAppModeSpace::ShutdownGonzagoSubsystem
void __thiscall cAppModeSpace::ShutdownGonzagoSubsystem()
{
    if (mpGonzagoSubsystem)
        mpGonzagoSubsystem->Shutdown(1);
    cGonzagoSubsystem* pSubsystem = mpGonzagoSubsystem;
    if (pSubsystem) {
        mpGonzagoSubsystem = 0;
        pSubsystem->Release();
    }
}

// @ 0xfda530 SP::cAppModeSpace::SetPlanetTimeOnFirstEntry
void __thiscall cAppModeSpace::SetPlanetTimeOnFirstEntry()
{
}

// @ 0xfda5e0 SP::cAppModeSpace::FUN_00fda5e0
void __thiscall cAppModeSpace::FUN_00fda5e0()
{
}

// @ 0xfda750 SP::cAppModeSpace::FUN_00fda750
void __thiscall cAppModeSpace::FUN_00fda750()
{
}

// @ 0xfda940 SP::cAppModeSpace::FUN_00fda940
void __thiscall cAppModeSpace::FUN_00fda940()
{
}

// @ 0xfda9f0 SP::cAppModeSpace::FUN_00fda9f0
void __thiscall cAppModeSpace::FUN_00fda9f0()
{
}

// @ 0xfdaa90 SP::cAppModeSpace::Write
void __thiscall cAppModeSpace::Write()
{
}

// @ 0xfdab40 SP::cAppModeSpace::FUN_00fdab40
void __thiscall cAppModeSpace::FUN_00fdab40()
{
}

// @ 0xfdabf0 SP::cAppModeSpace::FUN_00fdabf0
void __thiscall cAppModeSpace::FUN_00fdabf0()
{
}

} // namespace SP
