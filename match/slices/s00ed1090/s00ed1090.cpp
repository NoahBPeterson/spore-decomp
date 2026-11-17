// Scalar deleting destructor (0x00ed1090): run the destructor (0xed0b00), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_ed1090(void* p);   // 0x00f47380

struct Object_ed1090 {
    ~Object_ed1090();        // 0x00ed0b00
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00ed1090
void* Object_ed1090::DeletingDtor(unsigned int flags)
{
    this->~Object_ed1090();
    if (flags & 1)
        Free_ed1090(this);
    return this;
}
