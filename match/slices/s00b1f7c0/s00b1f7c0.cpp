// Factory (0x00b1f7c0): allocate a 0xd0-byte object from the "Simulator/cCreatureSpeciesMission" zone and construct it (0xc2f8c0).
#include "game/types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct Object_b1f7c0 {
    char mData[0xd0];
    Object_b1f7c0();   // 0x00c2f8c0
};

// @ 0x00b1f7c0
Object_b1f7c0* Create_b1f7c0()
{
    return new ("Simulator/cCreatureSpeciesMission", 0, 0, 0, 0) Object_b1f7c0();
}
