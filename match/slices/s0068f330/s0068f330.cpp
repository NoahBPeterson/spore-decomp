// Scalar deleting destructor (0x0068f330): run the destructor (0x68f2b0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_68f330(void* p);   // 0x00f47380

struct Object_68f330 {
    ~Object_68f330();        // 0x0068f2b0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x0068f330
void* Object_68f330::DeletingDtor(unsigned int flags)
{
    this->~Object_68f330();
    if (flags & 1)
        Free_68f330(this);
    return this;
}
