// Factory (0x00b1ebd0): allocate a 0x13c-byte object from the "Simulator/cGameBundle" zone and construct it (0xc35dc0).
#include "game/types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct Object_b1ebd0 {
    char mData[0x13c];
    Object_b1ebd0();   // 0x00c35dc0
};

// @ 0x00b1ebd0
Object_b1ebd0* Create_b1ebd0()
{
    return new ("Simulator/cGameBundle", 0, 0, 0, 0) Object_b1ebd0();
}
