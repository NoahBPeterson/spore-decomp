// Scalar deleting destructor (0x0092a840): its inline destructor restores the vtable, then the object is freed (0xf47380) when bit 0 of the flags is set.
#include "game/types.h"

void Free_92a840(void* p);   // 0x00f47380

struct Object_92a840 {
    virtual void v0();
    ~Object_92a840() { (void)this; }
    void* DeletingDtor(unsigned int flags);
};

// @ 0x0092a840
void* Object_92a840::DeletingDtor(unsigned int flags)
{
    this->~Object_92a840();
    if (flags & 1)
        Free_92a840(this);
    return this;
}
