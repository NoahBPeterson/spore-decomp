// Factory (0x00b1eff0): allocate a 0x238-byte object from the "Simulator/cOrnament" zone and construct it (0xc6f7f0).
#include "game/types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct Object_b1eff0 {
    char mData[0x238];
    Object_b1eff0();   // 0x00c6f7f0
};

// @ 0x00b1eff0
Object_b1eff0* Create_b1eff0()
{
    return new ("Simulator/cOrnament", 0, 0, 0, 0) Object_b1eff0();
}
