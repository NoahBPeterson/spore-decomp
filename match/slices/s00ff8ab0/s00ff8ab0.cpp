// Scalar deleting destructor (0x00ff8ab0): run the destructor (0xff8780), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_ff8ab0(void* p);   // 0x00f47380

struct Object_ff8ab0 {
    ~Object_ff8ab0();        // 0x00ff8780
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00ff8ab0
void* Object_ff8ab0::DeletingDtor(unsigned int flags)
{
    this->~Object_ff8ab0();
    if (flags & 1)
        Free_ff8ab0(this);
    return this;
}
