// Scalar deleting destructor (0x00ee8840): run the destructor (0xee7990), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_ee8840(void* p);   // 0x00f47380

struct Object_ee8840 {
    ~Object_ee8840();        // 0x00ee7990
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00ee8840
void* Object_ee8840::DeletingDtor(unsigned int flags)
{
    this->~Object_ee8840();
    if (flags & 1)
        Free_ee8840(this);
    return this;
}
