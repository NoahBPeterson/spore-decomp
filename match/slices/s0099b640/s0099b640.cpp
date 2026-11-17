// Scalar deleting destructor (0x0099b640): run the destructor (0x99b5e0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_99b640(void* p);   // 0x00f47380

struct Object_99b640 {
    ~Object_99b640();        // 0x0099b5e0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x0099b640
void* Object_99b640::DeletingDtor(unsigned int flags)
{
    this->~Object_99b640();
    if (flags & 1)
        Free_99b640(this);
    return this;
}
