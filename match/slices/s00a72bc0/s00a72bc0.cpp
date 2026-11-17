// Factory (0x00a72bc0): allocate a 0x258-byte object from the "Swarm" zone and construct it (0xa6e1a0).
#include "game/types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct Object_a72bc0 {
    char mData[0x258];
    Object_a72bc0();   // 0x00a6e1a0
};

// @ 0x00a72bc0
Object_a72bc0* Create_a72bc0()
{
    return new ("Swarm", 0, 0, 0, 0) Object_a72bc0();
}
