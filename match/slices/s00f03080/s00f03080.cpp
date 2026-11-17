// Scalar deleting destructor (0x00f03080): run the destructor (0xf03010), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_f03080(void* p);   // 0x00f47380

struct Object_f03080 {
    ~Object_f03080();        // 0x00f03010
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00f03080
void* Object_f03080::DeletingDtor(unsigned int flags)
{
    this->~Object_f03080();
    if (flags & 1)
        Free_f03080(this);
    return this;
}
