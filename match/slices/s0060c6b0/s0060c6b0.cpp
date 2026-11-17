// Scalar deleting destructor (0x0060c6b0): run the destructor (0x60c660), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_60c6b0(void* p);   // 0x00f47380

struct Object_60c6b0 {
    ~Object_60c6b0();        // 0x0060c660
    void* DeletingDtor(unsigned int flags);
};

// @ 0x0060c6b0
void* Object_60c6b0::DeletingDtor(unsigned int flags)
{
    this->~Object_60c6b0();
    if (flags & 1)
        Free_60c6b0(this);
    return this;
}
