// Scalar deleting destructor (0x00f18fd0): run the destructor (0xf18f50), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_f18fd0(void* p);   // 0x00f47380

struct Object_f18fd0 {
    ~Object_f18fd0();        // 0x00f18f50
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00f18fd0
void* Object_f18fd0::DeletingDtor(unsigned int flags)
{
    this->~Object_f18fd0();
    if (flags & 1)
        Free_f18fd0(this);
    return this;
}
