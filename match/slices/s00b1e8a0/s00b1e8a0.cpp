// Factory (0x00b1e8a0): allocate a 0x1f8-byte object from the "Simulator/cMissionBalance" zone and construct it (0xc4b570).
#include "game/types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct Object_b1e8a0 {
    char mData[0x1f8];
    Object_b1e8a0();   // 0x00c4b570
};

// @ 0x00b1e8a0
Object_b1e8a0* Create_b1e8a0()
{
    return new ("Simulator/cMissionBalance", 0, 0, 0, 0) Object_b1e8a0();
}
