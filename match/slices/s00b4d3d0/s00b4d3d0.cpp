// Scalar deleting destructor (0x00b4d3d0): its inline destructor restores the vtable, then the object is freed (0xf47380) when bit 0 of the flags is set.
#include "game/types.h"

void Free_b4d3d0(void* p);   // 0x00f47380

struct Object_b4d3d0 {
    virtual void v0();
    ~Object_b4d3d0() { (void)this; }
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00b4d3d0
void* Object_b4d3d0::DeletingDtor(unsigned int flags)
{
    this->~Object_b4d3d0();
    if (flags & 1)
        Free_b4d3d0(this);
    return this;
}
