// Factory (0x00b1f8e0): allocate a 0x168-byte object from the "Simulator/cPlaceableEffect" zone and construct it (0xf0d450).
#include "game/types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct Object_b1f8e0 {
    char mData[0x168];
    Object_b1f8e0();   // 0x00f0d450
};

// @ 0x00b1f8e0
Object_b1f8e0* Create_b1f8e0()
{
    return new ("Simulator/cPlaceableEffect", 0, 0, 0, 0) Object_b1f8e0();
}
