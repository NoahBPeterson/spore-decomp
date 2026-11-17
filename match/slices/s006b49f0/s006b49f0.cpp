// Scalar deleting destructor (0x006b49f0): run the destructor (0x6b4400), then free the object (0x926060) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_6b49f0(void* p);   // 0x00926060

struct Object_6b49f0 {
    ~Object_6b49f0();        // 0x006b4400
    void* DeletingDtor(unsigned int flags);
};

// @ 0x006b49f0
void* Object_6b49f0::DeletingDtor(unsigned int flags)
{
    this->~Object_6b49f0();
    if (flags & 1)
        Free_6b49f0(this);
    return this;
}
