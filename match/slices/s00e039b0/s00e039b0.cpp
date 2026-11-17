// Scalar deleting destructor (0x00e039b0): run the destructor (0xe03930), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_e039b0(void* p);   // 0x00f47380

struct Object_e039b0 {
    ~Object_e039b0();        // 0x00e03930
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00e039b0
void* Object_e039b0::DeletingDtor(unsigned int flags)
{
    this->~Object_e039b0();
    if (flags & 1)
        Free_e039b0(this);
    return this;
}
