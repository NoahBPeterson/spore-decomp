// Scalar deleting destructor (0x00803200): run the destructor (0x803140), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_803200(void* p);   // 0x00f47380

struct Object_803200 {
    ~Object_803200();        // 0x00803140
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00803200
void* Object_803200::DeletingDtor(unsigned int flags)
{
    this->~Object_803200();
    if (flags & 1)
        Free_803200(this);
    return this;
}
