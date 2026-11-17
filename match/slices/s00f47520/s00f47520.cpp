// Scalar deleting destructor (0x00f47520): its inline destructor restores the vtable and runs the base destructor (0x5725a0), then the object is freed (0xf47380) when bit 0 of the flags is set.
#include "game/types.h"

void Free_f47520(void* p);   // 0x00f47380

struct Base_f47520 {
    virtual void b0();
    ~Base_f47520();          // 0x005725a0
};
struct Object_f47520 : Base_f47520 {
    virtual void v0();
    ~Object_f47520() { (void)this; }
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00f47520
void* Object_f47520::DeletingDtor(unsigned int flags)
{
    this->~Object_f47520();
    if (flags & 1)
        Free_f47520(this);
    return this;
}
