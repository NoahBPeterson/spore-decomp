// Scalar deleting destructor (0x00e34450): run the destructor (0xe33e70), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_e34450(void* p);   // 0x00f47380

struct Object_e34450 {
    ~Object_e34450();        // 0x00e33e70
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00e34450
void* Object_e34450::DeletingDtor(unsigned int flags)
{
    this->~Object_e34450();
    if (flags & 1)
        Free_e34450(this);
    return this;
}
