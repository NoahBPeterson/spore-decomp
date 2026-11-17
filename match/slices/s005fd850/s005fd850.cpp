// Factory (0x005fd850): allocate a 0x188-byte object from the "Thumbnail_cImportExport" zone and construct it (0x5fcf40).
#include "game/types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct Object_5fd850 {
    char mData[0x188];
    Object_5fd850();   // 0x005fcf40
};

// @ 0x005fd850
Object_5fd850* Create_5fd850()
{
    return new ("Thumbnail_cImportExport", 0, 0, 0, 0) Object_5fd850();
}
