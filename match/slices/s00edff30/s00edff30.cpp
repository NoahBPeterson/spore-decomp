// Scalar deleting destructor (0x00edff30): run the destructor (0xedd6b0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_edff30(void* p);   // 0x00f47380

struct Object_edff30 {
    ~Object_edff30();        // 0x00edd6b0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00edff30
void* Object_edff30::DeletingDtor(unsigned int flags)
{
    this->~Object_edff30();
    if (flags & 1)
        Free_edff30(this);
    return this;
}
