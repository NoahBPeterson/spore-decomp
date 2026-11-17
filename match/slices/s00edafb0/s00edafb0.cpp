// Scalar deleting destructor (0x00edafb0): run the destructor (0xedae80), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_edafb0(void* p);   // 0x00f47380

struct Object_edafb0 {
    ~Object_edafb0();        // 0x00edae80
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00edafb0
void* Object_edafb0::DeletingDtor(unsigned int flags)
{
    this->~Object_edafb0();
    if (flags & 1)
        Free_edafb0(this);
    return this;
}
