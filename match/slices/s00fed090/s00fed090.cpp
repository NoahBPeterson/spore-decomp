// Scalar deleting destructor (0x00fed090): run the destructor (0xfece20), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_fed090(void* p);   // 0x00f47380

struct Object_fed090 {
    ~Object_fed090();        // 0x00fece20
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00fed090
void* Object_fed090::DeletingDtor(unsigned int flags)
{
    this->~Object_fed090();
    if (flags & 1)
        Free_fed090(this);
    return this;
}
