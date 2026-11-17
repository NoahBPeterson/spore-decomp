// Scalar deleting destructor (0x00611810): run the destructor (0x6116c0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_611810(void* p);   // 0x00f47380

struct Object_611810 {
    ~Object_611810();        // 0x006116c0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00611810
void* Object_611810::DeletingDtor(unsigned int flags)
{
    this->~Object_611810();
    if (flags & 1)
        Free_611810(this);
    return this;
}
