// Factory (0x00a0bc60): allocate a 0x88-byte object from the "Anim/Manager/singleton" zone and construct it (0xa0b9b0).
#include "game/types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct Object_a0bc60 {
    char mData[0x88];
    Object_a0bc60();   // 0x00a0b9b0
};

// @ 0x00a0bc60
Object_a0bc60* Create_a0bc60()
{
    return new ("Anim/Manager/singleton", 0, 0, 0, 0) Object_a0bc60();
}
