// Scalar deleting destructor (0x00bd6ff0): run the destructor (0xbd6c10), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_bd6ff0(void* p);   // 0x00f47380

struct Object_bd6ff0 {
    ~Object_bd6ff0();        // 0x00bd6c10
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00bd6ff0
void* Object_bd6ff0::DeletingDtor(unsigned int flags)
{
    this->~Object_bd6ff0();
    if (flags & 1)
        Free_bd6ff0(this);
    return this;
}
