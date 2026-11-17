// Scalar deleting destructor (0x0066cd00): run the destructor (0x66c0c0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_66cd00(void* p);   // 0x00f47380

struct Object_66cd00 {
    ~Object_66cd00();        // 0x0066c0c0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x0066cd00
void* Object_66cd00::DeletingDtor(unsigned int flags)
{
    this->~Object_66cd00();
    if (flags & 1)
        Free_66cd00(this);
    return this;
}
