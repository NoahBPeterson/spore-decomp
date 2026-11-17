// Factory (0x00b1eb10): allocate a 0x340-byte object from the "Simulator/cBuildingEntertainment" zone and construct it (0xbd1c40).
#include "game/types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct Object_b1eb10 {
    char mData[0x340];
    Object_b1eb10();   // 0x00bd1c40
};

// @ 0x00b1eb10
Object_b1eb10* Create_b1eb10()
{
    return new ("Simulator/cBuildingEntertainment", 0, 0, 0, 0) Object_b1eb10();
}
