// Scalar deleting destructor (0x0091d460): run the destructor (0x91cb40), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_91d460(void* p);   // 0x00f47380

struct Object_91d460 {
    ~Object_91d460();        // 0x0091cb40
    void* DeletingDtor(unsigned int flags);
};

// @ 0x0091d460
void* Object_91d460::DeletingDtor(unsigned int flags)
{
    this->~Object_91d460();
    if (flags & 1)
        Free_91d460(this);
    return this;
}
