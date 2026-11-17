// Scalar deleting destructor (0x00661160): run the destructor (0x660e30), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_661160(void* p);   // 0x00f47380

struct Object_661160 {
    ~Object_661160();        // 0x00660e30
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00661160
void* Object_661160::DeletingDtor(unsigned int flags)
{
    this->~Object_661160();
    if (flags & 1)
        Free_661160(this);
    return this;
}
