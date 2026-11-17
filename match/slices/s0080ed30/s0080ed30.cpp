// Scalar deleting destructor (0x0080ed30): run the destructor (0x80eca0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_80ed30(void* p);   // 0x00f47380

struct Object_80ed30 {
    ~Object_80ed30();        // 0x0080eca0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x0080ed30
void* Object_80ed30::DeletingDtor(unsigned int flags)
{
    this->~Object_80ed30();
    if (flags & 1)
        Free_80ed30(this);
    return this;
}
