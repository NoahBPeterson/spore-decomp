// Scalar deleting destructor (0x01066a20): run the destructor (0x10669a0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_1066a20(void* p);   // 0x00f47380

struct Object_1066a20 {
    ~Object_1066a20();        // 0x010669a0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x01066a20
void* Object_1066a20::DeletingDtor(unsigned int flags)
{
    this->~Object_1066a20();
    if (flags & 1)
        Free_1066a20(this);
    return this;
}
