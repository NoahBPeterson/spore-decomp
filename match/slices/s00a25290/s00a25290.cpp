// Scalar deleting destructor (0x00a25290): run the destructor (0xa22b20), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_a25290(void* p);   // 0x00f47380

struct Object_a25290 {
    ~Object_a25290();        // 0x00a22b20
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00a25290
void* Object_a25290::DeletingDtor(unsigned int flags)
{
    this->~Object_a25290();
    if (flags & 1)
        Free_a25290(this);
    return this;
}
