// Scalar deleting destructor (0x01037ac0): its inline destructor restores the vtable, then the object is freed (0xf47380) when bit 0 of the flags is set.
#include "game/types.h"

void Free_1037ac0(void* p);   // 0x00f47380

struct Object_1037ac0 {
    virtual void v0();
    ~Object_1037ac0() { (void)this; }
    void* DeletingDtor(unsigned int flags);
};

// @ 0x01037ac0
void* Object_1037ac0::DeletingDtor(unsigned int flags)
{
    this->~Object_1037ac0();
    if (flags & 1)
        Free_1037ac0(this);
    return this;
}
