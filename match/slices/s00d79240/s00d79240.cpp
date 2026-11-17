// Factory (0x00d79240): allocate a 0x110-byte object from the "Simulator/cTribeGameBehaviorParty" zone and construct it (0xd791a0).
#include "game/types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct Object_d79240 {
    char mData[0x110];
    Object_d79240();   // 0x00d791a0
};

// @ 0x00d79240
Object_d79240* Create_d79240()
{
    return new ("Simulator/cTribeGameBehaviorParty", 0, 0, 0, 0) Object_d79240();
}
