// Factory (0x00b23180): allocate a 0x94-byte object from the "Simulator/cVehicleGroupOrder" zone and construct it (0xb22100).
#include "game/types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct Object_b23180 {
    char mData[0x94];
    Object_b23180();   // 0x00b22100
};

// @ 0x00b23180
Object_b23180* Create_b23180()
{
    return new ("Simulator/cVehicleGroupOrder", 0, 0, 0, 0) Object_b23180();
}
