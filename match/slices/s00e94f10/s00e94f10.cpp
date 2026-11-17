// Scalar deleting destructor (0x00e94f10): run the destructor (0xe94c50), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_e94f10(void* p);   // 0x00f47380

struct Object_e94f10 {
    ~Object_e94f10();        // 0x00e94c50
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00e94f10
void* Object_e94f10::DeletingDtor(unsigned int flags)
{
    this->~Object_e94f10();
    if (flags & 1)
        Free_e94f10(this);
    return this;
}
