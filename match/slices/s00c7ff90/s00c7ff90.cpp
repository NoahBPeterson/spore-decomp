// Slice s00c7ff90 -- low-LOD planet plant species registration.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE2 /fp:fast
#include "types.h"

#pragma warning(disable : 4100)

// One plant species key: three raw dwords (12 bytes).
struct tSpeciesKey {
    uint32_t mField0;                                    // +0x00
    uint32_t mField4;                                    // +0x04
    uint32_t mField8;                                    // +0x08
};

// Growable list of species keys held by the planet.
class cSpeciesList {
public:
    uint8_t       pad000[0xbc];                          // +0x000 .. +0x0bb
    tSpeciesKey*  mpBegin;                               // +0x0bc
    tSpeciesKey*  mpEnd;                                 // +0x0c0
};

class cPlantSpecies;
class cTerrainDistributeInfo;

class cPlantSpeciesManager {
public:
    cPlantSpecies* GetSpeciesFromID(tSpeciesKey* pKey);   // 0x00b90410
};

class cTerrainDistributeInfo {
public:
    void SetInfoFromProps();                             // 0x00b2bbe0
};

class cPlanet {
public:
    void PushKeyBC(tSpeciesKey* pKey);                   // 0x00c73270

    uint8_t        pad000[0x13c];                        // +0x000 .. +0x13b
    cSpeciesList*  mpSpeciesList;                        // +0x13c
};

extern cPlantSpeciesManager* __cdecl           FUN_00b3d420();   // 0x00b3d420
extern cTerrainDistributeInfo* __cdecl         FUN_00b3d3b0();   // 0x00b3d3b0

namespace SP {

// Key -> int table (eastl hash table of pair<Key, int>).
class cSpeciesKeyTable {
public:
    __declspec(noinline) int32_t* FUN_00c80110(tSpeciesKey* pKey); // 0x00c80110
};

class cSimPlanetLowLOD {
public:
    cSimPlanetLowLOD();
    void FUN_00c80180();
    void FUN_00c805b0();
    void FUN_00c80680();
    void FUN_00c80780();
    bool AddPlantSpecies(tSpeciesKey* pKey);
    void FUN_00c80a80();

    uint8_t            pad000[0x4c];                     // +0x000 .. +0x04b
    cPlanet*           mpPlanet;                         // +0x04c
    uint8_t            pad050[0x2060 - 0x50];            // +0x050 .. +0x205f
    cSpeciesKeyTable   mSpeciesTable;                    // +0x2060
};

} // namespace SP

using namespace SP;

// @ 0xc7ff90 Simulator::cSimPlanetLowLOD::cSimPlanetLowLOD
void __fastcall cSimPlanetLowLODCtorSTUB(void* this_, int unused)
{
    (void)this_;
}

// @ 0xc80110 SP::cSpeciesKeyTable::FUN_00c80110
__declspec(noinline) int32_t* __thiscall cSpeciesKeyTable::FUN_00c80110(tSpeciesKey* pKey)
{
    return (int32_t*)pKey;
}

// @ 0xc80180 SP::cSimPlanetLowLOD::FUN_00c80180
void __thiscall cSimPlanetLowLOD::FUN_00c80180()
{
}

// @ 0xc805b0 SP::cSimPlanetLowLOD::FUN_00c805b0
void __thiscall cSimPlanetLowLOD::FUN_00c805b0()
{
}

// @ 0xc80680 SP::cSimPlanetLowLOD::FUN_00c80680
void __thiscall cSimPlanetLowLOD::FUN_00c80680()
{
}

// @ 0xc80780 SP::cSimPlanetLowLOD::FUN_00c80780
void __thiscall cSimPlanetLowLOD::FUN_00c80780()
{
}

// @ 0xc809d0 SP::cSimPlanetLowLOD::AddPlantSpecies
bool __thiscall cSimPlanetLowLOD::AddPlantSpecies(tSpeciesKey* pKey)
{
    cSpeciesList* pList = mpPlanet->mpSpeciesList;
    int32_t count = (int32_t)(pList->mpEnd - pList->mpBegin);
    tSpeciesKey* pEntry = pList->mpBegin;
    for (int32_t i = 0; i < count; ++i) {
        if (pEntry->mField0 == pKey->mField0 &&
            pEntry->mField4 == pKey->mField4 &&
            pEntry->mField8 == pKey->mField8)
            return false;
        ++pEntry;
    }
    if (!FUN_00b3d420()->GetSpeciesFromID(pKey))
        return false;
    if (count >= 9)
        return false;
    mpPlanet->PushKeyBC(pKey);
    *mSpeciesTable.FUN_00c80110(pKey) = 0;
    FUN_00b3d3b0()->SetInfoFromProps();
    return true;
}

// @ 0xc80a80 SP::cSimPlanetLowLOD::FUN_00c80a80
void __thiscall cSimPlanetLowLOD::FUN_00c80a80()
{
}
