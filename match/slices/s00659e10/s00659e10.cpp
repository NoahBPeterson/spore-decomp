// Scalar deleting destructor (0x00659e10): run the destructor (0x6580b0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_659e10(void* p);   // 0x00f47380

struct Object_659e10 {
    ~Object_659e10();        // 0x006580b0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00659e10
void* Object_659e10::DeletingDtor(unsigned int flags)
{
    this->~Object_659e10();
    if (flags & 1)
        Free_659e10(this);
    return this;
}
