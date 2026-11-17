// Scalar deleting destructor (0x00847690): run the destructor (0x847200), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_847690(void* p);   // 0x00f47380

struct Object_847690 {
    ~Object_847690();        // 0x00847200
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00847690
void* Object_847690::DeletingDtor(unsigned int flags)
{
    this->~Object_847690();
    if (flags & 1)
        Free_847690(this);
    return this;
}
