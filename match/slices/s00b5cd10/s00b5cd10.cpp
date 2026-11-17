// Scalar deleting destructor (0x00b5cd10): its inline destructor restores the vtable and runs the base destructor (0x83c750), then the object is freed (0xf47380) when bit 0 of the flags is set.
#include "game/types.h"

void Free_b5cd10(void* p);   // 0x00f47380

struct Base_b5cd10 {
    virtual void b0();
    ~Base_b5cd10();          // 0x0083c750
};
struct Object_b5cd10 : Base_b5cd10 {
    virtual void v0();
    ~Object_b5cd10() { (void)this; }
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00b5cd10
void* Object_b5cd10::DeletingDtor(unsigned int flags)
{
    this->~Object_b5cd10();
    if (flags & 1)
        Free_b5cd10(this);
    return this;
}
