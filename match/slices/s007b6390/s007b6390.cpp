// Scalar deleting destructor (0x007b6390): run the destructor (0x7b3180), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_7b6390(void* p);   // 0x00f47380

struct Object_7b6390 {
    ~Object_7b6390();        // 0x007b3180
    void* DeletingDtor(unsigned int flags);
};

// @ 0x007b6390
void* Object_7b6390::DeletingDtor(unsigned int flags)
{
    this->~Object_7b6390();
    if (flags & 1)
        Free_7b6390(this);
    return this;
}
