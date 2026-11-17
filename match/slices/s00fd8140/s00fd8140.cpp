// Factory (0x00fd8140): allocate a 0x330-byte object from the "Graphics" zone and construct it (0xfd7b30).
#include "game/types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct Object_fd8140 {
    char mData[0x330];
    Object_fd8140();   // 0x00fd7b30
};

// @ 0x00fd8140
Object_fd8140* Create_fd8140()
{
    return new ("Graphics", 0, 0, 0, 0) Object_fd8140();
}
