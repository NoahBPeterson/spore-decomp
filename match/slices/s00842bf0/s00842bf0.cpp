// Scalar deleting destructor (0x00842bf0): run the destructor (0x842b70), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_842bf0(void* p);   // 0x00f47380

struct Object_842bf0 {
    ~Object_842bf0();        // 0x00842b70
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00842bf0
void* Object_842bf0::DeletingDtor(unsigned int flags)
{
    this->~Object_842bf0();
    if (flags & 1)
        Free_842bf0(this);
    return this;
}
