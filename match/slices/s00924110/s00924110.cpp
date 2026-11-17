// Scalar deleting destructor (0x00924110): run the destructor (0x923e70), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_924110(void* p);   // 0x00f47380

struct Object_924110 {
    ~Object_924110();        // 0x00923e70
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00924110
void* Object_924110::DeletingDtor(unsigned int flags)
{
    this->~Object_924110();
    if (flags & 1)
        Free_924110(this);
    return this;
}
