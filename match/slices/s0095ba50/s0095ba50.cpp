// Scalar deleting destructor (0x0095ba50): run the destructor (0x95b8c0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_95ba50(void* p);   // 0x00f47380

struct Object_95ba50 {
    ~Object_95ba50();        // 0x0095b8c0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x0095ba50
void* Object_95ba50::DeletingDtor(unsigned int flags)
{
    this->~Object_95ba50();
    if (flags & 1)
        Free_95ba50(this);
    return this;
}
