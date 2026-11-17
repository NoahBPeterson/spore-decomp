// Scalar deleting destructor (0x00bd73e0): run the destructor (0xbd70b0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_bd73e0(void* p);   // 0x00f47380

struct Object_bd73e0 {
    ~Object_bd73e0();        // 0x00bd70b0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00bd73e0
void* Object_bd73e0::DeletingDtor(unsigned int flags)
{
    this->~Object_bd73e0();
    if (flags & 1)
        Free_bd73e0(this);
    return this;
}
