// Scalar deleting destructor (0x00e07930): run the destructor (0xe06870), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_e07930(void* p);   // 0x00f47380

struct Object_e07930 {
    ~Object_e07930();        // 0x00e06870
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00e07930
void* Object_e07930::DeletingDtor(unsigned int flags)
{
    this->~Object_e07930();
    if (flags & 1)
        Free_e07930(this);
    return this;
}
