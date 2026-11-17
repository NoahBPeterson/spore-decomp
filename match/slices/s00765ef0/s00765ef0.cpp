// Scalar deleting destructor (0x00765ef0): run the destructor (0x765580), then free the object (0x926060) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_765ef0(void* p);   // 0x00926060

struct Object_765ef0 {
    ~Object_765ef0();        // 0x00765580
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00765ef0
void* Object_765ef0::DeletingDtor(unsigned int flags)
{
    this->~Object_765ef0();
    if (flags & 1)
        Free_765ef0(this);
    return this;
}
