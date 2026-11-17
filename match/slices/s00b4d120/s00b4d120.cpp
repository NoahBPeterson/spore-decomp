// Scalar deleting destructor (0x00b4d120): run the destructor (0xb4ccc0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_b4d120(void* p);   // 0x00f47380

struct Object_b4d120 {
    ~Object_b4d120();        // 0x00b4ccc0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00b4d120
void* Object_b4d120::DeletingDtor(unsigned int flags)
{
    this->~Object_b4d120();
    if (flags & 1)
        Free_b4d120(this);
    return this;
}
