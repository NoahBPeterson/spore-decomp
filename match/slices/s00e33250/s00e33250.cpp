// Scalar deleting destructor (0x00e33250): run the destructor (0xe32c80), then free the object (0x951330) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_e33250(void* p);   // 0x00951330

struct Object_e33250 {
    ~Object_e33250();        // 0x00e32c80
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00e33250
void* Object_e33250::DeletingDtor(unsigned int flags)
{
    this->~Object_e33250();
    if (flags & 1)
        Free_e33250(this);
    return this;
}
