// Scalar deleting destructor (0x00924130): run the destructor (0x923ed0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_924130(void* p);   // 0x00f47380

struct Object_924130 {
    ~Object_924130();        // 0x00923ed0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00924130
void* Object_924130::DeletingDtor(unsigned int flags)
{
    this->~Object_924130();
    if (flags & 1)
        Free_924130(this);
    return this;
}
