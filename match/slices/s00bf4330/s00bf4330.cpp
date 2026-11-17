// Scalar deleting destructor (0x00bf4330): run the destructor (0xbf36f0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_bf4330(void* p);   // 0x00f47380

struct Object_bf4330 {
    ~Object_bf4330();        // 0x00bf36f0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00bf4330
void* Object_bf4330::DeletingDtor(unsigned int flags)
{
    this->~Object_bf4330();
    if (flags & 1)
        Free_bf4330(this);
    return this;
}
