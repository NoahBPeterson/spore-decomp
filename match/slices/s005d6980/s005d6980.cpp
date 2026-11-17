// Scalar deleting destructor (0x005d6980): its inline destructor restores the vtable, then the object is freed (0xf47380) when bit 0 of the flags is set.
#include "game/types.h"

void Free_5d6980(void* p);   // 0x00f47380

struct Object_5d6980 {
    virtual void v0();
    ~Object_5d6980() { (void)this; }
    void* DeletingDtor(unsigned int flags);
};

// @ 0x005d6980
void* Object_5d6980::DeletingDtor(unsigned int flags)
{
    this->~Object_5d6980();
    if (flags & 1)
        Free_5d6980(this);
    return this;
}
