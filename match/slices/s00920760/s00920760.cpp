// Scalar deleting destructor (0x00920760): run the destructor (0x920410), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_920760(void* p);   // 0x00f47380

struct Object_920760 {
    ~Object_920760();        // 0x00920410
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00920760
void* Object_920760::DeletingDtor(unsigned int flags)
{
    this->~Object_920760();
    if (flags & 1)
        Free_920760(this);
    return this;
}
