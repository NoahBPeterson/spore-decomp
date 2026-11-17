// Scalar deleting destructor (0x00ee0f30): run the destructor (0xedebb0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_ee0f30(void* p);   // 0x00f47380

struct Object_ee0f30 {
    ~Object_ee0f30();        // 0x00edebb0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00ee0f30
void* Object_ee0f30::DeletingDtor(unsigned int flags)
{
    this->~Object_ee0f30();
    if (flags & 1)
        Free_ee0f30(this);
    return this;
}
