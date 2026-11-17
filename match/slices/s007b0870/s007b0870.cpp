// Scalar deleting destructor (0x007b0870): run the destructor (0x7b02f0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_7b0870(void* p);   // 0x00f47380

struct Object_7b0870 {
    ~Object_7b0870();        // 0x007b02f0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x007b0870
void* Object_7b0870::DeletingDtor(unsigned int flags)
{
    this->~Object_7b0870();
    if (flags & 1)
        Free_7b0870(this);
    return this;
}
