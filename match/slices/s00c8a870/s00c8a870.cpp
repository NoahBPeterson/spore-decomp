// Scalar deleting destructor (0x00c8a870): run the destructor (0xc8a420), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_c8a870(void* p);   // 0x00f47380

struct Object_c8a870 {
    ~Object_c8a870();        // 0x00c8a420
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00c8a870
void* Object_c8a870::DeletingDtor(unsigned int flags)
{
    this->~Object_c8a870();
    if (flags & 1)
        Free_c8a870(this);
    return this;
}
