// Scalar deleting destructor (0x0059d940): its inline destructor restores the vtable, then the object is freed (0xf47380) when bit 0 of the flags is set.
#include "game/types.h"

void Free_59d940(void* p);   // 0x00f47380

struct Object_59d940 {
    virtual void v0();
    ~Object_59d940() { (void)this; }
    void* DeletingDtor(unsigned int flags);
};

// @ 0x0059d940
void* Object_59d940::DeletingDtor(unsigned int flags)
{
    this->~Object_59d940();
    if (flags & 1)
        Free_59d940(this);
    return this;
}
