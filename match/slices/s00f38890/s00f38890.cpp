// Scalar deleting destructor (0x00f38890): run the destructor (0xf38610), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_f38890(void* p);   // 0x00f47380

struct Object_f38890 {
    ~Object_f38890();        // 0x00f38610
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00f38890
void* Object_f38890::DeletingDtor(unsigned int flags)
{
    this->~Object_f38890();
    if (flags & 1)
        Free_f38890(this);
    return this;
}
