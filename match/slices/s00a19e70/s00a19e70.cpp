// Scalar deleting destructor (0x00a19e70): run the destructor (0xa19e00), then free the object (0x926060) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_a19e70(void* p);   // 0x00926060

struct Object_a19e70 {
    ~Object_a19e70();        // 0x00a19e00
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00a19e70
void* Object_a19e70::DeletingDtor(unsigned int flags)
{
    this->~Object_a19e70();
    if (flags & 1)
        Free_a19e70(this);
    return this;
}
