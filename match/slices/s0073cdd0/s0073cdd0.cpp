// Scalar deleting destructor (0x0073cdd0): run the destructor (0x73aae0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_73cdd0(void* p);   // 0x00f47380

struct Object_73cdd0 {
    ~Object_73cdd0();        // 0x0073aae0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x0073cdd0
void* Object_73cdd0::DeletingDtor(unsigned int flags)
{
    this->~Object_73cdd0();
    if (flags & 1)
        Free_73cdd0(this);
    return this;
}
