// Factory (0x00b1ea20): allocate a 0x12d8-byte object from the "Simulator/cPlayer" zone and construct it (0xc7b790).
#include "game/types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct Object_b1ea20 {
    char mData[0x12d8];
    Object_b1ea20();   // 0x00c7b790
};

// @ 0x00b1ea20
Object_b1ea20* Create_b1ea20()
{
    return new ("Simulator/cPlayer", 0, 0, 0, 0) Object_b1ea20();
}
