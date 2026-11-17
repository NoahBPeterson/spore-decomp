// Factory (0x00b1f440): allocate a 0x134-byte object from the "Simulator/cRotationRing" zone and construct it (0xd1dc20).
#include "game/types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct Object_b1f440 {
    char mData[0x134];
    Object_b1f440();   // 0x00d1dc20
};

// @ 0x00b1f440
Object_b1f440* Create_b1f440()
{
    return new ("Simulator/cRotationRing", 0, 0, 0, 0) Object_b1f440();
}
