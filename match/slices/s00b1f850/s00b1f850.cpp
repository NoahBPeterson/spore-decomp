// Factory (0x00b1f850): allocate a 0x88-byte object from the "Simulator/cFindMission" zone and construct it (0xc2f830).
#include "game/types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct Object_b1f850 {
    char mData[0x88];
    Object_b1f850();   // 0x00c2f830
};

// @ 0x00b1f850
Object_b1f850* Create_b1f850()
{
    return new ("Simulator/cFindMission", 0, 0, 0, 0) Object_b1f850();
}
