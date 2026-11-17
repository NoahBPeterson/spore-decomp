// Scalar deleting destructor (0x0083c820): its inline destructor restores the vtable, then the object is freed (0xf47380) when bit 0 of the flags is set.
#include "game/types.h"

void Free_83c820(void* p);   // 0x00f47380

struct Object_83c820 {
    virtual void v0();
    ~Object_83c820() { (void)this; }
    void* DeletingDtor(unsigned int flags);
};

// @ 0x0083c820
void* Object_83c820::DeletingDtor(unsigned int flags)
{
    this->~Object_83c820();
    if (flags & 1)
        Free_83c820(this);
    return this;
}
