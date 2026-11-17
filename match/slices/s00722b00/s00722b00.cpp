// Scalar deleting destructor (0x00722b00): run the destructor (0x7220c0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_722b00(void* p);   // 0x00f47380

struct Object_722b00 {
    ~Object_722b00();        // 0x007220c0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00722b00
void* Object_722b00::DeletingDtor(unsigned int flags)
{
    this->~Object_722b00();
    if (flags & 1)
        Free_722b00(this);
    return this;
}
