// Factory (0x00b1f530): allocate a 0x1d8-byte object from the "Simulator/cSimpleRotationRing" zone and construct it (0xc65c00).
#include "game/types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct Object_b1f530 {
    char mData[0x1d8];
    Object_b1f530();   // 0x00c65c00
};

// @ 0x00b1f530
Object_b1f530* Create_b1f530()
{
    return new ("Simulator/cSimpleRotationRing", 0, 0, 0, 0) Object_b1f530();
}
