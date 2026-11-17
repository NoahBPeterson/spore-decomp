// Scalar deleting destructor (0x01071550): run the destructor (0x106f5b0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_1071550(void* p);   // 0x00f47380

struct Object_1071550 {
    ~Object_1071550();        // 0x0106f5b0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x01071550
void* Object_1071550::DeletingDtor(unsigned int flags)
{
    this->~Object_1071550();
    if (flags & 1)
        Free_1071550(this);
    return this;
}
