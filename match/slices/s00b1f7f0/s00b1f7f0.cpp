// Factory (0x00b1f7f0): allocate a 0x90-byte object from the "Simulator/cCreatureTutorialMission" zone and construct it (0xc2f340).
#include "game/types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct Object_b1f7f0 {
    char mData[0x90];
    Object_b1f7f0();   // 0x00c2f340
};

// @ 0x00b1f7f0
Object_b1f7f0* Create_b1f7f0()
{
    return new ("Simulator/cCreatureTutorialMission", 0, 0, 0, 0) Object_b1f7f0();
}
