// Scalar deleting destructor (0x00d48720): its inline destructor restores the vtable and runs the base destructor (0xb32490), then the object is freed (0xf47380) when bit 0 of the flags is set.
#include "game/types.h"

void Free_d48720(void* p);   // 0x00f47380

struct Base_d48720 {
    virtual void b0();
    ~Base_d48720();          // 0x00b32490
};
struct Object_d48720 : Base_d48720 {
    virtual void v0();
    ~Object_d48720() { (void)this; }
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00d48720
void* Object_d48720::DeletingDtor(unsigned int flags)
{
    this->~Object_d48720();
    if (flags & 1)
        Free_d48720(this);
    return this;
}
