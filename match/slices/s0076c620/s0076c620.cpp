// Scalar deleting destructor (0x0076c620): run the destructor (0x76b3c0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_76c620(void* p);   // 0x00f47380

struct Object_76c620 {
    ~Object_76c620();        // 0x0076b3c0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x0076c620
void* Object_76c620::DeletingDtor(unsigned int flags)
{
    this->~Object_76c620();
    if (flags & 1)
        Free_76c620(this);
    return this;
}
