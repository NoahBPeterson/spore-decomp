// Scalar deleting destructor (0x010077c0): run the destructor (0x1006880), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_10077c0(void* p);   // 0x00f47380

struct Object_10077c0 {
    ~Object_10077c0();        // 0x01006880
    void* DeletingDtor(unsigned int flags);
};

// @ 0x010077c0
void* Object_10077c0::DeletingDtor(unsigned int flags)
{
    this->~Object_10077c0();
    if (flags & 1)
        Free_10077c0(this);
    return this;
}
