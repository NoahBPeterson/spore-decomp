// Scalar deleting destructor (0x005bdd70): run the destructor (0x5bdad0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_5bdd70(void* p);   // 0x00f47380

struct Object_5bdd70 {
    ~Object_5bdd70();        // 0x005bdad0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x005bdd70
void* Object_5bdd70::DeletingDtor(unsigned int flags)
{
    this->~Object_5bdd70();
    if (flags & 1)
        Free_5bdd70(this);
    return this;
}
