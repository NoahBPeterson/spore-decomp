// Scalar deleting destructor (0x00e0be30): run the destructor (0x966e40), then free the object (0x951330) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_e0be30(void* p);   // 0x00951330

struct Object_e0be30 {
    ~Object_e0be30();        // 0x00966e40
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00e0be30
void* Object_e0be30::DeletingDtor(unsigned int flags)
{
    this->~Object_e0be30();
    if (flags & 1)
        Free_e0be30(this);
    return this;
}
