// Factory (0x00f6a930): allocate a 0x20c-byte object from the "Terrain/TerrainEditor/cTerrainEditor" zone and construct it (0xf6a4b0).
#include "game/types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct Object_f6a930 {
    char mData[0x20c];
    Object_f6a930();   // 0x00f6a4b0
};

// @ 0x00f6a930
Object_f6a930* Create_f6a930()
{
    return new ("Terrain/TerrainEditor/cTerrainEditor", 0, 0, 0, 0) Object_f6a930();
}
