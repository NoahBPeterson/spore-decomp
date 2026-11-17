// Scalar deleting destructor (0x00714030): run the destructor (0x713fd0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_714030(void* p);   // 0x00f47380

struct Object_714030 {
    ~Object_714030();        // 0x00713fd0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00714030
void* Object_714030::DeletingDtor(unsigned int flags)
{
    this->~Object_714030();
    if (flags & 1)
        Free_714030(this);
    return this;
}
