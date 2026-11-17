// Scalar deleting destructor (0x00d4eb10): run the destructor (0xd4dfd0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_d4eb10(void* p);   // 0x00f47380

struct Object_d4eb10 {
    ~Object_d4eb10();        // 0x00d4dfd0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00d4eb10
void* Object_d4eb10::DeletingDtor(unsigned int flags)
{
    this->~Object_d4eb10();
    if (flags & 1)
        Free_d4eb10(this);
    return this;
}
