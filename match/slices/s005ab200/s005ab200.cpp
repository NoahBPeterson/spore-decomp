// Scalar deleting destructor (0x005ab200): run the destructor (0x5aad00), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_5ab200(void* p);   // 0x00f47380

struct Object_5ab200 {
    ~Object_5ab200();        // 0x005aad00
    void* DeletingDtor(unsigned int flags);
};

// @ 0x005ab200
void* Object_5ab200::DeletingDtor(unsigned int flags)
{
    this->~Object_5ab200();
    if (flags & 1)
        Free_5ab200(this);
    return this;
}
