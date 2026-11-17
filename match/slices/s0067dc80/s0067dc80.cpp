// Scalar deleting destructor (0x0067dc80): run the destructor (0x67db10), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_67dc80(void* p);   // 0x00f47380

struct Object_67dc80 {
    ~Object_67dc80();        // 0x0067db10
    void* DeletingDtor(unsigned int flags);
};

// @ 0x0067dc80
void* Object_67dc80::DeletingDtor(unsigned int flags)
{
    this->~Object_67dc80();
    if (flags & 1)
        Free_67dc80(this);
    return this;
}
