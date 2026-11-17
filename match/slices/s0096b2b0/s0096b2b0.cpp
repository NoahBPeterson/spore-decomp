// Scalar deleting destructor (0x0096b2b0): run the destructor (0x96ac10), then free the object (0x951330) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_96b2b0(void* p);   // 0x00951330

struct Object_96b2b0 {
    ~Object_96b2b0();        // 0x0096ac10
    void* DeletingDtor(unsigned int flags);
};

// @ 0x0096b2b0
void* Object_96b2b0::DeletingDtor(unsigned int flags)
{
    this->~Object_96b2b0();
    if (flags & 1)
        Free_96b2b0(this);
    return this;
}
