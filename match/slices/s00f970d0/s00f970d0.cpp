// Scalar deleting destructor (0x00f970d0): run the destructor (0xf8f970), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_f970d0(void* p);   // 0x00f47380

struct Object_f970d0 {
    ~Object_f970d0();        // 0x00f8f970
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00f970d0
void* Object_f970d0::DeletingDtor(unsigned int flags)
{
    this->~Object_f970d0();
    if (flags & 1)
        Free_f970d0(this);
    return this;
}
