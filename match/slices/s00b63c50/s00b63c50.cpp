// Scalar deleting destructor (0x00b63c50): run the destructor (0xb63b60), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_b63c50(void* p);   // 0x00f47380

struct Object_b63c50 {
    ~Object_b63c50();        // 0x00b63b60
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00b63c50
void* Object_b63c50::DeletingDtor(unsigned int flags)
{
    this->~Object_b63c50();
    if (flags & 1)
        Free_b63c50(this);
    return this;
}
