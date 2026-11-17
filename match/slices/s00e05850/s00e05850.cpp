// Scalar deleting destructor (0x00e05850): run the destructor (0xe04f10), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_e05850(void* p);   // 0x00f47380

struct Object_e05850 {
    ~Object_e05850();        // 0x00e04f10
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00e05850
void* Object_e05850::DeletingDtor(unsigned int flags)
{
    this->~Object_e05850();
    if (flags & 1)
        Free_e05850(this);
    return this;
}
