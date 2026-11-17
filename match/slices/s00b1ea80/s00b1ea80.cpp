// Factory (0x00b1ea80): allocate a 0x378-byte object from the "Simulator/cBuildingCityHall" zone and construct it (0xbd1af0).
#include "game/types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct Object_b1ea80 {
    char mData[0x378];
    Object_b1ea80();   // 0x00bd1af0
};

// @ 0x00b1ea80
Object_b1ea80* Create_b1ea80()
{
    return new ("Simulator/cBuildingCityHall", 0, 0, 0, 0) Object_b1ea80();
}
