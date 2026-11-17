// Scalar deleting destructor (0x00e93360): run the destructor (0xe932d0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_e93360(void* p);   // 0x00f47380

struct Object_e93360 {
    ~Object_e93360();        // 0x00e932d0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00e93360
void* Object_e93360::DeletingDtor(unsigned int flags)
{
    this->~Object_e93360();
    if (flags & 1)
        Free_e93360(this);
    return this;
}
