// Factory (0x00b1f230): allocate a 0x538-byte object from the "Simulator/cArtilleryProjectile" zone and construct it (0xcb6ed0).
#include "game/types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct Object_b1f230 {
    char mData[0x538];
    Object_b1f230();   // 0x00cb6ed0
};

// @ 0x00b1f230
Object_b1f230* Create_b1f230()
{
    return new ("Simulator/cArtilleryProjectile", 0, 0, 0, 0) Object_b1f230();
}
