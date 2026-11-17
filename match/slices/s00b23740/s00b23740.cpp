// Factory (0x00b23740): allocate a 0xc4-byte object from the "Simulator/cMilitaryAttackCityOrder" zone and construct it (0xb231b0).
#include "game/types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct Object_b23740 {
    char mData[0xc4];
    Object_b23740();   // 0x00b231b0
};

// @ 0x00b23740
Object_b23740* Create_b23740()
{
    return new ("Simulator/cMilitaryAttackCityOrder", 0, 0, 0, 0) Object_b23740();
}
