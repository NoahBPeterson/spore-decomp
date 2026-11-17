// Scalar deleting destructor (0x00bcc310): its inline destructor restores the vtable, then the object is freed (0xf47380) when bit 0 of the flags is set.
#include "game/types.h"

void Free_bcc310(void* p);   // 0x00f47380

struct Object_bcc310 {
    virtual void v0();
    ~Object_bcc310() { (void)this; }
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00bcc310
void* Object_bcc310::DeletingDtor(unsigned int flags)
{
    this->~Object_bcc310();
    if (flags & 1)
        Free_bcc310(this);
    return this;
}
