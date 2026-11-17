// Scalar deleting destructor (0x00f51660): run the destructor (0xf50040), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_f51660(void* p);   // 0x00f47380

struct Object_f51660 {
    ~Object_f51660();        // 0x00f50040
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00f51660
void* Object_f51660::DeletingDtor(unsigned int flags)
{
    this->~Object_f51660();
    if (flags & 1)
        Free_f51660(this);
    return this;
}
