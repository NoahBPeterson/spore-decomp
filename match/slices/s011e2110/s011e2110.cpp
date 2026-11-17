// Scalar deleting destructor (0x011e2110): its inline destructor restores the vtable, then the object is freed (0xf47380) when bit 0 of the flags is set.
#include "game/types.h"

void Free_11e2110(void* p);   // 0x00f47380

struct Object_11e2110 {
    virtual void v0();
    ~Object_11e2110() { (void)this; }
    void* DeletingDtor(unsigned int flags);
};

// @ 0x011e2110
void* Object_11e2110::DeletingDtor(unsigned int flags)
{
    this->~Object_11e2110();
    if (flags & 1)
        Free_11e2110(this);
    return this;
}
