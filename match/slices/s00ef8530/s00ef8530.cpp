// Scalar deleting destructor (0x00ef8530): run the destructor (0xef7950), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_ef8530(void* p);   // 0x00f47380

struct Object_ef8530 {
    ~Object_ef8530();        // 0x00ef7950
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00ef8530
void* Object_ef8530::DeletingDtor(unsigned int flags)
{
    this->~Object_ef8530();
    if (flags & 1)
        Free_ef8530(this);
    return this;
}
