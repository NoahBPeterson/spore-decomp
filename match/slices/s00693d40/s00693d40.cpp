// Scalar deleting destructor (0x00693d40): run the destructor (0x693900), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_693d40(void* p);   // 0x00f47380

struct Object_693d40 {
    ~Object_693d40();        // 0x00693900
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00693d40
void* Object_693d40::DeletingDtor(unsigned int flags)
{
    this->~Object_693d40();
    if (flags & 1)
        Free_693d40(this);
    return this;
}
