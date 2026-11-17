// Scalar deleting destructor (0x00d07a80): its inline destructor restores the vtable and runs the base destructor (0x8014b0), then the object is freed (0xf47380) when bit 0 of the flags is set.
#include "game/types.h"

void Free_d07a80(void* p);   // 0x00f47380

struct Base_d07a80 {
    virtual void b0();
    ~Base_d07a80();          // 0x008014b0
};
struct Object_d07a80 : Base_d07a80 {
    virtual void v0();
    ~Object_d07a80() { (void)this; }
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00d07a80
void* Object_d07a80::DeletingDtor(unsigned int flags)
{
    this->~Object_d07a80();
    if (flags & 1)
        Free_d07a80(this);
    return this;
}
