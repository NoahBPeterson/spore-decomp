// Scalar deleting destructor (0x00e25820): run the destructor (0xe24a50), then free the object (0x951330) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_e25820(void* p);   // 0x00951330

struct Object_e25820 {
    ~Object_e25820();        // 0x00e24a50
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00e25820
void* Object_e25820::DeletingDtor(unsigned int flags)
{
    this->~Object_e25820();
    if (flags & 1)
        Free_e25820(this);
    return this;
}
