// Scalar deleting destructor (0x0097feb0): run the destructor (0x97fb60), then free the object (0x951330) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_97feb0(void* p);   // 0x00951330

struct Object_97feb0 {
    ~Object_97feb0();        // 0x0097fb60
    void* DeletingDtor(unsigned int flags);
};

// @ 0x0097feb0
void* Object_97feb0::DeletingDtor(unsigned int flags)
{
    this->~Object_97feb0();
    if (flags & 1)
        Free_97feb0(this);
    return this;
}
