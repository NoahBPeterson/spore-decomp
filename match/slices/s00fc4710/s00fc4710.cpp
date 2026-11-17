// Scalar deleting destructor (0x00fc4710): run the destructor (0xfc30f0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_fc4710(void* p);   // 0x00f47380

struct Object_fc4710 {
    ~Object_fc4710();        // 0x00fc30f0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00fc4710
void* Object_fc4710::DeletingDtor(unsigned int flags)
{
    this->~Object_fc4710();
    if (flags & 1)
        Free_fc4710(this);
    return this;
}
