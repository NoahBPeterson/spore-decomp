// Factory (0x00b1ec00): allocate a 0x218-byte object from the "Simulator/cCulturalTarget" zone and construct it (0xbdab60).
#include "game/types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct Object_b1ec00 {
    char mData[0x218];
    Object_b1ec00();   // 0x00bdab60
};

// @ 0x00b1ec00
Object_b1ec00* Create_b1ec00()
{
    return new ("Simulator/cCulturalTarget", 0, 0, 0, 0) Object_b1ec00();
}
