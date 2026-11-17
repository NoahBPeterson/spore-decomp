// Scalar deleting destructor (0x0059c810): run the destructor (0x59c5f0), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_59c810(void* p);   // 0x00f47380

struct Object_59c810 {
    ~Object_59c810();        // 0x0059c5f0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x0059c810
void* Object_59c810::DeletingDtor(unsigned int flags)
{
    this->~Object_59c810();
    if (flags & 1)
        Free_59c810(this);
    return this;
}
