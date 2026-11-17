// Scalar deleting destructor (0x007afee0): run the destructor (0x7aea30), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_7afee0(void* p);   // 0x00f47380

struct Object_7afee0 {
    ~Object_7afee0();        // 0x007aea30
    void* DeletingDtor(unsigned int flags);
};

// @ 0x007afee0
void* Object_7afee0::DeletingDtor(unsigned int flags)
{
    this->~Object_7afee0();
    if (flags & 1)
        Free_7afee0(this);
    return this;
}
