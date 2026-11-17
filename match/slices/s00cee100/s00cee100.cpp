// Scalar deleting destructor (0x00cee100): its inline destructor restores the vtable and runs the base destructor (0x83c750), then the object is freed (0xf47380) when bit 0 of the flags is set.
#include "game/types.h"

void Free_cee100(void* p);   // 0x00f47380

struct Base_cee100 {
    virtual void b0();
    ~Base_cee100();          // 0x0083c750
};
struct Object_cee100 : Base_cee100 {
    virtual void v0();
    ~Object_cee100() { (void)this; }
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00cee100
void* Object_cee100::DeletingDtor(unsigned int flags)
{
    this->~Object_cee100();
    if (flags & 1)
        Free_cee100(this);
    return this;
}
