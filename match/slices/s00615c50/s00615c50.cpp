// Scalar deleting destructor (0x00615c50): its inline destructor restores the vtable, then the object is freed (0xf47380) when bit 0 of the flags is set.
#include "game/types.h"

void Free_615c50(void* p);   // 0x00f47380

struct Object_615c50 {
    virtual void v0();
    ~Object_615c50() { (void)this; }
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00615c50
void* Object_615c50::DeletingDtor(unsigned int flags)
{
    this->~Object_615c50();
    if (flags & 1)
        Free_615c50(this);
    return this;
}
