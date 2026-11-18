// Slice s00c84c60 -- Simulator::cSolarSystem::GetZoneBoundaryRelativeToSun (dev-only name).
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

// Cached per-star-type radius gas value; -1.0 means "not computed yet"
// (same cache the inlined copy in InitStar at 0x00c85a30 uses).
extern float gStarCache[13];                                     // 0x01579d10

bool  __cdecl IsGasStarType(int type);                           // 0x00c8b450
float __cdecl GetGasValue(int type);                             // 0x00c84420
float __cdecl GetStarRadius(int type);                           // 0x00c84120
float __cdecl GetStarTemperature(int type);                      // 0x00c84310

// @ 0x00c84c60
// Zone boundary distance from the sun: the cached star radius (or gas value)
// plus the zone's multiple of the star temperature.
float FUN_00c84c60(int type, int zone)
{
    if (gStarCache[type] < 0.0f)
        gStarCache[type] = IsGasStarType(type) ? GetGasValue(type) : GetStarRadius(type);

    float boundary = GetStarTemperature(type);
    switch (zone) {
    case 0:
        boundary = 15.0f;
        break;
    case 1:
        boundary = boundary * 85.0f;
        break;
    case 2:
        boundary = boundary * 195.0f;
        break;
    default:
        boundary = 0.0f;
        break;
    }
    return gStarCache[type] + boundary;
}
