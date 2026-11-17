// Factory (0x00b1f200): allocate a 0x250-byte object from the "Simulator/cTribeTool" zone and construct it (0xc9d230).
#include "game/types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct Object_b1f200 {
    char mData[0x250];
    Object_b1f200();   // 0x00c9d230
};

// @ 0x00b1f200
Object_b1f200* Create_b1f200()
{
    return new ("Simulator/cTribeTool", 0, 0, 0, 0) Object_b1f200();
}
