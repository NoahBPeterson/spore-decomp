// Factory (0x00b1eea0): allocate a 0x170-byte object from the "Simulator/cFruit" zone and construct it (0xb01910).
#include "game/types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct Object_b1eea0 {
    char mData[0x170];
    Object_b1eea0();   // 0x00b01910
};

// @ 0x00b1eea0
Object_b1eea0* Create_b1eea0()
{
    return new ("Simulator/cFruit", 0, 0, 0, 0) Object_b1eea0();
}
