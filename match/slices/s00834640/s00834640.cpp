// Scalar deleting destructor (0x00834640): run the destructor (0x834160), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_834640(void* p);   // 0x00f47380

struct Object_834640 {
    ~Object_834640();        // 0x00834160
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00834640
void* Object_834640::DeletingDtor(unsigned int flags)
{
    this->~Object_834640();
    if (flags & 1)
        Free_834640(this);
    return this;
}
