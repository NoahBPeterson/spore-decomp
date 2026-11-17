// Factory (0x00b1f110): allocate a 0x638-byte object from the "Simulator/cMovableDestructibleOrnament" zone and construct it (0xc68e30).
#include "game/types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct Object_b1f110 {
    char mData[0x638];
    Object_b1f110();   // 0x00c68e30
};

// @ 0x00b1f110
Object_b1f110* Create_b1f110()
{
    return new ("Simulator/cMovableDestructibleOrnament", 0, 0, 0, 0) Object_b1f110();
}
