// Scalar deleting destructor (0x01133eb0): its inline destructor restores the vtable, then the object is freed (0xf47380) when bit 0 of the flags is set.
#include "game/types.h"

void Free_1133eb0(void* p);   // 0x00f47380

struct Object_1133eb0 {
    virtual void v0();
    ~Object_1133eb0() { (void)this; }
    void* DeletingDtor(unsigned int flags);
};

// @ 0x01133eb0
void* Object_1133eb0::DeletingDtor(unsigned int flags)
{
    this->~Object_1133eb0();
    if (flags & 1)
        Free_1133eb0(this);
    return this;
}
