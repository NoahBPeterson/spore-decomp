// Scalar deleting destructor (0x00613840): run the destructor (0x6137e0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_613840(void* p);   // 0x00f47380

struct Object_613840 {
    ~Object_613840();        // 0x006137e0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00613840
void* Object_613840::DeletingDtor(unsigned int flags)
{
    this->~Object_613840();
    if (flags & 1)
        Free_613840(this);
    return this;
}
