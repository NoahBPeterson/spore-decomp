// Factory (0x00b1e790): allocate a 0x1f8-byte object from the "Simulator/cMissionTradeRoute" zone and construct it (0xc62370).
#include "game/types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct Object_b1e790 {
    char mData[0x1f8];
    Object_b1e790();   // 0x00c62370
};

// @ 0x00b1e790
Object_b1e790* Create_b1e790()
{
    return new ("Simulator/cMissionTradeRoute", 0, 0, 0, 0) Object_b1e790();
}
