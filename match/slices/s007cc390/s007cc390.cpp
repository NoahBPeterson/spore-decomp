// Factory (0x007cc390): allocate a 0xb4-byte object from the "App" zone and construct it (0x7cc310).
#include "game/types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct Object_7cc390 {
    char mData[0xb4];
    Object_7cc390();   // 0x007cc310
};

// @ 0x007cc390
Object_7cc390* Create_7cc390()
{
    return new ("App", 0, 0, 0, 0) Object_7cc390();
}
