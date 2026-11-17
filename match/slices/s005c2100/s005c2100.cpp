// Scalar deleting destructor (0x005c2100): run the destructor (0x5c20b0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_5c2100(void* p);   // 0x00f47380

struct Object_5c2100 {
    ~Object_5c2100();        // 0x005c20b0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x005c2100
void* Object_5c2100::DeletingDtor(unsigned int flags)
{
    this->~Object_5c2100();
    if (flags & 1)
        Free_5c2100(this);
    return this;
}
