// Scalar deleting destructor (0x00674620): run the destructor (0x673710), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_674620(void* p);   // 0x00f47380

struct Object_674620 {
    ~Object_674620();        // 0x00673710
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00674620
void* Object_674620::DeletingDtor(unsigned int flags)
{
    this->~Object_674620();
    if (flags & 1)
        Free_674620(this);
    return this;
}
