// Scalar deleting destructor (0x00e90d50): its inline destructor restores the vtable and runs the base destructor (0xe92660), then the object is freed (0xf47380) when bit 0 of the flags is set.
#include "game/types.h"

void Free_e90d50(void* p);   // 0x00f47380

struct Base_e90d50 {
    virtual void b0();
    ~Base_e90d50();          // 0x00e92660
};
struct Object_e90d50 : Base_e90d50 {
    virtual void v0();
    ~Object_e90d50() { (void)this; }
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00e90d50
void* Object_e90d50::DeletingDtor(unsigned int flags)
{
    this->~Object_e90d50();
    if (flags & 1)
        Free_e90d50(this);
    return this;
}
