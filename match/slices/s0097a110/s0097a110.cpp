// Scalar deleting destructor (0x0097a110): run the destructor (0x977600), then free the object (0x951330) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_97a110(void* p);   // 0x00951330

struct Object_97a110 {
    ~Object_97a110();        // 0x00977600
    void* DeletingDtor(unsigned int flags);
};

// @ 0x0097a110
void* Object_97a110::DeletingDtor(unsigned int flags)
{
    this->~Object_97a110();
    if (flags & 1)
        Free_97a110(this);
    return this;
}
