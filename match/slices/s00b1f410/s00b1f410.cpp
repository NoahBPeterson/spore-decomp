// Factory (0x00b1f410): allocate a 0x118-byte object from the "Simulator/cSoundLoopObject" zone and construct it (0xd06e70).
#include "game/types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct Object_b1f410 {
    char mData[0x118];
    Object_b1f410();   // 0x00d06e70
};

// @ 0x00b1f410
Object_b1f410* Create_b1f410()
{
    return new ("Simulator/cSoundLoopObject", 0, 0, 0, 0) Object_b1f410();
}
