// Factory (0x00b1f4a0): allocate a 0x118-byte object from the "Simulator/cMorphHandle" zone and construct it (0xc63be0).
#include "game/types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct Object_b1f4a0 {
    char mData[0x118];
    Object_b1f4a0();   // 0x00c63be0
};

// @ 0x00b1f4a0
Object_b1f4a0* Create_b1f4a0()
{
    return new ("Simulator/cMorphHandle", 0, 0, 0, 0) Object_b1f4a0();
}
