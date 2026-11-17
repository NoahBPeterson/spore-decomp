// Scalar deleting destructor (0x0107c490): run the destructor (0x107c160), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_107c490(void* p);   // 0x00f47380

struct Object_107c490 {
    ~Object_107c490();        // 0x0107c160
    void* DeletingDtor(unsigned int flags);
};

// @ 0x0107c490
void* Object_107c490::DeletingDtor(unsigned int flags)
{
    this->~Object_107c490();
    if (flags & 1)
        Free_107c490(this);
    return this;
}
