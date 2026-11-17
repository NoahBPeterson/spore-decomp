// Scalar deleting destructor (0x00c87b00): run the destructor (0xc87770), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_c87b00(void* p);   // 0x00f47380

struct Object_c87b00 {
    ~Object_c87b00();        // 0x00c87770
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00c87b00
void* Object_c87b00::DeletingDtor(unsigned int flags)
{
    this->~Object_c87b00();
    if (flags & 1)
        Free_c87b00(this);
    return this;
}
