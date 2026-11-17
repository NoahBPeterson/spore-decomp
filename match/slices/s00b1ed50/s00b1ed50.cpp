// Factory (0x00b1ed50): allocate a 0x668-byte object from the "Simulator/cPlanetaryArtifact" zone and construct it (0xc74a50).
#include "game/types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct Object_b1ed50 {
    char mData[0x668];
    Object_b1ed50();   // 0x00c74a50
};

// @ 0x00b1ed50
Object_b1ed50* Create_b1ed50()
{
    return new ("Simulator/cPlanetaryArtifact", 0, 0, 0, 0) Object_b1ed50();
}
