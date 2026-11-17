// Scalar deleting destructor (0x010a2c40): its inline destructor restores the vtable, then the object is freed (0xf47380) when bit 0 of the flags is set.
#include "game/types.h"

void Free_10a2c40(void* p);   // 0x00f47380

struct Object_10a2c40 {
    virtual void v0();
    ~Object_10a2c40() { (void)this; }
    void* DeletingDtor(unsigned int flags);
};

// @ 0x010a2c40
void* Object_10a2c40::DeletingDtor(unsigned int flags)
{
    this->~Object_10a2c40();
    if (flags & 1)
        Free_10a2c40(this);
    return this;
}
