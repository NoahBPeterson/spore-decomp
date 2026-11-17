// Scalar deleting destructor (0x00f10010): run the destructor (0xf0f740), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_f10010(void* p);   // 0x00f47380

struct Object_f10010 {
    ~Object_f10010();        // 0x00f0f740
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00f10010
void* Object_f10010::DeletingDtor(unsigned int flags)
{
    this->~Object_f10010();
    if (flags & 1)
        Free_f10010(this);
    return this;
}
