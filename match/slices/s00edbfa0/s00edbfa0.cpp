// Scalar deleting destructor (0x00edbfa0): run the destructor (0xedbe60), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_edbfa0(void* p);   // 0x00f47380

struct Object_edbfa0 {
    ~Object_edbfa0();        // 0x00edbe60
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00edbfa0
void* Object_edbfa0::DeletingDtor(unsigned int flags)
{
    this->~Object_edbfa0();
    if (flags & 1)
        Free_edbfa0(this);
    return this;
}
