// Scalar deleting destructor (0x006c0b00): run the destructor (0x6c0710), then free the object (0x926060) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_6c0b00(void* p);   // 0x00926060

struct Object_6c0b00 {
    ~Object_6c0b00();        // 0x006c0710
    void* DeletingDtor(unsigned int flags);
};

// @ 0x006c0b00
void* Object_6c0b00::DeletingDtor(unsigned int flags)
{
    this->~Object_6c0b00();
    if (flags & 1)
        Free_6c0b00(this);
    return this;
}
