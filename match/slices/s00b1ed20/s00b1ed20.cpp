// Factory (0x00b1ed20): allocate a 0x108-byte object from the "Simulator/cPlaceholderColonyEditorCursorAttachment" zone and construct it (0xc6fcd0).
#include "game/types.h"

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);  // 0x00f473a0

struct Object_b1ed20 {
    char mData[0x108];
    Object_b1ed20();   // 0x00c6fcd0
};

// @ 0x00b1ed20
Object_b1ed20* Create_b1ed20()
{
    return new ("Simulator/cPlaceholderColonyEditorCursorAttachment", 0, 0, 0, 0) Object_b1ed20();
}
