// Scalar deleting destructor (0x007a4400): run the destructor (0x7a4220), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_7a4400(void* p);   // 0x00f47380

struct Object_7a4400 {
    ~Object_7a4400();        // 0x007a4220
    void* DeletingDtor(unsigned int flags);
};

// @ 0x007a4400
void* Object_7a4400::DeletingDtor(unsigned int flags)
{
    this->~Object_7a4400();
    if (flags & 1)
        Free_7a4400(this);
    return this;
}
