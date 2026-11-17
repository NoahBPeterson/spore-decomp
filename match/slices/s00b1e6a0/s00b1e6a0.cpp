// Factory (0x00b1e6a0): allocate a 0x228-byte object from the "Simulator/cMissionExplore" zone and construct it (0xc50f50).
#include "game/types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct Object_b1e6a0 {
    char mData[0x228];
    Object_b1e6a0();   // 0x00c50f50
};

// @ 0x00b1e6a0
Object_b1e6a0* Create_b1e6a0()
{
    return new ("Simulator/cMissionExplore", 0, 0, 0, 0) Object_b1e6a0();
}
