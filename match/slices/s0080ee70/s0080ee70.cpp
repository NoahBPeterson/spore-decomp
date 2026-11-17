// Scalar deleting destructor (0x0080ee70): run the destructor (0x80ead0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_80ee70(void* p);   // 0x00f47380

struct Object_80ee70 {
    ~Object_80ee70();        // 0x0080ead0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x0080ee70
void* Object_80ee70::DeletingDtor(unsigned int flags)
{
    this->~Object_80ee70();
    if (flags & 1)
        Free_80ee70(this);
    return this;
}
