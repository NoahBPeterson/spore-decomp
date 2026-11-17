// Factory (0x00b1edb0): allocate a 0x4d8-byte object from the "Simulator/cCivilization" zone and construct it (0xbf78d0).
#include "game/types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct Object_b1edb0 {
    char mData[0x4d8];
    Object_b1edb0();   // 0x00bf78d0
};

// @ 0x00b1edb0
Object_b1edb0* Create_b1edb0()
{
    return new ("Simulator/cCivilization", 0, 0, 0, 0) Object_b1edb0();
}
