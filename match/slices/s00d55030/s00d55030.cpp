// Factory (0x00d55030): allocate a 0x100-byte object from the "Simulator/cBehaviorSpaceTurret" zone and construct it (0xd54fa0).
#include "game/types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct Object_d55030 {
    char mData[0x100];
    Object_d55030();   // 0x00d54fa0
};

// @ 0x00d55030
Object_d55030* Create_d55030()
{
    return new ("Simulator/cBehaviorSpaceTurret", 0, 0, 0, 0) Object_d55030();
}
