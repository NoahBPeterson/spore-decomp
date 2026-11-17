// Factory (0x00b1ede0): allocate a 0x16a0-byte object from the "Simulator/cCreatureAnimal" zone and construct it (0xc06800).
#include "game/types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct Object_b1ede0 {
    char mData[0x16a0];
    Object_b1ede0();   // 0x00c06800
};

// @ 0x00b1ede0
Object_b1ede0* Create_b1ede0()
{
    return new ("Simulator/cCreatureAnimal", 0, 0, 0, 0) Object_b1ede0();
}
