// Scalar deleting destructor (0x00627640): run the destructor (0x6275d0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_627640(void* p);   // 0x00f47380

struct Object_627640 {
    ~Object_627640();        // 0x006275d0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00627640
void* Object_627640::DeletingDtor(unsigned int flags)
{
    this->~Object_627640();
    if (flags & 1)
        Free_627640(this);
    return this;
}
