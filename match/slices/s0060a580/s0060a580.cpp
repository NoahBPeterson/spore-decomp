// Scalar deleting destructor (0x0060a580): run the destructor (0x60a080), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_60a580(void* p);   // 0x00f47380

struct Object_60a580 {
    ~Object_60a580();        // 0x0060a080
    void* DeletingDtor(unsigned int flags);
};

// @ 0x0060a580
void* Object_60a580::DeletingDtor(unsigned int flags)
{
    this->~Object_60a580();
    if (flags & 1)
        Free_60a580(this);
    return this;
}
