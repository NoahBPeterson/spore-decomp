// Scalar deleting destructor (0x00766200): run the destructor (0x766140), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_766200(void* p);   // 0x00f47380

struct Object_766200 {
    ~Object_766200();        // 0x00766140
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00766200
void* Object_766200::DeletingDtor(unsigned int flags)
{
    this->~Object_766200();
    if (flags & 1)
        Free_766200(this);
    return this;
}
