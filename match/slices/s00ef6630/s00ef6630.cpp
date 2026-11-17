// Scalar deleting destructor (0x00ef6630): run the destructor (0xef61b0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_ef6630(void* p);   // 0x00f47380

struct Object_ef6630 {
    ~Object_ef6630();        // 0x00ef61b0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00ef6630
void* Object_ef6630::DeletingDtor(unsigned int flags)
{
    this->~Object_ef6630();
    if (flags & 1)
        Free_ef6630(this);
    return this;
}
