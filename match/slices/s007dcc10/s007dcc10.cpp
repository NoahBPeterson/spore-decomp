// Scalar deleting destructor (0x007dcc10): run the destructor (0x7dc630), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_7dcc10(void* p);   // 0x00f47380

struct Object_7dcc10 {
    ~Object_7dcc10();        // 0x007dc630
    void* DeletingDtor(unsigned int flags);
};

// @ 0x007dcc10
void* Object_7dcc10::DeletingDtor(unsigned int flags)
{
    this->~Object_7dcc10();
    if (flags & 1)
        Free_7dcc10(this);
    return this;
}
