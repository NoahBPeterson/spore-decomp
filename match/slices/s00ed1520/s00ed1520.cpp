// Scalar deleting destructor (0x00ed1520): run the destructor (0x5f7400), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_ed1520(void* p);   // 0x00f47380

struct Object_ed1520 {
    ~Object_ed1520();        // 0x005f7400
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00ed1520
void* Object_ed1520::DeletingDtor(unsigned int flags)
{
    this->~Object_ed1520();
    if (flags & 1)
        Free_ed1520(this);
    return this;
}
