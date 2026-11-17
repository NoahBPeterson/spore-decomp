// Factory (0x00b1f700): allocate a 0x98-byte object from the "Simulator/cPlayerInventory" zone and construct it (0xff5190).
#include "game/types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct Object_b1f700 {
    char mData[0x98];
    Object_b1f700();   // 0x00ff5190
};

// @ 0x00b1f700
Object_b1f700* Create_b1f700()
{
    return new ("Simulator/cPlayerInventory", 0, 0, 0, 0) Object_b1f700();
}
