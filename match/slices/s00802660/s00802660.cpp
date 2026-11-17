// Scalar deleting destructor (0x00802660): run the destructor (0x801fd0), then free the object (0x926060) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_802660(void* p);   // 0x00926060

struct Object_802660 {
    ~Object_802660();        // 0x00801fd0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00802660
void* Object_802660::DeletingDtor(unsigned int flags)
{
    this->~Object_802660();
    if (flags & 1)
        Free_802660(this);
    return this;
}
