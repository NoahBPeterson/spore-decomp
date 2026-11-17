// Scalar deleting destructor (0x0069f920): run the destructor (0x69f0b0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_69f920(void* p);   // 0x00f47380

struct Object_69f920 {
    ~Object_69f920();        // 0x0069f0b0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x0069f920
void* Object_69f920::DeletingDtor(unsigned int flags)
{
    this->~Object_69f920();
    if (flags & 1)
        Free_69f920(this);
    return this;
}
