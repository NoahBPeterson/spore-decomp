// Scalar deleting destructor (0x00cee0d0): its inline destructor restores the vtable and runs the base destructor (0x83c750), then the object is freed (0xf47380) when bit 0 of the flags is set.
#include "game/types.h"

void Free_cee0d0(void* p);   // 0x00f47380

struct Base_cee0d0 {
    virtual void b0();
    ~Base_cee0d0();          // 0x0083c750
};
struct Object_cee0d0 : Base_cee0d0 {
    virtual void v0();
    ~Object_cee0d0() { (void)this; }
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00cee0d0
void* Object_cee0d0::DeletingDtor(unsigned int flags)
{
    this->~Object_cee0d0();
    if (flags & 1)
        Free_cee0d0(this);
    return this;
}
