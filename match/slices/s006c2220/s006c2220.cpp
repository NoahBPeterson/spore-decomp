// Scalar deleting destructor (0x006c2220): run the destructor (0x6c2170), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_6c2220(void* p);   // 0x00f47380

struct Object_6c2220 {
    ~Object_6c2220();        // 0x006c2170
    void* DeletingDtor(unsigned int flags);
};

// @ 0x006c2220
void* Object_6c2220::DeletingDtor(unsigned int flags)
{
    this->~Object_6c2220();
    if (flags & 1)
        Free_6c2220(this);
    return this;
}
