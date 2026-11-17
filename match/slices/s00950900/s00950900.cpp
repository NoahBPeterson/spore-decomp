// Scalar deleting destructor (0x00950900): run the destructor (0x950740), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_950900(void* p);   // 0x00f47380

struct Object_950900 {
    ~Object_950900();        // 0x00950740
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00950900
void* Object_950900::DeletingDtor(unsigned int flags)
{
    this->~Object_950900();
    if (flags & 1)
        Free_950900(this);
    return this;
}
