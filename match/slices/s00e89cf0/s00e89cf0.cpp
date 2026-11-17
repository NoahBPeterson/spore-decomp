// Scalar deleting destructor (0x00e89cf0): run the destructor (0xe88ae0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_e89cf0(void* p);   // 0x00f47380

struct Object_e89cf0 {
    ~Object_e89cf0();        // 0x00e88ae0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00e89cf0
void* Object_e89cf0::DeletingDtor(unsigned int flags)
{
    this->~Object_e89cf0();
    if (flags & 1)
        Free_e89cf0(this);
    return this;
}
