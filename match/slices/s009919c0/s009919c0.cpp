// Scalar deleting destructor (0x009919c0): run the destructor (0x991410), then free the object (0x951330) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_9919c0(void* p);   // 0x00951330

struct Object_9919c0 {
    ~Object_9919c0();        // 0x00991410
    void* DeletingDtor(unsigned int flags);
};

// @ 0x009919c0
void* Object_9919c0::DeletingDtor(unsigned int flags)
{
    this->~Object_9919c0();
    if (flags & 1)
        Free_9919c0(this);
    return this;
}
