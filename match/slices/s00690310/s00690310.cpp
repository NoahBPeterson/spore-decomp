// Scalar deleting destructor (0x00690310): run the destructor (0x68fc60), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_690310(void* p);   // 0x00f47380

struct Object_690310 {
    ~Object_690310();        // 0x0068fc60
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00690310
void* Object_690310::DeletingDtor(unsigned int flags)
{
    this->~Object_690310();
    if (flags & 1)
        Free_690310(this);
    return this;
}
