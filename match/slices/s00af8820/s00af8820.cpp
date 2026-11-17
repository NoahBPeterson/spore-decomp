// Scalar deleting destructor (0x00af8820): its inline destructor restores the vtable, then the object is freed (0xf47380) when bit 0 of the flags is set.
#include "game/types.h"

void Free_af8820(void* p);   // 0x00f47380

struct Object_af8820 {
    virtual void v0();
    ~Object_af8820() { (void)this; }
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00af8820
void* Object_af8820::DeletingDtor(unsigned int flags)
{
    this->~Object_af8820();
    if (flags & 1)
        Free_af8820(this);
    return this;
}
