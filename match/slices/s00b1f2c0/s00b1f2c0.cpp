// Factory (0x00b1f2c0): allocate a 0x5f0-byte object from the "Simulator/cDeepSpaceProjectile" zone and construct it (0xcbcb70).
#include "game/types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct Object_b1f2c0 {
    char mData[0x5f0];
    Object_b1f2c0();   // 0x00cbcb70
};

// @ 0x00b1f2c0
Object_b1f2c0* Create_b1f2c0()
{
    return new ("Simulator/cDeepSpaceProjectile", 0, 0, 0, 0) Object_b1f2c0();
}
