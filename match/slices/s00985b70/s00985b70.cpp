// Scalar deleting destructor (0x00985b70): run the destructor (0x9849d0), then free the object (0x951330) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_985b70(void* p);   // 0x00951330

struct Object_985b70 {
    ~Object_985b70();        // 0x009849d0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00985b70
void* Object_985b70::DeletingDtor(unsigned int flags)
{
    this->~Object_985b70();
    if (flags & 1)
        Free_985b70(this);
    return this;
}
