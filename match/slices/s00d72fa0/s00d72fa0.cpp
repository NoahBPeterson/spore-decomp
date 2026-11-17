// Factory (0x00d72fa0): allocate a 0xc8-byte object from the "Simulator/cTribeGameBehaviorFish" zone and construct it (0xd72e70).
#include "game/types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct Object_d72fa0 {
    char mData[0xc8];
    Object_d72fa0();   // 0x00d72e70
};

// @ 0x00d72fa0
Object_d72fa0* Create_d72fa0()
{
    return new ("Simulator/cTribeGameBehaviorFish", 0, 0, 0, 0) Object_d72fa0();
}
