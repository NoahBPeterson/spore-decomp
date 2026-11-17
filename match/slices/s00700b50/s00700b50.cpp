// Scalar deleting destructor (0x00700b50): run the destructor (0x700a30), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_700b50(void* p);   // 0x00f47380

struct Object_700b50 {
    ~Object_700b50();        // 0x00700a30
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00700b50
void* Object_700b50::DeletingDtor(unsigned int flags)
{
    this->~Object_700b50();
    if (flags & 1)
        Free_700b50(this);
    return this;
}
