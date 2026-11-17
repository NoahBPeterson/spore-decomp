// Scalar deleting destructor (0x00edabd0): run the destructor (0xedab50), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_edabd0(void* p);   // 0x00f47380

struct Object_edabd0 {
    ~Object_edabd0();        // 0x00edab50
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00edabd0
void* Object_edabd0::DeletingDtor(unsigned int flags)
{
    this->~Object_edabd0();
    if (flags & 1)
        Free_edabd0(this);
    return this;
}
