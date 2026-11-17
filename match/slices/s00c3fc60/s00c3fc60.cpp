// Scalar deleting destructor (0x00c3fc60): run the destructor (0xc3fa70), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_c3fc60(void* p);   // 0x00f47380

struct Object_c3fc60 {
    ~Object_c3fc60();        // 0x00c3fa70
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00c3fc60
void* Object_c3fc60::DeletingDtor(unsigned int flags)
{
    this->~Object_c3fc60();
    if (flags & 1)
        Free_c3fc60(this);
    return this;
}
