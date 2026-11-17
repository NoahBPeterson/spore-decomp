// Scalar deleting destructor (0x00e0ff60): run the destructor (0xe0f810), then free the object (0x951330) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_e0ff60(void* p);   // 0x00951330

struct Object_e0ff60 {
    ~Object_e0ff60();        // 0x00e0f810
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00e0ff60
void* Object_e0ff60::DeletingDtor(unsigned int flags)
{
    this->~Object_e0ff60();
    if (flags & 1)
        Free_e0ff60(this);
    return this;
}
