// Scalar deleting destructor (0x00e98a20): run the destructor (0xe98440), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_e98a20(void* p);   // 0x00f47380

struct Object_e98a20 {
    ~Object_e98a20();        // 0x00e98440
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00e98a20
void* Object_e98a20::DeletingDtor(unsigned int flags)
{
    this->~Object_e98a20();
    if (flags & 1)
        Free_e98a20(this);
    return this;
}
