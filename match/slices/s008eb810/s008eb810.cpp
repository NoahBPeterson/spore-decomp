// Scalar deleting destructor (0x008eb810): its inline destructor restores the vtable, then the object is freed (0xf47380) when bit 0 of the flags is set.
#include "game/types.h"

void Free_8eb810(void* p);   // 0x00f47380

struct Object_8eb810 {
    virtual void v0();
    ~Object_8eb810() { (void)this; }
    void* DeletingDtor(unsigned int flags);
};

// @ 0x008eb810
void* Object_8eb810::DeletingDtor(unsigned int flags)
{
    this->~Object_8eb810();
    if (flags & 1)
        Free_8eb810(this);
    return this;
}
