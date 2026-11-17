// Scalar deleting destructor (0x00993f80): run the destructor (0x993000), then free the object (0x951330) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_993f80(void* p);   // 0x00951330

struct Object_993f80 {
    ~Object_993f80();        // 0x00993000
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00993f80
void* Object_993f80::DeletingDtor(unsigned int flags)
{
    this->~Object_993f80();
    if (flags & 1)
        Free_993f80(this);
    return this;
}
