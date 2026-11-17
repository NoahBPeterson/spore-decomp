// Factory (0x00b1ee70): allocate a 0x680-byte object from the "Simulator/cGamePlant" zone and construct it (0xc3e510).
#include "game/types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct Object_b1ee70 {
    char mData[0x680];
    Object_b1ee70();   // 0x00c3e510
};

// @ 0x00b1ee70
Object_b1ee70* Create_b1ee70()
{
    return new ("Simulator/cGamePlant", 0, 0, 0, 0) Object_b1ee70();
}
