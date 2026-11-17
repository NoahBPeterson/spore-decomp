// Factory (0x00b1ef00): allocate a 0x130-byte object from the "Simulator/cNest" zone and construct it (0xc6a870).
#include "game/types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct Object_b1ef00 {
    char mData[0x130];
    Object_b1ef00();   // 0x00c6a870
};

// @ 0x00b1ef00
Object_b1ef00* Create_b1ef00()
{
    return new ("Simulator/cNest", 0, 0, 0, 0) Object_b1ef00();
}
