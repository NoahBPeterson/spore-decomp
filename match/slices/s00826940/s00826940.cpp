// Scalar deleting destructor (0x00826940): run the destructor (0x826560), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_826940(void* p);   // 0x00f47380

struct Object_826940 {
    ~Object_826940();        // 0x00826560
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00826940
void* Object_826940::DeletingDtor(unsigned int flags)
{
    this->~Object_826940();
    if (flags & 1)
        Free_826940(this);
    return this;
}
