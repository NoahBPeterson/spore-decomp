// Scalar deleting destructor (0x00d47940): run the destructor (0xd47850), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_d47940(void* p);   // 0x00f47380

struct Object_d47940 {
    ~Object_d47940();        // 0x00d47850
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00d47940
void* Object_d47940::DeletingDtor(unsigned int flags)
{
    this->~Object_d47940();
    if (flags & 1)
        Free_d47940(this);
    return this;
}
