// Scalar deleting destructor (0x006ae1f0): its inline destructor restores the vtable, then the object is freed (0xf47380) when bit 0 of the flags is set.
#include "game/types.h"

void Free_6ae1f0(void* p);   // 0x00f47380

struct Object_6ae1f0 {
    virtual void v0();
    ~Object_6ae1f0() { (void)this; }
    void* DeletingDtor(unsigned int flags);
};

// @ 0x006ae1f0
void* Object_6ae1f0::DeletingDtor(unsigned int flags)
{
    this->~Object_6ae1f0();
    if (flags & 1)
        Free_6ae1f0(this);
    return this;
}
