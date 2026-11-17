// Factory (0x00b1e900): allocate a 0x258-byte object from the "Simulator/cMissionFlight101" zone and construct it (0xc55f10).
#include "game/types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct Object_b1e900 {
    char mData[0x258];
    Object_b1e900();   // 0x00c55f10
};

// @ 0x00b1e900
Object_b1e900* Create_b1e900()
{
    return new ("Simulator/cMissionFlight101", 0, 0, 0, 0) Object_b1e900();
}
