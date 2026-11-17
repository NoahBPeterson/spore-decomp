// Scalar deleting destructor (0x0068f160): run the destructor (0x68f050), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_68f160(void* p);   // 0x00f47380

struct Object_68f160 {
    ~Object_68f160();        // 0x0068f050
    void* DeletingDtor(unsigned int flags);
};

// @ 0x0068f160
void* Object_68f160::DeletingDtor(unsigned int flags)
{
    this->~Object_68f160();
    if (flags & 1)
        Free_68f160(this);
    return this;
}
