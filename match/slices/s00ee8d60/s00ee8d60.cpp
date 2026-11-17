// Scalar deleting destructor (0x00ee8d60): run the destructor (0xee7e50), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_ee8d60(void* p);   // 0x00f47380

struct Object_ee8d60 {
    ~Object_ee8d60();        // 0x00ee7e50
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00ee8d60
void* Object_ee8d60::DeletingDtor(unsigned int flags)
{
    this->~Object_ee8d60();
    if (flags & 1)
        Free_ee8d60(this);
    return this;
}
