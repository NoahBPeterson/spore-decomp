// Factory (0x00b1f290): allocate a 0x5f0-byte object from the "Simulator/cDefaultToolProjectile" zone and construct it (0xcbc930).
#include "game/types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct Object_b1f290 {
    char mData[0x5f0];
    Object_b1f290();   // 0x00cbc930
};

// @ 0x00b1f290
Object_b1f290* Create_b1f290()
{
    return new ("Simulator/cDefaultToolProjectile", 0, 0, 0, 0) Object_b1f290();
}
