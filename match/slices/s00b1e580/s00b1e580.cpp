// Factory (0x00b1e580): allocate a 0x268-byte object from the "Simulator/cMissionFetch" zone and construct it (0xc52fa0).
#include "game/types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct Object_b1e580 {
    char mData[0x268];
    Object_b1e580();   // 0x00c52fa0
};

// @ 0x00b1e580
Object_b1e580* Create_b1e580()
{
    return new ("Simulator/cMissionFetch", 0, 0, 0, 0) Object_b1e580();
}
