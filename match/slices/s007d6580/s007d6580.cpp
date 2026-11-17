// Scalar deleting destructor (0x007d6580): run the destructor (0x7d6500), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_7d6580(void* p);   // 0x00f47380

struct Object_7d6580 {
    ~Object_7d6580();        // 0x007d6500
    void* DeletingDtor(unsigned int flags);
};

// @ 0x007d6580
void* Object_7d6580::DeletingDtor(unsigned int flags)
{
    this->~Object_7d6580();
    if (flags & 1)
        Free_7d6580(this);
    return this;
}
