// Scalar deleting destructor (0x00713c20): run the destructor (0x713780), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_713c20(void* p);   // 0x00f47380

struct Object_713c20 {
    ~Object_713c20();        // 0x00713780
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00713c20
void* Object_713c20::DeletingDtor(unsigned int flags)
{
    this->~Object_713c20();
    if (flags & 1)
        Free_713c20(this);
    return this;
}
