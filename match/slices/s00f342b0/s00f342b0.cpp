// Scalar deleting destructor (0x00f342b0): run the destructor (0xf340e0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_f342b0(void* p);   // 0x00f47380

struct Object_f342b0 {
    ~Object_f342b0();        // 0x00f340e0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00f342b0
void* Object_f342b0::DeletingDtor(unsigned int flags)
{
    this->~Object_f342b0();
    if (flags & 1)
        Free_f342b0(this);
    return this;
}
