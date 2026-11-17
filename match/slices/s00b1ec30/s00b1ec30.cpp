// Factory (0x00b1ec30): allocate a 0x818-byte object from the "Simulator/cCity" zone and construct it (0xbe6310).
#include "game/types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct Object_b1ec30 {
    char mData[0x818];
    Object_b1ec30();   // 0x00be6310
};

// @ 0x00b1ec30
Object_b1ec30* Create_b1ec30()
{
    return new ("Simulator/cCity", 0, 0, 0, 0) Object_b1ec30();
}
