// Factory (0x00eb8460): allocate a 0x138-byte object from the "Sporepedia/Scenario/cAdventureCreatureAssetView" zone and construct it (0xeb82c0).
#include "game/types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct Object_eb8460 {
    char mData[0x138];
    Object_eb8460();   // 0x00eb82c0
};

// @ 0x00eb8460
Object_eb8460* Create_eb8460()
{
    return new ("Sporepedia/Scenario/cAdventureCreatureAssetView", 0, 0, 0, 0) Object_eb8460();
}
