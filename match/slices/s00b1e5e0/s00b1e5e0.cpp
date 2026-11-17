// Factory (0x00b1e5e0): allocate a 0x228-byte object from the "Simulator/cRaidPlunderEvent" zone and construct it (0xc5bc30).
#include "game/types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct Object_b1e5e0 {
    char mData[0x228];
    Object_b1e5e0();   // 0x00c5bc30
};

// @ 0x00b1e5e0
Object_b1e5e0* Create_b1e5e0()
{
    return new ("Simulator/cRaidPlunderEvent", 0, 0, 0, 0) Object_b1e5e0();
}
