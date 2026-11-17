// Factory (0x00f95da0): allocate a 0x9c-byte object from the "Terrain/ShaderManager/cTerrainShaderMgr" zone and construct it (0xf95cf0).
#include "game/types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct Object_f95da0 {
    char mData[0x9c];
    Object_f95da0();   // 0x00f95cf0
};

// @ 0x00f95da0
Object_f95da0* Create_f95da0()
{
    return new ("Terrain/ShaderManager/cTerrainShaderMgr", 0, 0, 0, 0) Object_f95da0();
}
