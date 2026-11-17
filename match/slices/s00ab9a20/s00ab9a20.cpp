// Scalar deleting destructor (0x00ab9a20): run the destructor (0xab9270), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_ab9a20(void* p);   // 0x00f47380

struct Object_ab9a20 {
    ~Object_ab9a20();        // 0x00ab9270
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00ab9a20
void* Object_ab9a20::DeletingDtor(unsigned int flags)
{
    this->~Object_ab9a20();
    if (flags & 1)
        Free_ab9a20(this);
    return this;
}
