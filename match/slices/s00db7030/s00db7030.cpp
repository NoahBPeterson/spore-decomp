// Scalar deleting destructor (0x00db7030): run the destructor (0xdb6db0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_db7030(void* p);   // 0x00f47380

struct Object_db7030 {
    ~Object_db7030();        // 0x00db6db0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00db7030
void* Object_db7030::DeletingDtor(unsigned int flags)
{
    this->~Object_db7030();
    if (flags & 1)
        Free_db7030(this);
    return this;
}
