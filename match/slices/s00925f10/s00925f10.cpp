// Scalar deleting destructor (0x00925f10): run the destructor (0x925d60), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_925f10(void* p);   // 0x00f47380

struct Object_925f10 {
    ~Object_925f10();        // 0x00925d60
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00925f10
void* Object_925f10::DeletingDtor(unsigned int flags)
{
    this->~Object_925f10();
    if (flags & 1)
        Free_925f10(this);
    return this;
}
