// Scalar deleting destructor (0x009520e0): its inline destructor restores the vtable, then the object is freed (0xf47380) when bit 0 of the flags is set.
#include "game/types.h"

void Free_9520e0(void* p);   // 0x00f47380

struct Object_9520e0 {
    virtual void v0();
    ~Object_9520e0() { (void)this; }
    void* DeletingDtor(unsigned int flags);
};

// @ 0x009520e0
void* Object_9520e0::DeletingDtor(unsigned int flags)
{
    this->~Object_9520e0();
    if (flags & 1)
        Free_9520e0(this);
    return this;
}
