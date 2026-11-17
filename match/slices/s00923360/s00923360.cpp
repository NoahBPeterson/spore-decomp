// Scalar deleting destructor (0x00923360): its inline destructor restores the vtable, then the object is freed (0xf47380) when bit 0 of the flags is set.
#include "game/types.h"

void Free_923360(void* p);   // 0x00f47380

struct Object_923360 {
    virtual void v0();
    ~Object_923360() { (void)this; }
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00923360
void* Object_923360::DeletingDtor(unsigned int flags)
{
    this->~Object_923360();
    if (flags & 1)
        Free_923360(this);
    return this;
}
