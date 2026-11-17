// Scalar deleting destructor (0x00816970): run the destructor (0x816910), then free the object (0x951330) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_816970(void* p);   // 0x00951330

struct Object_816970 {
    ~Object_816970();        // 0x00816910
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00816970
void* Object_816970::DeletingDtor(unsigned int flags)
{
    this->~Object_816970();
    if (flags & 1)
        Free_816970(this);
    return this;
}
