// Scalar deleting destructor (0x005f7850): run the destructor (0x5f6df0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_5f7850(void* p);   // 0x00f47380

struct Object_5f7850 {
    ~Object_5f7850();        // 0x005f6df0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x005f7850
void* Object_5f7850::DeletingDtor(unsigned int flags)
{
    this->~Object_5f7850();
    if (flags & 1)
        Free_5f7850(this);
    return this;
}
