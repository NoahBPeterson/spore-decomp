// Factory (0x00b1e9f0): allocate a 0x1f8-byte object from the "Simulator/cMissionAdventure" zone and construct it (0xc4af60).
#include "game/types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct Object_b1e9f0 {
    char mData[0x1f8];
    Object_b1e9f0();   // 0x00c4af60
};

// @ 0x00b1e9f0
Object_b1e9f0* Create_b1e9f0()
{
    return new ("Simulator/cMissionAdventure", 0, 0, 0, 0) Object_b1e9f0();
}
