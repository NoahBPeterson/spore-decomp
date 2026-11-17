// Scalar deleting destructor (0x011ec090): its inline destructor restores the vtable, then the object is freed (0xf47380) when bit 0 of the flags is set.
#include "game/types.h"

void Free_11ec090(void* p);   // 0x00f47380

struct Object_11ec090 {
    virtual void v0();
    ~Object_11ec090() { (void)this; }
    void* DeletingDtor(unsigned int flags);
};

// @ 0x011ec090
void* Object_11ec090::DeletingDtor(unsigned int flags)
{
    this->~Object_11ec090();
    if (flags & 1)
        Free_11ec090(this);
    return this;
}
