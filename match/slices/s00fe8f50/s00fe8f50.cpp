// Scalar deleting destructor (0x00fe8f50): run the destructor (0xfe8e20), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_fe8f50(void* p);   // 0x00f47380

struct Object_fe8f50 {
    ~Object_fe8f50();        // 0x00fe8e20
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00fe8f50
void* Object_fe8f50::DeletingDtor(unsigned int flags)
{
    this->~Object_fe8f50();
    if (flags & 1)
        Free_fe8f50(this);
    return this;
}
