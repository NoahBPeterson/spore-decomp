// Factory (0x00b1f0e0): allocate a 0x290-byte object from the "Simulator/cCommodityNode" zone and construct it (0xbff010).
#include "game/types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct Object_b1f0e0 {
    char mData[0x290];
    Object_b1f0e0();   // 0x00bff010
};

// @ 0x00b1f0e0
Object_b1f0e0* Create_b1f0e0()
{
    return new ("Simulator/cCommodityNode", 0, 0, 0, 0) Object_b1f0e0();
}
