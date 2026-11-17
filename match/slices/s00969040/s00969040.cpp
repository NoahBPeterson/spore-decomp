// Scalar deleting destructor (0x00969040): run the destructor (0x968d10), then free the object (0x951330) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_969040(void* p);   // 0x00951330

struct Object_969040 {
    ~Object_969040();        // 0x00968d10
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00969040
void* Object_969040::DeletingDtor(unsigned int flags)
{
    this->~Object_969040();
    if (flags & 1)
        Free_969040(this);
    return this;
}
