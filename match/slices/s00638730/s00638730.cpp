// Scalar deleting destructor (0x00638730): its inline destructor restores the vtable, then the object is freed (0xf47380) when bit 0 of the flags is set.
#include "game/types.h"

void Free_638730(void* p);   // 0x00f47380

struct Object_638730 {
    virtual void v0();
    ~Object_638730() { (void)this; }
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00638730
void* Object_638730::DeletingDtor(unsigned int flags)
{
    this->~Object_638730();
    if (flags & 1)
        Free_638730(this);
    return this;
}
