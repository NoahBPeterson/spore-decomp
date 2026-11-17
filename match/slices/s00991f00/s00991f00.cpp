// Scalar deleting destructor (0x00991f00): run the destructor (0x991df0), then free the object (0x951330) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_991f00(void* p);   // 0x00951330

struct Object_991f00 {
    ~Object_991f00();        // 0x00991df0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00991f00
void* Object_991f00::DeletingDtor(unsigned int flags)
{
    this->~Object_991f00();
    if (flags & 1)
        Free_991f00(this);
    return this;
}
