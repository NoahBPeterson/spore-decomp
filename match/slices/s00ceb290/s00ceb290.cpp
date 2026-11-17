// Scalar deleting destructor (0x00ceb290): run the destructor (0xceac50), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_ceb290(void* p);   // 0x00f47380

struct Object_ceb290 {
    ~Object_ceb290();        // 0x00ceac50
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00ceb290
void* Object_ceb290::DeletingDtor(unsigned int flags)
{
    this->~Object_ceb290();
    if (flags & 1)
        Free_ceb290(this);
    return this;
}
