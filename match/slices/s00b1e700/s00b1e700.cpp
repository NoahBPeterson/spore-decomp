// Factory (0x00b1e700): allocate a 0x200-byte object from the "Simulator/cMissionScan" zone and construct it (0xc5e740).
#include "game/types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct Object_b1e700 {
    char mData[0x200];
    Object_b1e700();   // 0x00c5e740
};

// @ 0x00b1e700
Object_b1e700* Create_b1e700()
{
    return new ("Simulator/cMissionScan", 0, 0, 0, 0) Object_b1e700();
}
