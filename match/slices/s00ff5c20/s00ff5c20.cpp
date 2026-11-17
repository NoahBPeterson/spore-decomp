// Scalar deleting destructor (0x00ff5c20): its inline destructor restores the vtable and runs the base destructor (0x83c750), then the object is freed (0xf47380) when bit 0 of the flags is set.
#include "game/types.h"

void Free_ff5c20(void* p);   // 0x00f47380

struct Base_ff5c20 {
    virtual void b0();
    ~Base_ff5c20();          // 0x0083c750
};
struct Object_ff5c20 : Base_ff5c20 {
    virtual void v0();
    ~Object_ff5c20() { (void)this; }
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00ff5c20
void* Object_ff5c20::DeletingDtor(unsigned int flags)
{
    this->~Object_ff5c20();
    if (flags & 1)
        Free_ff5c20(this);
    return this;
}
