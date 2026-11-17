// Scalar deleting destructor (0x00608530): run the destructor (0x608090), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_608530(void* p);   // 0x00f47380

struct Object_608530 {
    ~Object_608530();        // 0x00608090
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00608530
void* Object_608530::DeletingDtor(unsigned int flags)
{
    this->~Object_608530();
    if (flags & 1)
        Free_608530(this);
    return this;
}
