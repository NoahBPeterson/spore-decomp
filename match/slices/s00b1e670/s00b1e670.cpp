// Factory (0x00b1e670): allocate a 0x238-byte object from the "Simulator/cMissionEradicate" zone and construct it (0xc4f7b0).
#include "game/types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct Object_b1e670 {
    char mData[0x238];
    Object_b1e670();   // 0x00c4f7b0
};

// @ 0x00b1e670
Object_b1e670* Create_b1e670()
{
    return new ("Simulator/cMissionEradicate", 0, 0, 0, 0) Object_b1e670();
}
