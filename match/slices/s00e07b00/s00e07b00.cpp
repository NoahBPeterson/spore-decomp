// Scalar deleting destructor (0x00e07b00): run the destructor (0xe07750), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_e07b00(void* p);   // 0x00f47380

struct Object_e07b00 {
    ~Object_e07b00();        // 0x00e07750
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00e07b00
void* Object_e07b00::DeletingDtor(unsigned int flags)
{
    this->~Object_e07b00();
    if (flags & 1)
        Free_e07b00(this);
    return this;
}
