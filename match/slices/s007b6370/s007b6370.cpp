// Scalar deleting destructor (0x007b6370): run the destructor (0x7b2eb0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_7b6370(void* p);   // 0x00f47380

struct Object_7b6370 {
    ~Object_7b6370();        // 0x007b2eb0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x007b6370
void* Object_7b6370::DeletingDtor(unsigned int flags)
{
    this->~Object_7b6370();
    if (flags & 1)
        Free_7b6370(this);
    return this;
}
