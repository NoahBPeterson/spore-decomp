// Scalar deleting destructor (0x00704da0): its inline destructor restores the vtable, then the object is freed (0x926060) when bit 0 of the flags is set.
#include "game/types.h"

void Free_704da0(void* p);   // 0x00926060

struct Object_704da0 {
    virtual void v0();
    ~Object_704da0() { (void)this; }
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00704da0
void* Object_704da0::DeletingDtor(unsigned int flags)
{
    this->~Object_704da0();
    if (flags & 1)
        Free_704da0(this);
    return this;
}
