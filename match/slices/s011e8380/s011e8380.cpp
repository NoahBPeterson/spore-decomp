// Scalar deleting destructor (0x011e8380): its inline destructor restores the vtable, then the object is freed (0xf47380) when bit 0 of the flags is set.
#include "game/types.h"

void Free_11e8380(void* p);   // 0x00f47380

struct Object_11e8380 {
    virtual void v0();
    ~Object_11e8380() { (void)this; }
    void* DeletingDtor(unsigned int flags);
};

// @ 0x011e8380
void* Object_11e8380::DeletingDtor(unsigned int flags)
{
    this->~Object_11e8380();
    if (flags & 1)
        Free_11e8380(this);
    return this;
}
