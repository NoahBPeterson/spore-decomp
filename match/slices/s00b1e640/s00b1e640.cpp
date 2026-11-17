// Factory (0x00b1e640): allocate a 0x1f8-byte object from the "Simulator/cMissionColonize" zone and construct it (0xc4def0).
#include "game/types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct Object_b1e640 {
    char mData[0x1f8];
    Object_b1e640();   // 0x00c4def0
};

// @ 0x00b1e640
Object_b1e640* Create_b1e640()
{
    return new ("Simulator/cMissionColonize", 0, 0, 0, 0) Object_b1e640();
}
