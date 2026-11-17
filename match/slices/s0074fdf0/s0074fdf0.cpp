// Scalar deleting destructor (0x0074fdf0): run the destructor (0x74f010), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_74fdf0(void* p);   // 0x00f47380

struct Object_74fdf0 {
    ~Object_74fdf0();        // 0x0074f010
    void* DeletingDtor(unsigned int flags);
};

// @ 0x0074fdf0
void* Object_74fdf0::DeletingDtor(unsigned int flags)
{
    this->~Object_74fdf0();
    if (flags & 1)
        Free_74fdf0(this);
    return this;
}
