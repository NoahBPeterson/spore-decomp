// Scalar deleting destructor (0x00e36460): run the destructor (0xe36260), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_e36460(void* p);   // 0x00f47380

struct Object_e36460 {
    ~Object_e36460();        // 0x00e36260
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00e36460
void* Object_e36460::DeletingDtor(unsigned int flags)
{
    this->~Object_e36460();
    if (flags & 1)
        Free_e36460(this);
    return this;
}
