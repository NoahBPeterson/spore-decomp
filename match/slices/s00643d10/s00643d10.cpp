// Scalar deleting destructor (0x00643d10): run the destructor (0x643c60), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_643d10(void* p);   // 0x00f47380

struct Object_643d10 {
    ~Object_643d10();        // 0x00643c60
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00643d10
void* Object_643d10::DeletingDtor(unsigned int flags)
{
    this->~Object_643d10();
    if (flags & 1)
        Free_643d10(this);
    return this;
}
