// Factory (0x0070a040): allocate a 0x190-byte object from the "Graphics" zone and construct it (0x709c40).
#include "game/types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct Object_70a040 {
    char mData[0x190];
    Object_70a040();   // 0x00709c40
};

// @ 0x0070a040
Object_70a040* Create_70a040()
{
    return new ("Graphics", 0, 0, 0, 0) Object_70a040();
}
