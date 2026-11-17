// Factory (0x00b1efc0): allocate a 0x1c8-byte object from the "Simulator/cGameplayMarker" zone and construct it (0xc3efb0).
#include "game/types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct Object_b1efc0 {
    char mData[0x1c8];
    Object_b1efc0();   // 0x00c3efb0
};

// @ 0x00b1efc0
Object_b1efc0* Create_b1efc0()
{
    return new ("Simulator/cGameplayMarker", 0, 0, 0, 0) Object_b1efc0();
}
