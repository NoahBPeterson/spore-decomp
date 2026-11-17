// Scalar deleting destructor (0x0063f040): its inline destructor restores the vtable, then the object is freed (0xf47380) when bit 0 of the flags is set.
#include "game/types.h"

void Free_63f040(void* p);   // 0x00f47380

struct Object_63f040 {
    virtual void v0();
    ~Object_63f040() { (void)this; }
    void* DeletingDtor(unsigned int flags);
};

// @ 0x0063f040
void* Object_63f040::DeletingDtor(unsigned int flags)
{
    this->~Object_63f040();
    if (flags & 1)
        Free_63f040(this);
    return this;
}
