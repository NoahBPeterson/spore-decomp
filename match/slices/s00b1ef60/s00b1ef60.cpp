// Factory (0x00b1ef60): allocate a 0x228-byte object from the "Simulator/cEgg" zone and construct it (0xc6a270).
#include "game/types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct Object_b1ef60 {
    char mData[0x228];
    Object_b1ef60();   // 0x00c6a270
};

// @ 0x00b1ef60
Object_b1ef60* Create_b1ef60()
{
    return new ("Simulator/cEgg", 0, 0, 0, 0) Object_b1ef60();
}
