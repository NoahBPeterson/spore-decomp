// Factory (0x00b1ec90): allocate a 0xd98-byte object from the "Simulator/cVehicle" zone and construct it (0xca78a0).
#include "game/types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct Object_b1ec90 {
    char mData[0xd98];
    Object_b1ec90();   // 0x00ca78a0
};

// @ 0x00b1ec90
Object_b1ec90* Create_b1ec90()
{
    return new ("Simulator/cVehicle", 0, 0, 0, 0) Object_b1ec90();
}
