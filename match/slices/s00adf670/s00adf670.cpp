// Scalar deleting destructor (0x00adf670): run the destructor (0xade680), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_adf670(void* p);   // 0x00f47380

struct Object_adf670 {
    ~Object_adf670();        // 0x00ade680
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00adf670
void* Object_adf670::DeletingDtor(unsigned int flags)
{
    this->~Object_adf670();
    if (flags & 1)
        Free_adf670(this);
    return this;
}
