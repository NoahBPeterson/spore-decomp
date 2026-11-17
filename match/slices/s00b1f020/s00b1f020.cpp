// Factory (0x00b1f020): allocate a 0x118-byte object from the "Simulator/cAnimalTrap" zone and construct it (0xbcb980).
#include "game/types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct Object_b1f020 {
    char mData[0x118];
    Object_b1f020();   // 0x00bcb980
};

// @ 0x00b1f020
Object_b1f020* Create_b1f020()
{
    return new ("Simulator/cAnimalTrap", 0, 0, 0, 0) Object_b1f020();
}
