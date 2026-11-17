// Scalar deleting destructor (0x00929e50): run the destructor (0x929d50), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_929e50(void* p);   // 0x00f47380

struct Object_929e50 {
    ~Object_929e50();        // 0x00929d50
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00929e50
void* Object_929e50::DeletingDtor(unsigned int flags)
{
    this->~Object_929e50();
    if (flags & 1)
        Free_929e50(this);
    return this;
}
