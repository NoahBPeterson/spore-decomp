// Scalar deleting destructor (0x00df10b0): run the destructor (0xdf0f20), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_df10b0(void* p);   // 0x00f47380

struct Object_df10b0 {
    ~Object_df10b0();        // 0x00df0f20
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00df10b0
void* Object_df10b0::DeletingDtor(unsigned int flags)
{
    this->~Object_df10b0();
    if (flags & 1)
        Free_df10b0(this);
    return this;
}
