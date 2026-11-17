// Scalar deleting destructor (0x008e22a0): run the destructor (0x8e1f10), then free the object (0x926060) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_8e22a0(void* p);   // 0x00926060

struct Object_8e22a0 {
    ~Object_8e22a0();        // 0x008e1f10
    void* DeletingDtor(unsigned int flags);
};

// @ 0x008e22a0
void* Object_8e22a0::DeletingDtor(unsigned int flags)
{
    this->~Object_8e22a0();
    if (flags & 1)
        Free_8e22a0(this);
    return this;
}
