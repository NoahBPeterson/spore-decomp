// Scalar deleting destructor (0x00de4700): its inline destructor restores the vtable, then the object is freed (0xf47380) when bit 0 of the flags is set.
#include "game/types.h"

void Free_de4700(void* p);   // 0x00f47380

struct Object_de4700 {
    virtual void v0();
    ~Object_de4700() { (void)this; }
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00de4700
void* Object_de4700::DeletingDtor(unsigned int flags)
{
    this->~Object_de4700();
    if (flags & 1)
        Free_de4700(this);
    return this;
}
