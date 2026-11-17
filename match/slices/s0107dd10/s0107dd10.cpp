// Scalar deleting destructor (0x0107dd10): its inline destructor restores the vtable, then the object is freed (0xf47380) when bit 0 of the flags is set.
#include "game/types.h"

void Free_107dd10(void* p);   // 0x00f47380

struct Object_107dd10 {
    virtual void v0();
    ~Object_107dd10() { (void)this; }
    void* DeletingDtor(unsigned int flags);
};

// @ 0x0107dd10
void* Object_107dd10::DeletingDtor(unsigned int flags)
{
    this->~Object_107dd10();
    if (flags & 1)
        Free_107dd10(this);
    return this;
}
