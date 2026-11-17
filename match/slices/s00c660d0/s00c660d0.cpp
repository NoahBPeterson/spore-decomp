// Scalar deleting destructor (0x00c660d0): run the destructor (0xc65540), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_c660d0(void* p);   // 0x00f47380

struct Object_c660d0 {
    ~Object_c660d0();        // 0x00c65540
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00c660d0
void* Object_c660d0::DeletingDtor(unsigned int flags)
{
    this->~Object_c660d0();
    if (flags & 1)
        Free_c660d0(this);
    return this;
}
