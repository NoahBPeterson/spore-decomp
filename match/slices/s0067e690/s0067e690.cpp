// Scalar deleting destructor (0x0067e690): run the destructor (0x67e1c0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_67e690(void* p);   // 0x00f47380

struct Object_67e690 {
    ~Object_67e690();        // 0x0067e1c0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x0067e690
void* Object_67e690::DeletingDtor(unsigned int flags)
{
    this->~Object_67e690();
    if (flags & 1)
        Free_67e690(this);
    return this;
}
