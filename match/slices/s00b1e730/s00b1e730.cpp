// Factory (0x00b1e730): allocate a 0x1f8-byte object from the "Simulator/cMissionTerraform" zone and construct it (0xc606e0).
#include "game/types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct Object_b1e730 {
    char mData[0x1f8];
    Object_b1e730();   // 0x00c606e0
};

// @ 0x00b1e730
Object_b1e730* Create_b1e730()
{
    return new ("Simulator/cMissionTerraform", 0, 0, 0, 0) Object_b1e730();
}
