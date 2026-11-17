// Factory (0x00b1e870): allocate a 0x230-byte object from the "Simulator/cMissionMultiStep" zone and construct it (0xc5ad40).
#include "game/types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct Object_b1e870 {
    char mData[0x230];
    Object_b1e870();   // 0x00c5ad40
};

// @ 0x00b1e870
Object_b1e870* Create_b1e870()
{
    return new ("Simulator/cMissionMultiStep", 0, 0, 0, 0) Object_b1e870();
}
