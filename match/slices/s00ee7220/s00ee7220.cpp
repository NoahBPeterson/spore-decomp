// Scalar deleting destructor (0x00ee7220): run the destructor (0xee6ef0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_ee7220(void* p);   // 0x00f47380

struct Object_ee7220 {
    ~Object_ee7220();        // 0x00ee6ef0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00ee7220
void* Object_ee7220::DeletingDtor(unsigned int flags)
{
    this->~Object_ee7220();
    if (flags & 1)
        Free_ee7220(this);
    return this;
}
