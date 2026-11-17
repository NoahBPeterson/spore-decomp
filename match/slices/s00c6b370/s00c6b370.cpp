// Scalar deleting destructor (0x00c6b370): run the destructor (0xc6a970), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_c6b370(void* p);   // 0x00f47380

struct Object_c6b370 {
    ~Object_c6b370();        // 0x00c6a970
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00c6b370
void* Object_c6b370::DeletingDtor(unsigned int flags)
{
    this->~Object_c6b370();
    if (flags & 1)
        Free_c6b370(this);
    return this;
}
