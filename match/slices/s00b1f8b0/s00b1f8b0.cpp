// Factory (0x00b1f8b0): allocate a 0x1ac-byte object from the "Simulator/cPlaceableSound" zone and construct it (0xeabba0).
#include "game/types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct Object_b1f8b0 {
    char mData[0x1ac];
    Object_b1f8b0();   // 0x00eabba0
};

// @ 0x00b1f8b0
Object_b1f8b0* Create_b1f8b0()
{
    return new ("Simulator/cPlaceableSound", 0, 0, 0, 0) Object_b1f8b0();
}
