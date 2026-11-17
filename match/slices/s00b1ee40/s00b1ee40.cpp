// Factory (0x00b1ee40): allocate a 0x8c-byte object from the "Simulator/cObstacle" zone and construct it (0xb73a30).
#include "game/types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct Object_b1ee40 {
    char mData[0x8c];
    Object_b1ee40();   // 0x00b73a30
};

// @ 0x00b1ee40
Object_b1ee40* Create_b1ee40()
{
    return new ("Simulator/cObstacle", 0, 0, 0, 0) Object_b1ee40();
}
