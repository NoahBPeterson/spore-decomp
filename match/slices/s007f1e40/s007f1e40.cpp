// Scalar deleting destructor (0x007f1e40): run the destructor (0x7f1d90), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_7f1e40(void* p);   // 0x00f47380

struct Object_7f1e40 {
    ~Object_7f1e40();        // 0x007f1d90
    void* DeletingDtor(unsigned int flags);
};

// @ 0x007f1e40
void* Object_7f1e40::DeletingDtor(unsigned int flags)
{
    this->~Object_7f1e40();
    if (flags & 1)
        Free_7f1e40(this);
    return this;
}
