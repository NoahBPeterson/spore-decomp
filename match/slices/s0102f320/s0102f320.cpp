// Scalar deleting destructor (0x0102f320): run the destructor (0x102f220), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_102f320(void* p);   // 0x00f47380

struct Object_102f320 {
    ~Object_102f320();        // 0x0102f220
    void* DeletingDtor(unsigned int flags);
};

// @ 0x0102f320
void* Object_102f320::DeletingDtor(unsigned int flags)
{
    this->~Object_102f320();
    if (flags & 1)
        Free_102f320(this);
    return this;
}
