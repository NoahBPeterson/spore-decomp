// Factory (0x00b1f2f0): allocate a 0x610-byte object from the "Simulator/cSpaceDefenseMissile" zone and construct it (0xcb84f0).
#include "game/types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct Object_b1f2f0 {
    char mData[0x610];
    Object_b1f2f0();   // 0x00cb84f0
};

// @ 0x00b1f2f0
Object_b1f2f0* Create_b1f2f0()
{
    return new ("Simulator/cSpaceDefenseMissile", 0, 0, 0, 0) Object_b1f2f0();
}
