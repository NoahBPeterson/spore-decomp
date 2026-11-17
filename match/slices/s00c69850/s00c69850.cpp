// Scalar deleting destructor (0x00c69850): its inline destructor restores the vtable and runs the base destructor (0xe92660), then the object is freed (0xf47380) when bit 0 of the flags is set.
#include "game/types.h"

void Free_c69850(void* p);   // 0x00f47380

struct Base_c69850 {
    virtual void b0();
    ~Base_c69850();          // 0x00e92660
};
struct Object_c69850 : Base_c69850 {
    virtual void v0();
    ~Object_c69850() { (void)this; }
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00c69850
void* Object_c69850::DeletingDtor(unsigned int flags)
{
    this->~Object_c69850();
    if (flags & 1)
        Free_c69850(this);
    return this;
}
