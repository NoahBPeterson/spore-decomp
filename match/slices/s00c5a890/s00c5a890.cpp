// Scalar deleting destructor (0x00c5a890): run the destructor (0xc5a7d0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_c5a890(void* p);   // 0x00f47380

struct Object_c5a890 {
    ~Object_c5a890();        // 0x00c5a7d0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00c5a890
void* Object_c5a890::DeletingDtor(unsigned int flags)
{
    this->~Object_c5a890();
    if (flags & 1)
        Free_c5a890(this);
    return this;
}
