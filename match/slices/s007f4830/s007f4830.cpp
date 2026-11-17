// Scalar deleting destructor (0x007f4830): run the destructor (0x7f45b0), then free the object (0x951330) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_7f4830(void* p);   // 0x00951330

struct Object_7f4830 {
    ~Object_7f4830();        // 0x007f45b0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x007f4830
void* Object_7f4830::DeletingDtor(unsigned int flags)
{
    this->~Object_7f4830();
    if (flags & 1)
        Free_7f4830(this);
    return this;
}
