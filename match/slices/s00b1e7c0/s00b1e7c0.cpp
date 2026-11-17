// Factory (0x00b1e7c0): allocate a 0x250-byte object from the "Simulator/cMissionMultiDelivery" zone and construct it (0xc58170).
#include "game/types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct Object_b1e7c0 {
    char mData[0x250];
    Object_b1e7c0();   // 0x00c58170
};

// @ 0x00b1e7c0
Object_b1e7c0* Create_b1e7c0()
{
    return new ("Simulator/cMissionMultiDelivery", 0, 0, 0, 0) Object_b1e7c0();
}
