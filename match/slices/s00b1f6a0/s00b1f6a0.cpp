// Factory (0x00b1f6a0): allocate a 0x158-byte object from the "Simulator/cEmpire" zone and construct it (0xc34830).
#include "game/types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct Object_b1f6a0 {
    char mData[0x158];
    Object_b1f6a0();   // 0x00c34830
};

// @ 0x00b1f6a0
Object_b1f6a0* Create_b1f6a0()
{
    return new ("Simulator/cEmpire", 0, 0, 0, 0) Object_b1f6a0();
}
