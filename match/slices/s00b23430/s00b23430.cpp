// Scalar deleting destructor (0x00b23430): run the destructor (0xb22440), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_b23430(void* p);   // 0x00f47380

struct Object_b23430 {
    ~Object_b23430();        // 0x00b22440
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00b23430
void* Object_b23430::DeletingDtor(unsigned int flags)
{
    this->~Object_b23430();
    if (flags & 1)
        Free_b23430(this);
    return this;
}
