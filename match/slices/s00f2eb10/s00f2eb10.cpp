// Scalar deleting destructor (0x00f2eb10): run the destructor (0xdfef70), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_f2eb10(void* p);   // 0x00f47380

struct Object_f2eb10 {
    ~Object_f2eb10();        // 0x00dfef70
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00f2eb10
void* Object_f2eb10::DeletingDtor(unsigned int flags)
{
    this->~Object_f2eb10();
    if (flags & 1)
        Free_f2eb10(this);
    return this;
}
