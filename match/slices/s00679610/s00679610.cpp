// Scalar deleting destructor (0x00679610): run the destructor (0x679400), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_679610(void* p);   // 0x00f47380

struct Object_679610 {
    ~Object_679610();        // 0x00679400
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00679610
void* Object_679610::DeletingDtor(unsigned int flags)
{
    this->~Object_679610();
    if (flags & 1)
        Free_679610(this);
    return this;
}
