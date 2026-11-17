// Scalar deleting destructor (0x007b6d10): run the destructor (0x7b6c70), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_7b6d10(void* p);   // 0x00f47380

struct Object_7b6d10 {
    ~Object_7b6d10();        // 0x007b6c70
    void* DeletingDtor(unsigned int flags);
};

// @ 0x007b6d10
void* Object_7b6d10::DeletingDtor(unsigned int flags)
{
    this->~Object_7b6d10();
    if (flags & 1)
        Free_7b6d10(this);
    return this;
}
