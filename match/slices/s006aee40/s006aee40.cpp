// Scalar deleting destructor (0x006aee40): run the destructor (0x6aebd0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_6aee40(void* p);   // 0x00f47380

struct Object_6aee40 {
    ~Object_6aee40();        // 0x006aebd0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x006aee40
void* Object_6aee40::DeletingDtor(unsigned int flags)
{
    this->~Object_6aee40();
    if (flags & 1)
        Free_6aee40(this);
    return this;
}
