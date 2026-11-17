// Scalar deleting destructor (0x0076c640): run the destructor (0x76b6c0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_76c640(void* p);   // 0x00f47380

struct Object_76c640 {
    ~Object_76c640();        // 0x0076b6c0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x0076c640
void* Object_76c640::DeletingDtor(unsigned int flags)
{
    this->~Object_76c640();
    if (flags & 1)
        Free_76c640(this);
    return this;
}
