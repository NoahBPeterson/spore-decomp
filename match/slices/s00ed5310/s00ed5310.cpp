// Scalar deleting destructor (0x00ed5310): run the destructor (0xed49a0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_ed5310(void* p);   // 0x00f47380

struct Object_ed5310 {
    ~Object_ed5310();        // 0x00ed49a0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00ed5310
void* Object_ed5310::DeletingDtor(unsigned int flags)
{
    this->~Object_ed5310();
    if (flags & 1)
        Free_ed5310(this);
    return this;
}
