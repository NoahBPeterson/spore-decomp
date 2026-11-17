// Factory (0x00b1eae0): allocate a 0x340-byte object from the "Simulator/cBuildingHouse" zone and construct it (0xbd1c00).
#include "game/types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct Object_b1eae0 {
    char mData[0x340];
    Object_b1eae0();   // 0x00bd1c00
};

// @ 0x00b1eae0
Object_b1eae0* Create_b1eae0()
{
    return new ("Simulator/cBuildingHouse", 0, 0, 0, 0) Object_b1eae0();
}
