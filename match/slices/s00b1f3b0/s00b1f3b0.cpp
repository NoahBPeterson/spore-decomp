// Factory (0x00b1f3b0): allocate a 0x558-byte object from the "Simulator/cResourceProjectile" zone and construct it (0xcb9010).
#include "game/types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct Object_b1f3b0 {
    char mData[0x558];
    Object_b1f3b0();   // 0x00cb9010
};

// @ 0x00b1f3b0
Object_b1f3b0* Create_b1f3b0()
{
    return new ("Simulator/cResourceProjectile", 0, 0, 0, 0) Object_b1f3b0();
}
