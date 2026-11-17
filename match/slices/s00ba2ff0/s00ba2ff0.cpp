// Scalar deleting destructor (0x00ba2ff0): run the destructor (0xba2f20), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_ba2ff0(void* p);   // 0x00f47380

struct Object_ba2ff0 {
    ~Object_ba2ff0();        // 0x00ba2f20
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00ba2ff0
void* Object_ba2ff0::DeletingDtor(unsigned int flags)
{
    this->~Object_ba2ff0();
    if (flags & 1)
        Free_ba2ff0(this);
    return this;
}
