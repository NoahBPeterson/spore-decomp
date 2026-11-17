// Scalar deleting destructor (0x0067fb30): run the destructor (0x67f910), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_67fb30(void* p);   // 0x00f47380

struct Object_67fb30 {
    ~Object_67fb30();        // 0x0067f910
    void* DeletingDtor(unsigned int flags);
};

// @ 0x0067fb30
void* Object_67fb30::DeletingDtor(unsigned int flags)
{
    this->~Object_67fb30();
    if (flags & 1)
        Free_67fb30(this);
    return this;
}
