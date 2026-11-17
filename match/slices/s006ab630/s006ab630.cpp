// Scalar deleting destructor (0x006ab630): run the destructor (0x6aae30), then free the object (0x926060) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_6ab630(void* p);   // 0x00926060

struct Object_6ab630 {
    ~Object_6ab630();        // 0x006aae30
    void* DeletingDtor(unsigned int flags);
};

// @ 0x006ab630
void* Object_6ab630::DeletingDtor(unsigned int flags)
{
    this->~Object_6ab630();
    if (flags & 1)
        Free_6ab630(this);
    return this;
}
