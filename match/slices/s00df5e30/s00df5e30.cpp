// Scalar deleting destructor (0x00df5e30): run the destructor (0xdf5cd0), then free the object (0x951330) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_df5e30(void* p);   // 0x00951330

struct Object_df5e30 {
    ~Object_df5e30();        // 0x00df5cd0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00df5e30
void* Object_df5e30::DeletingDtor(unsigned int flags)
{
    this->~Object_df5e30();
    if (flags & 1)
        Free_df5e30(this);
    return this;
}
