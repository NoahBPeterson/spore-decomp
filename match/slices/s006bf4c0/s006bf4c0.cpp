// Scalar deleting destructor (0x006bf4c0): run the destructor (0x6bf430), then free the object (0x926060) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_6bf4c0(void* p);   // 0x00926060

struct Object_6bf4c0 {
    ~Object_6bf4c0();        // 0x006bf430
    void* DeletingDtor(unsigned int flags);
};

// @ 0x006bf4c0
void* Object_6bf4c0::DeletingDtor(unsigned int flags)
{
    this->~Object_6bf4c0();
    if (flags & 1)
        Free_6bf4c0(this);
    return this;
}
