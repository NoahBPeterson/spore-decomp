// Scalar deleting destructor (0x00758220): run the destructor (0x7581a0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_758220(void* p);   // 0x00f47380

struct Object_758220 {
    ~Object_758220();        // 0x007581a0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00758220
void* Object_758220::DeletingDtor(unsigned int flags)
{
    this->~Object_758220();
    if (flags & 1)
        Free_758220(this);
    return this;
}
