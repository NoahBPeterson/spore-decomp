// Scalar deleting destructor (0x00b63980): its inline destructor restores the vtable and runs the base destructor (0x5725a0), then the object is freed (0xf47380) when bit 0 of the flags is set.
#include "game/types.h"

void Free_b63980(void* p);   // 0x00f47380

struct Base_b63980 {
    virtual void b0();
    ~Base_b63980();          // 0x005725a0
};
struct Object_b63980 : Base_b63980 {
    virtual void v0();
    ~Object_b63980() { (void)this; }
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00b63980
void* Object_b63980::DeletingDtor(unsigned int flags)
{
    this->~Object_b63980();
    if (flags & 1)
        Free_b63980(this);
    return this;
}
