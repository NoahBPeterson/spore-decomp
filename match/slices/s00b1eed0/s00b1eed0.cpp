// Factory (0x00b1eed0): allocate a 0x1d4-byte object from the "Simulator/cFruitGroup" zone and construct it (0xb02ca0).
#include "game/types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct Object_b1eed0 {
    char mData[0x1d4];
    Object_b1eed0();   // 0x00b02ca0
};

// @ 0x00b1eed0
Object_b1eed0* Create_b1eed0()
{
    return new ("Simulator/cFruitGroup", 0, 0, 0, 0) Object_b1eed0();
}
