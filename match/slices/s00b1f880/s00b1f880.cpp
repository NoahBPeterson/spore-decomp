// Factory (0x00b1f880): allocate a 0x1d8-byte object from the "Simulator/cNanoDrone" zone and construct it (0xc69150).
#include "game/types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct Object_b1f880 {
    char mData[0x1d8];
    Object_b1f880();   // 0x00c69150
};

// @ 0x00b1f880
Object_b1f880* Create_b1f880()
{
    return new ("Simulator/cNanoDrone", 0, 0, 0, 0) Object_b1f880();
}
