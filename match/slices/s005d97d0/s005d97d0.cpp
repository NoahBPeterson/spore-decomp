// Factory (0x005d97d0): allocate a 0xb8-byte object from the "Editor" zone and construct it (0x5d96d0).
#include "game/types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct Object_5d97d0 {
    char mData[0xb8];
    Object_5d97d0();   // 0x005d96d0
};

// @ 0x005d97d0
Object_5d97d0* Create_5d97d0()
{
    return new ("Editor", 0, 0, 0, 0) Object_5d97d0();
}
