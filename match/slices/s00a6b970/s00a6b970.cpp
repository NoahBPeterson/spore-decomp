// Factory (0x00a6b970): allocate a 0x9c-byte object from the "Swarm" zone and construct it (0xa6b8a0).
#include "game/types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct Object_a6b970 {
    char mData[0x9c];
    Object_a6b970();   // 0x00a6b8a0
};

// @ 0x00a6b970
Object_a6b970* Create_a6b970()
{
    return new ("Swarm", 0, 0, 0, 0) Object_a6b970();
}
