// Factory (0x00b1ef30): allocate a 0x220-byte object from the "Simulator/cHerd" zone and construct it (0xc6c110).
#include "game/types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct Object_b1ef30 {
    char mData[0x220];
    Object_b1ef30();   // 0x00c6c110
};

// @ 0x00b1ef30
Object_b1ef30* Create_b1ef30()
{
    return new ("Simulator/cHerd", 0, 0, 0, 0) Object_b1ef30();
}
