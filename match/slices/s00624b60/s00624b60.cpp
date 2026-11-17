// Scalar deleting destructor (0x00624b60): its inline destructor restores the vtable, then the object is freed (0xf47380) when bit 0 of the flags is set.
#include "game/types.h"

void Free_624b60(void* p);   // 0x00f47380

struct Object_624b60 {
    virtual void v0();
    ~Object_624b60() { (void)this; }
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00624b60
void* Object_624b60::DeletingDtor(unsigned int flags)
{
    this->~Object_624b60();
    if (flags & 1)
        Free_624b60(this);
    return this;
}
