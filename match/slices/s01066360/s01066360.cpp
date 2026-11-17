// Scalar deleting destructor (0x01066360): its inline destructor restores the vtable and runs the base destructor (0x83c750), then the object is freed (0xf47380) when bit 0 of the flags is set.
#include "game/types.h"

void Free_1066360(void* p);   // 0x00f47380

struct Base_1066360 {
    virtual void b0();
    ~Base_1066360();          // 0x0083c750
};
struct Object_1066360 : Base_1066360 {
    virtual void v0();
    ~Object_1066360() { (void)this; }
    void* DeletingDtor(unsigned int flags);
};

// @ 0x01066360
void* Object_1066360::DeletingDtor(unsigned int flags)
{
    this->~Object_1066360();
    if (flags & 1)
        Free_1066360(this);
    return this;
}
