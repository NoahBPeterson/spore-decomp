// Scalar deleting destructor (0x00cc5b30): run the destructor (0xcc5610), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_cc5b30(void* p);   // 0x00f47380

struct Object_cc5b30 {
    ~Object_cc5b30();        // 0x00cc5610
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00cc5b30
void* Object_cc5b30::DeletingDtor(unsigned int flags)
{
    this->~Object_cc5b30();
    if (flags & 1)
        Free_cc5b30(this);
    return this;
}
