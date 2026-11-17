// Factory (0x00b1e760): allocate a 0x200-byte object from the "Simulator/cMissionTrade" zone and construct it (0xc61f20).
#include "game/types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct Object_b1e760 {
    char mData[0x200];
    Object_b1e760();   // 0x00c61f20
};

// @ 0x00b1e760
Object_b1e760* Create_b1e760()
{
    return new ("Simulator/cMissionTrade", 0, 0, 0, 0) Object_b1e760();
}
