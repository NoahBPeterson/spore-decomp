// Scalar deleting destructor (0x00776a40): run the destructor (0x776680), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_776a40(void* p);   // 0x00f47380

struct Object_776a40 {
    ~Object_776a40();        // 0x00776680
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00776a40
void* Object_776a40::DeletingDtor(unsigned int flags)
{
    this->~Object_776a40();
    if (flags & 1)
        Free_776a40(this);
    return this;
}
