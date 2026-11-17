// Factory (0x00b1e990): allocate a 0x218-byte object from the "Simulator/cMissionChangeArchetype" zone and construct it (0xc4dbf0).
#include "game/types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct Object_b1e990 {
    char mData[0x218];
    Object_b1e990();   // 0x00c4dbf0
};

// @ 0x00b1e990
Object_b1e990* Create_b1e990()
{
    return new ("Simulator/cMissionChangeArchetype", 0, 0, 0, 0) Object_b1e990();
}
