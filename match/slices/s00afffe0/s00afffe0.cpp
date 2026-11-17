// Scalar deleting destructor (0x00afffe0): run the destructor (0xaff280), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_afffe0(void* p);   // 0x00f47380

struct Object_afffe0 {
    ~Object_afffe0();        // 0x00aff280
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00afffe0
void* Object_afffe0::DeletingDtor(unsigned int flags)
{
    this->~Object_afffe0();
    if (flags & 1)
        Free_afffe0(this);
    return this;
}
