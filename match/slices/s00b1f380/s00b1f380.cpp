// Factory (0x00b1f380): allocate a 0x588-byte object from the "Simulator/cCulturalProjectile" zone and construct it (0xcb8dd0).
#include "game/types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct Object_b1f380 {
    char mData[0x588];
    Object_b1f380();   // 0x00cb8dd0
};

// @ 0x00b1f380
Object_b1f380* Create_b1f380()
{
    return new ("Simulator/cCulturalProjectile", 0, 0, 0, 0) Object_b1f380();
}
