// Factory (0x00b1f0b0): allocate a 0x144-byte object from the "Simulator/cRock" zone and construct it (0xc7cde0).
#include "game/types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct Object_b1f0b0 {
    char mData[0x144];
    Object_b1f0b0();   // 0x00c7cde0
};

// @ 0x00b1f0b0
Object_b1f0b0* Create_b1f0b0()
{
    return new ("Simulator/cRock", 0, 0, 0, 0) Object_b1f0b0();
}
