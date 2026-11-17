// Scalar deleting destructor (0x01012430): run the destructor (0x1011b50), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_1012430(void* p);   // 0x00f47380

struct Object_1012430 {
    ~Object_1012430();        // 0x01011b50
    void* DeletingDtor(unsigned int flags);
};

// @ 0x01012430
void* Object_1012430::DeletingDtor(unsigned int flags)
{
    this->~Object_1012430();
    if (flags & 1)
        Free_1012430(this);
    return this;
}
