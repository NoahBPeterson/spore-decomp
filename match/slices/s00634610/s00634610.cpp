// Scalar deleting destructor (0x00634610): its inline destructor restores the vtable and runs the base destructor (0x5725a0), then the object is freed (0xf47380) when bit 0 of the flags is set.
#include "game/types.h"

void Free_634610(void* p);   // 0x00f47380

struct Base_634610 {
    virtual void b0();
    ~Base_634610();          // 0x005725a0
};
struct Object_634610 : Base_634610 {
    virtual void v0();
    ~Object_634610() { (void)this; }
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00634610
void* Object_634610::DeletingDtor(unsigned int flags)
{
    this->~Object_634610();
    if (flags & 1)
        Free_634610(this);
    return this;
}
