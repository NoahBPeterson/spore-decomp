// Scalar deleting destructor (0x00bba280): run the destructor (0xbba220), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_bba280(void* p);   // 0x00f47380

struct Object_bba280 {
    ~Object_bba280();        // 0x00bba220
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00bba280
void* Object_bba280::DeletingDtor(unsigned int flags)
{
    this->~Object_bba280();
    if (flags & 1)
        Free_bba280(this);
    return this;
}
