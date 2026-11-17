// Scalar deleting destructor (0x00ed8760): run the destructor (0xed8610), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_ed8760(void* p);   // 0x00f47380

struct Object_ed8760 {
    ~Object_ed8760();        // 0x00ed8610
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00ed8760
void* Object_ed8760::DeletingDtor(unsigned int flags)
{
    this->~Object_ed8760();
    if (flags & 1)
        Free_ed8760(this);
    return this;
}
