// Factory (0x00b1e6d0): allocate a 0x200-byte object from the "Simulator/cMissionWar" zone and construct it (0xc62cc0).
#include "game/types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct Object_b1e6d0 {
    char mData[0x200];
    Object_b1e6d0();   // 0x00c62cc0
};

// @ 0x00b1e6d0
Object_b1e6d0* Create_b1e6d0()
{
    return new ("Simulator/cMissionWar", 0, 0, 0, 0) Object_b1e6d0();
}
