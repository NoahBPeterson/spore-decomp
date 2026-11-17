// Scalar deleting destructor (0x0081be00): run the destructor (0x81b100), then free the object (0x951330) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_81be00(void* p);   // 0x00951330

struct Object_81be00 {
    ~Object_81be00();        // 0x0081b100
    void* DeletingDtor(unsigned int flags);
};

// @ 0x0081be00
void* Object_81be00::DeletingDtor(unsigned int flags)
{
    this->~Object_81be00();
    if (flags & 1)
        Free_81be00(this);
    return this;
}
