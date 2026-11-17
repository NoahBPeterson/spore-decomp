// Scalar deleting destructor (0x00998f40): run the destructor (0x998eb0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_998f40(void* p);   // 0x00f47380

struct Object_998f40 {
    ~Object_998f40();        // 0x00998eb0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00998f40
void* Object_998f40::DeletingDtor(unsigned int flags)
{
    this->~Object_998f40();
    if (flags & 1)
        Free_998f40(this);
    return this;
}
