// Scalar deleting destructor (0x00c8db10): run the destructor (0xc8d800), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_c8db10(void* p);   // 0x00f47380

struct Object_c8db10 {
    ~Object_c8db10();        // 0x00c8d800
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00c8db10
void* Object_c8db10::DeletingDtor(unsigned int flags)
{
    this->~Object_c8db10();
    if (flags & 1)
        Free_c8db10(this);
    return this;
}
