// Factory (0x00b1eab0): allocate a 0x340-byte object from the "Simulator/cBuildingIndustry" zone and construct it (0xbd1b70).
#include "game/types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct Object_b1eab0 {
    char mData[0x340];
    Object_b1eab0();   // 0x00bd1b70
};

// @ 0x00b1eab0
Object_b1eab0* Create_b1eab0()
{
    return new ("Simulator/cBuildingIndustry", 0, 0, 0, 0) Object_b1eab0();
}
