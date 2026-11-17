// Scalar deleting destructor (0x0069e380): run the destructor (0x69dca0), then free the object (0x926060) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_69e380(void* p);   // 0x00926060

struct Object_69e380 {
    ~Object_69e380();        // 0x0069dca0
    void* DeletingDtor(unsigned int flags);
};

// @ 0x0069e380
void* Object_69e380::DeletingDtor(unsigned int flags)
{
    this->~Object_69e380();
    if (flags & 1)
        Free_69e380(this);
    return this;
}
