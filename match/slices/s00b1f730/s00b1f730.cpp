// Factory (0x00b1f730): allocate a 0x818-byte object from the "Simulator/cGameDataUFO" zone and construct it (0xc3c870).
#include "game/types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct Object_b1f730 {
    char mData[0x818];
    Object_b1f730();   // 0x00c3c870
};

// @ 0x00b1f730
Object_b1f730* Create_b1f730()
{
    return new ("Simulator/cGameDataUFO", 0, 0, 0, 0) Object_b1f730();
}
