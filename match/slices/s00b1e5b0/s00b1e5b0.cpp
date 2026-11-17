// Factory (0x00b1e5b0): allocate a 0x1f8-byte object from the "Simulator/cMissionMakeAlly" zone and construct it (0xc56970).
#include "game/types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct Object_b1e5b0 {
    char mData[0x1f8];
    Object_b1e5b0();   // 0x00c56970
};

// @ 0x00b1e5b0
Object_b1e5b0* Create_b1e5b0()
{
    return new ("Simulator/cMissionMakeAlly", 0, 0, 0, 0) Object_b1e5b0();
}
