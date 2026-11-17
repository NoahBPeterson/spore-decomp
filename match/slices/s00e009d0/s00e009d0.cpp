// Scalar deleting destructor (0x00e009d0): run the destructor (0xe00970), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_e009d0(void* p);   // 0x00f47380

struct Object_e009d0 {
    ~Object_e009d0();        // 0x00e00970
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00e009d0
void* Object_e009d0::DeletingDtor(unsigned int flags)
{
    this->~Object_e009d0();
    if (flags & 1)
        Free_e009d0(this);
    return this;
}
