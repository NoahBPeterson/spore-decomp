// Scalar deleting destructor (0x00814380): run the destructor (0x813ca0), then free the object (0x951330) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_814380(void* p);   // 0x00951330

struct Object_814380 {
    ~Object_814380();        // 0x00813ca0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00814380
void* Object_814380::DeletingDtor(unsigned int flags)
{
    this->~Object_814380();
    if (flags & 1)
        Free_814380(this);
    return this;
}
