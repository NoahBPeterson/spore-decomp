// Factory (0x00b1ea50): allocate a 0x16c-byte object from the "Simulator/cGameTerrainCursor" zone and construct it (0xb30240).
#include "game/types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct Object_b1ea50 {
    char mData[0x16c];
    Object_b1ea50();   // 0x00b30240
};

// @ 0x00b1ea50
Object_b1ea50* Create_b1ea50()
{
    return new ("Simulator/cGameTerrainCursor", 0, 0, 0, 0) Object_b1ea50();
}
