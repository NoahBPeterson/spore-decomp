// Scalar deleting destructor (0x00dd7890): run the destructor (0xdd7160), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_dd7890(void* p);   // 0x00f47380

struct Object_dd7890 {
    ~Object_dd7890();        // 0x00dd7160
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00dd7890
void* Object_dd7890::DeletingDtor(unsigned int flags)
{
    this->~Object_dd7890();
    if (flags & 1)
        Free_dd7890(this);
    return this;
}
