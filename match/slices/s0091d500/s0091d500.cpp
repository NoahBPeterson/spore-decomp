// Scalar deleting destructor (0x0091d500): run the destructor (0x91cc60), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_91d500(void* p);   // 0x00f47380

struct Object_91d500 {
    ~Object_91d500();        // 0x0091cc60
    void* DeletingDtor(unsigned int flags);
};

// @ 0x0091d500
void* Object_91d500::DeletingDtor(unsigned int flags)
{
    this->~Object_91d500();
    if (flags & 1)
        Free_91d500(this);
    return this;
}
