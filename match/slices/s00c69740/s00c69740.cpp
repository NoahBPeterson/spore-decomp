// Scalar deleting destructor (0x00c69740): run the destructor (0xc69290), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_c69740(void* p);   // 0x00f47380

struct Object_c69740 {
    ~Object_c69740();        // 0x00c69290
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00c69740
void* Object_c69740::DeletingDtor(unsigned int flags)
{
    this->~Object_c69740();
    if (flags & 1)
        Free_c69740(this);
    return this;
}
