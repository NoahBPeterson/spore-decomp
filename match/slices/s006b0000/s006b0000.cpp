// Scalar deleting destructor (0x006b0000): run the destructor (0x6af8a0), then free the object (0x926060) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_6b0000(void* p);   // 0x00926060

struct Object_6b0000 {
    ~Object_6b0000();        // 0x006af8a0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x006b0000
void* Object_6b0000::DeletingDtor(unsigned int flags)
{
    this->~Object_6b0000();
    if (flags & 1)
        Free_6b0000(this);
    return this;
}
