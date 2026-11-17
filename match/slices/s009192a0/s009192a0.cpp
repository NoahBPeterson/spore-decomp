// Scalar deleting destructor (0x009192a0): run the destructor (0x93bde0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_9192a0(void* p);   // 0x00f47380

struct Object_9192a0 {
    ~Object_9192a0();        // 0x0093bde0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x009192a0
void* Object_9192a0::DeletingDtor(unsigned int flags)
{
    this->~Object_9192a0();
    if (flags & 1)
        Free_9192a0(this);
    return this;
}
