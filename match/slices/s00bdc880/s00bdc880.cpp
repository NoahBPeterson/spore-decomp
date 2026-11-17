// Scalar deleting destructor (0x00bdc880): run the destructor (0xbdace0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_bdc880(void* p);   // 0x00f47380

struct Object_bdc880 {
    ~Object_bdc880();        // 0x00bdace0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00bdc880
void* Object_bdc880::DeletingDtor(unsigned int flags)
{
    this->~Object_bdc880();
    if (flags & 1)
        Free_bdc880(this);
    return this;
}
