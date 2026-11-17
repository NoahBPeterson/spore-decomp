// Factory (0x00b1ed80): allocate a 0x658-byte object from the "Simulator/cToolObject" zone and construct it (0xc74950).
#include "game/types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct Object_b1ed80 {
    char mData[0x658];
    Object_b1ed80();   // 0x00c74950
};

// @ 0x00b1ed80
Object_b1ed80* Create_b1ed80()
{
    return new ("Simulator/cToolObject", 0, 0, 0, 0) Object_b1ed80();
}
