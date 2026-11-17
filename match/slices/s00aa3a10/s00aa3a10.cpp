// Scalar deleting destructor (0x00aa3a10): run the destructor (0xaa32f0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_aa3a10(void* p);   // 0x00f47380

struct Object_aa3a10 {
    ~Object_aa3a10();        // 0x00aa32f0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00aa3a10
void* Object_aa3a10::DeletingDtor(unsigned int flags)
{
    this->~Object_aa3a10();
    if (flags & 1)
        Free_aa3a10(this);
    return this;
}
