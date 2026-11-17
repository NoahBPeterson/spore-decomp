// Factory (0x00b1f140): allocate a 0x250-byte object from the "Simulator/cSolarHitSphere" zone and construct it (0xc3f6f0).
#include "game/types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct Object_b1f140 {
    char mData[0x250];
    Object_b1f140();   // 0x00c3f6f0
};

// @ 0x00b1f140
Object_b1f140* Create_b1f140()
{
    return new ("Simulator/cSolarHitSphere", 0, 0, 0, 0) Object_b1f140();
}
