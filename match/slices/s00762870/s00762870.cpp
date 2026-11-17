// Scalar deleting destructor (0x00762870): run the destructor (0x7622e0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_762870(void* p);   // 0x00f47380

struct Object_762870 {
    ~Object_762870();        // 0x007622e0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00762870
void* Object_762870::DeletingDtor(unsigned int flags)
{
    this->~Object_762870();
    if (flags & 1)
        Free_762870(this);
    return this;
}
