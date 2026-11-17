// Scalar deleting destructor (0x00f93990): run the destructor (0xf93420), then free the object (0xf47380) when bit 0 of
// the flags is set.
#include "game/types.h"

void Free_f93990(void* p);   // 0x00f47380

struct Object_f93990 {
    ~Object_f93990();        // 0x00f93420
    void* DeletingDtor(unsigned int flags);
};

// @ 0x00f93990
void* Object_f93990::DeletingDtor(unsigned int flags)
{
    this->~Object_f93990();
    if (flags & 1)
        Free_f93990(this);
    return this;
}
