// Scalar deleting destructor (0x0067dca0): run the destructor (0x67dbc0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_67dca0(void* p);   // 0x00f47380

struct Object_67dca0 {
    ~Object_67dca0();        // 0x0067dbc0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x0067dca0
void* Object_67dca0::DeletingDtor(unsigned int flags)
{
    this->~Object_67dca0();
    if (flags & 1)
        Free_67dca0(this);
    return this;
}
