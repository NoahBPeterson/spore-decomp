// Scalar deleting destructor (0x00832990): run the destructor (0x832710), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_832990(void* p);   // 0x00f47380

struct Object_832990 {
    ~Object_832990();        // 0x00832710
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00832990
void* Object_832990::DeletingDtor(unsigned int flags)
{
    this->~Object_832990();
    if (flags & 1)
        Free_832990(this);
    return this;
}
