// Scalar deleting destructor (0x00bd1b50): run the destructor (0xbd1100), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_bd1b50(void* p);   // 0x00f47380

struct Object_bd1b50 {
    ~Object_bd1b50();        // 0x00bd1100
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00bd1b50
void* Object_bd1b50::DeletingDtor(unsigned int flags)
{
    this->~Object_bd1b50();
    if (flags & 1)
        Free_bd1b50(this);
    return this;
}
