// Factory (0x00b1f1d0): allocate a 0x19e0-byte object from the "Simulator/cTribe" zone and construct it (0xc982a0).
#include "game/types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct Object_b1f1d0 {
    char mData[0x19e0];
    Object_b1f1d0();   // 0x00c982a0
};

// @ 0x00b1f1d0
Object_b1f1d0* Create_b1f1d0()
{
    return new ("Simulator/cTribe", 0, 0, 0, 0) Object_b1f1d0();
}
