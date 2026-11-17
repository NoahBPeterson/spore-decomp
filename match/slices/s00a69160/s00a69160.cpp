// Scalar deleting destructor (0x00a69160): its inline destructor restores the vtable, then the object is freed (0xf47380) when bit 0 of the flags is set.
#include "game/types.h"

void Free_a69160(void* p);   // 0x00f47380

struct Object_a69160 {
    virtual void v0();
    ~Object_a69160() { (void)this; }
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00a69160
void* Object_a69160::DeletingDtor(unsigned int flags)
{
    this->~Object_a69160();
    if (flags & 1)
        Free_a69160(this);
    return this;
}
