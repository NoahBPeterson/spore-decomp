// Scalar deleting destructor (0x00bbf290): run the destructor (0xbbebb0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_bbf290(void* p);   // 0x00f47380

struct Object_bbf290 {
    ~Object_bbf290();        // 0x00bbebb0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00bbf290
void* Object_bbf290::DeletingDtor(unsigned int flags)
{
    this->~Object_bbf290();
    if (flags & 1)
        Free_bbf290(this);
    return this;
}
