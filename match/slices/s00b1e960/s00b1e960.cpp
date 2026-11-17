// Factory (0x00b1e960): allocate a 0x200-byte object from the "Simulator/cMissionStory201" zone and construct it (0xc5f1b0).
#include "game/types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct Object_b1e960 {
    char mData[0x200];
    Object_b1e960();   // 0x00c5f1b0
};

// @ 0x00b1e960
Object_b1e960* Create_b1e960()
{
    return new ("Simulator/cMissionStory201", 0, 0, 0, 0) Object_b1e960();
}
