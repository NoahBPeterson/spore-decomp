// Factory (0x00b1f170): allocate a 0x250-byte object from the "Simulator/cHitSphere" zone and construct it (0xc3f4a0).
#include "game/types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct Object_b1f170 {
    char mData[0x250];
    Object_b1f170();   // 0x00c3f4a0
};

// @ 0x00b1f170
Object_b1f170* Create_b1f170()
{
    return new ("Simulator/cHitSphere", 0, 0, 0, 0) Object_b1f170();
}
