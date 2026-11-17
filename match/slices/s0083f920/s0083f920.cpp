// Scalar deleting destructor (0x0083f920): run the destructor (0x92fc50), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_83f920(void* p);   // 0x00f47380

struct Object_83f920 {
    ~Object_83f920();        // 0x0092fc50
    void* DeletingDtor(unsigned int flags);
};

// @ 0x0083f920
void* Object_83f920::DeletingDtor(unsigned int flags)
{
    this->~Object_83f920();
    if (flags & 1)
        Free_83f920(this);
    return this;
}
