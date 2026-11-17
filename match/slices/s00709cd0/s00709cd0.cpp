// Scalar deleting destructor (0x00709cd0): run the destructor (0x708900), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_709cd0(void* p);   // 0x00f47380

struct Object_709cd0 {
    ~Object_709cd0();        // 0x00708900
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00709cd0
void* Object_709cd0::DeletingDtor(unsigned int flags)
{
    this->~Object_709cd0();
    if (flags & 1)
        Free_709cd0(this);
    return this;
}
