// Scalar deleting destructor (0x006bbb40): its inline destructor restores the vtable, then the object is freed (0xf47380) when bit 0 of the flags is set.
#include "game/types.h"

void Free_6bbb40(void* p);   // 0x00f47380

struct Object_6bbb40 {
    virtual void v0();
    ~Object_6bbb40() { (void)this; }
    void* DeletingDtor(unsigned int flags);
};

// @ 0x006bbb40
void* Object_6bbb40::DeletingDtor(unsigned int flags)
{
    this->~Object_6bbb40();
    if (flags & 1)
        Free_6bbb40(this);
    return this;
}
