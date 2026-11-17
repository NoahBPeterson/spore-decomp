// Factory (0x00ef3df0): allocate a 0x150-byte object from the "Sporepedia/Scenario/cSPScenarioModeSporepediaAssetView" zone and construct it (0xef3b40).
#include "game/types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct Object_ef3df0 {
    char mData[0x150];
    Object_ef3df0();   // 0x00ef3b40
};

// @ 0x00ef3df0
Object_ef3df0* Create_ef3df0()
{
    return new ("Sporepedia/Scenario/cSPScenarioModeSporepediaAssetView", 0, 0, 0, 0) Object_ef3df0();
}
