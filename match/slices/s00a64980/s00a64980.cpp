// Scalar deleting destructor (0x00a64980): its inline destructor restores the vtable, then the object is freed (0xf47380) when bit 0 of the flags is set.
#include "game/types.h"

void Free_a64980(void* p);   // 0x00f47380

struct Object_a64980 {
    virtual void v0();
    ~Object_a64980() { (void)this; }
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00a64980
void* Object_a64980::DeletingDtor(unsigned int flags)
{
    this->~Object_a64980();
    if (flags & 1)
        Free_a64980(this);
    return this;
}
