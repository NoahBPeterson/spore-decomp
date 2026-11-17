// Factory (0x00b1f4d0): allocate a 0x138-byte object from the "Simulator/cTargetMorphHandle" zone and construct it (0xc63e30).
#include "game/types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct Object_b1f4d0 {
    char mData[0x138];
    Object_b1f4d0();   // 0x00c63e30
};

// @ 0x00b1f4d0
Object_b1f4d0* Create_b1f4d0()
{
    return new ("Simulator/cTargetMorphHandle", 0, 0, 0, 0) Object_b1f4d0();
}
