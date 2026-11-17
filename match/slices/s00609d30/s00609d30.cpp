// Scalar deleting destructor (0x00609d30): its inline destructor restores the vtable, then the object is freed (0xf47380) when bit 0 of the flags is set.
#include "game/types.h"

void Free_609d30(void* p);   // 0x00f47380

struct Object_609d30 {
    virtual void v0();
    ~Object_609d30() { (void)this; }
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00609d30
void* Object_609d30::DeletingDtor(unsigned int flags)
{
    this->~Object_609d30();
    if (flags & 1)
        Free_609d30(this);
    return this;
}
