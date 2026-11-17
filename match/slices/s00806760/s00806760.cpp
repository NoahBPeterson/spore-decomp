// Scalar deleting destructor (0x00806760): run the destructor (0x965670), then free the object (0x951330) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_806760(void* p);   // 0x00951330

struct Object_806760 {
    ~Object_806760();        // 0x00965670
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00806760
void* Object_806760::DeletingDtor(unsigned int flags)
{
    this->~Object_806760();
    if (flags & 1)
        Free_806760(this);
    return this;
}
