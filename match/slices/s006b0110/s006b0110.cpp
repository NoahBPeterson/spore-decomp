// Scalar deleting destructor (0x006b0110): run the destructor (0x6afa10), then free the object (0x926060) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_6b0110(void* p);   // 0x00926060

struct Object_6b0110 {
    ~Object_6b0110();        // 0x006afa10
    void* DeletingDtor(unsigned int flags);
};

// @ 0x006b0110
void* Object_6b0110::DeletingDtor(unsigned int flags)
{
    this->~Object_6b0110();
    if (flags & 1)
        Free_6b0110(this);
    return this;
}
