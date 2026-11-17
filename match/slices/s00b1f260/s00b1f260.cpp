// Factory (0x00b1f260): allocate a 0x520-byte object from the "Simulator/cFlakProjectile" zone and construct it (0xcb79f0).
#include "game/types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct Object_b1f260 {
    char mData[0x520];
    Object_b1f260();   // 0x00cb79f0
};

// @ 0x00b1f260
Object_b1f260* Create_b1f260()
{
    return new ("Simulator/cFlakProjectile", 0, 0, 0, 0) Object_b1f260();
}
