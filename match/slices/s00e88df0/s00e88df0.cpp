// Scalar deleting destructor (0x00e88df0): run the destructor (0xe87be0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_e88df0(void* p);   // 0x00f47380

struct Object_e88df0 {
    ~Object_e88df0();        // 0x00e87be0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00e88df0
void* Object_e88df0::DeletingDtor(unsigned int flags)
{
    this->~Object_e88df0();
    if (flags & 1)
        Free_e88df0(this);
    return this;
}
