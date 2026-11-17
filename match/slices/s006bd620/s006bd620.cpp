// Scalar deleting destructor (0x006bd620): run the destructor (0x6bd300), then free the object (0x926060) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_6bd620(void* p);   // 0x00926060

struct Object_6bd620 {
    ~Object_6bd620();        // 0x006bd300
    void* DeletingDtor(unsigned int flags);
};

// @ 0x006bd620
void* Object_6bd620::DeletingDtor(unsigned int flags)
{
    this->~Object_6bd620();
    if (flags & 1)
        Free_6bd620(this);
    return this;
}
