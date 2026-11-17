// Scalar deleting destructor (0x00ab1820): run the destructor (0xab0c30), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_ab1820(void* p);   // 0x00f47380

struct Object_ab1820 {
    ~Object_ab1820();        // 0x00ab0c30
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00ab1820
void* Object_ab1820::DeletingDtor(unsigned int flags)
{
    this->~Object_ab1820();
    if (flags & 1)
        Free_ab1820(this);
    return this;
}
