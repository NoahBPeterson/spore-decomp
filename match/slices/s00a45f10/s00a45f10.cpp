// Scalar deleting destructor (0x00a45f10): run the destructor (0xa45d10), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_a45f10(void* p);   // 0x00f47380

struct Object_a45f10 {
    ~Object_a45f10();        // 0x00a45d10
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00a45f10
void* Object_a45f10::DeletingDtor(unsigned int flags)
{
    this->~Object_a45f10();
    if (flags & 1)
        Free_a45f10(this);
    return this;
}
