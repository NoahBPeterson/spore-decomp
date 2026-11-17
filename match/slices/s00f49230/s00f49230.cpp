// Scalar deleting destructor (0x00f49230): run the destructor (0xf48b00), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_f49230(void* p);   // 0x00f47380

struct Object_f49230 {
    ~Object_f49230();        // 0x00f48b00
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00f49230
void* Object_f49230::DeletingDtor(unsigned int flags)
{
    this->~Object_f49230();
    if (flags & 1)
        Free_f49230(this);
    return this;
}
