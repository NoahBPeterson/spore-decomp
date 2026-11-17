// Scalar deleting destructor (0x00ea9420): run the destructor (0xea93c0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_ea9420(void* p);   // 0x00f47380

struct Object_ea9420 {
    ~Object_ea9420();        // 0x00ea93c0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00ea9420
void* Object_ea9420::DeletingDtor(unsigned int flags)
{
    this->~Object_ea9420();
    if (flags & 1)
        Free_ea9420(this);
    return this;
}
