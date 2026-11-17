// Scalar deleting destructor (0x00f63100): run the destructor (0xf62e60), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_f63100(void* p);   // 0x00f47380

struct Object_f63100 {
    ~Object_f63100();        // 0x00f62e60
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00f63100
void* Object_f63100::DeletingDtor(unsigned int flags)
{
    this->~Object_f63100();
    if (flags & 1)
        Free_f63100(this);
    return this;
}
