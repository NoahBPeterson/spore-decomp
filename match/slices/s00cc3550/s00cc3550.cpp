// Scalar deleting destructor (0x00cc3550): run the destructor (0xcc2cb0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_cc3550(void* p);   // 0x00f47380

struct Object_cc3550 {
    ~Object_cc3550();        // 0x00cc2cb0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00cc3550
void* Object_cc3550::DeletingDtor(unsigned int flags)
{
    this->~Object_cc3550();
    if (flags & 1)
        Free_cc3550(this);
    return this;
}
