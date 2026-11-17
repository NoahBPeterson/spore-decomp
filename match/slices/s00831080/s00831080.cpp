// Scalar deleting destructor (0x00831080): run the destructor (0x830b30), then free the object (0x951330) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_831080(void* p);   // 0x00951330

struct Object_831080 {
    ~Object_831080();        // 0x00830b30
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00831080
void* Object_831080::DeletingDtor(unsigned int flags)
{
    this->~Object_831080();
    if (flags & 1)
        Free_831080(this);
    return this;
}
