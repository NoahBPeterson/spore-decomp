// Scalar deleting destructor (0x00845fe0): run the destructor (0x844e50), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_845fe0(void* p);   // 0x00f47380

struct Object_845fe0 {
    ~Object_845fe0();        // 0x00844e50
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00845fe0
void* Object_845fe0::DeletingDtor(unsigned int flags)
{
    this->~Object_845fe0();
    if (flags & 1)
        Free_845fe0(this);
    return this;
}
