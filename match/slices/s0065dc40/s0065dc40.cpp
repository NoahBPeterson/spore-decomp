// Scalar deleting destructor (0x0065dc40): run the destructor (0x65d860), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_65dc40(void* p);   // 0x00f47380

struct Object_65dc40 {
    ~Object_65dc40();        // 0x0065d860
    void* DeletingDtor(unsigned int flags);
};

// @ 0x0065dc40
void* Object_65dc40::DeletingDtor(unsigned int flags)
{
    this->~Object_65dc40();
    if (flags & 1)
        Free_65dc40(this);
    return this;
}
