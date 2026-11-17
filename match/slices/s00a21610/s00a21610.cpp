// Scalar deleting destructor (0x00a21610): its inline destructor restores the vtable, then the object is freed (0xf47380) when bit 0 of the flags is set.
#include "game/types.h"

void Free_a21610(void* p);   // 0x00f47380

struct Object_a21610 {
    virtual void v0();
    ~Object_a21610() { (void)this; }
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00a21610
void* Object_a21610::DeletingDtor(unsigned int flags)
{
    this->~Object_a21610();
    if (flags & 1)
        Free_a21610(this);
    return this;
}
