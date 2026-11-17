// Scalar deleting destructor (0x00a87840): run the destructor (0xa87720), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_a87840(void* p);   // 0x00f47380

struct Object_a87840 {
    ~Object_a87840();        // 0x00a87720
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00a87840
void* Object_a87840::DeletingDtor(unsigned int flags)
{
    this->~Object_a87840();
    if (flags & 1)
        Free_a87840(this);
    return this;
}
