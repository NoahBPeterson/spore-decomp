// Factory (0x00b1ee10): allocate a 0x1038-byte object from the "Simulator/cCreatureCitizen" zone and construct it (0xc26e00).
#include "game/types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct Object_b1ee10 {
    char mData[0x1038];
    Object_b1ee10();   // 0x00c26e00
};

// @ 0x00b1ee10
Object_b1ee10* Create_b1ee10()
{
    return new ("Simulator/cCreatureCitizen", 0, 0, 0, 0) Object_b1ee10();
}
