// Scalar deleting destructor (0x00ce6630): its inline destructor restores the vtable and runs the base destructor (0xb32490), then the object is freed (0xf47380) when bit 0 of the flags is set.
#include "game/types.h"

void Free_ce6630(void* p);   // 0x00f47380

struct Base_ce6630 {
    virtual void b0();
    ~Base_ce6630();          // 0x00b32490
};
struct Object_ce6630 : Base_ce6630 {
    virtual void v0();
    ~Object_ce6630() { (void)this; }
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00ce6630
void* Object_ce6630::DeletingDtor(unsigned int flags)
{
    this->~Object_ce6630();
    if (flags & 1)
        Free_ce6630(this);
    return this;
}
