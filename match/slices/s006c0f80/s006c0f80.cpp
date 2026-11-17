// Scalar deleting destructor (0x006c0f80): run the destructor (0x6c0ed0), then free the object (0x926060) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_6c0f80(void* p);   // 0x00926060

struct Object_6c0f80 {
    ~Object_6c0f80();        // 0x006c0ed0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x006c0f80
void* Object_6c0f80::DeletingDtor(unsigned int flags)
{
    this->~Object_6c0f80();
    if (flags & 1)
        Free_6c0f80(this);
    return this;
}
