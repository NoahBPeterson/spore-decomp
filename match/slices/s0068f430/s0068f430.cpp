// Scalar deleting destructor (0x0068f430): its inline destructor restores the vtable, then the object is freed (0xf47380) when bit 0 of the flags is set.
#include "game/types.h"

void Free_68f430(void* p);   // 0x00f47380

struct Object_68f430 {
    virtual void v0();
    ~Object_68f430() { (void)this; }
    void* DeletingDtor(unsigned int flags);
};

// @ 0x0068f430
void* Object_68f430::DeletingDtor(unsigned int flags)
{
    this->~Object_68f430();
    if (flags & 1)
        Free_68f430(this);
    return this;
}
