// Slice s00c829e0 -- low-LOD planet cell table and keyed entry accessors.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE2 /fp:fast
#include "types.h"

#pragma warning(disable : 4100)

namespace SP {

class cPlanet;

// 4-byte planet key.
struct tPlanetKey {
    int32_t mIndex;                                      // +0x00
};

// Entry returned by the keyed table lookup.
struct tPlanetEntry {
    uint8_t pad000[0xa0];                                // +0x000 .. +0x09f
    bool    mFieldA0;                                    // +0x0a0
    bool    mFieldA1;                                    // +0x0a1
};

// Keyed table (eastl map of planet key -> entry).
class cPlanetEntryTable {
public:
    tPlanetEntry* FUN_00ba4e60(tPlanetKey* pKey);        // 0x00ba4e60
};

extern void* __cdecl GetUniverseContext();               // 0x01021080

extern volatile uint32_t gStubSink;                      // keeps stub calls alive

class cSimPlanetLowLOD {
public:
    void FUN_00c829e0();
    __declspec(noinline) void FUN_00c82d50(cPlanet* pPlanet, bool bValue);
    void FUN_00c82ea0();
    void FUN_00c82f00();
    void FUN_00c82f80();
    void FUN_00c83050(cPlanet* pOld, cPlanet* pNew, bool bValue);
    void FUN_00c83090(tPlanetKey key, bool bValue);
    bool FUN_00c830b0(tPlanetKey key);
    void FUN_00c830d0(tPlanetKey key, bool bValue);
    void UpdateBackgroundPlanet(cPlanet* pPlanet, bool bValue); // 0x00c817e0

    uint8_t            pad000[0x4c];                     // +0x0000 .. +0x004b
    cPlanet*           mpPlanet;                         // +0x004c
    uint8_t            pad050[0x11c0 - 0x50];            // +0x0050 .. +0x11bf
    cPlanetEntryTable  mEntryTable;                      // +0x11c0
};

} // namespace SP

using namespace SP;

// @ 0xc829e0 SP::cSimPlanetLowLOD::FUN_00c829e0
void __thiscall cSimPlanetLowLOD::FUN_00c829e0()
{
}

// @ 0xc82d50 SP::cSimPlanetLowLOD::FUN_00c82d50
__declspec(noinline) void __thiscall cSimPlanetLowLOD::FUN_00c82d50(cPlanet* pPlanet, bool bValue)
{
    gStubSink = pad000[0];                               // side effect keeps the call
}

// @ 0xc82ea0 SP::cSimPlanetLowLOD::FUN_00c82ea0
void __thiscall cSimPlanetLowLOD::FUN_00c82ea0()
{
}

// @ 0xc82f00 SP::cSimPlanetLowLOD::FUN_00c82f00
void __thiscall cSimPlanetLowLOD::FUN_00c82f00()
{
}

// @ 0xc82f80 SP::cSimPlanetLowLOD::FUN_00c82f80
void __thiscall cSimPlanetLowLOD::FUN_00c82f80()
{
}

// @ 0xc83050 SP::cSimPlanetLowLOD::FUN_00c83050
void __thiscall cSimPlanetLowLOD::FUN_00c83050(cPlanet* pOld, cPlanet* pNew, bool bValue)
{
    if (pOld == pNew) {
        if (!GetUniverseContext()) {
            FUN_00c82d50(pNew, bValue);
            return;
        }
    }
    UpdateBackgroundPlanet(pNew, bValue);
}

// @ 0xc83090 SP::cSimPlanetLowLOD::FUN_00c83090
void __thiscall cSimPlanetLowLOD::FUN_00c83090(tPlanetKey key, bool bValue)
{
    mEntryTable.FUN_00ba4e60(&key)->mFieldA0 = bValue;
}

// @ 0xc830b0 SP::cSimPlanetLowLOD::FUN_00c830b0
bool __thiscall cSimPlanetLowLOD::FUN_00c830b0(tPlanetKey key)
{
    return mEntryTable.FUN_00ba4e60(&key)->mFieldA1;
}

// @ 0xc830d0 SP::cSimPlanetLowLOD::FUN_00c830d0
void __thiscall cSimPlanetLowLOD::FUN_00c830d0(tPlanetKey key, bool bValue)
{
    mEntryTable.FUN_00ba4e60(&key)->mFieldA1 = bValue;
}
