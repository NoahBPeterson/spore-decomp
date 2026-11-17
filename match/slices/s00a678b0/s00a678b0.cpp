// Scalar deleting destructor (0x00a678b0): its inline destructor restores the vtable, then the object is freed (0xf47380) when bit 0 of the flags is set.
#include "game/types.h"

void Free_a678b0(void* p);   // 0x00f47380

struct Object_a678b0 {
    virtual void v0();
    ~Object_a678b0() { (void)this; }
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00a678b0
void* Object_a678b0::DeletingDtor(unsigned int flags)
{
    this->~Object_a678b0();
    if (flags & 1)
        Free_a678b0(this);
    return this;
}
