// Scalar deleting destructor (0x00c851e0): run the destructor (0xc84be0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_c851e0(void* p);   // 0x00f47380

struct Object_c851e0 {
    ~Object_c851e0();        // 0x00c84be0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00c851e0
void* Object_c851e0::DeletingDtor(unsigned int flags)
{
    this->~Object_c851e0();
    if (flags & 1)
        Free_c851e0(this);
    return this;
}
