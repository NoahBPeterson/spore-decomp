// Scalar deleting destructor (0x00f13870): run the destructor (0xf12de0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_f13870(void* p);   // 0x00f47380

struct Object_f13870 {
    ~Object_f13870();        // 0x00f12de0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00f13870
void* Object_f13870::DeletingDtor(unsigned int flags)
{
    this->~Object_f13870();
    if (flags & 1)
        Free_f13870(this);
    return this;
}
