// Scalar deleting destructor (0x00833820): run the destructor (0x833400), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_833820(void* p);   // 0x00f47380

struct Object_833820 {
    ~Object_833820();        // 0x00833400
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00833820
void* Object_833820::DeletingDtor(unsigned int flags)
{
    this->~Object_833820();
    if (flags & 1)
        Free_833820(this);
    return this;
}
