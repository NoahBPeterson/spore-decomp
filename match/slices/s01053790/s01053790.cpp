// Scalar deleting destructor (0x01053790): its inline destructor restores the vtable, then the object is freed (0xf47380) when bit 0 of the flags is set.
#include "game/types.h"

void Free_1053790(void* p);   // 0x00f47380

struct Object_1053790 {
    virtual void v0();
    ~Object_1053790() { (void)this; }
    void* DeletingDtor(unsigned int flags);
};

// @ 0x01053790
void* Object_1053790::DeletingDtor(unsigned int flags)
{
    this->~Object_1053790();
    if (flags & 1)
        Free_1053790(this);
    return this;
}
