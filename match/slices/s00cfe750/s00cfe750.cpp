// Scalar deleting destructor (0x00cfe750): its inline destructor restores the vtable and runs the base destructor (0xb32490), then the object is freed (0xf47380) when bit 0 of the flags is set.
#include "game/types.h"

void Free_cfe750(void* p);   // 0x00f47380

struct Base_cfe750 {
    virtual void b0();
    ~Base_cfe750();          // 0x00b32490
};
struct Object_cfe750 : Base_cfe750 {
    virtual void v0();
    ~Object_cfe750() { (void)this; }
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00cfe750
void* Object_cfe750::DeletingDtor(unsigned int flags)
{
    this->~Object_cfe750();
    if (flags & 1)
        Free_cfe750(this);
    return this;
}
