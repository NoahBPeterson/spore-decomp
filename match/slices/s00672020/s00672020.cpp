// Scalar deleting destructor (0x00672020): run the destructor (0x671f70), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_672020(void* p);   // 0x00f47380

struct Object_672020 {
    ~Object_672020();        // 0x00671f70
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00672020
void* Object_672020::DeletingDtor(unsigned int flags)
{
    this->~Object_672020();
    if (flags & 1)
        Free_672020(this);
    return this;
}
