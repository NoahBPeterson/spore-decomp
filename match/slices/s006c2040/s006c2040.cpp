// Scalar deleting destructor (0x006c2040): its inline destructor restores the vtable, then the object is freed (0xf47380) when bit 0 of the flags is set.
#include "game/types.h"

void Free_6c2040(void* p);   // 0x00f47380

struct Object_6c2040 {
    virtual void v0();
    ~Object_6c2040() { (void)this; }
    void* DeletingDtor(unsigned int flags);
};

// @ 0x006c2040
void* Object_6c2040::DeletingDtor(unsigned int flags)
{
    this->~Object_6c2040();
    if (flags & 1)
        Free_6c2040(this);
    return this;
}
