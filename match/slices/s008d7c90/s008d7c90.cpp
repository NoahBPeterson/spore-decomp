// Scalar deleting destructor (0x008d7c90): run the destructor (0x8d7570), then free the object (0x926060) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_8d7c90(void* p);   // 0x00926060

struct Object_8d7c90 {
    ~Object_8d7c90();        // 0x008d7570
    void* DeletingDtor(unsigned int flags);
};

// @ 0x008d7c90
void* Object_8d7c90::DeletingDtor(unsigned int flags)
{
    this->~Object_8d7c90();
    if (flags & 1)
        Free_8d7c90(this);
    return this;
}
