// Scalar deleting destructor (0x00ce5630): run the destructor (0xce4ed0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_ce5630(void* p);   // 0x00f47380

struct Object_ce5630 {
    ~Object_ce5630();        // 0x00ce4ed0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00ce5630
void* Object_ce5630::DeletingDtor(unsigned int flags)
{
    this->~Object_ce5630();
    if (flags & 1)
        Free_ce5630(this);
    return this;
}
