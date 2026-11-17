// Factory (0x00b1f320): allocate a 0x1f8-byte object from the "Simulator/cDefaultBeamProjectile" zone and construct it (0xcb88e0).
#include "game/types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct Object_b1f320 {
    char mData[0x1f8];
    Object_b1f320();   // 0x00cb88e0
};

// @ 0x00b1f320
Object_b1f320* Create_b1f320()
{
    return new ("Simulator/cDefaultBeamProjectile", 0, 0, 0, 0) Object_b1f320();
}
