// Scalar deleting destructor (0x00e8df20): its inline destructor restores the vtable and runs the base destructor (0xe92660), then the object is freed (0xf47380) when bit 0 of the flags is set.
#include "game/types.h"

void Free_e8df20(void* p);   // 0x00f47380

struct Base_e8df20 {
    virtual void b0();
    ~Base_e8df20();          // 0x00e92660
};
struct Object_e8df20 : Base_e8df20 {
    virtual void v0();
    ~Object_e8df20() { (void)this; }
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00e8df20
void* Object_e8df20::DeletingDtor(unsigned int flags)
{
    this->~Object_e8df20();
    if (flags & 1)
        Free_e8df20(this);
    return this;
}
