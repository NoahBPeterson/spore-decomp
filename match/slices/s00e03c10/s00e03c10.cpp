// Scalar deleting destructor (0x00e03c10): run the destructor (0xe03b20), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_e03c10(void* p);   // 0x00f47380

struct Object_e03c10 {
    ~Object_e03c10();        // 0x00e03b20
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00e03c10
void* Object_e03c10::DeletingDtor(unsigned int flags)
{
    this->~Object_e03c10();
    if (flags & 1)
        Free_e03c10(this);
    return this;
}
