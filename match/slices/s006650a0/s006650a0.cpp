// Scalar deleting destructor (0x006650a0): run the destructor (0x664dc0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_6650a0(void* p);   // 0x00f47380

struct Object_6650a0 {
    ~Object_6650a0();        // 0x00664dc0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x006650a0
void* Object_6650a0::DeletingDtor(unsigned int flags)
{
    this->~Object_6650a0();
    if (flags & 1)
        Free_6650a0(this);
    return this;
}
