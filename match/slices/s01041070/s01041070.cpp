// Scalar deleting destructor (0x01041070): run the destructor (0x1040950), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_1041070(void* p);   // 0x00f47380

struct Object_1041070 {
    ~Object_1041070();        // 0x01040950
    void* DeletingDtor(unsigned int flags);
};

// @ 0x01041070
void* Object_1041070::DeletingDtor(unsigned int flags)
{
    this->~Object_1041070();
    if (flags & 1)
        Free_1041070(this);
    return this;
}
