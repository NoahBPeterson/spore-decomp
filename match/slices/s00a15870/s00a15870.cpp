// Scalar deleting destructor (0x00a15870): run the destructor (0xa151d0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_a15870(void* p);   // 0x00f47380

struct Object_a15870 {
    ~Object_a15870();        // 0x00a151d0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00a15870
void* Object_a15870::DeletingDtor(unsigned int flags)
{
    this->~Object_a15870();
    if (flags & 1)
        Free_a15870(this);
    return this;
}
