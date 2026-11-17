// Scalar deleting destructor (0x00ed0730): run the destructor (0xed0340), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_ed0730(void* p);   // 0x00f47380

struct Object_ed0730 {
    ~Object_ed0730();        // 0x00ed0340
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00ed0730
void* Object_ed0730::DeletingDtor(unsigned int flags)
{
    this->~Object_ed0730();
    if (flags & 1)
        Free_ed0730(this);
    return this;
}
