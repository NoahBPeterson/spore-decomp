// Factory (0x00b1e7f0): allocate a 0x260-byte object from the "Simulator/cMissionBiosphere" zone and construct it (0xc4c2f0).
#include "game/types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct Object_b1e7f0 {
    char mData[0x260];
    Object_b1e7f0();   // 0x00c4c2f0
};

// @ 0x00b1e7f0
Object_b1e7f0* Create_b1e7f0()
{
    return new ("Simulator/cMissionBiosphere", 0, 0, 0, 0) Object_b1e7f0();
}
