// Factory (0x00b1e8d0): allocate a 0x200-byte object from the "Simulator/cMissionFindAliens" zone and construct it (0xc55130).
#include "game/types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct Object_b1e8d0 {
    char mData[0x200];
    Object_b1e8d0();   // 0x00c55130
};

// @ 0x00b1e8d0
Object_b1e8d0* Create_b1e8d0()
{
    return new ("Simulator/cMissionFindAliens", 0, 0, 0, 0) Object_b1e8d0();
}
