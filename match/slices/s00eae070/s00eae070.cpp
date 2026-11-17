// Scalar deleting destructor (0x00eae070): run the destructor (0xeadb30), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_eae070(void* p);   // 0x00f47380

struct Object_eae070 {
    ~Object_eae070();        // 0x00eadb30
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00eae070
void* Object_eae070::DeletingDtor(unsigned int flags)
{
    this->~Object_eae070();
    if (flags & 1)
        Free_eae070(this);
    return this;
}
