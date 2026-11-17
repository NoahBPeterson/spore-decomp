// Factory (0x00b1ef90): allocate a 0x260-byte object from the "Simulator/cInteractiveOrnament" zone and construct it (0xc404c0).
#include "game/types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct Object_b1ef90 {
    char mData[0x260];
    Object_b1ef90();   // 0x00c404c0
};

// @ 0x00b1ef90
Object_b1ef90* Create_b1ef90()
{
    return new ("Simulator/cInteractiveOrnament", 0, 0, 0, 0) Object_b1ef90();
}
