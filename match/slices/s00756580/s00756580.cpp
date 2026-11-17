// Scalar deleting destructor (0x00756580): run the destructor (0x755da0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_756580(void* p);   // 0x00f47380

struct Object_756580 {
    ~Object_756580();        // 0x00755da0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00756580
void* Object_756580::DeletingDtor(unsigned int flags)
{
    this->~Object_756580();
    if (flags & 1)
        Free_756580(this);
    return this;
}
