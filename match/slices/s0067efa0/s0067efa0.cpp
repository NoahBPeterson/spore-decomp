// Scalar deleting destructor (0x0067efa0): run the destructor (0x67ea40), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_67efa0(void* p);   // 0x00f47380

struct Object_67efa0 {
    ~Object_67efa0();        // 0x0067ea40
    void* DeletingDtor(unsigned int flags);
};

// @ 0x0067efa0
void* Object_67efa0::DeletingDtor(unsigned int flags)
{
    this->~Object_67efa0();
    if (flags & 1)
        Free_67efa0(this);
    return this;
}
