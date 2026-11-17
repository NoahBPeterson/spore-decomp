// Scalar deleting destructor (0x00615500): run the destructor (0x615380), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_615500(void* p);   // 0x00f47380

struct Object_615500 {
    ~Object_615500();        // 0x00615380
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00615500
void* Object_615500::DeletingDtor(unsigned int flags)
{
    this->~Object_615500();
    if (flags & 1)
        Free_615500(this);
    return this;
}
