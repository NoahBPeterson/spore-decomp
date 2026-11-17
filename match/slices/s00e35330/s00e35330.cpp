// Scalar deleting destructor (0x00e35330): run the destructor (0xe351b0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_e35330(void* p);   // 0x00f47380

struct Object_e35330 {
    ~Object_e35330();        // 0x00e351b0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00e35330
void* Object_e35330::DeletingDtor(unsigned int flags)
{
    this->~Object_e35330();
    if (flags & 1)
        Free_e35330(this);
    return this;
}
