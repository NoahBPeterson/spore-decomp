// Scalar deleting destructor (0x00ac5460): run the destructor (0xac5350), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_ac5460(void* p);   // 0x00f47380

struct Object_ac5460 {
    ~Object_ac5460();        // 0x00ac5350
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00ac5460
void* Object_ac5460::DeletingDtor(unsigned int flags)
{
    this->~Object_ac5460();
    if (flags & 1)
        Free_ac5460(this);
    return this;
}
