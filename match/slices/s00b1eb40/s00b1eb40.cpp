// Factory (0x00b1eb40): allocate a 0x3c8-byte object from the "Simulator/cBuildingScenario" zone and construct it (0xbd2600).
#include "game/types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct Object_b1eb40 {
    char mData[0x3c8];
    Object_b1eb40();   // 0x00bd2600
};

// @ 0x00b1eb40
Object_b1eb40* Create_b1eb40()
{
    return new ("Simulator/cBuildingScenario", 0, 0, 0, 0) Object_b1eb40();
}
