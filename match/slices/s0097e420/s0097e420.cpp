// Scalar deleting destructor (0x0097e420): run the destructor (0x97e1f0), then free the object (0x951330) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_97e420(void* p);   // 0x00951330

struct Object_97e420 {
    ~Object_97e420();        // 0x0097e1f0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x0097e420
void* Object_97e420::DeletingDtor(unsigned int flags)
{
    this->~Object_97e420();
    if (flags & 1)
        Free_97e420(this);
    return this;
}
