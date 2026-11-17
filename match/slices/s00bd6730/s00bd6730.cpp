// Scalar deleting destructor (0x00bd6730): run the destructor (0xbd6530), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_bd6730(void* p);   // 0x00f47380

struct Object_bd6730 {
    ~Object_bd6730();        // 0x00bd6530
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00bd6730
void* Object_bd6730::DeletingDtor(unsigned int flags)
{
    this->~Object_bd6730();
    if (flags & 1)
        Free_bd6730(this);
    return this;
}
