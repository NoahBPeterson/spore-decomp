// Scalar deleting destructor (0x0107da70): its inline destructor restores the vtable and runs the base destructor (0x107d740), then the object is freed (0xf47380) when bit 0 of the flags is set.
#include "game/types.h"

void Free_107da70(void* p);   // 0x00f47380

struct Base_107da70 {
    virtual void b0();
    ~Base_107da70();          // 0x0107d740
};
struct Object_107da70 : Base_107da70 {
    virtual void v0();
    ~Object_107da70() { (void)this; }
    void* DeletingDtor(unsigned int flags);
};

// @ 0x0107da70
void* Object_107da70::DeletingDtor(unsigned int flags)
{
    this->~Object_107da70();
    if (flags & 1)
        Free_107da70(this);
    return this;
}
