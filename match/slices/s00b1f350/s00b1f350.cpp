// Factory (0x00b1f350): allocate a 0x170-byte object from the "Simulator/cDefaultAoEArea" zone and construct it (0xcb8cd0).
#include "game/types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct Object_b1f350 {
    char mData[0x170];
    Object_b1f350();   // 0x00cb8cd0
};

// @ 0x00b1f350
Object_b1f350* Create_b1f350()
{
    return new ("Simulator/cDefaultAoEArea", 0, 0, 0, 0) Object_b1f350();
}
