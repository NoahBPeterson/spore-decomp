// Scalar deleting destructor (0x008d9990): run the destructor (0x8d93e0), then free the object (0x926060) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_8d9990(void* p);   // 0x00926060

struct Object_8d9990 {
    ~Object_8d9990();        // 0x008d93e0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x008d9990
void* Object_8d9990::DeletingDtor(unsigned int flags)
{
    this->~Object_8d9990();
    if (flags & 1)
        Free_8d9990(this);
    return this;
}
