// Scalar deleting destructor (0x00d15060): its inline destructor restores the vtable and runs the base destructor (0xaf1430), then the object is freed (0xf47380) when bit 0 of the flags is set.
#include "game/types.h"

void Free_d15060(void* p);   // 0x00f47380

struct Base_d15060 {
    virtual void b0();
    ~Base_d15060();          // 0x00af1430
};
struct Object_d15060 : Base_d15060 {
    virtual void v0();
    ~Object_d15060() { (void)this; }
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00d15060
void* Object_d15060::DeletingDtor(unsigned int flags)
{
    this->~Object_d15060();
    if (flags & 1)
        Free_d15060(this);
    return this;
}
