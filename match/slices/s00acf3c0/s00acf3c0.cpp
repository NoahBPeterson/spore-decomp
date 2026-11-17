// Scalar deleting destructor (0x00acf3c0): run the destructor (0xace320), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_acf3c0(void* p);   // 0x00f47380

struct Object_acf3c0 {
    ~Object_acf3c0();        // 0x00ace320
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00acf3c0
void* Object_acf3c0::DeletingDtor(unsigned int flags)
{
    this->~Object_acf3c0();
    if (flags & 1)
        Free_acf3c0(this);
    return this;
}
