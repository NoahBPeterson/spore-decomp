// Scalar deleting destructor (0x00e09af0): run the destructor (0xe09830), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_e09af0(void* p);   // 0x00f47380

struct Object_e09af0 {
    ~Object_e09af0();        // 0x00e09830
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00e09af0
void* Object_e09af0::DeletingDtor(unsigned int flags)
{
    this->~Object_e09af0();
    if (flags & 1)
        Free_e09af0(this);
    return this;
}
