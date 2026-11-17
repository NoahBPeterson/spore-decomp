// Factory (0x00b1f050): allocate a 0x14c-byte object from the "Simulator/cTotemPole" zone and construct it (0xc8d6c0).
#include "game/types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct Object_b1f050 {
    char mData[0x14c];
    Object_b1f050();   // 0x00c8d6c0
};

// @ 0x00b1f050
Object_b1f050* Create_b1f050()
{
    return new ("Simulator/cTotemPole", 0, 0, 0, 0) Object_b1f050();
}
