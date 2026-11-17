// Scalar deleting destructor (0x005a9670): run the destructor (0x5a9170), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_5a9670(void* p);   // 0x00f47380

struct Object_5a9670 {
    ~Object_5a9670();        // 0x005a9170
    void* DeletingDtor(unsigned int flags);
};

// @ 0x005a9670
void* Object_5a9670::DeletingDtor(unsigned int flags)
{
    this->~Object_5a9670();
    if (flags & 1)
        Free_5a9670(this);
    return this;
}
