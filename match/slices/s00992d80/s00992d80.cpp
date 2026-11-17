// Scalar deleting destructor (0x00992d80): run the destructor (0x992830), then free the object (0x951330) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_992d80(void* p);   // 0x00951330

struct Object_992d80 {
    ~Object_992d80();        // 0x00992830
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00992d80
void* Object_992d80::DeletingDtor(unsigned int flags)
{
    this->~Object_992d80();
    if (flags & 1)
        Free_992d80(this);
    return this;
}
