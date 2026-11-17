// Scalar deleting destructor (0x00925f60): its inline destructor restores the vtable and runs the base destructor (0x925d60), then the object is freed (0xf47380) when bit 0 of the flags is set.
#include "game/types.h"

void Free_925f60(void* p);   // 0x00f47380

struct Base_925f60 {
    virtual void b0();
    ~Base_925f60();          // 0x00925d60
};
struct Object_925f60 : Base_925f60 {
    virtual void v0();
    ~Object_925f60() { (void)this; }
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00925f60
void* Object_925f60::DeletingDtor(unsigned int flags)
{
    this->~Object_925f60();
    if (flags & 1)
        Free_925f60(this);
    return this;
}
