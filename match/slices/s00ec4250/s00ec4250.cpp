// Factory (0x00ec4250): allocate a 0x8c-byte object from the "Sporepedia/AssetData/cSPScenarioAssetData" zone and construct it (0xec41e0).
#include "game/types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct Object_ec4250 {
    char mData[0x8c];
    Object_ec4250();   // 0x00ec41e0
};

// @ 0x00ec4250
Object_ec4250* Create_ec4250()
{
    return new ("Sporepedia/AssetData/cSPScenarioAssetData", 0, 0, 0, 0) Object_ec4250();
}
