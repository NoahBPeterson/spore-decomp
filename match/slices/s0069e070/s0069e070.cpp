// Scalar deleting destructor (0x0069e070): run the destructor (0x69d400), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_69e070(void* p);   // 0x00f47380

struct Object_69e070 {
    ~Object_69e070();        // 0x0069d400
    void* DeletingDtor(unsigned int flags);
};

// @ 0x0069e070
void* Object_69e070::DeletingDtor(unsigned int flags)
{
    this->~Object_69e070();
    if (flags & 1)
        Free_69e070(this);
    return this;
}
