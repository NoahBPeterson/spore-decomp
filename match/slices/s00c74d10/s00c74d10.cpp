// Scalar deleting destructor (0x00c74d10): run the destructor (0xc74bd0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_c74d10(void* p);   // 0x00f47380

struct Object_c74d10 {
    ~Object_c74d10();        // 0x00c74bd0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00c74d10
void* Object_c74d10::DeletingDtor(unsigned int flags)
{
    this->~Object_c74d10();
    if (flags & 1)
        Free_c74d10(this);
    return this;
}
