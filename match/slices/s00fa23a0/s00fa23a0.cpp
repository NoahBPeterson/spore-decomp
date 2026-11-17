// Factory (0x00fa23a0): allocate a 0xa50-byte object from the "Terrain/Sphere/cTerrainSphere" zone and construct it (0xfa1bc0).
#include "game/types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct Object_fa23a0 {
    char mData[0xa50];
    Object_fa23a0();   // 0x00fa1bc0
};

// @ 0x00fa23a0
Object_fa23a0* Create_fa23a0()
{
    return new ("Terrain/Sphere/cTerrainSphere", 0, 0, 0, 0) Object_fa23a0();
}
