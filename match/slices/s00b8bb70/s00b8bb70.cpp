// 0x00b8bb70..0x00b8c328 -- SP::cPlanetModel / SP::cCityDisplayStrategy
// (SPGonzago).  Ray-cast helper plus the city display strategy's resource-node
// pass and a formation helper.
// Flags: /O2 /MD /Gy /EHsc /TP.

#include "types.h"

struct SVector3;

// 0x00b88770: cPlanetModel::RayCast (origin, direction, flags, radius, layer, mask)
void __stdcall PlanetRayCast(const SVector3* pOrigin, float fDirection, uint32_t nFlags,
                             float fRadius, int nLayer, int nMask);

// ---------------------------------------------------------------------------
// 0x00b8bb70: SP::cPlanetModel::FindClosestWater -- ray-cast downwards with a
// unit radius.
// ---------------------------------------------------------------------------
// @ 0x00b8bb70
void __stdcall FindClosestWater(const SVector3* pOrigin, float fDirection, uint32_t nFlags)
{
    PlanetRayCast(pOrigin, fDirection, nFlags, 1.0f, 1, 0);
}