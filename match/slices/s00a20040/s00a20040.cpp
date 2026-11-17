// Scalar deleting destructor (0x00a20040): run the destructor (0xa1f4d0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_a20040(void* p);   // 0x00f47380

struct Object_a20040 {
    ~Object_a20040();        // 0x00a1f4d0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00a20040
void* Object_a20040::DeletingDtor(unsigned int flags)
{
    this->~Object_a20040();
    if (flags & 1)
        Free_a20040(this);
    return this;
}
