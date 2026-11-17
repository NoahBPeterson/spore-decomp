// Scalar deleting destructor (0x0063cad0): run the destructor (0x63c3f0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_63cad0(void* p);   // 0x00f47380

struct Object_63cad0 {
    ~Object_63cad0();        // 0x0063c3f0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x0063cad0
void* Object_63cad0::DeletingDtor(unsigned int flags)
{
    this->~Object_63cad0();
    if (flags & 1)
        Free_63cad0(this);
    return this;
}
