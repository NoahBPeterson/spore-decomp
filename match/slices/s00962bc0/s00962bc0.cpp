// Scalar deleting destructor (0x00962bc0): run the destructor (0x962740), then free the object (0x951330) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_962bc0(void* p);   // 0x00951330

struct Object_962bc0 {
    ~Object_962bc0();        // 0x00962740
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00962bc0
void* Object_962bc0::DeletingDtor(unsigned int flags)
{
    this->~Object_962bc0();
    if (flags & 1)
        Free_962bc0(this);
    return this;
}
