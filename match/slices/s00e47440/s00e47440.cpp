// Scalar deleting destructor (0x00e47440): run the destructor (0xe47300), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_e47440(void* p);   // 0x00f47380

struct Object_e47440 {
    ~Object_e47440();        // 0x00e47300
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00e47440
void* Object_e47440::DeletingDtor(unsigned int flags)
{
    this->~Object_e47440();
    if (flags & 1)
        Free_e47440(this);
    return this;
}
