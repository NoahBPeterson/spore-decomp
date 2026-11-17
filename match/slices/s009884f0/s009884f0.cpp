// Scalar deleting destructor (0x009884f0): run the destructor (0x987b10), then free the object (0x951330) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_9884f0(void* p);   // 0x00951330

struct Object_9884f0 {
    ~Object_9884f0();        // 0x00987b10
    void* DeletingDtor(unsigned int flags);
};

// @ 0x009884f0
void* Object_9884f0::DeletingDtor(unsigned int flags)
{
    this->~Object_9884f0();
    if (flags & 1)
        Free_9884f0(this);
    return this;
}
