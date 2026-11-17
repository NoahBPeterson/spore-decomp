// Factory (0x00b1f820): allocate a 0x98-byte object from the "Simulator/cTribeToTribeMission" zone and construct it (0xc2f470).
#include "game/types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct Object_b1f820 {
    char mData[0x98];
    Object_b1f820();   // 0x00c2f470
};

// @ 0x00b1f820
Object_b1f820* Create_b1f820()
{
    return new ("Simulator/cTribeToTribeMission", 0, 0, 0, 0) Object_b1f820();
}
