// Factory (0x00b1f080): allocate a 0x110-byte object from the "Simulator/cTribeFoodMat" zone and construct it (0xc9ba80).
#include "game/types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct Object_b1f080 {
    char mData[0x110];
    Object_b1f080();   // 0x00c9ba80
};

// @ 0x00b1f080
Object_b1f080* Create_b1f080()
{
    return new ("Simulator/cTribeFoodMat", 0, 0, 0, 0) Object_b1f080();
}
