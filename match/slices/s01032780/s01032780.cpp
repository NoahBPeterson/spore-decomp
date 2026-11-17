// Factory (0x01032780): allocate a 0xa0-byte object from the "Simulator/cSpaceGameBehaviorAbducted" zone and construct it (0x10326d0).
#include "game/types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct Object_1032780 {
    char mData[0xa0];
    Object_1032780();   // 0x010326d0
};

// @ 0x01032780
Object_1032780* Create_1032780()
{
    return new ("Simulator/cSpaceGameBehaviorAbducted", 0, 0, 0, 0) Object_1032780();
}
