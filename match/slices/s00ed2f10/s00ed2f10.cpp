// Scalar deleting destructor (0x00ed2f10): run the destructor (0xed2bc0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_ed2f10(void* p);   // 0x00f47380

struct Object_ed2f10 {
    ~Object_ed2f10();        // 0x00ed2bc0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00ed2f10
void* Object_ed2f10::DeletingDtor(unsigned int flags)
{
    this->~Object_ed2f10();
    if (flags & 1)
        Free_ed2f10(this);
    return this;
}
