// Scalar deleting destructor (0x00fad710): run the destructor (0xfad4f0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_fad710(void* p);   // 0x00f47380

struct Object_fad710 {
    ~Object_fad710();        // 0x00fad4f0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00fad710
void* Object_fad710::DeletingDtor(unsigned int flags)
{
    this->~Object_fad710();
    if (flags & 1)
        Free_fad710(this);
    return this;
}
