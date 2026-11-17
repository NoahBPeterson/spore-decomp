// Scalar deleting destructor (0x00fc6930): run the destructor (0xfc57b0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_fc6930(void* p);   // 0x00f47380

struct Object_fc6930 {
    ~Object_fc6930();        // 0x00fc57b0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00fc6930
void* Object_fc6930::DeletingDtor(unsigned int flags)
{
    this->~Object_fc6930();
    if (flags & 1)
        Free_fc6930(this);
    return this;
}
