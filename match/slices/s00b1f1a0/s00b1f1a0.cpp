// Factory (0x00b1f1a0): allocate a 0x140-byte object from the "Simulator/cInterCityRoad" zone and construct it (0xc40f10).
#include "game/types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct Object_b1f1a0 {
    char mData[0x140];
    Object_b1f1a0();   // 0x00c40f10
};

// @ 0x00b1f1a0
Object_b1f1a0* Create_b1f1a0()
{
    return new ("Simulator/cInterCityRoad", 0, 0, 0, 0) Object_b1f1a0();
}
