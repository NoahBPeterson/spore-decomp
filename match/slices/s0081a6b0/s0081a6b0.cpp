// Scalar deleting destructor (0x0081a6b0): run the destructor (0x81a2b0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_81a6b0(void* p);   // 0x00f47380

struct Object_81a6b0 {
    ~Object_81a6b0();        // 0x0081a2b0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x0081a6b0
void* Object_81a6b0::DeletingDtor(unsigned int flags)
{
    this->~Object_81a6b0();
    if (flags & 1)
        Free_81a6b0(this);
    return this;
}
