// Factory (0x00b1f760): allocate a 0x260-byte object from the "Simulator/cTribeHut" zone and construct it (0xc9bf90).
#include "game/types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct Object_b1f760 {
    char mData[0x260];
    Object_b1f760();   // 0x00c9bf90
};

// @ 0x00b1f760
Object_b1f760* Create_b1f760()
{
    return new ("Simulator/cTribeHut", 0, 0, 0, 0) Object_b1f760();
}
