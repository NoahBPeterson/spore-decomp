// Scalar deleting destructor (0x00fcc1c0): its inline destructor restores the vtable, then the object is freed (0xf47380) when bit 0 of the flags is set.
#include "game/types.h"

void Free_fcc1c0(void* p);   // 0x00f47380

struct Object_fcc1c0 {
    virtual void v0();
    ~Object_fcc1c0() { (void)this; }
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00fcc1c0
void* Object_fcc1c0::DeletingDtor(unsigned int flags)
{
    this->~Object_fcc1c0();
    if (flags & 1)
        Free_fcc1c0(this);
    return this;
}
