// Scalar deleting destructor (0x005fdf20): run the destructor (0x5fdbb0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_5fdf20(void* p);   // 0x00f47380

struct Object_5fdf20 {
    ~Object_5fdf20();        // 0x005fdbb0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x005fdf20
void* Object_5fdf20::DeletingDtor(unsigned int flags)
{
    this->~Object_5fdf20();
    if (flags & 1)
        Free_5fdf20(this);
    return this;
}
