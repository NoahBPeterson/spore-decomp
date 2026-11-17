// Factory (0x00b1e610): allocate a 0x250-byte object from the "Simulator/cRaidEvent" zone and construct it (0xc5bd40).
#include "game/types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct Object_b1e610 {
    char mData[0x250];
    Object_b1e610();   // 0x00c5bd40
};

// @ 0x00b1e610
Object_b1e610* Create_b1e610()
{
    return new ("Simulator/cRaidEvent", 0, 0, 0, 0) Object_b1e610();
}
