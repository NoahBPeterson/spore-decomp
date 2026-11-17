// Factory (0x00b1f470): allocate a 0x12c-byte object from the "Simulator/cRotationBall" zone and construct it (0xd1d810).
#include "game/types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct Object_b1f470 {
    char mData[0x12c];
    Object_b1f470();   // 0x00d1d810
};

// @ 0x00b1f470
Object_b1f470* Create_b1f470()
{
    return new ("Simulator/cRotationBall", 0, 0, 0, 0) Object_b1f470();
}
