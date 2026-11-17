// Factory (0x00b1ecc0): allocate a 0x358-byte object from the "Simulator/cCityWalls" zone and construct it (0xbedb70).
#include "game/types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct Object_b1ecc0 {
    char mData[0x358];
    Object_b1ecc0();   // 0x00bedb70
};

// @ 0x00b1ecc0
Object_b1ecc0* Create_b1ecc0()
{
    return new ("Simulator/cCityWalls", 0, 0, 0, 0) Object_b1ecc0();
}
