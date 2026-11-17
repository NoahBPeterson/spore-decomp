// Factory (0x00b1f3e0): allocate a 0x524-byte object from the "Simulator/cICBM" zone and construct it (0xcb94b0).
#include "game/types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct Object_b1f3e0 {
    char mData[0x524];
    Object_b1f3e0();   // 0x00cb94b0
};

// @ 0x00b1f3e0
Object_b1f3e0* Create_b1f3e0()
{
    return new ("Simulator/cICBM", 0, 0, 0, 0) Object_b1f3e0();
}
