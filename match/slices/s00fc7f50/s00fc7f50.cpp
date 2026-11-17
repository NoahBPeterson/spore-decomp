// Scalar deleting destructor (0x00fc7f50): its inline destructor restores the vtable, then the object is freed (0xf47380) when bit 0 of the flags is set.
#include "game/types.h"

void Free_fc7f50(void* p);   // 0x00f47380

struct Object_fc7f50 {
    virtual void v0();
    ~Object_fc7f50() { (void)this; }
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00fc7f50
void* Object_fc7f50::DeletingDtor(unsigned int flags)
{
    this->~Object_fc7f50();
    if (flags & 1)
        Free_fc7f50(this);
    return this;
}
