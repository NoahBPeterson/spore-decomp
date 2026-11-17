// Scalar deleting destructor (0x007b4d50): run the destructor (0x7b4cd0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_7b4d50(void* p);   // 0x00f47380

struct Object_7b4d50 {
    ~Object_7b4d50();        // 0x007b4cd0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x007b4d50
void* Object_7b4d50::DeletingDtor(unsigned int flags)
{
    this->~Object_7b4d50();
    if (flags & 1)
        Free_7b4d50(this);
    return this;
}
