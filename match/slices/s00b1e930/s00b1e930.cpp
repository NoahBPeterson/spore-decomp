// Factory (0x00b1e930): allocate a 0x220-byte object from the "Simulator/cMissionUseTool" zone and construct it (0xc62880).
#include "game/types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct Object_b1e930 {
    char mData[0x220];
    Object_b1e930();   // 0x00c62880
};

// @ 0x00b1e930
Object_b1e930* Create_b1e930()
{
    return new ("Simulator/cMissionUseTool", 0, 0, 0, 0) Object_b1e930();
}
