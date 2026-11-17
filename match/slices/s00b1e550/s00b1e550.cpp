// Factory (0x00b1e550): allocate a 0x124-byte object from the "Simulator/cCheatObject" zone and construct it (0xbd6a80).
#include "game/types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct Object_b1e550 {
    char mData[0x124];
    Object_b1e550();   // 0x00bd6a80
};

// @ 0x00b1e550
Object_b1e550* Create_b1e550()
{
    return new ("Simulator/cCheatObject", 0, 0, 0, 0) Object_b1e550();
}
