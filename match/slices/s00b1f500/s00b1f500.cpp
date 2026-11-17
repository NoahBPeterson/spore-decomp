// Factory (0x00b1f500): allocate a 0x180-byte object from the "Simulator/cArrowMorphHandle" zone and construct it (0xc64bf0).
#include "game/types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct Object_b1f500 {
    char mData[0x180];
    Object_b1f500();   // 0x00c64bf0
};

// @ 0x00b1f500
Object_b1f500* Create_b1f500()
{
    return new ("Simulator/cArrowMorphHandle", 0, 0, 0, 0) Object_b1f500();
}
