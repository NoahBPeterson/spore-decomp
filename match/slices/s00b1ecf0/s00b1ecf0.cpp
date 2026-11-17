// Factory (0x00b1ecf0): allocate a 0x114-byte object from the "Simulator/cCityTerritory" zone and construct it (0xbeb950).
#include "game/types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct Object_b1ecf0 {
    char mData[0x114];
    Object_b1ecf0();   // 0x00beb950
};

// @ 0x00b1ecf0
Object_b1ecf0* Create_b1ecf0()
{
    return new ("Simulator/cCityTerritory", 0, 0, 0, 0) Object_b1ecf0();
}
