// Factory (0x00b1f560): allocate a 0x1b8-byte object from the "Simulator/cSimpleRotationBall" zone and construct it (0xc65f00).
#include "game/types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct Object_b1f560 {
    char mData[0x1b8];
    Object_b1f560();   // 0x00c65f00
};

// @ 0x00b1f560
Object_b1f560* Create_b1f560()
{
    return new ("Simulator/cSimpleRotationBall", 0, 0, 0, 0) Object_b1f560();
}
