// Scalar deleting destructor (0x00f62e40): run the destructor (0xb2afb0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_f62e40(void* p);   // 0x00f47380

struct Object_f62e40 {
    ~Object_f62e40();        // 0x00b2afb0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00f62e40
void* Object_f62e40::DeletingDtor(unsigned int flags)
{
    this->~Object_f62e40();
    if (flags & 1)
        Free_f62e40(this);
    return this;
}
