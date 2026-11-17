// Scalar deleting destructor (0x0068afe0): run the destructor (0x68a8d0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_68afe0(void* p);   // 0x00f47380

struct Object_68afe0 {
    ~Object_68afe0();        // 0x0068a8d0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x0068afe0
void* Object_68afe0::DeletingDtor(unsigned int flags)
{
    this->~Object_68afe0();
    if (flags & 1)
        Free_68afe0(this);
    return this;
}
