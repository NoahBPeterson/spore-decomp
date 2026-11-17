// Factory (0x00b1eb70): allocate a 0x6d0-byte object from the "Simulator/cTurret" zone and construct it (0xbcded0).
#include "game/types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct Object_b1eb70 {
    char mData[0x6d0];
    Object_b1eb70();   // 0x00bcded0
};

// @ 0x00b1eb70
Object_b1eb70* Create_b1eb70()
{
    return new ("Simulator/cTurret", 0, 0, 0, 0) Object_b1eb70();
}
