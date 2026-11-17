// Factory (0x00b1f670): allocate a 0x20c0-byte object from the "Simulator/cSimPlanetLowLOD" zone and construct it (0xc7ff90).
#include "game/types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct Object_b1f670 {
    char mData[0x20c0];
    Object_b1f670();   // 0x00c7ff90
};

// @ 0x00b1f670
Object_b1f670* Create_b1f670()
{
    return new ("Simulator/cSimPlanetLowLOD", 0, 0, 0, 0) Object_b1f670();
}
