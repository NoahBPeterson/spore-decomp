// Scalar deleting destructor (0x011eb960): its inline destructor restores the vtable, then the object is freed (0xf47380) when bit 0 of the flags is set.
#include "game/types.h"

void Free_11eb960(void* p);   // 0x00f47380

struct Object_11eb960 {
    virtual void v0();
    ~Object_11eb960() { (void)this; }
    void* DeletingDtor(unsigned int flags);
};

// @ 0x011eb960
void* Object_11eb960::DeletingDtor(unsigned int flags)
{
    this->~Object_11eb960();
    if (flags & 1)
        Free_11eb960(this);
    return this;
}
